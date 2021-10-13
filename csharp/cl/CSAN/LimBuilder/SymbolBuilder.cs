using System;
using System.Collections.Generic;
using Columbus.Lim.Asg;
using Columbus.Lim.Asg.Nodes.Base;
using Columbus.Lim.Asg.Nodes.Logical;
using Columbus.CSAN.Utils.Info;
using Columbus.CSAN.Extensions;
using Columbus.CSAN.Metrics.Size;
using Microsoft.CodeAnalysis;
using System.Runtime.CompilerServices;
using Columbus.CSAN.Contexts;
using Attribute = Columbus.Lim.Asg.Nodes.Logical.Attribute;
using Type = Columbus.Lim.Asg.Nodes.Type.Type;


namespace Columbus.CSAN.LimBuilder
{
    class SymbolBuilder
    {
        private readonly FileContext fileContext;
        private readonly ProjectContext projectContext;
        private readonly SolutionContext solutionContext;
        private readonly LOC loc;
        private readonly SymbolConverter symbolConverter;
        private readonly EdgeBuilder edgeBuilder;

        public SymbolBuilder(FileContext fileContext)
        {
            this.fileContext = fileContext;
            projectContext = fileContext.ProjectContext;
            solutionContext = projectContext.SolutionContext;
            loc = new LOC(solutionContext);
            symbolConverter = new SymbolConverter(fileContext);
            edgeBuilder = new EdgeBuilder(fileContext);
        }

        /// <summary>
        /// Create LIM node from Roslyn symbol
        /// </summary>
        /// <typeparam name="L"></typeparam>
        /// <typeparam name="R"></typeparam>
        /// <param name="roslynNode"></param>
        /// <param name="setHasMember"></param>
        /// <returns></returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public L BuildDispatch<L, R>(R roslynNode, bool setHasMember = true)
            where L : Base
            where R : ISymbol
        {
            L LimNode = symbolConverter.ConvertToLimNode(roslynNode) as L;
            if (LimNode == null) return default(L);

            if (Lim.Asg.Common.getIsMember(LimNode))
                fileContext.UsesStack.Push(new HashSet<uint>());

            FillData(LimNode, roslynNode, setHasMember);

            return LimNode;
        }

        /// <summary>
        /// Call LIM node propety filler
        /// </summary>
        /// <typeparam name="L"></typeparam>
        /// <typeparam name="R"></typeparam>
        /// <param name="limNode"></param>
        /// <param name="roslynNode"></param>
        /// <param name="setHasMember"></param>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private void FillData<L, R>(L limNode, R roslynNode, bool setHasMember)
            where L : Base
            where R : ISymbol
        {
            switch (limNode.NodeKind)
            {
                case Types.NodeKind.ndkPackage:
                    fillData(limNode as Package, roslynNode as INamespaceSymbol, setHasMember);
                    break;
                case Types.NodeKind.ndkClass:
                    fillData(limNode as Class, roslynNode as INamedTypeSymbol, setHasMember);
                    break;
                case Types.NodeKind.ndkClassGeneric:
                    fillData(limNode as ClassGeneric, roslynNode as INamedTypeSymbol, setHasMember);
                    break;
                case Types.NodeKind.ndkMethod:
                    fillData(limNode as Method, roslynNode as IMethodSymbol, setHasMember);
                    break;
                case Types.NodeKind.ndkMethodGeneric:
                    fillData(limNode as MethodGeneric, roslynNode as IMethodSymbol, setHasMember);
                    break;
                case Types.NodeKind.ndkAttribute:
                    fillData(limNode as Attribute, roslynNode, setHasMember);
                    break;
                case Types.NodeKind.ndkGenericParameter:
                    fillData(limNode as GenericParameter, roslynNode as ITypeParameterSymbol, setHasMember);
                    break;
                case Types.NodeKind.ndkParameter:
                    fillData(limNode as Parameter, roslynNode as IParameterSymbol, setHasMember);
                    break;
            }
        }

