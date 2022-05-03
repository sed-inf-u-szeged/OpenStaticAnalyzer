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

#ifndef DCF_CSHARP_NAMED_VISITOR_H
#define DCF_CSHARP_NAMED_VISITOR_H

#ifdef SCHEMA_CSHARP

class CSharpNamedVisitor : public NamedVisitor {
public:
    virtual void visit(const columbus::LANGUAGE_NAMESPACE::base::Base& node, bool callVirtualBase = true) {
        //if (node.getIsCompilerGenerated()) return;
        NamedVisitor::visit(node, callVirtualBase);
    }

    virtual void visitEnd(const columbus::LANGUAGE_NAMESPACE::base::Base& node, bool callVirtualBase = true) {
        //if (node.getIsCompilerGenerated()) return;
        NamedVisitor::visitEnd(node, callVirtualBase);
    }

    virtual void visit(const columbus::LANGUAGE_NAMESPACE::expression::InvocationExpressionSyntax& node, bool callVirtualBase = true) {
        NamedVisitor::visit(node, callVirtualBase);
        if (node.getPosition().getFileNameKey() != 0) {
            const columbus::LANGUAGE_NAMESPACE::structure::MethodDeclarationSyntax* refersTo = node.getMethodCall();
            if (refersTo && refersTo->getPosition().getFileNameKey() != 0) {
                repr += std::string("(") + refersTo->getIdentifier();
            }
        }
    }

    virtual void visitEnd(const columbus::LANGUAGE_NAMESPACE::expression::InvocationExpressionSyntax& node, bool callVirtualBase = true) {
        NamedVisitor::visit(node);
        if (node.getPosition().getFileNameKey() != 0) {
            const columbus::LANGUAGE_NAMESPACE::structure::MethodDeclarationSyntax* refersTo = node.getMethodCall();
            if (refersTo && refersTo->getPosition().getFileNameKey() != 0) {
                repr += std::string(")");
            }
        }
        NamedVisitor::visitEnd(node, callVirtualBase);
    }

    virtual void visit(const columbus::LANGUAGE_NAMESPACE::expression::CastExpressionSyntax& node, bool callVirtualBase = true) {
        NamedVisitor::visit(node, callVirtualBase);
        if (node.getPosition().getFileNameKey() != 0) {
            const columbus::LANGUAGE_NAMESPACE::structure::ConversionOperatorDeclarationSyntax* refersTo = node.getConversionOperatorCall();
            if (refersTo && refersTo->getPosition().getFileNameKey() != 0) {
                repr += std::string("(cast operator ") + ((columbus::LANGUAGE_NAMESPACE::structure::BaseTypeDeclarationSyntax*)refersTo->getParent())->getIdentifier() + std::string("()");
            }
        }
    }

    virtual void visitEnd(const columbus::LANGUAGE_NAMESPACE::expression::CastExpressionSyntax& node, bool callVirtualBase = true) {
        NamedVisitor::visit(node, callVirtualBase);
        if (node.getPosition().getFileNameKey() != 0) {
            const columbus::LANGUAGE_NAMESPACE::structure::ConversionOperatorDeclarationSyntax* refersTo = node.getConversionOperatorCall();
            if (refersTo && refersTo->getPosition().getFileNameKey() != 0) {
                repr += std::string(")");
            }
        }
        NamedVisitor::visitEnd(node, callVirtualBase);
    }

    virtual void visit(const columbus::LANGUAGE_NAMESPACE::expression::ElementAccessExpressionSyntax& node, bool callVirtualBase = true) {
        NamedVisitor::visit(node, callVirtualBase);
        if (node.getPosition().getFileNameKey() != 0) {
            if (!node.getAccessorCallIsEmpty()){
                columbus::LANGUAGE_NAMESPACE::ListIterator<columbus::LANGUAGE_NAMESPACE::structure::AccessorDeclarationSyntax> it = node.getAccessorCallListIteratorBegin();
                while (it != node.getAccessorCallListIteratorEnd()) {
                    if (it->getPosition().getFileNameKey() != 0) {
                        repr += std::string("(") + (*it).getIdentifier();
                    }
                    ++it;
                }
            }
        }
    }

