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

#ifndef _JAN2LIMH_
#define _JAN2LIMH_

#include "lim/inc/lim.h"
#include "java/inc/java.h"
#include "HalsteadVisitor.h"

#include <map>
#include <set>

namespace columbus { namespace JAN2Lim
{
  /**
  *   Currently supporting LIM API v3.0.13
  */
  class JAN2LimVisitor : public java::asg::VisitorAbstractNodes
  {
  public:

    //
    // TYPE DEFINITIONS
    //

    struct PosInfo
    {
      PosInfo() : posString(), file() {}

      std::string posString;
      std::string file;

      bool matches( const PosInfo& other ) const;
      bool operator < ( const PosInfo& other ) const;
    };

    typedef std::map<std::string, std::map<PosInfo, NodeId> > JAN2LimMap;
    typedef std::map<NodeId, NodeId> JAN2LimLocalMap;

    typedef std::map<const java::asg::type::Type*, lim::asg::type::Type*> TypeMap;
    typedef std::map<const std::string, lim::asg::logical::ClassGenericInstance*> CGIMap;

    typedef std::map<Key, std::set<long> > PathLineMapType;
    typedef std::map<NodeId, PathLineMapType> LLOCMapType;
    static LLOCMapType LLOCMap;

    static std::map<Key, NodeId> fileMap;

    enum CompletionStates
    {
      Incomplete
      , ExternalBuilt
      , Complete
    };

    struct VisitStat;

    //
    // INITIALIZATION
    //

    JAN2LimVisitor( lim::asg::Factory&, java::asg::Factory&, JAN2LimMap&, CGIMap&, std::map<NodeId, CompletionStates>&, std::string&, VisitStat&, LimOrigin&, lim::asg::OverrideRelations&, bool connectToRootComponent, bool buildEmptyInitBlocks, const std::string& changesetID, std::map<NodeId, HalsteadVisitor::HalsteadInfo>);

    void setNotFilteredComponenetUp(NodeId id,bool hasStructureInfo);

    //
    // VISITORS
    //

    // main logical build
    virtual void visit    ( const java::asg::struc::Package&, bool );
    virtual void visitEnd ( const java::asg::struc::Package&, bool );
    virtual void visit    ( const java::asg::struc::TypeDeclaration&, bool );
    virtual void visitEnd ( const java::asg::struc::TypeDeclaration&, bool );
    virtual void visit    ( const java::asg::struc::MethodDeclaration&, bool );
    virtual void visitEnd ( const java::asg::struc::MethodDeclaration&, bool );
    virtual void visit    ( const java::asg::struc::VariableDeclaration&, bool );
    virtual void visitEnd ( const java::asg::struc::VariableDeclaration&, bool );
    virtual void visit    ( const java::asg::struc::TypeParameter&, bool );
    virtual void visitEnd ( const java::asg::struc::TypeParameter&, bool );
    virtual void visit    ( const java::asg::struc::Parameter&, bool );
    virtual void visitEnd ( const java::asg::struc::Parameter&, bool );

    // other visitors
    virtual void visit    ( const java::asg::base::Commentable&, bool );
    virtual void visit    ( const java::asg::expr::TypeExpression&, bool );
    virtual void visit    ( const java::asg::expr::MethodInvocation&, bool );
    virtual void visit    ( const java::asg::expr::Identifier&, bool );
    virtual void visit    ( const java::asg::expr::NewClass&, bool );
    virtual void visit    ( const java::asg::statm::Throw&, bool );
    virtual void visit    ( const java::asg::struc::InstanceInitializerBlock&, bool );
    virtual void visitEnd ( const java::asg::struc::InstanceInitializerBlock&, bool );
    virtual void visit    ( const java::asg::struc::StaticInitializerBlock&, bool );
    virtual void visitEnd ( const java::asg::struc::StaticInitializerBlock&, bool );

