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

#include "../../inc/metrics/Documentation.h"

using namespace std;
using namespace columbus::lim::asg;
using namespace columbus::graphsupport::graphconstants;

namespace columbus { namespace lim { namespace metrics {

  DocBase::DocBase( const std::string& name, MetricDataTypes type, bool enabled, SharedContainers* shared ) :
    MetricHandler( name, type, enabled, shared ) {}

  const string& DocBase::translateLevel( Language language, const string& level ) const {
    const string& newLevel = MetricHandler::translateLevel( language, level );

    if ( language == limLangC ) {
      if (
        newLevel == NTYPE_LIM_STRUCTURE ||
        newLevel == NTYPE_LIM_UNION
      ) {
        return NTYPE_LIM_CLASS;
      }
    }

    if ( language == limLangCpp ) {
      if (
        newLevel == NTYPE_LIM_CLASS ||
        newLevel == NTYPE_LIM_UNION
      ) {
        return NTYPE_LIM_CLASS;
      }
    }

    return newLevel;
  }

  //
  // DLOC
  //

  DLOC::DLOC( bool enabled, SharedContainers* shared ) : DocBase( "DLOC", mdtInt, enabled, shared ) {

    this->registerHandler( phaseVisit, NTYPE_LIM_METHOD, limLangOther, false, [this]( NodeWrapper& node ) {

      const logical::Method& method = node.getLimNode<logical::Method>();
      this->mapComments(method, this->shared->currentMethodInfo());
      if ( ! this->shared->classStack.empty() ) {
        this->mapComments(method, this->shared->currentClassInfo());
      }
      this->mapComments(method, this->shared->currentPackageInfo());

      ListIterator<base::Component> i = method.getBelongsToListIteratorBegin(), end = method.getBelongsToListIteratorEnd();
      for (; i != end; ++i) {
        this->mapComments(method, this->shared->components.map[&(*i)]);
      }

      addMetric( node, this->shared->currentMethodInfo().mapCount(this->name) );

    });

    this->registerHandler( phaseVisit, NTYPE_LIM_ATTRIBUTE, limLangOther, false, [this]( NodeWrapper& node ) {

      const logical::Attribute& attr = node.getLimNode<logical::Attribute>();
      if ( ! this->shared->classStack.empty() ) {
        this->mapComments(attr, this->shared->currentClassInfo());
      }
      this->mapComments(attr, this->shared->currentPackageInfo());

      ListIterator<base::Component> i = attr.getBelongsToListIteratorBegin(), end = attr.getBelongsToListIteratorEnd();
      for (; i != end; ++i) {
        this->mapComments(attr, this->shared->components.map[&(*i)]);
      }

    });

    this->registerHandler( phaseVisitEnd, NTYPE_LIM_CLASS, limLangOther, false, [this]( NodeWrapper& node ) {

      const logical::Class& clazz = node.getLimNode<logical::Class>();
      this->mapComments(clazz, this->shared->currentClassInfo());
      this->mapComments(clazz, this->shared->currentPackageInfo());

      ListIterator<base::Component> i = clazz.getBelongsToListIteratorBegin(), end = clazz.getBelongsToListIteratorEnd();
      for (; i != end; ++i) {
        this->mapComments(clazz, this->shared->components.map[&(*i)]);
      }

      addMetric( node, this->shared->currentClassInfo().mapCount(this->name) );

    });

  }

  int getNumberOfEndLines(const std::string& str) {

      if (str.empty()) {
          return 0;
      }

      int nol = 1;
      for (size_t i = 0; i < str.size(); ++i) {
          if (str[i] == '\n') {
              nol++;
          }
      }
      return nol;
  }

  void DLOC::mapComments(const logical::Member& node, Info& info) const {
      ListIterator<base::Comment> commentIt = node.getCommentListIteratorBegin();
      for (; commentIt != node.getCommentListIteratorEnd(); ++commentIt) {
          info.maps[this->name][commentIt->getId()] = getNumberOfEndLines(commentIt->getText());
      }
  }

