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

#ifndef _JAVASCRIPT_SwitchCaseWrapper_H_
#define _JAVASCRIPT_SwitchCaseWrapper_H_

#include "javascript/inc/javascript.h"
#include <node.h>
#include <node_object_wrap.h>
#include "../Factory.h"

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {
  class Factory;

  class SwitchCaseWrapper : public node::ObjectWrap {
    public:
      columbus::javascript::asg::statement::SwitchCase* SwitchCase;
      static void Init(v8::Handle<v8::Object> exports);
      SwitchCaseWrapper(const SwitchCaseWrapper&);
      SwitchCaseWrapper(Factory* fact);
      virtual ~SwitchCaseWrapper();
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
      static void addConsequentClassDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addConsequentExportAllDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addConsequentExportDefaultDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addConsequentFunctionDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addConsequentVariableDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addConsequentBlockStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addConsequentBreakStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addConsequentContinueStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addConsequentDebuggerStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addConsequentEmptyStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addConsequentExpressionStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addConsequentForInStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addConsequentForOfStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addConsequentForStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addConsequentIfStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addConsequentLabeledStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addConsequentReturnStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addConsequentSwitchStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addConsequentThrowStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addConsequentTryStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addConsequentWhileStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addConsequentDoWhileStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addConsequentWithStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
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
}; //end of SwitchCaseWrapper

}}}}//end of namespaces
#endif