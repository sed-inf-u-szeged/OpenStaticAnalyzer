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

#include "../../inc/metrics/CBO.h"

using namespace std;
using namespace columbus::lim::asg;
using namespace columbus::graphsupport::graphconstants;

namespace columbus { namespace lim { namespace metrics {

  CBOBase::CBOBase( const std::string& name, MetricDataTypes type, bool enabled, SharedContainers* shared ) :
    MetricHandler( name, type, enabled, shared ) {}

  const std::string& CBOBase::translateLevel( asg::Language language, const std::string& level ) const {
    const string& newLevel = MetricHandler::translateLevel( language, level );

    if ( language == limLangC ) {
      if (
        newLevel == NTYPE_LIM_STRUCTURE ||
        newLevel == NTYPE_LIM_UNION
      ) {
        return NTYPE_LIM_CLASS;
      }
    }

    else if ( language == limLangCpp ) {
      if (
        newLevel == NTYPE_LIM_CLASS ||
        newLevel == NTYPE_LIM_UNION ||
        newLevel == NTYPE_LIM_INTERFACE
      ) {
        return NTYPE_LIM_CLASS;
      }
    }

    else if ( language == limLangCsharp ) {
      if (
        newLevel == NTYPE_LIM_CLASS ||
        newLevel == NTYPE_LIM_INTERFACE
      ) {
        return NTYPE_LIM_CLASS;
      }
    }

    return newLevel;
  }

  CBO::CBO( bool enabled, SharedContainers* shared ) : CBOBase( "CBO", mdtInt, enabled, shared ) {

    this->registerHandler( phaseVisit, NTYPE_LIM_CLASS, limLangOther, false, [this]( NodeWrapper& node ) {

      const logical::Class& clazz = node.getLimNode<logical::Class>();
      set<const logical::Class*> cbo;

      ListIterator<logical::Member> memberIt = clazz.getMemberListIteratorBegin(), memberEnd = clazz.getMemberListIteratorEnd();
      for ( ; memberIt != memberEnd; ++memberIt ) {

        // Method
        if ( Common::getIsMethod( *memberIt ) ) {
          const logical::Method& method = dynamic_cast<const logical::Method&>( *memberIt );
          if ( NodeWrapper::isDefinition( method ) ) {

            // MethodCalls
            ListIterator<logical::MethodCall> callIt = method.getCallsListIteratorBegin(), callEnd = method.getCallsListIteratorEnd();
            for ( ; callIt != callEnd; ++callIt ) {
              collectUsedClasses( *callIt, clazz, cbo );
            }

            // Method --> uses
            ListIterator<type::Type> usesIt = method.getUsesListIteratorBegin(), usesEnd = method.getUsesListIteratorEnd();
            for ( ; usesIt != usesEnd; ++usesIt ) {
              collectUsedClasses( *usesIt, clazz, cbo );
            }

            // Parameters
            ListIterator<logical::Parameter> parameterIt = method.getParameterListIteratorBegin(), parameterEnd = method.getParameterListIteratorEnd();
            for ( ; parameterIt != parameterEnd; ++parameterIt ) {
              collectUsedClasses( *parameterIt, clazz, cbo );
            }

            // Instantiations
            ListIterator<type::Type> instantiatesIt = method.getInstantiatesListIteratorBegin(), instantiatesEnd = method.getInstantiatesListIteratorEnd();
            for ( ; instantiatesIt != instantiatesEnd; ++instantiatesIt ) {
              collectUsedClasses(*instantiatesIt, clazz, cbo);
            }

            // AttributeAccesses
            ListIterator<logical::AttributeAccess> accessIt = method.getAccessesAttributeListIteratorBegin(), accessEnd = method.getAccessesAttributeListIteratorEnd();
            for ( ; accessIt != accessEnd; ++accessIt ) {
              collectUsedClasses( *accessIt, clazz, cbo );
            }

            // Returns
            ListIterator<type::Type> returnsIt = method.getReturnsListIteratorBegin(), returnsEnd = method.getReturnsListIteratorEnd();
            for ( ; returnsIt != returnsEnd; ++returnsIt ) {
              collectUsedClasses( *returnsIt, clazz, cbo );
            }

            // Throws
            ListIterator<type::Type> throwIt = method.getThrowsListIteratorBegin(), throwEnd = method.getThrowsListIteratorEnd();
            for ( ; throwIt != throwEnd; ++throwIt ) {
              collectUsedClasses( *throwIt, clazz, cbo );
            }

            // CanThrows
            ListIterator<type::Type> canThrowIt = method.getCanThrowListIteratorBegin(), canThrowEnd = method.getCanThrowListIteratorEnd();
            for ( ; canThrowIt != canThrowEnd; ++canThrowIt ) {
              collectUsedClasses( *canThrowIt, clazz, cbo );
            }
          }
        }

        // Attribute
        if ( Common::getIsAttribute( *memberIt ) ) {
          const logical::Attribute& attr = dynamic_cast<const logical::Attribute&>( *memberIt );

          // MethodCalls
          ListIterator<logical::MethodCall> callIt = attr.getCallsListIteratorBegin(), callEnd = attr.getCallsListIteratorEnd();
          for ( ; callIt != callEnd; ++callIt ) {
            collectUsedClasses( *callIt, clazz, cbo );
          }

          // Type
          ListIterator<type::Type> hasTypeIt = attr.getTypeListIteratorBegin();
          if ( hasTypeIt != attr.getTypeListIteratorEnd() ) {
            collectUsedClasses( dynamic_cast<const type::Type&>( *hasTypeIt ), clazz, cbo );
          }
        }
      }

      // Class --> uses
      ListIterator<type::Type> usesIt = clazz.getUsesListIteratorBegin(), usesEnd = clazz.getUsesListIteratorEnd();
      for ( ; usesIt != usesEnd; ++usesIt ) {
        collectUsedClasses( dynamic_cast<const type::Type&>( *usesIt ), clazz, cbo );
      }

      // Class --> parents
      ListIterator<type::Type> parentIt = clazz.getIsSubclassListIteratorBegin(), parentEnd = clazz.getIsSubclassListIteratorEnd();
      for ( ; parentIt != parentEnd; ++parentIt ) {
        collectUsedClasses( dynamic_cast<const type::Type&>( *parentIt ), clazz, cbo );
      }

      // Inverse CBO handling
      set<const logical::Class*>::iterator cboIt = cbo.begin(), cboEnd = cbo.end();
      for ( ; cboIt != cboEnd; ++cboIt ) {
        Info& info = this->shared->scopes.map[ *cboIt ];
        info.sets["CBOI"].insert( clazz.getId() );
      }

      int cboNum = (int)cbo.size();
      addMetric( node, cboNum );

      // propagate to package level
      this->shared->currentPackageInfo().ints[this->name] += cboNum;

      cleanup( node );

    });

  }

