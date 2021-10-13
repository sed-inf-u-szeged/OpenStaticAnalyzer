using System;
using System.Linq;
using Columbus.CSAN.Contexts;
using Columbus.CSAN.Extensions;
using Columbus.Lim.Asg;
using Columbus.Lim.Asg.Nodes.Base;
using Columbus.Lim.Asg.Nodes.Logical;
using Columbus.Lim.Asg.Nodes.Physical;
using Microsoft.CodeAnalysis;
using Type = Columbus.Lim.Asg.Nodes.Type.Type;

namespace Columbus.CSAN.LimBuilder
{
    class SymbolConverter
    {
        private readonly FileContext fileContext; // TODO do we really need file and project context?
        private readonly ProjectContext projectContext;
        private readonly SolutionContext solutionContext;
        private readonly Factory limFactory;

        public SymbolConverter(FileContext fileContext)
        {
            this.fileContext = fileContext;
            projectContext = fileContext.ProjectContext;
            solutionContext = projectContext.SolutionContext;
            limFactory = solutionContext.LimFactory;
        }

        public ISymbol GetDefinition(ISymbol symbol, out SyntaxNode node, bool needParent = false)
        {
            node = null;
            if (symbol.Locations.IsEmpty)
                return null;

            var location = symbol.Locations[0];
            if (location.IsInMetadata)
                return null;

            if (symbol is ITypeSymbol typeSymbol && typeSymbol.IsTupleType)
                return typeSymbol;

            solutionContext.WatchBag.RoslynWatch.Start();
            var model = solutionContext.Solution.GetDocument(location.SourceTree).GetSemanticModelAsync().Result;
            var root = model.SyntaxTree.GetRoot();
            var calledNode = root.FindNode(location.SourceSpan);
            if (calledNode != null)
            {
                node = calledNode;
                var newSymbol = model.GetDeclaredSymbol(needParent ? calledNode.Parent : calledNode);
                solutionContext.WatchBag.RoslynWatch.Stop();
                return newSymbol;
            }
            solutionContext.WatchBag.RoslynWatch.Stop();

            return null;
        }

