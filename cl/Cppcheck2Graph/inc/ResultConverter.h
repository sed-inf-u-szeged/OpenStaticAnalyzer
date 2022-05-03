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

#ifndef _CPPCHECK2GRAPH_RESULTCONVERTER_H_
#define _CPPCHECK2GRAPH_RESULTCONVERTER_H_

#include <lim/inc/lim.h>
#include <rul/inc/RulHandler.h>
#include <graph/inc/graph.h>
#include <strtable/inc/StrTable.h>
#include <graphsupport/inc/Metric.h>

#include "XMLParser.h"


namespace columbus {  namespace cppcheck2graph {
  /**
   * \brief Class for converting the cppcheck output into warnings, and adding it into the graph.
   */
  class ResultConverter: public DefaultHandler {
  public:
    /**
     * \brief Constructor.
     *
     * \param limFileName The name of the lim file.
     * \param txtOutFile  The name of the plain text output file.
     * \param rulFileName The name of the rul file.
     * \param rulConfig   Name of the rul config.
     * \param exportRul   Build the ruls into the graph.
     */
    ResultConverter(const std::string& limFileName, const std::string& txtOutFile, const std::string& rulFileName, const std::string& rulConfig, const bool exportRul, const std::string& changePathFrom, const std::string& changePathTo);

    virtual ~ResultConverter();

    /**
     * \brief Process an output file of cppcheck.
     *
     * \param resultFileName The name of the file.
     */
    void process(const std::string& resultFileName);

    /**
     * \brief Aggregate warnings.
     */
    void aggregateWarnings();

    /**
     * \brief Save the result graph into file.
     *
     * \param graphOutputFilename The name of the output file.
     * \param createXMLdump       Create xml dump.
     */
    void saveResultGraph(const std::string& graphOutputFilename, bool createXMLdump);

    /**
     * \brief Processing the xml opening tags, and creating warnings from the corresponding tags.
     */
    virtual void startElement (const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname, const Attributes &attrs);

    /**
     * \brief Processing the xml ending tags, and creating warnings from the corresponding tags.
     */
    virtual void endElement(const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname);

  private:
    XMLParser parser;

    rul::RulHandler rulHandler;
    RefDistributorStrTable limStrTable;
    lim::asg::Factory limFactory;
    graph::Graph graph;
    graphsupport::GraphRangeIndexer& graphIndexer;
    
    // Variables for xml attribute names.
    XMLCh* ruleIdXMLCh;
    XMLCh* warningMsgXMLCh;
    XMLCh* locationFileXMLCh;
    XMLCh* locationFile0XMLCh;
    XMLCh* locationLineXMLCh;

    const std::string& changePathFrom;
    const std::string& changePathTo;
    std::string txtOutFile;

    // Data for the current warning.
    std::string id;
    std::string warningText;
    graphsupport::WarningCache warningCache;
    /**
     * \brief Structure for a warning location.
     */
    struct Location{
      std::string file;
      int line;
    };

    // The locations for the current warning.
    std::list<Location> locations;

    /**
     * \brief Add current warning into the graph.
     */
    void addWarning();
  };

}}


#endif
