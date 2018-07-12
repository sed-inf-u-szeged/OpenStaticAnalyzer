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
    /// Provides filtering mechanism for the ASG.
    /// </summary>
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class Filter {

        /// <summary>
        /// The possible states of the Filter.
        /// </summary>
        public enum FilterState {

            /// <summary>The node is filtered.</summary>
            Filtered,

            /// <summary>The node and all of its anchestors are not filtered.</summary>
            NotFiltered
        }

        /// <summary>Contains the states of the nodes.</summary>
        protected List<FilterState> container;

        /// <summary>Reference to the factory.</summary>
        protected Factory fact;

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="factory">[in] Reference to the Factory.</param>
        public Filter(Factory factory) {
            fact = factory;
            container = new List<FilterState>();
        }

        /// <summary>
        /// Initializes the Filter.
        /// </summary>
        public void initializeFilter() {
            for (int i = 0; i < container.Count; ++i)
                container[i] = FilterState.NotFiltered;

            while (container.Count < fact.Size)
                container.Add(FilterState.NotFiltered);
        }

        /// <summary>
        /// Tells whether the node is filtered or not.
        /// </summary>
        /// <param name="id">[in] The id of the node.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the id is too large (larger than the size of the Filter).</exception>
        /// <returns>Returns true if the node with the given id is filtered.</returns>
        public bool getIsFiltered(uint id) {
            if (container.Count <= id)
                throw new CsharpException("Columbus.Csharp.Asg.Filter.getIsSelected()", "Too large NodeId");

            return container[(int)id] == FilterState.Filtered;
        }

        /// <summary>
        /// Filters out the given node and all of its descendants.
        /// </summary>
        /// <param name="id">[in] The id of the node.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the id is too large (larger than the size of the Filter).</exception>
        public void setFiltered(uint id) {
            if (Common.getIsValid(id)) {
                Visitors.VisitorFilter visitorFilter = new Visitors.VisitorFilter(fact, true);
                Algorithms.AlgorithmPreorder algorithmPreorder = new Algorithms.AlgorithmPreorder();
                algorithmPreorder.run(fact, visitorFilter, fact.getRef(id));
            }
        }

        /// <summary>
        /// Sets the state of the node, all of its descendants and all of its ancestors to not filtered.
        /// </summary>
        /// <param name="id">[in] The id of the node.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the id is too large (larger than the size of the Filter).</exception>
        public void setNotFiltered(uint id) {
            if (fact.getExist(id)) {
                Factory.TurnFilterOffSafely turnFilterOffSafely = new Factory.TurnFilterOffSafely(fact);
                Visitors.VisitorFilter visitorFilter = new Visitors.VisitorFilter(fact, false);
                Algorithms.AlgorithmPreorder algorithmPreorder = new Algorithms.AlgorithmPreorder();
                algorithmPreorder.run(fact, visitorFilter, fact.getRef(id));
                do {
                    container[(int)id] = FilterState.NotFiltered;
                    id = fact.getRef(id).Parent;
                } while (id != 0);
                turnFilterOffSafely.restore();
            }
        }

        /// <summary>
        /// Sets the state of the node and all of its ancestors to not filtered.
        /// </summary>
        /// <param name="id">[in] The id of the node.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the id is too large (larger than the size of the Filter).</exception>
        public void setNotFilteredThisNode(uint id) {
            if (fact.getExist(id)) {
                do {
                    container[(int)id] = FilterState.NotFiltered;
                    id = fact.getRef(id).Parent;
                } while (id != 0 && container[(int)id] == FilterState.Filtered);
            }
        }

        /// <summary>
        /// Filter out only the given node (without its children).
        /// </summary>
        /// <param name="id">[in] The id of the node.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the id is too large (larger than the size of the Filter).</exception>
        public void setFilteredThisNodeOnly(uint id) {
            if (container.Count <= id)
                throw new CsharpException("Columbus.Csharp.Asg.Filter.setFilteredThisNodeOnly()", "Too large NodeId");

            if (id == fact.Root)
                return;

            container[(int)id] = FilterState.Filtered;
        }

        /// <summary>
        /// Sets the state of the given node (without its children) to not filtered.
        /// </summary>
        /// <param name="id">[in] The id of the node.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the id is too large (larger than the size of the Filter).</exception>
        public void setNotFilteredThisNodeOnly(uint id) {
            if (container.Count <= id)
                throw new CsharpException("Columbus.Csharp.Asg.Filter.setNotFilteredThisNodeOnly()", "Too large NodeId");

            container[(int)id] = FilterState.NotFiltered;
        }

        /// <summary>
        /// Gives back the state of the node.
        /// </summary>
        /// <param name="id">[in] The id of the node.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the id is too large (larger than the size of the Filter).</exception>
        /// <returns>Returns the state of the node.</returns>
        public FilterState getFilterState(uint id) {
            if (container.Count <= id)
                throw new CsharpException("Columbus.Csharp.Asg.Filter.getFilterState()", "Too large NodeId");

            return container[(int)id];
        }

        /// <summary>
        /// Returns the number of nodes in the ASG.
        /// </summary>
        /// <returns>The number of nodes in the ASG.</returns>
        public uint Size {
            get {
                return (uint)container.Count;
            }
        }

        /// <summary>
        /// Resizes the Filters container.
        /// </summary>
        /// <param name="newSize">[in] The new size of the container.</param>
        public void resizeTo(int newSize) {
            while (container.Count < newSize)
                container.Add(FilterState.NotFiltered);
        }

        /// <summary>
        /// Sets the given nodes filter state.
        /// </summary>
        /// <param name="nodeId">[in] The node.</param>
        /// <param name="state">[in] The filter state.</param>
        public void set(uint nodeId, FilterState state) {
            container[(int)nodeId] = state;
        }

        /// <summary>
        /// Saves the filter.
        /// </summary>
        /// <param name="io">[in] The filter is saved into "io".</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there's someting wrong with the file.</exception>
        public void save(IO io) {
            io.writeUInt4((uint)(container.Count));
            for (int i = 0; i < container.Count; ++i)
                io.writeUByte1((container[i] == FilterState.Filtered ? (byte)0 : (byte)1));
        }

        /// <summary>
        /// Loads the filter.
        /// </summary>
        /// <param name="io">[in] The filter is loaded from "io".</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there's someting wrong with the file.</exception>
        public void load(IO io) {
            uint size = io.readUInt4();
            container = new List<FilterState>();
            for (int i = 0; i < size; ++i)
                container.Add((io.readUByte1() == 0 ? FilterState.Filtered : FilterState.NotFiltered));
        }

    }

}
