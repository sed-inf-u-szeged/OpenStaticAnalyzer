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

#include "../inc/MetaPropertyWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> MetaPropertyWrapper::constructor;

void MetaPropertyWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "MetaPropertyWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "setMetaIdentifier", setMetaIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPropertyIdentifier", setPropertyIdentifier);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "MetaPropertyWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void MetaPropertyWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new MetaPropertyWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    MetaPropertyWrapper* obj = new MetaPropertyWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `MetaPropertyWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


MetaPropertyWrapper::MetaPropertyWrapper(Factory* fact)                        
{                                                   
  MetaProperty = fact->getFactory()->createMetaPropertyNode();          
}                                                   

MetaPropertyWrapper::~MetaPropertyWrapper()
{        
}        

void MetaPropertyWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void MetaPropertyWrapper::setMetaIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  MetaPropertyWrapper* _MetaProperty2 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args.This());

  _MetaProperty2->MetaProperty->setMeta(_Identifier1->Identifier);
}
void MetaPropertyWrapper::setPropertyIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  MetaPropertyWrapper* _MetaProperty2 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args.This());

  _MetaProperty2->MetaProperty->setProperty(_Identifier1->Identifier);
}
void MetaPropertyWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  MetaPropertyWrapper* _MetaProperty2 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args.This());

  _MetaProperty2->MetaProperty->addComments(_Comment1->Comment);
}
void MetaPropertyWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  MetaPropertyWrapper* _MetaProperty = ObjectWrap::Unwrap<MetaPropertyWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _MetaProperty->MetaProperty->getPosition();
  range.setPath( param );
  _MetaProperty->MetaProperty->setPosition( range );
}

void MetaPropertyWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  MetaPropertyWrapper* _MetaProperty = ObjectWrap::Unwrap<MetaPropertyWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _MetaProperty->MetaProperty->getPosition();
  range.setLine( ui );
  _MetaProperty->MetaProperty->setPosition( range );
}

void MetaPropertyWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  MetaPropertyWrapper* _MetaProperty = ObjectWrap::Unwrap<MetaPropertyWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _MetaProperty->MetaProperty->getPosition();
  range.setCol( ui );
  _MetaProperty->MetaProperty->setPosition( range );
}

void MetaPropertyWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  MetaPropertyWrapper* _MetaProperty = ObjectWrap::Unwrap<MetaPropertyWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _MetaProperty->MetaProperty->getPosition();
  range.setEndLine( ui );
  _MetaProperty->MetaProperty->setPosition( range );
}

void MetaPropertyWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  MetaPropertyWrapper* _MetaProperty = ObjectWrap::Unwrap<MetaPropertyWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _MetaProperty->MetaProperty->getPosition();
  range.setEndCol( ui );
  _MetaProperty->MetaProperty->setPosition( range );
}

void MetaPropertyWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  MetaPropertyWrapper* _MetaProperty = ObjectWrap::Unwrap<MetaPropertyWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _MetaProperty->MetaProperty->getPosition();
  range.setWideLine( ui );
  _MetaProperty->MetaProperty->setPosition( range );
}

void MetaPropertyWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  MetaPropertyWrapper* _MetaProperty = ObjectWrap::Unwrap<MetaPropertyWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _MetaProperty->MetaProperty->getPosition();
  range.setWideCol( ui );
  _MetaProperty->MetaProperty->setPosition( range );
}

void MetaPropertyWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  MetaPropertyWrapper* _MetaProperty = ObjectWrap::Unwrap<MetaPropertyWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _MetaProperty->MetaProperty->getPosition();
  range.setWideEndLine( ui );
  _MetaProperty->MetaProperty->setPosition( range );
}

void MetaPropertyWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  MetaPropertyWrapper* _MetaProperty = ObjectWrap::Unwrap<MetaPropertyWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _MetaProperty->MetaProperty->getPosition();
  range.setWideEndCol( ui );
  _MetaProperty->MetaProperty->setPosition( range );
}

}}}} //end of namespaces