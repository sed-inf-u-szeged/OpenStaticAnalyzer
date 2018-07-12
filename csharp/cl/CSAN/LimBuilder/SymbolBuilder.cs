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

using System.Collections.Generic;
using System.Linq;

using Columbus.Lim.Asg;
using Columbus.Lim.Asg.Nodes.Base;
using Columbus.Lim.Asg.Nodes.Logical;

using Columbus.CSAN.Commons;
using Columbus.CSAN.Utils.Info;
using Columbus.CSAN.Extensions;
using Columbus.CSAN.Metrics.Size;
using Microsoft.CodeAnalysis;
using System.Runtime.CompilerServices;


namespace Columbus.CSAN.LimBuilder
{
    class SymbolBuilder
    {
        private static SymbolBuilder inst;

        /// <summary>
        /// Create instance from this class
        /// </summary>
        public static SymbolBuilder Instance
        {
            get
            {
                if (inst == null)
                {
                    inst = new SymbolBuilder();
                }
                return inst;
            }
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
        public static L BuildDispatch<L, R>(R roslynNode, bool setHasMember = true)
            where L : Base
            where R : ISymbol
        {

            L LimNode = roslynNode.ConvertToLimNode() as L;
            if (LimNode == null) return default(L);

            if (Lim.Asg.Common.getIsMember(LimNode))
                MainDeclaration.Instance.UsesStack.Push(new HashSet<uint>());

            Instance.FillData(LimNode, roslynNode, setHasMember);

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
        public void FillData<L, R>(L limNode, R roslynNode, bool setHasMember)
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
                    fillData(limNode as Attribute, roslynNode as IFieldSymbol, setHasMember);
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
            MainDeclaration.Instance.NamespaceStack.Push(limNode.Id);

            fillScopeData(limNode, roslynNode, setHasMember);

            foreach (var item in roslynNode.DeclaringSyntaxReferences)
            {
                string location = "";
                SyntaxNode syntaxNode = item.GetSyntax();
                if (!roslynNode.IsInMetadata())
                    location = Commons.Common.ProcessPath(syntaxNode.SyntaxTree.FilePath);
                uint key = 0;
                if (!string.IsNullOrEmpty(location))
                    key = MainDeclaration.Instance.LimFactory.StringTable.set(location);

                if (key == 0) return;

                if (!roslynNode.IsInMetadata() && !roslynNode.IsGlobalNamespace)
                {
                    Commons.Common.AddIsContainedInEdge(limNode, syntaxNode);
                    LOC.AddLocToComponent(
                        MainDeclaration.Instance.Component.Id,
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
            MainDeclaration.Instance.ClassStack.Push(new ClassInfo(limNode.Id));

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
                SyntaxNode m_node;
                if (roslynNode.BaseType.TypeKind != TypeKind.Error)
                {
                    var original = roslynNode.BaseType.GetDefinition(out m_node);
                    if (original != null && original.Kind == roslynNode.Kind)
                    {
                        MainDeclaration.Instance.ClassStack.Peek().IsSubclass.Add(new KeyValuePair<uint, bool>(original.GetLimType().Id, false));
                    }
                    else if (roslynNode.BaseType.IsInMetadata())
                    {
                        Base node = roslynNode.BaseType.GetLimType();
                        MainDeclaration.Instance.LimFactory.setFiltered(node.Id);
                        MainDeclaration.Instance.ClassStack.Peek().IsSubclass.Add(new KeyValuePair<uint, bool>(node.Id, true));
                    }
                }
            }
            foreach (var @interface in roslynNode.AllInterfaces)
            {
                SyntaxNode m_node;
                if (@interface.TypeKind != TypeKind.Error)
                {
                    var original = @interface.GetDefinition(out m_node);
                    if (original != null && original.Kind == @interface.Kind)
                    {
                        MainDeclaration.Instance.ClassStack.Peek().IsSubclass.Add(new KeyValuePair<uint, bool>(original.GetLimType().Id, false));
                    }
                    else if (@interface.IsInMetadata())
                    {
                        Base node = @interface.GetLimType();
                        MainDeclaration.Instance.LimFactory.setFiltered(node.Id);
                        MainDeclaration.Instance.ClassStack.Peek().IsSubclass.Add(new KeyValuePair<uint, bool>(node.Id, false));
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
                GenericParameter genericParam = argument.ConvertToLimNode() as GenericParameter;
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
            MainDeclaration.Instance.MethodStack.Push(new MethodInfo(limNode.Id));

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
                    var originalDef = returnType.GetDefinition(out _m);
                    if (originalDef != null && originalDef.Kind == returnType.Kind)
                        Commons.Common.Safe_Edge(limNode, "Returns", originalDef.GetLimType().Id);
                }
                else
                {
                    Lim.Asg.Nodes.Type.Type node = returnType.GetLimType();
                    MainDeclaration.Instance.LimFactory.setFiltered(node.Id);
                    Commons.Common.Safe_Edge(limNode, "Returns", node.Id);
                }
                limNode.MangledName += returnType.ToString();
                limNode.DemangledName = limNode.MangledName;
            }
            #endregion


            #region hasParamter
            foreach (var roslynParameter in roslynNode.Parameters)
            {
                Base limParameter = roslynParameter.ConvertToLimNode();
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
                Base genericParameter = argument.ConvertToLimNode();
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
        /// <param name="roslynNode"></param>
        /// <param name="setHasMember"></param>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private void fillData(Attribute limNode, IFieldSymbol roslynNode, bool setHasMember)
        {

            fillMemberData(limNode, roslynNode, setHasMember);

            if (MainDeclaration.Instance.ClassStack.Count > 0)
            {
                Class parnetClass = (Class)MainDeclaration.Instance.LimFactory.getRef(MainDeclaration.Instance.ClassStack.Peek().Id);
                if (parnetClass.ClassKind == Types.ClassKind.clkInterface)
                {
                    limNode.Accessibility = Types.AccessibilityKind.ackPublic;
                }
            }

            var roslynType = roslynNode.Type;
            if (roslynType != null)
            {
                if (roslynType is ITypeParameterSymbol)
                {
                    GenericParameter limReturnType = (GenericParameter)roslynType.ConvertToLimNode();
                    if (limReturnType == null) return;

                    fillData(limReturnType, roslynType as ITypeParameterSymbol, setHasMember);
                }
                else
                {
                    SyntaxNode syntaxNode = null;
                    var originalType = roslynType.GetDefinition(out syntaxNode);
                    Lim.Asg.Nodes.Type.Type limType = null;
                    if (originalType != null && originalType.Kind == roslynType.Kind)
                    {
                        if (((INamedTypeSymbol)originalType).IsGenericType)
                            limType = roslynType.GetLimType(originalType);
                        else
                            limType = originalType.GetLimType();

                    }
                    else if (roslynType.IsInMetadata())
                    {
                        limType = roslynType.GetLimType();
                        if (roslynType.TypeKind != TypeKind.Array)
                            MainDeclaration.Instance.LimFactory.setFiltered(limType.Id);
                    }
                    if (limNode.HasTypeIsEmpty) limNode.addHasType(limType);
                }
            }
            else
            {
                limNode.addHasType(Commons.Common.UnknownType);
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
                Lim.Asg.Nodes.Type.Type limTpye;
                if (!constraint.IsInMetadata())
                {
                    var original = constraint.GetDefinition(out _m);
                    if (original != null && original.Kind == constraint.Kind)
                        limTpye = original.GetLimType();
                    else continue;
                }
                else
                {
                    limTpye = constraint.GetLimType();
                    MainDeclaration.Instance.LimFactory.setFiltered(limTpye.Id);
                }

                Commons.Common.Safe_Edge(limNode, "HasParameterConstraint", limTpye.Id);
            }


            Base limParent = roslynNode.Parent().ConvertToLimNode();
            if (limParent != null)
            {
                if (roslynNode.Parent().IsInMetadata())
                    MainDeclaration.Instance.LimFactory.setFiltered(limParent.Id);
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
                Lim.Asg.Nodes.Type.Type type = null;
                if (!roslynNode.Type.IsInMetadata())
                {
                    var original = roslynNode.Type.GetDefinition(out _m);
                    if (original != null && original.Kind == roslynNode.Type.Kind)
                    {
                        var namedType = roslynNode.Type as INamedTypeSymbol;
                        if (namedType != null && namedType.IsGenericType)
                            type = roslynNode.Type.GetLimType(original);
                        else
                            type = original.GetLimType();
                    }
                }
                else
                {
                    type = roslynNode.Type.GetLimType();
                    if (roslynNode.Type.TypeKind != TypeKind.Array)
                        MainDeclaration.Instance.LimFactory.setFiltered(type.Id);
                }
                if (type != null) limNode.setHasType(type);
            }
            else
            {
                limNode.setHasType(Commons.Common.UnknownType);
            }

            if (MainDeclaration.Instance.MethodStack.Count > 0)
            {
                //hasParameter
                Method parent = (Method)MainDeclaration.Instance.LimFactory.getRef(
                    MainDeclaration.Instance.MethodStack.Peek().Id
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

            if (roslynNode.IsInMetadata())
            {
                MainDeclaration.Instance.LimFactory.setFiltered(limNode.Id);
            }

            if (MainDeclaration.Instance.SoftFilter != null)
            {
                if (MainDeclaration.Instance.CurrentFileIsSoftFiltered)
                {
                    MainDeclaration.Instance.LimFactory.setFiltered(limNode.Id);
                }
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


            limNode.MangledName = roslynNode.ToString();
            limNode.DemangledName = limNode.MangledName;

            if (aggregateLLOC && !roslynNode.IsInMetadata())
            {
                INamespaceSymbol ns = null;
                if (roslynNode.Kind == SymbolKind.Namespace) ns = (INamespaceSymbol)roslynNode;

                if (ns == null || (ns != null && !ns.IsGlobalNamespace))
                {
                    foreach (var location in roslynNode.DeclaringSyntaxReferences)
                    {
                        Commons.Common.AddIsContainedInEdge(limNode, location.GetSyntax());
                    }
                }
            }

            Commons.Common.Safe_Edge(limNode, "BelongsTo", MainDeclaration.Instance.Component.Id);

            if (setHasMember)
            {
                ISymbol roslynParent = roslynNode;
                Base limParent = null;
                do
                {
                    roslynParent = roslynParent != null ? roslynParent.Parent() : null;

                    if (roslynParent != null)
                    {
                        limParent = roslynParent.ConvertToLimNode();

                        if (roslynParent.Kind == SymbolKind.Namespace)
                            fillMemberData((Member)limParent, roslynParent, true, false);

                        if (roslynParent.IsInMetadata())
                        {
                            ((Member)limParent).IsCompilerGenerated = true;
                            ((Scope)limParent).MangledName = ((Scope)limParent).DemangledName = roslynParent.ToString();
                            MainDeclaration.Instance.LimFactory.setFiltered(limParent.Id);
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
                    LLOC.CollectLineInfos(syntaxNode.GetSyntax());
                }
            }
        }

        /// <summary>
        /// Fill collected Method datas
        /// </summary>
        /// <param name="method"></param>
        /// <param name="methodInfo"></param>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static void fillCollectedMethodData(Method method, MethodInfo methodInfo)
        {
            method.NestingLevel = (ushort)methodInfo.NL;
            method.NestingLevelElseIf = (ushort)methodInfo.NLE;
            method.NumberOfBranches = (ushort)methodInfo.NOB;
            method.NumberOfStatements = (ushort)methodInfo.NOS;

            foreach (KeyValuePair<uint, bool> call in methodInfo.Calls)
            {
                if (call.Value) MainDeclaration.Instance.LimFactory.setFiltered(call.Key);
                Commons.Common.Safe_Edge(method, "Calls", call.Key);
            }
            foreach (KeyValuePair<uint, bool> throws in methodInfo.Throws)
            {
                if (throws.Value) MainDeclaration.Instance.LimFactory.setFiltered(throws.Key);
                Commons.Common.Safe_Edge(method, "Throws", throws.Key);
            }
            foreach (KeyValuePair<uint, bool> canThrows in methodInfo.CanThrow)
            {
                if (canThrows.Value) MainDeclaration.Instance.LimFactory.setFiltered(canThrows.Key);
                Commons.Common.Safe_Edge(method, "CanThrow", canThrows.Key);
            }
            foreach (KeyValuePair<uint, bool> instantiates in methodInfo.Instantiates)
            {
                if (instantiates.Value) MainDeclaration.Instance.LimFactory.setFiltered(instantiates.Key);
                Commons.Common.Safe_Edge(method, "Instantiates", instantiates.Key);
            }
            foreach (KeyValuePair<uint, bool> accessAttribute in methodInfo.AccessAttribute)
            {
                if (accessAttribute.Value) MainDeclaration.Instance.LimFactory.setFiltered(accessAttribute.Key);
                Commons.Common.Safe_Edge(method, "AccessesAttribute", accessAttribute.Key);
            }

            if (!method.ReturnsIsEmpty)
            {
                Lim.Asg.Nodes.Type.Type returnType = method.ReturnsListIteratorBegin.getValue();
                if (returnType != null)
                {
                    MainDeclaration.Instance.UsesStack.Peek().Remove(returnType.Id);
                }
            }

            if (!method.HasParameterIsEmpty)
            {
                ListIterator<Lim.Asg.Nodes.Logical.Parameter> paramIt = method.HasParameterListIteratorBegin;
                while (paramIt.getValue() != null)
                {
                    MainDeclaration.Instance.UsesStack.Peek().Remove(paramIt.getValue().getHasType());
                    paramIt = paramIt.getNext();
                }
            }

            IEnumerable<uint> _throws = methodInfo.Throws.Select(t => t.Key);
            IEnumerable<uint> _canThrows = methodInfo.CanThrow.Select(t => t.Key);
            IEnumerable<uint> _instantiates = methodInfo.Instantiates.Select(t => t.Key);
            Commons.Common.Remove(ref _throws);
            Commons.Common.Remove(ref _canThrows);
            Commons.Common.Remove(ref _instantiates);

            Commons.Common.AddUses(method);
        }
    }
}