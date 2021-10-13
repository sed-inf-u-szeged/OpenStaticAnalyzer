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

#include "../inc/VisitorType.h"
#include "../inc/VisitorImport.h"
#include <common/inc/WriteMessage.h>
#include "../inc/messages.h"

using namespace common;
using namespace columbus;
using namespace std;

std::map< NodeId, std::set<NodeId> > VisitorType::type_set;

void VisitorType::setType(module::Object& obj, type::Type& type) {
  std::map< NodeId, std::set<NodeId> >::iterator it = type_set.find(obj.getId());
  
  if(it == type_set.end()){
    std::set<NodeId> node_set;
    bool new_type = true;
    for (python::asg::ListIterator<type::Type> lit = obj.getTypeListIteratorBegin(), litEnd = obj.getTypeListIteratorEnd(); lit != litEnd; ++lit) {
      NodeId type_id = lit->getId();
      if(type.getId() == type_id) new_type = false;
      node_set.insert(type_id);
    }
    if(new_type){
      node_set.insert(type.getId());
      obj.addType(&type);
    }
    type_set[obj.getId()] = node_set;
  }else{
    std::set<NodeId>::iterator type_it = (*it).second.find(type.getId());
    if(type_it == (*it).second.end()){
      (*it).second.insert(type.getId());
      obj.addType(&type);
    }
  }
}

void VisitorType::setType(expression::Expression& obj, type::Type& type) {
  if(obj.getType())
    throw PythonException(COLUMBUS_LOCATION, CMSG_EX_REDEFINITION(Common::toString(obj.getId())));
  obj.setType(&type);
}

NodeId VisitorType::findObject(const std::string& name, ListIterator<module::Object> lit, ListIterator<module::Object> litEnd) {
  NodeId object = 0;
  for (; lit != litEnd; ++lit){
    const module::Object& obj = *lit;
    if (obj.getName().compare(name) == 0) {
      object = obj.getId();
      break;
    }
  }
  return object;
}

NodeId VisitorType::getObject(base::Base& current_scope, std::string name, bool create_object){
  NodeId object = 0;
  NodeKind scope_kind = current_scope.getNodeKind();

  if(scope_kind == ndkModule || scope_kind == ndkFunctionDef || scope_kind == ndkClassDef || scope_kind == ndkLambda ){
    switch(scope_kind){
      case ndkModule:
        object = findObject(name, dynamic_cast<module::Module&>(current_scope).getObjectListIteratorBegin(), dynamic_cast<module::Module&>(current_scope).getObjectListIteratorEnd());
        break;
      case ndkFunctionDef:
        object = findObject(name, dynamic_cast<statement::FunctionDef&>(current_scope).getObjectListIteratorBegin(), dynamic_cast<statement::FunctionDef&>(current_scope).getObjectListIteratorEnd());
        break;
      case ndkClassDef:
        object = findObject(name, dynamic_cast<statement::ClassDef&>(current_scope).getObjectListIteratorBegin(), dynamic_cast<statement::ClassDef&>(current_scope).getObjectListIteratorEnd());
        break;
      case ndkLambda:
        object = findObject(name, dynamic_cast<expression::Lambda&>(current_scope).getObjectListIteratorBegin(), dynamic_cast<expression::Lambda&>(current_scope).getObjectListIteratorEnd());
        break;
      default:
        break;
    }

    if(object == 0 && create_object){
      module::Object* obj = dynamic_cast<module::Object*>(factory->createNode(ndkObject));
      obj->setName(name);
      switch(scope_kind){
        case ndkModule:
          dynamic_cast<module::Module&>(current_scope).addObject(obj);
          break;
        case ndkFunctionDef:
          dynamic_cast<statement::FunctionDef&>(current_scope).addObject(obj);
          break;
        case ndkClassDef:
          dynamic_cast<statement::ClassDef&>(current_scope).addObject(obj);
          break;
        case ndkLambda:
          dynamic_cast<expression::Lambda&>(current_scope).addObject(obj);
          break;
        default:
          break;
      } 
      object = obj->getId();
    }
  }
  return object;
}