        /// <summary>
        /// Fill Package propeties
        /// </summary>
        /// <param name="limNode"></param>
        /// <param name="roslynNode"></param>
        /// <param name="setHasMember"></param>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private void fillData(Package limNode, INamespaceSymbol roslynNode, bool setHasMember)
        {
            fileContext.NamespaceStack.Push(limNode.Id);

            fillScopeData(limNode, roslynNode, setHasMember);

            foreach (var item in roslynNode.DeclaringSyntaxReferences)
            {
                string location = "";
                SyntaxNode syntaxNode = item.GetSyntax();
                if (!roslynNode.IsInMetadata())
                    location = solutionContext.ProcessPath(syntaxNode.SyntaxTree.FilePath);
                uint key = 0;
                if (!String.IsNullOrEmpty(location))
                    key = solutionContext.LimFactory.StringTable.set(location);

                if (key == 0) return;

                if (!roslynNode.IsInMetadata() && !roslynNode.IsGlobalNamespace)
                {
                    edgeBuilder.AddIsContainedInEdge(limNode, syntaxNode);
                    loc.AddLocToComponent(
                        projectContext.Component.Id,
                        key,
                        (ulong)syntaxNode.GetLocation().GetLineSpan().EndLinePosition.Line + 1
                    );
                }
            }
        }

        /// <summary>
        /// Fill Class propeties
        /// </summary>
        /// <param name="limNode"></param>
        /// <param name="roslynNode"></param>
        /// <param name="setHasMember"></param>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private void fillData(Class limNode, INamedTypeSymbol roslynNode, bool setHasMember)
        {
            fileContext.ClassStack.Push(new ClassInfo(limNode.Id));

            fillScopeData(limNode, roslynNode, setHasMember);

            switch (roslynNode.TypeKind)
            {
                case TypeKind.Unknown:
                    break;

                case TypeKind.Class:
                    limNode.ClassKind = Types.ClassKind.clkClass;
                    break;

                case TypeKind.Delegate:
                    limNode.ClassKind = Types.ClassKind.clkDelegate;
                    break;

                case TypeKind.Enum:
                    limNode.ClassKind = Types.ClassKind.clkEnum;
                    break;

                case TypeKind.Interface:
                    limNode.ClassKind = Types.ClassKind.clkInterface;
                    break;

                case TypeKind.Struct:
                    limNode.ClassKind = Types.ClassKind.clkStruct;
                    break;

                default:
                    break;
            }

            limNode.IsAbstract = roslynNode.IsAbstract;

            //isSubClass
            if (roslynNode.BaseType != null)
            {
                var original = symbolConverter.GetDefinition(roslynNode.BaseType, out _);
                if (original != null && original.Kind == roslynNode.Kind)
                {
                    fileContext.ClassStack.Peek().IsSubclass.Add(new KeyValuePair<uint, bool>(symbolConverter.GetLimType(original).Id, false));
                }
                else if (roslynNode.BaseType.IsInMetadata())
                {
                    Base node = symbolConverter.GetLimType(roslynNode.BaseType);
                    solutionContext.LimFactory.setFiltered(node.Id);
                    fileContext.ClassStack.Peek().IsSubclass.Add(new KeyValuePair<uint, bool>(node.Id, true));
                }
            }
            foreach (var @interface in roslynNode.AllInterfaces)
            {
                SyntaxNode m_node;
                if (@interface.TypeKind != TypeKind.Error)
                {
                    var original = symbolConverter.GetDefinition(@interface, out m_node);
                    if (original != null && original.Kind == @interface.Kind)
                    {
                        fileContext.ClassStack.Peek().IsSubclass.Add(new KeyValuePair<uint, bool>(symbolConverter.GetLimType(original).Id, false));
                    }
                    else if (@interface.IsInMetadata())
                    {
                        Base node = symbolConverter.GetLimType(@interface);
                        solutionContext.LimFactory.setFiltered(node.Id);
                        fileContext.ClassStack.Peek().IsSubclass.Add(new KeyValuePair<uint, bool>(node.Id, false));
                    }
                }
            }

        }