        /// <summary>
        /// Type building strategy
        /// </summary>
        /// <param name="node"></param>
        /// <param name="refs"></param>
        private void AddLimTypeFormers(ISymbol node, ISymbol refs = null)
        {
            switch (node)
            {
                case IArrayTypeSymbol arrayTypeSymbol:
                    limFactory.addTypeFormer(limFactory.createTypeFormerArray().Id);
                    if (arrayTypeSymbol.ElementType != null)
                    {
                        if (arrayTypeSymbol.ElementType.IsInMetadata())
                            AddLimTypeFormers(arrayTypeSymbol.ElementType);
                        else
                        {
                            SyntaxNode syntaxNode;
                            var @ref = GetDefinition(arrayTypeSymbol.ElementType, out syntaxNode);
                            if (@ref != null && @ref.Kind == arrayTypeSymbol.ElementType.Kind)
                                if (@ref is INamedTypeSymbol && ((INamedTypeSymbol)@ref).IsGenericType)
                                    AddLimTypeFormers(arrayTypeSymbol.ElementType, @ref);
                                else
                                    AddLimTypeFormers(@ref);
                        }
                    }
                    break;

                case ITypeParameterSymbol typeParameterSymbol:
                    GenericParameter gp = (GenericParameter)ConvertToLimNode(typeParameterSymbol);
                    if (gp == null)
                        return;
                    limFactory.addTypeFormer(limFactory.createTypeFormerType(gp.Id).Id);
                    break;

                case IPointerTypeSymbol pointerTypeSymbol:
                    limFactory.addTypeFormer(
                        limFactory.createTypeFormerPointer(
                            pointerTypeSymbol.IsReferenceType ? Types.PointerKind.ptkReference : Types.PointerKind.ptkPointer
                        ).Id);
                    AddLimTypeFormers(pointerTypeSymbol.PointedAtType);
                    break;

                case INamedTypeSymbol namedTypeSymbol when namedTypeSymbol.Name != string.Empty || !(namedTypeSymbol is IErrorTypeSymbol):
                    if (namedTypeSymbol.IsGenericType)
                    {
                        ClassGenericInstance cgi = GetOrCreateClassGenericInstance(namedTypeSymbol, refs as INamedTypeSymbol);
                        limFactory.addTypeFormer(
                            limFactory.createTypeFormerType(cgi.Id).Id
                        );
                    }
                    else
                    {
                        Types.SimpleTypeKind stk = Types.SimpleTypeKind.stkUnknown;

                        switch (namedTypeSymbol.SpecialType)
                        {
                            case SpecialType.System_Object: stk = Types.SimpleTypeKind.stkObject; break;
                            case SpecialType.System_Void: stk = Types.SimpleTypeKind.stkVoid; break;
                            case SpecialType.System_Single: stk = Types.SimpleTypeKind.stkSingle; break;
                            case SpecialType.System_Boolean: stk = Types.SimpleTypeKind.stkBoolean; break;
                            case SpecialType.System_Char: stk = Types.SimpleTypeKind.stkCharacter; break;
                            case SpecialType.System_SByte: stk = Types.SimpleTypeKind.stkByte; break;
                            case SpecialType.System_Byte: stk = Types.SimpleTypeKind.stkByte; break;
                            case SpecialType.System_Int16: stk = Types.SimpleTypeKind.stkShort; break;
                            case SpecialType.System_UInt16: stk = Types.SimpleTypeKind.stkUnsignedShort; break;
                            case SpecialType.System_Int32: stk = Types.SimpleTypeKind.stkInteger; break;
                            case SpecialType.System_UInt32: stk = Types.SimpleTypeKind.stkUnsignedInteger; break;
                            case SpecialType.System_Int64: stk = Types.SimpleTypeKind.stkLong; break;
                            case SpecialType.System_UInt64: stk = Types.SimpleTypeKind.stkUnsignedLong; break;
                            case SpecialType.System_Decimal: stk = Types.SimpleTypeKind.stkDecimal; break;
                            case SpecialType.System_Double: stk = Types.SimpleTypeKind.stkDouble; break;
                            case SpecialType.System_String: stk = Types.SimpleTypeKind.stkString; break;
                            default:
                                if (!node.IsInMetadata() && GetDefinition(node, out _) == null)
                                    break;

                                Base refLimNode = ConvertToLimNode(node);
                                if (node.IsInMetadata())
                                    Commons.Common.MetaDataNameFiller(node, (Member)refLimNode);

                                limFactory.addTypeFormer(limFactory.createTypeFormerType(refLimNode.Id).Id);
                                return;
                        }

                        limFactory.addTypeFormer(
                            limFactory.createTypeFormerType(
                                limFactory.createSimpleType(stk).Id
                            ).Id
                        );
                    }
                    break;
                default:
                    limFactory.addTypeFormer(limFactory.createTypeFormerNonType().Id);
                    break;
            }
        }

