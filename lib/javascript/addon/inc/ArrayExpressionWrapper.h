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

#ifndef _JAVASCRIPT_ArrayExpressionWrapper_H_
#define _JAVASCRIPT_ArrayExpressionWrapper_H_

#include "javascript/inc/javascript.h"
#include <node.h>
#include <node_object_wrap.h>
#include "../Factory.h"

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {
  class Factory;

  class ArrayExpressionWrapper : public node::ObjectWrap {
    public:
      columbus::javascript::asg::expression::ArrayExpression* ArrayExpression;
      static void Init(v8::Handle<v8::Object> exports);
      ArrayExpressionWrapper(const ArrayExpressionWrapper&);
      ArrayExpressionWrapper(Factory* fact);
      virtual ~ArrayExpressionWrapper();
      static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);
      void wrap(const v8::FunctionCallbackInfo<v8::Value>& args){ this->Wrap(args.Holder()); }
      static v8::Persistent<v8::Function> constructor;
    private:
      static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

      static void addElementsSpreadElement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addElementsArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addElementsArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addElementsAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addElementsAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addElementsBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addElementsCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addElementsClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addElementsConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addElementsFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addElementsIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addElementsBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addElementsNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addElementsNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addElementsRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addElementsStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addElementsLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addElementsMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addElementsMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addElementsNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addElementsObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addElementsSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addElementsTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addElementsTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addElementsThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addElementsUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addElementsUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addElementsYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
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
}; //end of ArrayExpressionWrapper

}}}}//end of namespaces
#endif