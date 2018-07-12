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
#include "java/inc/messages.h"
#include "common/inc/WriteMessage.h"

namespace columbus { namespace java { namespace asg {

using namespace base;
using namespace struc;
using namespace type;
using namespace statm;
using namespace expr;

class CreatesVisitor : public VisitorAbstractNodes
{
protected:
  typedef std::set<NodeId>     Creates;
  typedef std::map<NodeId, Creates>  Container;

public:
  CreatesVisitor(Factory* fact, Container* createsCont) 
    : VisitorAbstractNodes(),
      factory(fact),
      createsCont(createsCont),
      arguments() 
  {}
  
  virtual void visit(const expr::NewClass& node, bool callFirst){
        common::WriteMsg::write(CMSG_CFG_ALG_CREATE_NEWCLASS, node.getId());  
        ClassType* ct = NULL;
        TypeExpression* typeName = node.getTypeName();
        
        if(Common::getIsSimpleTypeExpression(*typeName)) { // NodeKind::ndkSimpleTypeExpression;
            ct = dynamic_cast<ClassType*> (node.getType());
        } else if(Common::getIsTypeApplyExpression(*typeName)) {// NodeKind::ndkTypeApplyExpression;
            TypeApplyExpression *tae = dynamic_cast<TypeApplyExpression*> (typeName);
            if(tae || tae->getRawType()) {
                ct = dynamic_cast<ClassType*> (tae->getRawType()->getType());
            }
        } else {
			return;
        }
        
		if(!ct || !ct->getRefersTo()) {
            return;
        }
        
        Container::iterator iter = createsCont->find(ct->getRefersTo()->getId());
        if (iter != createsCont->end()) {
            iter->second.insert(node.getId());
        } else {
            Creates tmp;
            tmp.insert(node.getId());
            createsCont->insert(std::make_pair(ct->getRefersTo()->getId(), tmp));
        }
  }

  bool exist(NodeId i)  {return i && i!=1;}
protected:
  Factory    *factory;
  Container  *createsCont;
  NodeId     arguments;
private:
    CreatesVisitor(const CreatesVisitor&);
    CreatesVisitor& operator=(const CreatesVisitor&);
};

void AlgorithmCreates::run(Factory& fact) {
  factory = &fact;
  createsCont.clear();
  AlgorithmPreorder ap;
  ap.setVisitSpecialNodes(false, false);
  CreatesVisitor v(&fact, &createsCont);
  ap.run(fact,v);
}

// --- ConstIterator ----------------------------------------------------------

AlgorithmCreates::ConstIterator::ConstIterator(const Container* cont, const Factory* fact, NodeId node) 
    : createsCont(cont),
      factory(fact),
      i(),
      j()
{
  i = createsCont->find(node);
  if(i != createsCont->end()) j = i->second.begin();
}

bool AlgorithmCreates::ConstIterator::hasNext() const {
  return i != createsCont->end() && j != i->second.end();
}

const NodeId AlgorithmCreates::ConstIterator::next() {
  if (i == createsCont->end() || j == i->second.end()) throw Exception(COLUMBUS_LOCATION, CMSG_EX_ALG_CREATES_NEXT_ELEMENT_DOES_NOT_EXIST);
  return *j++;
}

}}}
