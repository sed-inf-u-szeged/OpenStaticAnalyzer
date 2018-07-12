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

#include <fstream>
#include <sstream>
#include <algorithm>

#include <io/inc/SimpleXmlIO.h>
#include <io/inc/messages.h>
#include "Exception.h"

using namespace std;


namespace columbus {  namespace io {

  string replaceCharsToXML(const string& attribute_changed) {
    string ret;
    size_t len = attribute_changed.size();
    char c;
    for (size_t i = 0; i < len; ++i) {
      c = attribute_changed[i];
      switch(c) {
        case '<':
          ret += "&lt;";
          break;
        case '>':
          ret += "&gt;";
          break;
        case '"':
            ret += "&quot;";
          break;
        case '\'':
            ret += "&apos;";
          break;
        case '&':
          ret += "&amp;";
          break;
        case '\t':
          ret += "&#x09;";
          break;
        case '\n':
          ret += "&#x0A;";
          break;
        case '\r':
          ret += "&#x0D;";
          break;
        default:
          ret += c;
          break;
      }
    }
    return ret;
  }

  string replaceXMLToChars(const string& data) {
    string ret;
    string subString;
    string sign;
    string cpData = data;
    while(true) {
      size_t locationAt = cpData.find_first_of('&');
      ret += cpData.substr(0, locationAt);
      if(locationAt == string::npos)
        break;
      subString = cpData.substr(locationAt);
      size_t locationQ = subString.find_first_of(';');
      if(locationQ == string::npos) {
        ret += subString;
        break;
      }
      sign = subString.substr(0, locationQ + 1);

      cpData = subString.substr(locationQ + 1);

      
      if(sign == "&amp;") {
        ret += "&";
        continue;
      }
      if(sign == "&lt;") {
        ret += "<";
        continue;
      }
      if(sign == "&gt;") {
        ret += ">";
        continue;
      }
      if(sign == "&quot;") {
        ret += "\"";
        continue;
      }
      if(sign == "&apos;") {
        ret += "'";
        continue;
      }
      if(sign == "&#x09;") {
        ret += "\t";
        continue;
      }
      if(sign == "&#x0A;") {
        ret += "\n";
        continue;
      }
      if(sign == "&#x0D;") {
        ret += "\r";
        continue;
      }
    }
    return ret;
  }


  SimpleXmlIO::SimpleXmlIO() :
    IOBase(OperationMode::text),
    lastOp(xwsNone),
    xmlElementStack()
  {
  }

  SimpleXmlIO::SimpleXmlIO(bool toError) :
    IOBase(OperationMode::text),
    lastOp(xwsNone),
    xmlElementStack()
  {
    open(toError);
  }

  SimpleXmlIO::SimpleXmlIO(const string& filename, eOpenMode mode) :
    IOBase(OperationMode::text),
    lastOp(xwsNone),
    xmlElementStack()
  {
    if( mode != IOBase::omWrite )
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_OPEN_XML_ONLY_WRITE);
    open(filename,mode);
  }

