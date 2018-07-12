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

#ifndef _JAVASCRIPT_LogicalExpressionWrapper_H_
#define _JAVASCRIPT_LogicalExpressionWrapper_H_

#include "javascript/inc/javascript.h"
#include <node.h>
#include <node_object_wrap.h>
#include "../Factory.h"

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {
  class Factory;

  class LogicalExpressionWrapper : public node::ObjectWrap {
    public:
      columbus::javascript::asg::expression::LogicalExpression* LogicalExpression;
      static void Init(v8::Handle<v8::Object> exports);
      LogicalExpressionWrapper(const LogicalExpressionWrapper&);
      LogicalExpressionWrapper(Factory* fact);
      virtual ~LogicalExpressionWrapper();
      static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);
      void wrap(const v8::FunctionCallbackInfo<v8::Value>& args){ this->Wrap(args.Holder()); }
      static v8::Persistent<v8::Function> constructor;
    private:
      static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

      static void setLeftArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setLeftArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setLeftAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setLeftAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setLeftBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setLeftCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setLeftClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setLeftConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setLeftFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setLeftIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setLeftBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setLeftNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setLeftNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setLeftRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setLeftStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setLeftLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setLeftMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setLeftMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setLeftNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setLeftObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setLeftSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setLeftTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setLeftTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setLeftThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setLeftUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setLeftUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setLeftYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setRightArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setRightArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setRightAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setRightAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setRightBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setRightCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setRightClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setRightConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setRightFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setRightIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setRightBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setRightNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setRightNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setRightRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setRightStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setRightLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setRightMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setRightMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setRightNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setRightObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setRightSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setRightTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setRightTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setRightThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setRightUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setRightUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setRightYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setOperator(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setPath(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setLine(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setCol(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setEndLine(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setEndCol(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setWideLine(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setWideCol(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setWideEndLine(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setWideEndCol(const v8::FunctionCallbackInfo<v8::Value>& args);
}; //end of LogicalExpressionWrapper

}}}}//end of namespaces
#endif