  const string& DLOC::translateLevel( Language language, const string& level ) const {
    const string& newLevel = DocBase::translateLevel( language, level );

    switch ( language ) {
      case limLangC:
      case limLangCpp:
      case limLangCsharp:
        if (
          newLevel == NTYPE_LIM_CLASS ||
          newLevel == NTYPE_LIM_ENUM ||
          newLevel == NTYPE_LIM_INTERFACE
        ) {
          return NTYPE_LIM_CLASS;
        }
        break;
      default:
        break;
    }

    return newLevel;
  }

  //
  // CLOC
  //

  CLOC::CLOC( bool enabled, SharedContainers* shared ) : DocBase( "CLOC", mdtInt, enabled, shared ) {

    dependencies.insert( "DLOC" );

    this->registerHandler( phaseVisit, NTYPE_LIM_METHOD, limLangOther, false, [this]( NodeWrapper& node ) {

      const logical::Method& method = node.getLimNode<logical::Method>();
      Info& info = this->shared->scopes.map[ &method ];
      int mcl = method.getCommentLines();

      // propagate the commentLines part only
      if (!this->shared->classStack.empty()) {
        this->shared->currentClassInfo().ints[this->name] += mcl;
      }
      this->shared->currentPackageInfo().ints[this->name] += mcl;

      ListIterator<base::Component> i = method.getBelongsToListIteratorBegin(), end = method.getBelongsToListIteratorEnd();
      for (; i != end; ++i) {
        this->shared->components.map[&(*i)].ints[this->name] += mcl;
      }

      int cloc = info.ints[this->name] = info.mapCount("DLOC") + mcl;
      addMetric(node, cloc);

      cleanup( node, "DLOC" );
      
    });

    this->registerHandler( phaseVisit, NTYPE_LIM_ATTRIBUTE, limLangOther, false, [this]( NodeWrapper& node ) {

      const logical::Attribute& attr = node.getLimNode<logical::Attribute>();
      int acl = attr.getCommentLines();
      if ( ! this->shared->classStack.empty() ) {
        this->shared->currentClassInfo().ints[this->name] += acl;
      }
      this->shared->currentPackageInfo().ints[this->name] += acl;

      // propagate to component level, like above
      ListIterator<base::Component> i = attr.getBelongsToListIteratorBegin(), end = attr.getBelongsToListIteratorEnd();
      for (; i != end; ++i) {
        this->shared->components.map[&(*i)].ints[this->name] += acl;
      }

    });

    this->registerHandler( phaseVisitEnd, NTYPE_LIM_CLASS, limLangOther, false, [this]( NodeWrapper& node ) {

      const logical::Class& clazz = node.getLimNode<logical::Class>();
      Info& info = this->shared->scopes.map[ &clazz ];
      int ccl = clazz.getCommentLines();

      // propagate to package level
      this->shared->currentPackageInfo().ints[this->name] += ccl;

      // propagate to component level
      ListIterator<base::Component> i = clazz.getBelongsToListIteratorBegin(), end = clazz.getBelongsToListIteratorEnd();
      for (; i != end; ++i) {
        this->shared->components.map[&(*i)].ints[this->name] += ccl;
      }

      int cloc = (info.ints[this->name] += info.mapCount("DLOC") + ccl);
      addMetric(node, cloc);

      cleanup( node, "DLOC" );
      
    });

    this->registerHandler( phaseVisitEnd, NTYPE_LIM_PACKAGE, limLangOther, false, [this]( NodeWrapper& node ) {

      const logical::Package& package = node.getLimNode<logical::Package>();
      Info& info = this->shared->scopes.map[ &package ];
      int pcl = package.getCommentLines();

      // propagate to component level
      ListIterator<base::Component> i = package.getBelongsToListIteratorBegin(), end = package.getBelongsToListIteratorEnd();
      for (; i != end; ++i) {
        this->shared->components.map[&(*i)].ints[this->name] += pcl;
      }

      int cloc = ( info.ints[this->name] += info.mapCount("DLOC") + pcl );
      addMetric( node, cloc );
      
    });

    this->registerHandler( phaseVisit, NTYPE_LIM_FILE, limLangOther, false, [this]( NodeWrapper& node ) {
      const physical::File& file = node.getLimNode<physical::File>();
      
      //
      // File-level CLOC is temporarily C/C++/Python only !!
      //
      Language l = file.getFactory().getLanguage();
      if ( l != limLangC && l != limLangCpp && l != limLangPython ) return;
      
      this->shared->files[&file].ints["CLOC"] = file.getCLOC();
      addMetric( node, (int) file.getCLOC() );
    });

    this->registerHandler(phaseVisitEnd, NTYPE_LIM_COMPONENT, limLangOther, false, [this](NodeWrapper& node) {
      const base::Base* ptr = &node.getLimNode<base::Base>();
      Info& info = this->shared->components.map[ptr];
      info.ints[this->name] += info.mapCount("DLOC");
    });

  }