  void CBO::collectUsedClasses( const asg::base::Base& to, const asg::logical::Class& node, std::set<const asg::logical::Class*>& usedClasses) const {

    if ( Common::getIsMethodCall( to ) ) {
      const logical::MethodCall& toMethodCall = (const logical::MethodCall&)to;
      const logical::Method* toMethod = toMethodCall.getMethod();
      if ( toMethod != NULL && ! NodeWrapper::isFunction( *toMethod ) ) {
        const logical::Class* refClass = getClassOfReferencedMember( node, *toMethod );
        if ( refClass != NULL && refClass->getId() != node.getId() ) {
          usedClasses.insert(refClass);
        }
      }
    } else if ( Common::getIsAttributeAccess( to ) ) {
      const logical::AttributeAccess& toAttributeAccess = (const logical::AttributeAccess&)to;
      const logical::Attribute* toAttribute = (const logical::Attribute*)toAttributeAccess.getAttribute();
      if ( toAttribute != NULL && ! NodeWrapper::isGlobalAttribute( *toAttribute ) ) {
        const logical::Class* refClass = getClassOfReferencedMember(node, *toAttribute);
        if ( refClass != NULL && refClass->getId() != node.getId() ) {
          usedClasses.insert(refClass);
        }
      }
    } else if ( Common::getIsParameter( to ) ) {
      const logical::Parameter& toParameter = (const logical::Parameter&)to;
      const type::Type* type = toParameter.getType();
      if ( type != NULL ) {
        getClassOfType( *type, node, usedClasses );
      }
    } else if ( Common::getIsGenericParameter( to ) ) {
      const logical::GenericParameter& toGenericParameter = (const logical::GenericParameter&)to;
      ListIterator<type::Type> typeIt = toGenericParameter.getParameterConstraintListIteratorBegin();
      for( ; typeIt != toGenericParameter.getParameterConstraintListIteratorEnd(); ++typeIt ) {
        getClassOfType( *typeIt, node, usedClasses );
      }
    
    } else if ( Common::getIsType( to ) ) {
      const type::Type& type = (const type::Type&)to;
      getClassOfType( type, node, usedClasses );
    }
  }

