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

#ifndef _LIM_METHOD_OVERRIDE_H_
#define _LIM_METHOD_OVERRIDE_H_

#include <csi/inc/HeaderData.h>
#include <io/inc/BinaryIO.h>

namespace columbus { namespace lim { namespace asg {

using namespace logical;

class OverrideRelations : public HeaderData {

public:
    typedef std::list<NodeId> IdList;

private:
    typedef struct {
      enum {
        single,
        multi
      } flag;
      union {
        NodeId id;
        IdList *list;
      } OverrideUnion;
    } OverrideStruct;

    typedef std::map<const NodeId, OverrideStruct> OverrideContainer;

    OverrideContainer _overrides;

    const Factory &_factory;

public:

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

    void _addOverride(const NodeId, const NodeId);
    void _addOverride(const Method&, const Method&);

    const bool getIsOverride(const NodeId);
    const NodeId getOverride(const NodeId);
    IdList getOverrideList(const NodeId);
    const int getNumberOfOverrides(const NodeId);

    OverrideRelations(const Factory&);
    ~OverrideRelations();

    /**
     * @brief Returns a string representation of the header data.
     */
    virtual std::string toString() const;

};

}}}

#endif /* _LIM_METHOD_OVERRIDE_H_ */