NodeId VisitorType::findObject(base::Base& base_scope, std::string name, bool top_level_only) {
  NodeId object = getObject(base_scope, name);
  
  if (object == 0) {
    NodeKind base_ndk = base_scope.getNodeKind();
    if (base_ndk == ndkClassDef) {
      ListIterator<statement::BaseSpecifier> spec = dynamic_cast<statement::ClassDef&>(base_scope).getBaseSpecifierListIteratorBegin();
      ListIterator<statement::BaseSpecifier> specEnd = dynamic_cast<statement::ClassDef&>(base_scope).getBaseSpecifierListIteratorEnd();
      for (; spec != specEnd; ++spec) {
         if (spec->getDerivesFrom()) {
          object = getObject(*spec->getDerivesFrom(), name);
          if (object != 0) {
            break;
          }
        }
      }
      if (object == 0 && !top_level_only) {
        base::Base* curr_scope = base_scope.getParent();
        if (curr_scope) {
          object = findObject(*curr_scope, name);
        }
      }
    } else if (base_ndk != ndkModule) {
      base::Base* curr_scope = base_scope.getParent();
      if (curr_scope) {
        NodeKind ndk = curr_scope->getNodeKind();
        while (ndk != ndkFunctionDef && ndk != ndkModule && ndk != ndkLambda) {
          curr_scope = curr_scope->getParent();
          if (curr_scope) {
            ndk = curr_scope->getNodeKind();
          } else {
            break;
          }
        }
      }
      if (curr_scope) {
        object = findObject(*curr_scope, name);
      }
    }
  }
  return object;
}

void VisitorType::ListAssign(expression::List& target, expression::Expression& value){
  ListIterator<expression::Expression> trlit = target.getExpressionListIteratorBegin();
  ListIterator<expression::Expression> trlitEnd = target.getExpressionListIteratorEnd();
  if(value.getNodeKind() == ndkStringLiteral){
    for (; trlit != trlitEnd; ++trlit){
      const expression::Expression& expr = *trlit;
      if (expr.getNodeKind() == ndkIdentifier) {
        const expression::Identifier& id = dynamic_cast<const expression::Identifier&>(expr);
        if(id.getRefersTo()){
          setType(*id.getRefersTo(), factory->createSequenceType(sekString));
          if(!id.getType())
            setType(const_cast<expression::Identifier&>(id), factory->createSequenceType(sekString));
        }
      }
    }
  }else if(value.getNodeKind() == ndkList){
    ListIterator<expression::Expression> lit = dynamic_cast<expression::List&>(value).getExpressionListIteratorBegin();
    ListIterator<expression::Expression> litEnd = dynamic_cast<expression::List&>(value).getExpressionListIteratorEnd();
    for(; trlit != trlitEnd && lit != litEnd; ++trlit, ++lit){
      const expression::Expression& rt = *trlit;
      const expression::Expression& vl = *lit;
      if(rt.getNodeKind() == ndkList){
        ListAssign(const_cast<expression::List&>(dynamic_cast<const expression::List&>(rt)), const_cast<expression::Expression&>(vl));
      }else if(rt.getNodeKind() == ndkIdentifier){
        if(vl.getType() && dynamic_cast<const expression::Identifier&>(rt).getRefersTo()){
          setType(*dynamic_cast<const expression::Identifier&>(rt).getRefersTo(), *vl.getType());
          if(!rt.getType())
            setType(const_cast<expression::Expression&>(rt), *vl.getType());
        }
      } // TODO: else if...
    }
  }
}

// module
void VisitorType::visit(const module::Package& node, bool callVirtualBase){
  scope.push_back(node.getId());
  module_scope.push_back(node.getId());
}
void VisitorType::visitEnd(const module::Package& node, bool callVirtualBase){
  scope.pop_back();
  module_scope.pop_back();
}

