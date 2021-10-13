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

#define PROGRAM_NAME "FindBugs2Graph"
#define EXECUTABLE_NAME "FindBugs2Graph"

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/util/XMLString.hpp>
#include <common/inc/WriteMessage.h>
#include <common/inc/Stat.h>
#include <Exception.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <list>
#include "../inc/RuleConverter.h"
#include "../inc/messages.h"
#include "../inc/ResultConverter.h"
#include "MainCommon.h"

using namespace std;
using namespace common;
using namespace columbus;


XERCES_CPP_NAMESPACE_USE


static bool makerul = false;
static string outTxt;
static string outGraph;
static string rulFile;
static string rulConfig = "Default";
static string limFile;
static bool exportRul;
static string inputFile;
static string messagesXML;
static string findbugsXML;
static string rulesXML;
static string idsTxt;

static bool ppMakeRul (const Option *o, char *argv[]) {
  makerul = true;
  messagesXML = argv[0];
  findbugsXML = argv[1];
  rulesXML = argv[2];
  return true;
}

static bool ppIds(const Option *o, char *argv[]) {
  idsTxt = argv[0];
  return true;
}

static bool ppGraph (const Option *o, char *argv[]) {
  outGraph = argv[0];
  return true;
}

static bool ppOut (const Option *o, char *argv[]) {
  outTxt = argv[0];
  return true;
}

static bool ppLimFile (const Option *o, char *argv[]) {
  limFile = argv[0];
  return true;
}

static bool ppRul (const Option *o, char *argv[]) {
  rulFile = argv[0];
  return true;
}

static bool ppRulConfig (const Option *o, char *argv[]) {
  rulConfig = argv[0];
  return true;
}

static bool ppExportRul(const Option *o, char *argv[]) {
  exportRul = true;
  return true;
}

static void ppFile(char *filename) {
  inputFile = filename;
}

const Option OPTIONS_OBJ [] = {
  { false,  "-makerul",         3, "messages.xml findbugs.xml rules-findbugs.xml", 0,  OT_WS,  ppMakeRul,  NULL,   "Makes rul file from the two xml files of the findbugs and the configuration xml of the sonar." },
  { false,  "-ids",             1, "fb_ids.txt",        0,  OT_WC,    ppIds,            NULL,   "File which contains previous rule ids."},
  { false,  "-graph",           1, "file",              1,  OT_WC,    ppGraph,          NULL,   "Save binary graph output."},
  { false,  "-out",             1, "file",              0,  OT_WC,    ppOut,            NULL,   "Specify the name of the output file. The list of rule violations will be dumped in it.\n"},
  CL_LIM
  CL_RUL_AND_RULCONFIG("FindBugs.rul")
  CL_EXPORTRUL
  COMMON_CL_ARGS
};



bool parseXML(const string& filename, DefaultHandler* handler) {
  SAX2XMLReader* parser = XMLReaderFactory::createXMLReader();
  parser->setFeature(XMLUni::fgSAX2CoreValidation, true);
  parser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
  parser->setFeature(XMLUni::fgXercesSchema, false);
  parser->setFeature(XMLUni::fgXercesLoadExternalDTD, false);

  parser->setContentHandler(handler);
  parser->setErrorHandler(handler);

  try {
      parser->parse(filename.c_str());
  }
  catch (const XMLException& toCatch) {
      char* message = XMLString::transcode(toCatch.getMessage());
      WriteMsg::write(CMSG_FILE_PARSE_ERROR, filename.c_str(), message);
      XMLString::release(&message);
      return false;
  }
  catch (const SAXParseException& toCatch) {
      char* message = XMLString::transcode(toCatch.getMessage());
      WriteMsg::write(CMSG_FILE_PARSE_ERROR, filename.c_str(), message);
      XMLString::release(&message);
      return false;
  }

  delete parser;
  return true;
}

bool getAttr(const Attributes& attrs, const char* attrName, string& val) {
  bool ret = false;
  XMLCh* nameCh = XMLString::transcode(attrName);
  char* value = XMLString::transcode(attrs.getValue(nameCh));
  if( value != NULL ) {
    val = value;
    ret = true;
  }
  XMLString::release(&nameCh);
  XMLString::release(&value);
  return ret;
}


int main(int argc, char* argv[]) {

  MAIN_BEGIN
    MainInit(argc, argv, "-");

    if (!makerul) {
      if (inputFile.empty()) {
        WriteMsg::write(CMSG_FINDBUGS2GRAPH_MISSING_ASG);
        clError();
      }

      if (limFile.empty()) {
        WriteMsg::write(CMSG_FINDBUGS2GRAPH_MISSING_LIM);
        clError();
      }
    }
    // init xerces
    try {
      XMLPlatformUtils::Initialize();
    }
    catch (const XMLException& toCatch) {
      char* message = XMLString::transcode(toCatch.getMessage());
      WriteMsg::write(CMSG_XERCES_ERROR, message);
      string exceptionMessage = "Error during XERCES initialization! ";
      exceptionMessage += message;
      XMLString::release(&message);
      throw Exception("initxerces()", exceptionMessage);
    }


    //make rule
    if (makerul) {
      RuleConverter ruleConverter;
      ruleConverter.convertRuleFile(messagesXML, findbugsXML, rulesXML, rulFile, rulConfig, idsTxt);
    } else {

      //process findbugs output
      if (!outTxt.empty()) {
         ofstream txtOutputStream(outTxt.c_str(), std::ofstream::trunc);
      }
      ResultConverter rc(limFile, rulFile, rulConfig, outTxt);

      rc.buildtree(exportRul);
      rc.collectData(inputFile);
      rc.aggregateWarnings(true);

      rc.saveGraph(outGraph);
    }

    // terminate xerces
    XMLPlatformUtils::Terminate();
    
  MAIN_END

  return 0;
}
