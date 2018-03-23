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

namespace Columbus.Lim.Asg {

    /// <summary>
    /// Factory, which handles (creates, deletes, sets their properties) nodes.
    /// </summary>
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class Factory {

        /// <summary>Container where the nodes are stored.</summary>
        private List<Columbus.Lim.Asg.Nodes.Base.Base> container;

        /// <summary>Reference to the StingTable.</summary>
        private StrTable strTable;

        /// <summary>The Filter of the ASG.</summary>
        private Filter filter;

        /// <summary>Stores whether the filter is turned on or off.</summary>
        private bool filterOn;

        /// <summary>The id of the root of the ASG.</summary>
        private uint root;

        /// <summary>The language of the ASG.</summary>
        public Types.LanguageKind Language { get; set; }

﻿		private uint rootComponentId;
        private Dictionary<uint, uint> componentNodes;

        /********************* Type Building ********************************/

        /// <summary>Dictionary(Key, NodeId)</summary>
        private Dictionary<uint, uint> typeMap;

        /// <summary>Dictionary(Key, NodeId)</summary>
        private Dictionary<uint, uint> typeFormerTypeMap;

        private Dictionary<Types.SimpleTypeKind, uint> simpleTypeMap;
        private Dictionary<Types.PointerKind, uint> typeFormerPointerMap;
        private uint typeFormerNonTypeMap;
        private uint typeFormerArrayMap;
        private Stack<uint> typeFormers;

        private Dictionary<uint, uint> methodCallNodeIdMap;
        private Dictionary<uint, uint> attributeAccesMap;
        private Dictionary<uint, uint> commentMap;
		
		public ReverseEdges ReverseEdges { get; private set; }        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="strTbl">[in] Reference to the StrTable.</param>
        public Factory(StrTable strTbl) {
            container = new List<Columbus.Lim.Asg.Nodes.Base.Base>();
            strTable = strTbl;
            filterOn = true;
            filter = new Filter(this);
﻿			typeFormers = new Stack<uint>();
            typeMap = new Dictionary<uint, uint>();
            simpleTypeMap = new Dictionary<Types.SimpleTypeKind, uint>();
            typeFormerArrayMap = 0;
            typeFormerTypeMap = new Dictionary<uint, uint>();
            componentNodes = new Dictionary<uint, uint>();
            methodCallNodeIdMap = new Dictionary<uint, uint>();
            typeFormerPointerMap = new Dictionary<Types.PointerKind, uint>();
            attributeAccesMap = new Dictionary<uint, uint>();
            commentMap = new Dictionary<uint, uint>();
            root = ((Columbus.Lim.Asg.Nodes.Logical.Package)createNode(Types.NodeKind.ndkPackage, 100)).Id;
﻿			((Nodes.Logical.Package)container[100]).Name = "global namespace";
            Nodes.Physical.FileSystem f = (Nodes.Physical.FileSystem)createNode(Types.NodeKind.ndkFileSystem, 101);
            f.Name = "FileSystem";
            Nodes.Base.Component cp = (Nodes.Base.Component)createNode(Types.NodeKind.ndkComponent, 102);
            rootComponentId = 102;
            cp.Name = "<System>";        }

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
                    header.add(PropertyData.csih_Type, "LanguageIndependentModel");
                    header.add(PropertyData.csih_APIVersion, Constant.APIVersion);
                    header.add(PropertyData.csih_BinaryVersion, Constant.BinaryVersion);
                    header.add(PropertyData.csih_Language, Convert.ToString((int)Language));
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
                        header.add(PropertyData.csih_Type, "LanguageIndependentModel");
                        header.add(PropertyData.csih_APIVersion, Constant.APIVersion);
                        header.add(PropertyData.csih_BinaryVersion, Constant.BinaryVersion);
                        header.add(PropertyData.csih_Language, Convert.ToString((int)Language));
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
                throw new LimException("Columbus.Lim.Factory.checkPropertyData()", "Missing file type information");
            }
            if (info != "LanguageIndependentModel") {
                throw new LimException("Columbus.Lim.Factory.checkPropertyData()", "Wrong file type information");
            }
            if (!propertyData.get(PropertyData.csih_APIVersion, out info)) {
                throw new LimException("Columbus.Lim.Factory.checkPropertyData()", "Missing API version information");
            }
            if (info != Constant.APIVersion) {
                throw new LimException("Columbus.Lim.Factory.checkPropertyData()", "Wrong API version(" + Constant.APIVersion + " required, " + info + " found)");
            }
            if (!propertyData.get(PropertyData.csih_BinaryVersion, out info)) {
                throw new LimException("Columbus.Lim.Factory.checkPropertyData()", "Missing binary version information");
            }
            if (info != Constant.APIVersion) {
                throw new LimException("Columbus.Lim.Factory.checkPropertyData()", "Wrong API version(" + Constant.BinaryVersion + " required, " + info + " found)");
            }
            if (!propertyData.get(PropertyData.csih_Language, out info)) {
                throw new LimException("Columbus.Lim.Factory.checkPropertyData()", "Missing language information");
            }
            Language = (Types.LanguageKind)int.Parse(info);
        }

        /// <summary>
        /// Loads the graph.
        /// </summary>
        /// <param name="fileName">[in] The graph is loaded from this file.</param>
        /// <param name="header">[in] The header information (also will be loaded).</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if the file can not be opened.</exception>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there's something wrong with the ASG.</exception>
        public void load(string fileName, LinkedList<IHeaderData> headerDataList) {
            container = new List<Columbus.Lim.Asg.Nodes.Base.Base>();
        
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
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the id is greater than the size of the container (greater than the largest id in the graph).</exception>
        /// <returns>Returns true if a node belongs to the id.</returns>
        public bool getExist(uint id) {
            if (container.Count <= id)
                throw new LimException("Columbus.Lim.Asg.Factory.getExist()", "Invalid NodeId (" + id.ToString() + ")");
            return container[(int)id] != null;
        }

        /// <summary>
        /// Gives back a reference to the node.
        /// </summary>
        /// <param name="id">[in] The id of the node.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is no node for the id.</exception>
        /// <returns>Reference to the node.</returns>
        public Columbus.Lim.Asg.Nodes.Base.Base getRef(uint id) {
            Columbus.Lim.Asg.Nodes.Base.Base nodeRef = null;
            if (id < container.Count)
                nodeRef = container[(int)id];
            //if (nodeRef == null)
                //throw new LimException("Columbus.Lim.Asg.Factory.getRef()", "Invalid NodeId (" + id.ToString() + ")");
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
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is no node for the id.</exception>
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
            public Iterator(List<Columbus.Lim.Asg.Nodes.Base.Base> container, Factory factory) {
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
            /// Returns a reference of the next node (Columbus.Lim.Asg.Nodes.Base.Base).
            /// </summary>
            /// <returns>Reference of the next node.</returns>
            /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the next element does not exist.</exception>
            public Columbus.Lim.Asg.Nodes.Base.Base getNext() {
                    while (currentPosition < cont.Count && (cont[currentPosition] == null || fact.getIsFiltered(cont[currentPosition].Id)))
                        ++currentPosition;
                    if (currentPosition >= cont.Count)
                        throw new LimException("Columbus.Lim.Asg.Factory.Iterator.next()", "Next element does not exist");
                    return cont[currentPosition++];
            }

            /// <summary>The Container.</summary>
            private List<Columbus.Lim.Asg.Nodes.Base.Base> cont;

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
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the id is too large (larger than the size of the ASG).</exception>
        /// <returns>Returns true if the Node is filtered and returns false if it isn't (or the filter mode is turned off).</returns>
        public bool getIsFiltered(uint id) {
            return !filterOn ? false : filter.getIsFiltered(id);
        }

        /// <summary>
        /// Filters out the given node and all of its descendants.
        /// </summary>
        /// <param name="id">[in] The id of the node.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException id the id is too large (larger than the size of the Filter).</exception>
        public void setFiltered(uint id) {
            filter.setFiltered(id);
        }

        /// <summary>
        /// Sets the state of the node, all of its descendants and all of its ancestors to not filtered.
        /// </summary>
        /// <param name="id">[in] The id of the node.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException id the id is too large (larger than the size of the Filter).</exception>
        public void setNotFiltered(uint id) {
            filter.setNotFiltered(id);
        }

        /// <summary>
        /// Sets the state of the node and all of its ancestors to not filtered.
        /// </summary>
        /// <param name="id">[in] The id of the node.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException id the id is too large (larger than the size of the Filter).</exception>
        public void setNotFilteredThisNode(uint id) {
            filter.setNotFilteredThisNode(id);
        }

        /// <summary>
        /// Gives back the filter state (lim.Filter.FilterStae) of the given node irrespectively of the state of the filter mode.
        /// </summary>
        /// <param name="id">[in] The id of the node.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the id is too large (larger than the size of the ASG).</exception>
        /// <returns>Returns with the state of the filter.</returns>
        public Filter.FilterState getFilterState(uint id) {
            return filter.getFilterState(id);
        }

        /// <summary>
        /// Loads the filter.
        /// </summary>
        /// <param name="fileName">[in] Then name of the filter file.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the filter contains more (or less) node than the factory does.</exception>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if any error happens during the loading.</exception>
        public void loadFilter(string fileName) {
            IO io = new IO(fileName, System.IO.FileMode.Open);

            if (filter == null)
                filter = new Filter(this);

            if (filter == null)
                throw new LimException("Columbus.Lim.Asg.Factory.loadFilter", "Memory allocation error");

            filter.load(io);

            if (container.Count > filter.Size)
                throw new LimException("Columbus.Lim.Asg.Factory.loadFilter", "The loaded filter does not match to the current ASG");

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
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException id the id is too large (larger than the size of the Filter).</exception>
        public void setFilteredThisNodeOnly(uint id) {
            filter.setFilteredThisNodeOnly(id);
        }

        /// <summary>
        /// Set only the given node to not filtered (without its children).
        /// </summary>
        /// <param name="id">[in] The id of the node.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException id the id is too large (larger than the size of the Filter).</exception>
        public void setNotFilteredThisNodeOnly(uint id) {
            filter.setNotFilteredThisNodeOnly(id);
        }


        // ******************** CreateNode ********************

        /// <summary>
        /// Creates a new node, insert it into the container and return with its id.
        /// </summary>
        /// <param name="kind">[in] The kind of the node.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">If an invalid (or an abstract) NodeKind is given, LimException is thrown.</exception>
        /// <returns>Reference to the new node.</returns>
        public Columbus.Lim.Asg.Nodes.Base.Base createNode(Types.NodeKind kind) {
            Columbus.Lim.Asg.Nodes.Base.Base newNode = null;

            switch (kind) {
                case Types.NodeKind.ndkControlFlowBlock:
                    newNode = new Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkAttribute:
                    newNode = new Columbus.Lim.Asg.Nodes.Logical.Attribute((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkClass:
                    newNode = new Columbus.Lim.Asg.Nodes.Logical.Class((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkClassGeneric:
                    newNode = new Columbus.Lim.Asg.Nodes.Logical.ClassGeneric((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkClassGenericInstance:
                    newNode = new Columbus.Lim.Asg.Nodes.Logical.ClassGenericInstance((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkClassGenericSpec:
                    newNode = new Columbus.Lim.Asg.Nodes.Logical.ClassGenericSpec((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkGenericParameter:
                    newNode = new Columbus.Lim.Asg.Nodes.Logical.GenericParameter((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkMethod:
                    newNode = new Columbus.Lim.Asg.Nodes.Logical.Method((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkMethodGeneric:
                    newNode = new Columbus.Lim.Asg.Nodes.Logical.MethodGeneric((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkMethodGenericInstance:
                    newNode = new Columbus.Lim.Asg.Nodes.Logical.MethodGenericInstance((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkMethodGenericSpec:
                    newNode = new Columbus.Lim.Asg.Nodes.Logical.MethodGenericSpec((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkPackage:
                    newNode = new Columbus.Lim.Asg.Nodes.Logical.Package((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkParameter:
                    newNode = new Columbus.Lim.Asg.Nodes.Logical.Parameter((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkFile:
                    newNode = new Columbus.Lim.Asg.Nodes.Physical.File((uint)container.Count, this);
                    break;
                case Types.NodeKind.ndkFolder:
                    newNode = new Columbus.Lim.Asg.Nodes.Physical.Folder((uint)container.Count, this);
                    break;
                default:
                    throw new LimException("Columbus.Lim.Asg.Factory.createNode()", "Invalid node kind");
            }
        
            if (newNode == null)
                throw new LimException("Columbus.Lim.Asg.Factory.creatNode()", "Node creation failed");
        
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
        /// <exception cref="Columbus.Lim.Asg.LimException">If an invalid (or an abstract) NodeKind is given, LimException is thrown.</exception>
        /// <returns>Reference to the new node.</returns>
        private Columbus.Lim.Asg.Nodes.Base.Base createNode(Types.NodeKind kind, uint id) {
            Columbus.Lim.Asg.Nodes.Base.Base newNode = null;

            switch (kind) {
                case Types.NodeKind.ndkComment:
                    newNode = new Columbus.Lim.Asg.Nodes.Base.Comment(id, this);
                    break;
                case Types.NodeKind.ndkComponent:
                    newNode = new Columbus.Lim.Asg.Nodes.Base.Component(id, this);
                    break;
                case Types.NodeKind.ndkControlFlowBlock:
                    newNode = new Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock(id, this);
                    break;
                case Types.NodeKind.ndkAttribute:
                    newNode = new Columbus.Lim.Asg.Nodes.Logical.Attribute(id, this);
                    break;
                case Types.NodeKind.ndkAttributeAccess:
                    newNode = new Columbus.Lim.Asg.Nodes.Logical.AttributeAccess(id, this);
                    break;
                case Types.NodeKind.ndkClass:
                    newNode = new Columbus.Lim.Asg.Nodes.Logical.Class(id, this);
                    break;
                case Types.NodeKind.ndkClassGeneric:
                    newNode = new Columbus.Lim.Asg.Nodes.Logical.ClassGeneric(id, this);
                    break;
                case Types.NodeKind.ndkClassGenericInstance:
                    newNode = new Columbus.Lim.Asg.Nodes.Logical.ClassGenericInstance(id, this);
                    break;
                case Types.NodeKind.ndkClassGenericSpec:
                    newNode = new Columbus.Lim.Asg.Nodes.Logical.ClassGenericSpec(id, this);
                    break;
                case Types.NodeKind.ndkFriendship:
                    newNode = new Columbus.Lim.Asg.Nodes.Logical.Friendship(id, this);
                    break;
                case Types.NodeKind.ndkGenericParameter:
                    newNode = new Columbus.Lim.Asg.Nodes.Logical.GenericParameter(id, this);
                    break;
                case Types.NodeKind.ndkMethod:
                    newNode = new Columbus.Lim.Asg.Nodes.Logical.Method(id, this);
                    break;
                case Types.NodeKind.ndkMethodCall:
                    newNode = new Columbus.Lim.Asg.Nodes.Logical.MethodCall(id, this);
                    break;
                case Types.NodeKind.ndkMethodGeneric:
                    newNode = new Columbus.Lim.Asg.Nodes.Logical.MethodGeneric(id, this);
                    break;
                case Types.NodeKind.ndkMethodGenericInstance:
                    newNode = new Columbus.Lim.Asg.Nodes.Logical.MethodGenericInstance(id, this);
                    break;
                case Types.NodeKind.ndkMethodGenericSpec:
                    newNode = new Columbus.Lim.Asg.Nodes.Logical.MethodGenericSpec(id, this);
                    break;
                case Types.NodeKind.ndkPackage:
                    newNode = new Columbus.Lim.Asg.Nodes.Logical.Package(id, this);
                    break;
                case Types.NodeKind.ndkParameter:
                    newNode = new Columbus.Lim.Asg.Nodes.Logical.Parameter(id, this);
                    break;
                case Types.NodeKind.ndkFile:
                    newNode = new Columbus.Lim.Asg.Nodes.Physical.File(id, this);
                    break;
                case Types.NodeKind.ndkFileSystem:
                    newNode = new Columbus.Lim.Asg.Nodes.Physical.FileSystem(id, this);
                    break;
                case Types.NodeKind.ndkFolder:
                    newNode = new Columbus.Lim.Asg.Nodes.Physical.Folder(id, this);
                    break;
                case Types.NodeKind.ndkSimpleType:
                    newNode = new Columbus.Lim.Asg.Nodes.Type.SimpleType(id, this);
                    break;
                case Types.NodeKind.ndkType:
                    newNode = new Columbus.Lim.Asg.Nodes.Type.Type(id, this);
                    break;
                case Types.NodeKind.ndkTypeFormerArray:
                    newNode = new Columbus.Lim.Asg.Nodes.Type.TypeFormerArray(id, this);
                    break;
                case Types.NodeKind.ndkTypeFormerMethod:
                    newNode = new Columbus.Lim.Asg.Nodes.Type.TypeFormerMethod(id, this);
                    break;
                case Types.NodeKind.ndkTypeFormerNonType:
                    newNode = new Columbus.Lim.Asg.Nodes.Type.TypeFormerNonType(id, this);
                    break;
                case Types.NodeKind.ndkTypeFormerPointer:
                    newNode = new Columbus.Lim.Asg.Nodes.Type.TypeFormerPointer(id, this);
                    break;
                case Types.NodeKind.ndkTypeFormerType:
                    newNode = new Columbus.Lim.Asg.Nodes.Type.TypeFormerType(id, this);
                    break;
                default:
                    throw new LimException("Columbus.Lim.Asg.Factory.createNode()", "Invalid node kind");
            }
        
            if (newNode == null)
                throw new LimException("Columbus.Lim.Asg.Factory.creatNode()", "Node creation failed");
        
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

        public Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock createControlFlowBlockNode(){
            return  (Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock)createNode(Types.NodeKind.ndkControlFlowBlock);
        }

        public Columbus.Lim.Asg.Nodes.Logical.Attribute createAttributeNode(){
            return  (Columbus.Lim.Asg.Nodes.Logical.Attribute)createNode(Types.NodeKind.ndkAttribute);
        }

        public Columbus.Lim.Asg.Nodes.Logical.Class createClassNode(){
            return  (Columbus.Lim.Asg.Nodes.Logical.Class)createNode(Types.NodeKind.ndkClass);
        }

        public Columbus.Lim.Asg.Nodes.Logical.ClassGeneric createClassGenericNode(){
            return  (Columbus.Lim.Asg.Nodes.Logical.ClassGeneric)createNode(Types.NodeKind.ndkClassGeneric);
        }

        public Columbus.Lim.Asg.Nodes.Logical.ClassGenericInstance createClassGenericInstanceNode(){
            return  (Columbus.Lim.Asg.Nodes.Logical.ClassGenericInstance)createNode(Types.NodeKind.ndkClassGenericInstance);
        }

        public Columbus.Lim.Asg.Nodes.Logical.ClassGenericSpec createClassGenericSpecNode(){
            return  (Columbus.Lim.Asg.Nodes.Logical.ClassGenericSpec)createNode(Types.NodeKind.ndkClassGenericSpec);
        }

        public Columbus.Lim.Asg.Nodes.Logical.GenericParameter createGenericParameterNode(){
            return  (Columbus.Lim.Asg.Nodes.Logical.GenericParameter)createNode(Types.NodeKind.ndkGenericParameter);
        }

        public Columbus.Lim.Asg.Nodes.Logical.Method createMethodNode(){
            return  (Columbus.Lim.Asg.Nodes.Logical.Method)createNode(Types.NodeKind.ndkMethod);
        }

        public Columbus.Lim.Asg.Nodes.Logical.MethodGeneric createMethodGenericNode(){
            return  (Columbus.Lim.Asg.Nodes.Logical.MethodGeneric)createNode(Types.NodeKind.ndkMethodGeneric);
        }

        public Columbus.Lim.Asg.Nodes.Logical.MethodGenericInstance createMethodGenericInstanceNode(){
            return  (Columbus.Lim.Asg.Nodes.Logical.MethodGenericInstance)createNode(Types.NodeKind.ndkMethodGenericInstance);
        }

        public Columbus.Lim.Asg.Nodes.Logical.MethodGenericSpec createMethodGenericSpecNode(){
            return  (Columbus.Lim.Asg.Nodes.Logical.MethodGenericSpec)createNode(Types.NodeKind.ndkMethodGenericSpec);
        }

        public Columbus.Lim.Asg.Nodes.Logical.Package createPackageNode(){
            return  (Columbus.Lim.Asg.Nodes.Logical.Package)createNode(Types.NodeKind.ndkPackage);
        }

        public Columbus.Lim.Asg.Nodes.Logical.Parameter createParameterNode(){
            return  (Columbus.Lim.Asg.Nodes.Logical.Parameter)createNode(Types.NodeKind.ndkParameter);
        }

        public Columbus.Lim.Asg.Nodes.Physical.File createFileNode(){
            return  (Columbus.Lim.Asg.Nodes.Physical.File)createNode(Types.NodeKind.ndkFile);
        }

        public Columbus.Lim.Asg.Nodes.Physical.Folder createFolderNode(){
            return  (Columbus.Lim.Asg.Nodes.Physical.Folder)createNode(Types.NodeKind.ndkFolder);
        }

﻿        public Columbus.Lim.Asg.Nodes.Physical.File createFile(string path)
        {
            return createFile(path, 101);
        }

        public void beginType()
        {
            //typeBuildStack.Push(string.Empty);
        }

        public Nodes.Type.TypeFormerPointer createTypeFormerPointer(Types.PointerKind ptk)
        {
            if (typeFormerPointerMap.ContainsKey(ptk) && typeFormerPointerMap[ptk] > 0) 
				return (Nodes.Type.TypeFormerPointer)getRef(typeFormerPointerMap[ptk]);

            Nodes.Type.TypeFormerPointer newNode = (Nodes.Type.TypeFormerPointer)createNode(Types.NodeKind.ndkTypeFormerPointer, Size);

            newNode.PointerKind = ptk;

            typeFormerPointerMap.Add(ptk, newNode.Id);

            return newNode;
        }

        public void addTypeFormer(uint typeFormer)
        {
            typeFormers.Push(typeFormer);
        }

        public Nodes.Physical.File createFile(string path, int nodeId)
        {
            if (string.IsNullOrEmpty(path))
            {
				StackTrace st = new StackTrace(new StackFrame(true));
				StackFrame sf = st.GetFrame(0);
                throw new LimException(sf.GetFileName() + ":" + sf.GetFileLineNumber(), "Path is null or empty");
            }
            if (!getExist((uint)nodeId))
            {
				StackTrace st = new StackTrace(new StackFrame(true));
				StackFrame sf = st.GetFrame(0);
                throw new LimException(sf.GetFileName() + ":" + sf.GetFileLineNumber(), "Array out of bound exception");
            }
            if (nodeId != 101 && container[101].NodeKind != Types.NodeKind.ndkFolder)
            {
				StackTrace st = new StackTrace(new StackFrame(true));
				StackFrame sf = st.GetFrame(0);
                throw new LimException(sf.GetFileName() + ":" + sf.GetFileLineNumber(), "Invalid NodeKind " + container[101].NodeKind);
            }

            Nodes.Physical.FileSystem fileSystem = null;
            Nodes.Physical.Folder folder = null;
            if (nodeId == 101)
            {
                fileSystem = (Nodes.Physical.FileSystem)container[101];
            }
            else
            {
                folder = (Nodes.Physical.Folder)container[nodeId];
            }

            int pos = 0;
            int lastPos = 0;
            string name = "";
            ListIterator<Nodes.Physical.FSEntry> it = null;
            int found = 0;
            while ((pos = path.IndexOf('\\', pos)) > 0)
            {
                if (lastPos > 0)
                {
                    name = path.Substring(lastPos, pos - lastPos);
                }
                else
                {
                    name = path[0] != '\\' ? path.Substring(0, pos) : "\\";
                }
                if (string.IsNullOrEmpty(name))
                {
					StackTrace st = new StackTrace(new StackFrame(true));
					StackFrame sf = st.GetFrame(0);
                    throw new LimException(sf.GetFileName() + ":" + sf.GetFileLineNumber(), "Empty folder name");
                }
                it = (fileSystem != null) ? fileSystem.HasFSEntryListIteratorBegin : folder.ContainsListIteratorBegin;
                found = 0;
                while (it.getValue() != null)
                {
                    if (found > 0) break;
                    string tmpName = name;
                    if (name != null)
                    {
                        //tmpName = folder.Name + "/" + tmpName;
                    }
                    Nodes.Physical.FSEntry entry = it.getValue();
                    if (entry.NodeKind == Types.NodeKind.ndkFolder && entry.Name == tmpName)
                    {
                        found = (int)it.getValue().Id;
                    }
                    it = it.getNext();
                }
                if (found > 0)
                {
                    fileSystem = null;
                    folder = (Nodes.Physical.Folder)container[found];
                }
                else
                {
                    Nodes.Physical.Folder newFolder = (Nodes.Physical.Folder)createNode(Types.NodeKind.ndkFolder, Size);
                    newFolder.Name = name;
                    if (fileSystem != null)
                    {
                        fileSystem.addHasFSEntry(newFolder);
                        fileSystem = null;
                    }
                    else
                    {
                        folder.addContains(newFolder);
                    }
                    folder = newFolder;
                }

                pos++;
                lastPos = pos;
            }

            name = "";
            if (lastPos != 0)
            {
                name = path.Substring(lastPos);
            }
            if (string.IsNullOrEmpty(name))
            {
				StackTrace st = new StackTrace(new StackFrame(true));
				StackFrame sf = st.GetFrame(0);
                throw new LimException(sf.GetFileName() + ":" + sf.GetFileLineNumber(), "Empty folder name");
            }
            it = (fileSystem != null) ? fileSystem.HasFSEntryListIteratorBegin : folder.ContainsListIteratorBegin;
            found = 0;
            while(it.getValue() != null)
            {
                if (found > 0) break;
                string tmpName = name;
                if (name != null)
                {
                    //tmpName = folder.Name + "/" + tmpName;
                }
                Nodes.Physical.FSEntry entry = it.getValue();
                if (entry.NodeKind == Types.NodeKind.ndkFile && entry.Name == tmpName)
                {
                    found = (int)it.getValue().Id;
                }
                it = it.getNext();
            }

            if (found > 0)
            {
                return (Nodes.Physical.File)container[found];
            }

            Nodes.Physical.File file = (Nodes.Physical.File)createNode(Types.NodeKind.ndkFile, Size);
            file.Name = name;
            if (fileSystem != null)
            {
                fileSystem.addHasFSEntry(file);
            }
            else
            {
                folder.addContains(file);
            }

            return file;
        }

        public Nodes.Base.Base replaceNode(Nodes.Base.Base node)
        {
            Nodes.Base.Base p = null;
            if (node.NodeKind == Types.NodeKind.ndkClass)
            {
                p = new Nodes.Logical.ClassGeneric(node.Id, this);
                p = node;
            }
            else if (node.NodeKind == Types.NodeKind.ndkMember)
            {
                p = new Nodes.Logical.MethodGeneric(node.Id, this);
                p = node;
            }

            container[(int)node.Id] = p;

            return p;
        }

        public Nodes.Type.TypeFormerArray createTypeFormerArray()
        {
            if (typeFormerArrayMap > 0)
            {
                return (Nodes.Type.TypeFormerArray)getRef(typeFormerArrayMap);
            }

            Nodes.Type.TypeFormerArray newNode = (Nodes.Type.TypeFormerArray)createNode(Types.NodeKind.ndkTypeFormerArray, Size);

            typeFormerArrayMap = newNode.Id;

            return newNode;
        }

        public Nodes.Type.TypeFormerNonType createTypeFormerNonType()
        {
            if (typeFormerNonTypeMap > 0)
            {
                return (Nodes.Type.TypeFormerNonType)getRef(typeFormerNonTypeMap);
            }

            Nodes.Type.TypeFormerNonType newNode = (Nodes.Type.TypeFormerNonType)createNode(Types.NodeKind.ndkTypeFormerNonType, Size);

            typeFormerNonTypeMap = newNode.Id;

            return newNode;
        }

        public Nodes.Type.TypeFormerType createTypeFormerType(uint refersToId)
        {
            if (typeFormerTypeMap.ContainsKey(refersToId) && typeFormerTypeMap[refersToId] > 0) 
				return (Nodes.Type.TypeFormerType)getRef(typeFormerTypeMap[refersToId]);

            Nodes.Type.TypeFormerType newNode = (Nodes.Type.TypeFormerType)createNode(Types.NodeKind.ndkTypeFormerType, Size);

            if (refersToId > 0) newNode.setRefersTo(refersToId);

            typeFormerTypeMap.Add(refersToId, newNode.Id);

            return newNode;
        }

        public Nodes.Type.SimpleType createSimpleType(Types.SimpleTypeKind stk)
        {
            if (simpleTypeMap.ContainsKey(stk) && simpleTypeMap[stk]  > 0)
                return (Nodes.Type.SimpleType)getRef(simpleTypeMap[stk]);

            Nodes.Type.SimpleType newNode = (Nodes.Type.SimpleType)createNode(Types.NodeKind.ndkSimpleType, Size);

            newNode.SimpleTypeKind = stk;

            simpleTypeMap.Add(stk, newNode.Id);

            return newNode;
        }

        public Nodes.Logical.AttributeAccess createAttributeAccessNode(uint attributId)
        {
            if (attributeAccesMap.ContainsKey(attributId) && attributeAccesMap[attributId] > 0) 
				return (Nodes.Logical.AttributeAccess)getRef(attributeAccesMap[attributId]);

            Nodes.Logical.AttributeAccess newNode = (Nodes.Logical.AttributeAccess)createNode(Types.NodeKind.ndkAttributeAccess, Size);

            if (attributId > 0) newNode.setAttribute(attributId);

            attributeAccesMap.Add(attributId, newNode.Id);

            return newNode;
        }

        public Nodes.Base.Comment createCommentNode(string text)
        {
            uint key = StringTable.set(text);
            if (commentMap.ContainsKey(key) && commentMap[key] > 0)
            {
                if (getExist(commentMap[key]))
                {
                    Nodes.Base.Base n = getRef(commentMap[key]);
                    if (n.NodeKind == Types.NodeKind.ndkComment && (n as Nodes.Base.Comment).TextKey == key)
                        return n as Nodes.Base.Comment;
                }
            }

            Nodes.Base.Comment newNode = createNode(Types.NodeKind.ndkComment, Size) as Nodes.Base.Comment;
            newNode.TextKey = key;
            commentMap.Add(key, newNode.Id);

            return newNode;
        }

        public uint ComponentRoot
        {
            get
            {
                if (!getExist(rootComponentId))
                {
					StackTrace st = new StackTrace(new StackFrame(true));
					StackFrame sf = st.GetFrame(0);
                    throw new LimException(sf.GetFileName() + ":" + sf.GetFileLineNumber(), "Missing Component root node.");
                }
                return rootComponentId;
            }
        }

        public Nodes.Logical.MethodCall createMethodCall(uint methodId)
        {
            if (methodCallNodeIdMap.ContainsKey(methodId) && methodCallNodeIdMap[methodId] > 0) 
				return (Nodes.Logical.MethodCall)getRef(methodCallNodeIdMap[methodId]);

            Nodes.Logical.MethodCall newNode = (Nodes.Logical.MethodCall)createNode(Types.NodeKind.ndkMethodCall, Size);

            if (methodId > 0)
                newNode.setMethod(methodId);

            methodCallNodeIdMap.Add(methodId, newNode.Id);

            return newNode;
        }

        public Nodes.Base.Component ComponentRootRef
        {
            get
            {
                if (!getExist(rootComponentId))
                {
					StackTrace st = new StackTrace(new StackFrame(true));
					StackFrame sf = st.GetFrame(0);
                    throw new LimException(sf.GetFileName() + ":" + sf.GetFileLineNumber(), "Missing Component root node.");
                }
                return (Nodes.Base.Component)getRef(rootComponentId);
            }
        }

        public Nodes.Base.Component createComponent(string name)
        {
            uint nameKey = StringTable.set(name);
            if (componentNodes.ContainsKey(nameKey) && componentNodes[nameKey] > 0)
            {
                if (getExist(componentNodes[nameKey]))
                {
                    Nodes.Base.Base n = getRef(componentNodes[nameKey]);
                    if (n.NodeKind == Types.NodeKind.ndkComponent && ((Nodes.Base.Component)n).NameKey == nameKey)
                    {
                        return (Nodes.Base.Component)n;
                    }
                }
            }

            Nodes.Base.Component component = (Nodes.Base.Component)createNode(Types.NodeKind.ndkComponent, Size);
            component.NameKey = nameKey;
            componentNodes.Add(nameKey, component.Id);

            return component;
        }

        public Nodes.Type.Type endType()
        {
            if (typeFormers.Count <= 0) {
				StackTrace st = new StackTrace(new StackFrame(true));
				StackFrame sf = st.GetFrame(0);
				throw new LimException(sf.GetFileName() + ":" + sf.GetFileLineNumber(), "Stack is empty");
			}

            uint key = StringTable.set("[" + string.Join(",", typeFormers) + "]");

            if (typeMap.ContainsKey(key))
            {
                uint find = typeMap[key];
                if (find > 0)
                {
                    while (typeFormers.Count > 0)
                    {
                        typeFormers.Pop();
                    }
                    return (Nodes.Type.Type)getRef(find);
                }
            }

            Nodes.Type.Type newNode = (Nodes.Type.Type)createNode(Types.NodeKind.ndkType, Size);

            while (typeFormers.Count > 0)
            {
                newNode.addHasTypeFormer((Nodes.Type.TypeFormer)getRef(typeFormers.Pop()));
            }

            typeMap.Add(key, newNode.Id);

            return newNode;
        }

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
        }    }

}