        /// <summary>
        /// Create ClassGenericInstance and connect to the Class, through the Instance edge.
        /// Furthermore, added GenericParameter to the ClassGenericInstance.
        /// </summary>
        /// <param name="symbol">Instanced class</param>
        /// <param name="refersTo">Instanced class definition</param>
        /// <returns>ClassGenericInstance from the LIM</returns>
        private ClassGenericInstance GetOrCreateClassGenericInstance(INamedTypeSymbol symbol, INamedTypeSymbol refersTo)
        {
            string uName = symbol.ToString();
            ClassGenericInstance cgi;
            if (solutionContext.CgiMap.TryGetValue(uName, out cgi))
                return cgi;

            cgi = limFactory.createClassGenericInstanceNode();
            cgi.IsRealInstance = true;
            cgi.Name = symbol.ToDisplayString(SymbolDisplayFormat.MinimallyQualifiedFormat);  // TODO why minimally qualified?
            cgi.MangledName = uName;
            cgi.DemangledName = uName;
            cgi.Language = Types.LanguageKind.lnkCsharp;

            solutionContext.CgiMap.Add(uName, cgi);

            bool isInMeta = false;

            if (refersTo == null)
            {
                refersTo = symbol.OriginalDefinition;
                if (refersTo == null)
                    return cgi;

                isInMeta = true;
            }

            Base owner = ConvertToLimNode(refersTo);

            if (isInMeta)
                Commons.Common.MetaDataNameFiller(symbol, (Member)owner); // TODO should be refersTo instead of symbol?

            if (!Lim.Asg.Common.getIsClass(owner))
                return cgi;

            Class ownerClass = owner as Class;
            Commons.Common.Safe_Edge(ownerClass, "Instance", cgi.Id);

            int i = 0;
            foreach (var argument in symbol.TypeArguments)
            {
                ITypeSymbol arg = null;
                if (!argument.IsInMetadata() && argument.TypeKind != TypeKind.TypeParameter)
                {
                    SyntaxNode tmp;
                    arg = (INamedTypeSymbol)GetDefinition(argument, out tmp);
                }
                Type param = arg != null ? GetLimType(arg) : GetLimType(argument);
                fileContext.UsesStack.Peek().Remove(param.Id);

                Types.TypeArgumentConstraintKind tack = Types.TypeArgumentConstraintKind.tackUpperBounded;
                if (symbol.TypeParameters[i].ConstraintTypes.Length > 0)
                {
                    tack = Types.TypeArgumentConstraintKind.tackUnbounded;
                }

                bool found = false;
                ListIteratorAssocTypeArgumentConstraintKind<Type> cIt = cgi.HasArgumentsListIteratorAssocBegin;
                while (cIt.getValue() != null)
                {
                    Type value = cIt.getValue();
                    if (param.Id == value.Id)
                    {
                        found = true;
                        break;
                    }
                    cIt = cIt.getNext();
                }
                if (!found)
                    cgi.addHasArguments(param, tack);
                i++;
            }

            return cgi;
        }

        /// <summary>
        /// Create MethodGenericInstance and connect to the Method, through the Instance edge.
        /// Furthermore, added GenericParameter to the MethodGenericInstance.
        /// </summary>
        /// <param name="symbol">Called method</param>
        /// <param name="refersTo">Called method definition</param>
        /// <returns>MethodGenericInstance node from the LIM</returns>
        public MethodGenericInstance GetOrCreateMethodGenericInstance(IMethodSymbol symbol, IMethodSymbol refersTo)
        {
            string uName = symbol.ToString();
            MethodGenericInstance mgi;
            if (solutionContext.MgiMap.TryGetValue(uName, out mgi))
                return mgi;

            mgi = limFactory.createMethodGenericInstanceNode();
            mgi.IsRealInstance = true;
            mgi.Name = symbol.ToDisplayString(SymbolDisplayFormat.MinimallyQualifiedFormat);
            mgi.MangledName = uName;
            mgi.DemangledName = uName;
            mgi.Language = Types.LanguageKind.lnkCsharp;

            Base owner = refersTo != null ? ConvertToLimNode(refersTo) : ConvertToLimNode(symbol.OriginalDefinition);
            if (owner == null) return null;
            if (Lim.Asg.Common.getIsMethod(owner))
            {
                Method ownerMethod = owner as Method;
                Commons.Common.Safe_Edge(ownerMethod, "Instance", mgi.Id);

                if (symbol.Arity > 0)
                {
                    int i = 0;
                    foreach (var argument in symbol.TypeArguments)
                    {
                        ITypeSymbol arg = null;
                        if (!argument.IsInMetadata() && argument.TypeKind != TypeKind.TypeParameter)
                        {
                            SyntaxNode discard;
                            arg = (INamedTypeSymbol)GetDefinition(argument, out discard);
                        }
                        Type param = (arg != null) ? GetLimType(arg) : GetLimType(argument);
                        fileContext.UsesStack.Peek().Remove(param.Id);

                        Types.TypeArgumentConstraintKind tack = Types.TypeArgumentConstraintKind.tackUpperBounded;
                        if (symbol.TypeParameters[i].ConstraintTypes.Any())
                        {
                            tack = Types.TypeArgumentConstraintKind.tackUnbounded;
                        }

                        bool found = false;
                        ListIteratorAssocTypeArgumentConstraintKind<Type> cIt = mgi.HasArgumentsListIteratorAssocBegin;
                        while (cIt.getValue() != null)
                        {
                            Type value = cIt.getValue();
                            if (param.Id == value.Id)
                            {
                                found = true;
                                break;
                            }
                            cIt = cIt.getNext();
                        }
                        if (!found)
                            mgi.addHasArguments(param, tack);
                        i++;
                    }
                }
            }

            solutionContext.MgiMap.Add(uName, mgi);

            return mgi;
        }

