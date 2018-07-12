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

#ifndef _JAVASCRIPT_CallExpressionWrapper_H_
#define _JAVASCRIPT_CallExpressionWrapper_H_

#include "javascript/inc/javascript.h"
#include <node.h>
#include <node_object_wrap.h>
#include "../Factory.h"

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {
  class Factory;

  class CallExpressionWrapper : public node::ObjectWrap {
    public:
      columbus::javascript::asg::expression::CallExpression* CallExpression;
      static void Init(v8::Handle<v8::Object> exports);
      CallExpressionWrapper(const CallExpressionWrapper&);
      CallExpressionWrapper(Factory* fact);
      virtual ~CallExpressionWrapper();
      static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);
      void wrap(const v8::FunctionCallbackInfo<v8::Value>& args){ this->Wrap(args.Holder()); }
      static v8::Persistent<v8::Function> constructor;
    private:
      static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

      static void setCalleeArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setCalleeArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setCalleeAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setCalleeAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setCalleeBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setCalleeCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setCalleeClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setCalleeConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setCalleeFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setCalleeIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setCalleeBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setCalleeNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setCalleeNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setCalleeRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setCalleeStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setCalleeLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setCalleeMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setCalleeMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setCalleeNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setCalleeObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setCalleeSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setCalleeTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setCalleeTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setCalleeThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setCalleeUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setCalleeUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setCalleeYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setCalleeSuper(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addArgumentsArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addArgumentsArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addArgumentsAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addArgumentsAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addArgumentsBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addArgumentsCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addArgumentsClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addArgumentsConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addArgumentsFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addArgumentsIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addArgumentsBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addArgumentsNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addArgumentsNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addArgumentsRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addArgumentsStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addArgumentsLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addArgumentsMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addArgumentsMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addArgumentsNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addArgumentsObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addArgumentsSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addArgumentsTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addArgumentsTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addArgumentsThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addArgumentsUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addArgumentsUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addArgumentsYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addArgumentsSpreadElement(const v8::FunctionCallbackInfo<v8::Value>& args);
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
}; //end of CallExpressionWrapper

}}}}//end of namespaces
#endif