  const string& CLOC::translateLevel( Language language, const string& level ) const {
    const string& newLevel = DocBase::translateLevel( language, level );

    switch ( language ) {
      case limLangCpp:
      case limLangCsharp:
        if (
          newLevel == NTYPE_LIM_CLASS ||
          newLevel == NTYPE_LIM_INTERFACE
        ) {
          return NTYPE_LIM_CLASS;
        }
        break;
      default:
        break;
    }

    return newLevel;
  }

  TCLOC::TCLOC( bool enabled, SharedContainers* shared ) : DocBase( "TCLOC", mdtInt, enabled, shared ) {

    dependencies.insert( "CLOC" );

    // Method level
    // Same for Classes and Packages, see translateLevel
    propagateScopeInt( phaseFinalize, NTYPE_LIM_METHOD, limLangOther );



    // Component level
    registerHandler(phaseFinalize, NTYPE_LIM_COMPONENT, limLangOther, false, [this, shared](NodeWrapper& node)
    {
      const base::Component* component = &node.getLimNode<base::Component>();
      const base::Base* ptr = &node.getLimNode<base::Base>();
      Info& info = this->shared->components.map[ptr];
      int value = 0;

      Language l = component->getFactory().getLanguage();
      // The <System> component is treated differently, as the Int metrics cannot be simply summed up from the subscomponents.
      // Since File-level CLOC is temporarily available in C/C++/Python only we use this for only those languages yet!!
      if (((l == limLangC) || (l == limLangCpp) || (l == limLangPython)) &&
          !component->getContainsIsEmpty())
      {
        for (auto fileInfo : shared->files)
          value += fileInfo.second.ints["CLOC"];
      }
      else
      {
        value = info.ints[this->name];
      }
      addMetric(node, value);
    });
  }

  const string& TCLOC::translateLevel( Language language, const string& level ) const {
    const string* newLevel = & DocBase::translateLevel( language, level );

    // grouping Interfaces to Classes
    if ( language == limLangCpp || language == limLangCsharp ) {
      if (
        newLevel == &NTYPE_LIM_CLASS ||
        newLevel == &NTYPE_LIM_INTERFACE
      ) {
        newLevel = &NTYPE_LIM_CLASS;
      }
    }

    // grouping all computations to the Method handler
    if ( newLevel == &NTYPE_LIM_CLASS || newLevel == &NTYPE_LIM_PACKAGE ) {
      return NTYPE_LIM_METHOD;
    }

    return *newLevel;
  }

  // (T)PDA

  const string PUBLIC = "PUBLIC";
  const string TOTAL_PUBLIC = "T" + PUBLIC;
  const string PUBLIC_DOC = "PDA";
  const string TOTAL_PUBLIC_DOC = "T" + PUBLIC_DOC;

  PDA::PDA( bool enabled, SharedContainers* shared ) : DocBase( "PDA", mdtInt, enabled, shared ) {

    registerHandler( phaseVisit, NTYPE_LIM_METHOD, limLangOther, false, [this] ( NodeWrapper& node ) {
      process( node );
    });

    registerHandler( phaseVisit, NTYPE_LIM_CLASS, limLangOther, false, [this] ( NodeWrapper& node ) {
      process( node );

      // exception, a class affects its own PDA/AD even if it's not public
      const logical::Scope& clazz = node.getLimNode<logical::Scope>();
      Info& info = this->shared->currentClassInfo();

      set<NodeId>& p = info.sets[PUBLIC];
      p.insert( clazz.getId() );

      set<NodeId>& d = info.sets[PUBLIC_DOC];
      if ( ! clazz.getCommentIsEmpty() ) {
        d.insert( clazz.getId() );
      }
    });

    propagateScopeSet( phaseVisitEnd, NTYPE_LIM_CLASS, limLangOther );
    propagateScopeSet( phaseVisitEnd, NTYPE_LIM_PACKAGE, limLangOther );

    registerHandler( phaseFinishVisit, NTYPE_LIM_FILE, limLangOther, false, [this] ( NodeWrapper& node ) {
      const physical::File& file = node.getLimNode<const physical::File&>();
      addMetric( node, (int) this->shared->files[&file].sets[this->name].size() );
    });

  }

