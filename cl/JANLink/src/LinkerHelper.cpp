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

#include <sstream>

#include <common/inc/WriteMessage.h>
#include <java/inc/java.h>
#include "../inc/LinkerHelper.h"
#include "../inc/messages.h"

using namespace std;
using namespace common;
using namespace columbus::java::asg;


namespace columbus { namespace java { namespace linker {

UniqueMap::UniqueMap() :
  nodes(),
  BlockComments(),
  JavadocComments(),
  LineComments(),
  ArrayTypes(),
  BooleanTypes(),
  ByteTypes(),
  CharTypes(),
  ClassTypes(),
  DoubleTypes(),
  ErrorTypes(),
  FloatTypes(),
  IntTypes(),
  LongTypes(),
  LowerBoundedWildcardTypes(),
  MethodTypes(),
  NoTypes(),
  NullTypes(),
  PackageTypes(),
  ParameterizedTypes(),
  ShortTypes(),
  TypeVariables(),
  UnboundedWildcardTypes(),
  UnionTypes(),
  UpperBoundedWildcardTypes(),
  VoidTypes()
{
}

LinkerHelper::LinkerHelper(UniqueMap& strMap, StrNodeIdMap& pathMap)
  : strMap(strMap), pathMap(pathMap), create(0)
{
}

LinkerHelper::~LinkerHelper() {
}

NodeId LinkerHelper::remap(NodeId oldId) {
  return oldId;
}

void LinkerHelper::storeUniqueString(const base::Base& node) {
  string position = getPositionString(node);
  NodeId newId = remap(node.getId());

  if (!getIsNeeded(node)) {
    if (!position.empty() && needToStorePath(node))
      pathMap.insert(make_pair(position, newId));
    return;
  }

  string uniquename = getUniqueString(node);

  StrMultiNodeIdMap::iterator it = strMap.nodes.find(uniquename);
  if (it != strMap.nodes.end()) {
    if (!position.empty()) {//non empty path
      if (!create) {
        StrNodeIdMap::iterator it2 = it->second.find("");
        if (it2 != it->second.end()) {
          it->second.insert(make_pair(position, it2->second));//replacing empty position
          it->second.erase(it2);
          return;
        }
      }
      it->second.insert(make_pair(position, newId));
    } else {//empty path
      if (it->second.empty())
        it->second.insert(make_pair(position, newId));
    }
  } else {//new uniquename
    StrNodeIdMap snim;
    snim[position] = newId;
    strMap.nodes.insert(make_pair(uniquename,snim));
  }
}


bool LinkerHelper::getIsNeeded(const columbus::java::asg::base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
       ndk == ndkCompilationUnit
    || ndk == ndkPackage
    || ndk == ndkTypeParameter
    || (Common::getIsMember(node) && ((ndk != ndkVariable || Common::getIsTypeDeclaration(*node.getParent())) && (ndk != ndkParameter || Common::getIsNormalMethod(*node.getParent()))));
}

bool LinkerHelper::needToStorePath(const columbus::java::asg::base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  base::Base* parent = node.getParent();

  if ((ndk != ndkVariable || (parent && Common::getIsTypeDeclaration(*parent))) &&
      (ndk != ndkParameter || (parent && Common::getIsNormalMethod(*parent)))
  )
    return true;

  return false;
}

std::string LinkerHelper::getPositionString(const columbus::java::asg::base::Base& node, bool withLineInfo /* = false */) {
  if (node.getNodeKind() == ndkPackage) {
    return "[]\t";
  } else if (Common::getIsPositionedWithoutComment(node)) {
    std::stringstream s;
    const Range& r = dynamic_cast<const base::PositionedWithoutComment&>(node).getPosition();
    const string& path = r.getPath();
    if (!path.empty()) {
      if (withLineInfo) {
        s << "[" << r.getWideLine()
          << "," << r.getWideCol()
          << "," << r.getWideEndLine()
          << "," << r.getWideEndCol()
          << "," << path
          << "]\t";
      } else {
        s << "[" << path << "]\t";
      }
      return s.str();
    }
  }
  return "";
}

std::string LinkerHelper::getUniqueString(const columbus::java::asg::base::Base& node) {
  switch (node.getNodeKind()) {
    case ndkCompilationUnit:
      return dynamic_cast<const struc::CompilationUnit&>(node).getPosition().getPath();

    case ndkTypeParameter:
      return Common::getUniqueNameForBase(*node.getParent()) + ".TP~" + dynamic_cast<const base::Named&>(node).getName(); // TODO

    case ndkParameter:
      if (node.getParent() && Common::getIsNormalMethod(*node.getParent())) {
        struc::NormalMethod& meth = dynamic_cast<struc::NormalMethod&>(*node.getParent());
        unsigned int ordinal = 0;
        for (ListIterator<struc::Parameter> it = meth.getParametersListIteratorBegin(); it != meth.getParametersListIteratorEnd(); ++it) {
          ++ordinal;
          if (it->getId() == node.getId())
            break;
        }
        return Common::getUniqueNameForBase(meth) + ".P~" + Common::toString(ordinal);
      }
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_WRONG_PARAMETER_NODE(node.getId()));

    default:
      if (Common::getIsComment(node)) {
        return getPositionString(node, true) + dynamic_cast<const base::Comment&>(node).getText();

      } else if (Common::getIsType(node)) {
        return Common::getUniqueNameForType(dynamic_cast<const type::Type&>(node));

      } else {
        return Common::getUniqueNameForBase(node);
      }
  }
}

}}}

