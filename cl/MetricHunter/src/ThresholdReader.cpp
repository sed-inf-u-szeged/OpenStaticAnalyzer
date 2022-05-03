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

#include "../inc/ThresholdReader.h"
#include <common/inc/WriteMessage.h>

#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMDocumentType.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>


#include <iostream>
#include <stack>
#include <set>
#include <vector>
#include <algorithm>
#include <io/inc/SimpleXmlIO.h>
#include <common/inc/StringSup.h>

using namespace std;
using namespace common;
XERCES_CPP_NAMESPACE_USE

#define _MID        "Mid"
#define _RELATION   "Relation"
#define _VALUE      "Value"
#define _ENTITY     "Entity"
#define _TAG        "threshold"
  
  namespace columbus { namespace rul {

    ThresholdReader::ThresholdReader(const string& trsFileName) : trs(), _filename(trsFileName), _xerces_inited(true) {
      xercesInit();
      parseXML();
    }

    ThresholdReader::~ThresholdReader() {
      if(_xerces_inited) {
        xercesTerminate();
      }
    }

    int ThresholdReader::xercesInited = 0;

    void ThresholdReader::xercesInit() {
      if(xercesInited == 0) {
        try {
          XMLPlatformUtils::Initialize();
        }
        catch (const XMLException& toCatch) {
          char* message = XMLString::transcode(toCatch.getMessage());
          string messageString = message;
          XMLString::release(&message);
          throw ThresholdReaderException("xercesInit", messageString);
        }
      }
      ++xercesInited;
    }

    void ThresholdReader::xercesTerminate() {
      --xercesInited;
      if(xercesInited == 0) {
        try {
          XMLPlatformUtils::Terminate();
        } catch (const XMLException& toCatch) {
          char* message = XMLString::transcode(toCatch.getMessage());
          string messageString = message;
          XMLString::release(&message);
          throw ThresholdReaderException("xercesTerminate", messageString);
        }
      }
    }


    void ThresholdReader::parseXML() {
      xercesc::XercesDOMParser *parser = new XercesDOMParser;

      parser->setValidationScheme( XercesDOMParser::Val_Never );
      parser->setDoNamespaces( false );
      parser->setDoSchema( false );
      parser->setLoadExternalDTD( false );

      XMLCh* tag = XMLString::transcode(_TAG);

      XMLCh* midCh = XMLString::transcode(_MID);
      XMLCh* relationCh = XMLString::transcode(_RELATION);
      XMLCh* valueCh = XMLString::transcode(_VALUE);
      XMLCh* entityCh = XMLString::transcode(_ENTITY);

      try {
        parser->parse(_filename.c_str());
        DOMDocument* xmlDoc = parser->getDocument();
        if (xmlDoc == NULL)
          throw ThresholdReaderException(COLUMBUS_LOCATION, "Failed to parse file: " + _filename);
          
        DOMElement* elementRoot = xmlDoc->getDocumentElement();
        if (elementRoot == NULL) 
          throw ThresholdReaderException(COLUMBUS_LOCATION, "Empty XML document");

        DOMNodeList* children = elementRoot->getChildNodes();
        const  XMLSize_t nodeCount = children->getLength();

        std::string mid;
        std::string relation;
        std::string value;
        std::string entity;

        for( XMLSize_t xx = 0; xx < nodeCount; ++xx ) {
          DOMNode* currentNode = children->item(xx);

          if( currentNode->getNodeType() && currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) {
            DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >( currentNode );
            if( XMLString::equals(currentElement->getTagName(), tag)) {

              const XMLCh* xmlch_OptionA = currentElement->getAttribute(midCh);
              mid = XMLString::transcode(xmlch_OptionA);

              const XMLCh* xmlch_OptionB = currentElement->getAttribute(relationCh);
              relation = XMLString::transcode(xmlch_OptionB);

              const XMLCh* xmlch_OptionC = currentElement->getAttribute(valueCh);
              value = XMLString::transcode(xmlch_OptionC);

              const XMLCh* xmlch_OptionD = currentElement->getAttribute(entityCh);
              entity = XMLString::transcode(xmlch_OptionD);
              vector<string> ruleEntities;
              common::split(entity, ruleEntities, ',');
              
              entities.insert(ruleEntities.begin(), ruleEntities.end());
                
              //There we create a temp object and push into the vector
              trs.push_back(Threshold(mid,relation,value, ruleEntities));

            }
          }
        }

        XMLString::release(&tag);
        XMLString::release(&midCh);
        XMLString::release(&relationCh);
        XMLString::release(&valueCh);
        XMLString::release(&entityCh);
      }
      catch( xercesc::XMLException& e )
      {
        char* message = XMLString::transcode(e.getMessage());
        string messageString = message;
        XMLString::release(&message);
        throw ThresholdReaderException("Xerces Exception", messageString);
      }

      delete parser;
    } //parseXMl

} } //rul, columbus
