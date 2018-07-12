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

using System;
using System.Linq;
using System.Collections.Generic;

using Columbus.Lim.Asg;
using Columbus.Lim.Asg.Nodes.Base;
using Columbus.Lim.Asg.Nodes.Logical;
using Columbus.Lim.Asg.Nodes.Physical;

using Columbus.CSAN.Extensions;
using Columbus.CSAN.Utils.Info;
using Columbus.CSAN.Metrics.Complexity;
using Columbus.CSAN.Metrics.Size;

using Microsoft.CodeAnalysis;
using System.Threading.Tasks;
using System.Runtime.CompilerServices;
using System.Text.RegularExpressions;

namespace Columbus.CSAN.Commons
{
    static class Common
    {
        /// <summary>
        /// Processes ChangePathFrom and to arguments on the given path
        /// </summary>
        /// <param name="path"></param>
        /// <returns></returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static string ProcessPath(string path)
        {
            return string.IsNullOrEmpty(path) || string.IsNullOrEmpty(MainDeclaration.Instance.ChangePathFrom) ? path : Regex.Replace(path, MainDeclaration.Instance.ChangePathFrom, MainDeclaration.Instance.ChangePathTo, RegexOptions.IgnoreCase);
        }

        /// <summary>
        /// Calculating metrics to the Method
        /// </summary>
        /// <param name="node">C# syntax node</param>
        public static void SetMetrics(Microsoft.CodeAnalysis.CSharp.CSharpSyntaxNode node)
        {
            MethodInfo mi = MainDeclaration.Instance.MethodStack.Pop();
            FillFromMethodStack(FillMethodMetrics(node, mi));
        }

        /// <summary>
        /// Changing Scope node realization level to Declares
        /// </summary>
        /// <param name="limNode">Scope node from LIM</param>
        public static void ChangeRealizationLevel(Scope limNode)
        {
            var IsContainedIn = limNode.IsContainedInListIteratorAssocBegin;
            while (IsContainedIn.getValue() != null)
            {
                IsContainedIn.getAssocItem().RealizationLevel = Types.RealizationLevel.relDeclares;
                IsContainedIn = IsContainedIn.getNext();
            }
        }
        
        /// <summary>
        /// Calculate metrics for Method
        /// </summary>
        /// <param name="node"></param>
        /// <param name="mi"></param>
        /// <returns></returns>
        public static MethodInfo FillMethodMetrics(Microsoft.CodeAnalysis.CSharp.CSharpSyntaxNode node, MethodInfo mi)
        {
            mi.NL = NL.Calculate(node);
            mi.NLE = NLE.Calculate(node);
            mi.NOB = NOB.Calculate(node);
            mi.NOS = NOS.Calculate(node);
            return mi;
        }

        /// <summary>
        /// Converts an absolute path to a relative one
        /// </summary>
        /// <param name="filePath">The file to be converted to relative</param>
        /// <param name="referencePath">Absolute path of the reference</param>
        /// <returns></returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static string MakeRelativePath(string filePath, string referencePath)
        {
            return new Uri(referencePath).MakeRelativeUri(new Uri(filePath)).ToString();
        }

        /// <summary>
        /// Check soft and hard filter matching
        /// </summary>
        /// <param name="filePath"></param>
        /// <returns></returns>
        public static bool CheckOuterFilters(string filePath)
        {
            if (MainDeclaration.Instance.SoftFilter != null)
            {
                MainDeclaration.Instance.CurrentFileIsSoftFiltered = !MainDeclaration.Instance.SoftFilter.IsNecessaryToAnalyse(filePath);
            }
            if (MainDeclaration.Instance.HardFilter != null)
            {
                try
                {
                    return !MainDeclaration.Instance.HardFilter.IsNecessaryToAnalyse(filePath);
                }
                catch (Exception)
                {
                    WriteMsg.WriteLine("Warning: Wrong regular expression!", WriteMsg.MsgLevel.Warning);
                }
            }
            return false;
        }