void VisitorType::visit(const module::Module& node, bool callVirtualBase){
  WriteMsg::write(CMSG_VISITING, node.getName().c_str());

  if (import_resolved.find(node.getId()) == import_resolved.end()) {
    AlgorithmPreorder ap;
    ap.setVisitSpecialNodes(false, false);

    VisitorImport* edge_visit = new VisitorImport(factory, std::list< NodeId >(), type_set, import_resolved);
    ap.run(*factory, *edge_visit, node);
    delete edge_visit;
  }
  if (node.getName().compare("__init__") == 0 && node.getParent() && filter == ExpressionsAndInit) {
    module::Package& base = dynamic_cast<module::Package&>(*node.getParent());
    for (ListIterator<module::Module> lit = base.getModuleListIteratorBegin(), litEnd = base.getModuleListIteratorEnd(); lit != litEnd; ++lit) {
      const module::Module& module = *lit;
      NodeId objectId = getObject(const_cast<module::Module&>(node), module.getName(), true);
      if (objectId) {
        module::Object& obj = dynamic_cast<module::Object&>(factory->getRef(objectId));
        if(obj.getRefersToSize() == 0)
          obj.addRefersTo(module.getId());
        setType(obj, factory->createReferenceType(module.getId()));
      }
    }
    for (ListIterator<module::Package> plit = base.getPackageListIteratorBegin(), plitEnd = base.getPackageListIteratorEnd(); plit != plitEnd; ++plit) {
      const module::Package& package = *plit;
      for (ListIterator<module::Module> lit = package.getModuleListIteratorBegin(), litEnd = package.getModuleListIteratorEnd(); lit != litEnd; ++lit) {
        const module::Module& module = *lit;
        if(module.getName().compare("__init__") == 0){
          NodeId objectId = getObject(const_cast<module::Module&>(node), module.getName(), true);
          if (objectId) {
            module::Object& obj = dynamic_cast<module::Object&>(factory->getRef(objectId));
            if(obj.getRefersToSize() == 0)
              obj.addRefersTo(module.getId());
            setType(obj, factory->createReferenceType(module.getId()));
          }
        }
      }
    }
  }
  scope.push_back(node.getId());
  module_scope.push_back(node.getId());
}
void VisitorType::visitEnd(const module::Module& node, bool callVirtualBase){
  scope.pop_back();
  module_scope.pop_back();
}

void VisitorType::visit(const module::Object& node, bool callVirtualBase){
  
}

void VisitorType::visitEnd(const module::Object& node, bool callVirtualBase){
  
}

// statement
void VisitorType::visit(const statement::ClassDef& node, bool callVirtualBase){
  scope.push_back(node.getId());
  module::Object* obj = node.getRefersTo();
  if(obj){
    setType(*obj, factory->createReferenceType(node.getId()));
  }
}

void VisitorType::visitEnd(const statement::ClassDef& node, bool callVirtualBase){
  scope.pop_back();
}

void VisitorType::visit(const statement::FunctionDef& node, bool callVirtualBase){
  NodeId parent = scope.back();
  scope.push_back(node.getId());
  module::Object* obj = node.getRefersTo();
  if(obj){
    setType(*obj, factory->createReferenceType(node.getId()));
  }

  if(parent){
    base::Base& bob = factory->getRef(parent);
    if(bob.getNodeKind() == ndkClassDef){
      if(node.getParameterSize() > 0){
        ListIterator<statement::Parameter> lit = node.getParameterListIteratorBegin();
        if (lit != node.getParameterListIteratorEnd()) {
          const statement::Parameter& par = *lit;
          
          if(par.getRefersTo() && par.getName().compare("self") == 0) {
            module::Object& bb = *par.getRefersTo();
            setType(bb, factory->createReferenceType(parent));
          }
        }
      }
    }
  }
}

void VisitorType::visitEnd(const statement::FunctionDef& node, bool callVirtualBase) {
  scope.pop_back();
}

void VisitorType::visit(const statement::BaseSpecifier& node, bool callVirtualBase){
}
void VisitorType::visitEnd(const statement::BaseSpecifier& node, bool callVirtualBase){
  if (!node.getDerivesFrom() && node.getName() && filter >= ReturnAndBaseSpec) {
    expression::Expression* name = node.getName();
    if(name->getType()){
      type::Type* type = name->getType();
      if(type->getNodeKind() == ndkReferenceType){
        if(dynamic_cast<type::ReferenceType&>(*type).getRefersTo()){
          base::Base* base = dynamic_cast<type::ReferenceType&>(*type).getRefersTo();
          if(base->getNodeKind() == ndkClassDef){
            const_cast<statement::BaseSpecifier&>(node).setDerivesFrom(base->getId());
          }
        }
      }
    }
  }
}

