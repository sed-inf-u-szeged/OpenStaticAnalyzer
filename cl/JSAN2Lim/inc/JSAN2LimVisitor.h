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

#ifndef _JSAN2LIMH_
#define _JSAN2LIMH_

#include "lim/inc/lim.h"
#include "javascript/inc/javascript.h"
#include "HalsteadVisitor.h"
#include <map>
#include <set>

namespace columbus {
namespace JSAN2Lim {

  class JSAN2LimVisitor : public javascript::asg::VisitorAbstractNodes {

  public:
    struct PosInfo {
      PosInfo()
        : posString()
        , file()
      {
      }

      std::string posString;
      std::string file;

      bool matches(const PosInfo& other) const;
      bool operator<(const PosInfo& other) const;
    };

    typedef std::map<PosInfo, NodeId> NodeMap;
    typedef std::map<std::string, NodeId> MethodMap;
    typedef std::map<std::string, NodeId> AttributeMap;
    typedef std::map<NodeId, NodeId> CallExprMap;
    typedef std::map<std::string, NodeId> ClassMap;

    JSAN2LimVisitor(lim::asg::Factory&, columbus::javascript::asg::Factory& javascriptFact, LimOrigin& origin, std::string& componentName, std::map<NodeId, HalsteadVisitor::HalsteadInfo>);
    lim::asg::Factory& limFactory;
    LimOrigin& origin;
    std::map<NodeId, HalsteadVisitor::HalsteadInfo> halsteadValues;    ///< Stores the halstead info for each method

    static std::map<Key, NodeId> fileMap;

    static void finalize(const columbus::lim::asg::Factory& factory);
    static void setLineMetricsOfComponent(lim::asg::base::Base& node);

  public:
    virtual void visit(const javascript::asg::structure::Class&, bool);
    virtual void visitEnd(const javascript::asg::structure::Class&, bool);
    virtual void visitEnd(const javascript::asg::declaration::ClassDeclaration&, bool);
    virtual void visitEnd(const javascript::asg::expression::ClassExpression&, bool);

    virtual void visit(const javascript::asg::structure::MethodDefinition&, bool);
    virtual void visitEnd(const javascript::asg::structure::MethodDefinition&, bool);

    virtual void visit(const javascript::asg::statement::Function&, bool);
    virtual void visitEnd(const javascript::asg::statement::Function&, bool);

    virtual void visit(const javascript::asg::expression::Identifier&, bool);
    virtual void visitEnd(const javascript::asg::expression::Identifier&, bool);

    virtual void visit(const javascript::asg::statement::Pattern&, bool);
    virtual void visitEnd(const javascript::asg::statement::Pattern&, bool);

    virtual void visit(const javascript::asg::expression::CallExpression&, bool);
    virtual void visitEnd(const javascript::asg::expression::CallExpression&, bool);

    virtual void visit(const javascript::asg::declaration::VariableDeclaration&, bool);
    virtual void visitEnd(const javascript::asg::declaration::VariableDeclaration&, bool);

    virtual void visit(const javascript::asg::base::Program&, bool);
    virtual void visitEnd(const javascript::asg::base::Program&, bool);

    virtual void visit(const javascript::asg::statement::IfStatement&, bool);
    virtual void visitEnd(const javascript::asg::statement::IfStatement&, bool);

    virtual void visit(const javascript::asg::statement::ForStatement&, bool);
    virtual void visitEnd(const javascript::asg::statement::ForStatement&, bool);

    virtual void visit(const javascript::asg::statement::WhileStatement&, bool);
    virtual void visitEnd(const javascript::asg::statement::WhileStatement&, bool);

    virtual void visit(const javascript::asg::statement::SwitchCase&, bool);
    virtual void visitEnd(const javascript::asg::statement::SwitchCase&, bool);

    virtual void visit(const javascript::asg::statement::SwitchStatement&, bool);
    virtual void visitEnd(const javascript::asg::statement::SwitchStatement&, bool);

    virtual void visit(const javascript::asg::statement::ForInStatement&, bool);
    virtual void visitEnd(const javascript::asg::statement::ForInStatement&, bool);

    virtual void visit(const javascript::asg::expression::ConditionalExpression&, bool);
    virtual void visitEnd(const javascript::asg::expression::ConditionalExpression&, bool);

    virtual void visitEnd(const javascript::asg::declaration::FunctionDeclaration&, bool);
    virtual void visitEnd(const javascript::asg::expression::FunctionExpression&, bool);
    virtual void visitEnd(const javascript::asg::expression::ArrowFunctionExpression&, bool);

    virtual void visit(const javascript::asg::statement::TryStatement&, bool);
    virtual void visitEnd(const javascript::asg::statement::TryStatement&, bool);

    virtual void visit(const javascript::asg::statement::BlockStatement&, bool);
    virtual void visitEnd(const javascript::asg::statement::BlockStatement&, bool);

    virtual void visit(const javascript::asg::statement::Statement&, bool);

    virtual void visit(const javascript::asg::base::Positioned&, bool);
    virtual void visitEnd(const javascript::asg::base::Positioned&, bool);

    virtual void visit(const javascript::asg::expression::LogicalExpression&, bool);
    virtual void visit(const javascript::asg::statement::CatchClause&, bool);

  private:
    struct ClassInfo {
      ClassInfo()
        : classNodeId(0)
        , isSubclass(0)
        , hasStaticMethod(false)
        , lines()
        , LLOC(0)
        , LOC(0)
        , TLOC(0)
        , TLLOC(0)
      {
      }