        /// <summary>
        /// Fill Class propeties by collection
        /// </summary>
        public static void FillFromClassStack()
        {
            ClassInfo classInfo = MainDeclaration.Instance.ClassStack.Peek();

            if (classInfo.Id > 0)
            {
                Class clazz = MainDeclaration.Instance.LimFactory.getRef(classInfo.Id) as Class;
                bool firstRun = clazz.IsSubclassIsEmpty;
                foreach (KeyValuePair<uint, bool> subClass in classInfo.IsSubclass)
                {
                    if (subClass.Value) MainDeclaration.Instance.LimFactory.setFiltered(subClass.Key);
                    if (firstRun) clazz.addIsSubclass(subClass.Key);
                    else Safe_Edge(clazz, "IsSubclass", subClass.Key);
                }

                IEnumerable<uint> IsSubclass = classInfo.IsSubclass.Select(t => t.Key);
                Remove(ref IsSubclass);
                AddUses(clazz);
            }

            MainDeclaration.Instance.ClassStack.Pop();
            MainDeclaration.Instance.UsesStack.Pop();
        }

        /// <summary>
        /// Fill Method properties by collection
        /// </summary>
        /// <param name="methodInfo"></param>
        public static void FillFromMethodStack(MethodInfo methodInfo, bool needToPopUsesStack = true)
        {
            Method method = (Method)MainDeclaration.Instance.LimFactory.getRef(methodInfo.Id);
            LimBuilder.SymbolBuilder.fillCollectedMethodData(method, methodInfo);

            if (needToPopUsesStack) MainDeclaration.Instance.UsesStack.Pop();
        }

        /// <summary>
        /// Add uses to the list
        /// </summary>
        /// <param name="member"></param>
        public static void AddUses(Member member)
        {
            bool firstRun = member.UsesIsEmpty;
            foreach (uint id in MainDeclaration.Instance.UsesStack.Peek())
            {
                if (firstRun) member.addUses(id);
                else Safe_Edge(member, "Uses", id);
            }
        }

        /// <summary>
        /// Remove uses from the list
        /// </summary>
        /// <param name="ids"></param>
        public static void Remove(ref IEnumerable<uint> ids)
        {
            if (MainDeclaration.Instance.UsesStack.Count > 0)
            {
                Parallel.ForEach(ids, id =>
                {
                    MainDeclaration.Instance.UsesStack.Peek().Remove(id);
                });
            }
        }

        /// <summary>
        /// Create Unknown Type in the LIM
        /// </summary>
        public static Lim.Asg.Nodes.Type.Type UnknownType
        {
            get
            {
                MainDeclaration.Instance.LimFactory.beginType();
                MainDeclaration.Instance.LimFactory.addTypeFormer(
                    MainDeclaration.Instance.LimFactory.createTypeFormerType(
                        MainDeclaration.Instance.LimFactory.createSimpleType(Types.SimpleTypeKind.stkUnknown).Id
                    ).Id
                );
                return MainDeclaration.Instance.LimFactory.endType();
            }
        }

