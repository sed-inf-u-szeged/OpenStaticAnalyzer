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

#include "../../inc/metrics/LCOM5.h"

using namespace std;
using namespace columbus::lim::asg;
using namespace columbus::graphsupport::graphconstants;

namespace columbus { namespace lim { namespace metrics {

  LCOM5::LCOM5( bool enabled, SharedContainers* shared ) : MetricHandler( "LCOM5", mdtInt, enabled, shared ) {

    registerHandler( phaseVisit, NTYPE_LIM_CLASS, limLangOther, false, [this] ( NodeWrapper& node ) {

      const logical::Class& clazz = node.getLimNode<logical::Class>();
      set<const logical::Class*> parentClasses;
      parentClasses.insert( &clazz );
      if ( ! clazz.getIsSubclassIsEmpty() ) {
        Common::collectAncestors( this->shared->factory->getReverseEdges(), clazz, parentClasses );
      }

      vector<ConnectedComponentElement> connectedComponents;
      connectedComponents.reserve( 1000 );

      ListIterator<logical::Member> memberIt = clazz.getMemberListIteratorBegin(),
                                    memberEnd = clazz.getMemberListIteratorEnd();

      for ( ; memberIt != memberEnd; ++memberIt ) {
        if ( Common::getIsMethod( *memberIt ) ) {
          const logical::Method& method = dynamic_cast<const logical::Method&>( *memberIt );
          if ( NodeWrapper::isDefinition( method ) ) {
            if ( !method.getIsAbstract() ) {
              connectedComponents.push_back( ConnectedComponentElement( &method ) );

              ListIterator<logical::AttributeAccess>  accessIt = method.getAccessesAttributeListIteratorBegin(),
                                                      accessEnd = method.getAccessesAttributeListIteratorEnd();

              for ( ; accessIt != accessEnd; ++accessIt ) {
                const logical::Attribute* attribute = accessIt->getAttribute();
                if ( attribute ) {
                  connectedComponents[connectedComponents.size() - 1].accessedAttributes.insert( attribute );
                }
              }

              ListIterator<logical::MethodCall> callsIt = method.getCallsListIteratorBegin(),
                                                callsEnd = method.getCallsListIteratorEnd();

              for ( ; callsIt != callsEnd; ++callsIt ) {
                const logical::Method* calledMethod = callsIt->getMethod();
                if ( calledMethod ) {
                  connectedComponents[connectedComponents.size() - 1].methodCalls.insert( calledMethod );
                }
              }
            }
          }
        }
      }

      int lcom = calculateConnectedComponents( clazz, connectedComponents, parentClasses );
      addMetric( node, lcom );

      // propagate to package level
      this->shared->currentPackageInfo().ints[this->name] += lcom;

    });

  }

  const string& LCOM5::translateLevel( Language language, const string& level ) const {
    const string& newLevel = MetricHandler::translateLevel( language, level );

    switch ( language ) {
      case limLangCpp:
        if (
          newLevel == NTYPE_LIM_CLASS ||
          newLevel == NTYPE_LIM_UNION
        ) {
          return NTYPE_LIM_CLASS;
        }
        break;
      default:
        break;
    }

    return newLevel;
  }


  ConnectedComponentElement* LCOM5::getConnectedComponentRootElement( ConnectedComponentElement* element ) const {
    ConnectedComponentElement* ccelement = element;
    if(element->nextElement != NULL && element->nextElement != element)
      ccelement = getConnectedComponentRootElement(element->nextElement);
    
    return ccelement;
  }