        /// <summary>
        /// Fill ClassGeneric propeties
        /// </summary>
        /// <param name="limNode"></param>
        /// <param name="roslynNode"></param>
        /// <param name="setHasMember"></param>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private void fillData(ClassGeneric limNode, INamedTypeSymbol roslynNode, bool setHasMember)
        {
            fillData(limNode as Class, roslynNode, setHasMember);

            #region hasGenericParameter

            foreach (var argument in roslynNode.TypeArguments)
            {
                GenericParameter genericParam = symbolConverter.ConvertToLimNode(argument) as GenericParameter;
                FillData(genericParam, argument, setHasMember);
            }

            #endregion hasGenericParameter
        }

        /// <summary>
        /// Fill Method propeties
        /// </summary>
        /// <param name="limNode"></param>
        /// <param name="roslynNode"></param>
        /// <param name="setHasMember"></param>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private void fillData(Method limNode, IMethodSymbol roslynNode, bool setHasMember)
        {
            fileContext.MethodStack.Push(new MethodInfo(limNode.Id));

            fillScopeData(limNode, roslynNode, setHasMember);

            limNode.IsAbstract = roslynNode.IsAbstract;

            if (roslynNode.ContainingType != null && roslynNode.ContainingType.TypeKind == TypeKind.Interface)
            {
                limNode.Accessibility = Types.AccessibilityKind.ackPublic;
                limNode.IsAbstract = true;
            }

            #region MethodKind
            Types.MethodKind limKind = Types.MethodKind.mekNormal;
            switch (roslynNode.MethodKind)
            {
                case MethodKind.Constructor:
                    limKind = Types.MethodKind.mekConstructor;
                    break;

                case MethodKind.Conversion:
                    limKind = Types.MethodKind.mekOperator;
                    break;

                case MethodKind.Destructor:
                    limKind = Types.MethodKind.mekDestructor;
                    break;

                case MethodKind.UserDefinedOperator:
                    limKind = Types.MethodKind.mekOperator;
                    break;

                default:
                    break;
            }

            if (roslynNode.Name.Length >= 3)
            {
                string firstThree = roslynNode.Name.Substring(0, 3);
                if (firstThree == "get") limKind = Types.MethodKind.mekGet;
                else if (firstThree == "set") limKind = Types.MethodKind.mekSet;
                else if (firstThree == "add") limKind = Types.MethodKind.mekAdd;
                if (roslynNode.Name.Length >= "remove".Length)
                {
                    firstThree = roslynNode.Name.Substring(0, "remove".Length);
                    if (firstThree == "remove") limKind = Types.MethodKind.mekRemove;
                }
            }

            limNode.MethodKind = limKind;

            #endregion MethodKind

            limNode.IsVirtual = roslynNode.IsVirtual;

            #region returns
            var returnType = roslynNode.ReturnType;
            if (returnType != null)
            {
                SyntaxNode _m;
                if (!returnType.IsInMetadata())
                {
                    var originalDef = symbolConverter.GetDefinition(returnType, out _m);
                    if (originalDef != null && originalDef.Kind == returnType.Kind)
                        Commons.Common.Safe_Edge(limNode, "Returns", symbolConverter.GetLimType(originalDef).Id);
                }
                else
                {
                    Type node = symbolConverter.GetLimType(returnType);
                    solutionContext.LimFactory.setFiltered(node.Id);
                    Commons.Common.Safe_Edge(limNode, "Returns", node.Id);
                }
                limNode.MangledName += returnType.ToString();
                limNode.DemangledName = limNode.MangledName;
            }
            #endregion


            #region hasParamter
            foreach (var roslynParameter in roslynNode.Parameters)
            {
                Base limParameter = symbolConverter.ConvertToLimNode(roslynParameter);
                if (limParameter == null) return;

                FillData(limParameter, roslynParameter, setHasMember);
            }
            #endregion

            //canThrow
            //already handling in visitor
        }

