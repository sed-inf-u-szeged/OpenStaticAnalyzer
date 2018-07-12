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

#include "../inc/BlockStatementWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> BlockStatementWrapper::constructor;

void BlockStatementWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "BlockStatementWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
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
  exports->Set(v8::String::NewFromUtf8(isolate, "BlockStatementWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void BlockStatementWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new BlockStatementWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    BlockStatementWrapper* obj = new BlockStatementWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `BlockStatementWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


BlockStatementWrapper::BlockStatementWrapper(Factory* fact)                        
{                                                   
  BlockStatement = fact->getFactory()->createBlockStatementNode();          
}                                                   

BlockStatementWrapper::~BlockStatementWrapper()
{        
}        

void BlockStatementWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void BlockStatementWrapper::addBodyClassDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassDeclarationWrapper* _ClassDeclaration1 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args[0]->ToObject());
  BlockStatementWrapper* _BlockStatement2 = ObjectWrap::Unwrap<BlockStatementWrapper>(args.This());

  _BlockStatement2->BlockStatement->addBody(_ClassDeclaration1->ClassDeclaration);
}
void BlockStatementWrapper::addBodyExportAllDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExportAllDeclarationWrapper* _ExportAllDeclaration1 = ObjectWrap::Unwrap<ExportAllDeclarationWrapper>(args[0]->ToObject());
  BlockStatementWrapper* _BlockStatement2 = ObjectWrap::Unwrap<BlockStatementWrapper>(args.This());

  _BlockStatement2->BlockStatement->addBody(_ExportAllDeclaration1->ExportAllDeclaration);
}
void BlockStatementWrapper::addBodyExportDefaultDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration1 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args[0]->ToObject());
  BlockStatementWrapper* _BlockStatement2 = ObjectWrap::Unwrap<BlockStatementWrapper>(args.This());

  _BlockStatement2->BlockStatement->addBody(_ExportDefaultDeclaration1->ExportDefaultDeclaration);
}
void BlockStatementWrapper::addBodyFunctionDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionDeclarationWrapper* _FunctionDeclaration1 = ObjectWrap::Unwrap<FunctionDeclarationWrapper>(args[0]->ToObject());
  BlockStatementWrapper* _BlockStatement2 = ObjectWrap::Unwrap<BlockStatementWrapper>(args.This());

  _BlockStatement2->BlockStatement->addBody(_FunctionDeclaration1->FunctionDeclaration);
}
void BlockStatementWrapper::addBodyVariableDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  VariableDeclarationWrapper* _VariableDeclaration1 = ObjectWrap::Unwrap<VariableDeclarationWrapper>(args[0]->ToObject());
  BlockStatementWrapper* _BlockStatement2 = ObjectWrap::Unwrap<BlockStatementWrapper>(args.This());

  _BlockStatement2->BlockStatement->addBody(_VariableDeclaration1->VariableDeclaration);
}
void BlockStatementWrapper::addBodyBlockStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BlockStatementWrapper* _BlockStatement1 = ObjectWrap::Unwrap<BlockStatementWrapper>(args[0]->ToObject());
  BlockStatementWrapper* _BlockStatement2 = ObjectWrap::Unwrap<BlockStatementWrapper>(args.This());

  _BlockStatement2->BlockStatement->addBody(_BlockStatement1->BlockStatement);
}
void BlockStatementWrapper::addBodyBreakStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BreakStatementWrapper* _BreakStatement1 = ObjectWrap::Unwrap<BreakStatementWrapper>(args[0]->ToObject());
  BlockStatementWrapper* _BlockStatement2 = ObjectWrap::Unwrap<BlockStatementWrapper>(args.This());

  _BlockStatement2->BlockStatement->addBody(_BreakStatement1->BreakStatement);
}
void BlockStatementWrapper::addBodyContinueStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ContinueStatementWrapper* _ContinueStatement1 = ObjectWrap::Unwrap<ContinueStatementWrapper>(args[0]->ToObject());
  BlockStatementWrapper* _BlockStatement2 = ObjectWrap::Unwrap<BlockStatementWrapper>(args.This());

  _BlockStatement2->BlockStatement->addBody(_ContinueStatement1->ContinueStatement);
}
void BlockStatementWrapper::addBodyDebuggerStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  DebuggerStatementWrapper* _DebuggerStatement1 = ObjectWrap::Unwrap<DebuggerStatementWrapper>(args[0]->ToObject());
  BlockStatementWrapper* _BlockStatement2 = ObjectWrap::Unwrap<BlockStatementWrapper>(args.This());

  _BlockStatement2->BlockStatement->addBody(_DebuggerStatement1->DebuggerStatement);
}
void BlockStatementWrapper::addBodyEmptyStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  EmptyStatementWrapper* _EmptyStatement1 = ObjectWrap::Unwrap<EmptyStatementWrapper>(args[0]->ToObject());
  BlockStatementWrapper* _BlockStatement2 = ObjectWrap::Unwrap<BlockStatementWrapper>(args.This());

  _BlockStatement2->BlockStatement->addBody(_EmptyStatement1->EmptyStatement);
}
void BlockStatementWrapper::addBodyExpressionStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExpressionStatementWrapper* _ExpressionStatement1 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args[0]->ToObject());
  BlockStatementWrapper* _BlockStatement2 = ObjectWrap::Unwrap<BlockStatementWrapper>(args.This());

  _BlockStatement2->BlockStatement->addBody(_ExpressionStatement1->ExpressionStatement);
}
void BlockStatementWrapper::addBodyForInStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ForInStatementWrapper* _ForInStatement1 = ObjectWrap::Unwrap<ForInStatementWrapper>(args[0]->ToObject());
  BlockStatementWrapper* _BlockStatement2 = ObjectWrap::Unwrap<BlockStatementWrapper>(args.This());

  _BlockStatement2->BlockStatement->addBody(_ForInStatement1->ForInStatement);
}
void BlockStatementWrapper::addBodyForOfStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ForOfStatementWrapper* _ForOfStatement1 = ObjectWrap::Unwrap<ForOfStatementWrapper>(args[0]->ToObject());
  BlockStatementWrapper* _BlockStatement2 = ObjectWrap::Unwrap<BlockStatementWrapper>(args.This());

  _BlockStatement2->BlockStatement->addBody(_ForOfStatement1->ForOfStatement);
}
void BlockStatementWrapper::addBodyForStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ForStatementWrapper* _ForStatement1 = ObjectWrap::Unwrap<ForStatementWrapper>(args[0]->ToObject());
  BlockStatementWrapper* _BlockStatement2 = ObjectWrap::Unwrap<BlockStatementWrapper>(args.This());

  _BlockStatement2->BlockStatement->addBody(_ForStatement1->ForStatement);
}
void BlockStatementWrapper::addBodyIfStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IfStatementWrapper* _IfStatement1 = ObjectWrap::Unwrap<IfStatementWrapper>(args[0]->ToObject());
  BlockStatementWrapper* _BlockStatement2 = ObjectWrap::Unwrap<BlockStatementWrapper>(args.This());

  _BlockStatement2->BlockStatement->addBody(_IfStatement1->IfStatement);
}
void BlockStatementWrapper::addBodyLabeledStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LabeledStatementWrapper* _LabeledStatement1 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args[0]->ToObject());
  BlockStatementWrapper* _BlockStatement2 = ObjectWrap::Unwrap<BlockStatementWrapper>(args.This());

  _BlockStatement2->BlockStatement->addBody(_LabeledStatement1->LabeledStatement);
}
void BlockStatementWrapper::addBodyReturnStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ReturnStatementWrapper* _ReturnStatement1 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args[0]->ToObject());
  BlockStatementWrapper* _BlockStatement2 = ObjectWrap::Unwrap<BlockStatementWrapper>(args.This());

  _BlockStatement2->BlockStatement->addBody(_ReturnStatement1->ReturnStatement);
}
void BlockStatementWrapper::addBodySwitchStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SwitchStatementWrapper* _SwitchStatement1 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args[0]->ToObject());
  BlockStatementWrapper* _BlockStatement2 = ObjectWrap::Unwrap<BlockStatementWrapper>(args.This());

  _BlockStatement2->BlockStatement->addBody(_SwitchStatement1->SwitchStatement);
}
void BlockStatementWrapper::addBodyThrowStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThrowStatementWrapper* _ThrowStatement1 = ObjectWrap::Unwrap<ThrowStatementWrapper>(args[0]->ToObject());
  BlockStatementWrapper* _BlockStatement2 = ObjectWrap::Unwrap<BlockStatementWrapper>(args.This());

  _BlockStatement2->BlockStatement->addBody(_ThrowStatement1->ThrowStatement);
}
void BlockStatementWrapper::addBodyTryStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TryStatementWrapper* _TryStatement1 = ObjectWrap::Unwrap<TryStatementWrapper>(args[0]->ToObject());
  BlockStatementWrapper* _BlockStatement2 = ObjectWrap::Unwrap<BlockStatementWrapper>(args.This());

  _BlockStatement2->BlockStatement->addBody(_TryStatement1->TryStatement);
}
void BlockStatementWrapper::addBodyWhileStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  WhileStatementWrapper* _WhileStatement1 = ObjectWrap::Unwrap<WhileStatementWrapper>(args[0]->ToObject());
  BlockStatementWrapper* _BlockStatement2 = ObjectWrap::Unwrap<BlockStatementWrapper>(args.This());

  _BlockStatement2->BlockStatement->addBody(_WhileStatement1->WhileStatement);
}
void BlockStatementWrapper::addBodyDoWhileStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  DoWhileStatementWrapper* _DoWhileStatement1 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args[0]->ToObject());
  BlockStatementWrapper* _BlockStatement2 = ObjectWrap::Unwrap<BlockStatementWrapper>(args.This());

  _BlockStatement2->BlockStatement->addBody(_DoWhileStatement1->DoWhileStatement);
}
void BlockStatementWrapper::addBodyWithStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  WithStatementWrapper* _WithStatement1 = ObjectWrap::Unwrap<WithStatementWrapper>(args[0]->ToObject());
  BlockStatementWrapper* _BlockStatement2 = ObjectWrap::Unwrap<BlockStatementWrapper>(args.This());

  _BlockStatement2->BlockStatement->addBody(_WithStatement1->WithStatement);
}
void BlockStatementWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  BlockStatementWrapper* _BlockStatement2 = ObjectWrap::Unwrap<BlockStatementWrapper>(args.This());

  _BlockStatement2->BlockStatement->addComments(_Comment1->Comment);
}
void BlockStatementWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  BlockStatementWrapper* _BlockStatement = ObjectWrap::Unwrap<BlockStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _BlockStatement->BlockStatement->getPosition();
  range.setPath( param );
  _BlockStatement->BlockStatement->setPosition( range );
}

void BlockStatementWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  BlockStatementWrapper* _BlockStatement = ObjectWrap::Unwrap<BlockStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _BlockStatement->BlockStatement->getPosition();
  range.setLine( ui );
  _BlockStatement->BlockStatement->setPosition( range );
}

void BlockStatementWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  BlockStatementWrapper* _BlockStatement = ObjectWrap::Unwrap<BlockStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _BlockStatement->BlockStatement->getPosition();
  range.setCol( ui );
  _BlockStatement->BlockStatement->setPosition( range );
}

void BlockStatementWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  BlockStatementWrapper* _BlockStatement = ObjectWrap::Unwrap<BlockStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _BlockStatement->BlockStatement->getPosition();
  range.setEndLine( ui );
  _BlockStatement->BlockStatement->setPosition( range );
}

void BlockStatementWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  BlockStatementWrapper* _BlockStatement = ObjectWrap::Unwrap<BlockStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _BlockStatement->BlockStatement->getPosition();
  range.setEndCol( ui );
  _BlockStatement->BlockStatement->setPosition( range );
}

void BlockStatementWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  BlockStatementWrapper* _BlockStatement = ObjectWrap::Unwrap<BlockStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _BlockStatement->BlockStatement->getPosition();
  range.setWideLine( ui );
  _BlockStatement->BlockStatement->setPosition( range );
}

void BlockStatementWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  BlockStatementWrapper* _BlockStatement = ObjectWrap::Unwrap<BlockStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _BlockStatement->BlockStatement->getPosition();
  range.setWideCol( ui );
  _BlockStatement->BlockStatement->setPosition( range );
}

void BlockStatementWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  BlockStatementWrapper* _BlockStatement = ObjectWrap::Unwrap<BlockStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _BlockStatement->BlockStatement->getPosition();
  range.setWideEndLine( ui );
  _BlockStatement->BlockStatement->setPosition( range );
}

void BlockStatementWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  BlockStatementWrapper* _BlockStatement = ObjectWrap::Unwrap<BlockStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _BlockStatement->BlockStatement->getPosition();
  range.setWideEndCol( ui );
  _BlockStatement->BlockStatement->setPosition( range );
}

}}}} //end of namespaces