  int LCOM5::calculateConnectedComponents( const asg::logical::Class& actClass, vector<ConnectedComponentElement>& connectedComponents, const set<const logical::Class*>& parentClasses ) {

    NodeId actClassId = actClass.getId();

    const size_t connectedComponentsSize = connectedComponents.size();
    const asg::ReverseEdges& revEdges = shared->factory->getReverseEdges();
    
    for(unsigned int i = 0; i < connectedComponentsSize; ++i){
      ConnectedComponentElement& actualElement = connectedComponents[i];
      const logical::Method &actualMethod = *actualElement.method;

      if(!actualMethod.getCallsIsEmpty()){
        ListIterator<logical::MethodCall> actualmethodCallIt = actualMethod.getCallsListIteratorBegin();
        for (; actualmethodCallIt != actualMethod.getCallsListIteratorEnd(); ++actualmethodCallIt) {
          const logical::Method* actualCalledMethod = actualmethodCallIt->getMethod();

          for (unsigned int j = 0; j < connectedComponentsSize; ++j) {

            if(i != j){     //onmagaval nem vizsgaljuk
              ConnectedComponentElement& elementInComponent = connectedComponents[j];
              const logical::Method &methodInComponent = *connectedComponents[j].method;

              if(actualCalledMethod != NULL && actualCalledMethod->getId() == methodInComponent.getId()){

                ListIterator<base::Base> it = revEdges.constIteratorBegin(actualCalledMethod->getId(), edkScope_HasMember);
                if(it != revEdges.constIteratorEnd(actualCalledMethod->getId(), edkScope_HasMember)) {
                  if (Common::getIsClass(*it)) {
                    const logical::Class *classOfMethod = (const logical::Class*)(&(*it));
                    if(classOfMethod->getAggregated() != NULL)
                      classOfMethod = (const logical::Class*)(classOfMethod->getAggregated());

                    if (classOfMethod->getId() == actClassId) {

                      if(actualElement.nextElement == NULL || actualElement.nextElement == &actualElement){                  //root elem hivott

                        if(elementInComponent.nextElement == NULL || elementInComponent.nextElement == &elementInComponent){             //root elemet hivtunk
                          elementInComponent.nextElement = &actualElement;                //vizsgalt elemet rakotjuk az aktualis elemre

                          actualElement.accessedAttributes.insert(elementInComponent.accessedAttributes.begin(), elementInComponent.accessedAttributes.end());
                          actualElement.methodCalls.insert(elementInComponent.methodCalls.begin(), elementInComponent.methodCalls.end());

                        }
                        else{
                          ConnectedComponentElement* rootElement = getConnectedComponentRootElement(&elementInComponent);
                          rootElement->nextElement = &actualElement;                      //vizsgalt elem gyokeret rakotjuk az aktualis elemre

                          actualElement.accessedAttributes.insert(rootElement->accessedAttributes.begin(), rootElement->accessedAttributes.end());
                          actualElement.methodCalls.insert(rootElement->methodCalls.begin(), rootElement->methodCalls.end());

                        }

                      }
                      else{                                                             //nem root elem hivott

                        ConnectedComponentElement* rootActualElement = getConnectedComponentRootElement(&actualElement);
                  
                        if(elementInComponent.nextElement == NULL || elementInComponent.nextElement == &elementInComponent){               //root elemet hivtunk
                          elementInComponent.nextElement = rootActualElement;               //vizsgalt elemet rakotjuk az aktualis elem gyokerere

                          rootActualElement->accessedAttributes.insert(elementInComponent.accessedAttributes.begin(), elementInComponent.accessedAttributes.end());
                          rootActualElement->methodCalls.insert(elementInComponent.methodCalls.begin(), elementInComponent.methodCalls.end());

                        }
                        else{
                          ConnectedComponentElement* rootElement = getConnectedComponentRootElement(&elementInComponent);
                          if(rootElement != rootActualElement){
                      
                            rootActualElement->nextElement = rootElement;                   //aktualis elem gyokeret rakotjuk az vizsgalt elem gyokerere

                            rootElement->accessedAttributes.insert(rootActualElement->accessedAttributes.begin(), rootActualElement->accessedAttributes.end());
                            rootElement->methodCalls.insert(rootActualElement->methodCalls.begin(), rootActualElement->methodCalls.end());

                          }

                        }
                  
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }

    for(unsigned int i = 0; i < connectedComponentsSize; ++i){
    ConnectedComponentElement& actualElement = connectedComponents[i];
    set<const logical::Attribute*>& actualAttributes = actualElement.accessedAttributes;
    set<const logical::Method*>& actualMethods = actualElement.methodCalls;
      
      if(actualElement.nextElement == NULL || actualElement.nextElement == &actualElement){                                //aktualis gyoker elem
        for (unsigned int j = 0; j < connectedComponentsSize; ++j) {

          if(i != j){     //onmagaval nem vizsgaljuk
            ConnectedComponentElement& elementInComponent = connectedComponents[j];
            set<const logical::Attribute*>& elementAttributes = elementInComponent.accessedAttributes;
            set<const logical::Method*>& elementMethods = elementInComponent.methodCalls;

            if(elementInComponent.nextElement == NULL || elementInComponent.nextElement == &elementInComponent){                     //vizsgalt gyoker elem

              bool isConnected = false;
              set<const logical::Attribute*>::const_iterator actualItEnd = actualAttributes.end();
              set<const logical::Attribute*>::const_iterator elementItEnd = elementAttributes.end();
              for(set<const logical::Attribute*>::const_iterator actualIt = actualAttributes.begin(); actualIt != actualItEnd; ++actualIt){
                if(*actualIt != NULL && elementAttributes.find(*actualIt) != elementItEnd){
                  
                  ListIterator<base::Base> it = revEdges.constIteratorBegin((*actualIt)->getId(), edkScope_HasMember);
                  if(it != revEdges.constIteratorEnd((*actualIt)->getId(), edkScope_HasMember)) {
                    if (Common::getIsClass(*it)) {
                      logical::Class *classOfAttribute = (logical::Class*)(&(*it));
                      if(classOfAttribute->getAggregated() != NULL)
                        classOfAttribute = (logical::Class*)(classOfAttribute->getAggregated());
                        
                        if (parentClasses.find(classOfAttribute) != parentClasses.end() || classOfAttribute->getId() == actClassId) {

                          elementInComponent.nextElement = &actualElement;

                          actualAttributes.insert(elementAttributes.begin(), elementAttributes.end());
                          isConnected = true;
                          break;
                        }

                    }
                  }
 
                }
          
              }
              if(isConnected)
                continue;

              set<const logical::Method*>::const_iterator actualCallsItEnd = actualMethods.end();
              set<const logical::Method*>::const_iterator elementCallsItEnd = elementMethods.end();
              for(set<const logical::Method*>::const_iterator callslIt = actualMethods.begin(); callslIt != actualCallsItEnd; ++callslIt){
                if(*callslIt != NULL && elementMethods.find(*callslIt) != elementCallsItEnd){
                  
                  ListIterator<base::Base> it = revEdges.constIteratorBegin((*callslIt)->getId(), edkScope_HasMember);
                  if(it != revEdges.constIteratorEnd((*callslIt)->getId(), edkScope_HasMember)) {
                    if (Common::getIsClass(*it)) {
                      logical::Class *classOfMethod = (logical::Class*)(&(*it));
                      if(classOfMethod->getAggregated() != NULL)
                        classOfMethod = (logical::Class*)(classOfMethod->getAggregated());
                        
                        if (parentClasses.find(classOfMethod) != parentClasses.end()) {

                          elementInComponent.nextElement = &actualElement;

                          actualMethods.insert(elementMethods.begin(), elementMethods.end());
                          break;
                        }

                    }
                  }
 
                }
          
              }

            }

          }
      
        }
      }
    }

    // ignore components that contain only contructors, destructors, getters or setters
    map<const ConnectedComponentElement*, bool> ignoreMap;
    for ( unsigned int i = 0; i < connectedComponentsSize; ++i ) {
      ConnectedComponentElement& actualElement = connectedComponents[i];

      // if the element is not already inspected
      if ( ignoreMap.find(&actualElement) == ignoreMap.end() ) {
        ConnectedComponentElement* step = &actualElement;

        // suppose that its component is irrelevant
        bool ignore = true;

        // search through it from the current element
        // if there is something relevant in it then don't ignore
        for ( ;; ) {

          MethodKind mk = step->method->getMethodKind();
          if ( mk != mekConstructor && mk != mekDestructor && mk != mekGet && mk != mekSet ) {
            ignore = false;
            break;
          }

          if ( step->nextElement == NULL || step->nextElement == step ) {
            break;
          }

          step = step->nextElement;
        }

        // propagate the ignore flag to the whole component after the current element
        // ( if it is not already filled out )
        if ( ignoreMap.find( step ) == ignoreMap.end() ) {
          for ( ;; ) {
            ignoreMap[step] = ignore;
            if ( step->nextElement == NULL || step->nextElement == step ) {
              break;
            }
            step = step->nextElement;
          }
        }
      }
    }


    unsigned int connectedComponentCounter = 0;
    for ( unsigned int i = 0; i < connectedComponentsSize; ++i ) {
      ConnectedComponentElement& actualElement = connectedComponents[i];

      if ( ! ignoreMap[&actualElement] && this->shared->LCOMMap != nullptr ) {

        // export the actual components to the shared map
        ConnectedComponentElement* last = &actualElement;
        while ( last->nextElement != NULL && last->nextElement != last ) {
          last = last->nextElement;
        }

        (*this->shared->LCOMMap)[actClass.getName()][last->method->getName()].push_back( actualElement.method->getName() );
      }

      if ( (actualElement.nextElement == NULL || actualElement.nextElement == &actualElement) && ! ignoreMap[&actualElement] ) {
        ++connectedComponentCounter;
      }
    }

    return connectedComponentCounter;

  }



  TLCOM5::TLCOM5(bool enabled, SharedContainers* shared) : MetricHandler("TLCOM5", mdtInt, enabled, shared) {
    dependencies.insert("LCOM5");
    propagateScopeInt(phaseFinalize, NTYPE_LIM_PACKAGE, limLangOther);
  }

}}}
