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

namespace Columbus.Lim.Asg {

    /// <summary>
    /// ListIteratorAssoc class, which iterates through Nodes.
    /// </summary>
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class ListIteratorAssoc<T> where T : Columbus.Lim.Asg.Nodes.Base.Base {

        /// <summary>
        /// Pointer to the Factory.
        /// </summary>
        protected Factory fact;

        /// <summary>
        /// Pointer to the Container the ids stored in.
        /// </summary>
        protected LinkedList<AssocEdge> container;

        /// <summary>
        /// Inner iterator of the Container.
        /// </summary>
        protected LinkedListNode<AssocEdge> it;

        /// <summary>
        /// Flag for invalidate.
        /// </summary>
        protected bool invalid;

        /// <summary>
        /// The actual node.
        /// </summary>
        protected T currentNode;

        /// <summary>
        /// Represent the association class which can be anything which can be represented by this union).
        /// </summary>
        public struct AssocClass {
            /// <summary>If the type associated with the edge is string, then use this value.</summary>
            public string acString;

            /// <summary>If the type associated with the edge is Types.TypeArgumentConstraintKind, then use this value.</summary>
            public Types.TypeArgumentConstraintKind acTypeArgumentConstraintKind;

            /// <summary>If the type associated with the edge is SourcePosition, then use this value.</summary>
            public SourcePosition acSourcePosition;

            /// <summary>If the type associated with the edge is Types.ParameterKind, then use this value.</summary>
            public Types.ParameterKind acParameterKind;
        }

        /// <summary>
        /// AssocEdge represents the edge which has association class (the id stores the end pointof the edge).
        /// </summary>
        public struct AssocEdge {
            /// <summary>Stores the end point of the edge.</summary>
            public uint id;

            /// <summary>Stores the associated value with the edge.</summary>
            public AssocClass assocClass;
        }

        /// <summary>
        /// Constructor, which creates a usable new iterator.
        /// </summary>
        /// <param name="_container">[in] The container which stores the ids of the nodes the iteration is going on it.</param>
        /// <param name="factory">[in] The Factory.</param>
        /// <param name="createAsBegin">[in] Create iterator begin or end.</param>
        public  ListIteratorAssoc(LinkedList<AssocEdge> _container, Factory factory, bool createAsBegin) {
            fact = factory;
            container = _container;
            it = (createAsBegin)? container.First : container.Last;
            if (it != null) {
                currentNode = (T)fact.getRef(it.Value.id);
            }
            invalid = false;
            if (createAsBegin) {
                if (currentNode != null && fact.getIsFiltered(currentNode.Id)){
                        currentNode = getNext().getValue();
                }
            }
        }

        /// <summary>
        /// Creates an ListIteratorAssoc by copying the one given in parameter.
        /// </summary>
        /// <param name="otherIt">[in] The other ListIteratorBase which initializes this one.</param>
        public ListIteratorAssoc(ListIteratorAssoc<T> iterator) {
            it = iterator.it;
            fact = iterator.fact;
            invalid = iterator.invalid;
            currentNode = iterator.currentNode;
            container = iterator.container;
        }

        public T getValue()
        {
                if (it == null) currentNode = null;
                return currentNode;
        }

        public ListIteratorAssoc<T> getNext()
        {
                if (invalid)
                    throw new Exception();
                if (it != null) it = it.Next;
                while (it != null && fact.getIsFiltered(it.Value.id)) {
                    it = it.Next;
                }
                if (it == null) currentNode = null; 
                else currentNode = (T)fact.getRef(it.Value.id);
                return new ListIteratorAssoc<T>(this);
        }

        public ListIteratorAssoc<T> getPrevious()
        {
                if (invalid)
                    throw new Exception();
                if (it != null) it = it.Previous;
                while (it != null && fact.getIsFiltered(it.Value.id)) {
                    it = it.Next;
                }
                if (it == null) currentNode = null; 
                else currentNode = (T)fact.getRef(it.Value.id);
                return new ListIteratorAssoc<T>(this);
        }

    }

