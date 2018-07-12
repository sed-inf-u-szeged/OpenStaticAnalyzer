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

#include "../inc/IdentifierWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> IdentifierWrapper::constructor;

void IdentifierWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "IdentifierWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRefersToIdentifier", setRefersToIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRefersToMemberExpression", setRefersToMemberExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRefersToArrayPattern", setRefersToArrayPattern);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRefersToAssignmentPattern", setRefersToAssignmentPattern);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRefersToObjectPattern", setRefersToObjectPattern);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRefersToRestElement", setRefersToRestElement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRefersToVariableDeclarator", setRefersToVariableDeclarator);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRefersToFunction", setRefersToFunction);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRefersToFunctionDeclaration", setRefersToFunctionDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRefersToArrowFunctionExpression", setRefersToArrowFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRefersToFunctionExpression", setRefersToFunctionExpression);
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
  NODE_SET_PROTOTYPE_METHOD(tpl, "setName", setName);
                                                                           
  constructor.Reset(isolate, tpl->GetFunction());                          
  exports->Set(v8::String::NewFromUtf8(isolate, "IdentifierWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void IdentifierWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new IdentifierWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    IdentifierWrapper* obj = new IdentifierWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `IdentifierWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


IdentifierWrapper::IdentifierWrapper(Factory* fact)                        
{                                                   
  Identifier = fact->getFactory()->createIdentifierNode();          
}                                                   

IdentifierWrapper::~IdentifierWrapper()
{        
}        

void IdentifierWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void IdentifierWrapper::setRefersToIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  IdentifierWrapper* _Identifier2 = ObjectWrap::Unwrap<IdentifierWrapper>(args.This());

  _Identifier2->Identifier->setRefersTo(_Identifier1->Identifier);
}
void IdentifierWrapper::setRefersToMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  IdentifierWrapper* _Identifier2 = ObjectWrap::Unwrap<IdentifierWrapper>(args.This());

  _Identifier2->Identifier->setRefersTo(_MemberExpression1->MemberExpression);
}
void IdentifierWrapper::setRefersToArrayPattern(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayPatternWrapper* _ArrayPattern1 = ObjectWrap::Unwrap<ArrayPatternWrapper>(args[0]->ToObject());
  IdentifierWrapper* _Identifier2 = ObjectWrap::Unwrap<IdentifierWrapper>(args.This());

  _Identifier2->Identifier->setRefersTo(_ArrayPattern1->ArrayPattern);
}
void IdentifierWrapper::setRefersToAssignmentPattern(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentPatternWrapper* _AssignmentPattern1 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args[0]->ToObject());
  IdentifierWrapper* _Identifier2 = ObjectWrap::Unwrap<IdentifierWrapper>(args.This());

  _Identifier2->Identifier->setRefersTo(_AssignmentPattern1->AssignmentPattern);
}
void IdentifierWrapper::setRefersToObjectPattern(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectPatternWrapper* _ObjectPattern1 = ObjectWrap::Unwrap<ObjectPatternWrapper>(args[0]->ToObject());
  IdentifierWrapper* _Identifier2 = ObjectWrap::Unwrap<IdentifierWrapper>(args.This());

  _Identifier2->Identifier->setRefersTo(_ObjectPattern1->ObjectPattern);
}
void IdentifierWrapper::setRefersToRestElement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RestElementWrapper* _RestElement1 = ObjectWrap::Unwrap<RestElementWrapper>(args[0]->ToObject());
  IdentifierWrapper* _Identifier2 = ObjectWrap::Unwrap<IdentifierWrapper>(args.This());

  _Identifier2->Identifier->setRefersTo(_RestElement1->RestElement);
}
void IdentifierWrapper::setRefersToVariableDeclarator(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  VariableDeclaratorWrapper* _VariableDeclarator1 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args[0]->ToObject());
  IdentifierWrapper* _Identifier2 = ObjectWrap::Unwrap<IdentifierWrapper>(args.This());

  _Identifier2->Identifier->setRefersTo(_VariableDeclarator1->VariableDeclarator);
}
void IdentifierWrapper::setRefersToFunction(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionWrapper* _Function1 = ObjectWrap::Unwrap<FunctionWrapper>(args[0]->ToObject());
  IdentifierWrapper* _Identifier2 = ObjectWrap::Unwrap<IdentifierWrapper>(args.This());

  _Identifier2->Identifier->setRefersTo(_Function1->Function);
}
void IdentifierWrapper::setRefersToFunctionDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionDeclarationWrapper* _FunctionDeclaration1 = ObjectWrap::Unwrap<FunctionDeclarationWrapper>(args[0]->ToObject());
  IdentifierWrapper* _Identifier2 = ObjectWrap::Unwrap<IdentifierWrapper>(args.This());

  _Identifier2->Identifier->setRefersTo(_FunctionDeclaration1->FunctionDeclaration);
}
void IdentifierWrapper::setRefersToArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  IdentifierWrapper* _Identifier2 = ObjectWrap::Unwrap<IdentifierWrapper>(args.This());

  _Identifier2->Identifier->setRefersTo(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void IdentifierWrapper::setRefersToFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  IdentifierWrapper* _Identifier2 = ObjectWrap::Unwrap<IdentifierWrapper>(args.This());

  _Identifier2->Identifier->setRefersTo(_FunctionExpression1->FunctionExpression);
}
void IdentifierWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  IdentifierWrapper* _Identifier2 = ObjectWrap::Unwrap<IdentifierWrapper>(args.This());

  _Identifier2->Identifier->addComments(_Comment1->Comment);
}
void IdentifierWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  IdentifierWrapper* _Identifier = ObjectWrap::Unwrap<IdentifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _Identifier->Identifier->getPosition();
  range.setPath( param );
  _Identifier->Identifier->setPosition( range );
}

void IdentifierWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  IdentifierWrapper* _Identifier = ObjectWrap::Unwrap<IdentifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _Identifier->Identifier->getPosition();
  range.setLine( ui );
  _Identifier->Identifier->setPosition( range );
}

void IdentifierWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  IdentifierWrapper* _Identifier = ObjectWrap::Unwrap<IdentifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _Identifier->Identifier->getPosition();
  range.setCol( ui );
  _Identifier->Identifier->setPosition( range );
}

void IdentifierWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  IdentifierWrapper* _Identifier = ObjectWrap::Unwrap<IdentifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _Identifier->Identifier->getPosition();
  range.setEndLine( ui );
  _Identifier->Identifier->setPosition( range );
}

void IdentifierWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  IdentifierWrapper* _Identifier = ObjectWrap::Unwrap<IdentifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _Identifier->Identifier->getPosition();
  range.setEndCol( ui );
  _Identifier->Identifier->setPosition( range );
}

void IdentifierWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  IdentifierWrapper* _Identifier = ObjectWrap::Unwrap<IdentifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _Identifier->Identifier->getPosition();
  range.setWideLine( ui );
  _Identifier->Identifier->setPosition( range );
}

void IdentifierWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  IdentifierWrapper* _Identifier = ObjectWrap::Unwrap<IdentifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _Identifier->Identifier->getPosition();
  range.setWideCol( ui );
  _Identifier->Identifier->setPosition( range );
}

void IdentifierWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  IdentifierWrapper* _Identifier = ObjectWrap::Unwrap<IdentifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _Identifier->Identifier->getPosition();
  range.setWideEndLine( ui );
  _Identifier->Identifier->setPosition( range );
}

void IdentifierWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  IdentifierWrapper* _Identifier = ObjectWrap::Unwrap<IdentifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _Identifier->Identifier->getPosition();
  range.setWideEndCol( ui );
  _Identifier->Identifier->setPosition( range );
}

void IdentifierWrapper::setName(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  IdentifierWrapper* _Identifier = ObjectWrap::Unwrap<IdentifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  _Identifier->Identifier->setName( param );
}
}}}} //end of namespaces