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

#ifndef PYTHON2LIM_H
#define PYTHON2LIM_H

#include <python/inc/python.h>
#include <lim/inc/lim.h>
#include <boost/icl/interval_set.hpp>

namespace columbus { namespace python {

  class Python2LimVisitor : public python::asg::VisitorAbstractNodes {
  public:

    typedef std::map<Key, NodeId> Key2IdMapType;

    Python2LimVisitor(python::asg::Factory& pyFact, lim::asg::Factory& limFact, LimOrigin& origin, const std::string& componentName, Key2IdMapType& key2Ids);
    virtual ~Python2LimVisitor();

    virtual void visit    (const columbus::python::asg::base::Positioned&, bool);

    /* visiting MODULE */
    virtual void visit    (const columbus::python::asg::module::Package&, bool);
    virtual void visitEnd (const columbus::python::asg::module::Package&, bool);
    virtual void visit    (const columbus::python::asg::module::Module&, bool);
    virtual void visitEnd (const columbus::python::asg::module::Module&, bool);

    /* visiting STATEMENT */
    virtual void visit    (const columbus::python::asg::statement::ClassDef&, bool);
    virtual void visitEnd (const columbus::python::asg::statement::ClassDef&, bool);
    virtual void visit    (const columbus::python::asg::statement::FunctionDef&, bool);
    virtual void visitEnd (const columbus::python::asg::statement::FunctionDef&, bool);
    virtual void visit    (const columbus::python::asg::statement::Parameter&, bool);

    virtual void visit    (const columbus::python::asg::statement::Try&, bool);
    virtual void visitEnd (const columbus::python::asg::statement::Try&, bool);
    virtual void visit    (const columbus::python::asg::statement::With&, bool);
    virtual void visitEnd (const columbus::python::asg::statement::With&, bool);
    virtual void visit    (const columbus::python::asg::statement::Iteration&, bool);
    virtual void visitEnd (const columbus::python::asg::statement::Iteration&, bool);
    virtual void visit    (const columbus::python::asg::statement::If&, bool);
    virtual void visitEnd (const columbus::python::asg::statement::If&, bool);
    virtual void visit    (const columbus::python::asg::statement::Handler&, bool);
    virtual void visit    (const columbus::python::asg::statement::Global&, bool);
    virtual void visit    (const columbus::python::asg::statement::Raise&, bool);
    virtual void visit    (const columbus::python::asg::statement::Assert&, bool);
    virtual void visit    (const columbus::python::asg::statement::Pass&, bool);
    virtual void visit    (const columbus::python::asg::statement::Assign&, bool);
    virtual void visit    (const columbus::python::asg::statement::Delete&, bool);
    virtual void visit    (const columbus::python::asg::statement::ImportStatement&, bool);
    virtual void visit    (const columbus::python::asg::statement::Return&, bool);
    virtual void visit    (const columbus::python::asg::statement::Print&, bool);
    virtual void visit    (const columbus::python::asg::statement::Break&, bool);
    virtual void visit    (const columbus::python::asg::statement::Continue&, bool);
    virtual void visit    (const columbus::python::asg::statement::Exec&, bool);
    virtual void visit    (const columbus::python::asg::statement::Alias&, bool);

    /* visiting EXPRESSION */
    virtual void visit    (const columbus::python::asg::expression::Identifier&, bool);
    virtual void visit    (const columbus::python::asg::expression::IfExpression&, bool);
    virtual void visit    (const columbus::python::asg::expression::Call&, bool);
    virtual void visit    (const columbus::python::asg::expression::BinaryLogical&, bool);
    virtual void visit    (const columbus::python::asg::expression::Expression&, bool);

    virtual void finishVisit();


    static void finalize( const columbus::lim::asg::Factory& factory );
    static void setLineMetrics( columbus::lim::asg::base::Base& node );


  private:

    struct MethodInfo;
    struct ScopeInfo;

  protected:

    static void setPackageLines( columbus::lim::asg::logical::Package& package );

  /**
   * \brief Returns the id of a lim node
   * \param id         [in] The id of python node whose lim id is needed.
   * \return                The lim id of the python node.
   */
    NodeId getLimNodeId(NodeId pythonId);

  /**
   * \brief Creates lim::asg::Base::base node or return it if it already exists.
   * \param _node      [in] The python node whose lim node pair is created.
   * \return                The lim node.
   */
    lim::asg::base::Base& createIncompleteLimNode(const python::asg::base::Base& _node);

  /**
   * \brief Creates lim::asg::Base::base node or return it if it already exists.
   * \param _node      [in] The python node whose lim node pair is created.
   * \return                The lim node.
   */
    lim::asg::base::Base& createCompleteLimNode(const python::asg::base::Base& _node);

  /**
   * \brief Creates a lim::asg::Base::base node or return it if it already exist and the node
   *        is marked complete or incomplete according to the second parameter.
   * \param _node              [in] The python node whose lim node pair is created.
   * \param isComplete         [in] Deciding whether a complete or an incomplete node is created.
   * \return                        The lim node.
   */
    lim::asg::base::Base& createLimNode(const python::asg::base::Base& _node, bool isComplete);

   /**
    * \brief Converts data for lim::asg::logical::Member
    * \param _node      [in] The python node which is converted.
    * \param limMember  [in] The lim node whose data will be set.
    */
    void setLimMemberData(const python::asg::base::Base& _node, lim::asg::logical::Member& limMember);

   /**
    * \brief Converts data for lim::asg::logical::Class
    * \param _node      [in] The python node which is converted.
    * \param limClass   [in] The lim node whose data will be set.
    */
    void setLimClassData(const python::asg::statement::Statement& _node, lim::asg::logical::Class& limClass);

