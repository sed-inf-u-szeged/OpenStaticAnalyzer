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

#include "../inc/LabeledStatementWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> LabeledStatementWrapper::constructor;

void LabeledStatementWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "LabeledStatementWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLabelIdentifier", setLabelIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyClassDeclaration", setBodyClassDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyExportAllDeclaration", setBodyExportAllDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyExportDefaultDeclaration", setBodyExportDefaultDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyFunctionDeclaration", setBodyFunctionDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyVariableDeclaration", setBodyVariableDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyBlockStatement", setBodyBlockStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyBreakStatement", setBodyBreakStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyContinueStatement", setBodyContinueStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyDebuggerStatement", setBodyDebuggerStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyEmptyStatement", setBodyEmptyStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyExpressionStatement", setBodyExpressionStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyForInStatement", setBodyForInStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyForOfStatement", setBodyForOfStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyForStatement", setBodyForStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyIfStatement", setBodyIfStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyLabeledStatement", setBodyLabeledStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyReturnStatement", setBodyReturnStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodySwitchStatement", setBodySwitchStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyThrowStatement", setBodyThrowStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyTryStatement", setBodyTryStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyWhileStatement", setBodyWhileStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyDoWhileStatement", setBodyDoWhileStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyWithStatement", setBodyWithStatement);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "LabeledStatementWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void LabeledStatementWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new LabeledStatementWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    LabeledStatementWrapper* obj = new LabeledStatementWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `LabeledStatementWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


LabeledStatementWrapper::LabeledStatementWrapper(Factory* fact)                        
{                                                   
  LabeledStatement = fact->getFactory()->createLabeledStatementNode();          
}                                                   

LabeledStatementWrapper::~LabeledStatementWrapper()
{        
}        

void LabeledStatementWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void LabeledStatementWrapper::setLabelIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  LabeledStatementWrapper* _LabeledStatement2 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());

  _LabeledStatement2->LabeledStatement->setLabel(_Identifier1->Identifier);
}
void LabeledStatementWrapper::setBodyClassDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassDeclarationWrapper* _ClassDeclaration1 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args[0]->ToObject());
  LabeledStatementWrapper* _LabeledStatement2 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());

  _LabeledStatement2->LabeledStatement->setBody(_ClassDeclaration1->ClassDeclaration);
}
void LabeledStatementWrapper::setBodyExportAllDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExportAllDeclarationWrapper* _ExportAllDeclaration1 = ObjectWrap::Unwrap<ExportAllDeclarationWrapper>(args[0]->ToObject());
  LabeledStatementWrapper* _LabeledStatement2 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());

  _LabeledStatement2->LabeledStatement->setBody(_ExportAllDeclaration1->ExportAllDeclaration);
}
void LabeledStatementWrapper::setBodyExportDefaultDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration1 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args[0]->ToObject());
  LabeledStatementWrapper* _LabeledStatement2 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());

  _LabeledStatement2->LabeledStatement->setBody(_ExportDefaultDeclaration1->ExportDefaultDeclaration);
}
void LabeledStatementWrapper::setBodyFunctionDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionDeclarationWrapper* _FunctionDeclaration1 = ObjectWrap::Unwrap<FunctionDeclarationWrapper>(args[0]->ToObject());
  LabeledStatementWrapper* _LabeledStatement2 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());

  _LabeledStatement2->LabeledStatement->setBody(_FunctionDeclaration1->FunctionDeclaration);
}
void LabeledStatementWrapper::setBodyVariableDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  VariableDeclarationWrapper* _VariableDeclaration1 = ObjectWrap::Unwrap<VariableDeclarationWrapper>(args[0]->ToObject());
  LabeledStatementWrapper* _LabeledStatement2 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());

  _LabeledStatement2->LabeledStatement->setBody(_VariableDeclaration1->VariableDeclaration);
}
void LabeledStatementWrapper::setBodyBlockStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BlockStatementWrapper* _BlockStatement1 = ObjectWrap::Unwrap<BlockStatementWrapper>(args[0]->ToObject());
  LabeledStatementWrapper* _LabeledStatement2 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());

  _LabeledStatement2->LabeledStatement->setBody(_BlockStatement1->BlockStatement);
}
void LabeledStatementWrapper::setBodyBreakStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BreakStatementWrapper* _BreakStatement1 = ObjectWrap::Unwrap<BreakStatementWrapper>(args[0]->ToObject());
  LabeledStatementWrapper* _LabeledStatement2 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());

  _LabeledStatement2->LabeledStatement->setBody(_BreakStatement1->BreakStatement);
}
void LabeledStatementWrapper::setBodyContinueStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ContinueStatementWrapper* _ContinueStatement1 = ObjectWrap::Unwrap<ContinueStatementWrapper>(args[0]->ToObject());
  LabeledStatementWrapper* _LabeledStatement2 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());

  _LabeledStatement2->LabeledStatement->setBody(_ContinueStatement1->ContinueStatement);
}
void LabeledStatementWrapper::setBodyDebuggerStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  DebuggerStatementWrapper* _DebuggerStatement1 = ObjectWrap::Unwrap<DebuggerStatementWrapper>(args[0]->ToObject());
  LabeledStatementWrapper* _LabeledStatement2 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());

  _LabeledStatement2->LabeledStatement->setBody(_DebuggerStatement1->DebuggerStatement);
}
void LabeledStatementWrapper::setBodyEmptyStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  EmptyStatementWrapper* _EmptyStatement1 = ObjectWrap::Unwrap<EmptyStatementWrapper>(args[0]->ToObject());
  LabeledStatementWrapper* _LabeledStatement2 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());

  _LabeledStatement2->LabeledStatement->setBody(_EmptyStatement1->EmptyStatement);
}
void LabeledStatementWrapper::setBodyExpressionStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExpressionStatementWrapper* _ExpressionStatement1 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args[0]->ToObject());
  LabeledStatementWrapper* _LabeledStatement2 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());

  _LabeledStatement2->LabeledStatement->setBody(_ExpressionStatement1->ExpressionStatement);
}
void LabeledStatementWrapper::setBodyForInStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ForInStatementWrapper* _ForInStatement1 = ObjectWrap::Unwrap<ForInStatementWrapper>(args[0]->ToObject());
  LabeledStatementWrapper* _LabeledStatement2 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());

  _LabeledStatement2->LabeledStatement->setBody(_ForInStatement1->ForInStatement);
}
void LabeledStatementWrapper::setBodyForOfStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ForOfStatementWrapper* _ForOfStatement1 = ObjectWrap::Unwrap<ForOfStatementWrapper>(args[0]->ToObject());
  LabeledStatementWrapper* _LabeledStatement2 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());

  _LabeledStatement2->LabeledStatement->setBody(_ForOfStatement1->ForOfStatement);
}
void LabeledStatementWrapper::setBodyForStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ForStatementWrapper* _ForStatement1 = ObjectWrap::Unwrap<ForStatementWrapper>(args[0]->ToObject());
  LabeledStatementWrapper* _LabeledStatement2 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());

  _LabeledStatement2->LabeledStatement->setBody(_ForStatement1->ForStatement);
}
void LabeledStatementWrapper::setBodyIfStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IfStatementWrapper* _IfStatement1 = ObjectWrap::Unwrap<IfStatementWrapper>(args[0]->ToObject());
  LabeledStatementWrapper* _LabeledStatement2 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());

  _LabeledStatement2->LabeledStatement->setBody(_IfStatement1->IfStatement);
}
void LabeledStatementWrapper::setBodyLabeledStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LabeledStatementWrapper* _LabeledStatement1 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args[0]->ToObject());
  LabeledStatementWrapper* _LabeledStatement2 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());

  _LabeledStatement2->LabeledStatement->setBody(_LabeledStatement1->LabeledStatement);
}
void LabeledStatementWrapper::setBodyReturnStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ReturnStatementWrapper* _ReturnStatement1 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args[0]->ToObject());
  LabeledStatementWrapper* _LabeledStatement2 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());

  _LabeledStatement2->LabeledStatement->setBody(_ReturnStatement1->ReturnStatement);
}
void LabeledStatementWrapper::setBodySwitchStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SwitchStatementWrapper* _SwitchStatement1 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args[0]->ToObject());
  LabeledStatementWrapper* _LabeledStatement2 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());

  _LabeledStatement2->LabeledStatement->setBody(_SwitchStatement1->SwitchStatement);
}
void LabeledStatementWrapper::setBodyThrowStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThrowStatementWrapper* _ThrowStatement1 = ObjectWrap::Unwrap<ThrowStatementWrapper>(args[0]->ToObject());
  LabeledStatementWrapper* _LabeledStatement2 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());

  _LabeledStatement2->LabeledStatement->setBody(_ThrowStatement1->ThrowStatement);
}
void LabeledStatementWrapper::setBodyTryStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TryStatementWrapper* _TryStatement1 = ObjectWrap::Unwrap<TryStatementWrapper>(args[0]->ToObject());
  LabeledStatementWrapper* _LabeledStatement2 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());

  _LabeledStatement2->LabeledStatement->setBody(_TryStatement1->TryStatement);
}
void LabeledStatementWrapper::setBodyWhileStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  WhileStatementWrapper* _WhileStatement1 = ObjectWrap::Unwrap<WhileStatementWrapper>(args[0]->ToObject());
  LabeledStatementWrapper* _LabeledStatement2 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());

  _LabeledStatement2->LabeledStatement->setBody(_WhileStatement1->WhileStatement);
}
void LabeledStatementWrapper::setBodyDoWhileStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  DoWhileStatementWrapper* _DoWhileStatement1 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args[0]->ToObject());
  LabeledStatementWrapper* _LabeledStatement2 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());

  _LabeledStatement2->LabeledStatement->setBody(_DoWhileStatement1->DoWhileStatement);
}
void LabeledStatementWrapper::setBodyWithStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  WithStatementWrapper* _WithStatement1 = ObjectWrap::Unwrap<WithStatementWrapper>(args[0]->ToObject());
  LabeledStatementWrapper* _LabeledStatement2 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());

  _LabeledStatement2->LabeledStatement->setBody(_WithStatement1->WithStatement);
}
void LabeledStatementWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  LabeledStatementWrapper* _LabeledStatement2 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());

  _LabeledStatement2->LabeledStatement->addComments(_Comment1->Comment);
}
void LabeledStatementWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  LabeledStatementWrapper* _LabeledStatement = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _LabeledStatement->LabeledStatement->getPosition();
  range.setPath( param );
  _LabeledStatement->LabeledStatement->setPosition( range );
}

void LabeledStatementWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  LabeledStatementWrapper* _LabeledStatement = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _LabeledStatement->LabeledStatement->getPosition();
  range.setLine( ui );
  _LabeledStatement->LabeledStatement->setPosition( range );
}

void LabeledStatementWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  LabeledStatementWrapper* _LabeledStatement = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _LabeledStatement->LabeledStatement->getPosition();
  range.setCol( ui );
  _LabeledStatement->LabeledStatement->setPosition( range );
}

void LabeledStatementWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  LabeledStatementWrapper* _LabeledStatement = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _LabeledStatement->LabeledStatement->getPosition();
  range.setEndLine( ui );
  _LabeledStatement->LabeledStatement->setPosition( range );
}

void LabeledStatementWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  LabeledStatementWrapper* _LabeledStatement = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _LabeledStatement->LabeledStatement->getPosition();
  range.setEndCol( ui );
  _LabeledStatement->LabeledStatement->setPosition( range );
}

void LabeledStatementWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  LabeledStatementWrapper* _LabeledStatement = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _LabeledStatement->LabeledStatement->getPosition();
  range.setWideLine( ui );
  _LabeledStatement->LabeledStatement->setPosition( range );
}

void LabeledStatementWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  LabeledStatementWrapper* _LabeledStatement = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _LabeledStatement->LabeledStatement->getPosition();
  range.setWideCol( ui );
  _LabeledStatement->LabeledStatement->setPosition( range );
}

void LabeledStatementWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  LabeledStatementWrapper* _LabeledStatement = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _LabeledStatement->LabeledStatement->getPosition();
  range.setWideEndLine( ui );
  _LabeledStatement->LabeledStatement->setPosition( range );
}

void LabeledStatementWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  LabeledStatementWrapper* _LabeledStatement = ObjectWrap::Unwrap<LabeledStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _LabeledStatement->LabeledStatement->getPosition();
  range.setWideEndCol( ui );
  _LabeledStatement->LabeledStatement->setPosition( range );
}

}}}} //end of namespaces