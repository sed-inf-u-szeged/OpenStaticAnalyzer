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

#ifndef _JAVASCRIPT_SequenceExpressionWrapper_H_
#define _JAVASCRIPT_SequenceExpressionWrapper_H_

#include "javascript/inc/javascript.h"
#include <node.h>
#include <node_object_wrap.h>
#include "../Factory.h"

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {
  class Factory;

  class SequenceExpressionWrapper : public node::ObjectWrap {
    public:
      columbus::javascript::asg::expression::SequenceExpression* SequenceExpression;
      static void Init(v8::Handle<v8::Object> exports);
      SequenceExpressionWrapper(const SequenceExpressionWrapper&);
      SequenceExpressionWrapper(Factory* fact);
      virtual ~SequenceExpressionWrapper();
      static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);
      void wrap(const v8::FunctionCallbackInfo<v8::Value>& args){ this->Wrap(args.Holder()); }
      static v8::Persistent<v8::Function> constructor;
    private:
      static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

      static void addExpressionsArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addExpressionsArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addExpressionsAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addExpressionsAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addExpressionsBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addExpressionsCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addExpressionsClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addExpressionsConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addExpressionsFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addExpressionsIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addExpressionsBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addExpressionsNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addExpressionsNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addExpressionsRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addExpressionsStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addExpressionsLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addExpressionsMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addExpressionsMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addExpressionsNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addExpressionsObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addExpressionsSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addExpressionsTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addExpressionsTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addExpressionsThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addExpressionsUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addExpressionsUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addExpressionsYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
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
}; //end of SequenceExpressionWrapper

}}}}//end of namespaces
#endif