   /**
    * \brief Converts data for lim::asg::logical::Method
    * \param _node        [in] The python node which is converted.
    * \param limMethod    [in] The lim node whose data will be set.
    */
    void setLimMethodData(const python::asg::statement::Statement& _node, lim::asg::logical::Method& limMethod);

   /**
    * \brief Converts data for a fictive lim method, which contains statements and expressions which are not in a class method or in a module function.
    * \param fictiveLimMethod    [in] The lim node whose data will be set.
    */
    void setFictiveMethodData(lim::asg::logical::Method& fictiveLimMethod);

   /**
    * \brief Converts data for lim::asg::logical::Attribute
    * \param _node    [in] The python node which is converted.
    * \param limAttribute [in] The lim node whose data will be set.
    */
    void setLimAttributeData(const python::asg::expression::Identifier& _node, lim::asg::logical::Attribute& limAttribute);

   /**
    * \brief Sets the component for the node.
    * \param limNodeId  [in] The node whose component data is set.
    */
    void setComponentData(NodeId limNodeId) const;

  /**
   * \brief Creates a fictive method for the given lim::asg::logical::Scope node.
   * \param limNode [in] The lime node.
   * \return        The lim method node.
   */
    lim::asg::logical::Method* createFictiveMethod(lim::asg::logical::Scope& limNode);

   /**
    * \brief Sets collected metrics and relations for lim::asg::logical::Method
    * \param limMethod  [in] The lim node whose data will be set.
    * \param methodInfo [in] The collected info.
    */
    void fillCollectedMethodData(lim::asg::logical::Method& limMethod, MethodInfo* methodInfo);

   /**
    * \brief Creates lim::asg::type::Type node
    */
    NodeId createType(NodeId pyType);

    void processDocstring(lim::asg::logical::Member& member, python::asg::base::Docstring* docstring);

    /**
     * \brief Returns the parent of a python node (it would be FunctionDef, ClassDef, Module)
     */
    NodeId getPythonParent(const python::asg::base::Base& _node);

   /**
    * \brief Increases the value of NOS if the statement is in a function.
    */
    void incNos(const python::asg::base::Positioned& _node);

   /**
    * \brief Increases the value of NOB if the statement is in a function.
    */
    void incNob(const python::asg::base::Base& _node);

   /**
    * \brief Returns true if the node is an If that is the FalseSubstatement of another If.
    */
    bool eligibleForNLE(const python::asg::statement::If& _node);

    /**
    * \brief Increases the current values of NL and NLE.
    */
    void incNL(bool NLE);

    /**
    * \brief Decreases the current values of NL and NLE.
    */
    void decNL(bool NLE);

    /**
    * \brief Create File node from the give SourcePosition.
    */
    lim::asg::physical::File& buildFileNode(const python::asg::Range& range);

  private:
    /** \internal \brief Map type for mapping python id to lim id. */
    typedef std::map<NodeId, NodeId> NodeIdMapType;

    /** \internal \brief Map type for mapping string table Key to lim NodeId. */
    typedef std::map<Key, NodeId> KeyNodeIdMapType;

    typedef std::map<NodeId, boost::icl::interval_set<unsigned> > NodeId2UnsignedIntervalSetMap;

    /** \internal \brief python factory */
    python::asg::Factory&     pyFact;
    /** \internal \brief lim factory */
    lim::asg::Factory&        limFact;
    /** \internal \brief lim origin */
    LimOrigin&                origin;

    /** \internal \brief For mapping from python id to lim id. */
    NodeIdMapType pythonId2limId;

    /** \internal \brief The id of the component.*/
    NodeId actualCompNodeId;

    /** \internal \brief Set for storing incomplete nodes */
    std::set<NodeId> incompleteNodes;

    /** \internal \brief For mapping from python string table key to lim id. */
    Key2IdMapType& pythonKey2LimId;

    /** \internal \brief Map for storing python type to lim type */
    std::map<NodeId, NodeId> PythonType2LimTypeMap;


    struct ScopeInfo {
      public:
        ScopeInfo() : node(NULL), limNode(NULL), fictiveMethodInfo(NULL), CLOC(0) {}
        virtual ~ScopeInfo() {}
        virtual MethodInfo* getMethodInfo() { return fictiveMethodInfo; }

        const python::asg::base::Base* node;
        lim::asg::base::Base* limNode;
        MethodInfo* fictiveMethodInfo;

        unsigned short CLOC;

      private:
        ScopeInfo(const ScopeInfo&);
        ScopeInfo& operator=(const ScopeInfo&);
    };

    struct MethodInfo : public ScopeInfo {
      public:
        MethodInfo() : NOS(0), NOB(1), NL(0), NLE(0), currentNL(0), currentNLE(0) {}
        virtual ~MethodInfo() {}
        virtual MethodInfo* getMethodInfo() { return this; }

        unsigned int NOS;
        unsigned int NOB;
        unsigned short NL;
        unsigned short NLE;

        unsigned short currentNL;
        unsigned short currentNLE;

        std::set<NodeId> calls;
        std::set<NodeId> accessesAttribute;
        std::set<NodeId> instantiates;
        std::set<NodeId> throws;
        std::set<NodeId> uses;
    };

    /** \internal \brief Stack for the current node info */
    std::vector<ScopeInfo*> infoStack;

    /** \internal \brief Map for storing the already built FileNodes */
    KeyNodeIdMapType pathFileNodeIdMap;

    /** \internal \brief  */
    NodeId2UnsignedIntervalSetMap fileNodeIdCommentLinesMap;
  };

}}
#endif //PYTHON2LIM_H