  void PDA::process( NodeWrapper& node ) {

    // A scope is considered a part of the public API if:
    // - it has a public accessibility (for everyone)
    // - non-static in case of a global function (for files only)
    // - it is inside only public classes or non-anonymous packages (for packages, components and files)

    const logical::Scope& originalScope = node.getLimNode<logical::Scope>();
    const logical::Scope& resolvedScope = resolve( originalScope );

    bool documented = !originalScope.getCommentIsEmpty() || !resolvedScope.getCommentIsEmpty();
    bool classPublic = isClassPublic( resolvedScope );
    bool packagePublic = classPublic && isPackagePublic( resolvedScope );
    bool filePublic = packagePublic && isFilePublic( resolvedScope );

    if ( ! shared->classStack.empty() ) {
      add( resolvedScope, shared->currentClassInfo().sets, classPublic, documented );
    }
    add( resolvedScope, shared->currentPackageInfo().sets, packagePublic, documented );
      
    ListIterator<base::Component> ci = resolvedScope.getBelongsToListIteratorBegin(),
                                  cend = resolvedScope.getBelongsToListIteratorEnd();
    for ( ; ci != cend; ++ci ) {
      add( resolvedScope, shared->components.map[&(*ci)].sets, packagePublic, documented );
    }

    ListIteratorAssocSourcePosition<physical::File> fi = resolvedScope.getIsContainedInListIteratorAssocBegin(),
                                                    fend = resolvedScope.getIsContainedInListIteratorAssocEnd();
    for (; fi != fend; ++fi) {
      add( resolvedScope, shared->files[&(*fi)].sets, filePublic, documented );
    }

  }

  const logical::Scope& PDA::resolve( const logical::Scope& scope ) {

    Key nameKey = scope.getMangledNameKey();

    if ( resolveMap.count(nameKey) > 0 ) {
      return *resolveMap[nameKey];
    }

    const logical::Scope* resolved = &scope;
    if ( ! NodeWrapper::isDefinition( scope ) ) {
      if ( scope.getDeclares() && Common::getIsScope(*scope.getDeclares()) ) {
        resolved = dynamic_cast<logical::Scope*>( scope.getDeclares() );
      }
    }

    resolveMap[nameKey] = resolved;
    return *resolved;
  }

  bool PDA::isClassPublic( const logical::Scope& scope ) const {
    AccessibilityKind ack = scope.getAccessibility();
    return (ack == ackPublic || (ack == ackNone && NodeWrapper::isFunction(scope)));
  }

  bool PDA::isPackagePublic( const logical::Scope& scope ) const {

    const logical::Scope* step = &scope;
    const ReverseEdges& rev = scope.getFactory().getReverseEdges();
    while ( true ) {

      ListIterator<base::Base> i = rev.constIteratorBegin( step->getId(), edkScope_HasMember );
      if ( i == rev.constIteratorEnd( step->getId(), edkScope_HasMember ) ) break;

      step = dynamic_cast<const logical::Scope*>( &(*i) );
      if ( Common::getIsClass(*step) && step->getAccessibility() == ackPublic ) continue;
      if ( Common::getIsPackage(*step) && !step->getIsAnonymous() ) continue;

      break;
    }

    return (step == scope.getFactory().getRoot());
  }

  bool PDA::isFilePublic( const logical::Scope& scope ) const {
    return ! (scope.getIsStatic() && NodeWrapper::isFunction(scope));
  }

  void PDA::add( const logical::Scope& scope, Info::SetMap& sets, bool isPublic, bool documented ) {

    NodeId scopeID = scope.getId();

    if ( isPublic ) {
      sets[PUBLIC].insert( scopeID );
      if ( documented ) {
        sets[PUBLIC_DOC].insert( scopeID );
      }
    }
    
  }

