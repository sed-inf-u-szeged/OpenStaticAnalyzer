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

#include "../inc/ExportNamedDeclarationWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> ExportNamedDeclarationWrapper::constructor;

void ExportNamedDeclarationWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "ExportNamedDeclarationWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationClassDeclaration", setDeclarationClassDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationExportAllDeclaration", setDeclarationExportAllDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationExportDefaultDeclaration", setDeclarationExportDefaultDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationFunctionDeclaration", setDeclarationFunctionDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationVariableDeclaration", setDeclarationVariableDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addSpecifiersExportSpecifier", addSpecifiersExportSpecifier);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "ExportNamedDeclarationWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void ExportNamedDeclarationWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new ExportNamedDeclarationWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    ExportNamedDeclarationWrapper* obj = new ExportNamedDeclarationWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `ExportNamedDeclarationWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


ExportNamedDeclarationWrapper::ExportNamedDeclarationWrapper(Factory* fact)                        
{                                                   
  ExportNamedDeclaration = fact->getFactory()->createExportNamedDeclarationNode();          
}                                                   

ExportNamedDeclarationWrapper::~ExportNamedDeclarationWrapper()
{        
}        

void ExportNamedDeclarationWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void ExportNamedDeclarationWrapper::setDeclarationClassDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassDeclarationWrapper* _ClassDeclaration1 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args[0]->ToObject());
  ExportNamedDeclarationWrapper* _ExportNamedDeclaration2 = ObjectWrap::Unwrap<ExportNamedDeclarationWrapper>(args.This());

  _ExportNamedDeclaration2->ExportNamedDeclaration->setDeclaration(_ClassDeclaration1->ClassDeclaration);
}
void ExportNamedDeclarationWrapper::setDeclarationExportAllDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExportAllDeclarationWrapper* _ExportAllDeclaration1 = ObjectWrap::Unwrap<ExportAllDeclarationWrapper>(args[0]->ToObject());
  ExportNamedDeclarationWrapper* _ExportNamedDeclaration2 = ObjectWrap::Unwrap<ExportNamedDeclarationWrapper>(args.This());

  _ExportNamedDeclaration2->ExportNamedDeclaration->setDeclaration(_ExportAllDeclaration1->ExportAllDeclaration);
}
void ExportNamedDeclarationWrapper::setDeclarationExportDefaultDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration1 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args[0]->ToObject());
  ExportNamedDeclarationWrapper* _ExportNamedDeclaration2 = ObjectWrap::Unwrap<ExportNamedDeclarationWrapper>(args.This());

  _ExportNamedDeclaration2->ExportNamedDeclaration->setDeclaration(_ExportDefaultDeclaration1->ExportDefaultDeclaration);
}
void ExportNamedDeclarationWrapper::setDeclarationFunctionDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionDeclarationWrapper* _FunctionDeclaration1 = ObjectWrap::Unwrap<FunctionDeclarationWrapper>(args[0]->ToObject());
  ExportNamedDeclarationWrapper* _ExportNamedDeclaration2 = ObjectWrap::Unwrap<ExportNamedDeclarationWrapper>(args.This());

  _ExportNamedDeclaration2->ExportNamedDeclaration->setDeclaration(_FunctionDeclaration1->FunctionDeclaration);
}
void ExportNamedDeclarationWrapper::setDeclarationVariableDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  VariableDeclarationWrapper* _VariableDeclaration1 = ObjectWrap::Unwrap<VariableDeclarationWrapper>(args[0]->ToObject());
  ExportNamedDeclarationWrapper* _ExportNamedDeclaration2 = ObjectWrap::Unwrap<ExportNamedDeclarationWrapper>(args.This());

  _ExportNamedDeclaration2->ExportNamedDeclaration->setDeclaration(_VariableDeclaration1->VariableDeclaration);
}
void ExportNamedDeclarationWrapper::addSpecifiersExportSpecifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExportSpecifierWrapper* _ExportSpecifier1 = ObjectWrap::Unwrap<ExportSpecifierWrapper>(args[0]->ToObject());
  ExportNamedDeclarationWrapper* _ExportNamedDeclaration2 = ObjectWrap::Unwrap<ExportNamedDeclarationWrapper>(args.This());

  _ExportNamedDeclaration2->ExportNamedDeclaration->addSpecifiers(_ExportSpecifier1->ExportSpecifier);
}
void ExportNamedDeclarationWrapper::setSourceBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  ExportNamedDeclarationWrapper* _ExportNamedDeclaration2 = ObjectWrap::Unwrap<ExportNamedDeclarationWrapper>(args.This());

  _ExportNamedDeclaration2->ExportNamedDeclaration->setSource(_BooleanLiteral1->BooleanLiteral);
}
void ExportNamedDeclarationWrapper::setSourceNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  ExportNamedDeclarationWrapper* _ExportNamedDeclaration2 = ObjectWrap::Unwrap<ExportNamedDeclarationWrapper>(args.This());

  _ExportNamedDeclaration2->ExportNamedDeclaration->setSource(_NullLiteral1->NullLiteral);
}
void ExportNamedDeclarationWrapper::setSourceNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  ExportNamedDeclarationWrapper* _ExportNamedDeclaration2 = ObjectWrap::Unwrap<ExportNamedDeclarationWrapper>(args.This());

  _ExportNamedDeclaration2->ExportNamedDeclaration->setSource(_NumberLiteral1->NumberLiteral);
}
void ExportNamedDeclarationWrapper::setSourceRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  ExportNamedDeclarationWrapper* _ExportNamedDeclaration2 = ObjectWrap::Unwrap<ExportNamedDeclarationWrapper>(args.This());

  _ExportNamedDeclaration2->ExportNamedDeclaration->setSource(_RegExpLiteral1->RegExpLiteral);
}
void ExportNamedDeclarationWrapper::setSourceStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  ExportNamedDeclarationWrapper* _ExportNamedDeclaration2 = ObjectWrap::Unwrap<ExportNamedDeclarationWrapper>(args.This());

  _ExportNamedDeclaration2->ExportNamedDeclaration->setSource(_StringLiteral1->StringLiteral);
}
void ExportNamedDeclarationWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  ExportNamedDeclarationWrapper* _ExportNamedDeclaration2 = ObjectWrap::Unwrap<ExportNamedDeclarationWrapper>(args.This());

  _ExportNamedDeclaration2->ExportNamedDeclaration->addComments(_Comment1->Comment);
}
void ExportNamedDeclarationWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  ExportNamedDeclarationWrapper* _ExportNamedDeclaration = ObjectWrap::Unwrap<ExportNamedDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _ExportNamedDeclaration->ExportNamedDeclaration->getPosition();
  range.setPath( param );
  _ExportNamedDeclaration->ExportNamedDeclaration->setPosition( range );
}

void ExportNamedDeclarationWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExportNamedDeclarationWrapper* _ExportNamedDeclaration = ObjectWrap::Unwrap<ExportNamedDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExportNamedDeclaration->ExportNamedDeclaration->getPosition();
  range.setLine( ui );
  _ExportNamedDeclaration->ExportNamedDeclaration->setPosition( range );
}

void ExportNamedDeclarationWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExportNamedDeclarationWrapper* _ExportNamedDeclaration = ObjectWrap::Unwrap<ExportNamedDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExportNamedDeclaration->ExportNamedDeclaration->getPosition();
  range.setCol( ui );
  _ExportNamedDeclaration->ExportNamedDeclaration->setPosition( range );
}

void ExportNamedDeclarationWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExportNamedDeclarationWrapper* _ExportNamedDeclaration = ObjectWrap::Unwrap<ExportNamedDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExportNamedDeclaration->ExportNamedDeclaration->getPosition();
  range.setEndLine( ui );
  _ExportNamedDeclaration->ExportNamedDeclaration->setPosition( range );
}

void ExportNamedDeclarationWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExportNamedDeclarationWrapper* _ExportNamedDeclaration = ObjectWrap::Unwrap<ExportNamedDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExportNamedDeclaration->ExportNamedDeclaration->getPosition();
  range.setEndCol( ui );
  _ExportNamedDeclaration->ExportNamedDeclaration->setPosition( range );
}

void ExportNamedDeclarationWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExportNamedDeclarationWrapper* _ExportNamedDeclaration = ObjectWrap::Unwrap<ExportNamedDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExportNamedDeclaration->ExportNamedDeclaration->getPosition();
  range.setWideLine( ui );
  _ExportNamedDeclaration->ExportNamedDeclaration->setPosition( range );
}

void ExportNamedDeclarationWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExportNamedDeclarationWrapper* _ExportNamedDeclaration = ObjectWrap::Unwrap<ExportNamedDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExportNamedDeclaration->ExportNamedDeclaration->getPosition();
  range.setWideCol( ui );
  _ExportNamedDeclaration->ExportNamedDeclaration->setPosition( range );
}

void ExportNamedDeclarationWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExportNamedDeclarationWrapper* _ExportNamedDeclaration = ObjectWrap::Unwrap<ExportNamedDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExportNamedDeclaration->ExportNamedDeclaration->getPosition();
  range.setWideEndLine( ui );
  _ExportNamedDeclaration->ExportNamedDeclaration->setPosition( range );
}

void ExportNamedDeclarationWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExportNamedDeclarationWrapper* _ExportNamedDeclaration = ObjectWrap::Unwrap<ExportNamedDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExportNamedDeclaration->ExportNamedDeclaration->getPosition();
  range.setWideEndCol( ui );
  _ExportNamedDeclaration->ExportNamedDeclaration->setPosition( range );
}

}}}} //end of namespaces