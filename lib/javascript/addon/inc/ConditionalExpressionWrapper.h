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

#ifndef _JAVASCRIPT_ConditionalExpressionWrapper_H_
#define _JAVASCRIPT_ConditionalExpressionWrapper_H_

#include "javascript/inc/javascript.h"
#include <node.h>
#include <node_object_wrap.h>
#include "../Factory.h"

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {
  class Factory;

  class ConditionalExpressionWrapper : public node::ObjectWrap {
    public:
      columbus::javascript::asg::expression::ConditionalExpression* ConditionalExpression;
      static void Init(v8::Handle<v8::Object> exports);
      ConditionalExpressionWrapper(const ConditionalExpressionWrapper&);
      ConditionalExpressionWrapper(Factory* fact);
      virtual ~ConditionalExpressionWrapper();
      static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);
      void wrap(const v8::FunctionCallbackInfo<v8::Value>& args){ this->Wrap(args.Holder()); }
      static v8::Persistent<v8::Function> constructor;
    private:
      static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

      static void setAlternateArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAlternateYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setConsequentYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
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
}; //end of ConditionalExpressionWrapper

}}}}//end of namespaces
#endif