      NodeId classNodeId;
      NodeId isSubclass;
      bool hasStaticMethod;
      std::set<int> lines;
      int LLOC;
      int LOC;
      int TLOC;
      int TLLOC;
      std::set<NodeId> comments;
    };

    struct MethodInfo {
      MethodInfo()
        : methodNodeId(0)
        , calls()
        , NOS(0)
        , NL(0)
        , NLE(0)
        , NOB(1)
        , currentNL(0)
        , currentNLE(0)
        , belongsTo()
        , hasMember()
        , lines()
        , isEmbeddedMethod(false)
        , LLOC(0)
        , LOC(0)
        , TLOC(0)
        , TLLOC(0)
      {
      }
      NodeId methodNodeId;
      std::set<NodeId> calls; // lim ids of outgoing MethodCall nodes
      int NOS;
      int NL;
      int NLE;
      int NOB;
      int currentNL;
      int currentNLE;
      std::set<NodeId> belongsTo;
      std::set<NodeId> hasMember;
      std::set<int> lines;
      bool isEmbeddedMethod;
      int LLOC;
      int LOC;
      int TLOC;
      int TLLOC;
      std::set<NodeId> comments;
    };

    struct PackageInfo {
      PackageInfo()
        : packageNodeId(0)
        , NL(0)
        , NLE(0)
        , NOB(1)
        , NOS(0)
        , LLOC(0)
        , LOC(0)
        , TLOC(0)
        , TLLOC(0)
        , lines()
      {
      }
      NodeId packageNodeId;
      int NL; //maximum function NL
      int NLE; //maximum function NLE
      int NOB;
      int NOS;
      int LLOC;
      int LOC;
      int TLOC;
      int TLLOC;
      std::set<int> lines;
      std::set<NodeId> comments;
    };

    struct AttributeInfo {
      AttributeInfo()
        : attributeNodeId(0)
        , lines()
      {
      }
      NodeId attributeNodeId;
      std::set<int> lines;
    };

    /*
    Metric counter part starts here
    */

    std::stack<AttributeInfo> attributeStack;
    std::stack<ClassInfo> classStack;
    std::stack<MethodInfo> methodStack;
    std::stack<PackageInfo> packageStack;
    std::stack<NodeId> fileStack;
    std::stack<NodeId> lastLimMemberNodeId;
    std::stack<NodeId> lastLimScopeNodeId;
    std::vector<std::string> demangledNameParts;

    void incNOS();
    void incNOB();
    void incNL(bool);
    void decNL(bool);

    bool eligibleForNLE(const javascript::asg::statement::IfStatement&);

    struct Interval {
      Interval()
        : key(0)
        , from(0)
        , to(0)
      {
      }

      Key key;
      unsigned long from;
      unsigned long to;
    };

    /*
    Metric counter part end here
    */

    PosInfo getPosInfo(const javascript::asg::base::Base&) const;

    lim::asg::NodeKind getLimKind(const javascript::asg::base::Base& node, bool tolerateError = false);
    lim::asg::base::Base& createLimNode(const javascript::asg::base::Base&, bool);
    lim::asg::base::Base* getLimNode(const javascript::asg::base::Base&);

    void fillData(lim::asg::logical::Method&, const javascript::asg::structure::MethodDefinition&);
    void fillData(lim::asg::logical::Attribute&, const javascript::asg::declaration::VariableDeclaration&);
    void fillData(lim::asg::logical::Method&, const javascript::asg::expression::FunctionExpression&);
    void fillData(lim::asg::logical::Method&, const javascript::asg::statement::Function&);
    void fillData(lim::asg::logical::Class&, const javascript::asg::structure::Class&);
    void fillData(lim::asg::logical::Parameter&, const javascript::asg::statement::Pattern&);
    void fillData(lim::asg::logical::MethodCall&, const javascript::asg::expression::CallExpression&);

    void fillData(lim::asg::logical::Method&, const javascript::asg::declaration::FunctionDeclaration&);

    void fillCollectedMethodData(lim::asg::logical::Method& method, const javascript::asg::base::Positioned& functionNode);
    void fillCollectedClassData(lim::asg::logical::Class&, const javascript::asg::structure::Class&);
    void fillCollectedPackageData(lim::asg::logical::Package&);

    void addIsContained(lim::asg::logical::Member& member, const javascript::asg::Range& range);
    void addIsContainedInEdge(lim::asg::logical::Member& member, const javascript::asg::base::Positioned& pos);
    bool isMethodParameter(const javascript::asg::statement::Pattern& patternNode);
    bool isLimCompatible(const javascript::asg::base::Positioned&);
    void fillMemberData(lim::asg::logical::Member& member);
    lim::asg::physical::File& createFile(const javascript::asg::base::Positioned&);
    std::string getDemangledName();
    void setSizeMetrics(lim::asg::logical::Member& member);
    void handleComments(lim::asg::Member&, const javascript::asg::base::Positioned&);

    NodeMap nodeMap;
    MethodMap methodMap;
    AttributeMap attributeMap;
    CallExprMap callExprMap;
    ClassMap classMap;
    javascript::asg::Factory& javascriptFactory; // Reference to the (current) JSAN factory
    lim::asg::base::Component& component; // The current component
    const lim::asg::ReverseEdges& revEdges; // Reverse edges for lim parent search
    NodeId skipUntil;
    int anonymusArrowCounter;
    int anonymusFunctionCounter;
    int anonymusMethodCounter;
    int anonymusClassCounter;
  };
}
}
#endif
