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

#ifndef _JAVASCRIPT_YieldExpressionWrapper_H_
#define _JAVASCRIPT_YieldExpressionWrapper_H_

#include "javascript/inc/javascript.h"
#include <node.h>
#include <node_object_wrap.h>
#include "../Factory.h"

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {
  class Factory;

  class YieldExpressionWrapper : public node::ObjectWrap {
    public:
      columbus::javascript::asg::expression::YieldExpression* YieldExpression;
      static void Init(v8::Handle<v8::Object> exports);
      YieldExpressionWrapper(const YieldExpressionWrapper&);
      YieldExpressionWrapper(Factory* fact);
      virtual ~YieldExpressionWrapper();
      static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);
      void wrap(const v8::FunctionCallbackInfo<v8::Value>& args){ this->Wrap(args.Holder()); }
      static v8::Persistent<v8::Function> constructor;
    private:
      static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

      static void setArgumentArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setArgumentArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setArgumentAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setArgumentAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setArgumentBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setArgumentCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setArgumentClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setArgumentConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setArgumentFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setArgumentIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setArgumentBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setArgumentNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setArgumentNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setArgumentRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setArgumentStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setArgumentLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setArgumentMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setArgumentMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setArgumentNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setArgumentObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setArgumentSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setArgumentTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setArgumentTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setArgumentThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setArgumentUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setArgumentUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setArgumentYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setDelegate(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setPath(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setLine(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setCol(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setEndLine(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setEndCol(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setWideLine(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setWideCol(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setWideEndLine(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setWideEndCol(const v8::FunctionCallbackInfo<v8::Value>& args);
}; //end of YieldExpressionWrapper

}}}}//end of namespaces
#endif