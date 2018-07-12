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

#ifndef _LIM_ORIGIN_H_
#define _LIM_ORIGIN_H_

#include <csi/inc/HeaderData.h>
#include <io/inc/BinaryIO.h>
#include <map>

/**
 * @file LimOrigin.h
 * @brief Contains the class 'LimOrigin' which stores informations related to nodes and their component id in lim, and lim nodes.
 */
namespace columbus {

  typedef std::map<std::pair<NodeId, NodeId>, NodeId> NodeIdPairToNodeId;
  typedef std::map<NodeId, Key> NodeId2KeyMapType;

  class LimOrigin : public HeaderData {
  public:
    /**
     * @brief Constructor
     */
    LimOrigin();

    /**
     * @brief Destructor
     */
    virtual ~LimOrigin();

    /** 
     * @brief It saves the header into the given file. The file must be opened for writing.
     * @param io [out]   The io::BinaryIO into the header will be written.
     * @throw IOException - if any error happen during the writing. 
     */
    void save(io::BinaryIO &binIo) const;

    /** 
     * @brief It loads back the header from the given file. The file must be opened for reading.
     * @param io [in] The io::BinaryIO from which the header will be read.
     * @throw IOException - if any error happen during the reading. 
     */
    void load(io::BinaryIO &binIo);

    /**
     * @brief It gives back the HeaderData type kind
     * @return the corresponding type kind
     */
    HeaderDataTypeKind getType() const;

    /**
     * @brief Adds component id (in lim) and cpp node id pair, and lim node id.
     */
    bool addCompIdCppIdLimIdToMap(NodeId compId, NodeId cppId, NodeId limId);

    /**
     * @brief Gives back the lim node id if it is set, or 0.
     */
    NodeId getLimIdToCompIdAndCppId(NodeId compId, NodeId cppId) const;

    /**
     * @brief Sets the extra path info to the node.
     */
    bool setExtraPath(NodeId nodeId, Key pathKey);

    /**
     * @brief Gives back the extra path info of the node.
     */
    Key getExtraPath(NodeId nodeId) const;

    /**
     * @brief Returns a string representation of the header data.
     */
    virtual std::string toString() const;

	/**
	 * @brief Returns map of the IDs from previous phase.
	 */
	NodeIdPairToNodeId getCompIdCppId2LimIdMap() const;

  private:
    NodeIdPairToNodeId compIdCppId2LimIdMap;
    NodeId2KeyMapType extraPathMap;
  };

}

#endif