void VisitorType::visit(const statement::Assign& node, bool callVirtualBase){
}
void VisitorType::visitEnd(const statement::Assign& node, bool callVirtualBase){
  if(filter >= Assignments){
    statement::TargetList* target_list = node.getTargetList();
    expression::Expression* value = node.getExpression();

    if (value) { // value is optional ?!
      ListIterator<expression::Expression> trlit = target_list->getTargetListIteratorBegin();
      for (; trlit != target_list->getTargetListIteratorEnd(); ++trlit){
        const expression::Expression& rt = *trlit;
        if(rt.getNodeKind() == ndkList){
          ListAssign(const_cast<expression::List&>(dynamic_cast<const expression::List&>(rt)), *value);
        }else if(rt.getNodeKind() == ndkIdentifier){
          if(value->getType() && dynamic_cast<const expression::Identifier&>(rt).getRefersTo()){
            setType(*dynamic_cast<const expression::Identifier&>(rt).getRefersTo(), *value->getType());
            if(!rt.getType())
              setType(const_cast<expression::Expression&>(rt), *value->getType());
          }
        }// TODO: else if(rt.getNodeKind() == ndkAttributeRef || ndkSubscript || ...)
      }
    }
  }
}

void VisitorType::visit(const statement::Return& node, bool callVirtualBase) {
}

void VisitorType::visitEnd(const statement::Return& node, bool callVirtualBase) {
  if(filter >= ReturnAndBaseSpec){
    NodeId parentNid = scope.back();
    base::Base& parent = factory->getRef(parentNid);
    if (parent.getNodeKind() == ndkFunctionDef) {     // if the return is in a function's block - should be, otherwise we get parser error
      statement::FunctionDef& fdef = dynamic_cast<statement::FunctionDef&>(parent);

      expression::Expression* rExp = node.getExpression();
      if (rExp && rExp->getType()) {
          if (!fdef.getReturnType()) {
            fdef.setReturnType(rExp->getType());
          } else if (fdef.getReturnType() != rExp->getType()) {
            fdef.setReturnType(&factory->createSimpleType(stkUnknown));
          }
      }
    }
  }
}

void VisitorType::visit(const statement::TargetList& node, bool callVirtualBase){
}

void VisitorType::visitEnd(const statement::TargetList& node, bool callVirtualBase){
}

// expression
void VisitorType::visit(const expression::List& node, bool callVirtualBase){
  if (!node.getType()) {
    if(node.getIsTuple()){
      setType(const_cast<expression::List&>(node), factory->createSequenceType(sekTuple));
    }else{
      setType(const_cast<expression::List&>(node), factory->createSequenceType(sekList));
    }
  }
}

void VisitorType::visitEnd(const expression::List& node, bool callVirtualBase){}

void VisitorType::visit(const expression::KeyValue& node, bool callVirtualBase){}
void VisitorType::visitEnd(const expression::KeyValue& node, bool callVirtualBase){}

void VisitorType::visit(const expression::Generator& node, bool callVirtualBase){
}
void VisitorType::visitEnd(const expression::Generator& node, bool callVirtualBase){}

void VisitorType::visit(const expression::GeneratorExpression& node, bool callVirtualBase){
  if (!node.getType()) {
    setType(const_cast<expression::GeneratorExpression&>(node), factory->createSequenceType(sekList));
  }
}

void VisitorType::visitEnd(const expression::GeneratorExpression& node, bool callVirtualBase){}

void VisitorType::visit(const expression::Lambda& node, bool callVirtualBase){
 scope.push_back(node.getId());
}
void VisitorType::visitEnd(const expression::Lambda& node, bool callVirtualBase){
  if (!node.getType() && node.getExpression()) {
    type::Type* eType = node.getExpression()->getType();
    if (eType){
      setType(const_cast<expression::Lambda&>(node), *eType);
    }
  }
}

void VisitorType::visit(const expression::Keyword& node, bool callVirtualBase){}

void VisitorType::visitEnd(const expression::Keyword& node, bool callVirtualBase){}

void VisitorType::visit(const expression::BinaryLogical& node, bool callVirtualBase){
  if (!node.getType()) { // TODO: in case of 'and' or 'or' operation the type is not allways boolean
    setType(const_cast<expression::BinaryLogical&>(node), factory->createSimpleType(stkBoolean));
  }
}
void VisitorType::visitEnd(const expression::BinaryLogical& node, bool callVirtualBase){}

