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

#ifndef _COPY_MOVE_WRAPPER_H_
#define _COPY_MOVE_WRAPPER_H_

#include <AbstractWrapperLib/inc/abstractwrapper/AbstractWrapper.h>

#include <string>
#include <list>

namespace ColumbusWrappers {
  class CopyMoveWrapper : public AbstractWrapper {
  public:
    CopyMoveWrapper(std::string configfile);

    bool process(int argc, char** argv);

  private:
    void checkExtension(std::string& file, std::list<std::string>& fileList, std::string& target, bool isFilter = false);

    void getFiles(std::list<std::string>& sourceFiles, std::string& target, std::list<std::string>& options, std::list<std::string> temp_argv);

    bool loadListFile(std::string& file, std::list<std::string>& fileList);

    void saveListFile(std::string& file, std::list<std::string>& fileList);

    void updateListFile(std::string& source, std::string& target);

    void updateListFile(std::string& source, std::string& target, std::string& listFile, bool isDirectory = false);

    void addToListFile(std::string& target);

    void addToListFile(std::string& source, std::string& listFile);

    std::string acsi_file;
    std::string csi_file;
    std::string lcsi_file;
  };
}

#endif