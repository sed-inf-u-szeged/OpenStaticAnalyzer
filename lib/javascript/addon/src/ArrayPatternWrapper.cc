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

#include "../inc/ArrayPatternWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> ArrayPatternWrapper::constructor;

void ArrayPatternWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "ArrayPatternWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsIdentifier", addElementsIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsMemberExpression", addElementsMemberExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsArrayPattern", addElementsArrayPattern);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsAssignmentPattern", addElementsAssignmentPattern);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsObjectPattern", addElementsObjectPattern);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsRestElement", addElementsRestElement);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "ArrayPatternWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void ArrayPatternWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new ArrayPatternWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    ArrayPatternWrapper* obj = new ArrayPatternWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `ArrayPatternWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


ArrayPatternWrapper::ArrayPatternWrapper(Factory* fact)                        
{                                                   
  ArrayPattern = fact->getFactory()->createArrayPatternNode();          
}                                                   

ArrayPatternWrapper::~ArrayPatternWrapper()
{        
}        

void ArrayPatternWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void ArrayPatternWrapper::addElementsIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  ArrayPatternWrapper* _ArrayPattern2 = ObjectWrap::Unwrap<ArrayPatternWrapper>(args.This());

  _ArrayPattern2->ArrayPattern->addElements(_Identifier1->Identifier);
}
void ArrayPatternWrapper::addElementsMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  ArrayPatternWrapper* _ArrayPattern2 = ObjectWrap::Unwrap<ArrayPatternWrapper>(args.This());

  _ArrayPattern2->ArrayPattern->addElements(_MemberExpression1->MemberExpression);
}
void ArrayPatternWrapper::addElementsArrayPattern(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayPatternWrapper* _ArrayPattern1 = ObjectWrap::Unwrap<ArrayPatternWrapper>(args[0]->ToObject());
  ArrayPatternWrapper* _ArrayPattern2 = ObjectWrap::Unwrap<ArrayPatternWrapper>(args.This());

  _ArrayPattern2->ArrayPattern->addElements(_ArrayPattern1->ArrayPattern);
}
void ArrayPatternWrapper::addElementsAssignmentPattern(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentPatternWrapper* _AssignmentPattern1 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args[0]->ToObject());
  ArrayPatternWrapper* _ArrayPattern2 = ObjectWrap::Unwrap<ArrayPatternWrapper>(args.This());

  _ArrayPattern2->ArrayPattern->addElements(_AssignmentPattern1->AssignmentPattern);
}
void ArrayPatternWrapper::addElementsObjectPattern(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectPatternWrapper* _ObjectPattern1 = ObjectWrap::Unwrap<ObjectPatternWrapper>(args[0]->ToObject());
  ArrayPatternWrapper* _ArrayPattern2 = ObjectWrap::Unwrap<ArrayPatternWrapper>(args.This());

  _ArrayPattern2->ArrayPattern->addElements(_ObjectPattern1->ObjectPattern);
}
void ArrayPatternWrapper::addElementsRestElement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RestElementWrapper* _RestElement1 = ObjectWrap::Unwrap<RestElementWrapper>(args[0]->ToObject());
  ArrayPatternWrapper* _ArrayPattern2 = ObjectWrap::Unwrap<ArrayPatternWrapper>(args.This());

  _ArrayPattern2->ArrayPattern->addElements(_RestElement1->RestElement);
}
void ArrayPatternWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  ArrayPatternWrapper* _ArrayPattern2 = ObjectWrap::Unwrap<ArrayPatternWrapper>(args.This());

  _ArrayPattern2->ArrayPattern->addComments(_Comment1->Comment);
}
void ArrayPatternWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  ArrayPatternWrapper* _ArrayPattern = ObjectWrap::Unwrap<ArrayPatternWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _ArrayPattern->ArrayPattern->getPosition();
  range.setPath( param );
  _ArrayPattern->ArrayPattern->setPosition( range );
}

void ArrayPatternWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ArrayPatternWrapper* _ArrayPattern = ObjectWrap::Unwrap<ArrayPatternWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ArrayPattern->ArrayPattern->getPosition();
  range.setLine( ui );
  _ArrayPattern->ArrayPattern->setPosition( range );
}

void ArrayPatternWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ArrayPatternWrapper* _ArrayPattern = ObjectWrap::Unwrap<ArrayPatternWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ArrayPattern->ArrayPattern->getPosition();
  range.setCol( ui );
  _ArrayPattern->ArrayPattern->setPosition( range );
}

void ArrayPatternWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ArrayPatternWrapper* _ArrayPattern = ObjectWrap::Unwrap<ArrayPatternWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ArrayPattern->ArrayPattern->getPosition();
  range.setEndLine( ui );
  _ArrayPattern->ArrayPattern->setPosition( range );
}

void ArrayPatternWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ArrayPatternWrapper* _ArrayPattern = ObjectWrap::Unwrap<ArrayPatternWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ArrayPattern->ArrayPattern->getPosition();
  range.setEndCol( ui );
  _ArrayPattern->ArrayPattern->setPosition( range );
}

void ArrayPatternWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ArrayPatternWrapper* _ArrayPattern = ObjectWrap::Unwrap<ArrayPatternWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ArrayPattern->ArrayPattern->getPosition();
  range.setWideLine( ui );
  _ArrayPattern->ArrayPattern->setPosition( range );
}

void ArrayPatternWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ArrayPatternWrapper* _ArrayPattern = ObjectWrap::Unwrap<ArrayPatternWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ArrayPattern->ArrayPattern->getPosition();
  range.setWideCol( ui );
  _ArrayPattern->ArrayPattern->setPosition( range );
}

void ArrayPatternWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ArrayPatternWrapper* _ArrayPattern = ObjectWrap::Unwrap<ArrayPatternWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ArrayPattern->ArrayPattern->getPosition();
  range.setWideEndLine( ui );
  _ArrayPattern->ArrayPattern->setPosition( range );
}

void ArrayPatternWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ArrayPatternWrapper* _ArrayPattern = ObjectWrap::Unwrap<ArrayPatternWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ArrayPattern->ArrayPattern->getPosition();
  range.setWideEndCol( ui );
  _ArrayPattern->ArrayPattern->setPosition( range );
}

}}}} //end of namespaces