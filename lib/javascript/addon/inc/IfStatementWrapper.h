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

#ifndef _JAVASCRIPT_IfStatementWrapper_H_
#define _JAVASCRIPT_IfStatementWrapper_H_

#include "javascript/inc/javascript.h"
#include <node.h>
#include <node_object_wrap.h>
#include "../Factory.h"

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {
  class Factory;

  class IfStatementWrapper : public node::ObjectWrap {
    public:
      columbus::javascript::asg::statement::IfStatement* IfStatement;
      static void Init(v8::Handle<v8::Object> exports);
      IfStatementWrapper(const IfStatementWrapper&);
      IfStatementWrapper(Factory* fact);
      virtual ~IfStatementWrapper();
      static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);
      void wrap(const v8::FunctionCallbackInfo<v8::Value>& args){ this->Wrap(args.Holder()); }
      static v8::Persistent<v8::Function> constructor;
    private:
      static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

      static void setTestArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTestArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTestAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTestAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTestBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTestCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTestClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTestConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTestFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTestIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTestBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTestNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTestNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTestRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTestStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTestLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTestMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTestMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTestNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTestObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTestSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTestTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTestTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTestThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTestUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTestUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTestYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentClassDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentExportAllDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentExportDefaultDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentFunctionDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentVariableDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentBlockStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentBreakStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentContinueStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentDebuggerStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentEmptyStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentExpressionStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentForInStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentForOfStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentForStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentIfStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentLabeledStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentReturnStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentSwitchStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentThrowStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentTryStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentWhileStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentDoWhileStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentWithStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateClassDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateExportAllDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateExportDefaultDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateFunctionDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateVariableDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateBlockStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateBreakStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateContinueStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateDebuggerStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateEmptyStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateExpressionStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateForInStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateForOfStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateForStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateIfStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateLabeledStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateReturnStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateSwitchStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateThrowStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateTryStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateWhileStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateDoWhileStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateWithStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setPath(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setLine(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setCol(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setEndLine(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setEndCol(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setWideLine(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setWideCol(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setWideEndLine(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setWideEndCol(const v8::FunctionCallbackInfo<v8::Value>& args);
}; //end of IfStatementWrapper

}}}}//end of namespaces
#endif