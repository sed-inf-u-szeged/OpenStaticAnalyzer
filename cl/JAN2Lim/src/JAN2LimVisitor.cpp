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

#include "../inc/JAN2LimVisitor.h"

#include <common/inc/FileSup.h>
#include <common/inc/StringSup.h>
#include <common/inc/WriteMessage.h>
#include "../inc/messages.h"

#include <utility>
#include <cctype>
#include <map>

#define VISIT_BEGIN(node,callVirtualBase,visitName) \
  VisitorAbstractNodes::visit( node, callVirtualBase ); \
  oldVersionLinking( node ); \
  lim::asg::base::Base* _ptr = getLimPtr( node ); \
  if ( _ptr ) propagateFilter( node, _ptr ); \
  if ( common::WriteMsg::getMessageLevel() >= common::WriteMsg::mlDDDebug ) \
  { \
    common::WriteMsg::write( CMSG_VISIT_BEGIN, visitName, node.getId(), _ptr ? _ptr->getId() : 0 ); \
  } \
  if ( skipUntil != 0 ) \
  { \
    if ( strcmp(visitName, "TypeDeclaration") == 0 ) classStats.skip++; \
    return; \
  }

#define VISIT_END(node,callVirtualBase,visitName) \
  VisitorAbstractNodes::visitEnd( node, callVirtualBase );

#define VISIT_END_FIRST(node,visitName) \
  if ( common::WriteMsg::getMessageLevel() >= common::WriteMsg::mlDDDebug ) \
  { \
    common::WriteMsg::write( CMSG_VISIT_END, visitName, node.getId(), getLimPtr(node) ? getLimPtr(node)->getId() : 0 ); \
  } \
  if ( skipUntil != 0 ) \
  { \
    if ( skipUntil == node.getId() ) \
    { \
      skipUntil = 0; \
    } \
    VisitorAbstractNodes::visitEnd( node, callVirtualBase ); \
    return; \
  }

#define NOPOS ",0,0,0,0"

