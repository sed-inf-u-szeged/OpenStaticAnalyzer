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

#ifndef DCF_NAMED_VISITOR_H
#define DCF_NAMED_VISITOR_H

class NamedVisitor : public VisitorAbstractNodes {
protected:
  std::string repr;
public:
  NamedVisitor() : repr("") {}
  virtual void visit(const Base& node, bool callVirtualBase = true) {
#if defined SCHEMA_PYTHON
    std::string name;
    if (node.getParent() != NULL ) {
      name = AlgorithmCommon::getUniqueName(node);
    }
    if (!name.empty()) {
      repr+=std::string("(")+name;
    }
#endif
    repr+=std::string("#")+common::toString(node.getNodeKind());
  }
  virtual void visitEnd(const Base& node, bool callVirtualBase = true) {
#if defined SCHEMA_PYTHON
    std::string name = AlgorithmCommon::getUniqueName(node);
    if (!name.empty()) {
      repr+=std::string(")");
    }
#endif
    repr+="$";
  }
  virtual void visit(const Named& node, bool callVirtualBase = true) {
    visit((Base&)node);
    repr+=std::string("(")+node.getName();
  }
  virtual void visitEnd(const Named& node, bool callVirtualBase = true) {
    repr+=std::string(")");
    visitEnd((Base&)node);
  }
  operator std::string() {return repr;}
};

#endif
