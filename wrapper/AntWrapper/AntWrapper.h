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

#ifndef __AntWrapper_H
#define __AntWrapper_H

#include "AbstractWrapperLib/inc/abstractwrapper/AbstractWrapper.h"

namespace ColumbusWrappers {

class AntWrapper: public AbstractWrapper {
  private:
    bool printTempBuildXml(std::string file, std::string basedir, std::string defaultTarget, std::string projectName);
    int buildOriginal(const std::string& antParameters);
    std::string getAttributeValue(const std::string& tag, const std::string attr);
    bool parsingParameters(int argc, char** argv, std::string& antParameters, std::string& filename, std::string& basedir, std::string& defaultTarget, std::string& projectName);
    bool loadLogFile();
  public:
    AntWrapper(std::string);
    bool process(int argc, char** argv);
};


}

#endif

