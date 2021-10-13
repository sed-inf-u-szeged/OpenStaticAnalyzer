using System;
using Columbus.Lim.Asg;
using Columbus.Lim.Asg.Nodes.Base;
using Columbus.Lim.Asg.Nodes.Logical;
using Columbus.CSAN.Utils.Info;
using Columbus.CSAN.Metrics.Complexity;
using Columbus.CSAN.Metrics.Size;

using Microsoft.CodeAnalysis;
using System.Runtime.CompilerServices;
using Microsoft.CodeAnalysis.CSharp;

namespace Columbus.CSAN.Commons
{
    static class Common
    {
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
        public static MethodInfo FillMethodMetrics(CSharpSyntaxNode node, MethodInfo mi)
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
                        case TypeKind.Class: // TODO make this the default, eg for partial framework types
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
