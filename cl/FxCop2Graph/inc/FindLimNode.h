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

#ifndef _FX2G_FLM_H_
#define _FX2G_FLM_H_

#include "FxCop2Graph.h"

class FindLimNode : columbus::lim::asg::Visitor
{
    public:
        FindLimNode(const std::string& mangleName, const columbus::lim::asg::Factory& limfact);
        virtual void visit(const columbus::lim::asg::logical::MethodGeneric& node, bool callVirtualBase);
        virtual void visit(const columbus::lim::asg::logical::Method& node, bool callVirtualBase);
        virtual void visit(const columbus::lim::asg::logical::Attribute& node, bool callVirtualBase);
        virtual void visit(const columbus::lim::asg::logical::Class& node, bool callVirtualBase);
        virtual void visit(const columbus::lim::asg::logical::ClassGeneric& node, bool callVirtualBase);
        virtual void visit(const columbus::lim::asg::logical::Package& node, bool callVirtualBase);
        const columbus::lim::asg::logical::Member* getLimNode();
    private:
        std::string mangleName;
        const columbus::lim::asg::logical::Member* foundNode;

        void set(const columbus::lim::asg::logical::Member&);
};

#endif