        /// <summary>
        /// Type building strategy
        /// </summary>
        /// <param name="node"></param>
        /// <param name="refs"></param>
        public static void AddLimTypeFormers(ISymbol node, ISymbol refs = null)
        {
            switch (node.Kind)
            {
                case SymbolKind.ArrayType:
                    MainDeclaration.Instance.LimFactory.addTypeFormer(MainDeclaration.Instance.LimFactory.createTypeFormerArray().Id);
                    var arrayTypeSymbol = node as IArrayTypeSymbol;
                    if (arrayTypeSymbol.ElementType != null)
                    {
                        if (arrayTypeSymbol.ElementType.IsInMetadata())
                            AddLimTypeFormers(arrayTypeSymbol.ElementType);
                        else
                        {
                            SyntaxNode syntaxNode = null;
                            var @ref = arrayTypeSymbol.ElementType.GetDefinition(out syntaxNode);
                            if (@ref != null && @ref.Kind == arrayTypeSymbol.ElementType.Kind)
                                if (@ref is INamedTypeSymbol && ((INamedTypeSymbol)@ref).IsGenericType)
                                    AddLimTypeFormers(arrayTypeSymbol.ElementType, @ref);
                                else
                                    AddLimTypeFormers(@ref);
                        }
                    }
                    break;

                case SymbolKind.TypeParameter:

                    GenericParameter gp = (GenericParameter)node.ConvertToLimNode();
                    if (gp == null) return;

                    MainDeclaration.Instance.LimFactory.addTypeFormer(MainDeclaration.Instance.LimFactory.createTypeFormerType(gp.Id).Id);

                    break;

                case SymbolKind.PointerType:
                    IPointerTypeSymbol pointerType = node as IPointerTypeSymbol;
                    if (pointerType.IsReferenceType)
                        MainDeclaration.Instance.LimFactory.addTypeFormer(MainDeclaration.Instance.LimFactory.createTypeFormerPointer(Types.PointerKind.ptkReference).Id);
                    else
                        MainDeclaration.Instance.LimFactory.addTypeFormer(MainDeclaration.Instance.LimFactory.createTypeFormerPointer(Types.PointerKind.ptkPointer).Id);
                    AddLimTypeFormers(pointerType.PointedAtType);
                    break;

                case SymbolKind.NamedType:
                    var namedTypeSymbol = node as INamedTypeSymbol;
                    if (namedTypeSymbol.IsGenericType)
                    {
                        ClassGenericInstance cgi = node.GetCGI(refs as INamedTypeSymbol);
                        MainDeclaration.Instance.LimFactory.addTypeFormer(
                            MainDeclaration.Instance.LimFactory.createTypeFormerType(cgi.Id).Id
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
                                SyntaxNode __node;
                                var _node = node.GetDefinition(out __node);
                                if (!node.IsInMetadata() && _node == null) break;

                                Base refLimNode = node.ConvertToLimNode();
                                if (node.IsInMetadata())
                                    MetaDataNameFiller(node, (Member)refLimNode);

                                MainDeclaration.Instance.LimFactory.addTypeFormer(MainDeclaration.Instance.LimFactory.createTypeFormerType(refLimNode.Id).Id);
                                return;
                        }

                        MainDeclaration.Instance.LimFactory.addTypeFormer(
                            MainDeclaration.Instance.LimFactory.createTypeFormerType(
                                MainDeclaration.Instance.LimFactory.createSimpleType(stk).Id
                            ).Id
                        );
                    }
                    break;
                case SymbolKind.DynamicType:
                case SymbolKind.ErrorType:
                    MainDeclaration.Instance.LimFactory.addTypeFormer(MainDeclaration.Instance.LimFactory.createTypeFormerNonType().Id);
                    break;
            }
        }

        /// <summary>
        /// Fill outer references LIM conversion properties
        /// </summary>
        /// <param name="symbol"></param>
        /// <param name="node"></param>
        public static void MetaDataNameFiller(ISymbol symbol, Member node)
        {
            node.MangledName = node.DemangledName = symbol.ToString();
            node.Name = symbol.Name;
            node.IsCompilerGenerated = true;
            switch (node.NodeKind)
            {
                case Types.NodeKind.ndkClass:
                    switch (((INamedTypeSymbol)symbol).TypeKind)
                    {
                        case TypeKind.Class:
                            ((Class)node).ClassKind = Types.ClassKind.clkClass;
                            break;
                        case TypeKind.Delegate:
                            ((Class)node).ClassKind = Types.ClassKind.clkDelegate;
                            break;
                        case TypeKind.Enum:
                            ((Class)node).ClassKind = Types.ClassKind.clkEnum;
                            break;
                        case TypeKind.Interface:
                            ((Class)node).ClassKind = Types.ClassKind.clkInterface;
                            break;
                        case TypeKind.Struct:
                            ((Class)node).ClassKind = Types.ClassKind.clkStruct;
                            break;
                    }
                    break;
                case Types.NodeKind.ndkMethod:
                    switch (((IMethodSymbol)symbol).MethodKind)
                    {
                        case MethodKind.AnonymousFunction:
                            break;
                        case MethodKind.BuiltinOperator:
                            ((Method)node).MethodKind = Types.MethodKind.mekOperator;
                            break;
                        case MethodKind.Constructor:
                            ((Method)node).MethodKind = Types.MethodKind.mekConstructor;
                            break;
                        case MethodKind.Conversion:
                            ((Method)node).MethodKind = Types.MethodKind.mekOperator;
                            break;
                        case MethodKind.DeclareMethod:
                            
                            break;
                        case MethodKind.Destructor:
                            ((Method)node).MethodKind = Types.MethodKind.mekDestructor;
                            break;
                        case MethodKind.EventAdd:
                            ((Method)node).MethodKind = Types.MethodKind.mekAdd;
                            break;
                        case MethodKind.EventRemove:
                            ((Method)node).MethodKind = Types.MethodKind.mekRemove;
                            break;
                        case MethodKind.PropertyGet:
                            ((Method)node).MethodKind = Types.MethodKind.mekGet;
                            break;
                        case MethodKind.PropertySet:
                            ((Method)node).MethodKind = Types.MethodKind.mekSet;
                            break;
                        case MethodKind.UserDefinedOperator:
                            ((Method)node).MethodKind = Types.MethodKind.mekOperator;
                            break;
                    }
                    break;
                default:
                    break;
            }
        }