    /// <summary>
    /// ListIteratorAssocString iterates edges whose association class represents 'string' type.
    /// </summary>
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class ListIteratorAssocString<T> : ListIteratorAssoc<T> where T : Columbus.Lim.Asg.Nodes.Base.Base {

        /// <summary>
        /// Constructor, which creates a usable new iterator.
        /// </summary>
        /// <param name="container">[in] The container which stores the ids of the nodes the iteration is going on it.</param>
        /// <param name="factory">[in] The Factory.</param>
        public ListIteratorAssocString(LinkedList<AssocEdge> container, Factory factory, bool createAsBegin) : base(container, factory, createAsBegin) {
        }

        /// <summary>
        /// Creates an ListIteratorAssocString by copying the one given in parameter.
        /// </summary>
        /// <param name="container">[in] The container which stores the ids of the nodes the iteration is going on it.</param>
        /// <param name="factory">[in] The Factory.</param>
        public ListIteratorAssocString(ListIteratorAssocString<T> iterator) : base(iterator) {
        }

        new public ListIteratorAssocString<T> getNext()
        {
                if (invalid)
                    throw new Exception();
                if (it != null) it = it.Next;
                while (it != null && fact.getIsFiltered(it.Value.id)) {
                    it = it.Next;
                }
                if (it == null) currentNode = null; 
                else currentNode = (T)fact.getRef(it.Value.id);
                return new ListIteratorAssocString<T>(this);
        }

        new public ListIteratorAssocString<T> getPrevious()
        {
                if (invalid)
                    throw new Exception();
                if (it != null) it = it.Previous;
                while (it != null && fact.getIsFiltered(it.Value.id)) {
                    it = it.Next;
                }
                if (it == null) currentNode = null; 
                else currentNode = (T)fact.getRef(it.Value.id);
                return new ListIteratorAssocString<T>(this);
        }

        /// <summary>
        /// Gives back the association class.
        /// </summary>
        /// <exception cref="Columbus.Lim.Asg.LimInvalidIteratorException">If the iterator is invalid LimInvalidIteratorException is thrown.</exception>
        /// <returns>Returns with the association class.</returns>
        public string getAssocItem() {
                return fact.StringTable.get(it.Value.assocClass.acString).ToString();

        }

    }


    /// <summary>
    /// ListIteratorAssocTypeArgumentConstraintKind iterates edges whose association class represents 'Types.TypeArgumentConstraintKind' type.
    /// </summary>
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class ListIteratorAssocTypeArgumentConstraintKind<T> : ListIteratorAssoc<T> where T : Columbus.Lim.Asg.Nodes.Base.Base {

        /// <summary>
        /// Constructor, which creates a usable new iterator.
        /// </summary>
        /// <param name="container">[in] The container which stores the ids of the nodes the iteration is going on it.</param>
        /// <param name="factory">[in] The Factory.</param>
        public ListIteratorAssocTypeArgumentConstraintKind(LinkedList<AssocEdge> container, Factory factory, bool createAsBegin) : base(container, factory, createAsBegin) {
        }

        /// <summary>
        /// Creates an ListIteratorAssocTypeArgumentConstraintKind by copying the one given in parameter.
        /// </summary>
        /// <param name="container">[in] The container which stores the ids of the nodes the iteration is going on it.</param>
        /// <param name="factory">[in] The Factory.</param>
        public ListIteratorAssocTypeArgumentConstraintKind(ListIteratorAssocTypeArgumentConstraintKind<T> iterator) : base(iterator) {
        }

        new public ListIteratorAssocTypeArgumentConstraintKind<T> getNext()
        {
                if (invalid)
                    throw new Exception();
                if (it != null) it = it.Next;
                while (it != null && fact.getIsFiltered(it.Value.id)) {
                    it = it.Next;
                }
                if (it == null) currentNode = null; 
                else currentNode = (T)fact.getRef(it.Value.id);
                return new ListIteratorAssocTypeArgumentConstraintKind<T>(this);
        }

        new public ListIteratorAssocTypeArgumentConstraintKind<T> getPrevious()
        {
                if (invalid)
                    throw new Exception();
                if (it != null) it = it.Previous;
                while (it != null && fact.getIsFiltered(it.Value.id)) {
                    it = it.Next;
                }
                if (it == null) currentNode = null; 
                else currentNode = (T)fact.getRef(it.Value.id);
                return new ListIteratorAssocTypeArgumentConstraintKind<T>(this);
        }

        /// <summary>
        /// Gives back the association class.
        /// </summary>
        /// <exception cref="Columbus.Lim.Asg.LimInvalidIteratorException">If the iterator is invalid LimInvalidIteratorException is thrown.</exception>
        /// <returns>Returns with the association class.</returns>
        public Types.TypeArgumentConstraintKind getAssocItem() {
                return it.Value.assocClass.acTypeArgumentConstraintKind;

        }

    }


