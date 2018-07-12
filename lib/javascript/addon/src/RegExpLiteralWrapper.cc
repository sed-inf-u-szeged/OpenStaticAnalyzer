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

#include "../inc/RegExpLiteralWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> RegExpLiteralWrapper::constructor;

void RegExpLiteralWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "RegExpLiteralWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "addCommentsComment", addCommentsComment);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPattern", setPattern);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setFlags", setFlags);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "RegExpLiteralWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void RegExpLiteralWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new RegExpLiteralWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    RegExpLiteralWrapper* obj = new RegExpLiteralWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `RegExpLiteralWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


RegExpLiteralWrapper::RegExpLiteralWrapper(Factory* fact)                        
{                                                   
  RegExpLiteral = fact->getFactory()->createRegExpLiteralNode();          
}                                                   

RegExpLiteralWrapper::~RegExpLiteralWrapper()
{        
}        

void RegExpLiteralWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void RegExpLiteralWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  RegExpLiteralWrapper* _RegExpLiteral2 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args.This());

  _RegExpLiteral2->RegExpLiteral->addComments(_Comment1->Comment);
}
void RegExpLiteralWrapper::setPattern(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  RegExpLiteralWrapper* _RegExpLiteral = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  _RegExpLiteral->RegExpLiteral->setPattern( param );
}
void RegExpLiteralWrapper::setFlags(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  RegExpLiteralWrapper* _RegExpLiteral = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  _RegExpLiteral->RegExpLiteral->setFlags( param );
}
void RegExpLiteralWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  RegExpLiteralWrapper* _RegExpLiteral = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _RegExpLiteral->RegExpLiteral->getPosition();
  range.setPath( param );
  _RegExpLiteral->RegExpLiteral->setPosition( range );
}

void RegExpLiteralWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  RegExpLiteralWrapper* _RegExpLiteral = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _RegExpLiteral->RegExpLiteral->getPosition();
  range.setLine( ui );
  _RegExpLiteral->RegExpLiteral->setPosition( range );
}

void RegExpLiteralWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  RegExpLiteralWrapper* _RegExpLiteral = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _RegExpLiteral->RegExpLiteral->getPosition();
  range.setCol( ui );
  _RegExpLiteral->RegExpLiteral->setPosition( range );
}

void RegExpLiteralWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  RegExpLiteralWrapper* _RegExpLiteral = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _RegExpLiteral->RegExpLiteral->getPosition();
  range.setEndLine( ui );
  _RegExpLiteral->RegExpLiteral->setPosition( range );
}

void RegExpLiteralWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  RegExpLiteralWrapper* _RegExpLiteral = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _RegExpLiteral->RegExpLiteral->getPosition();
  range.setEndCol( ui );
  _RegExpLiteral->RegExpLiteral->setPosition( range );
}

void RegExpLiteralWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  RegExpLiteralWrapper* _RegExpLiteral = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _RegExpLiteral->RegExpLiteral->getPosition();
  range.setWideLine( ui );
  _RegExpLiteral->RegExpLiteral->setPosition( range );
}

void RegExpLiteralWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  RegExpLiteralWrapper* _RegExpLiteral = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _RegExpLiteral->RegExpLiteral->getPosition();
  range.setWideCol( ui );
  _RegExpLiteral->RegExpLiteral->setPosition( range );
}

void RegExpLiteralWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  RegExpLiteralWrapper* _RegExpLiteral = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _RegExpLiteral->RegExpLiteral->getPosition();
  range.setWideEndLine( ui );
  _RegExpLiteral->RegExpLiteral->setPosition( range );
}

void RegExpLiteralWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  RegExpLiteralWrapper* _RegExpLiteral = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _RegExpLiteral->RegExpLiteral->getPosition();
  range.setWideEndCol( ui );
  _RegExpLiteral->RegExpLiteral->setPosition( range );
}

void RegExpLiteralWrapper::setRaw(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  RegExpLiteralWrapper* _RegExpLiteral = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  _RegExpLiteral->RegExpLiteral->setRaw( param );
}
}}}} //end of namespaces