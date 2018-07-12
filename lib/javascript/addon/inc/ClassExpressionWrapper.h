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

#ifndef _JAVASCRIPT_ClassExpressionWrapper_H_
#define _JAVASCRIPT_ClassExpressionWrapper_H_

#include "javascript/inc/javascript.h"
#include <node.h>
#include <node_object_wrap.h>
#include "../Factory.h"

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {
  class Factory;

  class ClassExpressionWrapper : public node::ObjectWrap {
    public:
      columbus::javascript::asg::expression::ClassExpression* ClassExpression;
      static void Init(v8::Handle<v8::Object> exports);
      ClassExpressionWrapper(const ClassExpressionWrapper&);
      ClassExpressionWrapper(Factory* fact);
      virtual ~ClassExpressionWrapper();
      static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);
      void wrap(const v8::FunctionCallbackInfo<v8::Value>& args){ this->Wrap(args.Holder()); }
      static v8::Persistent<v8::Function> constructor;
    private:
      static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

      static void addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setBodyClassBody(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setSuperClassArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setSuperClassArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setSuperClassAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setSuperClassAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setSuperClassBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setSuperClassCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setSuperClassClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setSuperClassConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setSuperClassFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setSuperClassIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setSuperClassBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setSuperClassNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setSuperClassNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setSuperClassRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setSuperClassStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setSuperClassLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setSuperClassMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setSuperClassMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setSuperClassNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setSuperClassObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setSuperClassSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setSuperClassTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setSuperClassTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setSuperClassThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setSuperClassUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setSuperClassUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setSuperClassYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setIdentifierIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setPath(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setLine(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setCol(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setEndLine(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setEndCol(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setWideLine(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setWideCol(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setWideEndLine(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setWideEndCol(const v8::FunctionCallbackInfo<v8::Value>& args);
}; //end of ClassExpressionWrapper

}}}}//end of namespaces
#endif