  const string& PDA::translateLevel( Language language, const string& level ) const {
    const string& newLevel = DocBase::translateLevel( language, level );

    switch ( language ) {
      case limLangC:
      case limLangCpp:
      case limLangCsharp:
        if (
          newLevel == NTYPE_LIM_CLASS ||
          newLevel == NTYPE_LIM_INTERFACE ||
          newLevel == NTYPE_LIM_ENUM
        ) {
          return NTYPE_LIM_CLASS;
        }
        break;
      default:
        break;
    }

    return newLevel;
  }

  TPDA::TPDA( bool enabled, SharedContainers* shared ) : DocBase( "TPDA", mdtInt, enabled, shared ) {

    dependencies.insert( "PDA" );

    propagateScopeSet( phaseFinalize, NTYPE_LIM_PACKAGE, limLangOther );
    propagateComponentSet();

  }

  //
  // (T)PUA
  //

  PUABase::PUABase( bool total, bool enabled, SharedContainers* shared ) : DocBase( ( total ? "TPUA" : "PUA" ), mdtInt, enabled, shared ) {

    dependencies.insert( "PDA" );

    if ( total ) {
      registerHandler( phaseFinalize, NTYPE_LIM_PACKAGE, limLangOther, false, [this] ( NodeWrapper& node ) {
        computeScope( node, true );
      });

      registerHandler( phaseFinalize, NTYPE_LIM_COMPONENT, limLangOther, false, [this] ( NodeWrapper& node ) {
        computeComponent( node );
      });
    } else {
      registerHandler( phaseVisitEnd, NTYPE_LIM_CLASS, limLangOther, false, [this] ( NodeWrapper& node ) {
        computeScope( node, false );
      });

      registerHandler( phaseVisitEnd, NTYPE_LIM_PACKAGE, limLangOther, false, [this] ( NodeWrapper& node ) {
        computeScope( node, false );
      });

      registerHandler( phaseFinishVisit, NTYPE_LIM_FILE, limLangOther, false, [this] ( NodeWrapper& node ) {
        const physical::File& file = node.getLimNode<const physical::File&>();
        compute( node, this->shared->files[&file].sets, false );
      });
    }
  }

  void PUABase::computeScope( NodeWrapper& node, bool total ) {
    const logical::Scope& scope = node.getLimNode<logical::Scope>();
    Info::SetMap& sets = shared->scopes.map[&scope].sets;
    compute( node, sets, total );
  }

  void PUABase::computeComponent( NodeWrapper& node ) {
    const base::Component& component = node.getLimNode<base::Component>();
    Info::SetMap& sets = shared->components.map[&component].sets;
    compute( node, sets, true );
  }

  void PUABase::compute( NodeWrapper& node, Info::SetMap& sets, bool total ) {
    int p = sets[total ? TOTAL_PUBLIC : PUBLIC].size();
    int d = sets[total ? TOTAL_PUBLIC_DOC : PUBLIC_DOC].size();

    addMetric( node, p - d );
  }

  PUA::PUA( bool enabled, SharedContainers* shared ) : PUABase( false, enabled, shared ) {}
  TPUA::TPUA( bool enabled, SharedContainers* shared ) : PUABase( true, enabled, shared ) {}

  const string& PUA::translateLevel( Language language, const string& level ) const {
    const string& newLevel = PUABase::translateLevel( language, level );

    switch ( language ) {
      case limLangC:
      case limLangCpp:
      case limLangCsharp:
        if (
          newLevel == NTYPE_LIM_CLASS ||
          newLevel == NTYPE_LIM_INTERFACE ||
          newLevel == NTYPE_LIM_ENUM
        ) {
          return NTYPE_LIM_CLASS;
        }
        break;
      default:
        break;
    }

    return newLevel;
  }

  //
  // (T)AD
  //

  ADBase::ADBase( bool total, bool enabled, SharedContainers* shared ) : DocBase( ( total ? "TAD" : "AD" ), mdtFloat, enabled, shared ) {

    dependencies.insert( "PDA" );

    if ( total ) {
      registerHandler( phaseFinalize, NTYPE_LIM_PACKAGE, limLangOther, false, [this] ( NodeWrapper& node ) {
        computeScope( node, true );
      });

      registerHandler( phaseFinalize, NTYPE_LIM_COMPONENT, limLangOther, false, [this] ( NodeWrapper& node ) {
        computeComponent( node );
      });
    } else {
      registerHandler( phaseVisitEnd, NTYPE_LIM_CLASS, limLangOther, false, [this] ( NodeWrapper& node ) {
        computeScope( node, false );
      });

      registerHandler( phaseVisitEnd, NTYPE_LIM_PACKAGE, limLangOther, false, [this] ( NodeWrapper& node ) {
        computeScope( node, false );
      });
    }
  }

