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

#ifndef _CPPCHECK2GRAPH_RULECONVERTER_H_
#define _CPPCHECK2GRAPH_RULECONVERTER_H_


#include <rul/inc/RulHandler.h>

#include "XMLParser.h"


namespace columbus {  namespace cppcheck2graph {
  /**
   * \brief Class for generating rul file from cppcheck error list.
   */
  class RuleConverter {
  public:
    /**
     * \brief Constructor
     *
     * \param rulConfig Name of the rul config.
     */
    RuleConverter(const std::string& rulConfig);

    virtual ~RuleConverter();

    /**
     * \brief Save the rules into a file.
     *
     * \param rulFileName The output file name.
     */
    void saveRulFile(const std::string& rulFileName);

    /**
     * \brief Process the cppcheck error list file.
     *
     * \param configFileName The config file name.
     * \param errorListFileName The error list file name.
     * \param errorGroupsFileName The error grouping file name.
     */
    void process(const std::string& configFileName, const std::string& errorListFileName, const std::string& errorGroupsFileName);

  private:
    XMLParser parser;

    rul::RulHandler rulHandler;
    
    std::map<std::string, std::string> ruleIdMap;
    std::map<std::string, std::string> ruleNameMap;
    std::map<std::string, bool> ruleEnabled;

  };

}}

#endif