    // metrics visitors
    virtual void visit    ( const java::asg::struc::Variable&, bool );
    virtual void visit    ( const java::asg::statm::Assert&, bool );
    virtual void visit    ( const java::asg::statm::Jump&, bool );
    virtual void visit    ( const java::asg::statm::Iteration&, bool );
    virtual void visitEnd ( const java::asg::statm::Iteration&, bool );
    virtual void visit    ( const java::asg::statm::Selection&, bool );
    virtual void visitEnd ( const java::asg::statm::Selection&, bool );
    virtual void visit    ( const java::asg::statm::Return&, bool );
    virtual void visit    ( const java::asg::statm::Empty&, bool );
    virtual void visit    ( const java::asg::statm::Case&, bool );
    virtual void visit    ( const java::asg::statm::Handler&, bool );
    virtual void visit    ( const java::asg::statm::ExpressionStatement&, bool );
    virtual void visit    ( const java::asg::statm::Block&, bool );
    virtual void visitEnd ( const java::asg::statm::Block&, bool );
    virtual void visit    ( const java::asg::statm::Synchronized&, bool );
    virtual void visit    ( const java::asg::statm::Try&, bool );
    virtual void visitEnd ( const java::asg::statm::Try&, bool );
    virtual void visit    ( const java::asg::expr::Conditional&, bool );
    virtual void visit    ( const java::asg::expr::InfixExpression&, bool );
    virtual void visitEnd ( const java::asg::base::Positioned&, bool );

    // finalization
    virtual void finishVisit();

  private:

    //
    // DATA
    //

    lim::asg::OverrideRelations &overrides;

    struct PackageInfo
    {
      PackageInfo() : package( 0 ) {}
      NodeId package;
    };

    struct MethodInfo
    {
      MethodInfo() :
        method( 0 )
        , calls()
        , throws()
        , canThrow()
        , instantiates()
        , accessesAttribute()
        , NOS( 0 )
        , NL( 0 )
        , NLE( 0 )
        , NOB( 1 )
        , currentNL( 0 )
        , currentNLE( 0 )
        , belongsTo()
        , hasMember()
      {}

      NodeId method;

      std::set<NodeId> calls;               // lim ids of outgoing MethodCall nodes
      std::set<NodeId> throws;              // lim type ids
      std::set<NodeId> canThrow;            // lim type ids
      std::set<NodeId> instantiates;        // lim type ids
      std::set<NodeId> accessesAttribute;   // lim Attribute ids
      int NOS;
      int NL;
      int NLE;
      int NOB;
      int currentNL;
      int currentNLE;

      // only for InitBlocks
      std::set<NodeId> belongsTo;
      std::set<NodeId> hasMember;                          
    };

    struct ClassInfo
    {
      ClassInfo() :
        clazz( 0 ),
        instanceInit(),
        staticInit(),
        isSubclass(),
        hasInstanceAttributes( false ),
        hasStaticAttributes( false )
      {}

      NodeId clazz;
      MethodInfo instanceInit;
      MethodInfo staticInit;

      std::set<NodeId> isSubclass;

      bool hasInstanceAttributes;
      bool hasStaticAttributes;
    };

    struct AttributeInfo
    {
      AttributeInfo() : attribute( 0 ), calls() {}

      NodeId attribute;
      std::set<NodeId> calls;
    };

    std::stack<PackageInfo> packageStack;       ///< Stack for the current Package info
    std::stack<ClassInfo> classStack;           ///< Stack for the current Class info
    std::stack<AttributeInfo> attributeStack;   ///< Stack for the current Attribute info
    std::stack<MethodInfo> methodStack;         ///< Stack for the current Method info
    std::stack<std::set<NodeId> > usesStack;    ///< Stack for the other type usage of the current Member

    lim::asg::Factory& limFactory;          ///< Reference to the Lim factory
    java::asg::Factory& javaFactory;        ///< Reference to the (current) JAN factory
    JAN2LimMap& uniqueNameNodeMap;          ///< Stores the unique names and Lim pointers of the nodes that are already built
    JAN2LimLocalMap localMap;               ///< Java pointer to Lim pointer map ( per .jsi, for performance )
    TypeMap typeMap;                        ///< For fast java::Type to lim::Type lookup
    CGIMap& cgiMap;                         ///< For unique ClassGenericInstance generation
    std::string& componentName;             ///< The name of the current component
    lim::asg::base::Component& component;   ///< The current component
    LimOrigin& origin;                      ///< The lim origin data
    const lim::asg::ReverseEdges& revEdges; ///< Reverse edges for lim parent search

