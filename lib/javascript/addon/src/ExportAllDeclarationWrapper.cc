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

#include "../inc/ExportAllDeclarationWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> ExportAllDeclarationWrapper::constructor;

void ExportAllDeclarationWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "ExportAllDeclarationWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
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
  exports->Set(v8::String::NewFromUtf8(isolate, "ExportAllDeclarationWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void ExportAllDeclarationWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new ExportAllDeclarationWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    ExportAllDeclarationWrapper* obj = new ExportAllDeclarationWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `ExportAllDeclarationWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


ExportAllDeclarationWrapper::ExportAllDeclarationWrapper(Factory* fact)                        
{                                                   
  ExportAllDeclaration = fact->getFactory()->createExportAllDeclarationNode();          
}                                                   

ExportAllDeclarationWrapper::~ExportAllDeclarationWrapper()
{        
}        

void ExportAllDeclarationWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void ExportAllDeclarationWrapper::setSourceBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  ExportAllDeclarationWrapper* _ExportAllDeclaration2 = ObjectWrap::Unwrap<ExportAllDeclarationWrapper>(args.This());

  _ExportAllDeclaration2->ExportAllDeclaration->setSource(_BooleanLiteral1->BooleanLiteral);
}
void ExportAllDeclarationWrapper::setSourceNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  ExportAllDeclarationWrapper* _ExportAllDeclaration2 = ObjectWrap::Unwrap<ExportAllDeclarationWrapper>(args.This());

  _ExportAllDeclaration2->ExportAllDeclaration->setSource(_NullLiteral1->NullLiteral);
}
void ExportAllDeclarationWrapper::setSourceNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  ExportAllDeclarationWrapper* _ExportAllDeclaration2 = ObjectWrap::Unwrap<ExportAllDeclarationWrapper>(args.This());

  _ExportAllDeclaration2->ExportAllDeclaration->setSource(_NumberLiteral1->NumberLiteral);
}
void ExportAllDeclarationWrapper::setSourceRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  ExportAllDeclarationWrapper* _ExportAllDeclaration2 = ObjectWrap::Unwrap<ExportAllDeclarationWrapper>(args.This());

  _ExportAllDeclaration2->ExportAllDeclaration->setSource(_RegExpLiteral1->RegExpLiteral);
}
void ExportAllDeclarationWrapper::setSourceStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  ExportAllDeclarationWrapper* _ExportAllDeclaration2 = ObjectWrap::Unwrap<ExportAllDeclarationWrapper>(args.This());

  _ExportAllDeclaration2->ExportAllDeclaration->setSource(_StringLiteral1->StringLiteral);
}
void ExportAllDeclarationWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  ExportAllDeclarationWrapper* _ExportAllDeclaration2 = ObjectWrap::Unwrap<ExportAllDeclarationWrapper>(args.This());

  _ExportAllDeclaration2->ExportAllDeclaration->addComments(_Comment1->Comment);
}
void ExportAllDeclarationWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  ExportAllDeclarationWrapper* _ExportAllDeclaration = ObjectWrap::Unwrap<ExportAllDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _ExportAllDeclaration->ExportAllDeclaration->getPosition();
  range.setPath( param );
  _ExportAllDeclaration->ExportAllDeclaration->setPosition( range );
}

void ExportAllDeclarationWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExportAllDeclarationWrapper* _ExportAllDeclaration = ObjectWrap::Unwrap<ExportAllDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExportAllDeclaration->ExportAllDeclaration->getPosition();
  range.setLine( ui );
  _ExportAllDeclaration->ExportAllDeclaration->setPosition( range );
}

void ExportAllDeclarationWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExportAllDeclarationWrapper* _ExportAllDeclaration = ObjectWrap::Unwrap<ExportAllDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExportAllDeclaration->ExportAllDeclaration->getPosition();
  range.setCol( ui );
  _ExportAllDeclaration->ExportAllDeclaration->setPosition( range );
}

void ExportAllDeclarationWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExportAllDeclarationWrapper* _ExportAllDeclaration = ObjectWrap::Unwrap<ExportAllDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExportAllDeclaration->ExportAllDeclaration->getPosition();
  range.setEndLine( ui );
  _ExportAllDeclaration->ExportAllDeclaration->setPosition( range );
}

void ExportAllDeclarationWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExportAllDeclarationWrapper* _ExportAllDeclaration = ObjectWrap::Unwrap<ExportAllDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExportAllDeclaration->ExportAllDeclaration->getPosition();
  range.setEndCol( ui );
  _ExportAllDeclaration->ExportAllDeclaration->setPosition( range );
}

void ExportAllDeclarationWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExportAllDeclarationWrapper* _ExportAllDeclaration = ObjectWrap::Unwrap<ExportAllDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExportAllDeclaration->ExportAllDeclaration->getPosition();
  range.setWideLine( ui );
  _ExportAllDeclaration->ExportAllDeclaration->setPosition( range );
}

void ExportAllDeclarationWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExportAllDeclarationWrapper* _ExportAllDeclaration = ObjectWrap::Unwrap<ExportAllDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExportAllDeclaration->ExportAllDeclaration->getPosition();
  range.setWideCol( ui );
  _ExportAllDeclaration->ExportAllDeclaration->setPosition( range );
}

void ExportAllDeclarationWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExportAllDeclarationWrapper* _ExportAllDeclaration = ObjectWrap::Unwrap<ExportAllDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExportAllDeclaration->ExportAllDeclaration->getPosition();
  range.setWideEndLine( ui );
  _ExportAllDeclaration->ExportAllDeclaration->setPosition( range );
}

void ExportAllDeclarationWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExportAllDeclarationWrapper* _ExportAllDeclaration = ObjectWrap::Unwrap<ExportAllDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExportAllDeclaration->ExportAllDeclaration->getPosition();
  range.setWideEndCol( ui );
  _ExportAllDeclaration->ExportAllDeclaration->setPosition( range );
}

}}}} //end of namespaces