void VisitorType::visit(const expression::IfExpression& node, bool callVirtualBase){}
void VisitorType::visitEnd(const expression::IfExpression& node, bool callVirtualBase){}

void VisitorType::visit(const expression::ArgumentList& node, bool callVirtualBase){}
void VisitorType::visitEnd(const expression::ArgumentList& node, bool callVirtualBase){}

void VisitorType::visit(const expression::StringConversion& node, bool callVirtualBase){
  if (!node.getType()) {
    setType(const_cast<expression::StringConversion&>(node), factory->createSequenceType(sekString));
  }
}
void VisitorType::visitEnd(const expression::StringConversion& node, bool callVirtualBase){}

void VisitorType::visit(const expression::UnaryOperation& node, bool callVirtualBase){}
void VisitorType::visitEnd(const expression::UnaryOperation& node, bool callVirtualBase){
  if (!node.getType()) {
    if(node.getKind() == unkNot){
      setType(const_cast<expression::UnaryOperation&>(node), factory->createSimpleType(stkBoolean));
    }else{
      expression::Expression* expr = node.getExpression();
      if(expr){
        type::Type* eType = expr->getType();
        if(eType){
          setType(const_cast<expression::UnaryOperation&>(node), *eType);
        }
      }
    }
  }
}

void VisitorType::visit(const expression::AttributeRef& node, bool callVirtualBase) {
}

void VisitorType::setAttributeType(const expression::AttributeRef& node, NodeId lTypeNid) {
  NodeKind lTypeKind;
  expression::Identifier* right = dynamic_cast<expression::Identifier*>(node.getRightExpression());
  std::string rightString = right->getName();

  if (Common::getIsValid(lTypeNid)) {
    type::Type& lType = dynamic_cast<type::Type&>(factory->getRef(lTypeNid));
    lTypeKind = lType.getNodeKind();

    if (lTypeKind == ndkReferenceType) {
      base::Positioned* object = dynamic_cast<type::ReferenceType&>(factory->getRef(lTypeNid)).getRefersTo();
      NodeKind objectKind;
      if (object) {
        objectKind = object->getNodeKind();
        if (objectKind == ndkClassDef || objectKind == ndkModule) {
          NodeId returnedNid = findObject(*object, rightString, true);    // looking for "rightString" attribute/class/function in "curr_scope" class/module
          if (!Common::getIsValid(returnedNid)) {      // no such object
            // TODO:check if it was last part of the attributeref (and left side of an assign) - in that case create a new object
          } else {
            module::Object& returned = dynamic_cast<module::Object&>(factory->getRef(returnedNid));
            if (returned.getTypeSize() == 1) {    // the resolved object has exactly one type -- clone, should be refactored
              ListIterator<type::Type> lit = returned.getTypeListIteratorBegin();
              const type::Type& tt = *lit;
              setType(const_cast<expression::AttributeRef&>(node), const_cast<type::Type&>(tt));
              right->setRefersTo(returned.getId());
              setType(const_cast<expression::Identifier&>(*right), const_cast<type::Type&>(tt));
            } else if (returned.getTypeSize() > 1){
              setType(const_cast<expression::AttributeRef&>(node), factory->createSimpleType(stkUnknown));
            }
          }
        } else if (objectKind == ndkFunctionDef) {
          type::Type* returnType = dynamic_cast<statement::FunctionDef&>(*object).getReturnType();
          if (returnType && lTypeNid != returnType->getId()) {
            setAttributeType(node, returnType->getId());
          }
        } else {
          // TODO?
        }
      }
    } else {
      setType(const_cast<expression::AttributeRef&>(node), factory->createSimpleType(stkUnknown));
    }
  }
}