    std::map<NodeId, CompletionStates>& nodeStates;                    ///< Stores the completion states of all lim nodes
    std::map<NodeId, HalsteadVisitor::HalsteadInfo> halsteadValues;    ///< Stores the halstead info for each method

    NodeId skipUntil;   ///< For skipping subtrees that are already built

    //
    // UTILS
    //

    std::string getUniqueName( const java::asg::base::Base& ) const;            ///< Gets the unique name of the given node
    PosInfo javaPosInfo( const java::asg::base::Base& ) const;                  ///< Gets a PosInfo struct that represents the java node's position (and can be used as a key)
    lim::asg::base::Base* getLimPtrByName( const java::asg::base::Base* );      ///< name-map part of the getLimPtr implementation, separated for oldVersionLinking
    lim::asg::base::Base* _getLimPtr( const java::asg::base::Base* );           ///< getLimPtr implementation, needs wrapper for origin data
    lim::asg::base::Base* getLimPtr( const java::asg::base::Base* );            ///< Converts JAN pointers to Lim pointers if they exist, 0 otherwise
    lim::asg::base::Base* getLimPtr( const java::asg::base::Base& );            ///< Converts JAN nodes to Lim pointers if they exist, 0 otherwise
    bool isClassLevelVariable( const java::asg::base::Base& node ) const;       ///< Returns whether the node should be a Lim Variable
    bool isMethodParameter( const java::asg::base::Base& node ) const;          ///< Returns whether the node should be a Lim Parameter
    bool isLimCompatible( const java::asg::base::Base& ) const;                 ///< Returns whether the node should be build in Lim
    java::asg::base::Base* getParentPtr( const java::asg::base::Base& );        ///< Gets the JAN pointer of parent from JAN node
    java::asg::base::Base* getParentPtr( const NodeId& );                       ///< Gets the JAN pointer of parent from JAN id
    CompletionStates getState( const lim::asg::base::Base* );                   ///< Gets the state of the Lim node
    void setState( const lim::asg::base::Base*, CompletionStates );             ///< Sets the state of the Lim node
    void visitInitBlocks( const java::asg::struc::InitializerBlock& );          ///< Combined visit logic for InitBlocks
    void erase( std::set<NodeId>&, const std::set<NodeId>& );

    //
    // BUILDING
    //

    lim::asg::NodeKind getLimKind( const java::asg::base::Base& node, bool tolerateError = false );             ///< Gets what kind of node we should build from the given java node
    lim::asg::base::Base& createLimNode( const java::asg::base::Base&, CompletionStates, bool );                ///< Creates a Lim node from a JAN node
    lim::asg::physical::File& createFile( const java::asg::base::PositionedWithoutComment& );                   ///< Create Lim File
    lim::asg::logical::ClassGenericInstance& getCGIforJavaType( const java::asg::type::ParameterizedType& );    ///< Builds unique lim::ClassGenericInstance nodes for java::Types
    inline void buildUnknown();                                                                                 ///< Adds an stk::Unknown simpleType
    void addLimTypeFormers( const java::asg::type::Type& );                                                     ///< Builds one or more lim::TypeFormers for a given java::Type
    lim::asg::type::Type& getLimType( const java::asg::type::Type& );                                           ///< Converts java Types to lim Types ( builds them first if necessary )
    lim::asg::type::Type& getUnknownType();                                                                     ///< Gets an "error" type directly

    //
    // DATA TRANSFER
    //

    template<class L, class J> L* buildDispatch( const java::asg::base::Base& );                    ///< Shared build and fill logic
    bool hasPosition( const java::asg::base::Base& javaNode );                                      ///< For correct linking
    void fillMemberData( lim::asg::logical::Member&, const java::asg::struc::Member& );             ///< Fills Member-related data
    void fillScopeData( lim::asg::logical::Scope&, const java::asg::struc::Member& );               ///< Fills Scope-related data
    void fillData( lim::asg::logical::Package&, const java::asg::struc::Package& );                 ///< Fills Package-related data
    void fillData( lim::asg::logical::Class&, const java::asg::struc::TypeDeclaration& );           ///< Fills Class-related data
    void fillData( lim::asg::logical::Method&, const java::asg::struc::Declaration& );              ///< Fills Method-related data
    void fillData( lim::asg::logical::Attribute&, const java::asg::struc::VariableDeclaration& );   ///< Fills Attribute-related data
    void fillData( lim::asg::logical::GenericParameter&, const java::asg::struc::TypeParameter& );  ///< Fills GenericParameter-related data
    void fillData( lim::asg::logical::Parameter&, const java::asg::struc::Parameter& );             ///< Fills Parameter-related data

