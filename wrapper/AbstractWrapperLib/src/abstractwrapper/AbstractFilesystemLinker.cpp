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


#include "../../inc/abstractwrapper/AbstractFilesystemLinker.h"
#include "../../inc/paramsup/ArParamsup.h"

#include <boost/filesystem.hpp>
#include <common/inc/FileSup.h>

using namespace std;


namespace ColumbusWrappers
{

  AbstractFSLinker::AbstractFSLinker(const std::string& configfile) : AbstractWrapper(configfile)
  {
    readConfig();
  }

  void AbstractFSLinker::readConfig() {
  }

  void AbstractFSLinker::createLink(const std::string &target, const std::string &link, const std::vector<string> &exts) const
  {
    string targetName = common::pathCanonicalize(target);
    insertDir(targetName, false);

    string linkName = link;
    insertDir(linkName, true);


    for (const auto& ext : exts)
    {
      boost::system::error_code ec;
      boost::filesystem::create_symlink(targetName + ext, linkName + ext, ec);
    }
  }

  bool AbstractFSLinker::executeFSLink(const ColumbusWrappers::LnArgs& lnArgs) const
  {
    writeDebugMsg("AbstractFSLinker", common::WriteMsg::mlDDDebug, "Form: %d", lnArgs.form);


    if (lnArgs.form == 1)
    {
      // ln [OPTION]... [-T] TARGET LINK_NAME   (1st form)
      const string& target = lnArgs.targets.front();

      if (ArWrapperSup::isObjectFile(target))
        createLink(target, lnArgs.linkName, { ".ast", ".ast.err", ".ast.ct.err", ".ast.comment" });

      else if (ArWrapperSup::isArchiveFile(target))
        createLink(target, lnArgs.linkName, { ".aast" });
    }
    else if (lnArgs.form == 2)
    {
      // ln [OPTION]... TARGET                  (2nd form)
      const string& target = lnArgs.targets.front();
      const string link = common::pathFindFileName(target);

      if (ArWrapperSup::isObjectFile(target))
        createLink(target, link, { ".ast", ".ast.err", ".ast.ct.err", ".ast.comment" });

      else if (ArWrapperSup::isArchiveFile(target))
        createLink(target, link, { ".aast" });
    }
    else if (lnArgs.form == 3)
    {
      // ln [OPTION]... TARGET... DIRECTORY     (3rd form)
    }
    else if (lnArgs.form == 4)
    {
      // ln [OPTION]... -t DIRECTORY TARGET...  (4th form)
    }



    return true;
  }

}


