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

#ifndef _PYTHON_Common_H_
#define _PYTHON_Common_H_

#include "python/inc/python.h"

/**
* \file Common.h
* \brief Contains declaration of Common namespace.
*/

namespace columbus { namespace python { namespace asg {
  typedef unsigned int NodeHashType;
  /**
  * \brief Common contains general graph algorithms and common functions
  */
  namespace Common {
      /**
      * \brief Decides whether the node is base::Comment or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is base::Comment.
      */
      bool getIsComment(const base::Base& node);

      /**
      * \brief Decides whether the node is base::Docstring or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is base::Docstring.
      */
      bool getIsDocstring(const base::Base& node);

      /**
      * \brief Decides whether the node is base::Named or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is base::Named.
      */
      bool getIsNamed(const base::Base& node);

      /**
      * \brief Decides whether the node is base::Positioned or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is base::Positioned.
      */
      bool getIsPositioned(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::ArgumentList or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::ArgumentList.
      */
      bool getIsArgumentList(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::AttributeRef or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::AttributeRef.
      */
      bool getIsAttributeRef(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::Binary or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::Binary.
      */
      bool getIsBinary(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::BinaryArithmetic or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::BinaryArithmetic.
      */
      bool getIsBinaryArithmetic(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::BinaryLogical or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::BinaryLogical.
      */
      bool getIsBinaryLogical(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::Call or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::Call.
      */
      bool getIsCall(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::DictComp or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::DictComp.
      */
      bool getIsDictComp(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::Dictionary or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::Dictionary.
      */
      bool getIsDictionary(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::Ellipsis or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::Ellipsis.
      */
      bool getIsEllipsis(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::Expression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::Expression.
      */
      bool getIsExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::ExpressionList or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::ExpressionList.
      */
      bool getIsExpressionList(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::ExtSlice or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::ExtSlice.
      */
      bool getIsExtSlice(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::FloatNumber or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::FloatNumber.
      */
      bool getIsFloatNumber(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::Generator or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::Generator.
      */
      bool getIsGenerator(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::GeneratorExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::GeneratorExpression.
      */
      bool getIsGeneratorExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::Identifier or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::Identifier.
      */
      bool getIsIdentifier(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::IfExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::IfExpression.
      */
      bool getIsIfExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::ImagNumber or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::ImagNumber.
      */
      bool getIsImagNumber(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::Index or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::Index.
      */
      bool getIsIndex(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::IntegerLiteral or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::IntegerLiteral.
      */
      bool getIsIntegerLiteral(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::KeyValue or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::KeyValue.
      */
      bool getIsKeyValue(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::Keyword or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::Keyword.
      */
      bool getIsKeyword(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::Lambda or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::Lambda.
      */
      bool getIsLambda(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::List or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::List.
      */
      bool getIsList(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::ListComp or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::ListComp.
      */
      bool getIsListComp(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::Literal or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::Literal.
      */
      bool getIsLiteral(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::LongInteger or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::LongInteger.
      */
      bool getIsLongInteger(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::Set or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::Set.
      */
      bool getIsSet(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::SetComp or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::SetComp.
      */
      bool getIsSetComp(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::Slice or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::Slice.
      */
      bool getIsSlice(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::Slicing or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::Slicing.
      */
      bool getIsSlicing(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::StringConversion or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::StringConversion.
      */
      bool getIsStringConversion(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::StringLiteral or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::StringLiteral.
      */
      bool getIsStringLiteral(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::Subscription or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::Subscription.
      */
      bool getIsSubscription(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::Unary or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::Unary.
      */
      bool getIsUnary(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::UnaryOperation or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::UnaryOperation.
      */
      bool getIsUnaryOperation(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::YieldExpression or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::YieldExpression.
      */
      bool getIsYieldExpression(const base::Base& node);

      /**
      * \brief Decides whether the node is module::Module or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is module::Module.
      */
      bool getIsModule(const base::Base& node);

      /**
      * \brief Decides whether the node is module::Object or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is module::Object.
      */
      bool getIsObject(const base::Base& node);

      /**
      * \brief Decides whether the node is module::Package or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is module::Package.
      */
      bool getIsPackage(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::Alias or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::Alias.
      */
      bool getIsAlias(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::Assert or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::Assert.
      */
      bool getIsAssert(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::Assign or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::Assign.
      */
      bool getIsAssign(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::AugAssign or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::AugAssign.
      */
      bool getIsAugAssign(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::BaseSpecifier or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::BaseSpecifier.
      */
      bool getIsBaseSpecifier(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::Break or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::Break.
      */
      bool getIsBreak(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::ClassDef or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::ClassDef.
      */
      bool getIsClassDef(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::CompoundStatement or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::CompoundStatement.
      */
      bool getIsCompoundStatement(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::Continue or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::Continue.
      */
      bool getIsContinue(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::Delete or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::Delete.
      */
      bool getIsDelete(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::Exec or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::Exec.
      */
      bool getIsExec(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::For or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::For.
      */
      bool getIsFor(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::FunctionDef or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::FunctionDef.
      */
      bool getIsFunctionDef(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::Global or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::Global.
      */
      bool getIsGlobal(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::Handler or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::Handler.
      */
      bool getIsHandler(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::If or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::If.
      */
      bool getIsIf(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::ImportFrom or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::ImportFrom.
      */
      bool getIsImportFrom(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::ImportStatement or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::ImportStatement.
      */
      bool getIsImportStatement(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::Iteration or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::Iteration.
      */
      bool getIsIteration(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::Parameter or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::Parameter.
      */
      bool getIsParameter(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::Pass or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::Pass.
      */
      bool getIsPass(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::Print or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::Print.
      */
      bool getIsPrint(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::Raise or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::Raise.
      */
      bool getIsRaise(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::Return or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::Return.
      */
      bool getIsReturn(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::SimpleStatement or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::SimpleStatement.
      */
      bool getIsSimpleStatement(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::Statement or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::Statement.
      */
      bool getIsStatement(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::Suite or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::Suite.
      */
      bool getIsSuite(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::TargetList or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::TargetList.
      */
      bool getIsTargetList(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::Try or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::Try.
      */
      bool getIsTry(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::TryExcept or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::TryExcept.
      */
      bool getIsTryExcept(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::TryFinal or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::TryFinal.
      */
      bool getIsTryFinal(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::While or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::While.
      */
      bool getIsWhile(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::With or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::With.
      */
      bool getIsWith(const base::Base& node);

      /**
      * \brief Decides whether the node is type::DictType or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::DictType.
      */
      bool getIsDictType(const base::Base& node);

      /**
      * \brief Decides whether the node is type::ReferenceType or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::ReferenceType.
      */
      bool getIsReferenceType(const base::Base& node);

      /**
      * \brief Decides whether the node is type::SequenceType or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::SequenceType.
      */
      bool getIsSequenceType(const base::Base& node);

      /**
      * \brief Decides whether the node is type::SimpleType or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::SimpleType.
      */
      bool getIsSimpleType(const base::Base& node);

      /**
      * \brief Decides whether the node is type::Type or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::Type.
      */
      bool getIsType(const base::Base& node);

      /**
      * \brief Decides whether the node is AP spec node or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is AP spec node.
      */
      bool getIsAPSpecNode(const base::Base& node);

      /**
      * \brief Decides whether the 'base' is one of the base kinds (transitive) of 'what'.
      * \param what [in] The examined node kind.
      * \param base [in] The base node kind.
      * \return Returns true if 'base' is a base kind of 'what'.
      */
      bool getIsBaseClassKind(NodeKind what, NodeKind base);

      /**
      * \brief Decides whether the node is composite or not.
      * \param node [in] The node which is being examined.
      * \return Returns true if the node is composite.
      */
      bool getIsComposite(const base::Base& node);

      /**
      * \brief Decides whether the node is composite or not.
      * \param node [in] The node which is being examined.
      * \return Returns true if the node is not composite.
      */
      bool getIsNotComposite(const base::Base& node);

      /**
      * \brief Gives back the string representation of the NodeId.
      * \param nodeId [in] The NodeId.
      * \return The string representation of the nodeId given in the parameter.
      */
      const std::string toString(NodeId nodeId);

      /**
      * \brief Gives back the string representation of the AssignmentKind kind.
      * \param kind            [in] The AssignmentKind.
      * \throw PythonException If the kind is not "valid" PythonException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(AssignmentKind kind);

      /**
      * \brief Gives back the string representation of the BinaryArithmeticKind kind.
      * \param kind            [in] The BinaryArithmeticKind.
      * \throw PythonException If the kind is not "valid" PythonException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(BinaryArithmeticKind kind);

      /**
      * \brief Gives back the string representation of the BinaryLogicalKind kind.
      * \param kind            [in] The BinaryLogicalKind.
      * \throw PythonException If the kind is not "valid" PythonException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(BinaryLogicalKind kind);

      /**
      * \brief Gives back the string representation of the OriginKind kind.
      * \param kind            [in] The OriginKind.
      * \throw PythonException If the kind is not "valid" PythonException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(OriginKind kind);

      /**
      * \brief Gives back the string representation of the ParameterKind kind.
      * \param kind            [in] The ParameterKind.
      * \throw PythonException If the kind is not "valid" PythonException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(ParameterKind kind);

      /**
      * \brief Gives back the string representation of the SequenceTypeKind kind.
      * \param kind            [in] The SequenceTypeKind.
      * \throw PythonException If the kind is not "valid" PythonException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(SequenceTypeKind kind);

      /**
      * \brief Gives back the string representation of the SimpleTypeKind kind.
      * \param kind            [in] The SimpleTypeKind.
      * \throw PythonException If the kind is not "valid" PythonException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(SimpleTypeKind kind);

      /**
      * \brief Gives back the string representation of the UnaryKind kind.
      * \param kind            [in] The UnaryKind.
      * \throw PythonException If the kind is not "valid" PythonException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(UnaryKind kind);

      /**
      * \brief Gives back the string representation of the NodeKind kind.
      * \param kind            [in] The NodeKind.
      * \throw PythonException If the kind is not "valid" PythonException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(NodeKind kind);

      /**
      * \brief Gives back the string representation of the EdgeKind kind.
      * \param kind            [in] The EdgeKind.
      * \throw PythonException If the kind is not "valid" PythonException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(EdgeKind kind);

      /**
      * \brief Returns true if the node exists and is not filtered out.
      * \param id [in] The examined node ID.
      * \return True if the node exists and is not filtered out.
      */
      bool getIsValid(NodeId id);

      /**
      * \brief Minimum of same type node similarity.
      */
      extern double SimilarityMinimum;

      /**
      * \brief Returns the minimum similarity value of same type nodes.
      * \return Minimum of same type node similarity.
      */
      double getSimilarityMinimum();

      /**
      * \brief Sets the minimum similarity value of same type nodes.
      * \param value [in] Minimum of same type node similarity.
      */
      void setSimilarityMinimum(double value);

      /**
      * \brief Minimum similarity for string type attributes.
      */
      extern double SimilarityMinForStrings;

      /**
      * \brief Returns the minimum similarity value for string type attributes.
      * \return Minimum similarity for string type attributes.
      */
      double getSimilarityMinForStrings();

      /**
      * \brief Sets the minimum similarity value for string type attributes.
      * \param value [in] Minimum similarity for string type attributes.
      */
      void setSimilarityMinForStrings(double value);

      /**
      * \brief Minimum similarity for AP spec edges.
      */
      extern double SimilarityMinForEdges;

      /**
      * \brief Returns the minimum similarity value for AP spec edges.
      * \return Minimum similarity for AP spec edges.
      */
      double getSimilarityMinForEdges();

      /**
      * \brief Sets the minimum similarity value for AP spec edges.
      * \param value [in] Minimum similarity for AP spec edges.
      */
      void setSimilarityMinForEdges(double value);

      const std::string getUniqueName(const base::Base& node);
      const std::string getQualifiedName(const base::Base& node);
      char* getUniqueNameForComponent(char* compName);
      base::Base* getScopeParent(const base::Base& node);
       bool getIsMemberNode(const base::Base& node);
  } // Common


}}}
#endif

