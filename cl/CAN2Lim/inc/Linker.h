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

#ifndef _CAN2LIM_LINKER_H
#define _CAN2LIM_LINKER_H

#include <lim/inc/lim.h>
#include <unordered_set>
#include "MergeUID.h"

class GlobalASTConversionInfo;

/*  This singleton class is responsible for linking. Linking in our case means just to apply Declares edges from
    Declarations to Definitions in the LIM tree.
    Linking in compilers usually happens per component. Here we link all components at once, at the end of the conversion. 
    
    The workflow is:
      1, During the visitation of the source file(s)
          a, add each unresolved declaration to unresolved_declarations
          b, add each definition to the UID_to_definitions map
          c, build a component_to_files map
      2, Based on the above, at the very end of the CAN2Lim conversion, connect the declarations to definitions by calling
          link_unresolved_declarations()

    But there is one catch right now. It is possibly that the same declaration links to different definitions in different components.
    The LIM schema currently doesn't support this kind of edges (only with variants, which we don't use in current CAN).
    As a result, if such case happens, we simply link the declaration to only one of them. Which is kinda bad, because it makes
    the LIM file dependent on which definition we find last, so it might create silly, sporadic errors in tests.
    The upside is that with this simplification, we can link faster. The SIMPLIFIED_LINKING switch makes the algorithm faster but
    incorrectly (as there is no correct solution anyways).

    TODO: Extend LIM schema or use variants and solve this issue in link_unresolved_declarations(). After that, delete SIMPLIFIED_LINKING.
*/
class Linker {
public:
  static const bool LINKER_DEBUG = false;
  static const bool SIMPLIFIED_LINKING = true;

public:
  GlobalASTConversionInfo &conversionInfo;

  std::vector<std::pair<std::shared_ptr<MergeUID>,columbus::lim::asg::Member*>> unresolved_declarations;
  std::vector<std::pair<std::shared_ptr<MergeUID>,columbus::lim::asg::base::Base*>> unresolved_calls;
  std::vector<std::pair<std::shared_ptr<MergeUID>,columbus::lim::asg::logical::Method*>> unresolved_attribute_accesses;

  std::unordered_multimap<std::shared_ptr<MergeUID>, columbus::lim::asg::Member*, MergeUID::UIDHasher, MergeUID::NoPosUIDEq> UID_to_definitions;

  struct FilePtrComparator {
    bool operator()(const columbus::lim::asg::physical::File* lhs, const columbus::lim::asg::physical::File* rhs) const{
      return lhs->getId() < rhs->getId();
    }
  };
  // The file set must not be unordered, as that would make the order of elements undefined, and that makes the tests fail sporadically (different node order...)
  std::unordered_map<columbus::lim::asg::base::Component*,std::set<columbus::lim::asg::physical::File*,FilePtrComparator>> component_to_files;

  std::unordered_map<columbus::lim::asg::physical::File*,std::set<columbus::lim::asg::base::Component*>> file_to_components;

  // If the decl is a definition this function adds it to UID_to_definitions
  // If it is a declaration inside a cpp file and the clang-tool finds it, it links it immediately to it's definition
  // If it is a declaration and the definition is not found, the declaration is added to unresolved_declarations
  // Note: Declarations in .h files are never bound to definition in a TU. That's because a declaration in a .h file might be linked to
  //       multiple definitions based on the component.
  //void handle_decl(const clang::Decl* decl, std::shared_ptr<clang::metrics::UID> uid, columbus::lim::asg::Member* limNode);

  void add_definition(columbus::lim::asg::Member * limNode, std::shared_ptr<clang::metrics::UID> uid);
  void add_declaration(columbus::lim::asg::Member * limNode, std::shared_ptr<clang::metrics::UID> uid);

  // MUST only be called at the end of the conversion, when unresolved_declarations, UID_to_definitions, component_to_files are filled up.
  // Also, all the files must have their belongsTo edges set properly, otherwise this will not work correctly.
  // Note: It's roughly O(n^2), with SIMPLIFIED_LINKING it's roughly O(n), but it can be done faster if needed to.
  bool link_unresolved_declarations();

  bool link_unresolved_calls();
  
  bool link_unresolved_attribute_accesses();

  static Linker& getInstance(GlobalASTConversionInfo &conversionInfo)
  {
    static Linker instance(conversionInfo);
    return instance;
  }
  
  void print_debug_overview();

public:
  Linker(Linker const&) = delete;
  void operator=(Linker const&) = delete;

private:
  Linker(GlobalASTConversionInfo& conversionInfo) : conversionInfo(conversionInfo) {}
};

#endif