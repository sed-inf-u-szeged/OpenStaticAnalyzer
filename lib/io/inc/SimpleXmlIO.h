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

#ifndef SimpleXmlIOIO_H
#define SimpleXmlIOIO_H

#include <io/inc/ioBase.h>
#include <stack>
#include <list>

/**
* \file SimpleXmlIO.h
* \brief Contains SimpleXmlIO declaration
*/

namespace columbus {  namespace io {

  class SimpleXmlIO : virtual public IOBase{

    public:

      class XmlHandler {
      public:
          typedef std::list<std::pair<std::string,std::string> > AttributeList; // a tag attributes (name,value)

        public:
          /**
          * \brief construcotr
          */
          XmlHandler();

          /**
          * \brief destructor
          */
          virtual ~XmlHandler();

          /**
          * \brief call, when read a xml begin tag
          * \param name [in] the tag name
          * \param list [in] the tag attruibutes
          */
          virtual void beginTag(const std::string& name, const AttributeList& list);

          /**
          * \brief call, when read a xml end tag
          * \param name [in] the tag name
          */
          virtual void endTag(const std::string& name);

          /**
          * \brief call, when read a xml content
          * \param content [in] the content text
          */
          virtual void content(const std::string& content);

          /**
          * \brief call, when read a <?xml version = "ver" encoding = "enc" ?>
          * \param version [in] the xml version
          * \param encoding [in] the xml encoding
          */
          virtual void versionAndEncoding(const std::string& version,const std::string& encoding);
      };

    private:
      // xml writer state
      enum XmlWriterState {
        xwsNone,
        xwsDTD,
        xwsEndLOp,
        xwsOpenTagOp,
        xwsContent
      };

      XmlWriterState lastOp; // last operation

      std::stack<std::string> xmlElementStack;  // stack for tag names
    
      void putTabs(int deletedNum = 0); // put tabs befor tags and contents

      /**
      * \brief write attribute to opened tag ( attribute="value" )
      * \param attribute [in] attribute name
      * \param value [in] attribute value
      * \throw IOException if the writing is failed.
      * \throw IOException if last operation isn't open element or attribute write
      */
      template<class Attr>
      void writeAttributeByTemplate(const std::string& attribute,Attr value);

    public:

      /**
      * \brief constructor, create empty SimpleXmlIO object
      */
      SimpleXmlIO();

      /**
      * \brief create SimpleXmlIO object and open a stream to stdout/stderr
      * \param toError [in] if it is true, stream is open to stderr, otherwise stdout
      */
      SimpleXmlIO(bool toError);

      /**
      * \brief create a SimpleXmlIO object and open a file
      * \param filename [in] file name
      * \param mode [in] open mode (it can be only omWrite)
      * \throw IOException if open is failed
      * \throw IOException wrong open mode
      */
      SimpleXmlIO(const std::string& filename, IOBase::eOpenMode mode);

      /**
      * \brief create a SimpleXmlIO object and open a file
      * \param filename [in] file name
      * \param mode [in] open mode (it can be only omWrite)
      * \throw IOException if open is failed
      * \throw IOException wrong open mode
      */
      SimpleXmlIO(const char *filename, IOBase::eOpenMode mode);

      /**
      * \brief destructor
      */
      ~SimpleXmlIO();
      
      // XML declaration
      /**
      * \brief write xml declaration (<?xml version="version" encoding="encoding"?>)
      * \param version [in] the xml version
      * \param encoding [in] the file encoding
      * \throw IOException if the writing is failed.
      * \throw IOException if last operation isn't none or write DTD
      */
      void writeXMLDeclaration(const std::string& version, const std::string& encoding);

      /**
      * \brief wrtie comment to xml (<!-- comment -->)
      * \param comment [in] the comment text
      * \throw IOException if the writing is failed.
      */
      void writeCommentTag(const std::string& comment);
      
      /**
      * \brief write begin of an element (<element )
      * \param element [in] the elemenet name
      * \throw IOException if the writing is failed.
      */
      void writeBeginElement(const std::string& element);

      /**
      * \brief write attribute to opened tag ( attribute="value" )
      * \param attribute [in] attribute name
      * \param value [in] attribute value
      * \throw IOException if the writing is failed.
      * \throw IOException if last operation isn't open element or attribute write
      */
      void writeAttribute(const std::string& attribute, const std::string& value);

      /**
      * \brief write attribute to opened tag ( attribute="value" )
      * \param attribute [in] attribute name
      * \param value [in] attribute value
      * \throw IOException if the writing is failed.
      * \throw IOException if last operation isn't open element or attribute write
      */
      void writeAttribute(const std::string& attribute, const char* value);

      /**
      * \brief write attribute to opened tag ( attribute="value" )
      * \param attribute [in] attribute name
      * \param value [in] attribute value
      * \throw IOException if the writing is failed.
      * \throw IOException if last operation isn't open element or attribute write
      */
      void writeAttribute(const std::string& attribute, bool value);

      /**
      * \brief write attribute to opened tag ( attribute="value" )
      * \param attribute [in] attribute name
      * \param value [in] attribute value
      * \throw IOException if the writing is failed.
      * \throw IOException if last operation isn't open element or attribute write
      */
      void writeAttribute(const std::string& attribute, int value);

      /**
      * \brief write attribute to opened tag ( attribute="value" )
      * \param attribute [in] attribute name
      * \param value [in] attribute value
      * \throw IOException if the writing is failed.
      * \throw IOException if last operation isn't open element or attribute write
      */
      void writeAttribute(const std::string& attribute, long long value);

      /**
      * \brief write attribute to opened tag ( attribute="value" )
      * \param attribute [in] attribute name
      * \param value [in] attribute value
      * \throw IOException if the writing is failed.
      * \throw IOException if last operation isn't open element or attribute write
      */
      void writeAttribute(const std::string& attribute, double value);

      /**
      * \brief write attribute to opened tag ( attribute="value" )
      * \param attribute [in] attribute name
      * \param value [in] attribute value
      * \throw IOException if the writing is failed.
      * \throw IOException if last operation isn't open element or attribute write
      */
      void writeAttribute(const std::string& attribute, void* value);

      /**
      * \brief write element content
      * \param content [in] the contetnt text
      * \throw IOException if the writing is failed.
      * \throw IOException if no elemepnt opened
      */
      void writeElementContent(const std::string& content);

      /**
      * \brief write element end tag (</element>)
      * \throw IOException if the writing is failed.
      * \throw IOException if no elemepnt opened
      */
      void writeEndElement();
      
      /**
      * \brief write dtd to top of the file
      * \throw IOException if the writing is failed.
      * \throw IOException if last operation isn't none
      */
      void writeDTDTag(const std::string& text);

      /**
      * \brief close the file and clos all open tags
      */
      void close();
  };

  /**
  * \brief load a XML from 'filename' and parse with 'xmlHandler'
  * \param filename [in] the XML name
  * \param xmlHandler [in] parse xml with this
  */
  void loadXml(const std::string& filename, SimpleXmlIO::XmlHandler &xmlHandler);

}}

#endif

