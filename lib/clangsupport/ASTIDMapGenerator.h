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

#ifndef _ASTIDMAPGENERATOR_H
#define _ASTIDMAPGENERATOR_H

#include <map>
#include <memory>

namespace clang
{
  class ASTContext;
}

namespace columbus
{
  enum AstNodeType
  {
    STMT,
    DECL
  };

  typedef struct
  {
    std::map<void*, unsigned> node2id;
    std::map<unsigned, std::pair<void*, AstNodeType>> id2node;
  } NodeIDMaps;

  std::shared_ptr<NodeIDMaps> generateNodeIDMaps(const clang::ASTContext& context);

} // namespace columbus
#endif
