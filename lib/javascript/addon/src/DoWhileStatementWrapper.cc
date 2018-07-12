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

#include "../inc/DoWhileStatementWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> DoWhileStatementWrapper::constructor;

void DoWhileStatementWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "DoWhileStatementWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
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
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTestArrayExpression", setTestArrayExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTestArrowFunctionExpression", setTestArrowFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTestAssignmentExpression", setTestAssignmentExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTestAwaitExpression", setTestAwaitExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTestBinaryExpression", setTestBinaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTestCallExpression", setTestCallExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTestClassExpression", setTestClassExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTestConditionalExpression", setTestConditionalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTestFunctionExpression", setTestFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTestIdentifier", setTestIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTestBooleanLiteral", setTestBooleanLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTestNullLiteral", setTestNullLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTestNumberLiteral", setTestNumberLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTestRegExpLiteral", setTestRegExpLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTestStringLiteral", setTestStringLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTestLogicalExpression", setTestLogicalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTestMemberExpression", setTestMemberExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTestMetaProperty", setTestMetaProperty);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTestNewExpression", setTestNewExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTestObjectExpression", setTestObjectExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTestSequenceExpression", setTestSequenceExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTestTaggedTemplateExpression", setTestTaggedTemplateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTestTemplateLiteral", setTestTemplateLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTestThisExpression", setTestThisExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTestUnaryExpression", setTestUnaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTestUpdateExpression", setTestUpdateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTestYieldExpression", setTestYieldExpression);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "DoWhileStatementWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void DoWhileStatementWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new DoWhileStatementWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    DoWhileStatementWrapper* obj = new DoWhileStatementWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `DoWhileStatementWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


DoWhileStatementWrapper::DoWhileStatementWrapper(Factory* fact)                        
{                                                   
  DoWhileStatement = fact->getFactory()->createDoWhileStatementNode();          
}                                                   

DoWhileStatementWrapper::~DoWhileStatementWrapper()
{        
}        

void DoWhileStatementWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void DoWhileStatementWrapper::setBodyClassDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassDeclarationWrapper* _ClassDeclaration1 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setBody(_ClassDeclaration1->ClassDeclaration);
}
void DoWhileStatementWrapper::setBodyExportAllDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExportAllDeclarationWrapper* _ExportAllDeclaration1 = ObjectWrap::Unwrap<ExportAllDeclarationWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setBody(_ExportAllDeclaration1->ExportAllDeclaration);
}
void DoWhileStatementWrapper::setBodyExportDefaultDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration1 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setBody(_ExportDefaultDeclaration1->ExportDefaultDeclaration);
}
void DoWhileStatementWrapper::setBodyFunctionDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionDeclarationWrapper* _FunctionDeclaration1 = ObjectWrap::Unwrap<FunctionDeclarationWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setBody(_FunctionDeclaration1->FunctionDeclaration);
}
void DoWhileStatementWrapper::setBodyVariableDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  VariableDeclarationWrapper* _VariableDeclaration1 = ObjectWrap::Unwrap<VariableDeclarationWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setBody(_VariableDeclaration1->VariableDeclaration);
}
void DoWhileStatementWrapper::setBodyBlockStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BlockStatementWrapper* _BlockStatement1 = ObjectWrap::Unwrap<BlockStatementWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setBody(_BlockStatement1->BlockStatement);
}
void DoWhileStatementWrapper::setBodyBreakStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BreakStatementWrapper* _BreakStatement1 = ObjectWrap::Unwrap<BreakStatementWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setBody(_BreakStatement1->BreakStatement);
}
void DoWhileStatementWrapper::setBodyContinueStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ContinueStatementWrapper* _ContinueStatement1 = ObjectWrap::Unwrap<ContinueStatementWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setBody(_ContinueStatement1->ContinueStatement);
}
void DoWhileStatementWrapper::setBodyDebuggerStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  DebuggerStatementWrapper* _DebuggerStatement1 = ObjectWrap::Unwrap<DebuggerStatementWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setBody(_DebuggerStatement1->DebuggerStatement);
}
void DoWhileStatementWrapper::setBodyEmptyStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  EmptyStatementWrapper* _EmptyStatement1 = ObjectWrap::Unwrap<EmptyStatementWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setBody(_EmptyStatement1->EmptyStatement);
}
void DoWhileStatementWrapper::setBodyExpressionStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExpressionStatementWrapper* _ExpressionStatement1 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setBody(_ExpressionStatement1->ExpressionStatement);
}
void DoWhileStatementWrapper::setBodyForInStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ForInStatementWrapper* _ForInStatement1 = ObjectWrap::Unwrap<ForInStatementWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setBody(_ForInStatement1->ForInStatement);
}
void DoWhileStatementWrapper::setBodyForOfStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ForOfStatementWrapper* _ForOfStatement1 = ObjectWrap::Unwrap<ForOfStatementWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setBody(_ForOfStatement1->ForOfStatement);
}
void DoWhileStatementWrapper::setBodyForStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ForStatementWrapper* _ForStatement1 = ObjectWrap::Unwrap<ForStatementWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setBody(_ForStatement1->ForStatement);
}
void DoWhileStatementWrapper::setBodyIfStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IfStatementWrapper* _IfStatement1 = ObjectWrap::Unwrap<IfStatementWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setBody(_IfStatement1->IfStatement);
}
void DoWhileStatementWrapper::setBodyLabeledStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LabeledStatementWrapper* _LabeledStatement1 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setBody(_LabeledStatement1->LabeledStatement);
}
void DoWhileStatementWrapper::setBodyReturnStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ReturnStatementWrapper* _ReturnStatement1 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setBody(_ReturnStatement1->ReturnStatement);
}
void DoWhileStatementWrapper::setBodySwitchStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SwitchStatementWrapper* _SwitchStatement1 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setBody(_SwitchStatement1->SwitchStatement);
}
void DoWhileStatementWrapper::setBodyThrowStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThrowStatementWrapper* _ThrowStatement1 = ObjectWrap::Unwrap<ThrowStatementWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setBody(_ThrowStatement1->ThrowStatement);
}
void DoWhileStatementWrapper::setBodyTryStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TryStatementWrapper* _TryStatement1 = ObjectWrap::Unwrap<TryStatementWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setBody(_TryStatement1->TryStatement);
}
void DoWhileStatementWrapper::setBodyWhileStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  WhileStatementWrapper* _WhileStatement1 = ObjectWrap::Unwrap<WhileStatementWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setBody(_WhileStatement1->WhileStatement);
}
void DoWhileStatementWrapper::setBodyDoWhileStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  DoWhileStatementWrapper* _DoWhileStatement1 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setBody(_DoWhileStatement1->DoWhileStatement);
}
void DoWhileStatementWrapper::setBodyWithStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  WithStatementWrapper* _WithStatement1 = ObjectWrap::Unwrap<WithStatementWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setBody(_WithStatement1->WithStatement);
}
void DoWhileStatementWrapper::setTestArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setTest(_ArrayExpression1->ArrayExpression);
}
void DoWhileStatementWrapper::setTestArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setTest(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void DoWhileStatementWrapper::setTestAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setTest(_AssignmentExpression1->AssignmentExpression);
}
void DoWhileStatementWrapper::setTestAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setTest(_AwaitExpression1->AwaitExpression);
}
void DoWhileStatementWrapper::setTestBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setTest(_BinaryExpression1->BinaryExpression);
}
void DoWhileStatementWrapper::setTestCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setTest(_CallExpression1->CallExpression);
}
void DoWhileStatementWrapper::setTestClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setTest(_ClassExpression1->ClassExpression);
}
void DoWhileStatementWrapper::setTestConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setTest(_ConditionalExpression1->ConditionalExpression);
}
void DoWhileStatementWrapper::setTestFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setTest(_FunctionExpression1->FunctionExpression);
}
void DoWhileStatementWrapper::setTestIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setTest(_Identifier1->Identifier);
}
void DoWhileStatementWrapper::setTestBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setTest(_BooleanLiteral1->BooleanLiteral);
}
void DoWhileStatementWrapper::setTestNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setTest(_NullLiteral1->NullLiteral);
}
void DoWhileStatementWrapper::setTestNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setTest(_NumberLiteral1->NumberLiteral);
}
void DoWhileStatementWrapper::setTestRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setTest(_RegExpLiteral1->RegExpLiteral);
}
void DoWhileStatementWrapper::setTestStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setTest(_StringLiteral1->StringLiteral);
}
void DoWhileStatementWrapper::setTestLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setTest(_LogicalExpression1->LogicalExpression);
}
void DoWhileStatementWrapper::setTestMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setTest(_MemberExpression1->MemberExpression);
}
void DoWhileStatementWrapper::setTestMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setTest(_MetaProperty1->MetaProperty);
}
void DoWhileStatementWrapper::setTestNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setTest(_NewExpression1->NewExpression);
}
void DoWhileStatementWrapper::setTestObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setTest(_ObjectExpression1->ObjectExpression);
}
void DoWhileStatementWrapper::setTestSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setTest(_SequenceExpression1->SequenceExpression);
}
void DoWhileStatementWrapper::setTestTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setTest(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void DoWhileStatementWrapper::setTestTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setTest(_TemplateLiteral1->TemplateLiteral);
}
void DoWhileStatementWrapper::setTestThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setTest(_ThisExpression1->ThisExpression);
}
void DoWhileStatementWrapper::setTestUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setTest(_UnaryExpression1->UnaryExpression);
}
void DoWhileStatementWrapper::setTestUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setTest(_UpdateExpression1->UpdateExpression);
}
void DoWhileStatementWrapper::setTestYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->setTest(_YieldExpression1->YieldExpression);
}
void DoWhileStatementWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  DoWhileStatementWrapper* _DoWhileStatement2 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());

  _DoWhileStatement2->DoWhileStatement->addComments(_Comment1->Comment);
}
void DoWhileStatementWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  DoWhileStatementWrapper* _DoWhileStatement = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _DoWhileStatement->DoWhileStatement->getPosition();
  range.setPath( param );
  _DoWhileStatement->DoWhileStatement->setPosition( range );
}

void DoWhileStatementWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  DoWhileStatementWrapper* _DoWhileStatement = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _DoWhileStatement->DoWhileStatement->getPosition();
  range.setLine( ui );
  _DoWhileStatement->DoWhileStatement->setPosition( range );
}

void DoWhileStatementWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  DoWhileStatementWrapper* _DoWhileStatement = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _DoWhileStatement->DoWhileStatement->getPosition();
  range.setCol( ui );
  _DoWhileStatement->DoWhileStatement->setPosition( range );
}

void DoWhileStatementWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  DoWhileStatementWrapper* _DoWhileStatement = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _DoWhileStatement->DoWhileStatement->getPosition();
  range.setEndLine( ui );
  _DoWhileStatement->DoWhileStatement->setPosition( range );
}

void DoWhileStatementWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  DoWhileStatementWrapper* _DoWhileStatement = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _DoWhileStatement->DoWhileStatement->getPosition();
  range.setEndCol( ui );
  _DoWhileStatement->DoWhileStatement->setPosition( range );
}

void DoWhileStatementWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  DoWhileStatementWrapper* _DoWhileStatement = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _DoWhileStatement->DoWhileStatement->getPosition();
  range.setWideLine( ui );
  _DoWhileStatement->DoWhileStatement->setPosition( range );
}

void DoWhileStatementWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  DoWhileStatementWrapper* _DoWhileStatement = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _DoWhileStatement->DoWhileStatement->getPosition();
  range.setWideCol( ui );
  _DoWhileStatement->DoWhileStatement->setPosition( range );
}

void DoWhileStatementWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  DoWhileStatementWrapper* _DoWhileStatement = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _DoWhileStatement->DoWhileStatement->getPosition();
  range.setWideEndLine( ui );
  _DoWhileStatement->DoWhileStatement->setPosition( range );
}

void DoWhileStatementWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  DoWhileStatementWrapper* _DoWhileStatement = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _DoWhileStatement->DoWhileStatement->getPosition();
  range.setWideEndCol( ui );
  _DoWhileStatement->DoWhileStatement->setPosition( range );
}

}}}} //end of namespaces