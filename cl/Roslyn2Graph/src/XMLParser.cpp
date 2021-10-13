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

#include <Exception.h>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include "../inc/XMLParser.h"

using namespace std;
using namespace columbus;
using namespace columbus::roslyn2graph;

XERCES_CPP_NAMESPACE_USE

XMLParser::XMLParser(){
}

XMLParser::~XMLParser(){
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
    throw Exception(COLUMBUS_LOCATION, exceptionMessage);
  }catch (const SAXParseException& toCatch) {
    char* message = XMLString::transcode(toCatch.getMessage());
    string exceptionMessage = message;
    XMLString::release(&message);
    throw Exception(COLUMBUS_LOCATION, exceptionMessage);
  }

  delete parser;
}