    virtual void visitEnd(const columbus::LANGUAGE_NAMESPACE::expression::ElementAccessExpressionSyntax& node, bool callVirtualBase = true) {
        NamedVisitor::visit(node, callVirtualBase);
        if (node.getPosition().getFileNameKey() != 0) {
            if (!node.getAccessorCallIsEmpty()){
                columbus::LANGUAGE_NAMESPACE::ListIterator<columbus::LANGUAGE_NAMESPACE::structure::AccessorDeclarationSyntax> it = node.getAccessorCallListIteratorBegin();
                while (it != node.getAccessorCallListIteratorEnd()) {
                    if (it->getPosition().getFileNameKey() != 0) {
                        repr += std::string(")");
                    }
                    ++it;
                }
            }
        }
        NamedVisitor::visitEnd(node, callVirtualBase);
    }

    virtual void visit(const columbus::LANGUAGE_NAMESPACE::expression::ObjectCreationExpressionSyntax& node, bool callVirtualBase = true) {
        NamedVisitor::visit(node, callVirtualBase);
        if (node.getPosition().getFileNameKey() != 0) {
            columbus::LANGUAGE_NAMESPACE::structure::ConstructorDeclarationSyntax* refersTo = node.getConstructorCall();
            if (refersTo && refersTo->getPosition().getFileNameKey() != 0) {
                repr += std::string("(") + refersTo->getIdentifier();
            }
        }
    }

    virtual void visitEnd(const columbus::LANGUAGE_NAMESPACE::expression::ObjectCreationExpressionSyntax& node, bool callVirtualBase = true) {
        NamedVisitor::visit(node, callVirtualBase);
        if (node.getPosition().getFileNameKey() != 0) {
            columbus::LANGUAGE_NAMESPACE::structure::ConstructorDeclarationSyntax* refersTo = node.getConstructorCall();
            if (refersTo && refersTo->getPosition().getFileNameKey() != 0) {
                repr += std::string(")");
            }
        }
        NamedVisitor::visitEnd(node, callVirtualBase);
    }

    virtual void visit(const columbus::LANGUAGE_NAMESPACE::structure::ConstructorInitializerSyntax& node, bool callVirtualBase = true) {
        NamedVisitor::visit(node, callVirtualBase);
        if (node.getPosition().getFileNameKey() != 0) {
            columbus::LANGUAGE_NAMESPACE::structure::ConstructorDeclarationSyntax* refersTo = node.getConstructorCall();
            if (refersTo && refersTo->getPosition().getFileNameKey() != 0) {
                repr += std::string("(") + refersTo->getIdentifier();
            }
        }
    }

    virtual void visitEnd(const columbus::LANGUAGE_NAMESPACE::structure::ConstructorInitializerSyntax& node, bool callVirtualBase = true) {
        NamedVisitor::visit(node, callVirtualBase);
        if (node.getPosition().getFileNameKey() != 0) {
            columbus::LANGUAGE_NAMESPACE::structure::ConstructorDeclarationSyntax* refersTo = node.getConstructorCall();
            if (refersTo && refersTo->getPosition().getFileNameKey() != 0) {
                repr += std::string(")");
            }
        }
        NamedVisitor::visitEnd(node, callVirtualBase);
    }

