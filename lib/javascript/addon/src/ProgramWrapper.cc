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

#include "../inc/ProgramWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> ProgramWrapper::constructor;

void ProgramWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "ProgramWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "addBodyModuleDeclaration", addBodyModuleDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addBodyExportNamedDeclaration", addBodyExportNamedDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addBodyImportDeclaration", addBodyImportDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addBodyClassDeclaration", addBodyClassDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addBodyExportAllDeclaration", addBodyExportAllDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addBodyExportDefaultDeclaration", addBodyExportDefaultDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addBodyFunctionDeclaration", addBodyFunctionDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addBodyVariableDeclaration", addBodyVariableDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addBodyBlockStatement", addBodyBlockStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addBodyBreakStatement", addBodyBreakStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addBodyContinueStatement", addBodyContinueStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addBodyDebuggerStatement", addBodyDebuggerStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addBodyEmptyStatement", addBodyEmptyStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addBodyExpressionStatement", addBodyExpressionStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addBodyForInStatement", addBodyForInStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addBodyForOfStatement", addBodyForOfStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addBodyForStatement", addBodyForStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addBodyIfStatement", addBodyIfStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addBodyLabeledStatement", addBodyLabeledStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addBodyReturnStatement", addBodyReturnStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addBodySwitchStatement", addBodySwitchStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addBodyThrowStatement", addBodyThrowStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addBodyTryStatement", addBodyTryStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addBodyWhileStatement", addBodyWhileStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addBodyDoWhileStatement", addBodyDoWhileStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addBodyWithStatement", addBodyWithStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addCommentsComment", addCommentsComment);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSourceType", setSourceType);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "ProgramWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void ProgramWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new ProgramWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    ProgramWrapper* obj = new ProgramWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `ProgramWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


ProgramWrapper::ProgramWrapper(Factory* fact)                        
{                                                   
  Program = fact->getFactory()->createProgramNode();          
}                                                   

ProgramWrapper::~ProgramWrapper()
{        
}        

void ProgramWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void ProgramWrapper::addBodyModuleDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ModuleDeclarationWrapper* _ModuleDeclaration1 = ObjectWrap::Unwrap<ModuleDeclarationWrapper>(args[0]->ToObject());
  ProgramWrapper* _Program2 = ObjectWrap::Unwrap<ProgramWrapper>(args.This());

  _Program2->Program->addBody(_ModuleDeclaration1->ModuleDeclaration);
}
void ProgramWrapper::addBodyExportNamedDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExportNamedDeclarationWrapper* _ExportNamedDeclaration1 = ObjectWrap::Unwrap<ExportNamedDeclarationWrapper>(args[0]->ToObject());
  ProgramWrapper* _Program2 = ObjectWrap::Unwrap<ProgramWrapper>(args.This());

  _Program2->Program->addBody(_ExportNamedDeclaration1->ExportNamedDeclaration);
}
void ProgramWrapper::addBodyImportDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ImportDeclarationWrapper* _ImportDeclaration1 = ObjectWrap::Unwrap<ImportDeclarationWrapper>(args[0]->ToObject());
  ProgramWrapper* _Program2 = ObjectWrap::Unwrap<ProgramWrapper>(args.This());

  _Program2->Program->addBody(_ImportDeclaration1->ImportDeclaration);
}
void ProgramWrapper::addBodyClassDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassDeclarationWrapper* _ClassDeclaration1 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args[0]->ToObject());
  ProgramWrapper* _Program2 = ObjectWrap::Unwrap<ProgramWrapper>(args.This());

  _Program2->Program->addBody(_ClassDeclaration1->ClassDeclaration);
}
void ProgramWrapper::addBodyExportAllDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExportAllDeclarationWrapper* _ExportAllDeclaration1 = ObjectWrap::Unwrap<ExportAllDeclarationWrapper>(args[0]->ToObject());
  ProgramWrapper* _Program2 = ObjectWrap::Unwrap<ProgramWrapper>(args.This());

  _Program2->Program->addBody(_ExportAllDeclaration1->ExportAllDeclaration);
}
void ProgramWrapper::addBodyExportDefaultDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration1 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args[0]->ToObject());
  ProgramWrapper* _Program2 = ObjectWrap::Unwrap<ProgramWrapper>(args.This());

  _Program2->Program->addBody(_ExportDefaultDeclaration1->ExportDefaultDeclaration);
}
void ProgramWrapper::addBodyFunctionDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionDeclarationWrapper* _FunctionDeclaration1 = ObjectWrap::Unwrap<FunctionDeclarationWrapper>(args[0]->ToObject());
  ProgramWrapper* _Program2 = ObjectWrap::Unwrap<ProgramWrapper>(args.This());

  _Program2->Program->addBody(_FunctionDeclaration1->FunctionDeclaration);
}
void ProgramWrapper::addBodyVariableDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  VariableDeclarationWrapper* _VariableDeclaration1 = ObjectWrap::Unwrap<VariableDeclarationWrapper>(args[0]->ToObject());
  ProgramWrapper* _Program2 = ObjectWrap::Unwrap<ProgramWrapper>(args.This());

  _Program2->Program->addBody(_VariableDeclaration1->VariableDeclaration);
}
void ProgramWrapper::addBodyBlockStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BlockStatementWrapper* _BlockStatement1 = ObjectWrap::Unwrap<BlockStatementWrapper>(args[0]->ToObject());
  ProgramWrapper* _Program2 = ObjectWrap::Unwrap<ProgramWrapper>(args.This());

  _Program2->Program->addBody(_BlockStatement1->BlockStatement);
}
void ProgramWrapper::addBodyBreakStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BreakStatementWrapper* _BreakStatement1 = ObjectWrap::Unwrap<BreakStatementWrapper>(args[0]->ToObject());
  ProgramWrapper* _Program2 = ObjectWrap::Unwrap<ProgramWrapper>(args.This());

  _Program2->Program->addBody(_BreakStatement1->BreakStatement);
}
void ProgramWrapper::addBodyContinueStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ContinueStatementWrapper* _ContinueStatement1 = ObjectWrap::Unwrap<ContinueStatementWrapper>(args[0]->ToObject());
  ProgramWrapper* _Program2 = ObjectWrap::Unwrap<ProgramWrapper>(args.This());

  _Program2->Program->addBody(_ContinueStatement1->ContinueStatement);
}
void ProgramWrapper::addBodyDebuggerStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  DebuggerStatementWrapper* _DebuggerStatement1 = ObjectWrap::Unwrap<DebuggerStatementWrapper>(args[0]->ToObject());
  ProgramWrapper* _Program2 = ObjectWrap::Unwrap<ProgramWrapper>(args.This());

  _Program2->Program->addBody(_DebuggerStatement1->DebuggerStatement);
}
void ProgramWrapper::addBodyEmptyStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  EmptyStatementWrapper* _EmptyStatement1 = ObjectWrap::Unwrap<EmptyStatementWrapper>(args[0]->ToObject());
  ProgramWrapper* _Program2 = ObjectWrap::Unwrap<ProgramWrapper>(args.This());

  _Program2->Program->addBody(_EmptyStatement1->EmptyStatement);
}
void ProgramWrapper::addBodyExpressionStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExpressionStatementWrapper* _ExpressionStatement1 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args[0]->ToObject());
  ProgramWrapper* _Program2 = ObjectWrap::Unwrap<ProgramWrapper>(args.This());

  _Program2->Program->addBody(_ExpressionStatement1->ExpressionStatement);
}
void ProgramWrapper::addBodyForInStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ForInStatementWrapper* _ForInStatement1 = ObjectWrap::Unwrap<ForInStatementWrapper>(args[0]->ToObject());
  ProgramWrapper* _Program2 = ObjectWrap::Unwrap<ProgramWrapper>(args.This());

  _Program2->Program->addBody(_ForInStatement1->ForInStatement);
}
void ProgramWrapper::addBodyForOfStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ForOfStatementWrapper* _ForOfStatement1 = ObjectWrap::Unwrap<ForOfStatementWrapper>(args[0]->ToObject());
  ProgramWrapper* _Program2 = ObjectWrap::Unwrap<ProgramWrapper>(args.This());

  _Program2->Program->addBody(_ForOfStatement1->ForOfStatement);
}
void ProgramWrapper::addBodyForStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ForStatementWrapper* _ForStatement1 = ObjectWrap::Unwrap<ForStatementWrapper>(args[0]->ToObject());
  ProgramWrapper* _Program2 = ObjectWrap::Unwrap<ProgramWrapper>(args.This());

  _Program2->Program->addBody(_ForStatement1->ForStatement);
}
void ProgramWrapper::addBodyIfStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IfStatementWrapper* _IfStatement1 = ObjectWrap::Unwrap<IfStatementWrapper>(args[0]->ToObject());
  ProgramWrapper* _Program2 = ObjectWrap::Unwrap<ProgramWrapper>(args.This());

  _Program2->Program->addBody(_IfStatement1->IfStatement);
}
void ProgramWrapper::addBodyLabeledStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LabeledStatementWrapper* _LabeledStatement1 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args[0]->ToObject());
  ProgramWrapper* _Program2 = ObjectWrap::Unwrap<ProgramWrapper>(args.This());

  _Program2->Program->addBody(_LabeledStatement1->LabeledStatement);
}
void ProgramWrapper::addBodyReturnStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ReturnStatementWrapper* _ReturnStatement1 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args[0]->ToObject());
  ProgramWrapper* _Program2 = ObjectWrap::Unwrap<ProgramWrapper>(args.This());

  _Program2->Program->addBody(_ReturnStatement1->ReturnStatement);
}
void ProgramWrapper::addBodySwitchStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SwitchStatementWrapper* _SwitchStatement1 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args[0]->ToObject());
  ProgramWrapper* _Program2 = ObjectWrap::Unwrap<ProgramWrapper>(args.This());

  _Program2->Program->addBody(_SwitchStatement1->SwitchStatement);
}
void ProgramWrapper::addBodyThrowStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThrowStatementWrapper* _ThrowStatement1 = ObjectWrap::Unwrap<ThrowStatementWrapper>(args[0]->ToObject());
  ProgramWrapper* _Program2 = ObjectWrap::Unwrap<ProgramWrapper>(args.This());

  _Program2->Program->addBody(_ThrowStatement1->ThrowStatement);
}
void ProgramWrapper::addBodyTryStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TryStatementWrapper* _TryStatement1 = ObjectWrap::Unwrap<TryStatementWrapper>(args[0]->ToObject());
  ProgramWrapper* _Program2 = ObjectWrap::Unwrap<ProgramWrapper>(args.This());

  _Program2->Program->addBody(_TryStatement1->TryStatement);
}
void ProgramWrapper::addBodyWhileStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  WhileStatementWrapper* _WhileStatement1 = ObjectWrap::Unwrap<WhileStatementWrapper>(args[0]->ToObject());
  ProgramWrapper* _Program2 = ObjectWrap::Unwrap<ProgramWrapper>(args.This());

  _Program2->Program->addBody(_WhileStatement1->WhileStatement);
}
void ProgramWrapper::addBodyDoWhileStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  DoWhileStatementWrapper* _DoWhileStatement1 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args[0]->ToObject());
  ProgramWrapper* _Program2 = ObjectWrap::Unwrap<ProgramWrapper>(args.This());

  _Program2->Program->addBody(_DoWhileStatement1->DoWhileStatement);
}
void ProgramWrapper::addBodyWithStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  WithStatementWrapper* _WithStatement1 = ObjectWrap::Unwrap<WithStatementWrapper>(args[0]->ToObject());
  ProgramWrapper* _Program2 = ObjectWrap::Unwrap<ProgramWrapper>(args.This());

  _Program2->Program->addBody(_WithStatement1->WithStatement);
}
void ProgramWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  ProgramWrapper* _Program2 = ObjectWrap::Unwrap<ProgramWrapper>(args.This());

  _Program2->Program->addComments(_Comment1->Comment);
}
void ProgramWrapper::setSourceType(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ProgramWrapper* _Program = ObjectWrap::Unwrap<ProgramWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  if( param == "pstScript" ){
    _Program->Program->setSourceType( pstScript );
  }
  if( param == "pstModule" ){
    _Program->Program->setSourceType( pstModule );
  }
}
void ProgramWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  ProgramWrapper* _Program = ObjectWrap::Unwrap<ProgramWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _Program->Program->getPosition();
  range.setPath( param );
  _Program->Program->setPosition( range );
}

void ProgramWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ProgramWrapper* _Program = ObjectWrap::Unwrap<ProgramWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _Program->Program->getPosition();
  range.setLine( ui );
  _Program->Program->setPosition( range );
}

void ProgramWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ProgramWrapper* _Program = ObjectWrap::Unwrap<ProgramWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _Program->Program->getPosition();
  range.setCol( ui );
  _Program->Program->setPosition( range );
}

void ProgramWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ProgramWrapper* _Program = ObjectWrap::Unwrap<ProgramWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _Program->Program->getPosition();
  range.setEndLine( ui );
  _Program->Program->setPosition( range );
}

void ProgramWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ProgramWrapper* _Program = ObjectWrap::Unwrap<ProgramWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _Program->Program->getPosition();
  range.setEndCol( ui );
  _Program->Program->setPosition( range );
}

void ProgramWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ProgramWrapper* _Program = ObjectWrap::Unwrap<ProgramWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _Program->Program->getPosition();
  range.setWideLine( ui );
  _Program->Program->setPosition( range );
}

void ProgramWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ProgramWrapper* _Program = ObjectWrap::Unwrap<ProgramWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _Program->Program->getPosition();
  range.setWideCol( ui );
  _Program->Program->setPosition( range );
}

void ProgramWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ProgramWrapper* _Program = ObjectWrap::Unwrap<ProgramWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _Program->Program->getPosition();
  range.setWideEndLine( ui );
  _Program->Program->setPosition( range );
}

void ProgramWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ProgramWrapper* _Program = ObjectWrap::Unwrap<ProgramWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _Program->Program->getPosition();
  range.setWideEndCol( ui );
  _Program->Program->setPosition( range );
}

void ProgramWrapper::setName(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ProgramWrapper* _Program = ObjectWrap::Unwrap<ProgramWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  _Program->Program->setName( param );
}
}}}} //end of namespaces