  void CBO::getClassOfType( const asg::type::Type& type, const asg::logical::Class& node, std::set<const asg::logical::Class*>& usedClasses ) const {

    ListIterator<type::TypeFormer> typeFormerIt = type.getTypeFormerListIteratorBegin(), typeFormerEnd = type.getTypeFormerListIteratorEnd();
    for ( ; typeFormerIt != typeFormerEnd; ++typeFormerIt ) {
      if ( Common::getIsTypeFormerType( *typeFormerIt ) ) {
        const type::TypeFormerType& typeFormerType = (const type::TypeFormerType&)*typeFormerIt;
        const base::Base* refBase = typeFormerType.getRefersTo();
        if ( refBase != NULL ) {

          if ( Common::getIsClass(*refBase) && usedClasses.find( (logical::Class*)refBase ) != usedClasses.end() ) {
            return;
          }

          switch( refBase->getNodeKind() ) {

            case ndkClass: {
              const logical::Class& refClass = (const logical::Class&)*refBase;
              if(refClass.getId() == node.getId())
                continue;
              usedClasses.insert(&refClass);
            }
            break;

            case ndkClassGeneric: {
              const logical::ClassGeneric& refClassGeneric = (const logical::ClassGeneric&)*refBase;
              if ( refClassGeneric.getId() == node.getId() ) continue;
              usedClasses.insert( &refClassGeneric );

              ListIterator<GenericParameter> genParIt = refClassGeneric.getGenericParameterListIteratorBegin();
              for ( ; genParIt != refClassGeneric.getGenericParameterListIteratorEnd(); ++genParIt ) {
                ListIterator<type::Type> constraintIt = genParIt->getParameterConstraintListIteratorBegin();
                for ( ; constraintIt != genParIt->getParameterConstraintListIteratorEnd(); ++constraintIt ) {
                  getClassOfType( *constraintIt, node, usedClasses );
                }
              }
            }
            break;

            case ndkClassGenericInstance: {
              const logical::ClassGenericInstance& refClassGenericInstance = (const logical::ClassGenericInstance&)*refBase;
              const logical::ClassGeneric* prototype = Common::getClassPrototype( this->shared->factory->getReverseEdges(), refClassGenericInstance );
              if ( prototype != NULL ) {
                if ( prototype->getId() == node.getId() ) {
                  continue;
                }
                usedClasses.insert(prototype);
              }

              ListIteratorAssocTypeArgumentConstraintKind<type::Type> constraintAssocIt = refClassGenericInstance.getArgumentsListIteratorAssocBegin();
              for ( ; constraintAssocIt != refClassGenericInstance.getArgumentsListIteratorAssocEnd(); ++constraintAssocIt ) {
                getClassOfType( *constraintAssocIt, node, usedClasses );
              }
            }
            break;

            case ndkClassGenericSpec: {
              const logical::ClassGenericSpec& refClassGenericSpec = (const logical::ClassGenericSpec&)*refBase;
              if( refClassGenericSpec.getId() == node.getId() ) continue;
              usedClasses.insert( &refClassGenericSpec );

              ListIteratorAssocTypeArgumentConstraintKind<type::Type> constraintAssocIt = refClassGenericSpec.getArgumentsListIteratorAssocBegin();
              for( ; constraintAssocIt != refClassGenericSpec.getArgumentsListIteratorAssocEnd(); ++constraintAssocIt ) {
                getClassOfType( *constraintAssocIt, node, usedClasses );
              }
            }
            break;

            default: continue;
          }
        }
      }
    }
  }

  const logical::Class* CBO::getClassOfReferencedMember( const logical::Class& fromClass, const logical::Member& referedMember ) const {

    unsigned int sameComponentCounter = 0;
    ListIterator<base::Base> it = this->shared->factory->getReverseEdges().constIteratorBegin( referedMember.getId(), edkScope_HasMember );
    for ( ; it != this->shared->factory->getReverseEdges().constIteratorEnd( referedMember.getId(), edkScope_HasMember ); ++it ) {
      if ( Common::getIsClass( *it ) ) {
        const logical::Class &classOfMember = (const logical::Class&)(*it);
        ListIterator<base::Component> frombelongsToIt = fromClass.getBelongsToListIteratorBegin();
        for ( ; frombelongsToIt != fromClass.getBelongsToListIteratorEnd(); ++frombelongsToIt ) {
          ListIterator<base::Component> classOfbelongsToIt = classOfMember.getBelongsToListIteratorBegin();
          for ( ; classOfbelongsToIt != classOfMember.getBelongsToListIteratorEnd(); ++classOfbelongsToIt ) {
            if ( frombelongsToIt->getId() == classOfbelongsToIt->getId() ) {
              ++sameComponentCounter;
            }
          }
        }
        if ( fromClass.getBelongsToSize() == sameComponentCounter ) {
          return &classOfMember;
        }
      }
    }
    return NULL;
  }

  CBOI::CBOI( bool enabled, SharedContainers* shared ) : CBOBase( "CBOI", mdtInt, enabled, shared ) {

    dependencies.insert( "CBO" );

    this->registerHandler( phaseFinishVisit, NTYPE_LIM_CLASS, limLangOther, false, [this]( NodeWrapper& node ) {

      const logical::Class& clazz = node.getLimNode<logical::Class>();
      Info& info = this->shared->scopes.map[ &clazz ];
      addMetric( node, (int) info.sets[this->name].size() );
      
      cleanup( node );
      
    });

  }

  TCBO::TCBO(bool enabled, SharedContainers* shared) : MetricHandler("TCBO", mdtInt, enabled, shared) {
      dependencies.insert("CBO");
      propagateScopeInt(phaseFinalize, NTYPE_LIM_PACKAGE, limLangOther);
  }

}}}
