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

#ifndef _JAVA_LINKERHELPER_H_
#define _JAVA_LINKERHELPER_H_

#include <java/inc/java.h>


namespace columbus { namespace java { namespace linker {

  typedef std::map<std::string, NodeId> StrNodeIdMap;
  typedef std::map<std::string, StrNodeIdMap> StrMultiNodeIdMap;

  struct UniqueMap {
    UniqueMap();

    StrMultiNodeIdMap nodes;
    StrNodeIdMap BlockComments;
    StrNodeIdMap JavadocComments;
    StrNodeIdMap LineComments;
    StrNodeIdMap ArrayTypes;
    StrNodeIdMap BooleanTypes;
    StrNodeIdMap ByteTypes;
    StrNodeIdMap CharTypes;
    StrNodeIdMap ClassTypes;
    StrNodeIdMap DoubleTypes;
    StrNodeIdMap ErrorTypes;
    StrNodeIdMap FloatTypes;
    StrNodeIdMap IntTypes;
    StrNodeIdMap LongTypes;
    StrNodeIdMap LowerBoundedWildcardTypes;
    StrNodeIdMap MethodTypes;
    StrNodeIdMap NoTypes;
    StrNodeIdMap NullTypes;
    StrNodeIdMap PackageTypes;
    StrNodeIdMap ParameterizedTypes;
    StrNodeIdMap ShortTypes;
    StrNodeIdMap TypeVariables;
    StrNodeIdMap UnboundedWildcardTypes;
    StrNodeIdMap UnionTypes;
    StrNodeIdMap UpperBoundedWildcardTypes;
    StrNodeIdMap VoidTypes;
  };

  class LinkerHelper {

    public:

      LinkerHelper(UniqueMap& strMap, StrNodeIdMap& pathMap);

      virtual ~LinkerHelper();

    protected:

      virtual NodeId remap(NodeId oldId);
      void storeUniqueString(const columbus::java::asg::base::Base& node);
      bool getIsNeeded(const columbus::java::asg::base::Base& node);
      bool needToStorePath(const columbus::java::asg::base::Base& node);
      std::string getPositionString(const columbus::java::asg::base::Base& node, bool withLineInfo = false);
      std::string getUniqueString(const columbus::java::asg::base::Base& node);

    protected:

      UniqueMap& strMap;
      StrNodeIdMap& pathMap;
      NodeId create;
  };

}}}

#endif