  void ADBase::computeScope( NodeWrapper& node, bool total ) {
    const logical::Scope& scope = node.getLimNode<logical::Scope>();
    Info::SetMap& sets = shared->scopes.map[&scope].sets;
    compute( node, sets, total );
  }

  void ADBase::computeComponent( NodeWrapper& node ) {
    const base::Component& component = node.getLimNode<base::Component>();
    Info::SetMap& sets = shared->components.map[&component].sets;
    compute( node, sets, true );
  }

  void ADBase::compute( NodeWrapper& node, Info::SetMap& sets, bool total ) {
    int p = sets[total ? TOTAL_PUBLIC : PUBLIC].size();
    int d = sets[total ? TOTAL_PUBLIC_DOC : PUBLIC_DOC].size();

    addMetric( node, (float)( p == 0 ? 0.0 : (d / (float)p) ) );
  }

  const string& ADBase::translateLevel( Language language, const string& level ) const {
    const string& newLevel = DocBase::translateLevel( language, level );

    switch ( language ) {
      case limLangC:
      case limLangCpp:
      case limLangCsharp:
        if (
          newLevel == NTYPE_LIM_CLASS ||
          newLevel == NTYPE_LIM_INTERFACE ||
          newLevel == NTYPE_LIM_ENUM
        ) {
          return NTYPE_LIM_CLASS;
        }
        break;
      default:
        break;
    }

    return newLevel;
  }

  AD::AD( bool enabled, SharedContainers* shared ) : ADBase( false, enabled, shared ) {}
  TAD::TAD( bool enabled, SharedContainers* shared ) : ADBase( true, enabled, shared ) {}

  //
  // (T)CD
  //

  CDBase::CDBase( bool total, bool enabled, SharedContainers* shared ) : DocBase( (total ? "TCD" : "CD"), mdtFloat, enabled, shared ) {

    if ( total ) {
      dependencies.insert( "TLLOC" );
      dependencies.insert( "TCLOC" );
      scopeLLOC = &logical::Scope::getTLLOC;
      componentLLOC = &base::Component::getTLLOC;
      CLOC = "TCLOC";
    } else {
      dependencies.insert( "LLOC" );
      dependencies.insert( "CLOC" );
      scopeLLOC = &logical::Scope::getLLOC;
      CLOC = "CLOC";
    }

    registerHandler( ( total ? phaseFinalize : phaseVisitEnd ), NTYPE_LIM_METHOD, limLangOther, false, [this] ( NodeWrapper& node ) {

      const logical::Scope& scope = node.getLimNode<logical::Scope>();

      int c = this->shared->scopes.map[&scope].ints[this->CLOC];
      int l = (scope.*(this->scopeLLOC))();

      int denom = c + l;
      double cd = ( denom == 0 ) ? 0.0 : ( c / (double)denom );

      addMetric( node, cd );

    });

    if ( total ) {

      registerHandler( phaseFinalize, NTYPE_LIM_COMPONENT, limLangOther, false, [this] ( NodeWrapper& node ) {

        const base::Component& component = node.getLimNode<base::Component>();

        int c = this->shared->components.map[&component].ints[this->CLOC];
        int l = (component.*(this->componentLLOC))();

        int denom = c + l;
        double cd = ( denom == 0 ) ? 0.0 : ( c / (double)denom );

        addMetric( node, cd );

      });

    }
  }

  const string& CDBase::translateLevel( Language language, const string& level ) const {

    const string& newLevel = DocBase::translateLevel( language, level );

    if ( newLevel == NTYPE_LIM_CLASS || newLevel == NTYPE_LIM_PACKAGE ) {
      return NTYPE_LIM_METHOD;
    }

    return newLevel;
  }

  CD::CD( bool enabled, SharedContainers* shared ) : CDBase( false, enabled, shared ) {}
  TCD::TCD( bool enabled, SharedContainers* shared ) : CDBase( true, enabled, shared ) {}

}}}
