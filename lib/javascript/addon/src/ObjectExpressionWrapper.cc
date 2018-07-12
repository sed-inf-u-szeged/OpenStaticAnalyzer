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

#include "../inc/ObjectExpressionWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> ObjectExpressionWrapper::constructor;

void ObjectExpressionWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "ObjectExpressionWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "addPropertiesProperty", addPropertiesProperty);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addPropertiesAssignmentProperty", addPropertiesAssignmentProperty);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "ObjectExpressionWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void ObjectExpressionWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new ObjectExpressionWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    ObjectExpressionWrapper* obj = new ObjectExpressionWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `ObjectExpressionWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


ObjectExpressionWrapper::ObjectExpressionWrapper(Factory* fact)                        
{                                                   
  ObjectExpression = fact->getFactory()->createObjectExpressionNode();          
}                                                   

ObjectExpressionWrapper::~ObjectExpressionWrapper()
{        
}        

void ObjectExpressionWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void ObjectExpressionWrapper::addPropertiesProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  PropertyWrapper* _Property1 = ObjectWrap::Unwrap<PropertyWrapper>(args[0]->ToObject());
  ObjectExpressionWrapper* _ObjectExpression2 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args.This());

  _ObjectExpression2->ObjectExpression->addProperties(_Property1->Property);
}
void ObjectExpressionWrapper::addPropertiesAssignmentProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentPropertyWrapper* _AssignmentProperty1 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args[0]->ToObject());
  ObjectExpressionWrapper* _ObjectExpression2 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args.This());

  _ObjectExpression2->ObjectExpression->addProperties(_AssignmentProperty1->AssignmentProperty);
}
void ObjectExpressionWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  ObjectExpressionWrapper* _ObjectExpression2 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args.This());

  _ObjectExpression2->ObjectExpression->addComments(_Comment1->Comment);
}
void ObjectExpressionWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  ObjectExpressionWrapper* _ObjectExpression = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _ObjectExpression->ObjectExpression->getPosition();
  range.setPath( param );
  _ObjectExpression->ObjectExpression->setPosition( range );
}

void ObjectExpressionWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ObjectExpressionWrapper* _ObjectExpression = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ObjectExpression->ObjectExpression->getPosition();
  range.setLine( ui );
  _ObjectExpression->ObjectExpression->setPosition( range );
}

void ObjectExpressionWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ObjectExpressionWrapper* _ObjectExpression = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ObjectExpression->ObjectExpression->getPosition();
  range.setCol( ui );
  _ObjectExpression->ObjectExpression->setPosition( range );
}

void ObjectExpressionWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ObjectExpressionWrapper* _ObjectExpression = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ObjectExpression->ObjectExpression->getPosition();
  range.setEndLine( ui );
  _ObjectExpression->ObjectExpression->setPosition( range );
}

void ObjectExpressionWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ObjectExpressionWrapper* _ObjectExpression = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ObjectExpression->ObjectExpression->getPosition();
  range.setEndCol( ui );
  _ObjectExpression->ObjectExpression->setPosition( range );
}

void ObjectExpressionWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ObjectExpressionWrapper* _ObjectExpression = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ObjectExpression->ObjectExpression->getPosition();
  range.setWideLine( ui );
  _ObjectExpression->ObjectExpression->setPosition( range );
}

void ObjectExpressionWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ObjectExpressionWrapper* _ObjectExpression = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ObjectExpression->ObjectExpression->getPosition();
  range.setWideCol( ui );
  _ObjectExpression->ObjectExpression->setPosition( range );
}

void ObjectExpressionWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ObjectExpressionWrapper* _ObjectExpression = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ObjectExpression->ObjectExpression->getPosition();
  range.setWideEndLine( ui );
  _ObjectExpression->ObjectExpression->setPosition( range );
}

void ObjectExpressionWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ObjectExpressionWrapper* _ObjectExpression = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ObjectExpression->ObjectExpression->getPosition();
  range.setWideEndCol( ui );
  _ObjectExpression->ObjectExpression->setPosition( range );
}

}}}} //end of namespaces