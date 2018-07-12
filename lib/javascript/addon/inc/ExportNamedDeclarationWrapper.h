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

#ifndef _JAVASCRIPT_ExportNamedDeclarationWrapper_H_
#define _JAVASCRIPT_ExportNamedDeclarationWrapper_H_

#include "javascript/inc/javascript.h"
#include <node.h>
#include <node_object_wrap.h>
#include "../Factory.h"

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {
  class Factory;

  class ExportNamedDeclarationWrapper : public node::ObjectWrap {
    public:
      columbus::javascript::asg::declaration::ExportNamedDeclaration* ExportNamedDeclaration;
      static void Init(v8::Handle<v8::Object> exports);
      ExportNamedDeclarationWrapper(const ExportNamedDeclarationWrapper&);
      ExportNamedDeclarationWrapper(Factory* fact);
      virtual ~ExportNamedDeclarationWrapper();
      static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);
      void wrap(const v8::FunctionCallbackInfo<v8::Value>& args){ this->Wrap(args.Holder()); }
      static v8::Persistent<v8::Function> constructor;
    private:
      static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

      static void setDeclarationClassDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setDeclarationExportAllDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setDeclarationExportDefaultDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setDeclarationFunctionDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setDeclarationVariableDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void addSpecifiersExportSpecifier(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setSourceBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setSourceNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setSourceNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setSourceRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void setSourceStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args);
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
}; //end of ExportNamedDeclarationWrapper

}}}}//end of namespaces
#endif