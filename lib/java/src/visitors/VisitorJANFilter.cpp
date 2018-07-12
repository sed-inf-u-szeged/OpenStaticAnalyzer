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

#include "java/inc/java.h"
#include <common/inc/StringSup.h>

using namespace std;
using namespace common;

namespace columbus { namespace java { namespace asg {

  JANFilter::JANFilter(Factory &factory, DirectoryFilter& filter, const bool filterRefl) :
    VisitorAbstractNodes(),
    fact(factory),
    filter(filter),
    filterRefl(filterRefl),
    visitedNodes(fact.size(), false)
  {
  }


  JANFilter::~JANFilter() {
  }

  void JANFilter::finishVisit() {
    Factory::ConstIterator it = fact.constIterator();
    while (it.hasNext()) {

      NodeId i = it.next().getId();
      if (!visitedNodes[i])
        fact.setFiltered(i);

    }
  }
  
  void JANFilter::visit(const base::Base& node, bool callVirtualBase) {
    visitedNodes[node.getId()] = true;
  }

  void JANFilter::visit(const struc::Member& node, bool callVirtualBase) {
    VisitorAbstractNodes::visit(node, callVirtualBase);

    if (node.getNodeKind() == ndkPackage) {

      // nothing to do, packages are filtered in the visitEnd method

    } else {

      if (!keepTheNode(node))
        fact.setFiltered(node.getId());

    }

  }


  void JANFilter::visit(const struc::CompilationUnit& node, bool callVirtualBase) {
    VisitorAbstractNodes::visit(node, callVirtualBase);

    if (!keepTheNode(node))
      fact.setFiltered(node.getId());

  }


  void JANFilter::visit(const base::Comment& node, bool callVirtualBase) {
    VisitorAbstractNodes::visit(node, callVirtualBase);

    if (!keepTheNode(node))
      fact.setFiltered(node.getId());

  }


  void JANFilter::visitEnd(const struc::Package& node, bool callVirtualBase) {
    VisitorAbstractNodes::visitEnd(node, callVirtualBase);

    if (&node == fact.getRoot())
      return;

    // if it has neither member nor compilation unit, it is filtered out
    if (node.getMembersIsEmpty() && node.getCompilationUnitsIsEmpty())
      fact.setFiltered(node.getId());

  }


  bool JANFilter::keepTheNode(const base::Base& node) const {

    string path = "";

    if (Common::getIsPositionedWithoutComment(node)) {
      path = dynamic_cast<const base::PositionedWithoutComment&>(node).getPosition().getPath();
    } else {
      return true;
    }

    LowerStringOnWindows(path);

    if (Common::getIsPositioned(node) && dynamic_cast<const base::Positioned&>(node).getIsCompilerGenerated()) { // e.g. generated constructor
      return true;
    }

    if (filter.isFilteredOut(path)){
      return false;
    }

    if (filterRefl) {
      return !path.empty(); // with reflection nodes have no position
    }

    return true;

  }

}}}
