/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2018 Department of Software Engineering - University of Szeged
 *
 *  Licensed under Version 1.2 of the EUPL (the "Licence");
 *
 *  You may not use this work except in compliance with the Licence.
 *
 *  You may obtain a copy of the Licence in the LICENSE file or at:
 *
 *  https://joinup.ec.europa.eu/software/page/eupl
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the Licence is distributed on an "AS IS" basis,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the Licence for the specific language governing permissions and
 *  limitations under the Licence.
 */

using System.Linq;

using Columbus.Lim.Asg;
using Columbus.Lim.Asg.Nodes.Base;
using Columbus.Lim.Asg.Nodes.Logical;

using Columbus.CSAN.Commons;

using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;

namespace Columbus.CSAN.Extensions
{
    static class SymbolExtension
    {
        /// <summary>
        /// Get definiton of symbol
        /// </summary>
        /// <param name="symbol"></param>
        /// <param name="node">Syntax node</param>
        /// <param name="needParent"></param>
        /// <returns></returns>
        public static ISymbol GetDefinition(this ISymbol symbol, out SyntaxNode node, bool needParent = false)
        {
            if (symbol.Locations.Length > 0)
            {
                Location item = symbol.Locations[0];
                if (item.IsInMetadata)
                {
                    node = null;
                    return null;
                }

                MainDeclaration.Instance.RoslynWatch.Start();
                SemanticModel model = MainDeclaration.Instance.Solution.GetDocument(item.SourceTree).GetSemanticModelAsync().Result;
                var root = model.SyntaxTree.GetRoot();
                var calledNode = root.FindNode(item.SourceSpan);
                if (calledNode != null)
                {
                    node = calledNode;
                    var newSymbol = model.GetDeclaredSymbol((needParent) ? calledNode.Parent : calledNode);
                    MainDeclaration.Instance.RoslynWatch.Stop();
                    return newSymbol;
                }
                MainDeclaration.Instance.RoslynWatch.Stop();
            }
            node = null;
            return null;
        }

        /// <summary>
        /// Create LIM node from Symbol
        /// </summary>
        /// <param name="symbol">SyntaxNode's symbol</param>
        /// <returns>LIM node</returns>
        public static Base Create(this ISymbol symbol)
        {
            Named newLimNode = (Named)MainDeclaration.Instance.LimFactory.createNode(symbol.GetLimKind());
            newLimNode.Name = symbol.Name;

            if (Lim.Asg.Common.getIsMember(newLimNode))
                ((Member)newLimNode).Language = Types.LanguageKind.lnkCsharp;


            MainDeclaration.Instance.LocalMap.Add(symbol, newLimNode.Id);

            return newLimNode;
        }

