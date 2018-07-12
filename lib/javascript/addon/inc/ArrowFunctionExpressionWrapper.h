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

#ifndef _JAVASCRIPT_ArrowFunctionExpressionWrapper_H_
#define _JAVASCRIPT_ArrowFunctionExpressionWrapper_H_

#include "javascript/inc/javascript.h"
#include <node.h>
#include <node_object_wrap.h>
#include "../Factory.h"

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {
  class Factory;

  class ArrowFunctionExpressionWrapper : public node::ObjectWrap {
    public:
      columbus::javascript::asg::expression::ArrowFunctionExpression* ArrowFunctionExpression;
      static void Init(v8::Handle<v8::Object> exports);
      ArrowFunctionExpressionWrapper(const ArrowFunctionExpressionWrapper&);
      ArrowFunctionExpressionWrapper(Factory* fact);
      virtual ~ArrowFunctionExpressionWrapper();
      static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);
      void wrap(const v8::FunctionCallbackInfo<v8::Value>& args){ this->Wrap(args.Holder()); }
      static v8::Persistent<v8::Function> constructor;
    private:
      static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

      static void addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addParamsIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addParamsMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addParamsArrayPattern(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addParamsAssignmentPattern(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addParamsObjectPattern(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addParamsRestElement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyBlockStatement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodySequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setIdentifierIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setPath(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setLine(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setCol(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setEndLine(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setEndCol(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setWideLine(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setWideCol(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setWideEndLine(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setWideEndCol(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setGenerator(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setAsync(const v8::FunctionCallbackInfo<v8::Value>& args);
}; //end of ArrowFunctionExpressionWrapper

}}}}//end of namespaces
#endif