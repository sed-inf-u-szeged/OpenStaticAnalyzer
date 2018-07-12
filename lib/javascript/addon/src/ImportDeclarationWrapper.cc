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

#include "../inc/ImportDeclarationWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> ImportDeclarationWrapper::constructor;

void ImportDeclarationWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "ImportDeclarationWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "addSpecifiersImportDefaultSpecifier", addSpecifiersImportDefaultSpecifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addSpecifiersImportNamespaceSpecifier", addSpecifiersImportNamespaceSpecifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addSpecifiersImportSpecifier", addSpecifiersImportSpecifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSourceBooleanLiteral", setSourceBooleanLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSourceNullLiteral", setSourceNullLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSourceNumberLiteral", setSourceNumberLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSourceRegExpLiteral", setSourceRegExpLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSourceStringLiteral", setSourceStringLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addCommentsComment", addCommentsComment);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPath", setPath);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLine", setLine);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setCol", setCol);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setEndLine", setEndLine);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setEndCol", setEndCol);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setWideLine", setWideLine);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setWideCol", setWideCol);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setWideEndLine", setWideEndLine);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setWideEndCol", setWideEndCol);
                                                                           
  constructor.Reset(isolate, tpl->GetFunction());                          
  exports->Set(v8::String::NewFromUtf8(isolate, "ImportDeclarationWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void ImportDeclarationWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new ImportDeclarationWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    ImportDeclarationWrapper* obj = new ImportDeclarationWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `ImportDeclarationWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


ImportDeclarationWrapper::ImportDeclarationWrapper(Factory* fact)                        
{                                                   
  ImportDeclaration = fact->getFactory()->createImportDeclarationNode();          
}                                                   

ImportDeclarationWrapper::~ImportDeclarationWrapper()
{        
}        

void ImportDeclarationWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void ImportDeclarationWrapper::addSpecifiersImportDefaultSpecifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ImportDefaultSpecifierWrapper* _ImportDefaultSpecifier1 = ObjectWrap::Unwrap<ImportDefaultSpecifierWrapper>(args[0]->ToObject());
  ImportDeclarationWrapper* _ImportDeclaration2 = ObjectWrap::Unwrap<ImportDeclarationWrapper>(args.This());

  _ImportDeclaration2->ImportDeclaration->addSpecifiers(_ImportDefaultSpecifier1->ImportDefaultSpecifier);
}
void ImportDeclarationWrapper::addSpecifiersImportNamespaceSpecifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ImportNamespaceSpecifierWrapper* _ImportNamespaceSpecifier1 = ObjectWrap::Unwrap<ImportNamespaceSpecifierWrapper>(args[0]->ToObject());
  ImportDeclarationWrapper* _ImportDeclaration2 = ObjectWrap::Unwrap<ImportDeclarationWrapper>(args.This());

  _ImportDeclaration2->ImportDeclaration->addSpecifiers(_ImportNamespaceSpecifier1->ImportNamespaceSpecifier);
}
void ImportDeclarationWrapper::addSpecifiersImportSpecifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ImportSpecifierWrapper* _ImportSpecifier1 = ObjectWrap::Unwrap<ImportSpecifierWrapper>(args[0]->ToObject());
  ImportDeclarationWrapper* _ImportDeclaration2 = ObjectWrap::Unwrap<ImportDeclarationWrapper>(args.This());

  _ImportDeclaration2->ImportDeclaration->addSpecifiers(_ImportSpecifier1->ImportSpecifier);
}
void ImportDeclarationWrapper::setSourceBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  ImportDeclarationWrapper* _ImportDeclaration2 = ObjectWrap::Unwrap<ImportDeclarationWrapper>(args.This());

  _ImportDeclaration2->ImportDeclaration->setSource(_BooleanLiteral1->BooleanLiteral);
}
void ImportDeclarationWrapper::setSourceNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  ImportDeclarationWrapper* _ImportDeclaration2 = ObjectWrap::Unwrap<ImportDeclarationWrapper>(args.This());

  _ImportDeclaration2->ImportDeclaration->setSource(_NullLiteral1->NullLiteral);
}
void ImportDeclarationWrapper::setSourceNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  ImportDeclarationWrapper* _ImportDeclaration2 = ObjectWrap::Unwrap<ImportDeclarationWrapper>(args.This());

  _ImportDeclaration2->ImportDeclaration->setSource(_NumberLiteral1->NumberLiteral);
}
void ImportDeclarationWrapper::setSourceRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  ImportDeclarationWrapper* _ImportDeclaration2 = ObjectWrap::Unwrap<ImportDeclarationWrapper>(args.This());

  _ImportDeclaration2->ImportDeclaration->setSource(_RegExpLiteral1->RegExpLiteral);
}
void ImportDeclarationWrapper::setSourceStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  ImportDeclarationWrapper* _ImportDeclaration2 = ObjectWrap::Unwrap<ImportDeclarationWrapper>(args.This());

  _ImportDeclaration2->ImportDeclaration->setSource(_StringLiteral1->StringLiteral);
}
void ImportDeclarationWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  ImportDeclarationWrapper* _ImportDeclaration2 = ObjectWrap::Unwrap<ImportDeclarationWrapper>(args.This());

  _ImportDeclaration2->ImportDeclaration->addComments(_Comment1->Comment);
}
void ImportDeclarationWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  ImportDeclarationWrapper* _ImportDeclaration = ObjectWrap::Unwrap<ImportDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _ImportDeclaration->ImportDeclaration->getPosition();
  range.setPath( param );
  _ImportDeclaration->ImportDeclaration->setPosition( range );
}

void ImportDeclarationWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ImportDeclarationWrapper* _ImportDeclaration = ObjectWrap::Unwrap<ImportDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ImportDeclaration->ImportDeclaration->getPosition();
  range.setLine( ui );
  _ImportDeclaration->ImportDeclaration->setPosition( range );
}

void ImportDeclarationWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ImportDeclarationWrapper* _ImportDeclaration = ObjectWrap::Unwrap<ImportDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ImportDeclaration->ImportDeclaration->getPosition();
  range.setCol( ui );
  _ImportDeclaration->ImportDeclaration->setPosition( range );
}

void ImportDeclarationWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ImportDeclarationWrapper* _ImportDeclaration = ObjectWrap::Unwrap<ImportDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ImportDeclaration->ImportDeclaration->getPosition();
  range.setEndLine( ui );
  _ImportDeclaration->ImportDeclaration->setPosition( range );
}

void ImportDeclarationWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ImportDeclarationWrapper* _ImportDeclaration = ObjectWrap::Unwrap<ImportDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ImportDeclaration->ImportDeclaration->getPosition();
  range.setEndCol( ui );
  _ImportDeclaration->ImportDeclaration->setPosition( range );
}

void ImportDeclarationWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ImportDeclarationWrapper* _ImportDeclaration = ObjectWrap::Unwrap<ImportDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ImportDeclaration->ImportDeclaration->getPosition();
  range.setWideLine( ui );
  _ImportDeclaration->ImportDeclaration->setPosition( range );
}

void ImportDeclarationWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ImportDeclarationWrapper* _ImportDeclaration = ObjectWrap::Unwrap<ImportDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ImportDeclaration->ImportDeclaration->getPosition();
  range.setWideCol( ui );
  _ImportDeclaration->ImportDeclaration->setPosition( range );
}

void ImportDeclarationWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ImportDeclarationWrapper* _ImportDeclaration = ObjectWrap::Unwrap<ImportDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ImportDeclaration->ImportDeclaration->getPosition();
  range.setWideEndLine( ui );
  _ImportDeclaration->ImportDeclaration->setPosition( range );
}

void ImportDeclarationWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ImportDeclarationWrapper* _ImportDeclaration = ObjectWrap::Unwrap<ImportDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ImportDeclaration->ImportDeclaration->getPosition();
  range.setWideEndCol( ui );
  _ImportDeclaration->ImportDeclaration->setPosition( range );
}

}}}} //end of namespaces