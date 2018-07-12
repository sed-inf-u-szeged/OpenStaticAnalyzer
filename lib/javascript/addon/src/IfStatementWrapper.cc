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

#include "../inc/IfStatementWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> IfStatementWrapper::constructor;

void IfStatementWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "IfStatementWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
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
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentClassDeclaration", setConsequentClassDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentExportAllDeclaration", setConsequentExportAllDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentExportDefaultDeclaration", setConsequentExportDefaultDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentFunctionDeclaration", setConsequentFunctionDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentVariableDeclaration", setConsequentVariableDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentBlockStatement", setConsequentBlockStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentBreakStatement", setConsequentBreakStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentContinueStatement", setConsequentContinueStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentDebuggerStatement", setConsequentDebuggerStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentEmptyStatement", setConsequentEmptyStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentExpressionStatement", setConsequentExpressionStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentForInStatement", setConsequentForInStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentForOfStatement", setConsequentForOfStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentForStatement", setConsequentForStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentIfStatement", setConsequentIfStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentLabeledStatement", setConsequentLabeledStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentReturnStatement", setConsequentReturnStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentSwitchStatement", setConsequentSwitchStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentThrowStatement", setConsequentThrowStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentTryStatement", setConsequentTryStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentWhileStatement", setConsequentWhileStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentDoWhileStatement", setConsequentDoWhileStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentWithStatement", setConsequentWithStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateClassDeclaration", setAlternateClassDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateExportAllDeclaration", setAlternateExportAllDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateExportDefaultDeclaration", setAlternateExportDefaultDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateFunctionDeclaration", setAlternateFunctionDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateVariableDeclaration", setAlternateVariableDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateBlockStatement", setAlternateBlockStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateBreakStatement", setAlternateBreakStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateContinueStatement", setAlternateContinueStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateDebuggerStatement", setAlternateDebuggerStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateEmptyStatement", setAlternateEmptyStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateExpressionStatement", setAlternateExpressionStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateForInStatement", setAlternateForInStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateForOfStatement", setAlternateForOfStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateForStatement", setAlternateForStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateIfStatement", setAlternateIfStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateLabeledStatement", setAlternateLabeledStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateReturnStatement", setAlternateReturnStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateSwitchStatement", setAlternateSwitchStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateThrowStatement", setAlternateThrowStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateTryStatement", setAlternateTryStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateWhileStatement", setAlternateWhileStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateDoWhileStatement", setAlternateDoWhileStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateWithStatement", setAlternateWithStatement);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "IfStatementWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void IfStatementWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new IfStatementWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    IfStatementWrapper* obj = new IfStatementWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `IfStatementWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


IfStatementWrapper::IfStatementWrapper(Factory* fact)                        
{                                                   
  IfStatement = fact->getFactory()->createIfStatementNode();          
}                                                   

IfStatementWrapper::~IfStatementWrapper()
{        
}        

void IfStatementWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void IfStatementWrapper::setTestArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setTest(_ArrayExpression1->ArrayExpression);
}
void IfStatementWrapper::setTestArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setTest(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void IfStatementWrapper::setTestAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setTest(_AssignmentExpression1->AssignmentExpression);
}
void IfStatementWrapper::setTestAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setTest(_AwaitExpression1->AwaitExpression);
}
void IfStatementWrapper::setTestBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setTest(_BinaryExpression1->BinaryExpression);
}
void IfStatementWrapper::setTestCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setTest(_CallExpression1->CallExpression);
}
void IfStatementWrapper::setTestClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setTest(_ClassExpression1->ClassExpression);
}
void IfStatementWrapper::setTestConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setTest(_ConditionalExpression1->ConditionalExpression);
}
void IfStatementWrapper::setTestFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setTest(_FunctionExpression1->FunctionExpression);
}
void IfStatementWrapper::setTestIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setTest(_Identifier1->Identifier);
}
void IfStatementWrapper::setTestBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setTest(_BooleanLiteral1->BooleanLiteral);
}
void IfStatementWrapper::setTestNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setTest(_NullLiteral1->NullLiteral);
}
void IfStatementWrapper::setTestNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setTest(_NumberLiteral1->NumberLiteral);
}
void IfStatementWrapper::setTestRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setTest(_RegExpLiteral1->RegExpLiteral);
}
void IfStatementWrapper::setTestStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setTest(_StringLiteral1->StringLiteral);
}
void IfStatementWrapper::setTestLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setTest(_LogicalExpression1->LogicalExpression);
}
void IfStatementWrapper::setTestMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setTest(_MemberExpression1->MemberExpression);
}
void IfStatementWrapper::setTestMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setTest(_MetaProperty1->MetaProperty);
}
void IfStatementWrapper::setTestNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setTest(_NewExpression1->NewExpression);
}
void IfStatementWrapper::setTestObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setTest(_ObjectExpression1->ObjectExpression);
}
void IfStatementWrapper::setTestSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setTest(_SequenceExpression1->SequenceExpression);
}
void IfStatementWrapper::setTestTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setTest(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void IfStatementWrapper::setTestTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setTest(_TemplateLiteral1->TemplateLiteral);
}
void IfStatementWrapper::setTestThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setTest(_ThisExpression1->ThisExpression);
}
void IfStatementWrapper::setTestUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setTest(_UnaryExpression1->UnaryExpression);
}
void IfStatementWrapper::setTestUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setTest(_UpdateExpression1->UpdateExpression);
}
void IfStatementWrapper::setTestYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setTest(_YieldExpression1->YieldExpression);
}
void IfStatementWrapper::setConsequentClassDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassDeclarationWrapper* _ClassDeclaration1 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setConsequent(_ClassDeclaration1->ClassDeclaration);
}
void IfStatementWrapper::setConsequentExportAllDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExportAllDeclarationWrapper* _ExportAllDeclaration1 = ObjectWrap::Unwrap<ExportAllDeclarationWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setConsequent(_ExportAllDeclaration1->ExportAllDeclaration);
}
void IfStatementWrapper::setConsequentExportDefaultDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration1 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setConsequent(_ExportDefaultDeclaration1->ExportDefaultDeclaration);
}
void IfStatementWrapper::setConsequentFunctionDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionDeclarationWrapper* _FunctionDeclaration1 = ObjectWrap::Unwrap<FunctionDeclarationWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setConsequent(_FunctionDeclaration1->FunctionDeclaration);
}
void IfStatementWrapper::setConsequentVariableDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  VariableDeclarationWrapper* _VariableDeclaration1 = ObjectWrap::Unwrap<VariableDeclarationWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setConsequent(_VariableDeclaration1->VariableDeclaration);
}
void IfStatementWrapper::setConsequentBlockStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BlockStatementWrapper* _BlockStatement1 = ObjectWrap::Unwrap<BlockStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setConsequent(_BlockStatement1->BlockStatement);
}
void IfStatementWrapper::setConsequentBreakStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BreakStatementWrapper* _BreakStatement1 = ObjectWrap::Unwrap<BreakStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setConsequent(_BreakStatement1->BreakStatement);
}
void IfStatementWrapper::setConsequentContinueStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ContinueStatementWrapper* _ContinueStatement1 = ObjectWrap::Unwrap<ContinueStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setConsequent(_ContinueStatement1->ContinueStatement);
}
void IfStatementWrapper::setConsequentDebuggerStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  DebuggerStatementWrapper* _DebuggerStatement1 = ObjectWrap::Unwrap<DebuggerStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setConsequent(_DebuggerStatement1->DebuggerStatement);
}
void IfStatementWrapper::setConsequentEmptyStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  EmptyStatementWrapper* _EmptyStatement1 = ObjectWrap::Unwrap<EmptyStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setConsequent(_EmptyStatement1->EmptyStatement);
}
void IfStatementWrapper::setConsequentExpressionStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExpressionStatementWrapper* _ExpressionStatement1 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setConsequent(_ExpressionStatement1->ExpressionStatement);
}
void IfStatementWrapper::setConsequentForInStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ForInStatementWrapper* _ForInStatement1 = ObjectWrap::Unwrap<ForInStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setConsequent(_ForInStatement1->ForInStatement);
}
void IfStatementWrapper::setConsequentForOfStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ForOfStatementWrapper* _ForOfStatement1 = ObjectWrap::Unwrap<ForOfStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setConsequent(_ForOfStatement1->ForOfStatement);
}
void IfStatementWrapper::setConsequentForStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ForStatementWrapper* _ForStatement1 = ObjectWrap::Unwrap<ForStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setConsequent(_ForStatement1->ForStatement);
}
void IfStatementWrapper::setConsequentIfStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IfStatementWrapper* _IfStatement1 = ObjectWrap::Unwrap<IfStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setConsequent(_IfStatement1->IfStatement);
}
void IfStatementWrapper::setConsequentLabeledStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LabeledStatementWrapper* _LabeledStatement1 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setConsequent(_LabeledStatement1->LabeledStatement);
}
void IfStatementWrapper::setConsequentReturnStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ReturnStatementWrapper* _ReturnStatement1 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setConsequent(_ReturnStatement1->ReturnStatement);
}
void IfStatementWrapper::setConsequentSwitchStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SwitchStatementWrapper* _SwitchStatement1 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setConsequent(_SwitchStatement1->SwitchStatement);
}
void IfStatementWrapper::setConsequentThrowStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThrowStatementWrapper* _ThrowStatement1 = ObjectWrap::Unwrap<ThrowStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setConsequent(_ThrowStatement1->ThrowStatement);
}
void IfStatementWrapper::setConsequentTryStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TryStatementWrapper* _TryStatement1 = ObjectWrap::Unwrap<TryStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setConsequent(_TryStatement1->TryStatement);
}
void IfStatementWrapper::setConsequentWhileStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  WhileStatementWrapper* _WhileStatement1 = ObjectWrap::Unwrap<WhileStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setConsequent(_WhileStatement1->WhileStatement);
}
void IfStatementWrapper::setConsequentDoWhileStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  DoWhileStatementWrapper* _DoWhileStatement1 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setConsequent(_DoWhileStatement1->DoWhileStatement);
}
void IfStatementWrapper::setConsequentWithStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  WithStatementWrapper* _WithStatement1 = ObjectWrap::Unwrap<WithStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setConsequent(_WithStatement1->WithStatement);
}
void IfStatementWrapper::setAlternateClassDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassDeclarationWrapper* _ClassDeclaration1 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setAlternate(_ClassDeclaration1->ClassDeclaration);
}
void IfStatementWrapper::setAlternateExportAllDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExportAllDeclarationWrapper* _ExportAllDeclaration1 = ObjectWrap::Unwrap<ExportAllDeclarationWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setAlternate(_ExportAllDeclaration1->ExportAllDeclaration);
}
void IfStatementWrapper::setAlternateExportDefaultDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration1 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setAlternate(_ExportDefaultDeclaration1->ExportDefaultDeclaration);
}
void IfStatementWrapper::setAlternateFunctionDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionDeclarationWrapper* _FunctionDeclaration1 = ObjectWrap::Unwrap<FunctionDeclarationWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setAlternate(_FunctionDeclaration1->FunctionDeclaration);
}
void IfStatementWrapper::setAlternateVariableDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  VariableDeclarationWrapper* _VariableDeclaration1 = ObjectWrap::Unwrap<VariableDeclarationWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setAlternate(_VariableDeclaration1->VariableDeclaration);
}
void IfStatementWrapper::setAlternateBlockStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BlockStatementWrapper* _BlockStatement1 = ObjectWrap::Unwrap<BlockStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setAlternate(_BlockStatement1->BlockStatement);
}
void IfStatementWrapper::setAlternateBreakStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BreakStatementWrapper* _BreakStatement1 = ObjectWrap::Unwrap<BreakStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setAlternate(_BreakStatement1->BreakStatement);
}
void IfStatementWrapper::setAlternateContinueStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ContinueStatementWrapper* _ContinueStatement1 = ObjectWrap::Unwrap<ContinueStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setAlternate(_ContinueStatement1->ContinueStatement);
}
void IfStatementWrapper::setAlternateDebuggerStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  DebuggerStatementWrapper* _DebuggerStatement1 = ObjectWrap::Unwrap<DebuggerStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setAlternate(_DebuggerStatement1->DebuggerStatement);
}
void IfStatementWrapper::setAlternateEmptyStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  EmptyStatementWrapper* _EmptyStatement1 = ObjectWrap::Unwrap<EmptyStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setAlternate(_EmptyStatement1->EmptyStatement);
}
void IfStatementWrapper::setAlternateExpressionStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExpressionStatementWrapper* _ExpressionStatement1 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setAlternate(_ExpressionStatement1->ExpressionStatement);
}
void IfStatementWrapper::setAlternateForInStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ForInStatementWrapper* _ForInStatement1 = ObjectWrap::Unwrap<ForInStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setAlternate(_ForInStatement1->ForInStatement);
}
void IfStatementWrapper::setAlternateForOfStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ForOfStatementWrapper* _ForOfStatement1 = ObjectWrap::Unwrap<ForOfStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setAlternate(_ForOfStatement1->ForOfStatement);
}
void IfStatementWrapper::setAlternateForStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ForStatementWrapper* _ForStatement1 = ObjectWrap::Unwrap<ForStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setAlternate(_ForStatement1->ForStatement);
}
void IfStatementWrapper::setAlternateIfStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IfStatementWrapper* _IfStatement1 = ObjectWrap::Unwrap<IfStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setAlternate(_IfStatement1->IfStatement);
}
void IfStatementWrapper::setAlternateLabeledStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LabeledStatementWrapper* _LabeledStatement1 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setAlternate(_LabeledStatement1->LabeledStatement);
}
void IfStatementWrapper::setAlternateReturnStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ReturnStatementWrapper* _ReturnStatement1 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setAlternate(_ReturnStatement1->ReturnStatement);
}
void IfStatementWrapper::setAlternateSwitchStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SwitchStatementWrapper* _SwitchStatement1 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setAlternate(_SwitchStatement1->SwitchStatement);
}
void IfStatementWrapper::setAlternateThrowStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThrowStatementWrapper* _ThrowStatement1 = ObjectWrap::Unwrap<ThrowStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setAlternate(_ThrowStatement1->ThrowStatement);
}
void IfStatementWrapper::setAlternateTryStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TryStatementWrapper* _TryStatement1 = ObjectWrap::Unwrap<TryStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setAlternate(_TryStatement1->TryStatement);
}
void IfStatementWrapper::setAlternateWhileStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  WhileStatementWrapper* _WhileStatement1 = ObjectWrap::Unwrap<WhileStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setAlternate(_WhileStatement1->WhileStatement);
}
void IfStatementWrapper::setAlternateDoWhileStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  DoWhileStatementWrapper* _DoWhileStatement1 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setAlternate(_DoWhileStatement1->DoWhileStatement);
}
void IfStatementWrapper::setAlternateWithStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  WithStatementWrapper* _WithStatement1 = ObjectWrap::Unwrap<WithStatementWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->setAlternate(_WithStatement1->WithStatement);
}
void IfStatementWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  IfStatementWrapper* _IfStatement2 = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());

  _IfStatement2->IfStatement->addComments(_Comment1->Comment);
}
void IfStatementWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  IfStatementWrapper* _IfStatement = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _IfStatement->IfStatement->getPosition();
  range.setPath( param );
  _IfStatement->IfStatement->setPosition( range );
}

void IfStatementWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  IfStatementWrapper* _IfStatement = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _IfStatement->IfStatement->getPosition();
  range.setLine( ui );
  _IfStatement->IfStatement->setPosition( range );
}

void IfStatementWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  IfStatementWrapper* _IfStatement = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _IfStatement->IfStatement->getPosition();
  range.setCol( ui );
  _IfStatement->IfStatement->setPosition( range );
}

void IfStatementWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  IfStatementWrapper* _IfStatement = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _IfStatement->IfStatement->getPosition();
  range.setEndLine( ui );
  _IfStatement->IfStatement->setPosition( range );
}

void IfStatementWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  IfStatementWrapper* _IfStatement = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _IfStatement->IfStatement->getPosition();
  range.setEndCol( ui );
  _IfStatement->IfStatement->setPosition( range );
}

void IfStatementWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  IfStatementWrapper* _IfStatement = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _IfStatement->IfStatement->getPosition();
  range.setWideLine( ui );
  _IfStatement->IfStatement->setPosition( range );
}

void IfStatementWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  IfStatementWrapper* _IfStatement = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _IfStatement->IfStatement->getPosition();
  range.setWideCol( ui );
  _IfStatement->IfStatement->setPosition( range );
}

void IfStatementWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  IfStatementWrapper* _IfStatement = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _IfStatement->IfStatement->getPosition();
  range.setWideEndLine( ui );
  _IfStatement->IfStatement->setPosition( range );
}

void IfStatementWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  IfStatementWrapper* _IfStatement = ObjectWrap::Unwrap<IfStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _IfStatement->IfStatement->getPosition();
  range.setWideEndCol( ui );
  _IfStatement->IfStatement->setPosition( range );
}

}}}} //end of namespaces