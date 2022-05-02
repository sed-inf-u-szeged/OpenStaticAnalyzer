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

#ifndef _FB2G_RLC_H_
#define _FB2G_RLC_H_

#include <string>
#include <vector>

class RuleConverter{
  public:
    void convertRuleFile(const std::string& messagesXML, const std::string& findbugsXML, const std::vector<std::string>& rulesXMLs, const std::string& rulName, const std::string& rulConfig, const std::string& idsFileName);
    static void formatMetricId(std::string& id);
};

#endif