        /// <summary>
        /// Fill MethodGeneric properties
        /// </summary>
        /// <param name="limNode"></param>
        /// <param name="roslynNode"></param>
        /// <param name="setHasMember"></param>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private void fillData(MethodGeneric limNode, IMethodSymbol roslynNode, bool setHasMember)
        {
            #region hasGenericParameter

            foreach (var argument in roslynNode.TypeArguments)
            {
                Base genericParameter = symbolConverter.ConvertToLimNode(argument);
                if (genericParameter == null) return;
                FillData(genericParameter, argument, setHasMember);
            }

            #endregion hasGenericParameter

            fillData(limNode as Method, roslynNode, setHasMember);
        }

        /// <summary>
        /// Fill Attribute node properties
        /// </summary>
        /// <param name="limNode"></param>
        /// <param name="roslynNode">An IFieldSymbol or an IEventSymbol</param>
        /// <param name="setHasMember"></param>
        /// <exception cref="ArgumentException">Thrown if <paramref name="roslynNode"/> is not an IFieldSymbol or an IEventSymbol</exception>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private void fillData(Attribute limNode, ISymbol roslynNode, bool setHasMember)
        {
            ITypeSymbol roslynType;
            switch (roslynNode)
            {
                case IFieldSymbol symbol:
                    roslynType = symbol.Type;
                    break;
                case IEventSymbol symbol:
                    roslynType = symbol.Type;
                    break;
                default:
                    throw new ArgumentException("Parameter should be a Field or an Event", nameof(roslynNode));
            }

            fillMemberData(limNode, roslynNode, setHasMember);

            if (fileContext.ClassStack.Count > 0)
            {
                Class parnetClass = (Class)solutionContext.LimFactory.getRef(fileContext.ClassStack.Peek().Id);
                if (parnetClass.ClassKind == Types.ClassKind.clkInterface)
                {
                    limNode.Accessibility = Types.AccessibilityKind.ackPublic;
                }
            }

            if (roslynType != null)
            {
                if (roslynType is ITypeParameterSymbol)
                {
                    GenericParameter limReturnType = (GenericParameter)symbolConverter.ConvertToLimNode(roslynType);
                    if (limReturnType == null) return;

                    fillData(limReturnType, roslynType as ITypeParameterSymbol, setHasMember);
                }
                else
                {
                    SyntaxNode syntaxNode = null;
                    var originalType = symbolConverter.GetDefinition(roslynType, out syntaxNode);
                    Type limType = null;
                    if (originalType != null && originalType.Kind == roslynType.Kind)
                    {
                        if (((INamedTypeSymbol)originalType).IsGenericType)
                            limType = symbolConverter.GetLimType(roslynType, originalType);
                        else
                            limType = symbolConverter.GetLimType(originalType);

                    }
                    else if (roslynType.IsInMetadata())
                    {
                        limType = symbolConverter.GetLimType(roslynType);
                        if (roslynType.TypeKind != TypeKind.Array)
                            solutionContext.LimFactory.setFiltered(limType.Id);
                    }
                    if (limNode.HasTypeIsEmpty && limType != null)
                        limNode.addHasType(limType);
                }
            }
            else
            {
                limNode.addHasType(CreateUnknownType());
            }
            limNode.MangledName += ' ' + roslynType.ToString();
            limNode.DemangledName = limNode.MangledName;
        }

