using System;
using System.Linq;
using Columbus.Lim.Asg;
using Columbus.Lim.Asg.Nodes.Base;
using Columbus.Lim.Asg.Nodes.Logical;

using Columbus.CSAN.Commons;
using Columbus.CSAN.LimBuilder;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace Columbus.CSAN.Extensions
{
    static class SymbolExtension
    {
        public static string GetFullMetadataName(this ISymbol s)
        {
            if (s.DeclaringSyntaxReferences.FirstOrDefault()?.GetSyntax() is LocalFunctionStatementSyntax)
                return s.ContainingSymbol.ToString() + '.' + s.ToString();
            else
                return s.ToString();
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
                    var method = (IMethodSymbol)typeInfo;
                    if (method.IsGenericMethod)
                    {
                        return Types.NodeKind.ndkMethodGeneric;
                    }
                    return Types.NodeKind.ndkMethod;
                case SymbolKind.Namespace: return Types.NodeKind.ndkPackage;
                case SymbolKind.Parameter: return Types.NodeKind.ndkParameter;
                case SymbolKind.Field:
                case SymbolKind.Event:
                    return Types.NodeKind.ndkAttribute;
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
            throw new ArgumentException($"Unknown SymbolKind: {typeInfo.Kind}", nameof(typeInfo));
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="node"></param>
        /// <returns></returns>
        public static bool IsInMetadata(this ISymbol node)
        {
            return node.DeclaringSyntaxReferences.IsEmpty;
        }

        /// <summary>
        /// Symbol is anonymous type
        /// </summary>
        /// <param name="symbol"></param>
        /// <returns>Return true if symbol is anonymous type</returns>
        public static bool IsAnonymousType(this ISymbol symbol)
        {
            return symbol is INamedTypeSymbol namedTypeSymbol && namedTypeSymbol.IsAnonymousType;
        }

        /// <summary>
        /// Symbol is anonymous method
        /// </summary>
        /// <param name="symbol"></param>
        /// <returns>Return true if symbol is iMethodSymbol and symbol's MethodKind is AnonymousFunction</returns>
        public static bool IsAnonymousMethod(this ISymbol symbol)
        {
            return symbol is IMethodSymbol methodSymbol && methodSymbol.MethodKind == MethodKind.AnonymousFunction;
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
                || symbol is IFieldSymbol
                || symbol is IEventSymbol;
        }
    }
}
