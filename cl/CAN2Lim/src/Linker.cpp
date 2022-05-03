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

#include "../inc/Linker.h"
#include "../inc/clangHelpers.h"
#include "../inc/ASTConversionInfo.h"

#include<iostream>


using namespace std;
using namespace clang;
using namespace columbus::lim::asg;

void Linker::add_definition(Member * limNode, std::shared_ptr<clang::metrics::UID> uid)
{
  UID_to_definitions.emplace(std::static_pointer_cast<MergeUID>(uid), limNode);
}

void Linker::add_declaration(Member * limNode, std::shared_ptr<clang::metrics::UID> uid)
{
  unresolved_declarations.push_back(std::pair<std::shared_ptr<MergeUID>,columbus::lim::asg::Member*>(std::static_pointer_cast<MergeUID>(uid), limNode));
}

/*void Linker::handle_decl(const Decl * decl, std::shared_ptr<clang::metrics::UID> uid, Member * limNode)
{
  if (isDefinition(decl))
  {
    UID_to_definitions.emplace(std::static_pointer_cast<MergeUID>(uid), limNode);
  }
  else
  {
    if(const Decl* localDefinition = getLocalDefinition(decl))
    {
      //cout << "LINKER: Local defintion found for declaration: " << limNode->getName() << endl;
      std::shared_ptr<clang::metrics::UID> localDefinitionUID = conversionInfo.uidFactory.create(localDefinition);
      auto localDefinitionIt = conversionInfo.limTable.find(localDefinitionUID);
      if (localDefinitionIt != conversionInfo.limTable.end())
      {
        //cout << "LINKER: Local defintion linked to declaration!" << endl;
        limNode->setDeclares(dynamic_cast<Member*>(localDefinitionIt->second));
      }
      else
      {
        conversionInfo.linker.unresolved_declarations.push_back(std::pair<std::shared_ptr<MergeUID>,columbus::lim::asg::Member*>(std::static_pointer_cast<MergeUID>(uid), limNode));
      }
    }
    else
    {
      conversionInfo.linker.unresolved_declarations.push_back(std::pair<std::shared_ptr<MergeUID>,columbus::lim::asg::Member*>(std::static_pointer_cast<MergeUID>(uid), limNode));
    }
  }
}*/

bool Linker::link_unresolved_declarations()
{
  if(LINKER_DEBUG)
    print_debug_overview();

  for (auto decl_kv : unresolved_declarations)
  {
    bool foundDefinitionForDeclaration = false;
    if(UID_to_definitions.count(decl_kv.first) == 0)
    {
      //if there is no definition for the declaration UID then we have to go no further, just skip this and go for next
      if(LINKER_DEBUG)
        cout << "Definition not found for " << decl_kv.first->getMangledName() << endl; 
      continue;
    }

    //check for each component (Note: we are using belongsTo edges of file nodes, so they must be set already)
    for (auto decl_comp_it = decl_kv.second->getBelongsToListIteratorBegin(); decl_comp_it != decl_kv.second->getBelongsToListIteratorEnd(); ++decl_comp_it)
    {
      if(SIMPLIFIED_LINKING && foundDefinitionForDeclaration) //in this case, we don't handle component-specific linking, so just break after finding the first definition
        break;

      const columbus::lim::asg::base::Component *decl_component = &(*decl_comp_it);
      auto range = UID_to_definitions.equal_range(decl_kv.first);
      for (auto def_it = range.first; def_it != range.second; ++def_it)
      {
        if(def_it->second->getIsContainedInIsEmpty())
          break; //definitions must have a containedIn file

        const columbus::lim::asg::physical::File *file = &(*(def_it->second->getIsContainedInListIteratorAssocBegin()));
        if (component_to_files[const_cast<columbus::lim::asg::base::Component*>(decl_component)].count(const_cast<columbus::lim::asg::physical::File*>(file)) == 1)
        {
          //the declaration and the definition is in the same component, so link them!
          //The only problem here is that the LIM is incapable of handling component-dependent linking, so here we just overwrite if there are multiple definitions...
          decl_kv.second->setDeclares(def_it->second); //TODO: modify this line accordingly, if the LIM schema is ready for it (and turn off SIMPLIFIED_LINKING)
          foundDefinitionForDeclaration = true;
          if(LINKER_DEBUG)
            cout << "Linked declaration " << decl_kv.first->getMangledName() << " in component " << decl_component->getName() << " to definition "<< def_it->first->getMangledName() <<" in file " << file->getName() << endl;
          break; //a declaration can only be linked to one file per component(if there are no multiple definitions, in which case, it shouldn't even build...)
        }
      }
    }
    if(LINKER_DEBUG && !foundDefinitionForDeclaration)
      //in this case there IS a definition for the declaration just not in the same compononent so we cannot link them
      cout << "Definition not found for " << decl_kv.first->getMangledName() << endl; 
  }

  return true;
}

