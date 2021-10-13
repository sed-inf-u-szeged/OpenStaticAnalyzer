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

#ifndef LIM_AP
#define LIM_AP

#include "Conditions/CreateCondition.h"

#ifdef __linux__
  #define VISIBILITY_DEFAULT __attribute__((visibility("default")))
#else
  #define VISIBILITY_DEFAULT
#endif

namespace columbus { namespace lim { namespace patterns {

    class VISIBILITY_DEFAULT LIM2PatternsVisitor : public columbus::lim::asg::VisitorAbstractNodes {
    public:

        LIM2PatternsVisitor
        (
            asg::Factory& fact,
            graph::Graph& inGraph,
            std::vector<std::unique_ptr<conditions::Condition>> &_patterns,
            const std::set<std::string> &_whitelist, 
            const std::set<std::string> &_blacklist,
            columbus::rul::RulHandler& rl
        );

        virtual ~LIM2PatternsVisitor();

        /** Visit methods */
        virtual void visit(const columbus::lim::asg::base::Base&, bool callVirtualBase = true);
        virtual void visitEnd(const columbus::lim::asg::base::Base&, bool callVirtualBase = true);
    
    private:
        bool skipPattern(const std::string &patternName);
        void visitYaml(const columbus::lim::asg::base::Base&, conditions::NodeTypeCondition *condition);
        void visitPython(const columbus::lim::asg::base::Base&, conditions::PythonCondition *condition);

    protected:

        /** \brief The lim factory */
        asg::Factory& factory;
        /** \brief The input graph */
        columbus::graph::Graph& inGraph;
        /** \brief The set for patterns */
        std::vector<std::unique_ptr<conditions::Condition>> &patterns;
        /** \brief The name of the pattern we want to test */
        const std::set<std::string>& whitelist, &blacklist;
        /** \brief The rulhandler */
        columbus::rul::RulHandler& rl;
        /** \brief Reverse edges of lim asg */
        const asg::ReverseEdges& revEdges;

        bool _moduleFlag;
        std::unique_ptr<pybind11::module> pythonBindingModule;
    };

    void lim2Patterns(const std::string& limFileName, const std::vector<std::string> &patternsFileName, const std::set<std::string>& whitelist, const std::set<std::string>& blacklist, const std::string& outputFileName, const std::string& patternsFolder, const std::string& metricFileName, const std::string &graphFileName, bool dumpXML, const std::string &rulDumpDir);
    void loadFilter(lim::asg::Factory& fact, const std::string& file);
    
} } }


#endif