        /// <summary>
        /// Get LIM kind from Symbol kind
        /// </summary>
        /// <param name="typeInfo">SyntaxNode's symbol</param>
        /// <returns>LIM node kind</returns>
        public static Types.NodeKind GetLimKind(this ISymbol typeInfo)
        {
            switch (typeInfo.Kind)
            {
                case SymbolKind.Method:
                    var method = typeInfo as IMethodSymbol;
                    if (method.IsGenericMethod)
                    {
                        return Types.NodeKind.ndkMethodGeneric;
                    }
                    return Types.NodeKind.ndkMethod;
                case SymbolKind.Namespace: return Types.NodeKind.ndkPackage;
                case SymbolKind.Parameter: return Types.NodeKind.ndkParameter;
                case SymbolKind.Field: return Types.NodeKind.ndkAttribute;
                case SymbolKind.TypeParameter: return Types.NodeKind.ndkGenericParameter;
                case SymbolKind.ErrorType:
                case SymbolKind.NamedType:
                    var namedTypeSymbol = typeInfo as INamedTypeSymbol;
                    if (namedTypeSymbol.IsGenericType)
                    {
                        return Types.NodeKind.ndkClassGeneric;
                    }
                    return Types.NodeKind.ndkClass;
            }
            return default(Types.NodeKind);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="node"></param>
        /// <returns></returns>
        public static bool IsInMetadata(this ISymbol node)
        {
            return node.DeclaringSyntaxReferences.Length == 0;
        }

        /// <summary>
        /// Create LIM type from symbol if it is not exists
        /// </summary>
        /// <param name="symbol"></param>
        /// <param name="refs"></param>
        /// <returns>LIM Type node</returns>
        public static Lim.Asg.Nodes.Type.Type GetLimType(this ISymbol symbol, ISymbol refs = null)
        {
            Lim.Asg.Nodes.Type.Type result;
            if (MainDeclaration.Instance.TypeMap.TryGetValue(symbol, out result))
                return result;

            MainDeclaration.Instance.LimFactory.beginType();
            Commons.Common.AddLimTypeFormers(symbol, refs);
            result = MainDeclaration.Instance.LimFactory.endType();

            MainDeclaration.Instance.TypeMap.Add(symbol, result);

            return result;
        }

        /// <summary>
        /// Create ClassGenericInstance and connect to the Class, through the Instance edge.
        /// Furthermore, added GenericParameter to the ClassGenericInstance.
        /// </summary>
        /// <param name="symbol">Instanced class</param>
        /// <param name="refersTo">Instanced class definiton</param>
        /// <returns>ClassGenericInstnace from the LIM</returns>
        public static ClassGenericInstance GetCGI(this ISymbol symbol, INamedTypeSymbol refersTo)
        {
            string uName = symbol.ToString();
            ClassGenericInstance cgi;
            if (MainDeclaration.Instance.CgiMap.TryGetValue(uName, out cgi))
                return cgi;

            cgi = MainDeclaration.Instance.LimFactory.createClassGenericInstanceNode();
            cgi.IsRealInstance = true;
            cgi.Name = symbol.ToDisplayString(SymbolDisplayFormat.MinimallyQualifiedFormat);
            cgi.MangledName = uName;
            cgi.DemangledName = uName;
            cgi.Language = Types.LanguageKind.lnkCsharp;

            INamedTypeSymbol roslynNode = symbol as INamedTypeSymbol;
            bool isInMeta = false;
            if (refersTo == null) { refersTo = (INamedTypeSymbol)symbol.OriginalDefinition; isInMeta = true; }
            if (refersTo != null)
            {
                Base owner = refersTo.ConvertToLimNode();
                if (isInMeta)
                    Commons.Common.MetaDataNameFiller(symbol, (Member)owner);

                if (Lim.Asg.Common.getIsClass(owner))
                {
                    Class ownerClass = owner as Class;
                    Commons.Common.Safe_Edge(ownerClass, "Instance", cgi.Id);

                    int i = 0;
                    foreach (var argument in roslynNode.TypeArguments)
                    {
                        ITypeSymbol arg = null;
                        if (!argument.IsInMetadata() && argument.TypeKind != TypeKind.TypeParameter)
                        {
                            SyntaxNode tmp;
                            arg = (INamedTypeSymbol)argument.GetDefinition(out tmp);
                        }
                        Lim.Asg.Nodes.Type.Type param = (arg != null) ? arg.GetLimType() : argument.GetLimType();
                        MainDeclaration.Instance.UsesStack.Peek().Remove(param.Id);

                        Types.TypeArgumentConstraintKind tack = Types.TypeArgumentConstraintKind.tackUpperBounded;
                        if (roslynNode.TypeParameters[i].ConstraintTypes.Length > 0)
                        {
                            tack = Types.TypeArgumentConstraintKind.tackUnbounded;
                        }

                        bool found = false;
                        ListIteratorAssocTypeArgumentConstraintKind<Lim.Asg.Nodes.Type.Type> cIt = cgi.HasArgumentsListIteratorAssocBegin;
                        while (cIt.getValue() != null)
                        {
                            Lim.Asg.Nodes.Type.Type value = cIt.getValue();
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
                }
            }

            MainDeclaration.Instance.CgiMap.Add(uName, cgi);

            return cgi;
        }

        /// <summary>
        /// Create MethodGenericInstance and connect to the Method, through the Instance edge.
        /// Furthermore, added GenericParameter to the MethodGenericInstance.
        /// </summary>
        /// <param name="symbol">Called method</param>
        /// <param name="refersTo">Called method definition</param>
        /// <returns>MethodGenericInstance node from the LIM</returns>
        public static MethodGenericInstance GetMGI(this ISymbol symbol, IMethodSymbol refersTo)
        {
            string uName = symbol.ToString();
            MethodGenericInstance mgi;
            if (MainDeclaration.Instance.MgiMap.TryGetValue(uName, out mgi))
                return mgi;

            mgi = MainDeclaration.Instance.LimFactory.createMethodGenericInstanceNode();
            mgi.IsRealInstance = true;
            mgi.Name = symbol.ToDisplayString(SymbolDisplayFormat.MinimallyQualifiedFormat);
            mgi.MangledName = uName;
            mgi.DemangledName = uName;
            mgi.Language = Types.LanguageKind.lnkCsharp;

            IMethodSymbol roslynNode = symbol as IMethodSymbol;

            Base owner = refersTo != null ? refersTo.ConvertToLimNode() : symbol.OriginalDefinition.ConvertToLimNode();
            if (owner == null) return null;
            if (Lim.Asg.Common.getIsMethod(owner))
            {
                Method ownerMethod = owner as Method;
                Commons.Common.Safe_Edge(ownerMethod, "Instance", mgi.Id);

                if (roslynNode.Arity > 0)
                {
                    int i = 0;
                    foreach (var argument in roslynNode.TypeArguments)
                    {
                        ITypeSymbol arg = null;
                        if (!argument.IsInMetadata() && argument.TypeKind != TypeKind.TypeParameter)
                        {
                            SyntaxNode _tmp = null;
                            arg = (INamedTypeSymbol)argument.GetDefinition(out _tmp);
                        }
                        Columbus.Lim.Asg.Nodes.Type.Type param = (arg != null) ? arg.GetLimType() : argument.GetLimType();
                        MainDeclaration.Instance.UsesStack.Peek().Remove(param.Id);

                        Types.TypeArgumentConstraintKind tack = Types.TypeArgumentConstraintKind.tackUpperBounded;
                        if (roslynNode.TypeParameters[i].ConstraintTypes.Any())
                        {
                            tack = Types.TypeArgumentConstraintKind.tackUnbounded;
                        }

                        bool found = false;
                        ListIteratorAssocTypeArgumentConstraintKind<Columbus.Lim.Asg.Nodes.Type.Type> cIt = mgi.HasArgumentsListIteratorAssocBegin;
                        while (cIt.getValue() != null)
                        {
                            Lim.Asg.Nodes.Type.Type value = cIt.getValue();
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

            MainDeclaration.Instance.MgiMap.Add(uName, mgi);

            return mgi;
        }

        /// <summary>
        /// ASG node to LIM node
        /// if already not exists the LIM node then we'll create one if it's LIM compatible
        /// </summary>
        /// <param name="symbol">ASG node</param>
        /// <returns>LIM node</returns>
        public static Base ConvertToLimNode(this ISymbol symbol)
        {
            uint id;

            if (MainDeclaration.Instance.LocalMap.TryGetValue(symbol, out id))
                return MainDeclaration.Instance.LimFactory.getRef(id);

            if (symbol.IsLimCompatibile())
            {
                return symbol.Create();
            }

            return null;
        }

        /// <summary>
        /// Symbol is anonymous type
        /// </summary>
        /// <param name="symbol"></param>
        /// <returns>Return true if symbol is anonymous type</returns>
        public static bool IsAnonymousType(this ISymbol symbol)
        {
            return symbol is INamedTypeSymbol && ((INamedTypeSymbol)symbol).IsAnonymousType;
        }

        /// <summary>
        /// Symbol is anonymous method
        /// </summary>
        /// <param name="symbol"></param>
        /// <returns>Return true if symbol is iMethodSymbol and symbol's MethodKind is AnonymousFunction</returns>
        public static bool IsAnonymousMethod(this ISymbol symbol)
        {
            return symbol is IMethodSymbol && ((IMethodSymbol)symbol).MethodKind == MethodKind.AnonymousFunction;
        }

        /// <summary>
        /// Symbol is compatible with LIM
        /// </summary>
        /// <param name="symbol"></param>
        /// <returns>Return true if symbol compatible with LIM</returns>
        public static bool IsLimCompatibile(this ISymbol symbol)
        {
            return
                symbol is INamespaceSymbol
                || symbol is INamedTypeSymbol
                || symbol is IMethodSymbol
                || symbol is IParameterSymbol
                || symbol is ITypeParameterSymbol
                || symbol is IFieldSymbol;
        }

        /// <summary>
        /// Get symbol "parent" if it is LIM compatible
        /// </summary>
        /// <param name="symbol"></param>
        /// <returns></returns>
        public static ISymbol Parent(this ISymbol symbol)
        {
            while (symbol != null && symbol.ContainingSymbol != null)
            {
                symbol = symbol.ContainingSymbol;
                if (symbol != null && symbol.Kind != SymbolKind.NetModule && symbol.Kind != SymbolKind.Assembly && symbol.Kind != SymbolKind.Namespace)
                {
                    SyntaxNode _m;
                    var tmp = symbol.GetDefinition(out _m);
                    if (tmp != null) symbol = tmp;
                }
                if (symbol.IsLimCompatibile())
                    return symbol;
            }

            return null;
        }

    }
}