#define SAFE_EDGE( node, name, type, param ) \
  do \
  { \
    bool node##_found = false; \
    lim::asg::ListIterator<type> node##_it = node.get##name##ListIteratorBegin(); \
    for ( ; node##_it != node.get##name##ListIteratorEnd(); ++node##_it ) \
    { \
      if ( node##_it->getId() == param ) { node##_found = true; break; } \
    } \
    if ( ! node##_found ) \
    { \
      node.add##name( param ); \
    } \
  } \
  while ( false )

#define COUNT_LLOC_BEGIN(SCOPE, NODE) \
  if (java::asg::Common::getIs##NODE(node)) { \
    const java::asg::SCOPE::NODE& n = dynamic_cast<const java::asg::SCOPE::NODE&>(node);

#define COUNT_LLOC_NODE_ATTR(ATTR) \
    insertLLOCMap(n.get##ATTR());

#define COUNT_LLOC_END \
  }



namespace columbus { namespace JAN2Lim
{
  using namespace std;

  //
  // INITIALIZATION
  //

  JAN2LimVisitor::LLOCMapType JAN2LimVisitor::LLOCMap;
  map<NodeId , map<Key, unsigned long> > JAN2LimVisitor::componentTLOCMap;
  set<NodeId> JAN2LimVisitor::initBlocks;
  
  map<Key, NodeId> JAN2LimVisitor::fileMap;

  JAN2LimVisitor::JAN2LimVisitor(
    lim::asg::Factory& limFact
    , columbus::java::asg::Factory& javaFact
    , JAN2LimMap& m
    , CGIMap& cgi
    , map<NodeId, JAN2LimVisitor::CompletionStates>& ns
    , string& componentName
    , VisitStat& stat
    , LimOrigin& origin
    , lim::asg::OverrideRelations& overridesRelations
    , bool connectToRootComponent
    , bool buildEmptyInitBlocks
    , const string& changesetID
    , map<NodeId, HalsteadVisitor::HalsteadInfo> halValues
  )
  : overrides(overridesRelations)
  , packageStack()
  , classStack()
  , attributeStack()
  , methodStack()
  , usesStack()
  , limFactory( limFact )
  , javaFactory( javaFact )
  , uniqueNameNodeMap( m )
  , localMap( JAN2LimLocalMap() )
  , typeMap()
  , cgiMap( cgi )
  , componentName( componentName )
  , component( limFactory.createComponent(componentName) )
  , origin( origin )
  , revEdges( limFact.getReverseEdges() )
  , nodeStates( ns )
  , halsteadValues( halValues )
  , skipUntil( 0 )
  , classStats( stat )
  , buildEmptyInitBlocks( buildEmptyInitBlocks )
  {
    // map java and lim roots
    localMap.insert( make_pair(javaFact.getRoot()->getId(), limFact.getRoot()->getId()) );
    setNotFilteredComponenetUp( component.getId(),!connectToRootComponent);
    component.setChangesetID(changesetID);

    // ensure that its data gets converted
    setState( limFact.getRoot(), Incomplete );

    // link current component to the root component
    if (connectToRootComponent) {
      bool alreadyContain = false;
      for (  lim::asg::ListIterator<lim::asg::base::Component> it = limFact.getComponentRootRef().getContainsListIteratorBegin();
        it != limFact.getComponentRootRef().getContainsListIteratorEnd();++it) {
          if (it->getId() == component.getId()) {
            alreadyContain =  true;
            break;
          }
      }
      if (! alreadyContain) {
        limFact.getComponentRootRef().addContains(component.getId());
      }
    }

    // shotName for component
    component.setShortName( common::pathRemoveExtension( common::pathFindFileName( componentName ) ) );
  }


  //
  //  UTILS
  //

  bool JAN2LimVisitor::PosInfo::matches( const PosInfo& other ) const
  {
    if ( file == "" || other.file == "" ) return true;
    if ( file != other.file ) return false;
    if ( posString == NOPOS || other.posString == NOPOS ) return true;
    return posString == other.posString;
  }

  bool JAN2LimVisitor::PosInfo::operator < ( const PosInfo& other ) const
  {
    return file < other.file || (file == other.file && posString < other.posString);
  }

  JAN2LimVisitor::PosInfo JAN2LimVisitor::javaPosInfo( const java::asg::base::Base& javaNode ) const
  {
    PosInfo posInfo;

    if ( java::asg::Common::getIsPositioned( javaNode ) )
    {
      java::asg::Range pos = dynamic_cast<const java::asg::base::Positioned&>( javaNode ).getPosition();

      posInfo.posString = pos.getPath() + ","
        + common::toString( pos.getWideLine() ) + ","
        + common::toString( pos.getWideCol() ) + ","
        + common::toString( pos.getWideEndLine() ) + ","
        + common::toString( pos.getWideEndCol() );

      // the path of itself or the first parent with real pos info
      const java::asg::base::Base* current = &javaNode;
      for ( ;; )
      {
        if ( current && java::asg::Common::getIsPositioned( *current ) )
        {
          string path = dynamic_cast<const java::asg::base::Positioned&>( *current ).getPosition().getPath();
          if ( path != "" )
          {
            posInfo.file = path;
            break;
          }
          else current = current->getParent();
        }
        else break;
      }
    }
    else
    {
      posInfo.posString = NOPOS;
    }

    return posInfo;
  }

  lim::asg::base::Base* JAN2LimVisitor::getLimPtrByName( const java::asg::base::Base* javaPtr )
  {
    string uniqueName;
    PosInfo posInfo;
    try
    {
      uniqueName = getUniqueName( * javaPtr );
      posInfo = javaPosInfo( *javaPtr );
    }
    catch ( ... )
    {
      return 0;
    }

    JAN2LimMap::const_iterator j = uniqueNameNodeMap.find( uniqueName );
    if ( j != uniqueNameNodeMap.end() )
    {
      map<PosInfo, NodeId>::const_iterator k = j->second.find( posInfo );

      // if we find a direct match, return that
      if ( k != j->second.end() )
      {
        return limFactory.getPointer( k->second );
      }

      // otherwise search the nodes with the same unique name
      // for a matching position info. if we find one then this
      // node gets combined into that
      for ( k = j->second.begin(); k != j->second.end(); ++k )
      {
        if ( posInfo.matches( k->first ) ) {
          lim::asg::base::Base* limNode = limFactory.getPointer( k->second );
          if (!(javaPtr->getNodeKind() == java::asg::ndkPackage && limNode->getNodeKind() != lim::asg::ndkPackage) &&
              !(java::asg::Common::getIsTypeDeclaration(*javaPtr) && !lim::asg::Common::getIsClass(*limNode)) )
          {
            return limNode;
          }
        }
      }
    }

    return 0;
  }

  lim::asg::base::Base* JAN2LimVisitor::_getLimPtr( const java::asg::base::Base* javaPtr )
  {
    // if the java ptr is 0, the lim ptr will be 0 too
    if ( ! javaPtr ) return 0;

    // if we've already seen this node in this round, then return the corresponding lim node
    JAN2LimLocalMap::const_iterator i = localMap.find( javaPtr->getId() );
    if ( i != localMap.end() )
    {
      return limFactory.getPointer( i->second );
    }

    // if it's an InitializerBlock, then we use the ClassStack
    // ( because they get combined into 1 Lim Method under the Class )
    else if ( java::asg::Common::getIsInitializerBlock( *javaPtr ) )
    {
      if ( ! classStack.empty() )
      {
        MethodInfo& info = java::asg::Common::getIsInstanceInitializerBlock( *javaPtr ) ? classStack.top().instanceInit : classStack.top().staticInit;
        if ( ! info.method ) info.method = createLimNode( *javaPtr, Complete, false ).getId();
        return limFactory.getPointer( info.method );
      }
      else return 0;
    }

    // if we haven't, we search the global map with its unique name and position string
    else
    {
      lim::asg::base::Base* byName = getLimPtrByName( javaPtr );
      if ( byName ) return byName;

      // it hasn't been build yet
      // but maybe it will be, so check if it's Lim compatible
      if ( isLimCompatible(*javaPtr) )
      {
        // if it is, we build an incomplete node for it
        return & createLimNode( *javaPtr, Incomplete, false );
      }
    }

    return 0;
  }

  lim::asg::base::Base* JAN2LimVisitor::getLimPtr( const java::asg::base::Base* javaPtr )
  {
    lim::asg::base::Base* retVal = _getLimPtr( javaPtr );

    // if valid lim node, set the corresponding origin data
    if ( retVal )
    {
      origin.addCompIdCppIdLimIdToMap( component.getId(), javaPtr->getId(), retVal->getId() );
    }

    return retVal;
  }

  lim::asg::base::Base* JAN2LimVisitor::getLimPtr( const java::asg::base::Base& javaNode )
  {
    return getLimPtr( & javaNode );
  }

  bool JAN2LimVisitor::isClassLevelVariable( const java::asg::base::Base& node ) const
  {
    // can only be variable or enumConst
    if ( java::asg::Common::getIsVariable(node) || java::asg::Common::getIsEnumConstant(node) )
    {
      // get immediate parent
      java::asg::base::Base* parent = node.getParent();
      if ( parent && java::asg::Common::getIsTypeDeclaration(*parent) ) return true;
    }

    return false;
  }

  bool JAN2LimVisitor::isMethodParameter( const java::asg::base::Base& node ) const
  {
    if ( ! java::asg::Common::getIsParameter(node) ) 
      return false;

    java::asg::base::Base* parent = node.getParent();
    if ( ! parent || ( ! java::asg::Common::getIsNormalMethod(*parent) && ! java::asg::Common::getIsLambda(*parent) ) )
      return false;

    return true;
  }

  bool JAN2LimVisitor::isLimCompatible( const java::asg::base::Base& node ) const
  {
    return   java::asg::Common::getIsPackage(node)
          || java::asg::Common::getIsTypeDeclaration(node)
          || java::asg::Common::getIsMethodDeclaration(node)
          || isClassLevelVariable(node)
          || isMethodParameter(node)
          || java::asg::Common::getIsTypeParameter(node)
          || java::asg::Common::getIsInitializerBlock(node)
          || java::asg::Common::getIsLambda(node);
  }

  java::asg::base::Base* JAN2LimVisitor::getParentPtr( const java::asg::base::Base& javaNode )
  {
    return getParentPtr( javaNode.getId() );
  }

  java::asg::base::Base* JAN2LimVisitor::getParentPtr( const NodeId& id ) {
    java::asg::base::Base* temp = javaFactory.getPointer( id ); // other, non-const pointer
     
    while (temp && temp->getParent()) {
      temp = temp->getParent();
      if ( isLimCompatible(*temp) ) {
        return temp;
      } 
    }

    return NULL;
  }

  JAN2LimVisitor::CompletionStates JAN2LimVisitor::getState( const lim::asg::base::Base* node )
  {
    map<NodeId, CompletionStates>::iterator i = nodeStates.find( node->getId() );
    if ( i == nodeStates.end() )
    {
      return Incomplete;
    }
    else
    {
      return i->second;
    }
  }

  void JAN2LimVisitor::setState( const lim::asg::base::Base* node, CompletionStates state )
  {
    nodeStates[node->getId()] = state;
  }

  string JAN2LimVisitor::getUniqueName( const java::asg::base::Base& node ) const
  {
    // TypeParameters would get the same unique name as their parent GenericDeclarations
    if ( java::asg::Common::getIsTypeParameter(node) )
    {
      return  (node.getParent()?java::asg::Common::getUniqueNameForBase(*node.getParent()):"") + ".TP~" + dynamic_cast<const java::asg::base::Named&>(node).getName();
    }

    else if ( java::asg::Common::getIsParameter(node) )
    {
      if ( node.getParent() && java::asg::Common::getIsNormalMethod(*node.getParent()) )
      {
        java::asg::struc::NormalMethod& meth = dynamic_cast<java::asg::struc::NormalMethod&>( *node.getParent() );
        unsigned int ordinal = 0;
        for ( java::asg::ListIterator<java::asg::struc::Parameter> it = meth.getParametersListIteratorBegin(); it != meth.getParametersListIteratorEnd(); ++it )
        {
          ++ordinal;
          if ( it->getId() == node.getId() ) break;
        }
        return java::asg::Common::getUniqueNameForBase( meth ) + ".P~" + java::asg::Common::toString(ordinal);
      }
      else if (node.getParent() && java::asg::Common::getIsLambda(*node.getParent()))
      {
        java::asg::expr::Lambda& meth = dynamic_cast<java::asg::expr::Lambda&>(*node.getParent());
        unsigned int ordinal = 0;
        for ( java::asg::ListIterator<java::asg::struc::Parameter> it = meth.getParametersListIteratorBegin(); it != meth.getParametersListIteratorEnd(); ++it )
        {
          ++ordinal;
          if (it->getId() == node.getId()) break;
        }
        return java::asg::Common::getUniqueNameForBase(meth) + ".P~" + java::asg::Common::toString(ordinal);
      }
      throw Exception( COLUMBUS_LOCATION, CMSG_EX_WRONG_PARAM_NODE(java::asg::Common::toString(node.getId())) );
    }

    return java::asg::Common::getUniqueNameForBase( node );
  }

  void JAN2LimVisitor::visitInitBlocks( const java::asg::struc::InitializerBlock& node )
  {
    if ( ! classStack.empty() )
    {
      // creation ( or access, if e.g. the Commentable visit already created it )
      lim::asg::logical::Method* initBlock = dynamic_cast<lim::asg::logical::Method*>( getLimPtr( node ) );

      // stack maintenance
      methodStack.push( java::asg::Common::getIsInstanceInitializerBlock( node ) ? classStack.top().instanceInit : classStack.top().staticInit );
      
      // data filling
      fillData( *initBlock, node );
    }
  }

  void JAN2LimVisitor::erase( set<NodeId>& a, const set<NodeId>& b )
  {
    for ( set<NodeId>::const_iterator i = b.begin(); i != b.end(); ++i )
    {
      a.erase( *i );
    }
  }


  //
  // BUILDING
  //

  lim::asg::NodeKind JAN2LimVisitor::getLimKind( const java::asg::base::Base& node, bool tolerateError )
  {
    lim::asg::NodeKind nodeKind;

    // Package
    if ( java::asg::Common::getIsPackage(node) ) nodeKind = lim::asg::ndkPackage;

    // Class
    else if ( java::asg::Common::getIsTypeDeclaration(node) )
    {
      if ( java::asg::Common::getIsGenericDeclaration(node) ) nodeKind = lim::asg::ndkClassGeneric;
      else                                                    nodeKind = lim::asg::ndkClass;
    }

    // Method
    else if ( java::asg::Common::getIsMethodDeclaration(node) )
    {
      if ( java::asg::Common::getIsGenericDeclaration(node) ) nodeKind = lim::asg::ndkMethodGeneric;
      else                                                    nodeKind = lim::asg::ndkMethod;
    }

    // Init Block
    else if ( java::asg::Common::getIsInitializerBlock(node) )
    {
      nodeKind = lim::asg::ndkMethod;
    }

    // Lambda
    else if (java::asg::Common::getIsLambda(node)) nodeKind = lim::asg::ndkMethod;

    // Variable
    else if ( java::asg::Common::getIsVariableDeclaration(node) )
    {
      if ( java::asg::Common::getIsParameter(node) ) nodeKind = lim::asg::ndkParameter;
      else                                           nodeKind = lim::asg::ndkAttribute;
    }

    // Type Parameter
    else if ( java::asg::Common::getIsTypeParameter(node) ) nodeKind = lim::asg::ndkGenericParameter;

    // Tolerated Error
    else if ( tolerateError ) nodeKind = lim::asg::ndkBase;

    // Error
    else throw Exception( COLUMBUS_LOCATION, CMSG_EX_INVALID_NODEKIND(node.getId(), node.getNodeKind()) );

    return nodeKind;
  }

  lim::asg::base::Base& JAN2LimVisitor::createLimNode( const java::asg::base::Base& node, JAN2LimVisitor::CompletionStates state = Incomplete, bool checkExists = true )
  {
    lim::asg::base::Base* limPtr = checkExists ? getLimPtr( node ) : NULL;
    if ( limPtr ) // the node already exists
    {
      setState( limPtr, state );
      return * limPtr;
    }
    
    // it did not exist, creating new node
    lim::asg::base::Named* newLimPtr = (lim::asg::base::Named*) limFactory.createNode( getLimKind( node ) );
    string uniqueName = getUniqueName( node );
    PosInfo posInfo = javaPosInfo( node );

    if (lim::asg::Common::getIsMember(*newLimPtr))
      ((lim::asg::logical::Member*)newLimPtr)->setLanguage(lim::asg::lnkJava);
      
    // setting lim::asg::base::Named node data
    if(java::asg::Common::getIsTypeDeclaration(node) || java::asg::Common::getIsMethodDeclaration(node) 
      || (java::asg::Common::getIsVariableDeclaration(node) && java::asg::Common::getIsTypeDeclaration(*node.getParent()))
      || java::asg::Common::getIsPackage(node) || java::asg::Common::getIsInitializerBlock(node) || java::asg::Common::getIsLambda(node)) {
      newLimPtr->setName( java::asg::Common::getName(node) );
    } else {
      newLimPtr->setName( uniqueName );
    }

    // inserting into java2lim maps
    JAN2LimMap::iterator i = uniqueNameNodeMap.find( uniqueName );
    if ( i == uniqueNameNodeMap.end() )
    {
      uniqueNameNodeMap[uniqueName] = map<PosInfo, NodeId>();
      uniqueNameNodeMap[uniqueName][posInfo] = newLimPtr->getId();
    }
    else
    {
      i->second[posInfo] = newLimPtr->getId();
    }
    
    localMap.insert( make_pair(node.getId(), newLimPtr->getId()) );

    // handling the state info
    setState( newLimPtr, state );

    // propagating filter information
    propagateFilter( node, newLimPtr, true );

    // filling origin data
    origin.addCompIdCppIdLimIdToMap( component.getId(), node.getId(), newLimPtr->getId() );

    return *newLimPtr;
  }

  lim::asg::physical::File& JAN2LimVisitor::createFile( const java::asg::base::PositionedWithoutComment& posWC )
  {
    const java::asg::Range& range = posWC.getPosition();
    lim::asg::physical::File& file = limFactory.createFile( range.getPath() );

    if ( javaFactory.getFilterState( posWC.getId() ) == java::asg::Filter::Filtered )
    {
      limFactory.setFilteredThisNodeOnly( file.getId() );
    }

    fileMap[ limFactory.getStringTable().set(range.getPath()) ] = file.getId();

    return file;
  }

  lim::asg::logical::ClassGenericInstance& JAN2LimVisitor::getCGIforJavaType( const java::asg::type::ParameterizedType& javaType )
  {
    // if it already exists, return that
    string uName = java::asg::Common::getUniqueNameForType( javaType );

    CGIMap::const_iterator i = cgiMap.find( uName );
    if ( i != cgiMap.end() )
    {
      return * i->second;
    }

    // otherwise create a new one
    lim::asg::logical::ClassGenericInstance& cgi = * limFactory.createClassGenericInstanceNode();
    cgi.setIsRealInstance( true );
    cgi.setLanguage(lim::asg::lnkJava);

    // get its owner Class
    java::asg::type::Type* rawType = javaType.getRawType();
    if ( rawType ) {

      java::asg::struc::TypeDeclaration* ref = NULL;
      java::asg::type::ClassType* rawTypeAsClassType =dynamic_cast<java::asg::type::ClassType*>( rawType );

      if (rawTypeAsClassType) {
        ref = rawTypeAsClassType->getRefersTo();
      }

      if ( ref ) {
        lim::asg::base::Base* owner = getLimPtr( ref );
        if ( ! owner ) {
          owner = & createLimNode( *ref );
        }

        if ( lim::asg::Common::getIsClass(*owner) ) {
          lim::asg::logical::Class& ownerClass = dynamic_cast<lim::asg::logical::Class&>( *owner );

          // set their connection
          //ownerClass.addInstance( cgi.getId() );
          SAFE_EDGE( ownerClass, Instance, lim::asg::logical::Member, cgi.getId() );
          // add the hasArguments edges
          if ( ! javaType.getArgumentTypesIsEmpty() )
          {
            for ( java::asg::ListIterator<java::asg::type::Type> i = javaType.getArgumentTypesListIteratorBegin();
                  i != javaType.getArgumentTypesListIteratorEnd();
                  ++i ) {
              NodeId param;
              lim::asg::TypeArgumentConstraintKind tack = lim::asg::tackNone;
              if ( java::asg::Common::getIsWildcardType(*i) ) {
                switch ( i->getNodeKind() ) {
                  case java::asg::ndkUpperBoundedWildcardType:  tack = lim::asg::tackUpperBounded;  break;
                  case java::asg::ndkLowerBoundedWildcardType:  tack = lim::asg::tackLowerBounded;  break;
                  case java::asg::ndkUnboundedWildcardType:     tack = lim::asg::tackUnbounded;     break;
                  default: 
                     common::WriteMsg::write(CMSG_UNHANDLED_NODE_KIND, i->getNodeKind());
                     break;  
                }
                param = getLimType( * dynamic_cast<const java::asg::type::WildcardType&>( *i ).getBound() ).getId();
              } else {
                param = getLimType( *i ).getId();
              }
              // SAFE ASSOC EDGE
              bool found = false;
              lim::asg::ListIteratorAssocTypeArgumentConstraintKind<lim::asg::type::Type> cIt = cgi.getArgumentsListIteratorAssocBegin();
              for ( ; cIt != cgi.getArgumentsListIteratorAssocEnd(); ++cIt ) {
                if ( cIt->getId() == param ) {
                  found = true;
                break;
                }
              }
              if ( ! found ) {
                cgi.addArguments( param, tack );
              }
            }
          }
        }
      } else {
        common::WriteMsg::write( CMSG_HAS_NOT_REFERS_TO );
      }
    } else {
      common::WriteMsg::write( CMSG_HAS_NOT_RAW_TYPE);
    }

    // insert into cgiMap and return
    cgiMap.insert( make_pair(uName, &cgi) );
    return cgi;
  }

  inline void JAN2LimVisitor::buildUnknown()
  {
    limFactory.addTypeFormer( limFactory.createTypeFormerType(limFactory.createSimpleType(lim::asg::stkUnknown).getId()).getId() );
  }

  void JAN2LimVisitor::addLimTypeFormers( const java::asg::type::Type& javaType )
  {
    // java::ArrayType --> TFArray + Component
    if ( java::asg::Common::getIsArrayType(javaType) )
    {
      limFactory.addTypeFormer( limFactory.createTypeFormerArray().getId() );
      if (dynamic_cast<const java::asg::type::ArrayType&>(javaType).getComponentType()) {
        addLimTypeFormers( * dynamic_cast<const java::asg::type::ArrayType&>(javaType).getComponentType() );
      }
    }

    // java::ClassType --> TFT(Class)
    else if ( java::asg::Common::getIsClassType(javaType) )
    {
      const java::asg::type::ClassType& classType = dynamic_cast<const java::asg::type::ClassType&>( javaType );
      java::asg::struc::TypeDeclaration* ref = classType.getRefersTo();
      if ( ! ref )
      {
        buildUnknown();
        return;
      }

      lim::asg::base::Base* refLimPtr = getLimPtr( ref );
      if ( ! refLimPtr ) 
        refLimPtr = & createLimNode( *ref );

      limFactory.addTypeFormer( limFactory.createTypeFormerType(refLimPtr->getId()).getId() );
    }

    // java::ParametrizedType --> ClassGenericInstance
    else if ( java::asg::Common::getIsParameterizedType(javaType) )
    {
      const java::asg::type::ParameterizedType& parType = dynamic_cast<const java::asg::type::ParameterizedType&>( javaType );

      lim::asg::logical::ClassGenericInstance& cgi = getCGIforJavaType( parType );
      limFactory.addTypeFormer( limFactory.createTypeFormerType(cgi.getId()).getId() );
    }

    // java::PrimitiveType --> TFT(SimpleType)
    else if ( java::asg::Common::getIsPrimitiveType(javaType) )
    {
      lim::asg::SimpleTypeKind stk = lim::asg::stkUnknown;
      java::asg::NodeKind ndk = javaType.getNodeKind();

      switch ( ndk )
      {
        case java::asg::ndkVoidType:    stk = lim::asg::stkVoid;      break;
        case java::asg::ndkBooleanType: stk = lim::asg::stkBoolean;   break;
        case java::asg::ndkCharType:    stk = lim::asg::stkCharacter; break;
        case java::asg::ndkByteType:    stk = lim::asg::stkByte;      break;
        case java::asg::ndkShortType:   stk = lim::asg::stkShort;     break;
        case java::asg::ndkIntType:     stk = lim::asg::stkInteger;   break;
        case java::asg::ndkLongType:    stk = lim::asg::stkLong;      break;
        case java::asg::ndkFloatType:   stk = lim::asg::stkFloat;     break;
        case java::asg::ndkDoubleType:  stk = lim::asg::stkDouble;    break;
        default: 
           common::WriteMsg::write(CMSG_UNHANDLED_NODE_KIND, ndk);
           break;  
      }

      limFactory.addTypeFormer( limFactory.createTypeFormerType(limFactory.createSimpleType(stk).getId()).getId() );
    }

    // java::TypeVariable --> TFT(GenericParameter)
    else if ( java::asg::Common::getIsTypeVariable(javaType) )
    {
      const java::asg::type::TypeVariable& typeVar = dynamic_cast<const java::asg::type::TypeVariable&>( javaType );
      java::asg::struc::TypeParameter* ref = typeVar.getRefersTo();
      if ( ! ref )
      {
        buildUnknown();
        return;
      }
      lim::asg::base::Base* refLimPtr = getLimPtr( ref );
      if ( ! refLimPtr ) {
        refLimPtr = & createLimNode( *ref );
      }

      limFactory.addTypeFormer( limFactory.createTypeFormerType(refLimPtr->getId()).getId() );
    }

    // java::ErrorType, java::NullType, java::NoType --> TFNonType
    else if
    (
      java::asg::Common::getIsErrorType(javaType)
      || java::asg::Common::getIsNullType(javaType)
      || java::asg::Common::getIsNoType(javaType)
    )
    {
      limFactory.addTypeFormer( limFactory.createTypeFormerNonType().getId() );
    }
    else if (  java::asg::Common::getIsUnionType(javaType) )
    {
      const java::asg::type::UnionType& typeVar = dynamic_cast<const java::asg::type::UnionType&>( javaType );
      for (java::asg::ListIterator<java::asg::type::Type> it = typeVar.getAlternativesListIteratorBegin();it != typeVar.getAlternativesListIteratorEnd();++it) {
        const java::asg::type::Type& ref = *it;
        addLimTypeFormers(ref);
      }
    }
    else if (java::asg::Common::getIsIntersectionType(javaType))
    {
      const java::asg::type::IntersectionType& typeVar = dynamic_cast<const java::asg::type::IntersectionType&>(javaType);
      for (java::asg::ListIterator<java::asg::type::Type> it = typeVar.getBoundsListIteratorBegin(); it != typeVar.getBoundsListIteratorEnd(); ++it) {
        const java::asg::type::Type& ref = *it;
        addLimTypeFormers(ref);
      }
    }
    else if( java::asg::Common::getIsWildcardType(javaType) )
    {
      const java::asg::type::WildcardType& wildCard = dynamic_cast<const java::asg::type::WildcardType&>( javaType );
      
      java::asg::type::Type * bound = wildCard.getBound();
      if ( ! bound )
      {
        buildUnknown();
        return;
      }
      addLimTypeFormers(*bound);
    }

    else if ( java::asg::Common::getIsMethodType(javaType) )
    {
      const java::asg::type::MethodType& methodType = dynamic_cast<const java::asg::type::MethodType&>(javaType);

      limFactory.beginTypeFormerMethod();

      if (methodType.getReturnType()) {
        lim::asg::base::Base& limRetType = getLimType(*methodType.getReturnType());
        limFactory.setTypeFormerMethodHasReturnType(limRetType.getId());
      }

      for (java::asg::ListIterator<java::asg::type::Type> it = methodType.getParameterTypesListIteratorBegin(); it != methodType.getParameterTypesListIteratorEnd(); ++it) {
        lim::asg::base::Base& limParamType = getLimType(*it);
        limFactory.addTypeFormerMethodHasParameterType(limParamType.getId(), lim::asg::ParameterKind::pmkInOut);
      }

      lim::asg::type::TypeFormerMethod& limMethodType = limFactory.endTypeFormerMethod();
      limFactory.addTypeFormer(limMethodType.getId());
    }

    // nothing matched --> Exception
    // - PackageType is not expected
    // - WildcardType can only appear inside a ParametrizedType
    // - UnionType can only appear when visiting TypeExpressions
    else
    {
      throw Exception( COLUMBUS_LOCATION, CMSG_EX_UNEXPECTED_TYPE( javaType.getId(), javaType.getNodeKind() ) );
    }
  }

  lim::asg::type::Type& JAN2LimVisitor::getLimType( const java::asg::type::Type& javaType ) // FIXME miert nem pointerrel ter vissza, azt lehetne vizsgalni
  {
    common::WriteMsg::write(CMSG_CONVERT_JAVA2LIM, javaType.getId());

    TypeMap::const_iterator i = typeMap.find( & javaType );
    if ( i != typeMap.end() ) return * i->second;
    
    limFactory.beginType();
    addLimTypeFormers( javaType );
    lim::asg::type::Type& limType = limFactory.endType();

    typeMap.insert( make_pair<const java::asg::type::Type*, lim::asg::type::Type*>(&javaType, &limType) );
    return limType;
  }

  lim::asg::type::Type& JAN2LimVisitor::getUnknownType()
  {
    limFactory.beginType();
    buildUnknown();
    return limFactory.endType();
  }


  //
  // DATA TRANSFER
  //

  template<class L, class J> L* JAN2LimVisitor::buildDispatch( const java::asg::base::Base& javaNode )
  {
    bool isClass = java::asg::Common::getIsTypeDeclaration( javaNode );

    L* limNodeAsBase = dynamic_cast<L*> (getLimPtr( javaNode ));
    if (!limNodeAsBase) {
      common::WriteMsg::write(CMSG_NO_NODE_TO_DISPATCH);
      return NULL;
    }

    L& limNode = static_cast<L&>( *limNodeAsBase );
    string className = "";
    if ( isClass && (common::WriteMsg::getMessageLevel() >= common::WriteMsg::mlDDebug)) className = getUniqueName( javaNode );

    bool javaPos = hasPosition( javaNode );

    // we transfer data if
    // - the lim node is in the Incomplete state and neither of the nodes have a position
    // - or the lim node is in the Incomplete or ExternalBuilt state and the java node has a position
    bool fill = false;
    if (((getState(&limNode) == Incomplete) && (!javaPos)) || java::asg::Common::getIsPackage(javaNode) )
    {
      if ( isClass )
      {
        classStats.external++;
        if ( common::WriteMsg::getMessageLevel() >= common::WriteMsg::mlDDebug )
        {
          common::WriteMsg::write( CMSG_NEW_EXT_CLASS, className.c_str() );
        }
      }
      fill = true;
      setState( &limNode, ExternalBuilt );
    }
    else if ( (getState(&limNode) == Incomplete || getState(&limNode) == ExternalBuilt) && javaPos )
    {
      if ( isClass )
      {
        classStats.source++;
        if ( getState(&limNode) == ExternalBuilt )
        {
          classStats.external--;
          classStats.converted++;
          common::WriteMsg::write( CMSG_EXT2COMPLETE_CLASS, className.c_str() );
        }
        else
        {
          common::WriteMsg::write( CMSG_NEW_COMPLETE_CLASS, className.c_str() );
        }
      }
      fill = true;
      setState( &limNode, Complete );
    }
    else if ( isClass )
    {
      classStats.irrelevant++;
      common::WriteMsg::write( CMSG_IRRELEVANT_CLASS, className.c_str() );
    }

    // if the data transfer is necessary
    if ( fill )
    {
      // create usesSet for the new Members
      if ( lim::asg::Common::getIsMember(limNode) ) usesStack.push( set<NodeId>() );

      // fill its data
      //TODO find out how to check the dynamic_cast
      fillData( limNode, dynamic_cast<const J&>(javaNode) );
    }

    // otherwise skip everything until we reach the visitEnd of this node
    else
    {
      skipUntil = javaNode.getId();
    }

    // return a reference to the node
    return &limNode;
  }

  bool JAN2LimVisitor::hasPosition( const java::asg::base::Base& javaNode )
  {
    if ( java::asg::Common::getIsPositioned(javaNode) )
    {
      java::asg::Range pos = dynamic_cast<const java::asg::base::Positioned&>( javaNode ).getPosition();

      if
      (
        pos.getPathKey()
        || pos.getWideLine()
        || pos.getWideCol()
        || pos.getWideEndLine()
        || pos.getWideEndCol()
      )
      {
        return true;
      }
    }

    return false;
  }

  void JAN2LimVisitor::fillMemberData( lim::asg::logical::Member& limNode, const java::asg::base::Base& javaNode )
  {
    bool initBlock = java::asg::Common::getIsInitializerBlock( javaNode );
    bool positioned = java::asg::Common::getIsPositioned( javaNode );

    // ----------------------- DATA

    // accessibility && isStatic && isCompilerGenerated
    if ( java::asg::Common::getIsNamedDeclaration(javaNode) )
    {
      const java::asg::struc::NamedDeclaration& namedDeclaration = dynamic_cast<const java::asg::struc::NamedDeclaration&>( javaNode );

      lim::asg::AccessibilityKind limAck = lim::asg::ackPublic;
      switch ( namedDeclaration.getAccessibility() )
      {
        case java::asg::ackPrivate:   limAck = lim::asg::ackPrivate;        break;
        case java::asg::ackProtected: limAck = lim::asg::ackProtected;      break;
        case java::asg::ackPublic:    limAck = lim::asg::ackPublic;         break;
        case java::asg::ackNone:      limAck = lim::asg::ackPackagePrivate; break;
        default:
          limAck = lim::asg::ackPrivate;
          common::WriteMsg::write(CMSG_UNHANDLED_ACCESSIBILITY, java::asg::Common::toString(namedDeclaration.getAccessibility()).c_str());
          break;
      }
      limNode.setAccessibility( limAck );
      limNode.setIsStatic( namedDeclaration.getIsStatic() );
      limNode.setIsCompilerGenerated( namedDeclaration.getIsCompilerGenerated() );
    }
    else
    {
      limNode.setAccessibility( lim::asg::ackPublic );
      limNode.setIsStatic( java::asg::Common::getIsStaticInitializerBlock( javaNode ) );
      limNode.setIsCompilerGenerated( false );
    }

    // hasComment, commentLines are built when visiting java::Commentable nodes

    // mangledName
    if
    (
      java::asg::Common::getIsTypeDeclaration( javaNode )
      || java::asg::Common::getIsMethodDeclaration( javaNode ) 
      || ( java::asg::Common::getIsVariableDeclaration( javaNode ) && java::asg::Common::getIsTypeDeclaration( *javaNode.getParent() ) )
      || java::asg::Common::getIsPackage( javaNode )
      || java::asg::Common::getIsInitializerBlock( javaNode )
      || java::asg::Common::getIsLambda(javaNode)
    )
    {
      limNode.setMangledName( java::asg::Common::getLongName( javaNode ) );
    }
    else
    {
      limNode.setMangledName( getUniqueName( javaNode ) );
    }

    // demangledName --> from mangledName
    limNode.setDemangledName( limNode.getMangledName() );

    limNode.setLanguage(lim::asg::lnkJava);

    // ----------------------- EDGES

    // isContainedIn
    // ( Packaged are treated separately )
    if ( positioned )
    {
      addIsContainedInEdge( limNode, dynamic_cast<const java::asg::base::Positioned&>( javaNode ) );
    }

    // belongsTo
    if ( ! initBlock ) SAFE_EDGE( limNode, BelongsTo, lim::asg::base::Component, component.getId() );
    else methodStack.top().belongsTo.insert( component.getId() );

    // compilationUnit --> irrelevant in java

    // hasMember
    if ( javaNode.getId() == javaFactory.getRoot()->getId() ) return;
  
    java::asg::base::Base* javaParent = & const_cast<java::asg::base::Base&>( javaNode );
    lim::asg::base::Base* limParent;
    do
    {
      javaParent = javaParent ? getParentPtr( * javaParent ): NULL;

      if (javaParent ) {
        limParent = getLimPtr( javaParent );
      } else  {
        limParent = NULL;
      }
    }
    while ( limParent && ! lim::asg::Common::getIsScope(*limParent) );

    if (  limParent ) {
      lim::asg::logical::Scope* parentScope = dynamic_cast<lim::asg::logical::Scope*>( limParent );

      if ( ! initBlock )
      {
        lim::asg::logical::Scope& parentScopeRef = (*parentScope);
        SAFE_EDGE( parentScopeRef, Member, lim::asg::logical::Member, limNode.getId() );
      }
      else
      {
        if ( ! methodStack.empty() ) methodStack.top().hasMember.insert( parentScope->getId() );
        else common::WriteMsg::write( CMSG_METHODE_STACK_IS_EMPTY);
      }
    }
    // aggregated, variant --> irrelevant in java

    // uses --> filled when visiting java::TypeExpression nodes

    // separate LLOC mapping for limCompatible nodes
    // ( when the stacks are already updated AND the hasMember edges are already present )
    if ( positioned ) insertLLOCMap( dynamic_cast<const java::asg::base::Positioned&>( javaNode ) );
  }

  void JAN2LimVisitor::fillScopeData( lim::asg::logical::Scope& limNode, const java::asg::base::Base& javaNode )
  {
    // Upcall --> Member
    fillMemberData( limNode, javaNode );

    // ----------------------- DATA

    // LLOC, TLLOC --> line info is gathered when visiting java::Positioned nodes, finalized separately in the end by setLLOC

    // isAnonymous
    limNode.setIsAnonymous( java::asg::Common::getIsAnonymousClass(javaNode) || java::asg::Common::getIsLambda(javaNode) );
  }

  void JAN2LimVisitor::fillData( lim::asg::logical::Package& limNode, const java::asg::struc::Package& javaNode )
  {
    // Stack
    packageStack.push( PackageInfo() );
    packageStack.top().package = limNode.getId();

    // Upcall --> Scope
    fillScopeData( limNode, javaNode );

    // Package isContainedIn + Component TLOC info
    java::asg::ListIterator<java::asg::struc::CompilationUnit> cuIt = javaNode.getCompilationUnitsListIteratorBegin();
    for ( ; cuIt != javaNode.getCompilationUnitsListIteratorEnd(); ++cuIt )
    {
      const java::asg::Range& range = cuIt->getPosition();
      Key key = limFactory.getStringTable().set( range.getPath() );
      if ( key == 0 ) continue;

      addIsContainedInEdge( limNode, *cuIt );
      addLocToComponent( component.getId(), key, range.getWideEndLine() );
    }
  }

  void JAN2LimVisitor::fillData( lim::asg::logical::Class& limNode, const java::asg::struc::TypeDeclaration& javaNode )
  {
    // Stack
    classStack.push( ClassInfo() );
    classStack.top().clazz = limNode.getId();

    // Upcall --> Scope
    fillScopeData( limNode, javaNode );

    // ----------------------- DATA

    // class kind
    lim::asg::ClassKind limClk = lim::asg::clkClass;
    if      ( java::asg::Common::getIsInterfaceDeclaration(javaNode) ) limClk = lim::asg::clkInterface;
    else if ( java::asg::Common::getIsEnum(javaNode) )                 limClk = lim::asg::clkEnum;
    else if ( java::asg::Common::getIsAnnotationType(javaNode) )       limClk = lim::asg::clkAnnotation;

    limNode.setClassKind( limClk );

    // abstract
    limNode.setIsAbstract( javaNode.getIsAbstract() );

    // ----------------------- EDGES

    // grantsFriendship --> irrelevant in java

    // isSubclass
    java::asg::expr::TypeExpression* sc = javaNode.getSuperClass();
    if (sc) {
      if (sc->getType() && ! classStack.empty()) {
        classStack.top().isSubclass.insert( getLimType(*sc->getType()).getId() );
      } else {
        common::WriteMsg::write(CMSG_TYPE_EXPR_WITHOUT_TYPE);
      }
    } 

    // isSubclass -- interfaces
    if ( ! javaNode.getSuperInterfacesIsEmpty() && ! classStack.empty() )
    {
      for ( java::asg::ListIterator<java::asg::expr::TypeExpression> i = javaNode.getSuperInterfacesListIteratorBegin(); i != javaNode.getSuperInterfacesListIteratorEnd(); ++i )
      {
        if (i->getType()) {
          classStack.top().isSubclass.insert( getLimType(*i->getType()).getId() );
        }
      }
    }

    // the hasGenericParameter edges are created when visiting the java::TypeParameter nodes
  }

  void JAN2LimVisitor::fillData( lim::asg::logical::Method& limNode, const java::asg::base::Base& javaNode )
  {
    // Stack
    if ( ! java::asg::Common::getIsInitializerBlock(javaNode) )
    {
      methodStack.push( MethodInfo() );
      methodStack.top().method = limNode.getId();
    }

    // Upcall --> Scope
    fillScopeData( limNode, javaNode );

    // ----------------------- DATA

    // method kind && abstract
    if ( java::asg::Common::getIsNormalMethod(javaNode) )
    {
      const java::asg::struc::NormalMethod& javaMethod = dynamic_cast<const java::asg::struc::NormalMethod&>( javaNode );
      limNode.setIsAbstract( javaMethod.getIsAbstract() );

      // if it's a member of an interface, it is automatically marked public and abstract
      if ( !classStack.empty() )
      {
        const lim::asg::logical::Class& parentClass = dynamic_cast<const lim::asg::logical::Class&>( limFactory.getRef( classStack.top().clazz ) );
        if ( parentClass.getClassKind() == lim::asg::clkInterface )
        {
          limNode.setAccessibility( lim::asg::ackPublic );
          limNode.setIsAbstract( true );
        }
      }

      lim::asg::MethodKind limKind = lim::asg::mekNormal;
      switch ( javaMethod.getMethodKind() )
      {
        case java::asg::mekConstructor:
        case java::asg::mekGeneratedAnonymousClassConstructor:
        case java::asg::mekGeneratedDefaultConstructor:         limKind = lim::asg::mekConstructor; break;
        default:                                                limKind = lim::asg::mekNormal;      break;
      }

      if ( common::isGetter(javaMethod.getName()) ) limKind = lim::asg::mekGet;
      else if ( common::isSetter(javaMethod.getName()) ) limKind = lim::asg::mekSet;

      limNode.setMethodKind( limKind );
    }
    else if ( java::asg::Common::getIsInitializerBlock(javaNode) )
    {
      // default values for init blocks
      limNode.setIsAbstract( false );
      limNode.setMethodKind( lim::asg::mekNormal );
    }
    else if ( java::asg::Common::getIsLambda(javaNode) )
    {
      // default values for lambdas
      limNode.setAccessibility( lim::asg::ackNone );
      limNode.setIsAbstract( false );
      limNode.setMethodKind( lim::asg::mekNormal );
    }
    else
    {
      // default values for annotations
      limNode.setIsAbstract( true );
      limNode.setMethodKind( lim::asg::mekNormal );
    }

    // virtual
    limNode.setIsVirtual( true );

    // nestingLevel       }
    // nestingLevelElseIf }
    // numberOfStatements }
    // numberOfBranches   } are computed between visit and visitEnd

    // halstead
    if (java::asg::Common::getIsMethodDeclaration(javaNode)) { // TODO lambda ?
      if (!dynamic_cast<const java::asg::base::Positioned&>(javaNode).getIsCompilerGenerated()) {
        HalsteadVisitor::HalsteadInfo& mi = halsteadValues[javaNode.getId()];
        limNode.setTotalOperators(mi.N1);
        limNode.setTotalOperands(mi.N2);
        limNode.setDistinctOperators(mi.n1);
        limNode.setDistinctOperands(mi.n2);
      }
    }

    // ----------------------- EDGES

    // the hasParameter edges are created when visiting the java::Parameter nodes

    // returns && canThrow
    if ( java::asg::Common::getIsMethodDeclaration(javaNode) )
    {
      const java::asg::struc::MethodDeclaration& methodDecl = dynamic_cast<const java::asg::struc::MethodDeclaration&>( javaNode );

      // returns
      if ( limNode.getMethodKind() != lim::asg::mekConstructor && limNode.getReturnsIsEmpty() )
      {
        java::asg::expr::TypeExpression* returnTE = methodDecl.getReturnType();
        if ( returnTE && returnTE->getType() )
        {
          limNode.addReturns( getLimType(*returnTE->getType()).getId() );
        }
        else
        {
          common::WriteMsg::write(CMSG_METHOD_WITHOUT_RETURN_TYPE);
        }
      }

      // canThrow
      if ( java::asg::Common::getIsNormalMethod( javaNode ) )
      {
        const java::asg::struc::NormalMethod& normalMethod = dynamic_cast<const java::asg::struc::NormalMethod&>( javaNode );

        if ( !normalMethod.getThrownExceptionsIsEmpty() )
        {
          java::asg::ListIterator<java::asg::expr::TypeExpression> i = normalMethod.getThrownExceptionsListIteratorBegin();
          for ( ; i != normalMethod.getThrownExceptionsListIteratorEnd(); ++i )
          {
            if ( i->getType() && !methodStack.empty() )
            {
              methodStack.top().canThrow.insert( getLimType(*i->getType()).getId() );
            }
          }
        }
      }
    }

    // calls is filled when visiting java::MethodInvocation nodes, finalized in visitEnd
    // instantiates is filled when visiting java::NewClass nodes, finalized in visitEnd
    // accessesAttribute is filled when visiting java::Identifier nodes, finalized in visitEnd
    // throws is filled when visiting java::statm::Throw nodes, finalized in visitEnd
    // the hasGenericParameter edges are created when visiting the java::TypeParameter nodes
  }

  void JAN2LimVisitor::fillData( lim::asg::logical::Attribute& limNode, const java::asg::struc::VariableDeclaration& javaNode )
  {
    // Stack
    attributeStack.push( AttributeInfo() );
    attributeStack.top().attribute = limNode.getId();

    // Upcall --> Member
    fillMemberData( limNode, javaNode );

    // Class relations
    if ( ! classStack.empty() )
    {
      if ( limNode.getIsStatic() ) classStack.top().hasStaticAttributes = true;
      else classStack.top().hasInstanceAttributes = true;

      // if it's a member of an interface, it is automatically marked public
      const lim::asg::logical::Class& parentClass = dynamic_cast<const lim::asg::logical::Class&>( limFactory.getRef( classStack.top().clazz ) );
      if ( parentClass.getClassKind() == lim::asg::clkInterface )
      {
        limNode.setAccessibility( lim::asg::ackPublic );
      }
    }

    // ----------------------- EDGES

    // hasType
    java::asg::expr::TypeExpression* javaTE = javaNode.getType();
    if ( javaTE && javaTE->getType() )
    {
      lim::asg::type::Type& limType = getLimType( * javaTE->getType() );
      if ( limNode.getTypeIsEmpty() ) limNode.addType( limType.getId() );
    }
    else
    {
      limNode.addType( getUnknownType().getId() );
      if ( javaTE ) common::WriteMsg::write(CMSG_TYPE_EXPR_WITHOUT_TYPE);
      else common::WriteMsg::write(CMSG_ATTRIB_WITHOUT_TYPE_EXPR);
    }

    // calls is filled when visiting java::MethodInvocation nodes, finalized in visitEnd
  }

  void JAN2LimVisitor::fillData( lim::asg::logical::GenericParameter& limNode, const java::asg::struc::TypeParameter& javaNode )
  {
    // ----------------------- DATA

    // genericParameterKind
    limNode.setGenericParameterKind( lim::asg::gpkType );

    // ----------------------- EDGES

    // hasParameterConstraint
    for ( java::asg::ListIterator<java::asg::expr::TypeExpression> i = javaNode.getBoundsListIteratorBegin(); i != javaNode.getBoundsListIteratorEnd(); ++i )
    {
      if ( i->getType()) {
        lim::asg::type::Type& limType = getLimType( * i->getType() );
        //limNode.addParameterConstraint( limType.getId() );
        SAFE_EDGE( limNode, ParameterConstraint, lim::asg::type::Type, limType.getId() );
      }
    }

    lim::asg::base::Base* limParent = getLimPtr( getParentPtr(javaNode) );
    if (limParent) {
      // hasGenericParameter
      if ( lim::asg::Common::getIsMethodGeneric(*limParent) )
      {
        lim::asg::logical::MethodGeneric& mg = static_cast<lim::asg::logical::MethodGeneric&>( * limParent );
        //mg.addGenericParameter( limNode.getId() );
        SAFE_EDGE( mg, GenericParameter, lim::asg::logical::GenericParameter, limNode.getId() );
      }
      else if ( lim::asg::Common::getIsClassGeneric(*limParent) )
      {
        lim::asg::logical::ClassGeneric& cg = static_cast<lim::asg::logical::ClassGeneric&>( * limParent );
        //cg.addGenericParameter( limNode.getId() );
        SAFE_EDGE( cg, GenericParameter, lim::asg::logical::GenericParameter, limNode.getId() );
      }
    }

    insertLLOCMap( javaNode );
  }

  void JAN2LimVisitor::fillData( lim::asg::logical::Parameter& limNode, const java::asg::struc::Parameter& javaNode )
  {
    // ----------------------- DATA

    // genericParameterKind
    limNode.setParamKind( lim::asg::pmkIn );

    // ----------------------- EDGES

    // hasType
    java::asg::expr::TypeExpression* javaTE = javaNode.getType();
    if ( javaTE && javaTE->getType() )
    {
      lim::asg::type::Type& limType = getLimType( * javaTE->getType() );
      limNode.setType( limType.getId() );
    }
    else
    {
      limNode.setType( getUnknownType().getId() );
      common::WriteMsg::write(CMSG_PARAM_WITHOUT_TYPE_EXPR);
    }

    if ( (!methodStack.empty()) && methodStack.top().method) {
      // hasParameter
      lim::asg::logical::Method& parent = dynamic_cast<lim::asg::logical::Method&>( limFactory.getRef( methodStack.top().method ) );
      SAFE_EDGE( parent, Parameter, lim::asg::logical::Parameter, limNode.getId() );
    }

    insertLLOCMap( javaNode );
  }

  void JAN2LimVisitor::fillCollectedMethodData( lim::asg::logical::Method& method, const MethodInfo& methodInfo )
  {
    method.setNestingLevel( methodInfo.NL );
    method.setNestingLevelElseIf( methodInfo.NLE );
    method.setNumberOfBranches( methodInfo.NOB );
    method.setNumberOfStatements( methodInfo.NOS );

    set<NodeId>::iterator i;

    for ( i = methodInfo.calls.begin();             i != methodInfo.calls.end();              ++i ) SAFE_EDGE( method, Calls, lim::asg::logical::MethodCall, *i );
    for ( i = methodInfo.throws.begin();            i != methodInfo.throws.end();             ++i ) SAFE_EDGE( method, Throws, lim::asg::type::Type, *i );
    for ( i = methodInfo.canThrow.begin();          i != methodInfo.canThrow.end();           ++i ) SAFE_EDGE( method, CanThrow, lim::asg::type::Type, *i );
    for ( i = methodInfo.instantiates.begin();      i != methodInfo.instantiates.end();       ++i ) SAFE_EDGE( method, Instantiates, lim::asg::type::Type, *i );
    for ( i = methodInfo.accessesAttribute.begin(); i != methodInfo.accessesAttribute.end();  ++i ) SAFE_EDGE( method, AccessesAttribute, lim::asg::logical::AttributeAccess, *i );

    set<NodeId>& usesSet = usesStack.top();

    if ( ! method.getReturnsIsEmpty() ) usesSet.erase( method.getReturnsListIteratorBegin()->getId() );
    erase( usesSet, methodInfo.throws );
    erase( usesSet, methodInfo.canThrow );
    erase( usesSet, methodInfo.instantiates );

    addUses( method, usesSet );
  }

  void JAN2LimVisitor::fillInitBlockData( const MethodInfo& methodInfo )
  {
    if ( methodInfo.method )
    {
      lim::asg::logical::Method& method = dynamic_cast<lim::asg::logical::Method&>( limFactory.getRef( methodInfo.method ) );
      fillCollectedMethodData( method, methodInfo );

      for ( set<NodeId>::iterator i = methodInfo.belongsTo.begin(); i != methodInfo.belongsTo.end(); ++i )
      {
        method.addBelongsTo( *i );
      }
      for ( set<NodeId>::iterator i = methodInfo.hasMember.begin(); i != methodInfo.hasMember.end(); ++i )
      {
        dynamic_cast<lim::asg::logical::Scope&>( limFactory.getRef( *i ) ).addMember( method.getId() );
      }

      initBlocks.insert( method.getId() );
    }
  }

  void JAN2LimVisitor::addUses( lim::asg::logical::Member& member, const set<NodeId>& ids )
  {
    bool firstRun = member.getUsesIsEmpty();
    for ( set<NodeId>::const_iterator i = ids.begin(); i != ids.end(); ++i )
    {
      if ( firstRun ) member.addUses( *i );
      else SAFE_EDGE( member, Uses, lim::asg::type::Type, *i );
    }
  }

  void JAN2LimVisitor::propagateFilter( const java::asg::base::Base& javaNode, lim::asg::base::Base* limPtr, bool first = false )
  {
    if ( ! isLimCompatible( javaNode ) ) return;

    bool limFiltered = limFactory.getFilterState( limPtr->getId() ) == lim::asg::Filter::Filtered;
    bool javaFiltered = javaFactory.getFilterState( javaNode.getId() ) == java::asg::Filter::Filtered;
    bool javaCompGen = java::asg::Common::getIsPositioned( javaNode ) && dynamic_cast<const java::asg::base::Positioned&>( javaNode ).getIsCompilerGenerated();

    // we filter the node if
    // - it's the first time we've seen it and the java node is filtered or compiler generated
    // - both the java and the lim nodes are filtered or compiler generated
    if ( (first && (javaFiltered || javaCompGen)) || (!first && (javaFiltered || javaCompGen) && limFiltered) ) limFactory.setFilteredThisNodeOnly( limPtr->getId() );

    // otherwise we set it to NOT filtered
    else limFactory.setNotFilteredThisNodeOnly( limPtr->getId() );
  }

  //
  //  MAIN LOGICAL BUILD VISITORS
  //

  /**********************************************/
  /*        java::Package --> lim::Package      */
  /**********************************************/
  void JAN2LimVisitor::visit( const java::asg::struc::Package& node, bool callVirtualBase )
  {
    VISIT_BEGIN( node, callVirtualBase, "Package" );
    buildDispatch<lim::asg::logical::Package, java::asg::struc::Package>( node );
  }

  void JAN2LimVisitor::visitEnd( const java::asg::struc::Package& node, bool callVirtualBase )
  {
    VISIT_END_FIRST( node, "Package" );
    
    if ( ! packageStack.empty() && packageStack.top().package && !usesStack.empty() )
    {
      lim::asg::logical::Package& package = dynamic_cast<lim::asg::logical::Package&>( limFactory.getRef( packageStack.top().package ) );
      addUses( package, usesStack.top() );
      packageStack.pop();
      usesStack.pop();
    }

    VISIT_END( node, callVirtualBase, "Package" );
  }


  /******************************************************************************/
  /*        java::TypeDeclaration --> lim::Class                                */
  /*        java::TypeDeclaration && GenericDeclaration --> lim::ClassGeneric   */
  /******************************************************************************/
  void JAN2LimVisitor::visit( const java::asg::struc::TypeDeclaration& node, bool callVirtualBase )
  {
    classStats.total++;
    VISIT_BEGIN( node, callVirtualBase, "TypeDeclaration" );
    buildDispatch<lim::asg::logical::Class, java::asg::struc::TypeDeclaration>( node );
  }

  void JAN2LimVisitor::visitEnd( const java::asg::struc::TypeDeclaration& node, bool callVirtualBase )
  {
    VISIT_END_FIRST( node, "TypeDeclaration" );

    if ( ! classStack.empty() ) {
      ClassInfo& classInfo = classStack.top();
    
      if ( buildEmptyInitBlocks )
      {
        // Instance
        if ( ! classInfo.instanceInit.method && classInfo.hasInstanceAttributes )
        {
          classInfo.instanceInit = createEmptyInitBlock( dynamic_cast<lim::asg::logical::Class*>( limFactory.getPointer( classInfo.clazz )), false );
        }

        // Static
        if ( ! classInfo.staticInit.method && classInfo.hasStaticAttributes )
        {
          classInfo.staticInit = createEmptyInitBlock( dynamic_cast<lim::asg::logical::Class*>( limFactory.getPointer( classInfo.clazz )), true );
        }
      }

      // finalizing InitBlock-related data
      fillInitBlockData( classInfo.instanceInit );
      fillInitBlockData( classInfo.staticInit );

      if ( classInfo.clazz )
      {
        // add isSubclass edges
        lim::asg::logical::Class& clazz = dynamic_cast<lim::asg::logical::Class&>( limFactory.getRef( classInfo.clazz ) );
        bool firstRun = clazz.getIsSubclassIsEmpty();
        for ( set<NodeId>::iterator i = classInfo.isSubclass.begin(); i != classInfo.isSubclass.end(); ++i )
        {
          if ( firstRun ) clazz.addIsSubclass( *i );
          else SAFE_EDGE( clazz, IsSubclass, lim::asg::type::Type, *i );
        }
    
        // add uses edges
        set<NodeId>& usesSet = usesStack.top();
        erase( usesSet, classInfo.isSubclass );
        addUses( clazz, usesSet );
      }

      classStack.pop();
      usesStack.pop();
    }

    VISIT_END( node, callVirtualBase, "TypeDeclaration" );
  }


  /************************************************************/
  /*        java::Method --> lim::Method                      */
  /*        java::AnnotationTypeElement --> lim::Method       */
  /*        java::MethodGeneric --> lim::MethodGeneric        */
  /************************************************************/
  void JAN2LimVisitor::visit( const java::asg::struc::MethodDeclaration& node, bool callVirtualBase )
  {
    VISIT_BEGIN( node, callVirtualBase, "MethodDeclaration" );
    buildDispatch<lim::asg::logical::Method, java::asg::struc::Declaration>( node );
  }

  void JAN2LimVisitor::visitEnd( const java::asg::struc::MethodDeclaration& node, bool callVirtualBase )
  {
    VISIT_END_FIRST( node, "MethodDeclaration" );
    if ( methodStack.size() > 0 && methodStack.top().method )
    {
      MethodInfo& methodInfo = methodStack.top();
      lim::asg::logical::Method& method = dynamic_cast<lim::asg::logical::Method&>( limFactory.getRef( methodInfo.method ) );
      fillCollectedMethodData( method, methodInfo );

      methodStack.pop();
      usesStack.pop();
    }
    else common::WriteMsg::write(CMSG_METHODE_STACK_IS_EMPTY);
    
    VISIT_END( node, callVirtualBase, "MethodDeclaration" );
  }


  /****************************************************/
  /*        java::Variable --> lim::Attribute         */
  /*        java::EnumConstant --> lim::Attribute     */
  /****************************************************/
  void JAN2LimVisitor::visit( const java::asg::struc::VariableDeclaration& node, bool callVirtualBase )
  {
    VISIT_BEGIN( node, callVirtualBase, "VariableDeclaration" );

    if ( ! isClassLevelVariable(node) ) return;

    buildDispatch<lim::asg::logical::Attribute, java::asg::struc::VariableDeclaration>( node );
  }

  void JAN2LimVisitor::visitEnd( const java::asg::struc::VariableDeclaration& node, bool callVirtualBase )
  {
    VISIT_END_FIRST( node, "VariableDeclaration" );

    if ( isClassLevelVariable(node) ) {
      if ( ! attributeStack.empty() && getLimPtr(node)->getId() == attributeStack.top().attribute )
      {
        AttributeInfo& ai = attributeStack.top();
        if ( ai.attribute )
        {
          lim::asg::logical::Attribute& attr = dynamic_cast<lim::asg::logical::Attribute&>( limFactory.getRef( ai.attribute ) );
          bool firstRun = attr.getCallsIsEmpty();
          for ( set<NodeId>::const_iterator i = ai.calls.begin(); i != ai.calls.end(); ++i )
          {
            if ( firstRun ) attr.addCalls( *i );
            else SAFE_EDGE( attr, Calls, lim::asg::logical::MethodCall, *i );
          }

          set<NodeId>& usesSet = usesStack.top();
          usesSet.erase( attr.getTypeListIteratorBegin()->getId() );
          addUses( attr, usesSet );
        }

        attributeStack.pop();
        usesStack.pop();
      }
    }

    VISIT_END( node, callVirtualBase, "VariableDeclaration" );
  }


  /****************************************************************/
  /*        java::TypeParameter --> lim::GenericParameter         */
  /****************************************************************/
  void JAN2LimVisitor::visit( const java::asg::struc::TypeParameter& node, bool callVirtualBase )
  {
    VISIT_BEGIN( node, callVirtualBase, "TypeParameter" );
    buildDispatch<lim::asg::logical::GenericParameter, java::asg::struc::TypeParameter>( node );
  }

  void JAN2LimVisitor::visitEnd( const java::asg::struc::TypeParameter& node, bool callVirtualBase )
  {
    VISIT_END_FIRST( node, "TypeParameter" );
    VISIT_END( node, callVirtualBase, "TypeParameter" );
  }


  /*****************************************************/
  /*        java::Parameter --> lim::Parameter         */
  /*****************************************************/
  void JAN2LimVisitor::visit( const java::asg::struc::Parameter& node, bool callVirtualBase )
  {
    VISIT_BEGIN( node, callVirtualBase, "Parameter" );

    // only visit parameters of NormalMethods
    if ( ! isMethodParameter(node) ) return;

    buildDispatch<lim::asg::logical::Parameter, java::asg::struc::Parameter>( node );
  }

  void JAN2LimVisitor::visitEnd( const java::asg::struc::Parameter& node, bool callVirtualBase )
  {
    VISIT_END_FIRST( node, "Parameter" );
    VISIT_END( node, callVirtualBase, "Parameter" );
  }

  
  /************************************************************/
  /*        java::Lambda --> lim::Method                      */
  /************************************************************/
  void JAN2LimVisitor::visit( const java::asg::expr::Lambda& node, bool callVirtualBase )
  {
    VISIT_BEGIN( node, callVirtualBase, "Lambda" );
    buildDispatch<lim::asg::logical::Method, java::asg::expr::Lambda>( node );
  }

  void JAN2LimVisitor::visitEnd( const java::asg::expr::Lambda& node, bool callVirtualBase )
  {
    VISIT_END_FIRST( node, "Lambda" );
    if ( methodStack.size() > 0 && methodStack.top().method )
    {
      MethodInfo& methodInfo = methodStack.top();
      lim::asg::logical::Method& method = dynamic_cast<lim::asg::logical::Method&>( limFactory.getRef( methodInfo.method ) );
      fillCollectedMethodData( method, methodInfo );

      methodStack.pop();
      usesStack.pop();
    }
    else common::WriteMsg::write(CMSG_METHODE_STACK_IS_EMPTY);

    VISIT_END( node, callVirtualBase, "Lambda" );
  }

  //
  //  OTHER VISITORS
  //


  // Member --> commentLines
  // Member --> hasComment
  // File   --> hasComment
  void JAN2LimVisitor::visit( const java::asg::base::Commentable& javaNode, bool callVirtualBase )
  {
    VISIT_BEGIN( javaNode, callVirtualBase, "Commentable" );
    bool isCompUnit = java::asg::Common::getIsCompilationUnit(javaNode);
    if (isCompUnit) {
      const java::asg::struc::CompilationUnit& javaCU = dynamic_cast<const java::asg::struc::CompilationUnit&>( javaNode );
      lim::asg::physical::File& file = createFile( javaCU );
     
      file.setLOC(javaCU.getPosition().getEndLine()-javaCU.getPosition().getLine()+1);
    }

    if ( javaNode.getCommentsIsEmpty() ) return;

    // compute comment-related data
    int lines = 0;
    set<NodeId> commentNodes;

    // a comment is built if
    // - it is attached to a CompilationUnit
    // - OR
    //   - it is attached to a Lim compatible node
    //   - and it is before the node
    //
    // - otherwise it only affects the commentLines metric

 
    bool limCompatible = isLimCompatible(javaNode);

    java::asg::Range nodePos;
    if ( limCompatible && java::asg::Common::getIsPositioned(javaNode)) {
      nodePos = dynamic_cast<const java::asg::base::Positioned&>( javaNode ).getPosition();
    }

    for ( java::asg::ListIterator<java::asg::base::Comment> i = javaNode.getCommentsListIteratorBegin(); i != javaNode.getCommentsListIteratorEnd(); ++i )
    {
      bool buildNode = isCompUnit;
      if ( ! buildNode && limCompatible )
      {
        const java::asg::Range& commentPos = i->getPosition();
        buildNode = commentPos.getWideEndLine() < nodePos.getWideLine();
        buildNode = buildNode || ( commentPos.getWideEndLine() == nodePos.getWideLine() && commentPos.getWideEndCol() < nodePos.getWideCol() );
      }

      if ( buildNode ) commentNodes.insert( limFactory.createComment(i->getText()).getId() );
      else lines += i->getPosition().getEndLine() - i->getPosition().getLine() + 1; 
    }

    // if the node is a java::CompilationUnit --> File::hasComment
    if ( isCompUnit )
    {
      const java::asg::struc::CompilationUnit& javaCU = dynamic_cast<const java::asg::struc::CompilationUnit&>( javaNode );
      lim::asg::physical::File& file = createFile( javaCU );
      for ( set<NodeId>::const_iterator i = commentNodes.begin(); i != commentNodes.end(); ++i )
      {
        SAFE_EDGE( file, Comment, lim::asg::base::Comment, *i );
      }
      return;
    }
    
    // if the node is Lim compatible Member --> Member::hasComment
    if ( limCompatible )
    {
      lim::asg::base::Base* limPtr = getLimPtr( javaNode );
      if ( ! limPtr ) limPtr = & createLimNode( javaNode );

      if ( lim::asg::Common::getIsMember(*limPtr) )
      {
        lim::asg::logical::Member& member = dynamic_cast<lim::asg::logical::Member&>( * limPtr );

        for ( set<NodeId>::const_iterator i = commentNodes.begin(); i != commentNodes.end(); ++i )
        {
          SAFE_EDGE( member, Comment, lim::asg::base::Comment, *i );
        }
        member.setCommentLines( member.getCommentLines() + lines );
      }
      return;
    }

    // otherwise just add the comment lines to the enclosing Scope
    java::asg::base::Base* limCompatibleParent = getParentPtr( javaNode );
    if ( limCompatibleParent )
    {
      lim::asg::base::Base* limPtr = getLimPtr( limCompatibleParent );
      if ( ! limPtr ) limPtr = & createLimNode( *limCompatibleParent );
      if ( lim::asg::Common::getIsMember(*limPtr) )
      {
        lim::asg::logical::Member& member = dynamic_cast<lim::asg::logical::Member&>( * limPtr );
        member.setCommentLines( member.getCommentLines() + lines );
      }
    }
  }

  // Member --> uses ( type conversion )
  void JAN2LimVisitor::visit( const java::asg::expr::TypeExpression& javaNode, bool callVirtualBase )
  {
    VISIT_BEGIN( javaNode, callVirtualBase, "TypeExpression" );

    if ( ! javaNode.getType() )
    {
      common::WriteMsg::write(CMSG_TYPE_EXPR_WITHOUT_TYPE);
      return;
    }

    
    java::asg::type::Type& javaType = * javaNode.getType();

    // PackageTypes are not relevant
    if ( java::asg::Common::getIsPackageType(javaType) )
    {
      return;
    }

    // Wildcard Types are handled separately inside ParametrizedTypes
    if ( java::asg::Common::getIsWildcardType(javaType) )
    {
      return;
    }

    // if it is a UnionType, each alternative is treated as a separate type
    else if ( java::asg::Common::getIsUnionType(javaType) )
    {
      const java::asg::type::UnionType& unionType = dynamic_cast<const java::asg::type::UnionType&>( javaType );
      if ( unionType.getAlternativesIsEmpty() ) return;
      for
      (
        java::asg::ListIterator<java::asg::type::Type> i = unionType.getAlternativesListIteratorBegin();
        i != unionType.getAlternativesListIteratorEnd();
        ++i
      )
      {
        if (!usesStack.empty()) {
          usesStack.top().insert( getLimType(*i).getId() );
        }
      }
    }
    else
    {
      if (!usesStack.empty()) {
        usesStack.top().insert( getLimType(javaType).getId() );
      }
    }
  }

  // Attribute --> calls
  // Method --> calls
  // ( InitBlock --> calls )
  void JAN2LimVisitor::visit( const java::asg::expr::MethodInvocation& javaNode, bool callVirtualBase )
  {
    VISIT_BEGIN( javaNode, callVirtualBase, "MethodInvocation" );

    java::asg::struc::MethodDeclaration* invokes = javaNode.getInvokes();

    NodeId calledMethodId = 0;

    if ( invokes ) {
      lim::asg::base::Base* calledMethod = getLimPtr( invokes );
      if ( ! calledMethod ) {
        calledMethod = & createLimNode( *invokes );
      }
      calledMethodId = calledMethod->getId();
    } else {
      common::WriteMsg::write(CMSG_INVOKES_IS_NULL);
    }

    lim::asg::logical::MethodCall& methodCall = limFactory.createMethodCall( calledMethodId );

    if ( ! attributeStack.empty() )
    {
      attributeStack.top().calls.insert( methodCall.getId() );
    }
    else if ( ! methodStack.empty() )
    {
      methodStack.top().calls.insert( methodCall.getId() );
    } else {
       common::WriteMsg::write(CMSG_METHODE_OR_A_STACK_IS_EMPTY);
    }
  }

  // Method --> accessesAttribute
  void JAN2LimVisitor::visit( const java::asg::expr::Identifier& javaNode, bool callVirtualBase )
  {
    VISIT_BEGIN( javaNode, callVirtualBase, "Identifier" );

    java::asg::base::Named* refPtr = javaNode.getRefersTo();
    // if it should be an attribute
    if ( refPtr && isClassLevelVariable(*refPtr) )
    {
      lim::asg::base::Base* limPtr = getLimPtr( refPtr );
      if ( ! limPtr ) limPtr = & createLimNode( *refPtr ); // now it is an attribute
      lim::asg::logical::AttributeAccess& attrAccess = limFactory.createAttributeAccess( limPtr->getId() );

      if ( ! methodStack.empty() ) {
        methodStack.top().accessesAttribute.insert( attrAccess.getId() );
      } else {
        common::WriteMsg::write(CMSG_METHODE_STACK_IS_EMPTY);
      }
    }
  }

  // Method --> instantiates, constructor calls
  void JAN2LimVisitor::visit( const java::asg::expr::NewClass& javaNode, bool callVirtualBase )
  {
    VISIT_BEGIN( javaNode, callVirtualBase, "NewClass" );

    if ( ! methodStack.empty() )
    {
      java::asg::expr::TypeExpression* javaTE = javaNode.getTypeName();
      if ( javaTE && javaTE->getType() )
      {
        lim::asg::type::Type& limType = getLimType( * javaTE->getType() );
        methodStack.top().instantiates.insert( limType.getId() );
      }
      else
      {
        methodStack.top().instantiates.insert( getUnknownType().getId() );
        common::WriteMsg::write(CMSG_NEWCLASS_WITHOUT_TYPE_EXPR);
      }

      java::asg::struc::NormalMethod* constructor = javaNode.getConstructor();
      if ( constructor )
      {
        lim::asg::base::Base* limConstructor = getLimPtr( constructor );
        if ( ! limConstructor ) limConstructor = & createLimNode( *constructor );

        lim::asg::logical::MethodCall& methodCall = limFactory.createMethodCall( limConstructor->getId() );
        methodStack.top().calls.insert( methodCall.getId() );
      }
    }
  }

  // Method --> uses
  void JAN2LimVisitor::visit( const java::asg::expr::MemberReference& javaNode, bool callVirtualBase )
  {
    VISIT_BEGIN( javaNode, callVirtualBase, "MemberReference" );

    java::asg::struc::MethodDeclaration* invokes = javaNode.getReferredMethod();

    NodeId calledMethodId = 0;

    if ( invokes ) {
      lim::asg::base::Base* calledMethod = getLimPtr( invokes );
      if ( ! calledMethod ) {
        calledMethod = & createLimNode( *invokes );
      }
      calledMethodId = calledMethod->getId();
    } else {
      common::WriteMsg::write(CMSG_INVOKES_IS_NULL);
    }

    if ( calledMethodId ) {
      if ( !usesStack.empty() ) {
        usesStack.top().insert( getLimType(*invokes->getMethodType()).getId() );
      }
    }
  }

  // Method --> throws, NOS++
  void JAN2LimVisitor::visit( const java::asg::statm::Throw& javaNode, bool callVirtualBase )
  {
    VISIT_BEGIN( javaNode, callVirtualBase, "Throw" );
    if (javaNode.getExpression() && javaNode.getExpression()->getType() &&  !methodStack.empty()) {
      methodStack.top().throws.insert( getLimType(*javaNode.getExpression()->getType()).getId() );
    }
    incNOS( javaNode );
  }

  // InstanceInitBlocks --> combined into a new Method
  void JAN2LimVisitor::visit( const java::asg::struc::InstanceInitializerBlock& node, bool callVirtualBase )
  {
    VISIT_BEGIN( node, callVirtualBase, "InstanceInitializerBlock" );

    visitInitBlocks( node );
  }

  void JAN2LimVisitor::visitEnd( const java::asg::struc::InstanceInitializerBlock& node, bool callVirtualBase )
  {
    VISIT_END_FIRST( node, "InstanceInitializerBlock" );

    if ( ! classStack.empty() ) 
    {
      classStack.top().instanceInit = methodStack.top();
      methodStack.pop();
    }

    VISIT_END( node, callVirtualBase, "InstanceInitializerBlock" );
  }

  // StaticInitBlocks --> combined into a new Method
  void JAN2LimVisitor::visit( const java::asg::struc::StaticInitializerBlock& node, bool callVirtualBase )
  {
    VISIT_BEGIN( node, callVirtualBase, "StaticInitializerBlock" );

    visitInitBlocks( node );
  }

  void JAN2LimVisitor::visitEnd( const java::asg::struc::StaticInitializerBlock& node, bool callVirtualBase )
  {
    VISIT_END_FIRST( node, "StaticInitializerBlock" );

    if ( ! classStack.empty() ) 
    {
      classStack.top().staticInit = methodStack.top();
      methodStack.pop();
    }
    VISIT_END( node, callVirtualBase, "StaticInitializerBlock" );
  }


  //
  // METRICS VISITORS
  //

  void JAN2LimVisitor::visit( const java::asg::struc::Variable& node, bool callVirtualBase )
  {
    VISIT_BEGIN( node, callVirtualBase, "Variable" );

    java::asg::base::Base* parent = node.getParent();
    if ( ! parent ) return;

    if ( java::asg::Common::getIsBlock( *parent ) || java::asg::Common::getIsBasicFor( *parent ) ) incNOS( node );
  }

  void JAN2LimVisitor::visit( const java::asg::statm::Assert& node, bool callVirtualBase )
  {
    VISIT_BEGIN( node, callVirtualBase, "Assert" );
    incNOS( node );
  }

  void JAN2LimVisitor::visit( const java::asg::statm::Jump& node, bool callVirtualBase )
  {
    VISIT_BEGIN( node, callVirtualBase, "Jump" );
    incNOS( node );
  }

  void JAN2LimVisitor::visit( const java::asg::statm::Iteration& node, bool callVirtualBase )
  {
    VISIT_BEGIN( node, callVirtualBase, "Iteration" );
    incNOS( node );
    incNOB();
    incNL( true );
  }

  void JAN2LimVisitor::visitEnd( const java::asg::statm::Iteration& node, bool callVirtualBase )
  {
    VISIT_END_FIRST( node, "Iteration" );
    decNL( true );
    VISIT_END( node, callVirtualBase, "Iteration" );
  }

  void JAN2LimVisitor::visit( const java::asg::statm::Selection& node, bool callVirtualBase )
  {
    VISIT_BEGIN( node, callVirtualBase, "Selection" );
    incNOS( node );
    if ( java::asg::Common::getIsIf( node ) ) incNOB();
    incNL( eligibleForNLE(node) );
  }

  void JAN2LimVisitor::visitEnd( const java::asg::statm::Selection& node, bool callVirtualBase )
  {
    VISIT_END_FIRST( node, "Selection" );
    decNL( eligibleForNLE(node) );
    VISIT_END( node, callVirtualBase, "Selection" );
  }

  void JAN2LimVisitor::visit( const java::asg::statm::Return& node, bool callVirtualBase )
  {
    VISIT_BEGIN( node, callVirtualBase, "Return" );
    incNOS( node );
  }

  void JAN2LimVisitor::visit( const java::asg::statm::Empty& node, bool callVirtualBase )
  {
    VISIT_BEGIN( node, callVirtualBase, "Empty" );
    if ( node.getParent() && ( !java::asg::Common::getIsCompilationUnit(*node.getParent()) && !java::asg::Common::getIsTypeDeclaration(*node.getParent()) ) ) {
      // skip empty stmt in compilation unit or in type declaration body (next to fields, methods, stc)
      incNOS( node );
    }
  }

  void JAN2LimVisitor::visit( const java::asg::statm::Case& node, bool callVirtualBase )
  {
    VISIT_BEGIN( node, callVirtualBase, "Case" );
    incNOB();
  }

  void JAN2LimVisitor::visit( const java::asg::statm::Handler& node, bool callVirtualBase )
  {
    VISIT_BEGIN( node, callVirtualBase, "Handler" );
    incNOB();
  }

  

  void JAN2LimVisitor::visit( const java::asg::statm::ExpressionStatement& node, bool callVirtualBase )
  {
    VISIT_BEGIN( node, callVirtualBase, "ExpressionStatement" );
    incNOS( node );
  }

  void JAN2LimVisitor::visit( const java::asg::statm::Block& node, bool callVirtualBase )
  {
    VISIT_BEGIN( node, callVirtualBase, "Block" );
    if ( node.getParent() && java::asg::Common::getIsBlock(*node.getParent()) ) {
      incNOS( node );
      incNL( true );
    }
  }

  void JAN2LimVisitor::visitEnd( const java::asg::statm::Block& node, bool callVirtualBase )
  {
    VISIT_END_FIRST( node, "Block" );
    if ( node.getParent() && java::asg::Common::getIsBlock(*node.getParent()) ) {
      decNL( true );
    }
    VISIT_END( node, callVirtualBase, "Block" );
  }

  void JAN2LimVisitor::visit( const java::asg::statm::Synchronized& node, bool callVirtualBase )
  {
    VISIT_BEGIN( node, callVirtualBase, "Synchronized" );
    incNOS( node );
  }

  void JAN2LimVisitor::visit( const java::asg::statm::Try& node, bool callVirtualBase )
  {
    VISIT_BEGIN( node, callVirtualBase, "Try" );
    incNOS( node );
    incNL( true );
  }

  void JAN2LimVisitor::visitEnd( const java::asg::statm::Try& node, bool callVirtualBase )
  {
    VISIT_END_FIRST( node, "Try" );
    decNL( true );
    VISIT_END( node, callVirtualBase, "Try" );
  }

  void JAN2LimVisitor::visit( const java::asg::expr::Conditional& node, bool callVirtualBase )
  {
    VISIT_BEGIN( node, callVirtualBase, "Conditional" );
    incNOB();
  }

  void JAN2LimVisitor::visit( const java::asg::expr::InfixExpression& node, bool callVirtualBase ) {
    using namespace java::asg;
    VISIT_BEGIN( node, callVirtualBase, "InfixExpression" );
    InfixOperatorKind kind = node.getOperator();
    if ( kind == iokConditionalAnd || kind == iokConditionalOr ) {
      incNOB();
    }
  }

  void JAN2LimVisitor::visitEnd ( const java::asg::base::Positioned& node, bool callVirtualBase )
  {
    VISIT_END_FIRST( node, "Positioned" );
    if ( ! isLimCompatible( node ) ) insertLLOCMap( node );
    VISIT_END( node, callVirtualBase, "Positioned" );
  }

  void JAN2LimVisitor::finishVisit()
  {
    // TODO: clean up, refactor to separate method
    // override edges for methods
    java::asg::Factory::const_iterator javaIt = javaFactory.begin();
    while(javaIt!=javaFactory.end()) {
      if(java::asg::Common::getIsMethodDeclaration(**javaIt)) {
        const java::asg::struc::MethodDeclaration &methodDecl = dynamic_cast<const java::asg::struc::MethodDeclaration &>(**javaIt);
        java::asg::ListIterator<java::asg::struc::MethodDeclaration> it = methodDecl.getOverridesListIteratorBegin();
        NodeId from = getLimPtr(methodDecl)->getId();
        while(it != methodDecl.getOverridesListIteratorEnd()) {
          overrides._addOverride(from, getLimPtr(*it)->getId());
          ++it;
        }
      }
      ++javaIt;
    }

    // linux root file name fix
    lim::asg::physical::FileSystem& fs = dynamic_cast<lim::asg::physical::FileSystem&>( limFactory.getRef( limFactory.getFileSystemRoot() ) );
    lim::asg::ListIterator<lim::asg::physical::FSEntry> fsIt = fs.getFSEntryListIteratorBegin();
    for ( ; fsIt != fs.getFSEntryListIteratorEnd(); ++fsIt )
    {
      if ( lim::asg::Common::getIsFolder( *fsIt ) )
      {
        lim::asg::physical::Folder& folder = dynamic_cast<lim::asg::physical::Folder&>( limFactory.getRef( fsIt->getId() ) );
        if ( folder.getName() == "/" )
        {
          folder.setName( "" );
        }
      }
    }
  }

  //
  // METRICS
  //

  void JAN2LimVisitor::insertLLOCMap( const java::asg::base::Positioned& node )
  {
    if ( javaFactory.getFilterState( node.getId() ) == java::asg::Filter::Filtered ) return;

    insertLLOCMap(node.getPosition()); // simple position

    // base
    COUNT_LLOC_BEGIN(base, Named)
    COUNT_LLOC_NODE_ATTR(NamePosition)
    COUNT_LLOC_END

    // expr
    COUNT_LLOC_BEGIN(expr, Conditional)
    COUNT_LLOC_NODE_ATTR(ColonPosition)
    COUNT_LLOC_END

    COUNT_LLOC_BEGIN(expr, NewArray)
    COUNT_LLOC_NODE_ATTR(LeftBracePosition)
    COUNT_LLOC_END

    // statm
    COUNT_LLOC_BEGIN(statm, Assert)
    COUNT_LLOC_NODE_ATTR(ColonPosition)
    COUNT_LLOC_END

    COUNT_LLOC_BEGIN(statm, BasicFor)
    COUNT_LLOC_NODE_ATTR(FirstSemiPosition)
    COUNT_LLOC_NODE_ATTR(SecondSemiPosition)
    COUNT_LLOC_END

    COUNT_LLOC_BEGIN(statm, Do)
    COUNT_LLOC_NODE_ATTR(WhilePosition)
    COUNT_LLOC_END

    COUNT_LLOC_BEGIN(statm, EnhancedFor)
    COUNT_LLOC_NODE_ATTR(ColonPosition)
    COUNT_LLOC_END

    COUNT_LLOC_BEGIN(statm, For)
    COUNT_LLOC_NODE_ATTR(LeftParenPosition)
    COUNT_LLOC_NODE_ATTR(RightParenPosition)
    COUNT_LLOC_END

    COUNT_LLOC_BEGIN(statm, Handler)
    COUNT_LLOC_NODE_ATTR(LeftParenPosition)
    COUNT_LLOC_NODE_ATTR(RightParenPosition)
    COUNT_LLOC_END

    COUNT_LLOC_BEGIN(statm, If)
    COUNT_LLOC_NODE_ATTR(ElsePosition)
    COUNT_LLOC_END

    COUNT_LLOC_BEGIN(statm, Jump)
    COUNT_LLOC_NODE_ATTR(LabelPosition)
    COUNT_LLOC_END

    COUNT_LLOC_BEGIN(statm, LabeledStatement)
    COUNT_LLOC_NODE_ATTR(ColonPosition)
    COUNT_LLOC_END

    COUNT_LLOC_BEGIN(statm, Switch)
    COUNT_LLOC_NODE_ATTR(BlockStartPosition)
    COUNT_LLOC_END

    COUNT_LLOC_BEGIN(statm, SwitchLabel)
    COUNT_LLOC_NODE_ATTR(ColonPosition)
    COUNT_LLOC_END

    COUNT_LLOC_BEGIN(statm, Try)
    COUNT_LLOC_NODE_ATTR(ResourceLeftParenPosition)
    COUNT_LLOC_NODE_ATTR(ResourceRightParenPosition)
    COUNT_LLOC_NODE_ATTR(FinallyPosition)
    COUNT_LLOC_END

    // struc
    COUNT_LLOC_BEGIN(struc, AnnotationType)
    COUNT_LLOC_NODE_ATTR(AtSignPosition)
    COUNT_LLOC_END

    COUNT_LLOC_BEGIN(struc, AnnotationTypeElement)
    COUNT_LLOC_NODE_ATTR(DefaultPosition)
    COUNT_LLOC_END

    COUNT_LLOC_BEGIN(struc, Enum)
    COUNT_LLOC_NODE_ATTR(SemiPosition)
    COUNT_LLOC_END

    COUNT_LLOC_BEGIN(struc, Import)
    COUNT_LLOC_NODE_ATTR(StaticPosition)
    COUNT_LLOC_END

    COUNT_LLOC_BEGIN(struc, MethodDeclaration)
    COUNT_LLOC_NODE_ATTR(AbstractPosition)
    COUNT_LLOC_NODE_ATTR(StrictfpPosition)
    COUNT_LLOC_NODE_ATTR(ParametersStartPosition)
    COUNT_LLOC_NODE_ATTR(ParametersEndPosition)
    COUNT_LLOC_END

    COUNT_LLOC_BEGIN(struc, NamedDeclaration)
    COUNT_LLOC_NODE_ATTR(AccessibilityPosition)
    COUNT_LLOC_NODE_ATTR(StaticPosition)
    COUNT_LLOC_NODE_ATTR(FinalPosition)
    COUNT_LLOC_END

    COUNT_LLOC_BEGIN(struc, NormalMethod)
    COUNT_LLOC_NODE_ATTR(SynchronizedPosition)
    COUNT_LLOC_NODE_ATTR(NativePosition)
    COUNT_LLOC_NODE_ATTR(ThrowsPosition)
    COUNT_LLOC_END

    COUNT_LLOC_BEGIN(struc, Parameter)
    COUNT_LLOC_NODE_ATTR(VarargsPosition)
    COUNT_LLOC_END

    COUNT_LLOC_BEGIN(struc, StaticInitializerBlock)
    COUNT_LLOC_NODE_ATTR(BlockStartPosition)
    COUNT_LLOC_END

    COUNT_LLOC_BEGIN(struc, TypeDeclaration)
    COUNT_LLOC_NODE_ATTR(TypeNamePosition)
    COUNT_LLOC_NODE_ATTR(AbstractPosition)
    COUNT_LLOC_NODE_ATTR(StrictfpPosition)
    COUNT_LLOC_NODE_ATTR(ExtendsPosition)
    COUNT_LLOC_NODE_ATTR(ImplementsPosition)
    COUNT_LLOC_NODE_ATTR(BodyStartPosition)
    COUNT_LLOC_END

    COUNT_LLOC_BEGIN(struc, Variable)
    COUNT_LLOC_NODE_ATTR(TransientPosition)
    COUNT_LLOC_NODE_ATTR(VolatilePosition)
    COUNT_LLOC_NODE_ATTR(EqualSignPosition)
    COUNT_LLOC_END
  }

  void JAN2LimVisitor::insertLLOCMap( const java::asg::Range& range )
  {
    Key pathKey = limFactory.getStringTable().set(range.getPath());
    unsigned line = range.getLine();
    unsigned endLine = range.getEndLine();
    unsigned wideLine = range.getWideLine();
    unsigned wideEndLine = range.getWideEndLine();

    if ( !line && !endLine && !wideLine && !wideEndLine ) return;

    // This positioned node belongs to the current method if
    // - it's not an initBlock ( then it belongs to the class only )
    // - the current class is't the child of the current method
    if ( ! methodStack.empty() )
    {
      bool innerClass = false;

      // sets innerClass to true if the current class is inside the current method
      if ( ! classStack.empty() )
      {
        NodeId currentMethodId = methodStack.top().method;
        NodeId step = classStack.top().clazz;

        while ( true )
        {
          lim::asg::ListIterator<lim::asg::base::Base> i = revEdges.constIteratorBegin( step, lim::asg::edkScope_HasMember );
          if ( i == revEdges.constIteratorEnd( step, lim::asg::edkScope_HasMember ) ) break;

          step = i->getId();

          if ( step == currentMethodId )
          {
            innerClass = true;
            break;
          }
        }
      }

      if ( ! innerClass ) assignPathLineToNode( methodStack.top().method, pathKey, line, endLine, wideLine, wideEndLine );
    }

    if ( ! classStack.empty() )
    {
      assignPathLineToNode( classStack.top().clazz, pathKey, line, endLine, wideLine, wideEndLine );
    }

    if ( ! packageStack.empty() )
    {
      assignPathLineToNode( packageStack.top().package, pathKey, line, endLine, wideLine, wideEndLine );
    }

    // component level TLLOC
    addLogicalLineOfComponent(pathKey, line, component.getId() );
    addLogicalLineOfComponent(pathKey, endLine, component.getId() );
    addLogicalLineOfComponent(pathKey, wideLine, component.getId() );
    addLogicalLineOfComponent(pathKey, wideEndLine, component.getId() );
  }

  void JAN2LimVisitor::assignPathLineToNode( NodeId limId, Key pathKey, long line, long endLine, long wideLine, long wideEndLine, LLOCMapType& localLLOCMap )
  {
    LLOCMapType::iterator it = localLLOCMap.find( limId );
    if ( it != localLLOCMap.end() )
    {
      // existing node
      PathLineMapType::iterator pathIt = it->second.find( pathKey );
      if ( pathIt != it->second.end() )
      {
        // existing path for that node
        if ( line )         pathIt->second.insert( line );
        if ( endLine )      pathIt->second.insert( endLine );
        if ( wideLine )     pathIt->second.insert( wideLine );
        if ( wideEndLine )  pathIt->second.insert( wideEndLine );
      }
      else
      {
        // new path for that node
        set<long> ls;
        if ( line )         ls.insert( line );
        if ( endLine )      ls.insert( endLine );
        if ( wideLine )     ls.insert( wideLine );
        if ( wideEndLine )  ls.insert( wideEndLine );
        it->second[ pathKey ] = ls;
      }
    }
    else
    {
      // new node
      set<long> ls;
      if (line)         ls.insert( line );
      if (endLine)      ls.insert( endLine );
      if (wideLine)     ls.insert( wideLine );
      if (wideEndLine)  ls.insert( wideEndLine );

      PathLineMapType plm;
      plm[ pathKey ] = ls;
      localLLOCMap[ limId ] = plm;
    }
  }

  void JAN2LimVisitor::setLineMetrics( lim::asg::Factory& limFactory )
  {
    // LLOC
    PathLineMapType fileLLOC;
    for ( LLOCMapType::const_iterator idIt = LLOCMap.begin(); idIt != LLOCMap.end(); ++idIt ) {
      lim::asg::base::Base& ref = limFactory.getRef( idIt->first );

      // File
      mergePathLineMaps( fileLLOC, idIt->second );

      // Scope
      if (lim::asg::Common::getIsScope( ref ) )
      {
        lim::asg::logical::Scope& scope = dynamic_cast<lim::asg::logical::Scope&>( ref );
        scope.setLLOC( scope.getLLOC() + pathLineMapCount( idIt->second ) ); // need to add getLLOC because of the possible InstanceInitBlocks
      }

      // Component
      else if ( lim::asg::Common::getIsComponent( ref ) )
      {
        lim::asg::base::Component& component = dynamic_cast<lim::asg::base::Component&>( ref );
        component.setTLLOC( pathLineMapCount( idIt->second ) );
      }
    }

    for ( PathLineMapType::iterator fileIt = fileLLOC.begin(); fileIt != fileLLOC.end(); ++fileIt )
    {
      lim::asg::physical::File& file = dynamic_cast<lim::asg::physical::File&>( limFactory.getRef( fileMap[ fileIt->first ] ) );
      file.setLLOC( fileIt->second.size() );
    }

    // TLLOC + (T)LOC
    for ( columbus::lim::asg::Factory::const_iterator it = limFactory.begin(); it != limFactory.end(); ++it )
    {
      if ( columbus::lim::asg::Common::getIsScope(**it) )
      {
        dynamic_cast<lim::asg::logical::Scope&>( limFactory.getRef((*it)->getId())).setTLLOC( collectTLLOC(dynamic_cast< const lim::asg::logical::Scope&> (**it)) );
        setLOC( dynamic_cast<lim::asg::logical::Scope&> (limFactory.getRef((*it)->getId())) );
      }
      
      if ( columbus::lim::asg::Common::getIsComponent(**it) )
      {
        long tloc = 0;
        for ( map<Key, unsigned long>::iterator  itfileKeys = componentTLOCMap[(*it)->getId()].begin();
          itfileKeys != componentTLOCMap[(*it)->getId()].end();++itfileKeys) {
            tloc += itfileKeys->second;
        }
        dynamic_cast<lim::asg::base::Component&>( limFactory.getRef((*it)->getId())).setTLOC( tloc) ;
      }
    }

    LLOCMap.clear();
  }

  void JAN2LimVisitor::filterInitBlocks( lim::asg::Factory& limFactory )
  {
    for ( set<NodeId>::const_iterator it = initBlocks.begin(); it != initBlocks.end(); ++it )
    {
      limFactory.setFiltered( *it );
    }

    initBlocks.clear();
  }

  void JAN2LimVisitor::mergePathLineMaps( PathLineMapType& result, const PathLineMapType& other )
  {
    for ( PathLineMapType::const_iterator it = other.begin(); it != other.end(); ++it )
    {
      result[it->first].insert( it->second.begin(), it->second.end() );
    }
  }



  unsigned long JAN2LimVisitor::collectTLLOC( const lim::asg::logical::Scope& limScope )
  {
    PathLineMapType TLLOC_ofScope;
    mergeTLLOC(limScope, TLLOC_ofScope);
    
    unsigned long TLLOC = 0;
    for ( PathLineMapType::const_iterator pathIt = TLLOC_ofScope.begin(); pathIt != TLLOC_ofScope.end(); ++pathIt )
    {
      TLLOC += pathIt->second.size();
    }

    return TLLOC;
  }

  void JAN2LimVisitor::incNOS( const java::asg::base::Positioned& javaNode )
  {
    if ( javaNode.getIsCompilerGenerated() ) return;
    if ( ! methodStack.empty() ) methodStack.top().NOS++;
  }

  void JAN2LimVisitor::incNOB()
  {
    if ( ! methodStack.empty() ) methodStack.top().NOB++;
  }

  void JAN2LimVisitor::incNL( bool NLE )
  {
    if ( methodStack.empty() ) return;

    // NL
    methodStack.top().currentNL++;
    if ( methodStack.top().currentNL > methodStack.top().NL ) methodStack.top().NL = methodStack.top().currentNL;

    // NLE
    if ( NLE )
    {
      methodStack.top().currentNLE++;
      if ( methodStack.top().currentNLE > methodStack.top().NLE ) methodStack.top().NLE = methodStack.top().currentNLE;
    }
  }

  void JAN2LimVisitor::decNL( bool NLE )
  {
    if ( methodStack.empty() ) return;
    methodStack.top().currentNL--;
    if ( NLE ) methodStack.top().currentNLE--;
  }

  bool JAN2LimVisitor::eligibleForNLE( const java::asg::statm::Selection& sel )
  {
    if
    (
      java::asg::Common::getIsIf( sel )
      && sel.getParent()
      && java::asg::Common::getIsIf( * sel.getParent() )
      && dynamic_cast<java::asg::statm::If&>( * sel.getParent() ).getFalseSubstatement()
      && dynamic_cast<java::asg::statm::If&>( * sel.getParent() ).getFalseSubstatement()->getId() == sel.getId()
    )
    {
      return false;
    }

    return true;
  }

  void JAN2LimVisitor::mergeTLLOC( const lim::asg::logical::Scope &limScope, PathLineMapType& TLLOC_ofScope )
  {
    LLOCMapType::iterator foundIt = LLOCMap.find( limScope.getId() );
    if ( foundIt != LLOCMap.end() )
    {
      mergePathLineMaps( TLLOC_ofScope , foundIt->second );
    }

    for ( lim::asg::ListIterator<lim::asg::logical::Member> memberIt = limScope.getMemberListIteratorBegin(); memberIt != limScope.getMemberListIteratorEnd(); ++memberIt )
    {
      if ( lim::asg::Common::getIsScope(*memberIt) )
      {
        mergeTLLOC(dynamic_cast<const lim::asg::logical::Scope&>(*memberIt),TLLOC_ofScope);
      }
    }
  }

  // Method < Class < Package
  bool operator <= ( const lim::asg::logical::Scope& lhs, const lim::asg::logical::Scope& rhs )
  {
    if ( lim::asg::Common::getIsMethod(lhs) ) return true;
    else if ( lim::asg::Common::getIsClass(lhs) ) return ! lim::asg::Common::getIsMethod(rhs);
    else if ( lim::asg::Common::getIsPackage( lhs ) ) return lim::asg::Common::getIsPackage( rhs );
    return false;
  } 

  void JAN2LimVisitor::setLOC( lim::asg::logical::Scope& limScope )
  {
    vector<Interval> intervals;
    unsigned long LOC = getTLOC( limScope, intervals ); // first its the TLOC, then it gets reduced
    limScope.setTLOC( LOC );
    set<NodeId> borders;

    for ( lim::asg::ListIterator<lim::asg::logical::Member> memberIt = limScope.getMemberListIteratorBegin(); memberIt != limScope.getMemberListIteratorEnd(); ++memberIt )
    {
      // the contents of a method count while its inner member's contents do not
      // so we calculate the difference between the method's LOC and TLOC first
      // and subtract only that from the enclosing scope's LOC.
      if ( lim::asg::Common::getIsMethod( *memberIt ) )
      {
        lim::asg::logical::Method& method = dynamic_cast<lim::asg::logical::Method&>( const_cast<lim::asg::logical::Member&>( *memberIt ) );
        setLOC( method );
        unsigned int methodLOC = method.getLOC();
        vector<Interval> temp;
        unsigned int methodTLOC = getTLOC( method, temp );

        LOC -= ( methodTLOC - methodLOC );
      }
      else if ( lim::asg::Common::getIsScope( *memberIt ) && limScope <= dynamic_cast<lim::asg::logical::Scope&>(const_cast<lim::asg::logical::Member&>(*memberIt )))
      {
        PathLineMapType visitedBorders;

        lim::asg::logical::Scope& memberScope = dynamic_cast<lim::asg::logical::Scope&>( const_cast<lim::asg::logical::Member&>( *memberIt ) );
        vector<Interval> memberIntervals;
        unsigned long memberTLOC = getTLOC( memberScope, memberIntervals );

        LOC -= memberTLOC;

        for ( vector<Interval>::const_iterator intervalIt = memberIntervals.begin(); intervalIt != memberIntervals.end(); ++intervalIt )
        {
          if ( borderCounts( limScope, intervalIt->key, intervalIt->from, visitedBorders ) ) LOC++; // FROM
          if ( borderCounts( limScope, intervalIt->key, intervalIt->to, visitedBorders ) ) LOC++;   // TO
        }
      }
    }

    if ( ((long)LOC) < 0 )
    {
      common::WriteMsg::write(CMSG_NEGATIVE_LOC);
      LOC = 0;
    }

    limScope.setLOC( LOC );
  }

  bool JAN2LimVisitor::borderCounts( lim::asg::logical::Scope& limScope, Key key, long line, PathLineMapType& visited )
  {
    // if already checked this border
    set<long> mapped = visited[key];
    if ( mapped.find( line ) != mapped.end() ) return false;
    else visited[key].insert( line );

    // if the parent also has something in this line
    LLOCMapType::iterator it = LLOCMap.find( limScope.getId() );
    if ( it != LLOCMap.end() )
    {
      mapped = it->second[key];
      if ( mapped.find( line ) != mapped.end() ) return true;
    }

    // otherwise
    return false;
  }

  unsigned long JAN2LimVisitor::getTLOC( const lim::asg::logical::Scope& limScope, vector<Interval>& intervals )
  {
    unsigned long TLOC = 0;

    if ( limScope.getFactory().getFilterState( limScope.getId() ) == lim::asg::Filter::Filtered ) return 0;

    // The root package does not have all the isContainedIn edges
    // So we calculate its TLOC by the sum of its child package's TLOC

    // Subpackages are not physically inside their parent Packages
    // ( unlike e.g. local or anonym classes inside other classes )
    // So the TLOC of a Package is computed recursively
    if ( lim::asg::Common::getIsPackage( limScope ) )
    {
      lim::asg::ListIterator<lim::asg::logical::Member> subPackageIt = limScope.getMemberListIteratorBegin();
      for ( ; subPackageIt != limScope.getMemberListIteratorEnd(); ++subPackageIt )
      {
        if ( ! lim::asg::Common::getIsPackage( *subPackageIt ) ) continue;
        const lim::asg::logical::Package& subPackage = dynamic_cast<const lim::asg::logical::Package&>( *subPackageIt );
        TLOC += getTLOC( subPackage, intervals );
      }
    }

    lim::asg::ListIteratorAssocSourcePosition<lim::asg::physical::File> fileIt = limScope.getIsContainedInListIteratorAssocBegin();
    for ( ; fileIt != limScope.getIsContainedInListIteratorAssocEnd(); ++fileIt )
    {
      lim::asg::SourcePosition pos = fileIt.getAssocClass();
      Interval i;
      i.key = limScope.getFactory().getStringTable().set(lim::asg::Common::getFullPath(*fileIt));
      i.from = pos.getLine();
      i.to = pos.getEndLine();
      intervals.push_back( i );

      TLOC += i.to - i.from + 1;
    }

    return TLOC;
  }

  unsigned long JAN2LimVisitor::pathLineMapCount( const PathLineMapType& map )
  {
    unsigned long LLOC = 0;
    for ( PathLineMapType::const_iterator pathIt = map.begin(); pathIt != map.end(); ++pathIt )
    {
      LLOC += pathIt->second.size();
    }
    return LLOC;
  }

  void JAN2LimVisitor::addIsContainedInEdge( lim::asg::logical::Member& limNode, const java::asg::base::PositionedWithoutComment& posWC )
  {
    const java::asg::Range& pos = posWC.getPosition();

    lim::asg::SourcePosition limPos;
    limPos.setLine( pos.getWideLine() );
    limPos.setColumn( pos.getWideCol() );
    limPos.setEndLine( pos.getWideEndLine() );
    limPos.setEndColumn( pos.getWideEndCol() );
    limPos.setRealizationLevel( lim::asg::relDefines );

    string filePath = pos.getPath();

    if ( ! filePath.empty() )
    {
      lim::asg::physical::File& file = createFile( posWC );

      bool found = false;
      lim::asg::ListIteratorAssocSourcePosition<lim::asg::physical::File> spIt = limNode.getIsContainedInListIteratorAssocBegin();
      for ( ; spIt != limNode.getIsContainedInListIteratorAssocEnd(); ++spIt )
      {
        lim::asg::SourcePosition oldSp = spIt.getAssocClass();
        if
        (
          spIt->getId() == file.getId()
          && oldSp.getLine() == pos.getWideLine()
          && oldSp.getColumn() == pos.getWideCol()
          && oldSp.getEndLine() == pos.getWideEndLine()
          && oldSp.getEndColumn() == pos.getWideEndCol()
        )
        {
          found = true;
          break;
        }
      }

      if ( ! found ) limNode.addIsContainedIn( file.getId(), limPos );
    }
  }

  void JAN2LimVisitor::oldVersionLinking( const java::asg::base::Base& node )
  {
    /*
    Old version linking is needed, when
    - a lim node with this node's unique name already exists and
    - it has a different nodeKind than this node would get
      - a Class can become a ClassGeneric
      - a Method can become a MethodGeneric

    In reverse cases ( a GenericDeclaration tries to become a normal one )
    we do nothing because it automatically gets linked to the already
    existing generic version of the node ( which is what we want )
    */

    lim::asg::base::Base* existingPtr = getLimPtrByName( &node );
    if ( ! existingPtr ) return;

    lim::asg::NodeKind existingKind = existingPtr->getNodeKind();
    lim::asg::NodeKind newKind = getLimKind( node, true );
    if ( existingKind == newKind ) return;

    bool methodCase = existingKind == lim::asg::ndkMethod && newKind == lim::asg::ndkMethodGeneric;
    bool classCase = existingKind == lim::asg::ndkClass && newKind == lim::asg::ndkClassGeneric;

    if ( !classCase || !methodCase ) return;

    limFactory.replaceNode( *existingPtr );

    const java::asg::struc::GenericDeclaration& genericDecl = dynamic_cast<const java::asg::struc::GenericDeclaration&>( node );
    java::asg::ListIterator<java::asg::struc::TypeParameter> typeParIt = genericDecl.getTypeParametersListIteratorBegin();
    for ( ; typeParIt != genericDecl.getTypeParametersListIteratorEnd(); ++typeParIt )
    {
      lim::asg::logical::GenericParameter& genPar = dynamic_cast<lim::asg::logical::GenericParameter&>( createLimNode( *typeParIt, Complete, false ) );
      fillData( genPar, *typeParIt );
    }
  }

  void JAN2LimVisitor::addLogicalLineOfComponent( Key pathKey, unsigned line, NodeId nodeId ) {
    if ( line )
    {
      LLOCMap[nodeId][pathKey].insert(line);
      for (lim::asg::ListIterator<lim::asg::base::Base> it = revEdges.constIteratorBegin(nodeId,lim::asg::edkComponent_Contains); it != revEdges.constIteratorEnd(nodeId,lim::asg::edkComponent_Contains);++it) {
        addLogicalLineOfComponent(pathKey,line,it->getId());
      }
    }
  }

  void JAN2LimVisitor::addLocToComponent(NodeId nodeId, Key key, long lastLineNumber ) {
    componentTLOCMap[ nodeId] [key] =lastLineNumber;
    for (lim::asg::ListIterator<lim::asg::base::Base> it = revEdges.constIteratorBegin(nodeId,lim::asg::edkComponent_Contains); it != revEdges.constIteratorEnd(nodeId,lim::asg::edkComponent_Contains);++it) {
      addLocToComponent(it->getId(),key,lastLineNumber);
    }
  }

  void JAN2LimVisitor::setNotFilteredComponenetUp(NodeId id,bool hasStructureInfo)
  {
    lim::asg::Factory::TurnFilterOffSafely tfos(limFactory);
    limFactory.setNotFilteredThisNodeOnly(id);

    if (((lim::asg::base::Component&)limFactory.getRef(id)).getAnalysisTime() == lim::asg::atkNever) {
      if ( hasStructureInfo) {
        ((lim::asg::base::Component&)limFactory.getRef(id)).setAnalysisTime(lim::asg::atkBefore);
      } else {
        ((lim::asg::base::Component&)limFactory.getRef(id)).setAnalysisTime(lim::asg::atkNow);
      }
    }

    for (lim::asg::ListIterator<lim::asg::base::Base> it = limFactory.getReverseEdges().constIteratorBegin(id,lim::asg::edkComponent_Contains);
      it != limFactory.getReverseEdges().constIteratorEnd(id,lim::asg::edkComponent_Contains) ; ++it) {
        setNotFilteredComponenetUp(it->getId(),hasStructureInfo);
    }
  }

  JAN2LimVisitor::MethodInfo JAN2LimVisitor::createEmptyInitBlock( lim::asg::logical::Class* parent, bool isStatic )
  {
    // Method data
    lim::asg::logical::Method* method = limFactory.createMethodNode();
    method->setName( isStatic ? java::asg::Common::getStaticInitBlockName() : java::asg::Common::getInstanceInitBlockName() );
    method->setMangledName( parent->getMangledName() + ( isStatic ? java::asg::Common::getStaticInitBlockSuffix() : java::asg::Common::getInstanceInitBlockSuffix() ) );
    method->setIsStatic( isStatic );

    method->setLanguage(lim::asg::lnkJava);    
    
    // MethodInfo data
    MethodInfo info;
    info.method = method->getId();

    lim::asg::ListIterator<lim::asg::base::Component> bIt = parent->getBelongsToListIteratorBegin();
    for ( ; bIt != parent->getBelongsToListIteratorEnd(); ++bIt )
    {
      info.belongsTo.insert( bIt->getId() );
    }

    return info;
  }
}}