    /// <summary>
    /// ListIteratorAssocSourcePosition iterates edges whose association class represents 'SourcePosition' type.
    /// </summary>
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class ListIteratorAssocSourcePosition<T> : ListIteratorAssoc<T> where T : Columbus.Lim.Asg.Nodes.Base.Base {

        /// <summary>
        /// Constructor, which creates a usable new iterator.
        /// </summary>
        /// <param name="container">[in] The container which stores the ids of the nodes the iteration is going on it.</param>
        /// <param name="factory">[in] The Factory.</param>
        public ListIteratorAssocSourcePosition(LinkedList<AssocEdge> container, Factory factory, bool createAsBegin) : base(container, factory, createAsBegin) {
        }

        /// <summary>
        /// Creates an ListIteratorAssocSourcePosition by copying the one given in parameter.
        /// </summary>
        /// <param name="container">[in] The container which stores the ids of the nodes the iteration is going on it.</param>
        /// <param name="factory">[in] The Factory.</param>
        public ListIteratorAssocSourcePosition(ListIteratorAssocSourcePosition<T> iterator) : base(iterator) {
        }

        new public ListIteratorAssocSourcePosition<T> getNext()
        {
                if (invalid)
                    throw new Exception();
                if (it != null) it = it.Next;
                while (it != null && fact.getIsFiltered(it.Value.id)) {
                    it = it.Next;
                }
                if (it == null) currentNode = null; 
                else currentNode = (T)fact.getRef(it.Value.id);
                return new ListIteratorAssocSourcePosition<T>(this);
        }

        new public ListIteratorAssocSourcePosition<T> getPrevious()
        {
                if (invalid)
                    throw new Exception();
                if (it != null) it = it.Previous;
                while (it != null && fact.getIsFiltered(it.Value.id)) {
                    it = it.Next;
                }
                if (it == null) currentNode = null; 
                else currentNode = (T)fact.getRef(it.Value.id);
                return new ListIteratorAssocSourcePosition<T>(this);
        }

        /// <summary>
        /// Gives back the association class.
        /// </summary>
        /// <exception cref="Columbus.Lim.Asg.LimInvalidIteratorException">If the iterator is invalid LimInvalidIteratorException is thrown.</exception>
        /// <returns>Returns with the association class.</returns>
        public SourcePosition getAssocItem() {
                return it.Value.assocClass.acSourcePosition;

        }

    }


    /// <summary>
    /// ListIteratorAssocParameterKind iterates edges whose association class represents 'Types.ParameterKind' type.
    /// </summary>
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class ListIteratorAssocParameterKind<T> : ListIteratorAssoc<T> where T : Columbus.Lim.Asg.Nodes.Base.Base {

        /// <summary>
        /// Constructor, which creates a usable new iterator.
        /// </summary>
        /// <param name="container">[in] The container which stores the ids of the nodes the iteration is going on it.</param>
        /// <param name="factory">[in] The Factory.</param>
        public ListIteratorAssocParameterKind(LinkedList<AssocEdge> container, Factory factory, bool createAsBegin) : base(container, factory, createAsBegin) {
        }

        /// <summary>
        /// Creates an ListIteratorAssocParameterKind by copying the one given in parameter.
        /// </summary>
        /// <param name="container">[in] The container which stores the ids of the nodes the iteration is going on it.</param>
        /// <param name="factory">[in] The Factory.</param>
        public ListIteratorAssocParameterKind(ListIteratorAssocParameterKind<T> iterator) : base(iterator) {
        }

        new public ListIteratorAssocParameterKind<T> getNext()
        {
                if (invalid)
                    throw new Exception();
                if (it != null) it = it.Next;
                while (it != null && fact.getIsFiltered(it.Value.id)) {
                    it = it.Next;
                }
                if (it == null) currentNode = null; 
                else currentNode = (T)fact.getRef(it.Value.id);
                return new ListIteratorAssocParameterKind<T>(this);
        }

        new public ListIteratorAssocParameterKind<T> getPrevious()
        {
                if (invalid)
                    throw new Exception();
                if (it != null) it = it.Previous;
                while (it != null && fact.getIsFiltered(it.Value.id)) {
                    it = it.Next;
                }
                if (it == null) currentNode = null; 
                else currentNode = (T)fact.getRef(it.Value.id);
                return new ListIteratorAssocParameterKind<T>(this);
        }

        /// <summary>
        /// Gives back the association class.
        /// </summary>
        /// <exception cref="Columbus.Lim.Asg.LimInvalidIteratorException">If the iterator is invalid LimInvalidIteratorException is thrown.</exception>
        /// <returns>Returns with the association class.</returns>
        public Types.ParameterKind getAssocItem() {
                return it.Value.assocClass.acParameterKind;

        }

    }

}