        /// <summary>
        /// Get symbol "parent" if it is LIM compatible
        /// </summary>
        /// <param name="symbol"></param>
        /// <returns></returns>
        public ISymbol Parent(ISymbol symbol)
        {
            while (symbol?.ContainingSymbol != null)
            {
                symbol = symbol.ContainingSymbol;
                if (symbol != null && symbol.Kind != SymbolKind.NetModule && symbol.Kind != SymbolKind.Assembly && symbol.Kind != SymbolKind.Namespace)
                {
                    SyntaxNode discard;
                    var tmp = GetDefinition(symbol, out discard);
                    if (tmp != null)
                        symbol = tmp;
                }
                if (symbol.IsLimCompatibile())
                    return symbol;
            }

            return null;
        }

        /// <summary>
        /// Create LIM type from symbol if it is not exists
        /// </summary>
        /// <param name="symbol"></param>
        /// <param name="refs"></param>
        /// <returns>LIM Type node</returns>
        public Type GetLimType(ISymbol symbol, ISymbol refs = null)
        {
            Type result;
            if (solutionContext.TypeMap.TryGetValue(symbol, out result))
                return result;

            limFactory.beginType();
            AddLimTypeFormers(symbol, refs);
            result = limFactory.endType();

            solutionContext.TypeMap.Add(symbol, result);

            return result;
        }

        /// <summary>
        /// Create LIM node from Symbol
        /// </summary>
        /// <param name="symbol">SyntaxNode's symbol</param>
        /// <returns>LIM node</returns>
        private Base Create(ISymbol symbol)
        {
            Named newLimNode = (Named)limFactory.createNode(symbol.GetLimKind());
            newLimNode.Name = symbol.Name;

            if (Lim.Asg.Common.getIsMember(newLimNode))
                ((Member)newLimNode).Language = Types.LanguageKind.lnkCsharp;


            solutionContext.MainMap.Add(symbol, newLimNode.Id);

            return newLimNode;
        }

        /// <summary>
        /// ASG node to LIM node
        /// if already not exists the LIM node then we'll create one if it's LIM compatible
        /// </summary>
        /// <param name="symbol">ASG node</param>
        /// <returns>LIM node</returns>
        public Base ConvertToLimNode(ISymbol symbol)
        {
            uint id;

            if (solutionContext.MainMap.TryGetValue(symbol, out id))
                return limFactory.getRef(id);

            return symbol.IsLimCompatibile() ? Create(symbol) : null;
        }

        public void CreateCommentNode(SyntaxNode node, ISymbol symbol)
        {
            string commentStr = node.GetDocumentationComment();
            if (commentStr == String.Empty)
                return;
            if (symbol.IsLimCompatibile())
            {
                Member limNode = ConvertToLimNode(symbol) as Member;

                Comment comment = limFactory.createCommentNode(commentStr.TrimEnd('\r', '\n'));
                Commons.Common.Safe_Edge(limNode, "HasComment", comment.Id);
            }
        }

        /// <summary>
        /// Create File node from Location if it is possible
        /// </summary>
        /// <param name="roslynNode"></param>
        /// <returns>LIM File node</returns>
        public File CreateFile(Location roslynNode)
        {
            if (!solutionContext.HardFilter.IsNecessaryToAnalyse(roslynNode.SourceTree.FilePath))
                return null;

            File file = solutionContext.LimFactory.createFile(solutionContext.ProcessPath(roslynNode.SourceTree.FilePath));
            uint key = solutionContext.LimFactory.StringTable.set(solutionContext.ProcessPath(roslynNode.SourceTree.FilePath));
            if (!solutionContext.FileMap.ContainsKey(key))
            {
                solutionContext.FileMap.Add(key, file.Id);
            }


            file.LOC = (uint)roslynNode.GetMappedLineSpan().EndLinePosition.Line + 1;

            return file;
        }
    }
}
