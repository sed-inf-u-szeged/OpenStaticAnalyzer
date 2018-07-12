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

#ifndef __METRICHUNTER_DEFINES_H__
#define __METRICHUNTER_DEFINES_H__

#define _CONFIG "java"
#define LESS_THAN "lt"
#define GREATER_THAN "gt"
#define LESS_EQUAL "le"
#define GREATER_EQUAL "ge"


inline int extractIntAttr( const columbus::graph::Node& gNode, const std::string& name ){
  columbus::graph::Attribute::AttributeIterator aIt = gNode.findAttributeByName( name );
  if ( aIt.hasNext() ) return (int) ((columbus::graph::AttributeInt&)aIt.next()).getValue();
  else return 0;
}

inline std::string extractStringAttr( const columbus::graph::Node& gNode, const std::string& name ){
  columbus::graph::Attribute::AttributeIterator aIt = gNode.findAttributeByName( name );
  if ( aIt.hasNext() ) return (std::string) ((columbus::graph::AttributeString&)aIt.next()).getValue();
  else return std::string();
}  

inline int extractIntCompAttr( const columbus::graph::Node& gNode, const std::string& compName, const std::string& name ){
  columbus::graph::Attribute::AttributeIterator caIt = gNode.findAttributeByName( compName );
  if ( caIt.hasNext() ){
    columbus::graph::Attribute::AttributeIterator aIt = ((columbus::graph::AttributeComposite&)caIt.next()).findAttributeByName( name );
    if ( aIt.hasNext() ) return (int) ((columbus::graph::AttributeInt&)aIt.next()).getValue();
  }
  return 0;
}

inline std::string extractStringCompAttr( const columbus::graph::Node& gNode, const std::string& compName, const std::string& name ){
  columbus::graph::Attribute::AttributeIterator caIt = gNode.findAttributeByName( compName );
  if ( caIt.hasNext() ){
    columbus::graph::Attribute::AttributeIterator aIt = ((columbus::graph::AttributeComposite&)caIt.next()).findAttributeByName( name );
    if ( aIt.hasNext() ) return (std::string) ((columbus::graph::AttributeString&)aIt.next()).getValue();
  }
  return std::string();
}


static inline std::string getWarningString(const std::string& id, const std::string& entity, const std::string& rel, const std::string& value, const std::string& threshold ) {
  std::string relstring = "Unknown relation";

  if(rel == LESS_THAN) relstring = "less";
  else if(rel == GREATER_THAN) relstring = "greater";
  else if(rel == LESS_EQUAL) relstring = "equal or less";
  else if(rel == GREATER_EQUAL) relstring =  "equal or greater";
  if(value == "") {
    return "The metric " + id + " (defined for "+ entity + " '%') value is "+ relstring +" than the threshold value '" +  threshold +"'.";
  } else { 
    return "The metric " + id + " (defined for "+ entity + " '%') value '" + value + "' is "+ relstring +" than the threshold value '" +  threshold +"'.";
  }
}

inline std::string getWarningName(const std::string& metricName, const std::string& entityType) {
  return metricName + "_warning_" + entityType;
}

#endif
