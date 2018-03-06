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

#include "../inc/VisitorImport.h"
#include <common/inc/WriteMessage.h>
#include "../inc/messages.h"

using namespace common;
using namespace columbus;
using namespace std;

void VisitorImport::setType(module::Object& obj, type::Type& type) {
  std::map< NodeId, std::set<NodeId> >::iterator it = type_set.find(obj.getId());
  
  if(it == type_set.end()){
    std::set<NodeId> node_set;
    bool new_type = true;
    ListIterator<type::Type> lit = obj.getTypeListIteratorBegin();
    for (; lit != obj.getTypeListIteratorEnd(); ++lit){
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

NodeId VisitorImport::findModule(module::Package& package, std::string name){
  NodeId package_id = package.getId();
  NodeId module_id = 0;
  
  while(name.find_first_of(".") != std::string::npos){
    std::string pname = name.substr(0, name.find_first_of("."));
    module::Package& package = dynamic_cast<module::Package&>(factory->getRef(package_id));
    ListIterator<module::Package> lit = package.getPackageListIteratorBegin();

    bool find = false;
     for (; lit != package.getPackageListIteratorEnd(); ++lit) {
      const module::Package& chpackage = *lit;
      if(pname.compare(chpackage.getName()) == 0){
        package_id = chpackage.getId();
        find = true;
        break;
      }
    }
    if(!find){
      package_id = 0;
      break;
    }

    size_t size = name.find_first_of(".")+1;
    name = name.substr(size, name.length()-size);
  }
  if(package_id != 0){
    module::Package& pkg = dynamic_cast<module::Package&>(factory->getRef(package_id));
    ListIterator<module::Package> lit = pkg.getPackageListIteratorBegin();
    ListIterator<module::Package> litEnd = pkg.getPackageListIteratorEnd();
    for(; lit != litEnd; ++lit){
      const module::Package& package = *lit;
      if(name.compare(package.getName()) == 0){
        package_id = package.getId();
        name = "__init__";
        break;
      }
    }
    module::Package& act_pkg = dynamic_cast<module::Package&>(factory->getRef(package_id));
    ListIterator<module::Module> moduleLit = act_pkg.getModuleListIteratorBegin();
    for(; moduleLit != act_pkg.getModuleListIteratorEnd(); ++moduleLit){
      const module::Module& module = *moduleLit;
      if(name.compare(module.getName()) == 0){
        module_id = module.getId();
        break;
      }
    }
  }
  return module_id;
}

std::set<std::string> VisitorImport::getAll(module::Module& module){
  ListIterator<module::Object> lit = module.getObjectListIteratorBegin();
  std::set<std::string> __all__;
  std::set<std::string> ret;
  for(; lit != module.getObjectListIteratorEnd(); ++lit){
    const module::Object& obj = *lit;
    std::string name = obj.getName();
    if(obj.getName().compare("__all__") == 0){
      bool new_all = false;
      if(obj.getRefersToSize() == 1){
        const base::Base& id = *obj.getRefersToListIteratorBegin();
        if(id.getNodeKind() == ndkIdentifier){
          base::Base* parent = id.getParent();
          NodeKind ndk = parent->getNodeKind();
          while(parent && (ndk != ndkModule && ndk != ndkAssign)){
            parent = parent->getParent();
            if(parent) ndk = parent->getNodeKind();
          }
          if(parent && ndk == ndkAssign){
            statement::Assign& assign = dynamic_cast<statement::Assign&>(*parent);
            statement::TargetList* trlist = assign.getTargetList();
            if(trlist){
              NodeId all = 0;
              ListIterator<expression::Expression> trlit = trlist->getTargetListIteratorBegin();
              for(; trlit != trlist->getTargetListIteratorEnd(); ++trlit){
                all = getAssignValue(const_cast<expression::Expression&>(*trlit), *assign.getExpression(), id.getId());
                if (all != 0){
                  break;
                }
              }
              if(Common::getIsValid(all)){
                const base::Base& all_node = factory->getRef(all);
                if(all_node.getNodeKind() == ndkList){
                  new_all = true;
                  ListIterator<expression::Expression> list = dynamic_cast<const expression::List&>(all_node).getExpressionListIteratorBegin();
                  for(; list != dynamic_cast<const expression::List&>(all_node).getExpressionListIteratorEnd(); ++list){
                    const base::Base& item = *list;
                    if(item.getNodeKind() == ndkStringLiteral){
                      __all__.insert(dynamic_cast<const expression::StringLiteral&>(item).getValue());
                    }else{
                      new_all = false;
                    }
                  }
                }
              }
            }
          }
        }
      }
      if(new_all){
        ret = __all__;
        break;
      }
    }
    if(name[0] != '_'){
      ret.insert(name);
    }
  }
  return ret;
}

NodeId VisitorImport::findObject(const std::string& name, ListIterator<module::Object> lit, ListIterator<module::Object> litEnd) {
  NodeId object = 0;
  for (; lit != litEnd; ++lit){
    const module::Object& obj = *lit;
    if(obj.getName().compare(name) == 0){
      object = obj.getId();
      break;
    }
  }
  return object;
}

NodeId VisitorImport::getObject(base::Base& current_scope, std::string name, bool create_object){
  NodeId object = 0;
  NodeKind scope_kind = current_scope.getNodeKind();

  if(scope_kind == ndkModule || scope_kind == ndkFunctionDef || scope_kind == ndkClassDef || scope_kind == ndkLambda){
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

NodeId VisitorImport::getAssignValue(expression::Expression& target_list, expression::Expression& value, NodeId target){
  NodeId ret = 0;
  if(target_list.getNodeKind() == ndkList){
    if(value.getNodeKind() == ndkStringLiteral){
      if(dynamic_cast<expression::List&>(target_list).getIsTuple()){
        ret = value.getId();
      }
    }else if(value.getNodeKind() == ndkList){
      ListIterator<expression::Expression> trlit = dynamic_cast<expression::List&>(target_list).getExpressionListIteratorBegin();
      ListIterator<expression::Expression> trlitEnd = dynamic_cast<expression::List&>(target_list).getExpressionListIteratorEnd();
      ListIterator<expression::Expression> lit = dynamic_cast<expression::List&>(value).getExpressionListIteratorBegin();
      ListIterator<expression::Expression> litEnd = dynamic_cast<expression::List&>(value).getExpressionListIteratorEnd();
       for(; trlit != trlitEnd && lit != litEnd; ++trlit, ++lit){
        const expression::Expression& rt = *trlit;
        const expression::Expression& vl = *lit;
        if(rt.getNodeKind() == ndkList){
          ret = getAssignValue(const_cast<expression::List&>(dynamic_cast<const expression::List&>(rt)), const_cast<expression::Expression&>(vl), target);
        }else if(rt.getNodeKind() == ndkIdentifier){
          if(rt.getId() == target){
            ret = vl.getId();
            break;
          }
        } // TODO: else if...
      }
    }
  }else if(target_list.getNodeKind() == ndkIdentifier){
    if(target_list.getId() == target){
      ret = value.getId();
    }
  }
  return ret;
}

void VisitorImport::visit(const statement::ClassDef& n, bool callVirtualBase){
  scope.push_back(n.getId());
}

void VisitorImport::visitEnd(const statement::ClassDef& n, bool callVirtualBase){
  scope.pop_back();  
}

void VisitorImport::visit(const statement::FunctionDef& n, bool callVirtualBase){
  scope.push_back(n.getId());  
}

void VisitorImport::visitEnd(const statement::FunctionDef& n, bool callVirtualBase){
  scope.pop_back();  
}

void VisitorImport::visit(const module::Module& n, bool callVirtualBase){
#ifdef _DEBUG
  for(unsigned i=0; i<import_tree.size(); ++i){
    WriteMsg::write(WriteMsg::mlDebug, "  ");
  }
#endif
  WriteMsg::write(CMSG_IMPORT_MODULE, n.getName().c_str());

  package_id = n.getParent()->getId();
  import_tree.push_back(n.getId());
  scope.push_back(n.getId()); 
}

void VisitorImport::visitEnd(const module::Module& n, bool callVirtualBase){
  import_resolved.insert(n.getId());
  import_tree.pop_back();
  scope.pop_back();
}

void VisitorImport::visit(const statement::ImportFrom& node, bool callVirtualBase){
  import_scope = package_id;
  int level = node.getLevel();
  bool found = true;
  for (int i = 0; i < level; ++i){
    base::Base& base = factory->getRef(import_scope);
    if (base.getParent()){
      import_scope = base.getParent()->getId();
    }else{
      WriteMsg::write(CMSG_WRONG_PKG_LEVEL, level, node.getId());
      found = false;
      break;
    }
  }
  if (found)
    import_scope = findModule(dynamic_cast<module::Package&>(factory->getRef(import_scope)), node.getModulname());
}
void VisitorImport::visitEnd(const statement::ImportFrom& node, bool callVirtualBase){
  import_scope = 0;
}

void VisitorImport::visit(const statement::ImportStatement& node, bool callVirtualBase){
  import_scope = package_id;
}
void VisitorImport::visitEnd(const statement::ImportStatement& node, bool callVirtualBase){
  import_scope = 0;
}

void VisitorImport::visit(const statement::Alias& node, bool callVirtualBase){

  if(!node.getRefersTo()){
    std::string name = node.getName();
    if(import_scope){
      base::Base& iscope = factory->getRef(import_scope);
      if(iscope.getNodeKind() == ndkModule){
        list<NodeId>::iterator it = find(import_tree.begin(), import_tree.end(), import_scope);
        if(import_resolved.find(import_scope) == import_resolved.end()){
          if(it != import_tree.end()){

          }else{
            VisitorImport* edge_visit = new VisitorImport(factory, import_tree, type_set, import_resolved);
            AlgorithmPreorder ap;
            ap.setVisitSpecialNodes(false, false);
            ap.run(*factory, *edge_visit, import_scope);
            delete edge_visit;
          }
        }

        std::set<std::string> __all__ = getAll(dynamic_cast<module::Module&>(iscope));
        ListIterator<module::Object> lit = dynamic_cast<module::Module&>(iscope).getObjectListIteratorBegin();
        ListIterator<module::Object> litEnd = dynamic_cast<module::Module&>(iscope).getObjectListIteratorEnd();
        if(name.compare("*") == 0){
          const_cast<statement::Alias&>(node).setRefersTo(import_scope);
          for(; lit != litEnd; ++lit){
            const module::Object& obj = *lit;
            if(__all__.find(obj.getName()) != __all__.end()){
              NodeId objid = getObject(factory->getRef(scope.back()), obj.getName(), true);
              if(Common::getIsValid(objid) && objid != obj.getId()){
                module::Object& local_obj = dynamic_cast<module::Object&>(factory->getRef(objid));
                ListIterator<base::Positioned> reflit = obj.getRefersToListIteratorBegin();
                for(; reflit != obj.getRefersToListIteratorEnd(); ++reflit){
                  local_obj.addRefersTo(reflit->getId());
                }
                ListIterator<type::Type> typeLit = obj.getTypeListIteratorBegin();
                for(; typeLit != obj.getTypeListIteratorEnd(); ++typeLit){
                  setType(local_obj, const_cast<type::Type&>(*typeLit));
                }
              }
            }
          }
        }else{
          for(; lit != litEnd; ++lit){
            const module::Object& obj = *lit;
            if(name.compare(obj.getName()) == 0){
              const_cast<statement::Alias&>(node).setRefersTo(obj.getId());
              std::string obj_name; 
              if(node.getAlias().size() != 0){
                obj_name = node.getAlias();
              }else{
                obj_name = name;
              }              
              NodeId objid = getObject(factory->getRef(scope.back()), obj_name, true);
              if(obj.getId() != objid){
                module::Object& local_obj = dynamic_cast<module::Object&>(factory->getRef(objid));
                ListIterator<base::Positioned> reflit = obj.getRefersToListIteratorBegin();
                for(; reflit != obj.getRefersToListIteratorEnd(); ++reflit){
                  local_obj.addRefersTo(reflit->getId());
                }
                ListIterator<type::Type> typeLit = obj.getTypeListIteratorBegin();
                for(; typeLit != obj.getTypeListIteratorEnd(); ++typeLit){
                  setType(local_obj, const_cast<type::Type&>(*typeLit));
                }
              }
            }
          }
        }
      }else{
        NodeId import_module = findModule(dynamic_cast<module::Package&>(factory->getRef(import_scope)), name);
        if (Common::getIsValid(import_module)) {
          module::Module& module = dynamic_cast<module::Module&>(factory->getRef(import_module));
          list<NodeId>::iterator it = find(import_tree.begin(), import_tree.end(), module.getId());
          if (import_resolved.find(module.getId()) == import_resolved.end() && it == import_tree.end()) {
            VisitorImport* edge_visit = new VisitorImport(factory, import_tree, type_set, import_resolved);
            AlgorithmPreorder ap;
            ap.setVisitSpecialNodes(false, false);
            ap.run(*factory, *edge_visit, module);
            delete edge_visit;
          }
          std::string obj_name; 
          if(node.getAlias().size() != 0){
            obj_name = node.getAlias();
          }else{
            obj_name = name;
          }
          const_cast<statement::Alias&>(node).setRefersTo(import_module);
          size_t pos = obj_name.find_first_of(".");
          if(pos != std::string::npos){
            obj_name = obj_name.substr(0, pos);
            import_module = findModule(dynamic_cast<module::Package&>(factory->getRef(import_scope)), obj_name);
          }
          NodeId objid = getObject(factory->getRef(scope.back()), obj_name, true);
          module::Object& local_obj = dynamic_cast<module::Object&>(factory->getRef(objid));
          local_obj.addRefersTo(import_module);
          setType(local_obj, dynamic_cast<type::Type&>(factory->createReferenceType(import_module)));
        }
      }
    }
  }
}
void VisitorImport::visitEnd(const statement::Alias& node, bool callVirtualBase){}
