/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2017 Department of Software Engineering - University of Szeged
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

#include <string>
#include <fstream>

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/parsers/AbstractDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>

#if defined(XERCES_NEW_IOSTREAMS)
#include <iostream>
#else
#include <iostream.h>
#endif

#include "CheckerStrategy.h"
#include <rul/inc/RulHandler.h>
#include <common/inc/StringSup.h>
#include <graphsupport/inc/Metric.h>
#include <graphsupport/inc/RulBuilder.h>
#include <graphsupport/inc/GraphConstants.h>
#include <common/inc/WriteMessage.h>
#include "messages.h"

using namespace std;
using namespace columbus;
using namespace common;
using namespace columbus::graph;

XERCES_CPP_NAMESPACE_USE


void CheckerStrategy::loaddom(const char* filename ){
  try{
    if(doc){
      doc->release();
      doc = 0;
    }
    XMLPlatformUtils::Initialize();
  }
  catch (const XMLException& toCatch)
    {
      WriteMsg::write(CMSG_PMD2GRAPH_ERROR_DURING_INIT, XMLString::transcode(toCatch.getMessage()));
      return;
    }

    // Instantiate the DOM parser.
    XercesDOMParser* parser = new XercesDOMParser();
    ErrorHandler*  errHandler = (ErrorHandler*) new HandlerBase();
    parser->setErrorHandler(errHandler);

#ifndef _DEBUG
    try
    {
#endif
      LocalFileInputSource source(XMLString::transcode(filename));
      source.setEncoding(XMLString::transcode("UTF-8"));
      parser->parse(source);
      doc = parser->getDocument();
#ifndef _DEBUG
    }
    catch (const SAXParseException& toCatch)
    {
      WriteMsg::write(CMSG_PMD2GRAPH_ERROR_DURING_PARSING, filename,XMLString::transcode(toCatch.getMessage()));
      if (toCatch.getLineNumber())
        WriteMsg::write(CMSG_PMD2GRAPH_LINE, toCatch.getLineNumber(), toCatch.getColumnNumber());
      exit(1);
    }
    catch (const XMLException& toCatch)
    {
      WriteMsg::write(CMSG_PMD2GRAPH_ERROR_DURING_PARSING, filename, XMLString::transcode(toCatch.getMessage()));
        exit(1);
    }
    catch (const DOMException& toCatch)
    {
      const unsigned int maxChars = 2047;
      XMLCh errText[maxChars + 1];

      WriteMsg::write(CMSG_PMD2GRAPH_ERROR_DURING_PARSING_DOMEX, filename, toCatch.code);

      if (DOMImplementation::loadDOMExceptionMsg(toCatch.code, errText, maxChars))
        WriteMsg::write(CMSG_PMD2GRAPH_EX_MESSAGE, XMLString::transcode(errText));

      exit(1);
    }
    catch (...)
    {
      WriteMsg::write(CMSG_PMD2GRAPH_UNEXPECTED_PARSING_EX, filename);
      exit(1);
    }
#endif
}


void CheckerStrategy::savedom(const char * filename)
{
  try
  {
    static const XMLCh gLS[] = { chLatin_L, chLatin_S, chNull };
    DOMImplementation *impl = DOMImplementationRegistry::getDOMImplementation(gLS);

    DOMLSSerializer* theSerializer = ((DOMImplementationLS*)impl)->createLSSerializer();
    DOMLSOutput *theOutputDesc = ((DOMImplementationLS*)impl)->createLSOutput(); 

    DOMConfiguration *configuration = theSerializer->getDomConfig(); 
    if (configuration->canSetParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true))
      configuration->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true)
      ; 
    if (configuration->canSetParameter(XMLUni::fgDOMXMLDeclaration, true))
      configuration->setParameter(XMLUni::fgDOMXMLDeclaration, true); 

    LocalFileFormatTarget *myFormTarget = new LocalFileFormatTarget(XMLString::transcode(filename)); 
    theOutputDesc->setByteStream(myFormTarget); 
    
    theSerializer->write(doc, theOutputDesc); 
    
    theOutputDesc->release();
    theSerializer->release();

  }
  catch (const XMLException& toCatch)
  {
    WriteMsg::write(CMSG_PMD2GRAPH_ERROR_CREATING_TRANSCODER, XMLString::transcode(toCatch.getMessage()));
    exit(1);
  }
  catch (...)
  {
    WriteMsg::write(CMSG_PMD2GRAPH_ERROR_WRITING_XML_FILE);
    exit(1);
  }
}

void CheckerStrategy::makeCsv(std::string& lim, std::string& rul, std::string& rulConfig, File_Names& file_names, std::string& metrics, std::string& groupedmetrics, std::string& monitor, std::string& checkerbasedir, const std::map<string, string>& levelMap)
{
  mt = new MetricTree(lim, rul, rulConfig, levelMap, graph, graphIndexer);
  mt->buildtree();
}

void CheckerStrategy::makeCsv(std::string& lim, std::string& rul, std::string& rulConfig, File_Names& file_names, std::string& metrics, std::string& groupedmetrics, std::string& monitor, std::string& checkerbasedir) {
  std::map<string, string> levelMap;
  makeCsv(lim, rul, rulConfig, file_names, metrics, groupedmetrics, monitor, checkerbasedir, levelMap) ;
}

void CheckerStrategy::setShortName(std::string& rulename,std::string& shortname, int small /* = 0 */, int ext /* = 0 */ ){
  int tsmall = small;
  for(unsigned int i = 0; i < rulename.size(); i++){
    if( (rulename[i] >= 'A' && rulename[i] <= 'Z')
        ||(rulename[i] >= '0' && rulename[i] <= '9') )
      shortname += rulename[i];
    else if(rulename[i] >= 'a' && rulename[i] <= 'z' && tsmall > 0){
      shortname += rulename[i];
      tsmall--;
    }
  }
  if(ext > 0)
    shortname += toString(ext);
  if(shortname.empty())
    setShortName(rulename,shortname,++small);
  else{
    set<string>::iterator it1 = shortnames.find(shortname);
    set<string>::iterator it2 = shortnames.end();
    if(it1 != it2){
      shortname.clear();
      if(tsmall > 0)
        setShortName(rulename, shortname, ++small, ++ext);
      else
        setShortName(rulename, shortname, ++small);
    }
    else{
      shortnames.insert(shortname);
    }
  }
}

bool CheckerStrategy::getIsNeeded (const std::string& id, const rul::RulHandler& xRulHandler) {
  return xRulHandler.getIsEnabled(id);
}

void CheckerStrategy::saveGraph(const std::string& filename, bool exportRul) {
  if(exportRul)
    graphsupport::buildRulToGraph(graph, *(mt->xRulhandler));
  graph.saveBinary(filename);
}