void VisitorType::visitEnd(const expression::AttributeRef& node, bool callVirtualBase) {
  if (!node.getType() && filter >= ExprAndAtrRef) {
    expression::Expression* left = node.getLeftExpression();
    expression::Identifier* right = dynamic_cast<expression::Identifier*>(node.getRightExpression());

    std::string rightString = right->getName();
    NodeKind lKind = left->getNodeKind();
    
    if (lKind == ndkAttributeRef || lKind == ndkIdentifier) {
      if (!left->getType() && lKind == ndkAttributeRef) {
        setType(const_cast<expression::AttributeRef&>(node), factory->createSimpleType(stkUnknown));
      } else {
        NodeId lTypeNid = 0;
        
        if (lKind == ndkIdentifier) {
          NodeId lObjectNid = findObject(factory->getRef(scope.back()), dynamic_cast<expression::Identifier&>(*left).getName());
          if (!Common::getIsValid(lObjectNid)) {
            setType(const_cast<expression::AttributeRef&>(node), factory->createSimpleType(stkUnknown));
          } else {
            module::Object& lObject = dynamic_cast<module::Object&>(factory->getRef(lObjectNid));
            if (lObject.getTypeSize() == 1) {
              ListIterator<type::Type> lit = lObject.getTypeListIteratorBegin();
              lTypeNid = (*lit).getId();
            } else if (lObject.getTypeSize() > 1) {
              setType(const_cast<expression::AttributeRef&>(node), factory->createSimpleType(stkUnknown));
            }
          }
        } else {
          lTypeNid = left->getType()->getId();
        }
        
        setAttributeType(node, lTypeNid);
      }
    } else if (lKind == ndkCall) {
      statement::CompoundStatement* comStm = dynamic_cast<expression::Call&>(*left).getRefersTo();
      if (comStm) {
        NodeKind refKind = comStm->getNodeKind();
        if (refKind == ndkClassDef) {
          NodeId objNid = getObject(*comStm, rightString);
          if (!Common::getIsValid(objNid)) {
            setType(const_cast<expression::AttributeRef&>(node), factory->createSimpleType(stkUnknown));
          } else {
            module::Object& returned = dynamic_cast<module::Object&>(factory->getRef(objNid));
            if (returned.getTypeSize() == 1) {    // the resolved object has exactly one type  -- clone, should be refactored
              ListIterator<type::Type> lit = returned.getTypeListIteratorBegin();
              const type::Type& tt = *lit;
              setType(const_cast<expression::AttributeRef&>(node), const_cast<type::Type&>(tt));
              right->setRefersTo(returned.getId());
              setType(const_cast<expression::Identifier&>(*right), const_cast<type::Type&>(tt));
            } else if (returned.getTypeSize() > 1) {
              setType(const_cast<expression::AttributeRef&>(node), factory->createSimpleType(stkUnknown));
            }
          }
        } else if (refKind == ndkFunctionDef) {
          type::Type* returnType = dynamic_cast<statement::FunctionDef&>(*comStm).getReturnType();
          if (returnType) {
            setAttributeType(node, returnType->getId());
          }
        }
      }
    }
  }
}

void VisitorType::visit(const expression::Dictionary& node, bool callVirtualBase){
  if (!node.getType()) {
    setType(const_cast<expression::Dictionary&>(node), factory->createDictType());
  }
}
void VisitorType::visitEnd(const expression::Dictionary& node, bool callVirtualBase){}

void VisitorType::visit(const expression::Slicing& node, bool callVirtualBase){}
void VisitorType::visitEnd(const expression::Slicing& node, bool callVirtualBase){}

void VisitorType::visit(const expression::Slice& node, bool callVirtualBase){}
void VisitorType::visitEnd(const expression::Slice& node, bool callVirtualBase){}

