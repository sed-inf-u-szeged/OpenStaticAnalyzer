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

#ifndef _JAVASCRIPT_VariableDeclaratorWrapper_H_
#define _JAVASCRIPT_VariableDeclaratorWrapper_H_

#include "javascript/inc/javascript.h"
#include <node.h>
#include <node_object_wrap.h>
#include "../Factory.h"

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {
  class Factory;

  class VariableDeclaratorWrapper : public node::ObjectWrap {
    public:
      columbus::javascript::asg::declaration::VariableDeclarator* VariableDeclarator;
      static void Init(v8::Handle<v8::Object> exports);
      VariableDeclaratorWrapper(const VariableDeclaratorWrapper&);
      VariableDeclaratorWrapper(Factory* fact);
      virtual ~VariableDeclaratorWrapper();
      static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);
      void wrap(const v8::FunctionCallbackInfo<v8::Value>& args){ this->Wrap(args.Holder()); }
      static v8::Persistent<v8::Function> constructor;
    private:
      static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

      static void setIdentifierIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setIdentifierMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setIdentifierArrayPattern(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setIdentifierAssignmentPattern(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setIdentifierObjectPattern(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setIdentifierRestElement(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setInitArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setInitArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setInitAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setInitAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setInitBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setInitCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setInitClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setInitConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setInitFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setInitIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setInitBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setInitNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setInitNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setInitRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setInitStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setInitLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setInitMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setInitMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setInitNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setInitObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setInitSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setInitTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setInitTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setInitThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setInitUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setInitUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setInitYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args);
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
}; //end of VariableDeclaratorWrapper

}}}}//end of namespaces
#endif