        /// <summary>
        /// Fill GenericParameter properties
        /// </summary>
        /// <param name="limNode"></param>
        /// <param name="roslynNode"></param>
        /// <param name="setHasMember"></param>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private void fillData(GenericParameter limNode, ITypeParameterSymbol roslynNode, bool setHasMember)
        {
            limNode.GenericParameterKind = Types.GenericParameterKind.gpkType;

            foreach (var constraint in roslynNode.ConstraintTypes)
            {
                SyntaxNode _m;
                Type limTpye;
                if (!constraint.IsInMetadata())
                {
                    var original = symbolConverter.GetDefinition(constraint, out _m);
                    if (original != null && original.Kind == constraint.Kind)
                        limTpye = symbolConverter.GetLimType(original);
                    else continue;
                }
                else
                {
                    limTpye = symbolConverter.GetLimType(constraint);
                    solutionContext.LimFactory.setFiltered(limTpye.Id);
                }

                Commons.Common.Safe_Edge(limNode, "HasParameterConstraint", limTpye.Id);
            }


            Base limParent = symbolConverter.ConvertToLimNode(symbolConverter.Parent(roslynNode));
            if (limParent != null)
            {
                if (symbolConverter.Parent(roslynNode).IsInMetadata())
                    solutionContext.LimFactory.setFiltered(limParent.Id);
                if (Lim.Asg.Common.getIsMethodGeneric(limParent))
                {
                    MethodGeneric methodGeneric = (MethodGeneric)limParent;
                    Commons.Common.Safe_Edge(methodGeneric, "HasGenericParameter", limNode.Id);
                }
                else if (Lim.Asg.Common.getIsClassGeneric(limParent))
                {
                    ClassGeneric clasGeneric = (ClassGeneric)limParent;
                    Commons.Common.Safe_Edge(clasGeneric, "HasGenericParameter", limNode.Id);
                }
            }
        }

        /// <summary>
        /// Fill Parameter node properties 
        /// </summary>
        /// <param name="limNode"></param>
        /// <param name="roslynNode"></param>
        /// <param name="setHasMember"></param>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private void fillData(Parameter limNode, IParameterSymbol roslynNode, bool setHasMember)
        {
            switch (roslynNode.RefKind)
            {
                case RefKind.None:
                    limNode.ParamKind = Types.ParameterKind.pmkIn;
                    break;
                case RefKind.Ref:
                    limNode.ParamKind = Types.ParameterKind.pmkInOut;
                    break;
                case RefKind.Out:
                    limNode.ParamKind = Types.ParameterKind.pmkOut;
                    break;
            }
            if (roslynNode.Type != null)
            {
                SyntaxNode _m;
                Type type = null;
                if (!roslynNode.Type.IsInMetadata())
                {
                    var original = symbolConverter.GetDefinition(roslynNode.Type, out _m);
                    if (original != null && original.Kind == roslynNode.Type.Kind)
                    {
                        var namedType = roslynNode.Type as INamedTypeSymbol;
                        if (namedType != null && namedType.IsGenericType)
                            type = symbolConverter.GetLimType(roslynNode.Type, original);
                        else
                            type = symbolConverter.GetLimType(original);
                    }
                }
                else
                {
                    type = symbolConverter.GetLimType(roslynNode.Type);
                    if (roslynNode.Type.TypeKind != TypeKind.Array)
                        solutionContext.LimFactory.setFiltered(type.Id);
                }
                if (type != null) limNode.setHasType(type);
            }
            else
            {
                limNode.setHasType(CreateUnknownType());
            }

            if (fileContext.MethodStack.Count > 0)
            {
                //hasParameter
                Method parent = (Method)solutionContext.LimFactory.getRef(
                    fileContext.MethodStack.Peek().Id
                );
                Commons.Common.Safe_Edge(parent, "HasParameter", limNode.Id);
            }
        }

        /// <summary>
        /// Fill Scope node properties
        /// </summary>
        /// <param name="limNode"></param>
        /// <param name="roslynNode"></param>
        /// <param name="setHasMember"></param>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private void fillScopeData(Scope limNode, ISymbol roslynNode, bool setHasMember)
        {
            fillMemberData(limNode, roslynNode, setHasMember);

            limNode.IsAnonymous = roslynNode.IsAnonymousMethod() || roslynNode.IsAnonymousType();
        }

