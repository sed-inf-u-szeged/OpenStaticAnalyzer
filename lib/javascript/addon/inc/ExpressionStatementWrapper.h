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

#ifndef _JAVASCRIPT_ExpressionStatementWrapper_H_
#define _JAVASCRIPT_ExpressionStatementWrapper_H_

#include "javascript/inc/javascript.h"
#include <node.h>
#include <node_object_wrap.h>
#include "../Factory.h"

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {
  class Factory;

  class ExpressionStatementWrapper : public node::ObjectWrap {
    public:
      columbus::javascript::asg::statement::ExpressionStatement* ExpressionStatement;
      static void Init(v8::Handle<v8::Object> exports);
      ExpressionStatementWrapper(const ExpressionStatementWrapper&);
      ExpressionStatementWrapper(Factory* fact);
      virtual ~ExpressionStatementWrapper();
      static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);
      void wrap(const v8::FunctionCallbackInfo<v8::Value>& args){ this->Wrap(args.Holder()); }
      static v8::Persistent<v8::Function> constructor;
    private:
      static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

      static void setExpressionArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setExpressionArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setExpressionAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setExpressionAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setExpressionBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setExpressionCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setExpressionClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setExpressionConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setExpressionFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setExpressionIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setExpressionBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setExpressionNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setExpressionNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setExpressionRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setExpressionStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setExpressionLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setExpressionMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setExpressionMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setExpressionNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setExpressionObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setExpressionSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setExpressionTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setExpressionTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setExpressionThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setExpressionUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setExpressionUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setExpressionYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
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
}; //end of ExpressionStatementWrapper

}}}}//end of namespaces
#endif