bool Linker::link_unresolved_calls()
{
  //helper lambda
  auto hasCallsAlready = [](auto node, columbus::NodeId callId)
  {
    for (auto it = node->getCallsListIteratorBegin(); it != node->getCallsListIteratorEnd(); ++it)
    {
      if (it->getId() == callId)
        return true;
    }

    return false;
  };

  for (auto call_kv : unresolved_calls)
  {
    bool foundDefinitionForCall = false;
    if(UID_to_definitions.count(call_kv.first) == 0)
    {
      //if there is no definition for the call UID then we have to go no further, just skip this and go for next
      if(LINKER_DEBUG)
        cout << "Definition not found for " << call_kv.first->getMangledName() << endl; 
      continue;
    }

    auto range = UID_to_definitions.equal_range(call_kv.first);
    for (auto def_it = range.first; def_it != range.second; ++def_it)
    {
      // This is defense against a bug that i couldnt handle properly
      // If its not a method dont try to put a call on it
      if (dynamic_cast<Method*>(def_it->second) == NULL)
        continue;

      MethodCall *limCall = &conversionInfo.limFactory.createMethodCall(def_it->second->getId());
      if (Attribute *attr = dynamic_cast<Attribute*>(call_kv.second))
      {
        //cout << attr->getName() << endl;
        if(!hasCallsAlready(attr,limCall->getId()))
          attr->addCalls(limCall);
      }
      else if (Method *method = dynamic_cast<Method*>(call_kv.second))
      {
        if(!hasCallsAlready(method,limCall->getId()))
          method->addCalls(limCall);
      }
    }

    if(LINKER_DEBUG && !foundDefinitionForCall)
      cout << "Definition not found for " << call_kv.first->getMangledName() << endl; 

  }
  return true;
}

bool Linker::link_unresolved_attribute_accesses()
{
  for (auto access_kv : unresolved_attribute_accesses)
  {
    bool foundDefinitionForCall = false;
    if(UID_to_definitions.count(access_kv.first) == 0)
    {
      //if there is no definition for the call UID then we have to go no further, just skip this and go for next
      if(LINKER_DEBUG)
        cout << "Definition not found for " << access_kv.first->getMangledName() << endl; 
      continue;
    }

    auto range = UID_to_definitions.equal_range(access_kv.first);
    for (auto def_it = range.first; def_it != range.second; ++def_it)
    {
      if (Attribute* limAttribute = dynamic_cast<Attribute*>(def_it->second))
      {
        AttributeAccess& access = conversionInfo.limFactory.createAttributeAccess(limAttribute->getId());
        Method* limMethod = access_kv.second;

        if(!contains(limMethod->getAccessesAttributeListIteratorBegin(),limMethod->getAccessesAttributeListIteratorEnd(),&access))
          limMethod->addAccessesAttribute(&access);
      }
      
    }

    if(LINKER_DEBUG && !foundDefinitionForCall)
      cout << "Definition not found for " << access_kv.first->getMangledName() << endl; 

  }
  return true;
}

void Linker::print_debug_overview()
{
  if (LINKER_DEBUG)
  {
    cout << "Linking overview:" << endl;
    /*cout << "File to components map:" << endl;
    for (auto kv : file_to_components)
    {
      cout << "File: " << kv.first->getName() << " , it's components: " << endl;
      for(auto component : kv.second)
      {
        cout << component->getName() << endl;
      }
    }*/
    cout << "Component to files map:" << endl;
    for (auto kv : component_to_files)
    {
      cout << "Component: " << kv.first->getName() << " , it's files: " << endl;
      for(auto file : kv.second)
      {
        cout << file->getName() << endl;
      }
    }
    cout << "Unresolved declarations:" << endl;
    for (auto p : unresolved_declarations)
    {
      cout << "UID: " << p.first->getMangledName() << " , declarationName: " << p.second->getName() << endl;
    }
    cout << "Definitions:" << endl;
    for (auto p : UID_to_definitions)
    {
      cout << "UID: " << p.first->getMangledName() << " , definitionName: " << p.second->getName() << endl;
    }
  }
}