        /// <summary>
        /// Create association edge for the File node
        /// </summary>
        /// <param name="limNode"></param>
        /// <param name="roslynNode"></param>
        public static void AddIsContainedInEdge(Member limNode, SyntaxNode roslynNode)
        {

            SourcePosition limPos = new SourcePosition();
            FileLinePositionSpan flps = roslynNode.GetLocation().GetLineSpan();
            limPos.Line = (uint)flps.StartLinePosition.Line + 1;
            limPos.Column = (uint)flps.StartLinePosition.Character + 1;
            limPos.EndLine = (uint)flps.EndLinePosition.Line + 1;
            limPos.EndColumn = (uint)flps.EndLinePosition.Character + 1;
            limPos.RealizationLevel = Types.RealizationLevel.relDefines;

            string filePath = Common.ProcessPath(roslynNode.GetLocation().SourceTree.FilePath);

            if (!string.IsNullOrEmpty(filePath))
            {
                File file = roslynNode.GetLocation().CreateFile();
                if (file == null) return;
                bool found = false;
                ListIteratorAssocSourcePosition<File> sourcePositionInFileBeginIt = limNode.IsContainedInListIteratorAssocBegin;

                for (File fileIt = sourcePositionInFileBeginIt.getValue(); fileIt != null; fileIt = sourcePositionInFileBeginIt.getNext().getValue())
                {
                    SourcePosition oldSp = sourcePositionInFileBeginIt.getAssocItem();
                    if
                    (
                        fileIt.Id == file.Id
                        && oldSp.Line == (uint)flps.StartLinePosition.Line + 1
                        && oldSp.Column == (uint)flps.StartLinePosition.Character + 1
                        && oldSp.EndLine == (uint)flps.EndLinePosition.Line + 1
                        && oldSp.EndColumn == (uint)flps.EndLinePosition.Character + 1
                    )
                    {
                        found = true;
                        break;
                    }
                }
                if (!found) limNode.addIsContainedIn(file, limPos);
            }
        }
        
        /// <summary>
        /// Add node to the edge without duplication.
        /// </summary>
        /// <param name="limNode">From node</param>
        /// <param name="name">Edge name</param>
        /// <param name="param">To node</param>
        public static void Safe_Edge(Base limNode, string name, uint param)
        {
            bool node_found = false;
            /*  node.##name##ListIterator */
            var it = limNode.GetListIteratorBegin(name);
            if (it != null)
            {
                for (; it.getValue() != null; it = it.getNext())
                {
                    if (it.getValue().Id == param)
                    {
                        node_found = true;
                        break;
                    }
                }
                if (!node_found)
                {
                    /*  node.add##name##(param) */
                    limNode.add(name, param);
                }
            }
        }

    }
}