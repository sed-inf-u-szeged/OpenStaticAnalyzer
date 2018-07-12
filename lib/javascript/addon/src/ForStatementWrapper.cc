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

#include "../inc/ForStatementWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> ForStatementWrapper::constructor;

void ForStatementWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "ForStatementWrapper"));             
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
  NODE_SET_PROTOTYPE_METHOD(tpl, "setUpdateArrayExpression", setUpdateArrayExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setUpdateArrowFunctionExpression", setUpdateArrowFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setUpdateAssignmentExpression", setUpdateAssignmentExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setUpdateAwaitExpression", setUpdateAwaitExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setUpdateBinaryExpression", setUpdateBinaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setUpdateCallExpression", setUpdateCallExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setUpdateClassExpression", setUpdateClassExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setUpdateConditionalExpression", setUpdateConditionalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setUpdateFunctionExpression", setUpdateFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setUpdateIdentifier", setUpdateIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setUpdateBooleanLiteral", setUpdateBooleanLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setUpdateNullLiteral", setUpdateNullLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setUpdateNumberLiteral", setUpdateNumberLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setUpdateRegExpLiteral", setUpdateRegExpLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setUpdateStringLiteral", setUpdateStringLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setUpdateLogicalExpression", setUpdateLogicalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setUpdateMemberExpression", setUpdateMemberExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setUpdateMetaProperty", setUpdateMetaProperty);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setUpdateNewExpression", setUpdateNewExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setUpdateObjectExpression", setUpdateObjectExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setUpdateSequenceExpression", setUpdateSequenceExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setUpdateTaggedTemplateExpression", setUpdateTaggedTemplateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setUpdateTemplateLiteral", setUpdateTemplateLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setUpdateThisExpression", setUpdateThisExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setUpdateUnaryExpression", setUpdateUnaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setUpdateUpdateExpression", setUpdateUpdateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setUpdateYieldExpression", setUpdateYieldExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitArrayExpression", setInitArrayExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitArrowFunctionExpression", setInitArrowFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitAssignmentExpression", setInitAssignmentExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitAwaitExpression", setInitAwaitExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitBinaryExpression", setInitBinaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitCallExpression", setInitCallExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitClassExpression", setInitClassExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitConditionalExpression", setInitConditionalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitFunctionExpression", setInitFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitIdentifier", setInitIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitBooleanLiteral", setInitBooleanLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitNullLiteral", setInitNullLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitNumberLiteral", setInitNumberLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitRegExpLiteral", setInitRegExpLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitStringLiteral", setInitStringLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitLogicalExpression", setInitLogicalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitMemberExpression", setInitMemberExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitMetaProperty", setInitMetaProperty);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitNewExpression", setInitNewExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitObjectExpression", setInitObjectExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitSequenceExpression", setInitSequenceExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitTaggedTemplateExpression", setInitTaggedTemplateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitTemplateLiteral", setInitTemplateLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitThisExpression", setInitThisExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitUnaryExpression", setInitUnaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitUpdateExpression", setInitUpdateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitYieldExpression", setInitYieldExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitVariableDeclaration", setInitVariableDeclaration);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "ForStatementWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void ForStatementWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new ForStatementWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    ForStatementWrapper* obj = new ForStatementWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `ForStatementWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


ForStatementWrapper::ForStatementWrapper(Factory* fact)                        
{                                                   
  ForStatement = fact->getFactory()->createForStatementNode();          
}                                                   

ForStatementWrapper::~ForStatementWrapper()
{        
}        

void ForStatementWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void ForStatementWrapper::setBodyClassDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassDeclarationWrapper* _ClassDeclaration1 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setBody(_ClassDeclaration1->ClassDeclaration);
}
void ForStatementWrapper::setBodyExportAllDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExportAllDeclarationWrapper* _ExportAllDeclaration1 = ObjectWrap::Unwrap<ExportAllDeclarationWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setBody(_ExportAllDeclaration1->ExportAllDeclaration);
}
void ForStatementWrapper::setBodyExportDefaultDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration1 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setBody(_ExportDefaultDeclaration1->ExportDefaultDeclaration);
}
void ForStatementWrapper::setBodyFunctionDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionDeclarationWrapper* _FunctionDeclaration1 = ObjectWrap::Unwrap<FunctionDeclarationWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setBody(_FunctionDeclaration1->FunctionDeclaration);
}
void ForStatementWrapper::setBodyVariableDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  VariableDeclarationWrapper* _VariableDeclaration1 = ObjectWrap::Unwrap<VariableDeclarationWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setBody(_VariableDeclaration1->VariableDeclaration);
}
void ForStatementWrapper::setBodyBlockStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BlockStatementWrapper* _BlockStatement1 = ObjectWrap::Unwrap<BlockStatementWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setBody(_BlockStatement1->BlockStatement);
}
void ForStatementWrapper::setBodyBreakStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BreakStatementWrapper* _BreakStatement1 = ObjectWrap::Unwrap<BreakStatementWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setBody(_BreakStatement1->BreakStatement);
}
void ForStatementWrapper::setBodyContinueStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ContinueStatementWrapper* _ContinueStatement1 = ObjectWrap::Unwrap<ContinueStatementWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setBody(_ContinueStatement1->ContinueStatement);
}
void ForStatementWrapper::setBodyDebuggerStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  DebuggerStatementWrapper* _DebuggerStatement1 = ObjectWrap::Unwrap<DebuggerStatementWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setBody(_DebuggerStatement1->DebuggerStatement);
}
void ForStatementWrapper::setBodyEmptyStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  EmptyStatementWrapper* _EmptyStatement1 = ObjectWrap::Unwrap<EmptyStatementWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setBody(_EmptyStatement1->EmptyStatement);
}
void ForStatementWrapper::setBodyExpressionStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExpressionStatementWrapper* _ExpressionStatement1 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setBody(_ExpressionStatement1->ExpressionStatement);
}
void ForStatementWrapper::setBodyForInStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ForInStatementWrapper* _ForInStatement1 = ObjectWrap::Unwrap<ForInStatementWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setBody(_ForInStatement1->ForInStatement);
}
void ForStatementWrapper::setBodyForOfStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ForOfStatementWrapper* _ForOfStatement1 = ObjectWrap::Unwrap<ForOfStatementWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setBody(_ForOfStatement1->ForOfStatement);
}
void ForStatementWrapper::setBodyForStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ForStatementWrapper* _ForStatement1 = ObjectWrap::Unwrap<ForStatementWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setBody(_ForStatement1->ForStatement);
}
void ForStatementWrapper::setBodyIfStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IfStatementWrapper* _IfStatement1 = ObjectWrap::Unwrap<IfStatementWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setBody(_IfStatement1->IfStatement);
}
void ForStatementWrapper::setBodyLabeledStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LabeledStatementWrapper* _LabeledStatement1 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setBody(_LabeledStatement1->LabeledStatement);
}
void ForStatementWrapper::setBodyReturnStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ReturnStatementWrapper* _ReturnStatement1 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setBody(_ReturnStatement1->ReturnStatement);
}
void ForStatementWrapper::setBodySwitchStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SwitchStatementWrapper* _SwitchStatement1 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setBody(_SwitchStatement1->SwitchStatement);
}
void ForStatementWrapper::setBodyThrowStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThrowStatementWrapper* _ThrowStatement1 = ObjectWrap::Unwrap<ThrowStatementWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setBody(_ThrowStatement1->ThrowStatement);
}
void ForStatementWrapper::setBodyTryStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TryStatementWrapper* _TryStatement1 = ObjectWrap::Unwrap<TryStatementWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setBody(_TryStatement1->TryStatement);
}
void ForStatementWrapper::setBodyWhileStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  WhileStatementWrapper* _WhileStatement1 = ObjectWrap::Unwrap<WhileStatementWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setBody(_WhileStatement1->WhileStatement);
}
void ForStatementWrapper::setBodyDoWhileStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  DoWhileStatementWrapper* _DoWhileStatement1 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setBody(_DoWhileStatement1->DoWhileStatement);
}
void ForStatementWrapper::setBodyWithStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  WithStatementWrapper* _WithStatement1 = ObjectWrap::Unwrap<WithStatementWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setBody(_WithStatement1->WithStatement);
}
void ForStatementWrapper::setTestArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setTest(_ArrayExpression1->ArrayExpression);
}
void ForStatementWrapper::setTestArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setTest(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void ForStatementWrapper::setTestAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setTest(_AssignmentExpression1->AssignmentExpression);
}
void ForStatementWrapper::setTestAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setTest(_AwaitExpression1->AwaitExpression);
}
void ForStatementWrapper::setTestBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setTest(_BinaryExpression1->BinaryExpression);
}
void ForStatementWrapper::setTestCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setTest(_CallExpression1->CallExpression);
}
void ForStatementWrapper::setTestClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setTest(_ClassExpression1->ClassExpression);
}
void ForStatementWrapper::setTestConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setTest(_ConditionalExpression1->ConditionalExpression);
}
void ForStatementWrapper::setTestFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setTest(_FunctionExpression1->FunctionExpression);
}
void ForStatementWrapper::setTestIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setTest(_Identifier1->Identifier);
}
void ForStatementWrapper::setTestBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setTest(_BooleanLiteral1->BooleanLiteral);
}
void ForStatementWrapper::setTestNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setTest(_NullLiteral1->NullLiteral);
}
void ForStatementWrapper::setTestNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setTest(_NumberLiteral1->NumberLiteral);
}
void ForStatementWrapper::setTestRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setTest(_RegExpLiteral1->RegExpLiteral);
}
void ForStatementWrapper::setTestStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setTest(_StringLiteral1->StringLiteral);
}
void ForStatementWrapper::setTestLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setTest(_LogicalExpression1->LogicalExpression);
}
void ForStatementWrapper::setTestMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setTest(_MemberExpression1->MemberExpression);
}
void ForStatementWrapper::setTestMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setTest(_MetaProperty1->MetaProperty);
}
void ForStatementWrapper::setTestNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setTest(_NewExpression1->NewExpression);
}
void ForStatementWrapper::setTestObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setTest(_ObjectExpression1->ObjectExpression);
}
void ForStatementWrapper::setTestSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setTest(_SequenceExpression1->SequenceExpression);
}
void ForStatementWrapper::setTestTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setTest(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void ForStatementWrapper::setTestTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setTest(_TemplateLiteral1->TemplateLiteral);
}
void ForStatementWrapper::setTestThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setTest(_ThisExpression1->ThisExpression);
}
void ForStatementWrapper::setTestUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setTest(_UnaryExpression1->UnaryExpression);
}
void ForStatementWrapper::setTestUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setTest(_UpdateExpression1->UpdateExpression);
}
void ForStatementWrapper::setTestYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setTest(_YieldExpression1->YieldExpression);
}
void ForStatementWrapper::setUpdateArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setUpdate(_ArrayExpression1->ArrayExpression);
}
void ForStatementWrapper::setUpdateArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setUpdate(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void ForStatementWrapper::setUpdateAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setUpdate(_AssignmentExpression1->AssignmentExpression);
}
void ForStatementWrapper::setUpdateAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setUpdate(_AwaitExpression1->AwaitExpression);
}
void ForStatementWrapper::setUpdateBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setUpdate(_BinaryExpression1->BinaryExpression);
}
void ForStatementWrapper::setUpdateCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setUpdate(_CallExpression1->CallExpression);
}
void ForStatementWrapper::setUpdateClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setUpdate(_ClassExpression1->ClassExpression);
}
void ForStatementWrapper::setUpdateConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setUpdate(_ConditionalExpression1->ConditionalExpression);
}
void ForStatementWrapper::setUpdateFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setUpdate(_FunctionExpression1->FunctionExpression);
}
void ForStatementWrapper::setUpdateIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setUpdate(_Identifier1->Identifier);
}
void ForStatementWrapper::setUpdateBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setUpdate(_BooleanLiteral1->BooleanLiteral);
}
void ForStatementWrapper::setUpdateNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setUpdate(_NullLiteral1->NullLiteral);
}
void ForStatementWrapper::setUpdateNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setUpdate(_NumberLiteral1->NumberLiteral);
}
void ForStatementWrapper::setUpdateRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setUpdate(_RegExpLiteral1->RegExpLiteral);
}
void ForStatementWrapper::setUpdateStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setUpdate(_StringLiteral1->StringLiteral);
}
void ForStatementWrapper::setUpdateLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setUpdate(_LogicalExpression1->LogicalExpression);
}
void ForStatementWrapper::setUpdateMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setUpdate(_MemberExpression1->MemberExpression);
}
void ForStatementWrapper::setUpdateMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setUpdate(_MetaProperty1->MetaProperty);
}
void ForStatementWrapper::setUpdateNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setUpdate(_NewExpression1->NewExpression);
}
void ForStatementWrapper::setUpdateObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setUpdate(_ObjectExpression1->ObjectExpression);
}
void ForStatementWrapper::setUpdateSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setUpdate(_SequenceExpression1->SequenceExpression);
}
void ForStatementWrapper::setUpdateTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setUpdate(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void ForStatementWrapper::setUpdateTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setUpdate(_TemplateLiteral1->TemplateLiteral);
}
void ForStatementWrapper::setUpdateThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setUpdate(_ThisExpression1->ThisExpression);
}
void ForStatementWrapper::setUpdateUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setUpdate(_UnaryExpression1->UnaryExpression);
}
void ForStatementWrapper::setUpdateUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setUpdate(_UpdateExpression1->UpdateExpression);
}
void ForStatementWrapper::setUpdateYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setUpdate(_YieldExpression1->YieldExpression);
}
void ForStatementWrapper::setInitArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setInit(_ArrayExpression1->ArrayExpression);
}
void ForStatementWrapper::setInitArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setInit(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void ForStatementWrapper::setInitAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setInit(_AssignmentExpression1->AssignmentExpression);
}
void ForStatementWrapper::setInitAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setInit(_AwaitExpression1->AwaitExpression);
}
void ForStatementWrapper::setInitBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setInit(_BinaryExpression1->BinaryExpression);
}
void ForStatementWrapper::setInitCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setInit(_CallExpression1->CallExpression);
}
void ForStatementWrapper::setInitClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setInit(_ClassExpression1->ClassExpression);
}
void ForStatementWrapper::setInitConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setInit(_ConditionalExpression1->ConditionalExpression);
}
void ForStatementWrapper::setInitFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setInit(_FunctionExpression1->FunctionExpression);
}
void ForStatementWrapper::setInitIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setInit(_Identifier1->Identifier);
}
void ForStatementWrapper::setInitBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setInit(_BooleanLiteral1->BooleanLiteral);
}
void ForStatementWrapper::setInitNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setInit(_NullLiteral1->NullLiteral);
}
void ForStatementWrapper::setInitNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setInit(_NumberLiteral1->NumberLiteral);
}
void ForStatementWrapper::setInitRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setInit(_RegExpLiteral1->RegExpLiteral);
}
void ForStatementWrapper::setInitStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setInit(_StringLiteral1->StringLiteral);
}
void ForStatementWrapper::setInitLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setInit(_LogicalExpression1->LogicalExpression);
}
void ForStatementWrapper::setInitMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setInit(_MemberExpression1->MemberExpression);
}
void ForStatementWrapper::setInitMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setInit(_MetaProperty1->MetaProperty);
}
void ForStatementWrapper::setInitNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setInit(_NewExpression1->NewExpression);
}
void ForStatementWrapper::setInitObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setInit(_ObjectExpression1->ObjectExpression);
}
void ForStatementWrapper::setInitSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setInit(_SequenceExpression1->SequenceExpression);
}
void ForStatementWrapper::setInitTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setInit(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void ForStatementWrapper::setInitTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setInit(_TemplateLiteral1->TemplateLiteral);
}
void ForStatementWrapper::setInitThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setInit(_ThisExpression1->ThisExpression);
}
void ForStatementWrapper::setInitUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setInit(_UnaryExpression1->UnaryExpression);
}
void ForStatementWrapper::setInitUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setInit(_UpdateExpression1->UpdateExpression);
}
void ForStatementWrapper::setInitYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setInit(_YieldExpression1->YieldExpression);
}
void ForStatementWrapper::setInitVariableDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  VariableDeclarationWrapper* _VariableDeclaration1 = ObjectWrap::Unwrap<VariableDeclarationWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->setInit(_VariableDeclaration1->VariableDeclaration);
}
void ForStatementWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  ForStatementWrapper* _ForStatement2 = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());

  _ForStatement2->ForStatement->addComments(_Comment1->Comment);
}
void ForStatementWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  ForStatementWrapper* _ForStatement = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _ForStatement->ForStatement->getPosition();
  range.setPath( param );
  _ForStatement->ForStatement->setPosition( range );
}

void ForStatementWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ForStatementWrapper* _ForStatement = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ForStatement->ForStatement->getPosition();
  range.setLine( ui );
  _ForStatement->ForStatement->setPosition( range );
}

void ForStatementWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ForStatementWrapper* _ForStatement = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ForStatement->ForStatement->getPosition();
  range.setCol( ui );
  _ForStatement->ForStatement->setPosition( range );
}

void ForStatementWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ForStatementWrapper* _ForStatement = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ForStatement->ForStatement->getPosition();
  range.setEndLine( ui );
  _ForStatement->ForStatement->setPosition( range );
}

void ForStatementWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ForStatementWrapper* _ForStatement = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ForStatement->ForStatement->getPosition();
  range.setEndCol( ui );
  _ForStatement->ForStatement->setPosition( range );
}

void ForStatementWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ForStatementWrapper* _ForStatement = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ForStatement->ForStatement->getPosition();
  range.setWideLine( ui );
  _ForStatement->ForStatement->setPosition( range );
}

void ForStatementWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ForStatementWrapper* _ForStatement = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ForStatement->ForStatement->getPosition();
  range.setWideCol( ui );
  _ForStatement->ForStatement->setPosition( range );
}

void ForStatementWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ForStatementWrapper* _ForStatement = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ForStatement->ForStatement->getPosition();
  range.setWideEndLine( ui );
  _ForStatement->ForStatement->setPosition( range );
}

void ForStatementWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ForStatementWrapper* _ForStatement = ObjectWrap::Unwrap<ForStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ForStatement->ForStatement->getPosition();
  range.setWideEndCol( ui );
  _ForStatement->ForStatement->setPosition( range );
}

}}}} //end of namespaces