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
using System.Collections.Generic;
using System.Text;

namespace Columbus.Csharp.Asg {

    /// <summary>
    /// ListIterator class, which iterates through Nodes.
    /// </summary>
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class ListIterator<T> where T : Columbus.Csharp.Asg.Nodes.Base.Base {

        /// <summary>
        /// Pointer to the Factory.
        /// </summary>
        protected Factory fact;

        /// <summary>
        /// Pointer to the Container the ids stored in.
        /// </summary>
        protected LinkedList<uint> container;

        /// <summary>
        /// Inner iterator of the Container.
        /// </summary>
        protected LinkedListNode<uint> it;

        /// <summary>
        /// Flag for invalidate.
        /// </summary>
        protected bool invalid;

        /// <summary>
        /// The actual node.
        /// </summary>
        protected T currentNode;

        /// <summary>
        /// Constructor, which creates a usable new iterator.
        /// </summary>
        /// <param name="_container">[in] The container which stores the ids of the nodes the iteration is going on it.</param>
        /// <param name="factory">[in] The Factory.</param>
        /// <param name="createAsBegin">[in] Create iterator begin or end.</param>
        public  ListIterator(LinkedList<uint> _container, Factory factory, bool createAsBegin) {
            fact = factory;
            container = _container;
            it = (createAsBegin)? container.First : container.Last;
            if (it != null) {
                currentNode = (T)fact.getRef(it.Value);
            }
            invalid = false;
            if (createAsBegin) {
                if (currentNode != null && fact.getIsFiltered(currentNode.Id)){
                        currentNode = getNext().getValue();
                }
            }
        }

        /// <summary>
        /// Creates an ListIterator by copying the one given in parameter.
        /// </summary>
        /// <param name="otherIt">[in] The other ListIteratorBase which initializes this one.</param>
        public ListIterator(ListIterator<T> iterator) {
            it = iterator.it;
            fact = iterator.fact;
            invalid = iterator.invalid;
            currentNode = iterator.currentNode;
            container = iterator.container;
        }

        /// <summary>
        /// Creates an ListIterator with new generic type.
        /// </summary>
        public ListIterator<K> Convert<K>() where K : Columbus.Csharp.Asg.Nodes.Base.Base
        {
            var converted = new ListIterator<K>(container, fact, true);
            converted.it = it;
            converted.currentNode = currentNode as K;
            converted.invalid = invalid;
            return converted;
        }

        public T getValue()
        {
                if (it == null) currentNode = null;
                return currentNode;
        }

        public ListIterator<T> getNext()
        {
                if (invalid)
                    throw new Exception();
                if (it != null) it = it.Next;
                while (it != null && fact.getIsFiltered(it.Value)) {
                    it = it.Next;
                }
                if (it == null) currentNode = null; 
                else currentNode = (T)fact.getRef(it.Value);
                return new ListIterator<T>(this);
        }

        public ListIterator<T> getPrevious()
        {
                if (invalid)
                    throw new Exception();
                if (it != null) it = it.Previous;
                while (it != null && fact.getIsFiltered(it.Value)) {
                    it = it.Next;
                }
                if (it == null) currentNode = null; 
                else currentNode = (T)fact.getRef(it.Value);
                return new ListIterator<T>(this);
        }

    }
}
