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

#include "../inc/BooleanLiteralWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> BooleanLiteralWrapper::constructor;

void BooleanLiteralWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "BooleanLiteralWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "addCommentsComment", addCommentsComment);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setValue", setValue);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPath", setPath);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLine", setLine);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setCol", setCol);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setEndLine", setEndLine);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setEndCol", setEndCol);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setWideLine", setWideLine);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setWideCol", setWideCol);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setWideEndLine", setWideEndLine);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setWideEndCol", setWideEndCol);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRaw", setRaw);
                                                                           
  constructor.Reset(isolate, tpl->GetFunction());                          
  exports->Set(v8::String::NewFromUtf8(isolate, "BooleanLiteralWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void BooleanLiteralWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new BooleanLiteralWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    BooleanLiteralWrapper* obj = new BooleanLiteralWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `BooleanLiteralWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


BooleanLiteralWrapper::BooleanLiteralWrapper(Factory* fact)                        
{                                                   
  BooleanLiteral = fact->getFactory()->createBooleanLiteralNode();          
}                                                   

BooleanLiteralWrapper::~BooleanLiteralWrapper()
{        
}        

void BooleanLiteralWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void BooleanLiteralWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  BooleanLiteralWrapper* _BooleanLiteral2 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args.This());

  _BooleanLiteral2->BooleanLiteral->addComments(_Comment1->Comment);
}
void BooleanLiteralWrapper::setValue(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  BooleanLiteralWrapper* _BooleanLiteral = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::transform(param.begin(), param.end(), param.begin(), ::tolower);
  std::istringstream is(param);                                    
  bool b;                                                        
  is >> std::boolalpha >> b;                                     
  _BooleanLiteral->BooleanLiteral->setValue( b );
}
void BooleanLiteralWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  BooleanLiteralWrapper* _BooleanLiteral = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _BooleanLiteral->BooleanLiteral->getPosition();
  range.setPath( param );
  _BooleanLiteral->BooleanLiteral->setPosition( range );
}

void BooleanLiteralWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  BooleanLiteralWrapper* _BooleanLiteral = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _BooleanLiteral->BooleanLiteral->getPosition();
  range.setLine( ui );
  _BooleanLiteral->BooleanLiteral->setPosition( range );
}

void BooleanLiteralWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  BooleanLiteralWrapper* _BooleanLiteral = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _BooleanLiteral->BooleanLiteral->getPosition();
  range.setCol( ui );
  _BooleanLiteral->BooleanLiteral->setPosition( range );
}

void BooleanLiteralWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  BooleanLiteralWrapper* _BooleanLiteral = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _BooleanLiteral->BooleanLiteral->getPosition();
  range.setEndLine( ui );
  _BooleanLiteral->BooleanLiteral->setPosition( range );
}

void BooleanLiteralWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  BooleanLiteralWrapper* _BooleanLiteral = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _BooleanLiteral->BooleanLiteral->getPosition();
  range.setEndCol( ui );
  _BooleanLiteral->BooleanLiteral->setPosition( range );
}

void BooleanLiteralWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  BooleanLiteralWrapper* _BooleanLiteral = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _BooleanLiteral->BooleanLiteral->getPosition();
  range.setWideLine( ui );
  _BooleanLiteral->BooleanLiteral->setPosition( range );
}

void BooleanLiteralWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  BooleanLiteralWrapper* _BooleanLiteral = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _BooleanLiteral->BooleanLiteral->getPosition();
  range.setWideCol( ui );
  _BooleanLiteral->BooleanLiteral->setPosition( range );
}

void BooleanLiteralWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  BooleanLiteralWrapper* _BooleanLiteral = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _BooleanLiteral->BooleanLiteral->getPosition();
  range.setWideEndLine( ui );
  _BooleanLiteral->BooleanLiteral->setPosition( range );
}

void BooleanLiteralWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  BooleanLiteralWrapper* _BooleanLiteral = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _BooleanLiteral->BooleanLiteral->getPosition();
  range.setWideEndCol( ui );
  _BooleanLiteral->BooleanLiteral->setPosition( range );
}

void BooleanLiteralWrapper::setRaw(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  BooleanLiteralWrapper* _BooleanLiteral = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  _BooleanLiteral->BooleanLiteral->setRaw( param );
}
}}}} //end of namespaces