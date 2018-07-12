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

#include "../inc/XMLParser.h"
#include "../inc/messages.h"

using namespace std;
using namespace common;
using namespace columbus;
using namespace columbus::eslint2graph;


XMLParser::XMLParser(){
  try {
    XMLPlatformUtils::Initialize();
  }catch (const XMLException& toCatch) {
    char* message = XMLString::transcode(toCatch.getMessage());
    string exceptionMessage = message;
    XMLString::release(&message);
    throw Exception("XMLParser::XMLParser", exceptionMessage);
  }
}

void XMLParser::terminate() {
  try {
    XMLPlatformUtils::Terminate();
  }
  catch (const XMLException& toCatch) {
    char* message = XMLString::transcode(toCatch.getMessage());
    string exceptionMessage = message;
    XMLString::release(&message);
    throw Exception("XMLParser::~XMLParser", exceptionMessage);
  }
}

XMLParser::~XMLParser() {
  terminate();
}

void XMLParser::parseXML(const std::string& file, DefaultHandler* handler) {
  
  SAX2XMLReader* parser = XMLReaderFactory::createXMLReader();
  parser->setFeature(XMLUni::fgSAX2CoreValidation, true);
  parser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
  parser->setFeature(XMLUni::fgXercesSchema, false);
  parser->setFeature(XMLUni::fgXercesLoadExternalDTD, false);

  parser->setContentHandler(handler);
  parser->setErrorHandler(handler);

  try {
    LocalFileInputSource source(XMLString::transcode(file.c_str()));
    parser->parse(source);
  }catch (const XMLException& toCatch) {
    char* message = XMLString::transcode(toCatch.getMessage());
    string exceptionMessage = message;
    XMLString::release(&message);
    throw Exception("XMLParser::parseXML",exceptionMessage);
  }catch (const SAXParseException& toCatch) {
    char* message = XMLString::transcode(toCatch.getMessage());
    string exceptionMessage = message;
    XMLString::release(&message);
    throw Exception("XMLParser::parseXML",exceptionMessage);
  }
  delete parser;
}