    void fillCollectedMethodData( lim::asg::logical::Method&, const MethodInfo& );                  ///< Fills collected Method-related data
    void fillInitBlockData( const MethodInfo& );                                                    ///< Fills collected Static- or InstanceInitBlock-related data
    void addUses( lim::asg::logical::Member&, const std::set<NodeId>& );                            ///< Fills the uses edges

    void propagateFilter( const java::asg::base::Base&, lim::asg::base::Base*, bool );              ///< Propagate the collected filter information

    //
    // METRICS
    //
  public:
    static void setLineMetrics( lim::asg::Factory& );   ///< Finalizes LLOC and TLLOC data in the LimFactory
    static void filterInitBlocks( lim::asg::Factory& ); ///< Filters all init blocks

  private:
    void insertLLOCMap( const java::asg::base::Positioned& );                                                     ///< Fills LLOC info for Positioned nodes
    void insertLLOCMap( const java::asg::Range& );                                                     ///< Fills LLOC info
    void assignPathLineToNode( NodeId, Key, long, long, long, long, LLOCMapType& = LLOCMap);   ///< Matches LLOC info to Lim nodes
    static unsigned long collectTLLOC( const lim::asg::logical::Scope& );                                         ///< collects TLLOC data for Scopes

    static void mergeTLLOC( const lim::asg::logical::Scope &limScope, PathLineMapType& TLLOC_ofScope );

    struct Interval
    {
      Interval() : key( 0 ), from( 0 ), to( 0 ) {}

      Key key;
      unsigned long from;
      unsigned long to;
    };

    static bool getIsCommonLine(const LLOCMapType& llocMap, NodeId id, Key key, unsigned long line);
    static void setLOC( lim::asg::logical::Scope& limScope );
    static bool borderCounts( lim::asg::logical::Scope& limScope, Key key, long line, PathLineMapType& visited );
    static unsigned long getTLOC( const lim::asg::logical::Scope& limScope, std::vector<Interval>& intervals );

    // PathLineMapType componentLLOCMap;

    // separate treatment for the System component
    // needs to be revised when the component hierarchy changes
    //static PathLineMapType systemLLOCMap;

    static std::map< NodeId , std::map<Key, unsigned long> > componentTLOCMap;

    static unsigned long pathLineMapCount( const PathLineMapType& map );

    static std::set<NodeId> initBlocks; ///< Filter these nodes (InitBlocks) AFTER setting TLLOC, se we don't have to turn off the filter

    void incNOS( const java::asg::base::Positioned& javaNode );
    void incNOB();
    void incNL( bool );
    void decNL( bool );

    bool eligibleForNLE( const java::asg::statm::Selection& );  ///< Is it an If that is the FalseSubstatement of another If?
    static void mergePathLineMaps( PathLineMapType& result, const PathLineMapType& other );

    void addIsContainedInEdge( lim::asg::logical::Member& limNode, const java::asg::base::PositionedWithoutComment& posWC );
    //
    // STATISTICS RELATED
    //
  public:

    struct VisitStat
    {
      VisitStat()
        : external( 0 )
        , source( 0 )
        , skip( 0 )
        , irrelevant( 0 )
        , converted( 0 )
        , total( 0 )
      {}

      int external;
      int source;
      int skip;
      int irrelevant;
      int converted;
      int total;
    };

  private:
    VisitStat& classStats;
    bool scc;

    void oldVersionLinking( const java::asg::base::Base& node );
    void addLogicalLineOfComponent( Key pathKey, unsigned line , NodeId);
    void addLocToComponent ( NodeId nodeId, Key key, long lastLineNumber );

  private:
    bool buildEmptyInitBlocks;

    MethodInfo createEmptyInitBlock( lim::asg::logical::Class* parent, bool isStatic );
  };
}}

#endif