void VisitorType::visit(const expression::BinaryArithmetic& node, bool callVirtualBase){}
void VisitorType::visitEnd(const expression::BinaryArithmetic& node, bool callVirtualBase){
  if (!node.getType()) {
    expression::Expression* leftExp = node.getLeftExpression();
    expression::Expression* rightExp = node.getRightExpression();

    type::Type* leftType = leftExp->getType();
    type::Type* rightType = rightExp->getType();

    if (leftType && rightType) {
      NodeKind lNodeKind = leftType->getNodeKind();
      NodeKind rNodeKind = rightType->getNodeKind();

      if (lNodeKind == ndkSimpleType && rNodeKind == ndkSimpleType) { 
        SimpleTypeKind nType;
        SimpleTypeKind lType = dynamic_cast<type::SimpleType&>(*leftType).getKind();
        SimpleTypeKind rType = dynamic_cast<type::SimpleType&>(*rightType).getKind();
        if (lType == stkImaginary || rType == stkImaginary) nType = stkImaginary;
        else if (lType == stkFloat || rType == stkFloat) nType = stkFloat;
        else if (lType == stkLong || rType == stkLong) nType = stkLong;
        else nType = stkInteger;
        if (lType == stkUnknown || rType == stkUnknown) nType = stkUnknown;
        
        setType(const_cast<expression::BinaryArithmetic&>(node), factory->createSimpleType(nType));
      } else if (lNodeKind == ndkSequenceType && rNodeKind == ndkSequenceType) {
        SequenceTypeKind lType = dynamic_cast<type::SequenceType&>(*leftType).getKind();
        SequenceTypeKind rType = dynamic_cast<type::SequenceType&>(*rightType).getKind();

        if (lType == rType) {
          setType(const_cast<expression::BinaryArithmetic&>(node), factory->createSequenceType(lType));
        } else {
          setType(const_cast<expression::BinaryArithmetic&>(node), factory->createSimpleType(stkUnknown));
        }
      } else if (lNodeKind == ndkDictType && rNodeKind == ndkDictType) {
        setType(const_cast<expression::BinaryArithmetic&>(node), factory->createDictType());
      } else if (lNodeKind == ndkSequenceType && rNodeKind == ndkSimpleType) {
        SequenceTypeKind lType = dynamic_cast<type::SequenceType&>(*leftType).getKind();
        SimpleTypeKind rType = dynamic_cast<type::SimpleType&>(*rightType).getKind();
        
        if (rType == stkUnknown) {
          setType(const_cast<expression::BinaryArithmetic&>(node), factory->createSimpleType(stkUnknown));
        } else if (lType == sekString && (rType == stkInteger || rType == stkLong) ) {
          setType(const_cast<expression::BinaryArithmetic&>(node), factory->createSequenceType(sekString));
        } else if (lType == sekList && (rType == stkBoolean || rType == stkInteger) ) {
          setType(const_cast<expression::BinaryArithmetic&>(node), factory->createSequenceType(sekList));
        } else {
          setType(const_cast<expression::BinaryArithmetic&>(node), factory->createSimpleType(stkUnknown));
        }
      } else if (lNodeKind == ndkSimpleType && rNodeKind == ndkSequenceType) {
        SimpleTypeKind lType = dynamic_cast<type::SimpleType&>(*leftType).getKind();
        SequenceTypeKind rType = dynamic_cast<type::SequenceType&>(*rightType).getKind();
        
        if (lType == stkUnknown) {
          setType(const_cast<expression::BinaryArithmetic&>(node), factory->createSimpleType(stkUnknown));
        } else if (rType == sekString && (lType == stkInteger || lType == stkLong) ) {
          setType(const_cast<expression::BinaryArithmetic&>(node), factory->createSequenceType(sekString));
        } else if (rType == sekList && (lType == stkBoolean || lType == stkInteger) ) {
          setType(const_cast<expression::BinaryArithmetic&>(node), factory->createSequenceType(sekList));
        } else {
          setType(const_cast<expression::BinaryArithmetic&>(node), factory->createSimpleType(stkUnknown));
        }
      }
    }
  }
}

void VisitorType::visit(const expression::Identifier& node, bool callVirtualBase){
  if(!node.getType() && filter >= ExprAndAtrRef){
    if(node.getRefersTo()){
      module::Object* ob = node.getRefersTo();
      if(ob->getTypeSize() == 1){
        ListIterator<type::Type> lit = ob->getTypeListIteratorBegin();
        setType(const_cast<expression::Identifier&>(node), const_cast<type::Type&>(*lit));
      }else if(ob->getRefersToSize() == 1){
        ListIterator<base::Positioned> lit = ob->getRefersToListIteratorBegin();
        const base::Base& base = *lit;
        if(base.getNodeKind() == ndkFunctionDef || base.getNodeKind() == ndkClassDef)
          setType(const_cast<expression::Identifier&>(node), factory->createReferenceType(base.getId()));
      }
    }else{
      if(node.getParent() && node.getParent()->getNodeKind() != ndkAttributeRef){
        NodeId objid = findObject(factory->getRef(scope.back()), node.getName());
        if(Common::getIsValid(objid)){
          module::Object& ob = dynamic_cast<module::Object&>(factory->getRef(objid));
          const_cast<expression::Identifier&>(node).setRefersTo(objid);
          if(ob.getTypeSize() == 1){
            ListIterator<type::Type> lit = ob.getTypeListIteratorBegin();
            setType(const_cast<expression::Identifier&>(node), const_cast<type::Type&>(*lit));
          }
        }
      }
    }
  }
}
void VisitorType::visitEnd(const expression::Identifier& node, bool callVirtualBase){}