    virtual void visit(const columbus::LANGUAGE_NAMESPACE::expression::IdentifierNameSyntax& node, bool callVirtualBase = true) {
        NamedVisitor::visit(node, callVirtualBase);
        using namespace columbus::LANGUAGE_NAMESPACE;
        if (node.getPosition().getFileNameKey() != 0) {
            base::Positioned* dec = node.getDeclaration();
            if (dec) {
                if (dec->getNodeKind() == ndkCatchDeclarationSyntax) {
                    structure::CatchDeclarationSyntax* catchDec = static_cast<structure::CatchDeclarationSyntax*>(dec);
                    expression::TypeSyntax* tpyeSyntax = catchDec->getType();
                    if (tpyeSyntax) {
                        if (Common::getIsNameSyntax(*tpyeSyntax)) {
                            repr += std::string("(") + QualifiedNameSyntaxParser(static_cast<expression::NameSyntax*>(tpyeSyntax), "");
                        }
                    }
                } else {
                    repr += std::string("(") + AlgorithmCommon::getName(*dec);
                }
            }

            dec = node.getOriginalDefinition();
            if (dec) {
                repr += std::string("(") + AlgorithmCommon::getName(*dec);
            }
            if (!node.getAccessorCallIsEmpty()) {
                columbus::LANGUAGE_NAMESPACE::ListIterator<columbus::LANGUAGE_NAMESPACE::structure::AccessorDeclarationSyntax> it = node.getAccessorCallListIteratorBegin();
                while (it != node.getAccessorCallListIteratorEnd()) {
                    if (it->getPosition().getFileNameKey() != 0) {
                        repr += std::string("(") + (*it).getIdentifier();
                    }
                    ++it;
                }
            }
        }
    }

    virtual void visitEnd(const columbus::LANGUAGE_NAMESPACE::expression::IdentifierNameSyntax& node, bool callVirtualBase = true) {
        NamedVisitor::visit(node, callVirtualBase);
        if (node.getPosition().getFileNameKey() != 0) {
            columbus::LANGUAGE_NAMESPACE::base::Positioned* dec = node.getDeclaration();
            if (dec) {
                repr += std::string(")");
            }
            dec = node.getOriginalDefinition();
            if (dec) {
                repr += std::string(")");
            }
            if (!node.getAccessorCallIsEmpty()) {
                columbus::LANGUAGE_NAMESPACE::ListIterator<columbus::LANGUAGE_NAMESPACE::structure::AccessorDeclarationSyntax> it = node.getAccessorCallListIteratorBegin();
                while (it != node.getAccessorCallListIteratorEnd()) {
                    if (it->getPosition().getFileNameKey() != 0) {
                        repr += std::string(")");
                    }
                    ++it;
                }
            }
        }
    }

    virtual void visit(const columbus::LANGUAGE_NAMESPACE::expression::BinaryExpressionSyntax& node, bool callVirtualBase = true) {
        NamedVisitor::visit(node, callVirtualBase);
        if (node.getPosition().getFileNameKey() != 0) {
            columbus::LANGUAGE_NAMESPACE::structure::OperatorDeclarationSyntax* refersTo = node.getOverloadedOperatorCall();
            if (refersTo && refersTo->getPosition().getFileNameKey() != 0) {
                repr += std::string("(operator ") + ((columbus::LANGUAGE_NAMESPACE::structure::BaseTypeDeclarationSyntax*)refersTo->getParent())->getIdentifier() + std::string("()");
            }
        }
    }

    virtual void visitEnd(const columbus::LANGUAGE_NAMESPACE::expression::BinaryExpressionSyntax& node, bool callVirtualBase = true) {
        NamedVisitor::visit(node, callVirtualBase);
        if (node.getPosition().getFileNameKey() != 0) {
            const columbus::LANGUAGE_NAMESPACE::structure::OperatorDeclarationSyntax* refersTo = node.getOverloadedOperatorCall();
            if (refersTo && refersTo->getPosition().getFileNameKey() != 0) {
                repr += std::string(")");
            }
        }
        NamedVisitor::visitEnd(node, callVirtualBase);
    }

    virtual void visit(const columbus::LANGUAGE_NAMESPACE::expression::LiteralExpressionSyntax& node, bool callVirtualBase = true) {
        NamedVisitor::visit(node, callVirtualBase);
        if (node.getPosition().getFileNameKey() != 0) {
            repr += std::string("(") + node.getToken();
        }
    }

    virtual void visitEnd(const columbus::LANGUAGE_NAMESPACE::expression::LiteralExpressionSyntax& node, bool callVirtualBase = true) {
        NamedVisitor::visit(node, callVirtualBase);
        if (node.getPosition().getFileNameKey() != 0) {
            repr += std::string(")");
        }
        NamedVisitor::visitEnd(node, callVirtualBase);
    }
};

#endif
#endif