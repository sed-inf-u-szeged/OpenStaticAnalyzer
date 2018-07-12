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

#ifndef _JAVASCRIPT_AssignmentPropertyWrapper_H_
#define _JAVASCRIPT_AssignmentPropertyWrapper_H_

#include "javascript/inc/javascript.h"
#include <node.h>
#include <node_object_wrap.h>
#include "../Factory.h"

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {
  class Factory;

  class AssignmentPropertyWrapper : public node::ObjectWrap {
    public:
      columbus::javascript::asg::expression::AssignmentProperty* AssignmentProperty;
      static void Init(v8::Handle<v8::Object> exports);
      AssignmentPropertyWrapper(const AssignmentPropertyWrapper&);
      AssignmentPropertyWrapper(Factory* fact);
      virtual ~AssignmentPropertyWrapper();
      static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);
      void wrap(const v8::FunctionCallbackInfo<v8::Value>& args){ this->Wrap(args.Holder()); }
      static v8::Persistent<v8::Function> constructor;
    private:
      static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

      static void setValueArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setValueArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setValueAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setValueAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setValueBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setValueCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setValueClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setValueConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setValueFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setValueIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setValueBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setValueNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setValueNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setValueRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setValueStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setValueLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setValueMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setValueMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setValueNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setValueObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setValueSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setValueTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setValueTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setValueThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setValueUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setValueUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setValueYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setValueArrayPattern(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setValueAssignmentPattern(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setValueObjectPattern(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setValueRestElement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setKeyArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setKeyArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setKeyAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setKeyAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setKeyBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setKeyCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setKeyClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setKeyConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setKeyFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setKeyIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setKeyBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setKeyNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setKeyNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setKeyRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setKeyStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setKeyLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setKeyMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setKeyMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setKeyNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setKeyObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setKeySequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setKeyTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setKeyTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setKeyThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setKeyUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setKeyUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setKeyYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setKind(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setMethod(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setShorthand(const v8::FunctionCallbackInfo<v8::Value>& args);
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
}; //end of AssignmentPropertyWrapper

}}}}//end of namespaces
#endif