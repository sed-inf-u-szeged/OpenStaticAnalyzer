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

#ifndef _DCF_CSNODEEV_H_
#define _DCF_CSNODEEV_H_

#ifdef SCHEMA_CSHARP

#include "../common.h"
#include "NodeEmbeddednessVisitorBase.h"
#include <csharp/inc/csharp.h>

namespace columbus {

    class CSNodeEmbeddednessVisitorBase : public NodeEmbeddednessVisitorBase {
    public:
        CSNodeEmbeddednessVisitorBase(ConectedEdgesMap& mapTofill, const columbus::dcf::DuplicatedCodeMiner& dcf) :
            NodeEmbeddednessVisitorBase(mapTofill, dcf) {}
        virtual ~CSNodeEmbeddednessVisitorBase(){}
    protected:

        void putNode(const columbus::csharp::asg::base::Positioned& n1, const columbus::csharp::asg::base::Positioned& n2, bool unique);

        void visit(const LANGUAGE_NAMESPACE::expression::IdentifierNameSyntax& node, bool b) {
            NodeEmbeddednessVisitorBase::visit(node, b);
            LANGUAGE_NAMESPACE::base::Positioned* dec = node.getDeclaration();
            if (dec) {
                putNode(node, *dec, false);
            }
            dec = node.getOriginalDefinition();
            if (dec) {
                putNode(node, *dec, false);
            }
            if (!node.getAccessorCallIsEmpty()) {
                LANGUAGE_NAMESPACE::ListIterator<LANGUAGE_NAMESPACE::structure::AccessorDeclarationSyntax> it = node.getAccessorCallListIteratorBegin();
                while (it != node.getAccessorCallListIteratorEnd()) {
                    putNode(*it, node, false);
                    ++it;
                }
            }
        }

        void visit(const LANGUAGE_NAMESPACE::expression::TypeSyntax& node, bool b) {
            NodeEmbeddednessVisitorBase::visit(node, b);
            LANGUAGE_NAMESPACE::base::Positioned* originDef = node.getOriginalDefinition();
            if (originDef) {
                putNode(*originDef, node, true);
            }
        }

        void visit(const LANGUAGE_NAMESPACE::expression::CastExpressionSyntax& node, bool b) {
            NodeEmbeddednessVisitorBase::visit(node, b);
            LANGUAGE_NAMESPACE::base::Positioned* convOpCall = node.getConversionOperatorCall();
            if (convOpCall) {
                putNode(node, *convOpCall, false);
            }
        }

        void visit(const LANGUAGE_NAMESPACE::expression::BinaryExpressionSyntax& node, bool b) {
            NodeEmbeddednessVisitorBase::visit(node, b);
            LANGUAGE_NAMESPACE::base::Positioned* ovOpCall = node.getOverloadedOperatorCall();
            if (ovOpCall) {
                putNode(*ovOpCall, node, false);
            }
        }

        void visit(const LANGUAGE_NAMESPACE::expression::AssignmentExpressionSyntax& node, bool b) {
            NodeEmbeddednessVisitorBase::visit(node, b);
            LANGUAGE_NAMESPACE::base::Positioned* ovOpCall = node.getOverloadedOperatorCall();
            if (ovOpCall) {
                putNode(*ovOpCall, node, false);
            }
            LANGUAGE_NAMESPACE::base::Positioned* eventAccessorCall = node.getEventAccessorCall();
            if (eventAccessorCall) {
                putNode(*eventAccessorCall, node, false);
            }
        }

        void visit(const LANGUAGE_NAMESPACE::expression::PrefixUnaryExpressionSyntax& node, bool b) {
            NodeEmbeddednessVisitorBase::visit(node, b);
            LANGUAGE_NAMESPACE::base::Positioned* ovOpCall = node.getOverloadedOperatorCall();
            if (ovOpCall) {
                putNode(*ovOpCall, node, false);
            }
        }

        void visit(const LANGUAGE_NAMESPACE::expression::PostfixUnaryExpressionSyntax& node, bool b) {
            NodeEmbeddednessVisitorBase::visit(node, b);
            LANGUAGE_NAMESPACE::base::Positioned* ovOpCall = node.getOverloadedOperatorCall();
            if (ovOpCall) {
                putNode(node, *ovOpCall, false);
            }
        }

        void visit(const LANGUAGE_NAMESPACE::expression::InvocationExpressionSyntax& node, bool b) {
            NodeEmbeddednessVisitorBase::visit(node, b);
            LANGUAGE_NAMESPACE::base::Positioned* methodCall = node.getMethodCall();
            if (methodCall) {
                putNode(*methodCall, node, false);
            }
        }

        void visit(const LANGUAGE_NAMESPACE::expression::ObjectCreationExpressionSyntax& node, bool b) {
            NodeEmbeddednessVisitorBase::visit(node, b);
            LANGUAGE_NAMESPACE::base::Positioned* methodCall = node.getConstructorCall();
            if (methodCall) {
                putNode(node, *methodCall, false);
            }
        }

        void visit(const LANGUAGE_NAMESPACE::structure::ConstructorInitializerSyntax& node, bool b) {
            NodeEmbeddednessVisitorBase::visit(node, b);
            LANGUAGE_NAMESPACE::base::Positioned* methodCall = node.getConstructorCall();
            if (methodCall) {
                putNode(*methodCall, node, false);
            }
        }

        void visit(const LANGUAGE_NAMESPACE::expression::ElementAccessExpressionSyntax& node, bool b) {
            NodeEmbeddednessVisitorBase::visit(node, b);
            if (!node.getAccessorCallIsEmpty()) {
                LANGUAGE_NAMESPACE::ListIterator<LANGUAGE_NAMESPACE::structure::AccessorDeclarationSyntax> it = node.getAccessorCallListIteratorBegin();
                while (it != node.getAccessorCallListIteratorEnd()) {
                    putNode(*it, node, false);
                    ++it;
                }
            }
        }
    };
}
#define NODE_EMBEDDEDNESS_VISITOR CSNodeEmbeddednessVisitorBase
#endif // SCHEMA_CSHARP

#endif // _DCF_CSNODEEV_H_
