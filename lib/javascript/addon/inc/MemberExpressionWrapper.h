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

#ifndef _JAVASCRIPT_MemberExpressionWrapper_H_
#define _JAVASCRIPT_MemberExpressionWrapper_H_

#include "javascript/inc/javascript.h"
#include <node.h>
#include <node_object_wrap.h>
#include "../Factory.h"

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {
  class Factory;

  class MemberExpressionWrapper : public node::ObjectWrap {
    public:
      columbus::javascript::asg::expression::MemberExpression* MemberExpression;
      static void Init(v8::Handle<v8::Object> exports);
      MemberExpressionWrapper(const MemberExpressionWrapper&);
      MemberExpressionWrapper(Factory* fact);
      virtual ~MemberExpressionWrapper();
      static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);
      void wrap(const v8::FunctionCallbackInfo<v8::Value>& args){ this->Wrap(args.Holder()); }
      static v8::Persistent<v8::Function> constructor;
    private:
      static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

      static void setPropertyArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setPropertyArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setPropertyAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setPropertyAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setPropertyBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setPropertyCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setPropertyClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setPropertyConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setPropertyFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setPropertyIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setPropertyBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setPropertyNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setPropertyNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setPropertyRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setPropertyStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setPropertyLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setPropertyMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setPropertyMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setPropertyNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setPropertyObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setPropertySequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setPropertyTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setPropertyTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setPropertyThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setPropertyUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setPropertyUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setPropertyYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setObjectSuper(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setObjectArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setObjectArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setObjectAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setObjectAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setObjectBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setObjectCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setObjectClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setObjectConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setObjectFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setObjectIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setObjectBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setObjectNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setObjectNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setObjectRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setObjectStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setObjectLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setObjectMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setObjectMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setObjectNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setObjectObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setObjectSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setObjectTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setObjectTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setObjectThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setObjectUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setObjectUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setObjectYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setComputed(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setPath(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setLine(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setCol(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setEndLine(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setEndCol(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setWideLine(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setWideCol(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setWideEndLine(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setWideEndCol(const v8::FunctionCallbackInfo<v8::Value>& args);
}; //end of MemberExpressionWrapper

}}}}//end of namespaces
#endif