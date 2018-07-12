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

#include "../inc/WithStatementWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> WithStatementWrapper::constructor;

void WithStatementWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "WithStatementWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "setObjectArrayExpression", setObjectArrayExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setObjectArrowFunctionExpression", setObjectArrowFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setObjectAssignmentExpression", setObjectAssignmentExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setObjectAwaitExpression", setObjectAwaitExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setObjectBinaryExpression", setObjectBinaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setObjectCallExpression", setObjectCallExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setObjectClassExpression", setObjectClassExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setObjectConditionalExpression", setObjectConditionalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setObjectFunctionExpression", setObjectFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setObjectIdentifier", setObjectIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setObjectBooleanLiteral", setObjectBooleanLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setObjectNullLiteral", setObjectNullLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setObjectNumberLiteral", setObjectNumberLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setObjectRegExpLiteral", setObjectRegExpLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setObjectStringLiteral", setObjectStringLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setObjectLogicalExpression", setObjectLogicalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setObjectMemberExpression", setObjectMemberExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setObjectMetaProperty", setObjectMetaProperty);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setObjectNewExpression", setObjectNewExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setObjectObjectExpression", setObjectObjectExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setObjectSequenceExpression", setObjectSequenceExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setObjectTaggedTemplateExpression", setObjectTaggedTemplateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setObjectTemplateLiteral", setObjectTemplateLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setObjectThisExpression", setObjectThisExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setObjectUnaryExpression", setObjectUnaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setObjectUpdateExpression", setObjectUpdateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setObjectYieldExpression", setObjectYieldExpression);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "WithStatementWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void WithStatementWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new WithStatementWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    WithStatementWrapper* obj = new WithStatementWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `WithStatementWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


WithStatementWrapper::WithStatementWrapper(Factory* fact)                        
{                                                   
  WithStatement = fact->getFactory()->createWithStatementNode();          
}                                                   

WithStatementWrapper::~WithStatementWrapper()
{        
}        

void WithStatementWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void WithStatementWrapper::setObjectArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setObject(_ArrayExpression1->ArrayExpression);
}
void WithStatementWrapper::setObjectArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setObject(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void WithStatementWrapper::setObjectAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setObject(_AssignmentExpression1->AssignmentExpression);
}
void WithStatementWrapper::setObjectAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setObject(_AwaitExpression1->AwaitExpression);
}
void WithStatementWrapper::setObjectBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setObject(_BinaryExpression1->BinaryExpression);
}
void WithStatementWrapper::setObjectCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setObject(_CallExpression1->CallExpression);
}
void WithStatementWrapper::setObjectClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setObject(_ClassExpression1->ClassExpression);
}
void WithStatementWrapper::setObjectConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setObject(_ConditionalExpression1->ConditionalExpression);
}
void WithStatementWrapper::setObjectFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setObject(_FunctionExpression1->FunctionExpression);
}
void WithStatementWrapper::setObjectIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setObject(_Identifier1->Identifier);
}
void WithStatementWrapper::setObjectBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setObject(_BooleanLiteral1->BooleanLiteral);
}
void WithStatementWrapper::setObjectNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setObject(_NullLiteral1->NullLiteral);
}
void WithStatementWrapper::setObjectNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setObject(_NumberLiteral1->NumberLiteral);
}
void WithStatementWrapper::setObjectRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setObject(_RegExpLiteral1->RegExpLiteral);
}
void WithStatementWrapper::setObjectStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setObject(_StringLiteral1->StringLiteral);
}
void WithStatementWrapper::setObjectLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setObject(_LogicalExpression1->LogicalExpression);
}
void WithStatementWrapper::setObjectMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setObject(_MemberExpression1->MemberExpression);
}
void WithStatementWrapper::setObjectMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setObject(_MetaProperty1->MetaProperty);
}
void WithStatementWrapper::setObjectNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setObject(_NewExpression1->NewExpression);
}
void WithStatementWrapper::setObjectObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setObject(_ObjectExpression1->ObjectExpression);
}
void WithStatementWrapper::setObjectSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setObject(_SequenceExpression1->SequenceExpression);
}
void WithStatementWrapper::setObjectTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setObject(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void WithStatementWrapper::setObjectTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setObject(_TemplateLiteral1->TemplateLiteral);
}
void WithStatementWrapper::setObjectThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setObject(_ThisExpression1->ThisExpression);
}
void WithStatementWrapper::setObjectUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setObject(_UnaryExpression1->UnaryExpression);
}
void WithStatementWrapper::setObjectUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setObject(_UpdateExpression1->UpdateExpression);
}
void WithStatementWrapper::setObjectYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setObject(_YieldExpression1->YieldExpression);
}
void WithStatementWrapper::setBodyClassDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassDeclarationWrapper* _ClassDeclaration1 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setBody(_ClassDeclaration1->ClassDeclaration);
}
void WithStatementWrapper::setBodyExportAllDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExportAllDeclarationWrapper* _ExportAllDeclaration1 = ObjectWrap::Unwrap<ExportAllDeclarationWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setBody(_ExportAllDeclaration1->ExportAllDeclaration);
}
void WithStatementWrapper::setBodyExportDefaultDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration1 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setBody(_ExportDefaultDeclaration1->ExportDefaultDeclaration);
}
void WithStatementWrapper::setBodyFunctionDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionDeclarationWrapper* _FunctionDeclaration1 = ObjectWrap::Unwrap<FunctionDeclarationWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setBody(_FunctionDeclaration1->FunctionDeclaration);
}
void WithStatementWrapper::setBodyVariableDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  VariableDeclarationWrapper* _VariableDeclaration1 = ObjectWrap::Unwrap<VariableDeclarationWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setBody(_VariableDeclaration1->VariableDeclaration);
}
void WithStatementWrapper::setBodyBlockStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BlockStatementWrapper* _BlockStatement1 = ObjectWrap::Unwrap<BlockStatementWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setBody(_BlockStatement1->BlockStatement);
}
void WithStatementWrapper::setBodyBreakStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BreakStatementWrapper* _BreakStatement1 = ObjectWrap::Unwrap<BreakStatementWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setBody(_BreakStatement1->BreakStatement);
}
void WithStatementWrapper::setBodyContinueStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ContinueStatementWrapper* _ContinueStatement1 = ObjectWrap::Unwrap<ContinueStatementWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setBody(_ContinueStatement1->ContinueStatement);
}
void WithStatementWrapper::setBodyDebuggerStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  DebuggerStatementWrapper* _DebuggerStatement1 = ObjectWrap::Unwrap<DebuggerStatementWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setBody(_DebuggerStatement1->DebuggerStatement);
}
void WithStatementWrapper::setBodyEmptyStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  EmptyStatementWrapper* _EmptyStatement1 = ObjectWrap::Unwrap<EmptyStatementWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setBody(_EmptyStatement1->EmptyStatement);
}
void WithStatementWrapper::setBodyExpressionStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExpressionStatementWrapper* _ExpressionStatement1 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setBody(_ExpressionStatement1->ExpressionStatement);
}
void WithStatementWrapper::setBodyForInStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ForInStatementWrapper* _ForInStatement1 = ObjectWrap::Unwrap<ForInStatementWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setBody(_ForInStatement1->ForInStatement);
}
void WithStatementWrapper::setBodyForOfStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ForOfStatementWrapper* _ForOfStatement1 = ObjectWrap::Unwrap<ForOfStatementWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setBody(_ForOfStatement1->ForOfStatement);
}
void WithStatementWrapper::setBodyForStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ForStatementWrapper* _ForStatement1 = ObjectWrap::Unwrap<ForStatementWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setBody(_ForStatement1->ForStatement);
}
void WithStatementWrapper::setBodyIfStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IfStatementWrapper* _IfStatement1 = ObjectWrap::Unwrap<IfStatementWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setBody(_IfStatement1->IfStatement);
}
void WithStatementWrapper::setBodyLabeledStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LabeledStatementWrapper* _LabeledStatement1 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setBody(_LabeledStatement1->LabeledStatement);
}
void WithStatementWrapper::setBodyReturnStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ReturnStatementWrapper* _ReturnStatement1 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setBody(_ReturnStatement1->ReturnStatement);
}
void WithStatementWrapper::setBodySwitchStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SwitchStatementWrapper* _SwitchStatement1 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setBody(_SwitchStatement1->SwitchStatement);
}
void WithStatementWrapper::setBodyThrowStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThrowStatementWrapper* _ThrowStatement1 = ObjectWrap::Unwrap<ThrowStatementWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setBody(_ThrowStatement1->ThrowStatement);
}
void WithStatementWrapper::setBodyTryStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TryStatementWrapper* _TryStatement1 = ObjectWrap::Unwrap<TryStatementWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setBody(_TryStatement1->TryStatement);
}
void WithStatementWrapper::setBodyWhileStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  WhileStatementWrapper* _WhileStatement1 = ObjectWrap::Unwrap<WhileStatementWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setBody(_WhileStatement1->WhileStatement);
}
void WithStatementWrapper::setBodyDoWhileStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  DoWhileStatementWrapper* _DoWhileStatement1 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setBody(_DoWhileStatement1->DoWhileStatement);
}
void WithStatementWrapper::setBodyWithStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  WithStatementWrapper* _WithStatement1 = ObjectWrap::Unwrap<WithStatementWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->setBody(_WithStatement1->WithStatement);
}
void WithStatementWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  WithStatementWrapper* _WithStatement2 = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());

  _WithStatement2->WithStatement->addComments(_Comment1->Comment);
}
void WithStatementWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  WithStatementWrapper* _WithStatement = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _WithStatement->WithStatement->getPosition();
  range.setPath( param );
  _WithStatement->WithStatement->setPosition( range );
}

void WithStatementWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  WithStatementWrapper* _WithStatement = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _WithStatement->WithStatement->getPosition();
  range.setLine( ui );
  _WithStatement->WithStatement->setPosition( range );
}

void WithStatementWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  WithStatementWrapper* _WithStatement = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _WithStatement->WithStatement->getPosition();
  range.setCol( ui );
  _WithStatement->WithStatement->setPosition( range );
}

void WithStatementWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  WithStatementWrapper* _WithStatement = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _WithStatement->WithStatement->getPosition();
  range.setEndLine( ui );
  _WithStatement->WithStatement->setPosition( range );
}

void WithStatementWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  WithStatementWrapper* _WithStatement = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _WithStatement->WithStatement->getPosition();
  range.setEndCol( ui );
  _WithStatement->WithStatement->setPosition( range );
}

void WithStatementWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  WithStatementWrapper* _WithStatement = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _WithStatement->WithStatement->getPosition();
  range.setWideLine( ui );
  _WithStatement->WithStatement->setPosition( range );
}

void WithStatementWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  WithStatementWrapper* _WithStatement = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _WithStatement->WithStatement->getPosition();
  range.setWideCol( ui );
  _WithStatement->WithStatement->setPosition( range );
}

void WithStatementWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  WithStatementWrapper* _WithStatement = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _WithStatement->WithStatement->getPosition();
  range.setWideEndLine( ui );
  _WithStatement->WithStatement->setPosition( range );
}

void WithStatementWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  WithStatementWrapper* _WithStatement = ObjectWrap::Unwrap<WithStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _WithStatement->WithStatement->getPosition();
  range.setWideEndCol( ui );
  _WithStatement->WithStatement->setPosition( range );
}

}}}} //end of namespaces