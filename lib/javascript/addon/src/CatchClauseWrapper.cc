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

#include "../inc/CatchClauseWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> CatchClauseWrapper::constructor;

void CatchClauseWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "CatchClauseWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "setParamIdentifier", setParamIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setParamMemberExpression", setParamMemberExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setParamArrayPattern", setParamArrayPattern);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setParamAssignmentPattern", setParamAssignmentPattern);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setParamObjectPattern", setParamObjectPattern);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setParamRestElement", setParamRestElement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyBlockStatement", setBodyBlockStatement);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "CatchClauseWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void CatchClauseWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new CatchClauseWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    CatchClauseWrapper* obj = new CatchClauseWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `CatchClauseWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


CatchClauseWrapper::CatchClauseWrapper(Factory* fact)                        
{                                                   
  CatchClause = fact->getFactory()->createCatchClauseNode();          
}                                                   

CatchClauseWrapper::~CatchClauseWrapper()
{        
}        

void CatchClauseWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void CatchClauseWrapper::setParamIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  CatchClauseWrapper* _CatchClause2 = ObjectWrap::Unwrap<CatchClauseWrapper>(args.This());

  _CatchClause2->CatchClause->setParam(_Identifier1->Identifier);
}
void CatchClauseWrapper::setParamMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  CatchClauseWrapper* _CatchClause2 = ObjectWrap::Unwrap<CatchClauseWrapper>(args.This());

  _CatchClause2->CatchClause->setParam(_MemberExpression1->MemberExpression);
}
void CatchClauseWrapper::setParamArrayPattern(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayPatternWrapper* _ArrayPattern1 = ObjectWrap::Unwrap<ArrayPatternWrapper>(args[0]->ToObject());
  CatchClauseWrapper* _CatchClause2 = ObjectWrap::Unwrap<CatchClauseWrapper>(args.This());

  _CatchClause2->CatchClause->setParam(_ArrayPattern1->ArrayPattern);
}
void CatchClauseWrapper::setParamAssignmentPattern(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentPatternWrapper* _AssignmentPattern1 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args[0]->ToObject());
  CatchClauseWrapper* _CatchClause2 = ObjectWrap::Unwrap<CatchClauseWrapper>(args.This());

  _CatchClause2->CatchClause->setParam(_AssignmentPattern1->AssignmentPattern);
}
void CatchClauseWrapper::setParamObjectPattern(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectPatternWrapper* _ObjectPattern1 = ObjectWrap::Unwrap<ObjectPatternWrapper>(args[0]->ToObject());
  CatchClauseWrapper* _CatchClause2 = ObjectWrap::Unwrap<CatchClauseWrapper>(args.This());

  _CatchClause2->CatchClause->setParam(_ObjectPattern1->ObjectPattern);
}
void CatchClauseWrapper::setParamRestElement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RestElementWrapper* _RestElement1 = ObjectWrap::Unwrap<RestElementWrapper>(args[0]->ToObject());
  CatchClauseWrapper* _CatchClause2 = ObjectWrap::Unwrap<CatchClauseWrapper>(args.This());

  _CatchClause2->CatchClause->setParam(_RestElement1->RestElement);
}
void CatchClauseWrapper::setBodyBlockStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BlockStatementWrapper* _BlockStatement1 = ObjectWrap::Unwrap<BlockStatementWrapper>(args[0]->ToObject());
  CatchClauseWrapper* _CatchClause2 = ObjectWrap::Unwrap<CatchClauseWrapper>(args.This());

  _CatchClause2->CatchClause->setBody(_BlockStatement1->BlockStatement);
}
void CatchClauseWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  CatchClauseWrapper* _CatchClause2 = ObjectWrap::Unwrap<CatchClauseWrapper>(args.This());

  _CatchClause2->CatchClause->addComments(_Comment1->Comment);
}
void CatchClauseWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  CatchClauseWrapper* _CatchClause = ObjectWrap::Unwrap<CatchClauseWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _CatchClause->CatchClause->getPosition();
  range.setPath( param );
  _CatchClause->CatchClause->setPosition( range );
}

void CatchClauseWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  CatchClauseWrapper* _CatchClause = ObjectWrap::Unwrap<CatchClauseWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _CatchClause->CatchClause->getPosition();
  range.setLine( ui );
  _CatchClause->CatchClause->setPosition( range );
}

void CatchClauseWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  CatchClauseWrapper* _CatchClause = ObjectWrap::Unwrap<CatchClauseWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _CatchClause->CatchClause->getPosition();
  range.setCol( ui );
  _CatchClause->CatchClause->setPosition( range );
}

void CatchClauseWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  CatchClauseWrapper* _CatchClause = ObjectWrap::Unwrap<CatchClauseWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _CatchClause->CatchClause->getPosition();
  range.setEndLine( ui );
  _CatchClause->CatchClause->setPosition( range );
}

void CatchClauseWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  CatchClauseWrapper* _CatchClause = ObjectWrap::Unwrap<CatchClauseWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _CatchClause->CatchClause->getPosition();
  range.setEndCol( ui );
  _CatchClause->CatchClause->setPosition( range );
}

void CatchClauseWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  CatchClauseWrapper* _CatchClause = ObjectWrap::Unwrap<CatchClauseWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _CatchClause->CatchClause->getPosition();
  range.setWideLine( ui );
  _CatchClause->CatchClause->setPosition( range );
}

void CatchClauseWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  CatchClauseWrapper* _CatchClause = ObjectWrap::Unwrap<CatchClauseWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _CatchClause->CatchClause->getPosition();
  range.setWideCol( ui );
  _CatchClause->CatchClause->setPosition( range );
}

void CatchClauseWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  CatchClauseWrapper* _CatchClause = ObjectWrap::Unwrap<CatchClauseWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _CatchClause->CatchClause->getPosition();
  range.setWideEndLine( ui );
  _CatchClause->CatchClause->setPosition( range );
}

void CatchClauseWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  CatchClauseWrapper* _CatchClause = ObjectWrap::Unwrap<CatchClauseWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _CatchClause->CatchClause->getPosition();
  range.setWideEndCol( ui );
  _CatchClause->CatchClause->setPosition( range );
}

}}}} //end of namespaces