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

using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;
using System.Diagnostics;

namespace Columbus.Csharp.Asg {

    /// <summary>
    /// Factory, which handles (creates, deletes, sets their properties) nodes.
    /// </summary>
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class Factory {

        /// <summary>Container where the nodes are stored.</summary>
        private List<Columbus.Csharp.Asg.Nodes.Base.Base> container;

        /// <summary>Reference to the StingTable.</summary>
        private StrTable strTable;

        /// <summary>The Filter of the ASG.</summary>
        private Filter filter;

        /// <summary>Stores whether the filter is turned on or off.</summary>
        private bool filterOn;

        /// <summary>The id of the root of the ASG.</summary>
        private uint root;

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="strTbl">[in] Reference to the StrTable.</param>
        public Factory(StrTable strTbl) {
            container = new List<Columbus.Csharp.Asg.Nodes.Base.Base>();
            strTable = strTbl;
            filterOn = true;
            filter = new Filter(this);

            root = ((Columbus.Csharp.Asg.Nodes.Structure.CompilationUnitSyntax)createNode(Types.NodeKind.ndkCompilationUnitSyntax, 100)).Id;
        }

        /// <summary>
        /// Saves the graph.
        /// </summary>
        /// <param name="fileName">[in] The graph is saved into this file.</param>
        /// <param name="header">[in] The header information (also will be saved).</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if the file can not be opened.</exception>
        public void save(string fileName, List<IHeaderData> headerDataList) {
            TurnFilterOffSafely turnFilterOffSafely = new TurnFilterOffSafely(this);
        
            IO io = new IO(fileName, System.IO.FileMode.Create);
        
            try {
                io.writeString("csi");
                bool isContainPropertyData = false;
                for (int i = 0; i < headerDataList.Count; i++) {
                    if (headerDataList[i].Type == HeaderDataTypeKind.hdkPropertyData) {
                        if (i + 1 < headerDataList.Count) {
        		            headerDataList.Insert(0, headerDataList[i]);
                          headerDataList.RemoveAt(++i);
                        }
                        isContainPropertyData = true;
                        break;
                    }
                }
                if (!isContainPropertyData) {
                    PropertyData header = new PropertyData();
                    io.writeUInt4((uint)headerDataList.Count + 1);
                    header.add(PropertyData.csih_Type, "CSharpLanguage");
                    header.add(PropertyData.csih_APIVersion, Constant.APIVersion);
                    header.add(PropertyData.csih_BinaryVersion, Constant.BinaryVersion);
                    io.writeUShort2((ushort)header.Type);
                    io.writeStartSizeOfBlock();
                    header.save(io);
                    io.writeEndSizeOfBlock();
                } else {
                    io.writeUInt4((uint)headerDataList.Count);
                }
                foreach (var headerData in headerDataList) {
                    if (headerData.Type == HeaderDataTypeKind.hdkPropertyData) {
                        PropertyData header = headerData as PropertyData;
                        header.add(PropertyData.csih_Type, "CSharpLanguage");
                        header.add(PropertyData.csih_APIVersion, Constant.APIVersion);
                        header.add(PropertyData.csih_BinaryVersion, Constant.BinaryVersion);
                    }
                    io.writeUShort2((ushort)headerData.Type);
                    io.writeStartSizeOfBlock();
                    headerData.save(io);
                    io.writeEndSizeOfBlock();
                }

                Algorithms.AlgorithmPreorder algPre = new Algorithms.AlgorithmPreorder();
                Visitors.VisitorSave vSave = new Visitors.VisitorSave(io);
                algPre.run(this, vSave);
        
                io.writeUInt4(0);
                io.writeUShort2(0);

                strTable.save(io);
            } finally {
                io.close();
            }
        
            turnFilterOffSafely.restore();
        }

        /// <summary>
        /// Checks if the ASG file is valid or not.
        /// </summary>
        /// <param name="fileName">[in] The graph is loaded from this file.</param>
        /// <returns>The ASG is valid or if it is not, then the errors int the ASG file.</returns>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if the file can not be opened.</exception>
        private void checkPropertyData(PropertyData propertyData) {
            string info = "";
            if (!propertyData.get(PropertyData.csih_Type, out info)) {
                throw new CsharpException("Columbus.Csharp.Factory.checkPropertyData()", "Missing file type information");
            }
            if (info != "CSharpLanguage") {
                throw new CsharpException("Columbus.Csharp.Factory.checkPropertyData()", "Wrong file type information");
            }
            if (!propertyData.get(PropertyData.csih_APIVersion, out info)) {
                throw new CsharpException("Columbus.Csharp.Factory.checkPropertyData()", "Missing API version information");
            }
            if (info != Constant.APIVersion) {
                throw new CsharpException("Columbus.Csharp.Factory.checkPropertyData()", "Wrong API version(" + Constant.APIVersion + " required, " + info + " found)");
            }
            if (!propertyData.get(PropertyData.csih_BinaryVersion, out info)) {
                throw new CsharpException("Columbus.Csharp.Factory.checkPropertyData()", "Missing binary version information");
            }
            if (info != Constant.APIVersion) {
                throw new CsharpException("Columbus.Csharp.Factory.checkPropertyData()", "Wrong API version(" + Constant.BinaryVersion + " required, " + info + " found)");
            }
        }

        /// <summary>
        /// Loads the graph.
        /// </summary>
        /// <param name="fileName">[in] The graph is loaded from this file.</param>
        /// <param name="header">[in] The header information (also will be loaded).</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if the file can not be opened.</exception>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the ASG.</exception>
        public void load(string fileName, LinkedList<IHeaderData> headerDataList) {
            container = new List<Columbus.Csharp.Asg.Nodes.Base.Base>();
        
            IO io = new IO(fileName, System.IO.FileMode.Open);
        
            try {
                string headerString;
                io.readData(out headerString, 4);
                if (headerString != "csi\0") return;
                uint CsiHeaderSize = io.readUInt4();

                for (int i = 0; i < CsiHeaderSize; ++i) {
                    HeaderDataTypeKind type = (HeaderDataTypeKind)io.readUShort2();
                    bool handled = false;
                    foreach (IHeaderData headerData in headerDataList) {
                        if (type == headerData.Type) {
                            handled = true;
                            io.readULong8();
                            headerData.load(io);
                            if (type == HeaderDataTypeKind.hdkPropertyData) {
                                checkPropertyData((PropertyData)headerData);
                            }
                            break;
                        }
                    }
                    if (!handled) {
                        if (type == HeaderDataTypeKind.hdkPropertyData) {
                            PropertyData propertyData = new PropertyData();
                            io.readULong8();
                            propertyData.load(io);
                            checkPropertyData(propertyData);
                        } else {
                            long size = (long)io.readULong8();
                            io.vSkip(size - 8);
                        }
                    }
                }
                uint id = root = io.readUInt4();
                Types.NodeKind kind = (Types.NodeKind)io.readUShort2();
        
                while (id != 0 || (uint)kind != 0) {
                    createNode(kind, id);
                    container[(int)id].load(io);
        
                    id = io.readUInt4();
                    kind = (Types.NodeKind)io.readUShort2();
                }
                strTable.load(io);
            } finally {
                io.close();
            }
        }

        /// <summary>
        /// Gives back the id of the root node.
        /// </summary>
        /// <returns>The id of the root node.</returns>
        public uint Root {
            get {
                return root;
            }
        }

        /// <summary>
        /// Decides whether it is a valid id or not.
        /// </summary>
        /// <param name="id">[in] The id whose validity is examined.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the id is greater than the size of the container (greater than the largest id in the graph).</exception>
        /// <returns>Returns true if a node belongs to the id.</returns>
        public bool getExist(uint id) {
            if (container.Count <= id)
                throw new CsharpException("Columbus.Csharp.Asg.Factory.getExist()", "Invalid NodeId (" + id.ToString() + ")");
            return container[(int)id] != null;
        }

        /// <summary>
        /// Gives back a reference to the node.
        /// </summary>
        /// <param name="id">[in] The id of the node.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there is no node for the id.</exception>
        /// <returns>Reference to the node.</returns>
        public Columbus.Csharp.Asg.Nodes.Base.Base getRef(uint id) {
            Columbus.Csharp.Asg.Nodes.Base.Base nodeRef = null;
            if (id < container.Count)
                nodeRef = container[(int)id];
            //if (nodeRef == null)
                //throw new CsharpException("Columbus.Csharp.Asg.Factory.getRef()", "Invalid NodeId (" + id.ToString() + ")");
            return nodeRef;
        }

        /// <summary>
        /// Gives back a reference to the StringTable.
        /// </summary>
        /// <returns>Reference to the StringTable.</returns>
        public StrTable StringTable {
            get {
                return strTable;
            }
        }

        public bool isIndividual(int id) {
           return (container[id] != null) && (container[id].Parent == 0);
        }

        /// <summary>
        /// Gives back the NodeKind of a node.
        /// </summary>
        /// <param name="id">[in] The id of the node.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there is no node for the id.</exception>
        /// <returns>The NodeKind of the node.</returns>
        public Types.NodeKind getNodeKind(uint id) {
            return getRef(id).NodeKind;
        }


        // ******************** Iterator ********************

        /// <summary>
        /// Nested iterator class which enumerates the nodes in the ASG.
        /// </summary>
        public class Iterator {

            /// <summary>
            /// Constructor for Iterator.
            /// </summary>
            /// <param name="container">[in] The Container</param>
            /// <param name="factory">[in] The Factory.</param>
            public Iterator(List<Columbus.Csharp.Asg.Nodes.Base.Base> container, Factory factory) {
                cont = container;
                fact = factory;
                currentPosition = 0;
            }

            /// <summary>
            /// Examines the existance of the next node.
            /// </summary>
            /// <returns>Returns true if a next node exists.</returns>
            public bool hasNext() {
                    int pos = currentPosition;
                    while (pos < cont.Count && (cont[pos] == null || fact.getIsFiltered(cont[pos].Id)))
                        ++pos;
                    return pos < cont.Count;
            }

            /// <summary>
            /// Returns a reference of the next node (Columbus.Csharp.Asg.Nodes.Base.Base).
            /// </summary>
            /// <returns>Reference of the next node.</returns>
            /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the next element does not exist.</exception>
            public Columbus.Csharp.Asg.Nodes.Base.Base getNext() {
                    while (currentPosition < cont.Count && (cont[currentPosition] == null || fact.getIsFiltered(cont[currentPosition].Id)))
                        ++currentPosition;
                    if (currentPosition >= cont.Count)
                        throw new CsharpException("Columbus.Csharp.Asg.Factory.Iterator.next()", "Next element does not exist");
                    return cont[currentPosition++];
            }

            /// <summary>The Container.</summary>
            private List<Columbus.Csharp.Asg.Nodes.Base.Base> cont;

            /// <summary>The Factory.</summary>
            private Factory fact;

            /// <summary>The actual position.</summary>
            private int currentPosition;

        }

        /// <summary>
        /// Creates and returns an iterator, which enumerates the nodes in the ASG.
        /// </summary>
        /// <returns>An iterator to the nodes.</returns>
        public Iterator getIterator() {
            return new Iterator(container, this);
        }

        /// <summary>
        /// Tells whether the ASG has nodes (O(n)).
        /// </summary>
        /// <returns>Returns true if there is not any node.</returns>
        public bool IsEmpty {
            get {
                for (int i = 0; i < container.Count; ++i) {
                    if (container[i] != null) {
                        return false;
                    }
                }

                return true;
            }
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


        // ******************** Filter ********************

        /// <summary>
        /// Turns the Filter on.
        /// </summary>
        public void turnFilterOn() {
            filterOn = true;
        }

        /// <summary>
        /// Turns the Filter off.
        /// </summary>
        public void turnFilterOff() {
            filterOn = false;
        }

        /// <summary>
        /// A solution to turn Filter off safely.
        /// </summary>
        public class TurnFilterOffSafely {

            /// <summary>
            /// Constructor to turn Filter off safely.
            /// </summary>
            /// <param name="factory">[in] Reference to the Factory.</param>
            public TurnFilterOffSafely(Factory factory) {
                try {
                    fact = factory;
                    oldState = factory.IsFilterTurnedOn;
                    factory.turnFilterOff();
                } catch { }
            }

            /// <summary>
            /// Restores the filter state safely.
            /// </summary>
            public void restore() {
                try {
                    if (oldState)
                        fact.turnFilterOn();
                } catch { }
            }

            /// <summary>Reference to the Factory.</summary>
            private Factory fact;

            /// <summary>The original state of the Filter.</summary>
            private bool oldState;

        }

        /// <summary>
        /// Gives back the state of the Filter.
        /// </summary>
        /// <returns>Returns true if the Filter is turned on, otherwise returns false.</returns>
        public bool IsFilterTurnedOn {
            get {
                return filterOn;
            }
        }

        /// <summary>
        /// Initializes the filter (see Filter.initializeFilter() for more details).
        /// </summary>
        public void initializeFilter() {
            filter.initializeFilter();
        }

        /// <summary>
        /// Tells whether the given node is filtered or not.
        /// </summary>
        /// <param name="id">[in] The id of the node.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the id is too large (larger than the size of the ASG).</exception>
        /// <returns>Returns true if the Node is filtered and returns false if it isn't (or the filter mode is turned off).</returns>
        public bool getIsFiltered(uint id) {
            return !filterOn ? false : filter.getIsFiltered(id);
        }

        /// <summary>
        /// Filters out the given node and all of its descendants.
        /// </summary>
        /// <param name="id">[in] The id of the node.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException id the id is too large (larger than the size of the Filter).</exception>
        public void setFiltered(uint id) {
            filter.setFiltered(id);
        }

        /// <summary>
        /// Sets the state of the node, all of its descendants and all of its ancestors to not filtered.
        /// </summary>
        /// <param name="id">[in] The id of the node.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException id the id is too large (larger than the size of the Filter).</exception>
        public void setNotFiltered(uint id) {
            filter.setNotFiltered(id);
        }

        /// <summary>
        /// Sets the state of the node and all of its ancestors to not filtered.
        /// </summary>
        /// <param name="id">[in] The id of the node.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException id the id is too large (larger than the size of the Filter).</exception>
        public void setNotFilteredThisNode(uint id) {
            filter.setNotFilteredThisNode(id);
        }

        /// <summary>
        /// Gives back the filter state (csharp.Filter.FilterStae) of the given node irrespectively of the state of the filter mode.
        /// </summary>
        /// <param name="id">[in] The id of the node.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the id is too large (larger than the size of the ASG).</exception>
        /// <returns>Returns with the state of the filter.</returns>
        public Filter.FilterState getFilterState(uint id) {
            return filter.getFilterState(id);
        }

        /// <summary>
        /// Loads the filter.
        /// </summary>
        /// <param name="fileName">[in] Then name of the filter file.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the filter contains more (or less) node than the factory does.</exception>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if any error happens during the loading.</exception>
        public void loadFilter(string fileName) {
            IO io = new IO(fileName, System.IO.FileMode.Open);

            if (filter == null)
                filter = new Filter(this);

            if (filter == null)
                throw new CsharpException("Columbus.Csharp.Asg.Factory.loadFilter", "Memory allocation error");

            filter.load(io);

            if (container.Count > filter.Size)
                throw new CsharpException("Columbus.Csharp.Asg.Factory.loadFilter", "The loaded filter does not match to the current ASG");

            io.close();
        }

        /// <summary>
        /// Saves the filter.
        /// </summary>
        /// <param name="fileName">[in] Then name of the filter file.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if any error happens during the saving.</exception>
        public void saveFilter(string fileName) {
            IO io = new IO(fileName, System.IO.FileMode.Create);
            if (filter != null)
                filter.save(io);
            io.close();
        }

        /// <summary>
        /// Filter out only the given node (without its children).
        /// </summary>
        /// <param name="id">[in] The id of the node.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException id the id is too large (larger than the size of the Filter).</exception>
        public void setFilteredThisNodeOnly(uint id) {
            filter.setFilteredThisNodeOnly(id);
        }

        /// <summary>
        /// Set only the given node to not filtered (without its children).
        /// </summary>
        /// <param name="id">[in] The id of the node.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException id the id is too large (larger than the size of the Filter).</exception>
        public void setNotFilteredThisNodeOnly(uint id) {
            filter.setNotFilteredThisNodeOnly(id);
        }


        // ******************** CreateNode ********************

        /// <summary>
        /// Creates a new node, insert it into the container and return with its id.
        /// </summary>
        /// <param name="kind">[in] The kind of the node.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">If an invalid (or an abstract) NodeKind is given, CsharpException is thrown.</exception>
        /// <returns>Reference to the new node.</returns>
        public Columbus.Csharp.Asg.Nodes.Base.Base createNode(Types.NodeKind kind) {
            Columbus.Csharp.Asg.Nodes.Base.Base newNode = null;

            switch (kind) {
                case Types.NodeKind.ndkAliasQualifiedNameSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.AliasQualifiedNameSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkAnonymousMethodExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.AnonymousMethodExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkAnonymousObjectCreationExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.AnonymousObjectCreationExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkArrayCreationExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.ArrayCreationExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkArrayTypeSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.ArrayTypeSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkAssignmentExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.AssignmentExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkAwaitExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.AwaitExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkBaseExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.BaseExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkBinaryExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.BinaryExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkCastExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.CastExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkCheckedExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.CheckedExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkConditionalAccessExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.ConditionalAccessExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkConditionalExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.ConditionalExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkDefaultExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.DefaultExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkElementAccessExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.ElementAccessExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkElementBindingExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.ElementBindingExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkGenericNameSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.GenericNameSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkIdentifierNameSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkImplicitArrayCreationExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.ImplicitArrayCreationExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkImplicitElementAccessSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.ImplicitElementAccessSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkInitializerExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.InitializerExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkInterpolatedStringExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.InterpolatedStringExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkInvocationExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.InvocationExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkLiteralExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.LiteralExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkMakeRefExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.MakeRefExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkMemberAccessExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.MemberAccessExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkMemberBindingExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.MemberBindingExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkNullableTypeSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.NullableTypeSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkObjectCreationExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.ObjectCreationExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkOmittedArraySizeExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.OmittedArraySizeExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkOmittedTypeArgumentSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.OmittedTypeArgumentSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkParenthesizedExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkParenthesizedLambdaExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedLambdaExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkPointerTypeSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.PointerTypeSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkPostfixUnaryExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.PostfixUnaryExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkPredefinedTypeSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.PredefinedTypeSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkPrefixUnaryExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.PrefixUnaryExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkQualifiedNameSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.QualifiedNameSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkQueryExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.QueryExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkRefTypeExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.RefTypeExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkRefValueExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.RefValueExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkSimpleLambdaExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.SimpleLambdaExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkSizeOfExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.SizeOfExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkStackAllocArrayCreationExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.StackAllocArrayCreationExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkThisExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.ThisExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkTypeOfExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.TypeOfExpressionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkBlockSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkBreakStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.BreakStatementSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkCheckedStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.CheckedStatementSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkContinueStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.ContinueStatementSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkDoStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.DoStatementSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkEmptyStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.EmptyStatementSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkExpressionStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.ExpressionStatementSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkFixedStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.FixedStatementSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkForEachStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.ForEachStatementSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkForStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.ForStatementSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkGotoStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.GotoStatementSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkIfStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.IfStatementSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkLabeledStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.LabeledStatementSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkLocalDeclarationStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.LocalDeclarationStatementSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkLockStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.LockStatementSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkReturnStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.ReturnStatementSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkSwitchStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.SwitchStatementSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkThrowStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.ThrowStatementSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkTryStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.TryStatementSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkUnsafeStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.UnsafeStatementSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkUsingStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.UsingStatementSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkWhileStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.WhileStatementSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkYieldStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.YieldStatementSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkAccessorDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkAccessorListSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.AccessorListSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkAnonymousObjectMemberDeclaratorSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.AnonymousObjectMemberDeclaratorSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkArgumentListSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.ArgumentListSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkArgumentSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.ArgumentSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkArrayRankSpecifierSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.ArrayRankSpecifierSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkArrowExpressionClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.ArrowExpressionClauseSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkAttributeArgumentListSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentListSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkAttributeArgumentSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkAttributeListSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkAttributeSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.AttributeSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkAttributeTargetSpecifierSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.AttributeTargetSpecifierSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkBaseListSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.BaseListSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkBracketedArgumentListSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.BracketedArgumentListSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkBracketedParameterListSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.BracketedParameterListSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkCaseSwitchLabelSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.CaseSwitchLabelSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkCatchClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.CatchClauseSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkCatchDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.CatchDeclarationSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkCatchFilterClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.CatchFilterClauseSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkClassDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.ClassDeclarationSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkClassOrStructConstraintSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.ClassOrStructConstraintSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkCompilationUnitSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.CompilationUnitSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkConstructorConstraintSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.ConstructorConstraintSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkConstructorDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.ConstructorDeclarationSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkConstructorInitializerSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.ConstructorInitializerSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkConversionOperatorDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorDeclarationSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkConversionOperatorMemberCrefSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorMemberCrefSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkCrefBracketedParameterListSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.CrefBracketedParameterListSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkCrefParameterListSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.CrefParameterListSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkCrefParameterSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.CrefParameterSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkDefaultSwitchLabelSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.DefaultSwitchLabelSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkDelegateDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.DelegateDeclarationSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkDestructorDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.DestructorDeclarationSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkElseClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.ElseClauseSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkEnumDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.EnumDeclarationSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkEnumMemberDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.EnumMemberDeclarationSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkEqualsValueClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.EqualsValueClauseSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkEventDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.EventDeclarationSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkEventFieldDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.EventFieldDeclarationSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkExplicitInterfaceSpecifierSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.ExplicitInterfaceSpecifierSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkExternAliasDirectiveSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.ExternAliasDirectiveSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkFieldDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.FieldDeclarationSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkFinallyClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.FinallyClauseSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkFromClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.FromClauseSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkGlobalStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.GlobalStatementSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkGroupClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.GroupClauseSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkIncompleteMemberSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.IncompleteMemberSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkIndexerDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.IndexerDeclarationSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkIndexerMemberCrefSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.IndexerMemberCrefSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkInterfaceDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.InterfaceDeclarationSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkInterpolatedStringTextSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringTextSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkInterpolationAlignmentClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.InterpolationAlignmentClauseSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkInterpolationFormatClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.InterpolationFormatClauseSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkInterpolationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.InterpolationSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkJoinClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.JoinClauseSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkJoinIntoClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.JoinIntoClauseSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkLetClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.LetClauseSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkMethodDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.MethodDeclarationSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkNameColonSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.NameColonSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkNameEqualsSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.NameEqualsSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkNameMemberCrefSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.NameMemberCrefSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkNamespaceDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.NamespaceDeclarationSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkOperatorDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.OperatorDeclarationSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkOperatorMemberCrefSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.OperatorMemberCrefSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkOrderByClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.OrderByClauseSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkOrderingSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.OrderingSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkParameterListSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.ParameterListSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkParameterSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.ParameterSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkPropertyDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.PropertyDeclarationSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkQualifiedCrefSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.QualifiedCrefSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkQueryBodySyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.QueryBodySyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkQueryContinuationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.QueryContinuationSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkSelectClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.SelectClauseSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkSimpleBaseTypeSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.SimpleBaseTypeSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkStructDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.StructDeclarationSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkSwitchSectionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.SwitchSectionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkSyntaxToken:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.SyntaxToken((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkTypeArgumentListSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.TypeArgumentListSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkTypeConstraintSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.TypeConstraintSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkTypeCrefSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.TypeCrefSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkTypeParameterConstraintClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkTypeParameterListSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.TypeParameterListSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkTypeParameterSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.TypeParameterSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkUsingDirectiveSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.UsingDirectiveSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkVariableDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkVariableDeclaratorSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.VariableDeclaratorSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkWhereClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.WhereClauseSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkXmlCDataSectionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.XmlCDataSectionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkXmlCommentSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.XmlCommentSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkXmlCrefAttributeSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.XmlCrefAttributeSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkXmlElementEndTagSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.XmlElementEndTagSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkXmlElementStartTagSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.XmlElementStartTagSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkXmlElementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.XmlElementSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkXmlEmptyElementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.XmlEmptyElementSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkXmlNameAttributeSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.XmlNameAttributeSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkXmlNameSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.XmlNameSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkXmlPrefixSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.XmlPrefixSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkXmlProcessingInstructionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.XmlProcessingInstructionSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkXmlTextAttributeSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.XmlTextAttributeSyntax((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkXmlTextSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.XmlTextSyntax((uint)container.Count, this);
                    break;
                default:
                    throw new CsharpException("Columbus.Csharp.Asg.Factory.createNode()", "Invalid node kind");
            }
        
            if (newNode == null)
                throw new CsharpException("Columbus.Csharp.Asg.Factory.creatNode()", "Node creation failed");
        
            container.Add(newNode);
        
            if (filter.Size < container.Count)
                filter.resizeTo(container.Count);
            filter.set(newNode.Id, Filter.FilterState.NotFiltered);
        
          if (ReverseEdges != null)
            ReverseEdges.insertNode(newNode.Id);
        
            return newNode;
        }

        /// <summary>
        /// Creates a new node, insert it into the container and return with its id.
        /// </summary>
        /// <param name="kind">[in] The kind of the node.</param>
        /// <param name="id">[in] The id of the new node.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">If an invalid (or an abstract) NodeKind is given, CsharpException is thrown.</exception>
        /// <returns>Reference to the new node.</returns>
        private Columbus.Csharp.Asg.Nodes.Base.Base createNode(Types.NodeKind kind, uint id) {
            Columbus.Csharp.Asg.Nodes.Base.Base newNode = null;

            switch (kind) {
                case Types.NodeKind.ndkAliasQualifiedNameSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.AliasQualifiedNameSyntax(id, this);
                    break;
                case Types.NodeKind.ndkAnonymousMethodExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.AnonymousMethodExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkAnonymousObjectCreationExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.AnonymousObjectCreationExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkArrayCreationExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.ArrayCreationExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkArrayTypeSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.ArrayTypeSyntax(id, this);
                    break;
                case Types.NodeKind.ndkAssignmentExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.AssignmentExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkAwaitExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.AwaitExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkBaseExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.BaseExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkBinaryExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.BinaryExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkCastExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.CastExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkCheckedExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.CheckedExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkConditionalAccessExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.ConditionalAccessExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkConditionalExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.ConditionalExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkDefaultExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.DefaultExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkElementAccessExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.ElementAccessExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkElementBindingExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.ElementBindingExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkGenericNameSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.GenericNameSyntax(id, this);
                    break;
                case Types.NodeKind.ndkIdentifierNameSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax(id, this);
                    break;
                case Types.NodeKind.ndkImplicitArrayCreationExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.ImplicitArrayCreationExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkImplicitElementAccessSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.ImplicitElementAccessSyntax(id, this);
                    break;
                case Types.NodeKind.ndkInitializerExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.InitializerExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkInterpolatedStringExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.InterpolatedStringExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkInvocationExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.InvocationExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkLiteralExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.LiteralExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkMakeRefExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.MakeRefExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkMemberAccessExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.MemberAccessExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkMemberBindingExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.MemberBindingExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkNullableTypeSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.NullableTypeSyntax(id, this);
                    break;
                case Types.NodeKind.ndkObjectCreationExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.ObjectCreationExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkOmittedArraySizeExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.OmittedArraySizeExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkOmittedTypeArgumentSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.OmittedTypeArgumentSyntax(id, this);
                    break;
                case Types.NodeKind.ndkParenthesizedExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkParenthesizedLambdaExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedLambdaExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkPointerTypeSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.PointerTypeSyntax(id, this);
                    break;
                case Types.NodeKind.ndkPostfixUnaryExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.PostfixUnaryExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkPredefinedTypeSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.PredefinedTypeSyntax(id, this);
                    break;
                case Types.NodeKind.ndkPrefixUnaryExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.PrefixUnaryExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkQualifiedNameSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.QualifiedNameSyntax(id, this);
                    break;
                case Types.NodeKind.ndkQueryExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.QueryExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkRefTypeExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.RefTypeExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkRefValueExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.RefValueExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkSimpleLambdaExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.SimpleLambdaExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkSizeOfExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.SizeOfExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkStackAllocArrayCreationExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.StackAllocArrayCreationExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkThisExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.ThisExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkTypeOfExpressionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Expression.TypeOfExpressionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkBlockSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax(id, this);
                    break;
                case Types.NodeKind.ndkBreakStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.BreakStatementSyntax(id, this);
                    break;
                case Types.NodeKind.ndkCheckedStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.CheckedStatementSyntax(id, this);
                    break;
                case Types.NodeKind.ndkContinueStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.ContinueStatementSyntax(id, this);
                    break;
                case Types.NodeKind.ndkDoStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.DoStatementSyntax(id, this);
                    break;
                case Types.NodeKind.ndkEmptyStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.EmptyStatementSyntax(id, this);
                    break;
                case Types.NodeKind.ndkExpressionStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.ExpressionStatementSyntax(id, this);
                    break;
                case Types.NodeKind.ndkFixedStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.FixedStatementSyntax(id, this);
                    break;
                case Types.NodeKind.ndkForEachStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.ForEachStatementSyntax(id, this);
                    break;
                case Types.NodeKind.ndkForStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.ForStatementSyntax(id, this);
                    break;
                case Types.NodeKind.ndkGotoStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.GotoStatementSyntax(id, this);
                    break;
                case Types.NodeKind.ndkIfStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.IfStatementSyntax(id, this);
                    break;
                case Types.NodeKind.ndkLabeledStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.LabeledStatementSyntax(id, this);
                    break;
                case Types.NodeKind.ndkLocalDeclarationStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.LocalDeclarationStatementSyntax(id, this);
                    break;
                case Types.NodeKind.ndkLockStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.LockStatementSyntax(id, this);
                    break;
                case Types.NodeKind.ndkReturnStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.ReturnStatementSyntax(id, this);
                    break;
                case Types.NodeKind.ndkSwitchStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.SwitchStatementSyntax(id, this);
                    break;
                case Types.NodeKind.ndkThrowStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.ThrowStatementSyntax(id, this);
                    break;
                case Types.NodeKind.ndkTryStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.TryStatementSyntax(id, this);
                    break;
                case Types.NodeKind.ndkUnsafeStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.UnsafeStatementSyntax(id, this);
                    break;
                case Types.NodeKind.ndkUsingStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.UsingStatementSyntax(id, this);
                    break;
                case Types.NodeKind.ndkWhileStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.WhileStatementSyntax(id, this);
                    break;
                case Types.NodeKind.ndkYieldStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Statement.YieldStatementSyntax(id, this);
                    break;
                case Types.NodeKind.ndkAccessorDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax(id, this);
                    break;
                case Types.NodeKind.ndkAccessorListSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.AccessorListSyntax(id, this);
                    break;
                case Types.NodeKind.ndkAnonymousObjectMemberDeclaratorSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.AnonymousObjectMemberDeclaratorSyntax(id, this);
                    break;
                case Types.NodeKind.ndkArgumentListSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.ArgumentListSyntax(id, this);
                    break;
                case Types.NodeKind.ndkArgumentSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.ArgumentSyntax(id, this);
                    break;
                case Types.NodeKind.ndkArrayRankSpecifierSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.ArrayRankSpecifierSyntax(id, this);
                    break;
                case Types.NodeKind.ndkArrowExpressionClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.ArrowExpressionClauseSyntax(id, this);
                    break;
                case Types.NodeKind.ndkAttributeArgumentListSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentListSyntax(id, this);
                    break;
                case Types.NodeKind.ndkAttributeArgumentSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentSyntax(id, this);
                    break;
                case Types.NodeKind.ndkAttributeListSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax(id, this);
                    break;
                case Types.NodeKind.ndkAttributeSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.AttributeSyntax(id, this);
                    break;
                case Types.NodeKind.ndkAttributeTargetSpecifierSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.AttributeTargetSpecifierSyntax(id, this);
                    break;
                case Types.NodeKind.ndkBaseListSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.BaseListSyntax(id, this);
                    break;
                case Types.NodeKind.ndkBracketedArgumentListSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.BracketedArgumentListSyntax(id, this);
                    break;
                case Types.NodeKind.ndkBracketedParameterListSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.BracketedParameterListSyntax(id, this);
                    break;
                case Types.NodeKind.ndkCaseSwitchLabelSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.CaseSwitchLabelSyntax(id, this);
                    break;
                case Types.NodeKind.ndkCatchClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.CatchClauseSyntax(id, this);
                    break;
                case Types.NodeKind.ndkCatchDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.CatchDeclarationSyntax(id, this);
                    break;
                case Types.NodeKind.ndkCatchFilterClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.CatchFilterClauseSyntax(id, this);
                    break;
                case Types.NodeKind.ndkClassDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.ClassDeclarationSyntax(id, this);
                    break;
                case Types.NodeKind.ndkClassOrStructConstraintSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.ClassOrStructConstraintSyntax(id, this);
                    break;
                case Types.NodeKind.ndkCompilationUnitSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.CompilationUnitSyntax(id, this);
                    break;
                case Types.NodeKind.ndkConstructorConstraintSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.ConstructorConstraintSyntax(id, this);
                    break;
                case Types.NodeKind.ndkConstructorDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.ConstructorDeclarationSyntax(id, this);
                    break;
                case Types.NodeKind.ndkConstructorInitializerSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.ConstructorInitializerSyntax(id, this);
                    break;
                case Types.NodeKind.ndkConversionOperatorDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorDeclarationSyntax(id, this);
                    break;
                case Types.NodeKind.ndkConversionOperatorMemberCrefSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorMemberCrefSyntax(id, this);
                    break;
                case Types.NodeKind.ndkCrefBracketedParameterListSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.CrefBracketedParameterListSyntax(id, this);
                    break;
                case Types.NodeKind.ndkCrefParameterListSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.CrefParameterListSyntax(id, this);
                    break;
                case Types.NodeKind.ndkCrefParameterSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.CrefParameterSyntax(id, this);
                    break;
                case Types.NodeKind.ndkDefaultSwitchLabelSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.DefaultSwitchLabelSyntax(id, this);
                    break;
                case Types.NodeKind.ndkDelegateDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.DelegateDeclarationSyntax(id, this);
                    break;
                case Types.NodeKind.ndkDestructorDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.DestructorDeclarationSyntax(id, this);
                    break;
                case Types.NodeKind.ndkElseClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.ElseClauseSyntax(id, this);
                    break;
                case Types.NodeKind.ndkEnumDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.EnumDeclarationSyntax(id, this);
                    break;
                case Types.NodeKind.ndkEnumMemberDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.EnumMemberDeclarationSyntax(id, this);
                    break;
                case Types.NodeKind.ndkEqualsValueClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.EqualsValueClauseSyntax(id, this);
                    break;
                case Types.NodeKind.ndkEventDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.EventDeclarationSyntax(id, this);
                    break;
                case Types.NodeKind.ndkEventFieldDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.EventFieldDeclarationSyntax(id, this);
                    break;
                case Types.NodeKind.ndkExplicitInterfaceSpecifierSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.ExplicitInterfaceSpecifierSyntax(id, this);
                    break;
                case Types.NodeKind.ndkExternAliasDirectiveSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.ExternAliasDirectiveSyntax(id, this);
                    break;
                case Types.NodeKind.ndkFieldDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.FieldDeclarationSyntax(id, this);
                    break;
                case Types.NodeKind.ndkFinallyClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.FinallyClauseSyntax(id, this);
                    break;
                case Types.NodeKind.ndkFromClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.FromClauseSyntax(id, this);
                    break;
                case Types.NodeKind.ndkGlobalStatementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.GlobalStatementSyntax(id, this);
                    break;
                case Types.NodeKind.ndkGroupClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.GroupClauseSyntax(id, this);
                    break;
                case Types.NodeKind.ndkIncompleteMemberSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.IncompleteMemberSyntax(id, this);
                    break;
                case Types.NodeKind.ndkIndexerDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.IndexerDeclarationSyntax(id, this);
                    break;
                case Types.NodeKind.ndkIndexerMemberCrefSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.IndexerMemberCrefSyntax(id, this);
                    break;
                case Types.NodeKind.ndkInterfaceDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.InterfaceDeclarationSyntax(id, this);
                    break;
                case Types.NodeKind.ndkInterpolatedStringTextSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringTextSyntax(id, this);
                    break;
                case Types.NodeKind.ndkInterpolationAlignmentClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.InterpolationAlignmentClauseSyntax(id, this);
                    break;
                case Types.NodeKind.ndkInterpolationFormatClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.InterpolationFormatClauseSyntax(id, this);
                    break;
                case Types.NodeKind.ndkInterpolationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.InterpolationSyntax(id, this);
                    break;
                case Types.NodeKind.ndkJoinClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.JoinClauseSyntax(id, this);
                    break;
                case Types.NodeKind.ndkJoinIntoClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.JoinIntoClauseSyntax(id, this);
                    break;
                case Types.NodeKind.ndkLetClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.LetClauseSyntax(id, this);
                    break;
                case Types.NodeKind.ndkMethodDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.MethodDeclarationSyntax(id, this);
                    break;
                case Types.NodeKind.ndkNameColonSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.NameColonSyntax(id, this);
                    break;
                case Types.NodeKind.ndkNameEqualsSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.NameEqualsSyntax(id, this);
                    break;
                case Types.NodeKind.ndkNameMemberCrefSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.NameMemberCrefSyntax(id, this);
                    break;
                case Types.NodeKind.ndkNamespaceDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.NamespaceDeclarationSyntax(id, this);
                    break;
                case Types.NodeKind.ndkOperatorDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.OperatorDeclarationSyntax(id, this);
                    break;
                case Types.NodeKind.ndkOperatorMemberCrefSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.OperatorMemberCrefSyntax(id, this);
                    break;
                case Types.NodeKind.ndkOrderByClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.OrderByClauseSyntax(id, this);
                    break;
                case Types.NodeKind.ndkOrderingSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.OrderingSyntax(id, this);
                    break;
                case Types.NodeKind.ndkParameterListSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.ParameterListSyntax(id, this);
                    break;
                case Types.NodeKind.ndkParameterSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.ParameterSyntax(id, this);
                    break;
                case Types.NodeKind.ndkPropertyDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.PropertyDeclarationSyntax(id, this);
                    break;
                case Types.NodeKind.ndkQualifiedCrefSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.QualifiedCrefSyntax(id, this);
                    break;
                case Types.NodeKind.ndkQueryBodySyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.QueryBodySyntax(id, this);
                    break;
                case Types.NodeKind.ndkQueryContinuationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.QueryContinuationSyntax(id, this);
                    break;
                case Types.NodeKind.ndkSelectClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.SelectClauseSyntax(id, this);
                    break;
                case Types.NodeKind.ndkSimpleBaseTypeSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.SimpleBaseTypeSyntax(id, this);
                    break;
                case Types.NodeKind.ndkStructDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.StructDeclarationSyntax(id, this);
                    break;
                case Types.NodeKind.ndkSwitchSectionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.SwitchSectionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkSyntaxToken:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.SyntaxToken(id, this);
                    break;
                case Types.NodeKind.ndkTypeArgumentListSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.TypeArgumentListSyntax(id, this);
                    break;
                case Types.NodeKind.ndkTypeConstraintSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.TypeConstraintSyntax(id, this);
                    break;
                case Types.NodeKind.ndkTypeCrefSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.TypeCrefSyntax(id, this);
                    break;
                case Types.NodeKind.ndkTypeParameterConstraintClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax(id, this);
                    break;
                case Types.NodeKind.ndkTypeParameterListSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.TypeParameterListSyntax(id, this);
                    break;
                case Types.NodeKind.ndkTypeParameterSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.TypeParameterSyntax(id, this);
                    break;
                case Types.NodeKind.ndkUsingDirectiveSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.UsingDirectiveSyntax(id, this);
                    break;
                case Types.NodeKind.ndkVariableDeclarationSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax(id, this);
                    break;
                case Types.NodeKind.ndkVariableDeclaratorSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.VariableDeclaratorSyntax(id, this);
                    break;
                case Types.NodeKind.ndkWhereClauseSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.WhereClauseSyntax(id, this);
                    break;
                case Types.NodeKind.ndkXmlCDataSectionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.XmlCDataSectionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkXmlCommentSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.XmlCommentSyntax(id, this);
                    break;
                case Types.NodeKind.ndkXmlCrefAttributeSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.XmlCrefAttributeSyntax(id, this);
                    break;
                case Types.NodeKind.ndkXmlElementEndTagSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.XmlElementEndTagSyntax(id, this);
                    break;
                case Types.NodeKind.ndkXmlElementStartTagSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.XmlElementStartTagSyntax(id, this);
                    break;
                case Types.NodeKind.ndkXmlElementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.XmlElementSyntax(id, this);
                    break;
                case Types.NodeKind.ndkXmlEmptyElementSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.XmlEmptyElementSyntax(id, this);
                    break;
                case Types.NodeKind.ndkXmlNameAttributeSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.XmlNameAttributeSyntax(id, this);
                    break;
                case Types.NodeKind.ndkXmlNameSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.XmlNameSyntax(id, this);
                    break;
                case Types.NodeKind.ndkXmlPrefixSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.XmlPrefixSyntax(id, this);
                    break;
                case Types.NodeKind.ndkXmlProcessingInstructionSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.XmlProcessingInstructionSyntax(id, this);
                    break;
                case Types.NodeKind.ndkXmlTextAttributeSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.XmlTextAttributeSyntax(id, this);
                    break;
                case Types.NodeKind.ndkXmlTextSyntax:
                    newNode = new Columbus.Csharp.Asg.Nodes.Structure.XmlTextSyntax(id, this);
                    break;
                default:
                    throw new CsharpException("Columbus.Csharp.Asg.Factory.createNode()", "Invalid node kind");
            }
        
            if (newNode == null)
                throw new CsharpException("Columbus.Csharp.Asg.Factory.creatNode()", "Node creation failed");
        
            while (container.Count < (int)id + 1)
                container.Add(null);
        
            container[(int)id] = newNode;
        
            if (filter.Size < container.Count)
                filter.resizeTo(container.Count);
            filter.set(newNode.Id, Filter.FilterState.NotFiltered);
        
          if (ReverseEdges != null)
            ReverseEdges.insertNode(newNode.Id);
        
            return newNode;
        }

        public Columbus.Csharp.Asg.Nodes.Expression.AliasQualifiedNameSyntax createAliasQualifiedNameSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.AliasQualifiedNameSyntax)createNode(Types.NodeKind.ndkAliasQualifiedNameSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.AnonymousMethodExpressionSyntax createAnonymousMethodExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.AnonymousMethodExpressionSyntax)createNode(Types.NodeKind.ndkAnonymousMethodExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.AnonymousObjectCreationExpressionSyntax createAnonymousObjectCreationExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.AnonymousObjectCreationExpressionSyntax)createNode(Types.NodeKind.ndkAnonymousObjectCreationExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.ArrayCreationExpressionSyntax createArrayCreationExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.ArrayCreationExpressionSyntax)createNode(Types.NodeKind.ndkArrayCreationExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.ArrayTypeSyntax createArrayTypeSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.ArrayTypeSyntax)createNode(Types.NodeKind.ndkArrayTypeSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.AssignmentExpressionSyntax createAssignmentExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.AssignmentExpressionSyntax)createNode(Types.NodeKind.ndkAssignmentExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.AwaitExpressionSyntax createAwaitExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.AwaitExpressionSyntax)createNode(Types.NodeKind.ndkAwaitExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.BaseExpressionSyntax createBaseExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.BaseExpressionSyntax)createNode(Types.NodeKind.ndkBaseExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.BinaryExpressionSyntax createBinaryExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.BinaryExpressionSyntax)createNode(Types.NodeKind.ndkBinaryExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.CastExpressionSyntax createCastExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.CastExpressionSyntax)createNode(Types.NodeKind.ndkCastExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.CheckedExpressionSyntax createCheckedExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.CheckedExpressionSyntax)createNode(Types.NodeKind.ndkCheckedExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.ConditionalAccessExpressionSyntax createConditionalAccessExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.ConditionalAccessExpressionSyntax)createNode(Types.NodeKind.ndkConditionalAccessExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.ConditionalExpressionSyntax createConditionalExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.ConditionalExpressionSyntax)createNode(Types.NodeKind.ndkConditionalExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.DefaultExpressionSyntax createDefaultExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.DefaultExpressionSyntax)createNode(Types.NodeKind.ndkDefaultExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.ElementAccessExpressionSyntax createElementAccessExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.ElementAccessExpressionSyntax)createNode(Types.NodeKind.ndkElementAccessExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.ElementBindingExpressionSyntax createElementBindingExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.ElementBindingExpressionSyntax)createNode(Types.NodeKind.ndkElementBindingExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.GenericNameSyntax createGenericNameSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.GenericNameSyntax)createNode(Types.NodeKind.ndkGenericNameSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax createIdentifierNameSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax)createNode(Types.NodeKind.ndkIdentifierNameSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.ImplicitArrayCreationExpressionSyntax createImplicitArrayCreationExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.ImplicitArrayCreationExpressionSyntax)createNode(Types.NodeKind.ndkImplicitArrayCreationExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.ImplicitElementAccessSyntax createImplicitElementAccessSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.ImplicitElementAccessSyntax)createNode(Types.NodeKind.ndkImplicitElementAccessSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.InitializerExpressionSyntax createInitializerExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.InitializerExpressionSyntax)createNode(Types.NodeKind.ndkInitializerExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.InterpolatedStringExpressionSyntax createInterpolatedStringExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.InterpolatedStringExpressionSyntax)createNode(Types.NodeKind.ndkInterpolatedStringExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.InvocationExpressionSyntax createInvocationExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.InvocationExpressionSyntax)createNode(Types.NodeKind.ndkInvocationExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.LiteralExpressionSyntax createLiteralExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.LiteralExpressionSyntax)createNode(Types.NodeKind.ndkLiteralExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.MakeRefExpressionSyntax createMakeRefExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.MakeRefExpressionSyntax)createNode(Types.NodeKind.ndkMakeRefExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.MemberAccessExpressionSyntax createMemberAccessExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.MemberAccessExpressionSyntax)createNode(Types.NodeKind.ndkMemberAccessExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.MemberBindingExpressionSyntax createMemberBindingExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.MemberBindingExpressionSyntax)createNode(Types.NodeKind.ndkMemberBindingExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.NullableTypeSyntax createNullableTypeSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.NullableTypeSyntax)createNode(Types.NodeKind.ndkNullableTypeSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.ObjectCreationExpressionSyntax createObjectCreationExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.ObjectCreationExpressionSyntax)createNode(Types.NodeKind.ndkObjectCreationExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.OmittedArraySizeExpressionSyntax createOmittedArraySizeExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.OmittedArraySizeExpressionSyntax)createNode(Types.NodeKind.ndkOmittedArraySizeExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.OmittedTypeArgumentSyntax createOmittedTypeArgumentSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.OmittedTypeArgumentSyntax)createNode(Types.NodeKind.ndkOmittedTypeArgumentSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedExpressionSyntax createParenthesizedExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedExpressionSyntax)createNode(Types.NodeKind.ndkParenthesizedExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedLambdaExpressionSyntax createParenthesizedLambdaExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedLambdaExpressionSyntax)createNode(Types.NodeKind.ndkParenthesizedLambdaExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.PointerTypeSyntax createPointerTypeSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.PointerTypeSyntax)createNode(Types.NodeKind.ndkPointerTypeSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.PostfixUnaryExpressionSyntax createPostfixUnaryExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.PostfixUnaryExpressionSyntax)createNode(Types.NodeKind.ndkPostfixUnaryExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.PredefinedTypeSyntax createPredefinedTypeSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.PredefinedTypeSyntax)createNode(Types.NodeKind.ndkPredefinedTypeSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.PrefixUnaryExpressionSyntax createPrefixUnaryExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.PrefixUnaryExpressionSyntax)createNode(Types.NodeKind.ndkPrefixUnaryExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.QualifiedNameSyntax createQualifiedNameSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.QualifiedNameSyntax)createNode(Types.NodeKind.ndkQualifiedNameSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.QueryExpressionSyntax createQueryExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.QueryExpressionSyntax)createNode(Types.NodeKind.ndkQueryExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.RefTypeExpressionSyntax createRefTypeExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.RefTypeExpressionSyntax)createNode(Types.NodeKind.ndkRefTypeExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.RefValueExpressionSyntax createRefValueExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.RefValueExpressionSyntax)createNode(Types.NodeKind.ndkRefValueExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.SimpleLambdaExpressionSyntax createSimpleLambdaExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.SimpleLambdaExpressionSyntax)createNode(Types.NodeKind.ndkSimpleLambdaExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.SizeOfExpressionSyntax createSizeOfExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.SizeOfExpressionSyntax)createNode(Types.NodeKind.ndkSizeOfExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.StackAllocArrayCreationExpressionSyntax createStackAllocArrayCreationExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.StackAllocArrayCreationExpressionSyntax)createNode(Types.NodeKind.ndkStackAllocArrayCreationExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.ThisExpressionSyntax createThisExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.ThisExpressionSyntax)createNode(Types.NodeKind.ndkThisExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Expression.TypeOfExpressionSyntax createTypeOfExpressionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Expression.TypeOfExpressionSyntax)createNode(Types.NodeKind.ndkTypeOfExpressionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax createBlockSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax)createNode(Types.NodeKind.ndkBlockSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Statement.BreakStatementSyntax createBreakStatementSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Statement.BreakStatementSyntax)createNode(Types.NodeKind.ndkBreakStatementSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Statement.CheckedStatementSyntax createCheckedStatementSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Statement.CheckedStatementSyntax)createNode(Types.NodeKind.ndkCheckedStatementSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Statement.ContinueStatementSyntax createContinueStatementSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Statement.ContinueStatementSyntax)createNode(Types.NodeKind.ndkContinueStatementSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Statement.DoStatementSyntax createDoStatementSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Statement.DoStatementSyntax)createNode(Types.NodeKind.ndkDoStatementSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Statement.EmptyStatementSyntax createEmptyStatementSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Statement.EmptyStatementSyntax)createNode(Types.NodeKind.ndkEmptyStatementSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Statement.ExpressionStatementSyntax createExpressionStatementSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Statement.ExpressionStatementSyntax)createNode(Types.NodeKind.ndkExpressionStatementSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Statement.FixedStatementSyntax createFixedStatementSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Statement.FixedStatementSyntax)createNode(Types.NodeKind.ndkFixedStatementSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Statement.ForEachStatementSyntax createForEachStatementSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Statement.ForEachStatementSyntax)createNode(Types.NodeKind.ndkForEachStatementSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Statement.ForStatementSyntax createForStatementSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Statement.ForStatementSyntax)createNode(Types.NodeKind.ndkForStatementSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Statement.GotoStatementSyntax createGotoStatementSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Statement.GotoStatementSyntax)createNode(Types.NodeKind.ndkGotoStatementSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Statement.IfStatementSyntax createIfStatementSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Statement.IfStatementSyntax)createNode(Types.NodeKind.ndkIfStatementSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Statement.LabeledStatementSyntax createLabeledStatementSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Statement.LabeledStatementSyntax)createNode(Types.NodeKind.ndkLabeledStatementSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Statement.LocalDeclarationStatementSyntax createLocalDeclarationStatementSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Statement.LocalDeclarationStatementSyntax)createNode(Types.NodeKind.ndkLocalDeclarationStatementSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Statement.LockStatementSyntax createLockStatementSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Statement.LockStatementSyntax)createNode(Types.NodeKind.ndkLockStatementSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Statement.ReturnStatementSyntax createReturnStatementSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Statement.ReturnStatementSyntax)createNode(Types.NodeKind.ndkReturnStatementSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Statement.SwitchStatementSyntax createSwitchStatementSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Statement.SwitchStatementSyntax)createNode(Types.NodeKind.ndkSwitchStatementSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Statement.ThrowStatementSyntax createThrowStatementSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Statement.ThrowStatementSyntax)createNode(Types.NodeKind.ndkThrowStatementSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Statement.TryStatementSyntax createTryStatementSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Statement.TryStatementSyntax)createNode(Types.NodeKind.ndkTryStatementSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Statement.UnsafeStatementSyntax createUnsafeStatementSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Statement.UnsafeStatementSyntax)createNode(Types.NodeKind.ndkUnsafeStatementSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Statement.UsingStatementSyntax createUsingStatementSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Statement.UsingStatementSyntax)createNode(Types.NodeKind.ndkUsingStatementSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Statement.WhileStatementSyntax createWhileStatementSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Statement.WhileStatementSyntax)createNode(Types.NodeKind.ndkWhileStatementSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Statement.YieldStatementSyntax createYieldStatementSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Statement.YieldStatementSyntax)createNode(Types.NodeKind.ndkYieldStatementSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax createAccessorDeclarationSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax)createNode(Types.NodeKind.ndkAccessorDeclarationSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.AccessorListSyntax createAccessorListSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.AccessorListSyntax)createNode(Types.NodeKind.ndkAccessorListSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.AnonymousObjectMemberDeclaratorSyntax createAnonymousObjectMemberDeclaratorSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.AnonymousObjectMemberDeclaratorSyntax)createNode(Types.NodeKind.ndkAnonymousObjectMemberDeclaratorSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.ArgumentListSyntax createArgumentListSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.ArgumentListSyntax)createNode(Types.NodeKind.ndkArgumentListSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.ArgumentSyntax createArgumentSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.ArgumentSyntax)createNode(Types.NodeKind.ndkArgumentSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.ArrayRankSpecifierSyntax createArrayRankSpecifierSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.ArrayRankSpecifierSyntax)createNode(Types.NodeKind.ndkArrayRankSpecifierSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.ArrowExpressionClauseSyntax createArrowExpressionClauseSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.ArrowExpressionClauseSyntax)createNode(Types.NodeKind.ndkArrowExpressionClauseSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentListSyntax createAttributeArgumentListSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentListSyntax)createNode(Types.NodeKind.ndkAttributeArgumentListSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentSyntax createAttributeArgumentSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentSyntax)createNode(Types.NodeKind.ndkAttributeArgumentSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax createAttributeListSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax)createNode(Types.NodeKind.ndkAttributeListSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.AttributeSyntax createAttributeSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.AttributeSyntax)createNode(Types.NodeKind.ndkAttributeSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.AttributeTargetSpecifierSyntax createAttributeTargetSpecifierSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.AttributeTargetSpecifierSyntax)createNode(Types.NodeKind.ndkAttributeTargetSpecifierSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.BaseListSyntax createBaseListSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.BaseListSyntax)createNode(Types.NodeKind.ndkBaseListSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.BracketedArgumentListSyntax createBracketedArgumentListSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.BracketedArgumentListSyntax)createNode(Types.NodeKind.ndkBracketedArgumentListSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.BracketedParameterListSyntax createBracketedParameterListSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.BracketedParameterListSyntax)createNode(Types.NodeKind.ndkBracketedParameterListSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.CaseSwitchLabelSyntax createCaseSwitchLabelSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.CaseSwitchLabelSyntax)createNode(Types.NodeKind.ndkCaseSwitchLabelSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.CatchClauseSyntax createCatchClauseSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.CatchClauseSyntax)createNode(Types.NodeKind.ndkCatchClauseSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.CatchDeclarationSyntax createCatchDeclarationSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.CatchDeclarationSyntax)createNode(Types.NodeKind.ndkCatchDeclarationSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.CatchFilterClauseSyntax createCatchFilterClauseSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.CatchFilterClauseSyntax)createNode(Types.NodeKind.ndkCatchFilterClauseSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.ClassDeclarationSyntax createClassDeclarationSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.ClassDeclarationSyntax)createNode(Types.NodeKind.ndkClassDeclarationSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.ClassOrStructConstraintSyntax createClassOrStructConstraintSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.ClassOrStructConstraintSyntax)createNode(Types.NodeKind.ndkClassOrStructConstraintSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.CompilationUnitSyntax createCompilationUnitSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.CompilationUnitSyntax)createNode(Types.NodeKind.ndkCompilationUnitSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.ConstructorConstraintSyntax createConstructorConstraintSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.ConstructorConstraintSyntax)createNode(Types.NodeKind.ndkConstructorConstraintSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.ConstructorDeclarationSyntax createConstructorDeclarationSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.ConstructorDeclarationSyntax)createNode(Types.NodeKind.ndkConstructorDeclarationSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.ConstructorInitializerSyntax createConstructorInitializerSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.ConstructorInitializerSyntax)createNode(Types.NodeKind.ndkConstructorInitializerSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorDeclarationSyntax createConversionOperatorDeclarationSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorDeclarationSyntax)createNode(Types.NodeKind.ndkConversionOperatorDeclarationSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorMemberCrefSyntax createConversionOperatorMemberCrefSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorMemberCrefSyntax)createNode(Types.NodeKind.ndkConversionOperatorMemberCrefSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.CrefBracketedParameterListSyntax createCrefBracketedParameterListSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.CrefBracketedParameterListSyntax)createNode(Types.NodeKind.ndkCrefBracketedParameterListSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.CrefParameterListSyntax createCrefParameterListSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.CrefParameterListSyntax)createNode(Types.NodeKind.ndkCrefParameterListSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.CrefParameterSyntax createCrefParameterSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.CrefParameterSyntax)createNode(Types.NodeKind.ndkCrefParameterSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.DefaultSwitchLabelSyntax createDefaultSwitchLabelSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.DefaultSwitchLabelSyntax)createNode(Types.NodeKind.ndkDefaultSwitchLabelSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.DelegateDeclarationSyntax createDelegateDeclarationSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.DelegateDeclarationSyntax)createNode(Types.NodeKind.ndkDelegateDeclarationSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.DestructorDeclarationSyntax createDestructorDeclarationSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.DestructorDeclarationSyntax)createNode(Types.NodeKind.ndkDestructorDeclarationSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.ElseClauseSyntax createElseClauseSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.ElseClauseSyntax)createNode(Types.NodeKind.ndkElseClauseSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.EnumDeclarationSyntax createEnumDeclarationSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.EnumDeclarationSyntax)createNode(Types.NodeKind.ndkEnumDeclarationSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.EnumMemberDeclarationSyntax createEnumMemberDeclarationSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.EnumMemberDeclarationSyntax)createNode(Types.NodeKind.ndkEnumMemberDeclarationSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.EqualsValueClauseSyntax createEqualsValueClauseSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.EqualsValueClauseSyntax)createNode(Types.NodeKind.ndkEqualsValueClauseSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.EventDeclarationSyntax createEventDeclarationSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.EventDeclarationSyntax)createNode(Types.NodeKind.ndkEventDeclarationSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.EventFieldDeclarationSyntax createEventFieldDeclarationSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.EventFieldDeclarationSyntax)createNode(Types.NodeKind.ndkEventFieldDeclarationSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.ExplicitInterfaceSpecifierSyntax createExplicitInterfaceSpecifierSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.ExplicitInterfaceSpecifierSyntax)createNode(Types.NodeKind.ndkExplicitInterfaceSpecifierSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.ExternAliasDirectiveSyntax createExternAliasDirectiveSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.ExternAliasDirectiveSyntax)createNode(Types.NodeKind.ndkExternAliasDirectiveSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.FieldDeclarationSyntax createFieldDeclarationSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.FieldDeclarationSyntax)createNode(Types.NodeKind.ndkFieldDeclarationSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.FinallyClauseSyntax createFinallyClauseSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.FinallyClauseSyntax)createNode(Types.NodeKind.ndkFinallyClauseSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.FromClauseSyntax createFromClauseSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.FromClauseSyntax)createNode(Types.NodeKind.ndkFromClauseSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.GlobalStatementSyntax createGlobalStatementSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.GlobalStatementSyntax)createNode(Types.NodeKind.ndkGlobalStatementSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.GroupClauseSyntax createGroupClauseSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.GroupClauseSyntax)createNode(Types.NodeKind.ndkGroupClauseSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.IncompleteMemberSyntax createIncompleteMemberSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.IncompleteMemberSyntax)createNode(Types.NodeKind.ndkIncompleteMemberSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.IndexerDeclarationSyntax createIndexerDeclarationSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.IndexerDeclarationSyntax)createNode(Types.NodeKind.ndkIndexerDeclarationSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.IndexerMemberCrefSyntax createIndexerMemberCrefSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.IndexerMemberCrefSyntax)createNode(Types.NodeKind.ndkIndexerMemberCrefSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.InterfaceDeclarationSyntax createInterfaceDeclarationSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.InterfaceDeclarationSyntax)createNode(Types.NodeKind.ndkInterfaceDeclarationSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringTextSyntax createInterpolatedStringTextSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringTextSyntax)createNode(Types.NodeKind.ndkInterpolatedStringTextSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.InterpolationAlignmentClauseSyntax createInterpolationAlignmentClauseSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.InterpolationAlignmentClauseSyntax)createNode(Types.NodeKind.ndkInterpolationAlignmentClauseSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.InterpolationFormatClauseSyntax createInterpolationFormatClauseSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.InterpolationFormatClauseSyntax)createNode(Types.NodeKind.ndkInterpolationFormatClauseSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.InterpolationSyntax createInterpolationSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.InterpolationSyntax)createNode(Types.NodeKind.ndkInterpolationSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.JoinClauseSyntax createJoinClauseSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.JoinClauseSyntax)createNode(Types.NodeKind.ndkJoinClauseSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.JoinIntoClauseSyntax createJoinIntoClauseSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.JoinIntoClauseSyntax)createNode(Types.NodeKind.ndkJoinIntoClauseSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.LetClauseSyntax createLetClauseSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.LetClauseSyntax)createNode(Types.NodeKind.ndkLetClauseSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.MethodDeclarationSyntax createMethodDeclarationSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.MethodDeclarationSyntax)createNode(Types.NodeKind.ndkMethodDeclarationSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.NameColonSyntax createNameColonSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.NameColonSyntax)createNode(Types.NodeKind.ndkNameColonSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.NameEqualsSyntax createNameEqualsSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.NameEqualsSyntax)createNode(Types.NodeKind.ndkNameEqualsSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.NameMemberCrefSyntax createNameMemberCrefSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.NameMemberCrefSyntax)createNode(Types.NodeKind.ndkNameMemberCrefSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.NamespaceDeclarationSyntax createNamespaceDeclarationSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.NamespaceDeclarationSyntax)createNode(Types.NodeKind.ndkNamespaceDeclarationSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.OperatorDeclarationSyntax createOperatorDeclarationSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.OperatorDeclarationSyntax)createNode(Types.NodeKind.ndkOperatorDeclarationSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.OperatorMemberCrefSyntax createOperatorMemberCrefSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.OperatorMemberCrefSyntax)createNode(Types.NodeKind.ndkOperatorMemberCrefSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.OrderByClauseSyntax createOrderByClauseSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.OrderByClauseSyntax)createNode(Types.NodeKind.ndkOrderByClauseSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.OrderingSyntax createOrderingSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.OrderingSyntax)createNode(Types.NodeKind.ndkOrderingSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.ParameterListSyntax createParameterListSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.ParameterListSyntax)createNode(Types.NodeKind.ndkParameterListSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.ParameterSyntax createParameterSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.ParameterSyntax)createNode(Types.NodeKind.ndkParameterSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.PropertyDeclarationSyntax createPropertyDeclarationSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.PropertyDeclarationSyntax)createNode(Types.NodeKind.ndkPropertyDeclarationSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.QualifiedCrefSyntax createQualifiedCrefSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.QualifiedCrefSyntax)createNode(Types.NodeKind.ndkQualifiedCrefSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.QueryBodySyntax createQueryBodySyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.QueryBodySyntax)createNode(Types.NodeKind.ndkQueryBodySyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.QueryContinuationSyntax createQueryContinuationSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.QueryContinuationSyntax)createNode(Types.NodeKind.ndkQueryContinuationSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.SelectClauseSyntax createSelectClauseSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.SelectClauseSyntax)createNode(Types.NodeKind.ndkSelectClauseSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.SimpleBaseTypeSyntax createSimpleBaseTypeSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.SimpleBaseTypeSyntax)createNode(Types.NodeKind.ndkSimpleBaseTypeSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.StructDeclarationSyntax createStructDeclarationSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.StructDeclarationSyntax)createNode(Types.NodeKind.ndkStructDeclarationSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.SwitchSectionSyntax createSwitchSectionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.SwitchSectionSyntax)createNode(Types.NodeKind.ndkSwitchSectionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.SyntaxToken createSyntaxTokenNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.SyntaxToken)createNode(Types.NodeKind.ndkSyntaxToken);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.TypeArgumentListSyntax createTypeArgumentListSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.TypeArgumentListSyntax)createNode(Types.NodeKind.ndkTypeArgumentListSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.TypeConstraintSyntax createTypeConstraintSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.TypeConstraintSyntax)createNode(Types.NodeKind.ndkTypeConstraintSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.TypeCrefSyntax createTypeCrefSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.TypeCrefSyntax)createNode(Types.NodeKind.ndkTypeCrefSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax createTypeParameterConstraintClauseSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax)createNode(Types.NodeKind.ndkTypeParameterConstraintClauseSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.TypeParameterListSyntax createTypeParameterListSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.TypeParameterListSyntax)createNode(Types.NodeKind.ndkTypeParameterListSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.TypeParameterSyntax createTypeParameterSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.TypeParameterSyntax)createNode(Types.NodeKind.ndkTypeParameterSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.UsingDirectiveSyntax createUsingDirectiveSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.UsingDirectiveSyntax)createNode(Types.NodeKind.ndkUsingDirectiveSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax createVariableDeclarationSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax)createNode(Types.NodeKind.ndkVariableDeclarationSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.VariableDeclaratorSyntax createVariableDeclaratorSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.VariableDeclaratorSyntax)createNode(Types.NodeKind.ndkVariableDeclaratorSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.WhereClauseSyntax createWhereClauseSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.WhereClauseSyntax)createNode(Types.NodeKind.ndkWhereClauseSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.XmlCDataSectionSyntax createXmlCDataSectionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.XmlCDataSectionSyntax)createNode(Types.NodeKind.ndkXmlCDataSectionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.XmlCommentSyntax createXmlCommentSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.XmlCommentSyntax)createNode(Types.NodeKind.ndkXmlCommentSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.XmlCrefAttributeSyntax createXmlCrefAttributeSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.XmlCrefAttributeSyntax)createNode(Types.NodeKind.ndkXmlCrefAttributeSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.XmlElementEndTagSyntax createXmlElementEndTagSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.XmlElementEndTagSyntax)createNode(Types.NodeKind.ndkXmlElementEndTagSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.XmlElementStartTagSyntax createXmlElementStartTagSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.XmlElementStartTagSyntax)createNode(Types.NodeKind.ndkXmlElementStartTagSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.XmlElementSyntax createXmlElementSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.XmlElementSyntax)createNode(Types.NodeKind.ndkXmlElementSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.XmlEmptyElementSyntax createXmlEmptyElementSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.XmlEmptyElementSyntax)createNode(Types.NodeKind.ndkXmlEmptyElementSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.XmlNameAttributeSyntax createXmlNameAttributeSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.XmlNameAttributeSyntax)createNode(Types.NodeKind.ndkXmlNameAttributeSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.XmlNameSyntax createXmlNameSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.XmlNameSyntax)createNode(Types.NodeKind.ndkXmlNameSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.XmlPrefixSyntax createXmlPrefixSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.XmlPrefixSyntax)createNode(Types.NodeKind.ndkXmlPrefixSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.XmlProcessingInstructionSyntax createXmlProcessingInstructionSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.XmlProcessingInstructionSyntax)createNode(Types.NodeKind.ndkXmlProcessingInstructionSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.XmlTextAttributeSyntax createXmlTextAttributeSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.XmlTextAttributeSyntax)createNode(Types.NodeKind.ndkXmlTextAttributeSyntax);
        }

        public Columbus.Csharp.Asg.Nodes.Structure.XmlTextSyntax createXmlTextSyntaxNode(){
            return  (Columbus.Csharp.Asg.Nodes.Structure.XmlTextSyntax)createNode(Types.NodeKind.ndkXmlTextSyntax);
        }

﻿        public ReverseEdges ReverseEdges { get; set; }
		
		public ReverseEdges GetReverseEdges(FuncPtrWithBaseParameterType newSelector = null)
        {
            if (ReverseEdges == null || newSelector != ReverseEdges.selectorFunc)
            {
                if (ReverseEdges != null)
                {
                    ReverseEdges = null;
                    WriteMsg.WriteLine("Debug: Selector function is changed.", WriteMsg.MsgLevel.Debug);
                }
                ReverseEdges = new ReverseEdges(this, newSelector);
            }

            return ReverseEdges;
        }

    }

}
