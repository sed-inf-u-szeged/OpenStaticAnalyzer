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

#include "../inc/ExportSpecifierWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> ExportSpecifierWrapper::constructor;

void ExportSpecifierWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "ExportSpecifierWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "setExportedIdentifier", setExportedIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLocalIdentifier", setLocalIdentifier);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "ExportSpecifierWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void ExportSpecifierWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new ExportSpecifierWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    ExportSpecifierWrapper* obj = new ExportSpecifierWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `ExportSpecifierWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


ExportSpecifierWrapper::ExportSpecifierWrapper(Factory* fact)                        
{                                                   
  ExportSpecifier = fact->getFactory()->createExportSpecifierNode();          
}                                                   

ExportSpecifierWrapper::~ExportSpecifierWrapper()
{        
}        

void ExportSpecifierWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void ExportSpecifierWrapper::setExportedIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  ExportSpecifierWrapper* _ExportSpecifier2 = ObjectWrap::Unwrap<ExportSpecifierWrapper>(args.This());

  _ExportSpecifier2->ExportSpecifier->setExported(_Identifier1->Identifier);
}
void ExportSpecifierWrapper::setLocalIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  ExportSpecifierWrapper* _ExportSpecifier2 = ObjectWrap::Unwrap<ExportSpecifierWrapper>(args.This());

  _ExportSpecifier2->ExportSpecifier->setLocal(_Identifier1->Identifier);
}
void ExportSpecifierWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  ExportSpecifierWrapper* _ExportSpecifier2 = ObjectWrap::Unwrap<ExportSpecifierWrapper>(args.This());

  _ExportSpecifier2->ExportSpecifier->addComments(_Comment1->Comment);
}
void ExportSpecifierWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  ExportSpecifierWrapper* _ExportSpecifier = ObjectWrap::Unwrap<ExportSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _ExportSpecifier->ExportSpecifier->getPosition();
  range.setPath( param );
  _ExportSpecifier->ExportSpecifier->setPosition( range );
}

void ExportSpecifierWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExportSpecifierWrapper* _ExportSpecifier = ObjectWrap::Unwrap<ExportSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExportSpecifier->ExportSpecifier->getPosition();
  range.setLine( ui );
  _ExportSpecifier->ExportSpecifier->setPosition( range );
}

void ExportSpecifierWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExportSpecifierWrapper* _ExportSpecifier = ObjectWrap::Unwrap<ExportSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExportSpecifier->ExportSpecifier->getPosition();
  range.setCol( ui );
  _ExportSpecifier->ExportSpecifier->setPosition( range );
}

void ExportSpecifierWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExportSpecifierWrapper* _ExportSpecifier = ObjectWrap::Unwrap<ExportSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExportSpecifier->ExportSpecifier->getPosition();
  range.setEndLine( ui );
  _ExportSpecifier->ExportSpecifier->setPosition( range );
}

void ExportSpecifierWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExportSpecifierWrapper* _ExportSpecifier = ObjectWrap::Unwrap<ExportSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExportSpecifier->ExportSpecifier->getPosition();
  range.setEndCol( ui );
  _ExportSpecifier->ExportSpecifier->setPosition( range );
}

void ExportSpecifierWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExportSpecifierWrapper* _ExportSpecifier = ObjectWrap::Unwrap<ExportSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExportSpecifier->ExportSpecifier->getPosition();
  range.setWideLine( ui );
  _ExportSpecifier->ExportSpecifier->setPosition( range );
}

void ExportSpecifierWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExportSpecifierWrapper* _ExportSpecifier = ObjectWrap::Unwrap<ExportSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExportSpecifier->ExportSpecifier->getPosition();
  range.setWideCol( ui );
  _ExportSpecifier->ExportSpecifier->setPosition( range );
}

void ExportSpecifierWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExportSpecifierWrapper* _ExportSpecifier = ObjectWrap::Unwrap<ExportSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExportSpecifier->ExportSpecifier->getPosition();
  range.setWideEndLine( ui );
  _ExportSpecifier->ExportSpecifier->setPosition( range );
}

void ExportSpecifierWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExportSpecifierWrapper* _ExportSpecifier = ObjectWrap::Unwrap<ExportSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExportSpecifier->ExportSpecifier->getPosition();
  range.setWideEndCol( ui );
  _ExportSpecifier->ExportSpecifier->setPosition( range );
}

}}}} //end of namespaces