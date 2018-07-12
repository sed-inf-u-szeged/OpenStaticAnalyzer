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

#include "../inc/VariableDeclarationWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> VariableDeclarationWrapper::constructor;

void VariableDeclarationWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "VariableDeclarationWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "addDeclarationsVariableDeclarator", addDeclarationsVariableDeclarator);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addCommentsComment", addCommentsComment);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKind", setKind);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "VariableDeclarationWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void VariableDeclarationWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new VariableDeclarationWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    VariableDeclarationWrapper* obj = new VariableDeclarationWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `VariableDeclarationWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


VariableDeclarationWrapper::VariableDeclarationWrapper(Factory* fact)                        
{                                                   
  VariableDeclaration = fact->getFactory()->createVariableDeclarationNode();          
}                                                   

VariableDeclarationWrapper::~VariableDeclarationWrapper()
{        
}        

void VariableDeclarationWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void VariableDeclarationWrapper::addDeclarationsVariableDeclarator(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  VariableDeclaratorWrapper* _VariableDeclarator1 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args[0]->ToObject());
  VariableDeclarationWrapper* _VariableDeclaration2 = ObjectWrap::Unwrap<VariableDeclarationWrapper>(args.This());

  _VariableDeclaration2->VariableDeclaration->addDeclarations(_VariableDeclarator1->VariableDeclarator);
}
void VariableDeclarationWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  VariableDeclarationWrapper* _VariableDeclaration2 = ObjectWrap::Unwrap<VariableDeclarationWrapper>(args.This());

  _VariableDeclaration2->VariableDeclaration->addComments(_Comment1->Comment);
}
void VariableDeclarationWrapper::setKind(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  VariableDeclarationWrapper* _VariableDeclaration = ObjectWrap::Unwrap<VariableDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  if( param == "dkVar" ){
    _VariableDeclaration->VariableDeclaration->setKind( dkVar );
  }
  if( param == "dkLet" ){
    _VariableDeclaration->VariableDeclaration->setKind( dkLet );
  }
  if( param == "dkConst" ){
    _VariableDeclaration->VariableDeclaration->setKind( dkConst );
  }
}
void VariableDeclarationWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  VariableDeclarationWrapper* _VariableDeclaration = ObjectWrap::Unwrap<VariableDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _VariableDeclaration->VariableDeclaration->getPosition();
  range.setPath( param );
  _VariableDeclaration->VariableDeclaration->setPosition( range );
}

void VariableDeclarationWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  VariableDeclarationWrapper* _VariableDeclaration = ObjectWrap::Unwrap<VariableDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _VariableDeclaration->VariableDeclaration->getPosition();
  range.setLine( ui );
  _VariableDeclaration->VariableDeclaration->setPosition( range );
}

void VariableDeclarationWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  VariableDeclarationWrapper* _VariableDeclaration = ObjectWrap::Unwrap<VariableDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _VariableDeclaration->VariableDeclaration->getPosition();
  range.setCol( ui );
  _VariableDeclaration->VariableDeclaration->setPosition( range );
}

void VariableDeclarationWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  VariableDeclarationWrapper* _VariableDeclaration = ObjectWrap::Unwrap<VariableDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _VariableDeclaration->VariableDeclaration->getPosition();
  range.setEndLine( ui );
  _VariableDeclaration->VariableDeclaration->setPosition( range );
}

void VariableDeclarationWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  VariableDeclarationWrapper* _VariableDeclaration = ObjectWrap::Unwrap<VariableDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _VariableDeclaration->VariableDeclaration->getPosition();
  range.setEndCol( ui );
  _VariableDeclaration->VariableDeclaration->setPosition( range );
}

void VariableDeclarationWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  VariableDeclarationWrapper* _VariableDeclaration = ObjectWrap::Unwrap<VariableDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _VariableDeclaration->VariableDeclaration->getPosition();
  range.setWideLine( ui );
  _VariableDeclaration->VariableDeclaration->setPosition( range );
}

void VariableDeclarationWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  VariableDeclarationWrapper* _VariableDeclaration = ObjectWrap::Unwrap<VariableDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _VariableDeclaration->VariableDeclaration->getPosition();
  range.setWideCol( ui );
  _VariableDeclaration->VariableDeclaration->setPosition( range );
}

void VariableDeclarationWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  VariableDeclarationWrapper* _VariableDeclaration = ObjectWrap::Unwrap<VariableDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _VariableDeclaration->VariableDeclaration->getPosition();
  range.setWideEndLine( ui );
  _VariableDeclaration->VariableDeclaration->setPosition( range );
}

void VariableDeclarationWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  VariableDeclarationWrapper* _VariableDeclaration = ObjectWrap::Unwrap<VariableDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _VariableDeclaration->VariableDeclaration->getPosition();
  range.setWideEndCol( ui );
  _VariableDeclaration->VariableDeclaration->setPosition( range );
}

}}}} //end of namespaces