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

#include "../inc/ObjectPatternWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> ObjectPatternWrapper::constructor;

void ObjectPatternWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "ObjectPatternWrapper"));             
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
  exports->Set(v8::String::NewFromUtf8(isolate, "ObjectPatternWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void ObjectPatternWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new ObjectPatternWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    ObjectPatternWrapper* obj = new ObjectPatternWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `ObjectPatternWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


ObjectPatternWrapper::ObjectPatternWrapper(Factory* fact)                        
{                                                   
  ObjectPattern = fact->getFactory()->createObjectPatternNode();          
}                                                   

ObjectPatternWrapper::~ObjectPatternWrapper()
{        
}        

void ObjectPatternWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void ObjectPatternWrapper::addPropertiesProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  PropertyWrapper* _Property1 = ObjectWrap::Unwrap<PropertyWrapper>(args[0]->ToObject());
  ObjectPatternWrapper* _ObjectPattern2 = ObjectWrap::Unwrap<ObjectPatternWrapper>(args.This());

  _ObjectPattern2->ObjectPattern->addProperties(_Property1->Property);
}
void ObjectPatternWrapper::addPropertiesAssignmentProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentPropertyWrapper* _AssignmentProperty1 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args[0]->ToObject());
  ObjectPatternWrapper* _ObjectPattern2 = ObjectWrap::Unwrap<ObjectPatternWrapper>(args.This());

  _ObjectPattern2->ObjectPattern->addProperties(_AssignmentProperty1->AssignmentProperty);
}
void ObjectPatternWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  ObjectPatternWrapper* _ObjectPattern2 = ObjectWrap::Unwrap<ObjectPatternWrapper>(args.This());

  _ObjectPattern2->ObjectPattern->addComments(_Comment1->Comment);
}
void ObjectPatternWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  ObjectPatternWrapper* _ObjectPattern = ObjectWrap::Unwrap<ObjectPatternWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _ObjectPattern->ObjectPattern->getPosition();
  range.setPath( param );
  _ObjectPattern->ObjectPattern->setPosition( range );
}

void ObjectPatternWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ObjectPatternWrapper* _ObjectPattern = ObjectWrap::Unwrap<ObjectPatternWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ObjectPattern->ObjectPattern->getPosition();
  range.setLine( ui );
  _ObjectPattern->ObjectPattern->setPosition( range );
}

void ObjectPatternWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ObjectPatternWrapper* _ObjectPattern = ObjectWrap::Unwrap<ObjectPatternWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ObjectPattern->ObjectPattern->getPosition();
  range.setCol( ui );
  _ObjectPattern->ObjectPattern->setPosition( range );
}

void ObjectPatternWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ObjectPatternWrapper* _ObjectPattern = ObjectWrap::Unwrap<ObjectPatternWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ObjectPattern->ObjectPattern->getPosition();
  range.setEndLine( ui );
  _ObjectPattern->ObjectPattern->setPosition( range );
}

void ObjectPatternWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ObjectPatternWrapper* _ObjectPattern = ObjectWrap::Unwrap<ObjectPatternWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ObjectPattern->ObjectPattern->getPosition();
  range.setEndCol( ui );
  _ObjectPattern->ObjectPattern->setPosition( range );
}

void ObjectPatternWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ObjectPatternWrapper* _ObjectPattern = ObjectWrap::Unwrap<ObjectPatternWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ObjectPattern->ObjectPattern->getPosition();
  range.setWideLine( ui );
  _ObjectPattern->ObjectPattern->setPosition( range );
}

void ObjectPatternWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ObjectPatternWrapper* _ObjectPattern = ObjectWrap::Unwrap<ObjectPatternWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ObjectPattern->ObjectPattern->getPosition();
  range.setWideCol( ui );
  _ObjectPattern->ObjectPattern->setPosition( range );
}

void ObjectPatternWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ObjectPatternWrapper* _ObjectPattern = ObjectWrap::Unwrap<ObjectPatternWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ObjectPattern->ObjectPattern->getPosition();
  range.setWideEndLine( ui );
  _ObjectPattern->ObjectPattern->setPosition( range );
}

void ObjectPatternWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ObjectPatternWrapper* _ObjectPattern = ObjectWrap::Unwrap<ObjectPatternWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ObjectPattern->ObjectPattern->getPosition();
  range.setWideEndCol( ui );
  _ObjectPattern->ObjectPattern->setPosition( range );
}

}}}} //end of namespaces