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

#ifndef _METRICS_LCOM_H_
#define _METRICS_LCOM_H_

#include "../MetricHandler.h"

namespace columbus { namespace lim { namespace metrics {

  struct ConnectedComponentElement{

    const lim::asg::Method* method;
    ConnectedComponentElement *nextElement;
    std::set<const lim::asg::logical::Attribute*> accessedAttributes;
    std::set<const lim::asg::logical::Method*> methodCalls;

    ConnectedComponentElement(const lim::asg::logical::Method* method) :
        method(method), nextElement(NULL), accessedAttributes() {}

    ConnectedComponentElement(const ConnectedComponentElement& element) :
        method(element.method), nextElement(element.nextElement), accessedAttributes(element.accessedAttributes) {}

    ConnectedComponentElement& operator = ( const ConnectedComponentElement& element ) {
      method = element.method;
      nextElement = element.nextElement;
      accessedAttributes = element.accessedAttributes;

      return *this;
    }
    
  };

  class LCOM5 : public MetricHandler {
    public:
      LCOM5( bool enabled, SharedContainers* shared );
    protected:
      const std::string& translateLevel( asg::Language language, const std::string& level ) const override;
    private:
      ConnectedComponentElement* getConnectedComponentRootElement( ConnectedComponentElement* element ) const;
      int calculateConnectedComponents( const asg::logical::Class& actClass, std::vector<ConnectedComponentElement>& connectedComponents, const std::set<const asg::logical::Class*>& parentClasses );
  };


  class TLCOM5 : public MetricHandler {
    public:
      TLCOM5(bool enabled, SharedContainers* shared);
  };

}}}

#endif
