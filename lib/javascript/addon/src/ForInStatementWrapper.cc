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

#include "../inc/ForInStatementWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> ForInStatementWrapper::constructor;

void ForInStatementWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "ForInStatementWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRightArrayExpression", setRightArrayExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRightArrowFunctionExpression", setRightArrowFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRightAssignmentExpression", setRightAssignmentExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRightAwaitExpression", setRightAwaitExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRightBinaryExpression", setRightBinaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRightCallExpression", setRightCallExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRightClassExpression", setRightClassExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRightConditionalExpression", setRightConditionalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRightFunctionExpression", setRightFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRightIdentifier", setRightIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRightBooleanLiteral", setRightBooleanLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRightNullLiteral", setRightNullLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRightNumberLiteral", setRightNumberLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRightRegExpLiteral", setRightRegExpLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRightStringLiteral", setRightStringLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRightLogicalExpression", setRightLogicalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRightMemberExpression", setRightMemberExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRightMetaProperty", setRightMetaProperty);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRightNewExpression", setRightNewExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRightObjectExpression", setRightObjectExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRightSequenceExpression", setRightSequenceExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRightTaggedTemplateExpression", setRightTaggedTemplateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRightTemplateLiteral", setRightTemplateLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRightThisExpression", setRightThisExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRightUnaryExpression", setRightUnaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRightUpdateExpression", setRightUpdateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRightYieldExpression", setRightYieldExpression);
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
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftIdentifier", setLeftIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftMemberExpression", setLeftMemberExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftArrayPattern", setLeftArrayPattern);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftAssignmentPattern", setLeftAssignmentPattern);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftObjectPattern", setLeftObjectPattern);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftRestElement", setLeftRestElement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftVariableDeclaration", setLeftVariableDeclaration);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "ForInStatementWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void ForInStatementWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new ForInStatementWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    ForInStatementWrapper* obj = new ForInStatementWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `ForInStatementWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


ForInStatementWrapper::ForInStatementWrapper(Factory* fact)                        
{                                                   
  ForInStatement = fact->getFactory()->createForInStatementNode();          
}                                                   

ForInStatementWrapper::~ForInStatementWrapper()
{        
}        

void ForInStatementWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void ForInStatementWrapper::setRightArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setRight(_ArrayExpression1->ArrayExpression);
}
void ForInStatementWrapper::setRightArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setRight(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void ForInStatementWrapper::setRightAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setRight(_AssignmentExpression1->AssignmentExpression);
}
void ForInStatementWrapper::setRightAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setRight(_AwaitExpression1->AwaitExpression);
}
void ForInStatementWrapper::setRightBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setRight(_BinaryExpression1->BinaryExpression);
}
void ForInStatementWrapper::setRightCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setRight(_CallExpression1->CallExpression);
}
void ForInStatementWrapper::setRightClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setRight(_ClassExpression1->ClassExpression);
}
void ForInStatementWrapper::setRightConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setRight(_ConditionalExpression1->ConditionalExpression);
}
void ForInStatementWrapper::setRightFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setRight(_FunctionExpression1->FunctionExpression);
}
void ForInStatementWrapper::setRightIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setRight(_Identifier1->Identifier);
}
void ForInStatementWrapper::setRightBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setRight(_BooleanLiteral1->BooleanLiteral);
}
void ForInStatementWrapper::setRightNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setRight(_NullLiteral1->NullLiteral);
}
void ForInStatementWrapper::setRightNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setRight(_NumberLiteral1->NumberLiteral);
}
void ForInStatementWrapper::setRightRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setRight(_RegExpLiteral1->RegExpLiteral);
}
void ForInStatementWrapper::setRightStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setRight(_StringLiteral1->StringLiteral);
}
void ForInStatementWrapper::setRightLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setRight(_LogicalExpression1->LogicalExpression);
}
void ForInStatementWrapper::setRightMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setRight(_MemberExpression1->MemberExpression);
}
void ForInStatementWrapper::setRightMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setRight(_MetaProperty1->MetaProperty);
}
void ForInStatementWrapper::setRightNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setRight(_NewExpression1->NewExpression);
}
void ForInStatementWrapper::setRightObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setRight(_ObjectExpression1->ObjectExpression);
}
void ForInStatementWrapper::setRightSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setRight(_SequenceExpression1->SequenceExpression);
}
void ForInStatementWrapper::setRightTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setRight(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void ForInStatementWrapper::setRightTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setRight(_TemplateLiteral1->TemplateLiteral);
}
void ForInStatementWrapper::setRightThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setRight(_ThisExpression1->ThisExpression);
}
void ForInStatementWrapper::setRightUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setRight(_UnaryExpression1->UnaryExpression);
}
void ForInStatementWrapper::setRightUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setRight(_UpdateExpression1->UpdateExpression);
}
void ForInStatementWrapper::setRightYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setRight(_YieldExpression1->YieldExpression);
}
void ForInStatementWrapper::setBodyClassDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassDeclarationWrapper* _ClassDeclaration1 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setBody(_ClassDeclaration1->ClassDeclaration);
}
void ForInStatementWrapper::setBodyExportAllDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExportAllDeclarationWrapper* _ExportAllDeclaration1 = ObjectWrap::Unwrap<ExportAllDeclarationWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setBody(_ExportAllDeclaration1->ExportAllDeclaration);
}
void ForInStatementWrapper::setBodyExportDefaultDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration1 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setBody(_ExportDefaultDeclaration1->ExportDefaultDeclaration);
}
void ForInStatementWrapper::setBodyFunctionDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionDeclarationWrapper* _FunctionDeclaration1 = ObjectWrap::Unwrap<FunctionDeclarationWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setBody(_FunctionDeclaration1->FunctionDeclaration);
}
void ForInStatementWrapper::setBodyVariableDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  VariableDeclarationWrapper* _VariableDeclaration1 = ObjectWrap::Unwrap<VariableDeclarationWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setBody(_VariableDeclaration1->VariableDeclaration);
}
void ForInStatementWrapper::setBodyBlockStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BlockStatementWrapper* _BlockStatement1 = ObjectWrap::Unwrap<BlockStatementWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setBody(_BlockStatement1->BlockStatement);
}
void ForInStatementWrapper::setBodyBreakStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BreakStatementWrapper* _BreakStatement1 = ObjectWrap::Unwrap<BreakStatementWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setBody(_BreakStatement1->BreakStatement);
}
void ForInStatementWrapper::setBodyContinueStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ContinueStatementWrapper* _ContinueStatement1 = ObjectWrap::Unwrap<ContinueStatementWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setBody(_ContinueStatement1->ContinueStatement);
}
void ForInStatementWrapper::setBodyDebuggerStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  DebuggerStatementWrapper* _DebuggerStatement1 = ObjectWrap::Unwrap<DebuggerStatementWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setBody(_DebuggerStatement1->DebuggerStatement);
}
void ForInStatementWrapper::setBodyEmptyStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  EmptyStatementWrapper* _EmptyStatement1 = ObjectWrap::Unwrap<EmptyStatementWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setBody(_EmptyStatement1->EmptyStatement);
}
void ForInStatementWrapper::setBodyExpressionStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExpressionStatementWrapper* _ExpressionStatement1 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setBody(_ExpressionStatement1->ExpressionStatement);
}
void ForInStatementWrapper::setBodyForInStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ForInStatementWrapper* _ForInStatement1 = ObjectWrap::Unwrap<ForInStatementWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setBody(_ForInStatement1->ForInStatement);
}
void ForInStatementWrapper::setBodyForOfStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ForOfStatementWrapper* _ForOfStatement1 = ObjectWrap::Unwrap<ForOfStatementWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setBody(_ForOfStatement1->ForOfStatement);
}
void ForInStatementWrapper::setBodyForStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ForStatementWrapper* _ForStatement1 = ObjectWrap::Unwrap<ForStatementWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setBody(_ForStatement1->ForStatement);
}
void ForInStatementWrapper::setBodyIfStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IfStatementWrapper* _IfStatement1 = ObjectWrap::Unwrap<IfStatementWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setBody(_IfStatement1->IfStatement);
}
void ForInStatementWrapper::setBodyLabeledStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LabeledStatementWrapper* _LabeledStatement1 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setBody(_LabeledStatement1->LabeledStatement);
}
void ForInStatementWrapper::setBodyReturnStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ReturnStatementWrapper* _ReturnStatement1 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setBody(_ReturnStatement1->ReturnStatement);
}
void ForInStatementWrapper::setBodySwitchStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SwitchStatementWrapper* _SwitchStatement1 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setBody(_SwitchStatement1->SwitchStatement);
}
void ForInStatementWrapper::setBodyThrowStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThrowStatementWrapper* _ThrowStatement1 = ObjectWrap::Unwrap<ThrowStatementWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setBody(_ThrowStatement1->ThrowStatement);
}
void ForInStatementWrapper::setBodyTryStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TryStatementWrapper* _TryStatement1 = ObjectWrap::Unwrap<TryStatementWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setBody(_TryStatement1->TryStatement);
}
void ForInStatementWrapper::setBodyWhileStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  WhileStatementWrapper* _WhileStatement1 = ObjectWrap::Unwrap<WhileStatementWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setBody(_WhileStatement1->WhileStatement);
}
void ForInStatementWrapper::setBodyDoWhileStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  DoWhileStatementWrapper* _DoWhileStatement1 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setBody(_DoWhileStatement1->DoWhileStatement);
}
void ForInStatementWrapper::setBodyWithStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  WithStatementWrapper* _WithStatement1 = ObjectWrap::Unwrap<WithStatementWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setBody(_WithStatement1->WithStatement);
}
void ForInStatementWrapper::setLeftIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setLeft(_Identifier1->Identifier);
}
void ForInStatementWrapper::setLeftMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setLeft(_MemberExpression1->MemberExpression);
}
void ForInStatementWrapper::setLeftArrayPattern(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayPatternWrapper* _ArrayPattern1 = ObjectWrap::Unwrap<ArrayPatternWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setLeft(_ArrayPattern1->ArrayPattern);
}
void ForInStatementWrapper::setLeftAssignmentPattern(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentPatternWrapper* _AssignmentPattern1 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setLeft(_AssignmentPattern1->AssignmentPattern);
}
void ForInStatementWrapper::setLeftObjectPattern(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectPatternWrapper* _ObjectPattern1 = ObjectWrap::Unwrap<ObjectPatternWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setLeft(_ObjectPattern1->ObjectPattern);
}
void ForInStatementWrapper::setLeftRestElement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RestElementWrapper* _RestElement1 = ObjectWrap::Unwrap<RestElementWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setLeft(_RestElement1->RestElement);
}
void ForInStatementWrapper::setLeftVariableDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  VariableDeclarationWrapper* _VariableDeclaration1 = ObjectWrap::Unwrap<VariableDeclarationWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->setLeft(_VariableDeclaration1->VariableDeclaration);
}
void ForInStatementWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  ForInStatementWrapper* _ForInStatement2 = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());

  _ForInStatement2->ForInStatement->addComments(_Comment1->Comment);
}
void ForInStatementWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  ForInStatementWrapper* _ForInStatement = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _ForInStatement->ForInStatement->getPosition();
  range.setPath( param );
  _ForInStatement->ForInStatement->setPosition( range );
}

void ForInStatementWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ForInStatementWrapper* _ForInStatement = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ForInStatement->ForInStatement->getPosition();
  range.setLine( ui );
  _ForInStatement->ForInStatement->setPosition( range );
}

void ForInStatementWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ForInStatementWrapper* _ForInStatement = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ForInStatement->ForInStatement->getPosition();
  range.setCol( ui );
  _ForInStatement->ForInStatement->setPosition( range );
}

void ForInStatementWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ForInStatementWrapper* _ForInStatement = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ForInStatement->ForInStatement->getPosition();
  range.setEndLine( ui );
  _ForInStatement->ForInStatement->setPosition( range );
}

void ForInStatementWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ForInStatementWrapper* _ForInStatement = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ForInStatement->ForInStatement->getPosition();
  range.setEndCol( ui );
  _ForInStatement->ForInStatement->setPosition( range );
}

void ForInStatementWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ForInStatementWrapper* _ForInStatement = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ForInStatement->ForInStatement->getPosition();
  range.setWideLine( ui );
  _ForInStatement->ForInStatement->setPosition( range );
}

void ForInStatementWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ForInStatementWrapper* _ForInStatement = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ForInStatement->ForInStatement->getPosition();
  range.setWideCol( ui );
  _ForInStatement->ForInStatement->setPosition( range );
}

void ForInStatementWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ForInStatementWrapper* _ForInStatement = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ForInStatement->ForInStatement->getPosition();
  range.setWideEndLine( ui );
  _ForInStatement->ForInStatement->setPosition( range );
}

void ForInStatementWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ForInStatementWrapper* _ForInStatement = ObjectWrap::Unwrap<ForInStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ForInStatement->ForInStatement->getPosition();
  range.setWideEndCol( ui );
  _ForInStatement->ForInStatement->setPosition( range );
}

}}}} //end of namespaces