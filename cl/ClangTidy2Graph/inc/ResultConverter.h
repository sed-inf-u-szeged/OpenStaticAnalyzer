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

#ifndef _CLANGTIDY2GRAPH_RESULTCONVERTER_H_
#define _CLANGTIDY2GRAPH_RESULTCONVERTER_H_

#include <lim/inc/lim.h>
#include <rul/inc/RulHandler.h>
#include <graph/inc/graph.h>
#include <strtable/inc/StrTable.h>
#include <graphsupport/inc/Metric.h>
#include <io/inc/SimpleXmlIO.h>

using namespace columbus::io;

namespace columbus { namespace clangtidy2graph{
  
  
  struct Note{
      std::string file;
      int line;
      int column;
      std::string message;
  };
  
  /**
   * \brief Structure for a warning.
   */
  struct Warning{
    std::string file;
    int line;
    int column;
    std::string message;
    std::string name;
    
    std::list<Note> notes;
  };
  
  
  //Handler for xml parser
  class Handler : public SimpleXmlIO::XmlHandler{
    public:
      ~Handler();
      /**
       * \brief call, when read a xml begin tag
       * \param name [in] the tag name
       * \param list [in] the tag attruibutes
       */
      void beginTag(const std::string& name, const AttributeList& list);
      
      /**
       * \brief call, when read a xml content
       * \param content [in] the content text
       */
      void content(const std::string& content);
      
      /**
       * \brief call, when read a xml end tag
       * \param name [in] the tag name
       */
      void endTag(const std::string& name);
      
      /**
       * \brief Returns list of warnings
       */
      std::list<Warning> getWarnings();
      
      /**
       * \brief Clear list of warnings
       */
      void clearWarnings();
    
    private:
      bool hasToSkip; //if the location is invalid, then skip whole diagnostic part
      std::string currentTag;
      bool isNote = false;
      
      // List of warnings
      std::list<Warning> warnings;
      
      /**
       * \brief Resolve escape characters.
       * \param content string.
       */
      std::string resolveEscapeChars(std::string content);
  };
  
  class ResultConverter{
    
  public:
  
    /**
     * \brief Constructor
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
     * \brief Process an output file of clang-tidy
     *
     * \param resultFileName The name of the file.
     */
    void process(const std::string& resultFileName);
    
    
    /**
     * \brief Save the result graph into file.
     *
     * \param graphOutputFilename The name of the output file.
     * \param createXMLdump       Create xml dump.
     */
    void saveResultGraph(const std::string& graphOutputFilename, bool createXMLdump);
    
    /**
     * \brief Aggregate warnings.
     */
    void aggregateWarnings();
        
  private:
    Handler handler;
        
    rul::RulHandler rulHandler;
    RefDistributorStrTable limStrTable;
    lim::asg::Factory limFactory;
    graph::Graph graph;
    graphsupport::GraphRangeIndexer& graphIndexer;
    
    const std::string& changePathFrom;
    const std::string& changePathTo;
    std::string txtOutFile;
    graphsupport::WarningCache warningCache;
    
    int num_notes = 0, unable_to_add = 0, not_found = 0, success = 0, num_of_warnings = 0, not_defined = 0, invalid_node = 0, already_added = 0; //DEBUG

    /**
     * \brief Add a warning into the graph.
     */
    void addWarning(Warning& warning);
    
  };
  
  
}} //namespace end: columbus, clangtidy2graph


#endif