  SimpleXmlIO::SimpleXmlIO(const char *filename, eOpenMode mode) : 
    IOBase(OperationMode::text),
    lastOp(xwsNone),
    xmlElementStack()
  {
    if( mode != IOBase::omWrite )
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_OPEN_XML_ONLY_WRITE);
    open(filename,mode);
  }

  SimpleXmlIO::~SimpleXmlIO() {
    
    if (lastOp == xwsOpenTagOp) {
      *stream << "/>" << '\n';
      xmlElementStack.pop();
    } else if (lastOp == xwsContent) {
      *stream << "</" << xmlElementStack.top() << ">" << '\n';
      xmlElementStack.pop();
    }
    
    while (!xmlElementStack.empty()) {
      putTabs(1);
      *stream << "</" << xmlElementStack.top() << ">" << '\n';
      xmlElementStack.pop();
    }
  }

  void SimpleXmlIO::putTabs(int deletedNum){
    for(size_t i = 0; i < xmlElementStack.size() - deletedNum; i++) {
      *stream << "  ";
    }
  }

  void SimpleXmlIO::writeXMLDeclaration(const string& version, const string& encoding) {
    if( (lastOp != xwsNone) && (lastOp != xwsDTD) )
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_XML_DECLARATION_TOP);
    try {
      (*stream) << "<?xml version=\"" << version << "\" encoding=\"" << encoding << "\"?>" << '\n';
      lastOp = xwsEndLOp;
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
  }

  void SimpleXmlIO::writeCommentTag(const string& comment) {
    try {
    if(lastOp == xwsOpenTagOp)
      *stream << ">" << '\n';
    if(lastOp != xwsContent)
      putTabs();
      
    *stream << "<!-- " << replaceCharsToXML(comment) << " -->" << '\n';
    lastOp = xwsEndLOp;
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
  }
 
  void SimpleXmlIO::writeBeginElement(const string& element) {
    try {
      if(lastOp == xwsOpenTagOp)
        *stream << ">" << '\n';
      if(lastOp != xwsContent)
        putTabs();


      string xmlElement = replaceCharsToXML(element);

      *stream << "<" << xmlElement;

      xmlElementStack.push(xmlElement);
      lastOp = xwsOpenTagOp;
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
  }

  void SimpleXmlIO::writeEndElement() {
    if(xmlElementStack.empty())
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_XML_TAG_NOT_FOUND);
    try {
      if( lastOp == xwsOpenTagOp ) {
        *stream << "/>" << '\n';
        xmlElementStack.pop();
      } else {
        const string& element = xmlElementStack.top();
        if(lastOp != xwsContent)
          putTabs(1);
        *stream << "</" << element << ">" << '\n';
        xmlElementStack.pop();
      }
      lastOp = xwsEndLOp;
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION,fail.what());
    }
  }

  void SimpleXmlIO::writeElementContent(const string& content) {
    if(xmlElementStack.empty())
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_XML_TAG_NOT_FOUND);
    try {
      if( lastOp == xwsOpenTagOp ) {
        *stream << ">";
      } 

      *stream << replaceCharsToXML(content) ;

      lastOp = xwsContent;
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
  }

  template<class Attr>
  void SimpleXmlIO::writeAttributeByTemplate(const string& attribute, Attr value) {
    try {
      if( lastOp == xwsOpenTagOp) {
        *stream << " " << replaceCharsToXML(attribute) << " = " << "\"" << value << "\"";
      } else {
        throw IOException(COLUMBUS_LOCATION, CMSG_EX_XML_LAST_OPERATION);
      }
      lastOp = xwsOpenTagOp;
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
  }

  void SimpleXmlIO::writeAttribute(const string& attribute, const char* value) {
    writeAttributeByTemplate(attribute, replaceCharsToXML(value));
  }


  void SimpleXmlIO::writeAttribute(const string& attribute, const string& value) {
    writeAttributeByTemplate(attribute, replaceCharsToXML(value));
  }

  void SimpleXmlIO::writeAttribute(const string& attribute, bool value) {
    writeAttributeByTemplate(attribute,value);
  }

  void SimpleXmlIO::writeAttribute(const string& attribute, int value) {
    writeAttributeByTemplate(attribute,value);
  }

  void SimpleXmlIO::writeAttribute(const string& attribute, long long value) {
    writeAttributeByTemplate(attribute,value);
  }

  void SimpleXmlIO::writeAttribute(const string& attribute, double value) {
    writeAttributeByTemplate(attribute,value);
  }

  void SimpleXmlIO::writeAttribute(const string& attribute, void* value) {
    writeAttributeByTemplate(attribute, value);
  }

  void SimpleXmlIO::writeDTDTag(const string& text) {
    if( (lastOp != xwsNone) )
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_XML_DTD_TOP);
    try {
      *stream << "<!DOCTYPE " << text << " >" << '\n';
    } catch(const exception& fail) {
      throw IOException(COLUMBUS_LOCATION, fail.what());
    }
    lastOp = xwsDTD;
  }

  void SimpleXmlIO::close() {
    while(!xmlElementStack.empty()) {
      writeEndElement();
    }
    IOBase::close();
  }

  int countQuotes(const string& text) {
    int count = 0;
    size_t len = text.size();
    for (size_t i = 0; i < len; ++i) {
      if(text[i] == '\"')
        ++count;
    }
    return count;
  }

  void parseTag(const string& tag, SimpleXmlIO::XmlHandler& xmlHandler) {
    SimpleXmlIO::XmlHandler::AttributeList attributeList;
    string buffer;
    if(!tag.empty()) {
      string name;
      if(tag[0] == '/') {
        // get name
        stringstream tag_stream(tag);

        tag_stream >> buffer;
        name = buffer.substr(1);
        xmlHandler.endTag( replaceXMLToChars(name) );
        return;
      } else {
        bool isClosed = false;
        bool isXmlHead = false;
        // get name
        string tag_copy;
        if(tag[tag.length()-1] == '/') {
          tag_copy = tag.substr(0,tag.length()-1);
          isClosed = true;
        } else {
          tag_copy = tag;
        }

        if( (tag[0] == '?') && (tag[tag.length()-1] == '?') ) {
          tag_copy = tag.substr(1,tag.length()-2);
          isXmlHead = true;
        }

        stringstream tag_stream(tag_copy);

        tag_stream >> buffer;
        name = buffer;
        // get attributes
        SimpleXmlIO::XmlHandler::AttributeList attrList;
        while(!tag_stream.eof()) {
          string attribute;
          buffer.clear();

          size_t eq_pos;
          size_t length;
          do {
            if(tag_stream.eof()) break;
            do {
              tag_stream >> buffer;
              attribute += buffer;
              eq_pos = attribute.find_first_of("=");
              length = attribute.length()-1;
              if(tag_stream.eof()) break;
            }while( !((eq_pos != string::npos) && (length > eq_pos) && !buffer.empty()) );
            // attribute end is not ", add lose space
            if(attribute.empty()) {
                break;
            }
            if(attribute[length] != '\"' || countQuotes(attribute) < 2) {
              attribute += " ";
            }
          // if attribute don't contains 2 " is not ended
          }while(attribute[length] != '\"' || countQuotes(attribute) < 2);
          // split attribute
          if(attribute.empty())
            continue;
          string attribute_name = attribute.substr(0,attribute.find('='));
          string attribute_value = attribute.substr(attribute.find('=')+1);
          if( (attribute_value[0] != '"') || (attribute_value[attribute_value.length()-1] != '"') || (attribute_value.length() < 2) ) {
            string message("Wrong attribute format! (\" not found) ");
            message += name + " " + attribute_name + " " + attribute_value + "on tag: " + tag;
            throw IOException(COLUMBUS_LOCATION, message.c_str());
          }
          attribute_value = attribute_value.substr(1,attribute_value.length()-2);
          // add atribute to list
          attributeList.push_back(make_pair(replaceXMLToChars(attribute_name), replaceXMLToChars(attribute_value)) );


        }
        // call begin tag
        if(!isXmlHead) {
          xmlHandler.beginTag(replaceXMLToChars(name), attributeList);
        } else {
          string version;
          string encoding;
          for(SimpleXmlIO::XmlHandler::AttributeList::const_iterator it = attributeList.begin(); it != attributeList.end(); it++ ) {
            if(it->first == "version")
              version = it->second;
            if(it->first == "encoding")
              encoding = it->second;
          }
          xmlHandler.versionAndEncoding(version,encoding);
        }
        // call end of tag if it is closed 
        if(isClosed && !isXmlHead)
          xmlHandler.endTag(replaceXMLToChars(name) );
      }
    } else {
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_XML_WRONG_TAG);
    }
  }

  void loadXml(const string& filename, SimpleXmlIO::XmlHandler& XmlHandler) {
    ifstream xml(filename.c_str(),ios_base::in);
    if(xml.fail())
      throw IOException(COLUMBUS_LOCATION, CMSG_EX_OPEN_FILE + filename);
    // find next tag < >
    while(!xml.eof() ) {
      string buffer;
      string content;
      getline(xml,buffer,'<');
    
      content = buffer;
      if(xml.eof()) break;
      buffer.clear();
      getline(xml,buffer,'>');
      // xml > inside apostrophes
      while(countQuotes(buffer)%2 != 0) {
        string bufferAP;
        getline(xml,bufferAP,'>');
        buffer += ">" + bufferAP;
        if(xml.eof()) throw IOException(COLUMBUS_LOCATION, CMSG_EX_XML_WRONG_TAG_FORMAT + buffer);;
      }
      // xml command, skyped
      if (buffer.size() > 2 && buffer[0] == '!' && buffer[1] != '-') {
        continue;
      }
      // xml comment
      if (buffer.size() > 3 && buffer[0] == '!' && buffer[1] == '-' && buffer[2] == '-' ) {
        while(buffer[buffer.size()-1] != '-' && buffer[buffer.size()-2] != '-') {
          buffer.clear();
          getline(xml,buffer,'>');
        }
        continue;
      } else {
        if(!content.empty())
          XmlHandler.content(content);
        parseTag(buffer,XmlHandler);
      }
    }
  }

}}

