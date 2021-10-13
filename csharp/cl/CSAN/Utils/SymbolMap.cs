using System;
using System.Collections;
using Microsoft.CodeAnalysis;
using System.Collections.Generic;
using Columbus.CSAN.Extensions;

namespace Columbus.CSAN.Utils
{
    class SymbolMap<T> : IDictionary<ISymbol, T>
    {
        private readonly Dictionary<ISymbol, T> map;

        public SymbolMap()
        {
            map = new Dictionary<ISymbol, T>(new SymbolEqualityComparer());
        }

        public void Add(ISymbol symbol, T limNodeId) => map.Add(symbol, limNodeId);

        public bool ContainsKey(ISymbol symbol) => map.ContainsKey(symbol);
        public bool Remove(ISymbol key) => map.Remove(key);

        public T this[ISymbol symbol]
        {
            get => map[symbol];
            set => map[symbol] = value;
        }

        public ICollection<ISymbol> Keys => map.Keys;

        public ICollection<T> Values => map.Values;

        public bool TryGetValue(ISymbol node, out T id) => map.TryGetValue(node, out id);


        public IEnumerator<KeyValuePair<ISymbol, T>> GetEnumerator() => map.GetEnumerator();

        IEnumerator IEnumerable.GetEnumerator() => ((IEnumerable)map).GetEnumerator();

        public void Add(KeyValuePair<ISymbol, T> item) => ((ICollection<KeyValuePair<ISymbol, T>>)map).Add(item);

        public void Clear() => map.Clear();

        public bool Contains(KeyValuePair<ISymbol, T> item) => ((ICollection<KeyValuePair<ISymbol, T>>)map).Contains(item);

        public void CopyTo(KeyValuePair<ISymbol, T>[] array, int arrayIndex) => ((ICollection<KeyValuePair<ISymbol, T>>)map).CopyTo(array, arrayIndex);

        public bool Remove(KeyValuePair<ISymbol, T> item) => ((ICollection<KeyValuePair<ISymbol, T>>)map).Remove(item);

        public int Count => map.Count;

        public bool IsReadOnly => false;

        class SymbolEqualityComparer : EqualityComparer<ISymbol>
        {
            public override bool Equals(ISymbol x, ISymbol y)
            {
                if (ReferenceEquals(x, y))
                    return true;

                if (ReferenceEquals(x, null) ||
                    ReferenceEquals(y, null) ||
                    x.Kind != y.Kind ||
                    x.CanBeReferencedByName != y.CanBeReferencedByName)
                    return false;

                if (!x.CanBeReferencedByName && x.Kind == SymbolKind.Method)
                {
                    // lambdas and delegates
                    if (string.IsNullOrEmpty(x.Name))
                        return Equals(x.DeclaringSyntaxReferences[0].Span, y.DeclaringSyntaxReferences[0].Span) &&
                               Equals(x.DeclaringSyntaxReferences[0].SyntaxTree.FilePath, y.DeclaringSyntaxReferences[0].SyntaxTree.FilePath);
                    // anonymous class property accessors
                    return Equals(x.ContainingSymbol, y.ContainingSymbol) && Equals(x.ToString(), y.ToString());
                }

                if (x.Kind == SymbolKind.Parameter && !Equals(x.ContainingSymbol, y.ContainingSymbol))
                    return false;

                return x.Name == y.Name &&
                       x.MetadataName == y.MetadataName &&
                       Equals(x.ToString().TrimEnd('?'), y.ToString().TrimEnd('?'));
            }

            public override int GetHashCode(ISymbol obj)
            {
                var hashCode = new HashCode();

                if (!obj.CanBeReferencedByName && obj.Kind == SymbolKind.Method)
                {
                    // delegates and lambdas
                    if (string.IsNullOrEmpty(obj.Name))
                    {
                        hashCode.Add(obj.DeclaringSyntaxReferences[0].Span.GetHashCode());
                        hashCode.Add(obj.DeclaringSyntaxReferences[0].SyntaxTree.FilePath);
                    }
                    // anonymous type property getters
                    else
                    {
                        hashCode.Add(GetHashCode(obj.ContainingSymbol));
                        hashCode.Add(obj.ToString());
                    }
                    return hashCode.ToHashCode();
                }

                if (obj.Kind == SymbolKind.Parameter)
                    hashCode.Add(GetHashCode(obj.ContainingSymbol));

                hashCode.Add(obj.Kind);
                hashCode.Add(obj.Name);
                hashCode.Add(obj.MetadataName);
                hashCode.Add(obj.ToString().TrimEnd('?'));

                return hashCode.ToHashCode();
            }
        }
    }
}
