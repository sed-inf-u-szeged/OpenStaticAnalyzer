/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2017 Department of Software Engineering - University of Szeged
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

using Microsoft.CodeAnalysis;
using System.Collections.Generic;
using System.Linq;

namespace Columbus.CSAN.Utils
{
    class SymbolMap<T>
    {
        private Dictionary<ISymbol, T> map;

        public SymbolMap()
        {
            map = new Dictionary<ISymbol, T>(new AnonymousClassSymbolEqualityComparer());
        }

        public void Add(ISymbol symbol, T limNodeId)
        {
            map.Add(symbol, limNodeId);
        }

        public bool ContainsKey(ISymbol symbol)
        {
            return map.ContainsKey(symbol);
        }

        public T this[ISymbol symbol]
        {
            get
            {
                return map[symbol];
            }
        }

        public bool TryGetValue(ISymbol node, out T id)
        {
            return map.TryGetValue(node, out id);
        }

        public ISymbol GetValueByKey(T key)
        {
            return map.FirstOrDefault(x => x.Value.Equals(key)).Key;
        }

        class AnonymousClassSymbolEqualityComparer : EqualityComparer<ISymbol>
        {
            public override bool Equals(ISymbol x, ISymbol y)
            {
                if (x.Kind == SymbolKind.NamedType)
                {
                    if (((INamedTypeSymbol)x).IsAnonymousType)
                    {
                        return x.DeclaringSyntaxReferences[0].Span.CompareTo(y.DeclaringSyntaxReferences[0].Span) == 0;
                    }
                }

                return x.Equals(y);
            }

            public override int GetHashCode(ISymbol obj)
            {
                return obj.GetHashCode();
            }
        }
    }
}
