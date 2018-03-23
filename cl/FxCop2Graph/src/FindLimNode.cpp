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

#include "../inc/FindLimNode.h"


FindLimNode::FindLimNode(const std::string& mangleName, const columbus::lim::asg::Factory& limfact) : mangleName(mangleName), foundNode(NULL) {
    columbus::lim::asg::AlgorithmPreorder ap;
    ap.setVisitSpecialNodes(true, false);
    ap.setSafeMode();
    ap.run(limfact, *this);
}

const columbus::lim::asg::logical::Member* FindLimNode::getLimNode() {
    return foundNode;
}

void FindLimNode::set(const columbus::lim::asg::logical::Member& node)  {
    if (node.getMangledName() == mangleName) {
        foundNode = &node;
    }
}

void FindLimNode::visit(const columbus::lim::asg::logical::MethodGeneric& node, bool callVirtualBase) {
    set(node);
}

void FindLimNode::visit(const columbus::lim::asg::logical::Method& node, bool callVirtualBase) {
    set(node);
}

void FindLimNode::visit(const columbus::lim::asg::logical::Attribute& node, bool callVirtualBase) {
    set(node);
}

void FindLimNode::visit(const columbus::lim::asg::logical::Class& node, bool callVirtualBase) {
    set(node);
}

void FindLimNode::visit(const columbus::lim::asg::logical::ClassGeneric& node, bool callVirtualBase) {
    set(node);
}

void FindLimNode::visit(const columbus::lim::asg::logical::Package& node, bool callVirtualBase) {
    set(node);
}