        /// <summary>
        /// Fill member properties
        /// </summary>
        /// <param name="limNode">LIM node reference</param>
        /// <param name="roslynNode">C# syntax node reference</param>
        /// <param name="setHasMember"></param>
        /// <param name="aggregateLLOC">Default is true and </param>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private void fillMemberData(Member limNode, ISymbol roslynNode, bool setHasMember, bool aggregateLLOC = true)
        {
            limNode.Language = Types.LanguageKind.lnkCsharp;

            if (roslynNode.IsInMetadata() || fileContext.SoftFiltered)
            {
                solutionContext.LimFactory.setFiltered(limNode.Id);
            }

            #region Accessibility
            switch (roslynNode.DeclaredAccessibility)
            {
                case Accessibility.Private:
                    limNode.Accessibility = Types.AccessibilityKind.ackPrivate;
                    break;

                case Accessibility.ProtectedAndInternal:
                    limNode.Accessibility = Types.AccessibilityKind.ackInternal;
                    break;

                case Accessibility.Protected:
                    limNode.Accessibility = Types.AccessibilityKind.ackProtected;
                    break;

                case Accessibility.Internal:
                    limNode.Accessibility = Types.AccessibilityKind.ackInternal;
                    break;

                case Accessibility.ProtectedOrInternal:
                    limNode.Accessibility = Types.AccessibilityKind.ackProtectedInternal;
                    break;

                case Accessibility.Public:
                    limNode.Accessibility = Types.AccessibilityKind.ackPublic;
                    break;

                default:
                    break;
            }
            #endregion

            limNode.IsStatic = roslynNode.IsStatic;
            limNode.IsCompilerGenerated = false;


            limNode.MangledName = roslynNode.GetFullMetadataName();
            limNode.DemangledName = limNode.MangledName;

            if (aggregateLLOC && !roslynNode.IsInMetadata())
            {
                INamespaceSymbol ns = null;
                if (roslynNode.Kind == SymbolKind.Namespace) ns = (INamespaceSymbol)roslynNode;

                if (ns == null || (ns != null && !ns.IsGlobalNamespace))
                {
                    foreach (var location in roslynNode.DeclaringSyntaxReferences)
                    {
                        edgeBuilder.AddIsContainedInEdge(limNode, location.GetSyntax());
                    }
                }
            }

            // TODO maybe not if in metadata
            Commons.Common.Safe_Edge(limNode, "BelongsTo", projectContext.Component.Id);

            if (setHasMember)
            {
                ISymbol roslynParent = roslynNode;
                Base limParent = null;
                do
                {
                    roslynParent = roslynParent != null ? symbolConverter.Parent(roslynParent) : null;

                    if (roslynParent != null)
                    {
                        limParent = symbolConverter.ConvertToLimNode(roslynParent);

                        if (roslynParent.Kind == SymbolKind.Namespace)
                            fillMemberData((Member)limParent, roslynParent, true, false);

                        if (roslynParent.IsInMetadata())
                        {
                            ((Member)limParent).IsCompilerGenerated = true;
                            ((Scope)limParent).MangledName = ((Scope)limParent).DemangledName = roslynParent.ToString();
                            solutionContext.LimFactory.setFiltered(limParent.Id);
                        }
                    }
                    else
                        limParent = null;

                } while (roslynParent != null && !Lim.Asg.Common.getIsScope(limParent));
                if (limParent != null)
                {
                    Scope scope = (Scope)limParent;
                    Commons.Common.Safe_Edge(scope, "HasMember", limNode.Id);
                }
            }

            if (aggregateLLOC && !roslynNode.IsInMetadata() && roslynNode.DeclaringSyntaxReferences.Length > 0)
            {
                foreach (var syntaxNode in roslynNode.DeclaringSyntaxReferences)
                {
                    fileContext.LlocCalculator.CollectLineInfos(syntaxNode.GetSyntax());
                }
            }
        }

        /// <summary>
        /// Create Unknown Type in the LIM
        /// </summary>
        private Type CreateUnknownType()
        {
            solutionContext.LimFactory.beginType();
            solutionContext.LimFactory.addTypeFormer(
                solutionContext.LimFactory.createTypeFormerType(
                    solutionContext.LimFactory.createSimpleType(Types.SimpleTypeKind.stkUnknown).Id
                ).Id
            );
            return solutionContext.LimFactory.endType();
        }
    }
}