void VisitorType::visit(const expression::ListComp& node, bool callVirtualBase){
  if (!node.getType()) {
    setType(const_cast<expression::ListComp&>(node), factory->createSequenceType(sekList));
  }
}
void VisitorType::visitEnd(const expression::ListComp& node, bool callVirtualBase){}

void VisitorType::visit(const expression::ExpressionList& node, bool callVirtualBase){}
void VisitorType::visitEnd(const expression::ExpressionList& node, bool callVirtualBase){}

void VisitorType::visit(const expression::Ellipsis& node, bool callVirtualBase){}
void VisitorType::visitEnd(const expression::Ellipsis& node, bool callVirtualBase){}

void VisitorType::visit(const expression::ExtSlice& node, bool callVirtualBase){}
void VisitorType::visitEnd(const expression::ExtSlice& node, bool callVirtualBase){}

void VisitorType::visit(const expression::Subscription& node, bool callVirtualBase){}
void VisitorType::visitEnd(const expression::Subscription& node, bool callVirtualBase){}

void VisitorType::visit(const expression::Call& node, bool callVirtualBase) {

}
void VisitorType::visitEnd(const expression::Call& node, bool callVirtualBase) {
  if (filter >= ExprAndAtrRef) {
    if (!node.getRefersTo()) {
      expression::Expression* ex = node.getExpression();
      if (ex->getType()) {
        type::Type* type = ex->getType();
        if (type->getNodeKind() == ndkReferenceType) {
          if (dynamic_cast<type::ReferenceType&>(*type).getRefersTo()) {
            base::Base* ref = dynamic_cast<type::ReferenceType&>(*type).getRefersTo();
            NodeKind ndk = ref->getNodeKind();
            if (ndk == ndkClassDef || ndk == ndkFunctionDef) {
              const_cast<expression::Call&>(node).setRefersTo(ref->getId());
            }
          }
        }
      }
    }else{
      if (!node.getType()) {
        base::Base* ref = node.getRefersTo();
        NodeKind ndk = ref->getNodeKind();
        if (ndk == ndkClassDef) {
          setType(const_cast<expression::Call&>(node), factory->createReferenceType(ref->getId()));
        } else if(ndk == ndkFunctionDef) {
          type::Type* return_type = dynamic_cast<const statement::FunctionDef&>(*ref).getReturnType();
          if (return_type) {
            setType(const_cast<expression::Call&>(node), *return_type);
          }
        }
      }
    }
  }
}

void VisitorType::visit(const expression::Index& node, bool callVirtualBase){
}

void VisitorType::visitEnd(const expression::Index& node, bool callVirtualBase){}


// literal
void VisitorType::visit(const expression::LongInteger& node, bool callVirtualBase){
  if (!node.getType()) {
    setType(const_cast<expression::LongInteger&>(node), factory->createSimpleType(stkLong));
  }
}

void VisitorType::visit(const expression::IntegerLiteral& node, bool callVirtualBase){
  if (!node.getType()) {
    setType(const_cast<expression::IntegerLiteral&>(node), factory->createSimpleType(stkInteger));
  }
}

void VisitorType::visit(const expression::ImagNumber& node, bool callVirtualBase){
  if (!node.getType()) {
    setType(const_cast<expression::ImagNumber&>(node), factory->createSimpleType(stkImaginary));
  }
}

void VisitorType::visit(const expression::FloatNumber& node, bool callVirtualBase){
  if (!node.getType()) {
    setType(const_cast<expression::FloatNumber&>(node), factory->createSimpleType(stkFloat));
  }
}

void VisitorType::visit(const expression::StringLiteral& node, bool callVirtualBase){
  if (!node.getType()) {
    setType(const_cast<expression::StringLiteral&>(node),  factory->createSequenceType(sekString));
  }
}
