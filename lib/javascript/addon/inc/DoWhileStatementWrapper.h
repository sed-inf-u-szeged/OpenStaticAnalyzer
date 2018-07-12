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

#ifndef _JAVASCRIPT_DoWhileStatementWrapper_H_
#define _JAVASCRIPT_DoWhileStatementWrapper_H_

#include "javascript/inc/javascript.h"
#include <node.h>
#include <node_object_wrap.h>
#include "../Factory.h"

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {
  class Factory;

  class DoWhileStatementWrapper : public node::ObjectWrap {
    public:
      columbus::javascript::asg::statement::DoWhileStatement* DoWhileStatement;
      static void Init(v8::Handle<v8::Object> exports);
      DoWhileStatementWrapper(const DoWhileStatementWrapper&);
      DoWhileStatementWrapper(Factory* fact);
      virtual ~DoWhileStatementWrapper();
      static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);
      void wrap(const v8::FunctionCallbackInfo<v8::Value>& args){ this->Wrap(args.Holder()); }
      static v8::Persistent<v8::Function> constructor;
    private:
      static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

      static void setBodyClassDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyExportAllDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyExportDefaultDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyFunctionDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyVariableDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyBlockStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyBreakStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyContinueStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyDebuggerStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyEmptyStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyExpressionStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyForInStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyForOfStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyForStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyIfStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyLabeledStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyReturnStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodySwitchStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyThrowStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyTryStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyWhileStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyDoWhileStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyWithStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
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
}; //end of DoWhileStatementWrapper

}}}}//end of namespaces
#endif