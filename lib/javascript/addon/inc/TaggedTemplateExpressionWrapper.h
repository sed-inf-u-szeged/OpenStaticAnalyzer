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

#ifndef _JAVASCRIPT_TaggedTemplateExpressionWrapper_H_
#define _JAVASCRIPT_TaggedTemplateExpressionWrapper_H_

#include "javascript/inc/javascript.h"
#include <node.h>
#include <node_object_wrap.h>
#include "../Factory.h"

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {
  class Factory;

  class TaggedTemplateExpressionWrapper : public node::ObjectWrap {
    public:
      columbus::javascript::asg::expression::TaggedTemplateExpression* TaggedTemplateExpression;
      static void Init(v8::Handle<v8::Object> exports);
      TaggedTemplateExpressionWrapper(const TaggedTemplateExpressionWrapper&);
      TaggedTemplateExpressionWrapper(Factory* fact);
      virtual ~TaggedTemplateExpressionWrapper();
      static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);
      void wrap(const v8::FunctionCallbackInfo<v8::Value>& args){ this->Wrap(args.Holder()); }
      static v8::Persistent<v8::Function> constructor;
    private:
      static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

      static void setTagArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTagArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTagAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTagAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTagBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTagCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTagClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTagConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTagFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTagIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTagBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTagNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTagNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTagRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTagStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTagLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTagMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTagMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTagNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTagObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTagSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTagTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTagTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTagThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTagUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTagUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setTagYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setQuasiTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
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
}; //end of TaggedTemplateExpressionWrapper

}}}}//end of namespaces
#endif