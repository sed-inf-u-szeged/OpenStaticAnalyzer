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

#include "../inc/SwitchCaseWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> SwitchCaseWrapper::constructor;

void SwitchCaseWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "SwitchCaseWrapper"));             
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
  NODE_SET_PROTOTYPE_METHOD(tpl, "addConsequentClassDeclaration", addConsequentClassDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addConsequentExportAllDeclaration", addConsequentExportAllDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addConsequentExportDefaultDeclaration", addConsequentExportDefaultDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addConsequentFunctionDeclaration", addConsequentFunctionDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addConsequentVariableDeclaration", addConsequentVariableDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addConsequentBlockStatement", addConsequentBlockStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addConsequentBreakStatement", addConsequentBreakStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addConsequentContinueStatement", addConsequentContinueStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addConsequentDebuggerStatement", addConsequentDebuggerStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addConsequentEmptyStatement", addConsequentEmptyStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addConsequentExpressionStatement", addConsequentExpressionStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addConsequentForInStatement", addConsequentForInStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addConsequentForOfStatement", addConsequentForOfStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addConsequentForStatement", addConsequentForStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addConsequentIfStatement", addConsequentIfStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addConsequentLabeledStatement", addConsequentLabeledStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addConsequentReturnStatement", addConsequentReturnStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addConsequentSwitchStatement", addConsequentSwitchStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addConsequentThrowStatement", addConsequentThrowStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addConsequentTryStatement", addConsequentTryStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addConsequentWhileStatement", addConsequentWhileStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addConsequentDoWhileStatement", addConsequentDoWhileStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addConsequentWithStatement", addConsequentWithStatement);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "SwitchCaseWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void SwitchCaseWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new SwitchCaseWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    SwitchCaseWrapper* obj = new SwitchCaseWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `SwitchCaseWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


SwitchCaseWrapper::SwitchCaseWrapper(Factory* fact)                        
{                                                   
  SwitchCase = fact->getFactory()->createSwitchCaseNode();          
}                                                   

SwitchCaseWrapper::~SwitchCaseWrapper()
{        
}        

void SwitchCaseWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void SwitchCaseWrapper::setTestArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->setTest(_ArrayExpression1->ArrayExpression);
}
void SwitchCaseWrapper::setTestArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->setTest(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void SwitchCaseWrapper::setTestAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->setTest(_AssignmentExpression1->AssignmentExpression);
}
void SwitchCaseWrapper::setTestAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->setTest(_AwaitExpression1->AwaitExpression);
}
void SwitchCaseWrapper::setTestBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->setTest(_BinaryExpression1->BinaryExpression);
}
void SwitchCaseWrapper::setTestCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->setTest(_CallExpression1->CallExpression);
}
void SwitchCaseWrapper::setTestClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->setTest(_ClassExpression1->ClassExpression);
}
void SwitchCaseWrapper::setTestConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->setTest(_ConditionalExpression1->ConditionalExpression);
}
void SwitchCaseWrapper::setTestFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->setTest(_FunctionExpression1->FunctionExpression);
}
void SwitchCaseWrapper::setTestIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->setTest(_Identifier1->Identifier);
}
void SwitchCaseWrapper::setTestBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->setTest(_BooleanLiteral1->BooleanLiteral);
}
void SwitchCaseWrapper::setTestNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->setTest(_NullLiteral1->NullLiteral);
}
void SwitchCaseWrapper::setTestNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->setTest(_NumberLiteral1->NumberLiteral);
}
void SwitchCaseWrapper::setTestRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->setTest(_RegExpLiteral1->RegExpLiteral);
}
void SwitchCaseWrapper::setTestStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->setTest(_StringLiteral1->StringLiteral);
}
void SwitchCaseWrapper::setTestLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->setTest(_LogicalExpression1->LogicalExpression);
}
void SwitchCaseWrapper::setTestMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->setTest(_MemberExpression1->MemberExpression);
}
void SwitchCaseWrapper::setTestMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->setTest(_MetaProperty1->MetaProperty);
}
void SwitchCaseWrapper::setTestNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->setTest(_NewExpression1->NewExpression);
}
void SwitchCaseWrapper::setTestObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->setTest(_ObjectExpression1->ObjectExpression);
}
void SwitchCaseWrapper::setTestSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->setTest(_SequenceExpression1->SequenceExpression);
}
void SwitchCaseWrapper::setTestTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->setTest(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void SwitchCaseWrapper::setTestTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->setTest(_TemplateLiteral1->TemplateLiteral);
}
void SwitchCaseWrapper::setTestThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->setTest(_ThisExpression1->ThisExpression);
}
void SwitchCaseWrapper::setTestUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->setTest(_UnaryExpression1->UnaryExpression);
}
void SwitchCaseWrapper::setTestUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->setTest(_UpdateExpression1->UpdateExpression);
}
void SwitchCaseWrapper::setTestYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->setTest(_YieldExpression1->YieldExpression);
}
void SwitchCaseWrapper::addConsequentClassDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassDeclarationWrapper* _ClassDeclaration1 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->addConsequent(_ClassDeclaration1->ClassDeclaration);
}
void SwitchCaseWrapper::addConsequentExportAllDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExportAllDeclarationWrapper* _ExportAllDeclaration1 = ObjectWrap::Unwrap<ExportAllDeclarationWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->addConsequent(_ExportAllDeclaration1->ExportAllDeclaration);
}
void SwitchCaseWrapper::addConsequentExportDefaultDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration1 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->addConsequent(_ExportDefaultDeclaration1->ExportDefaultDeclaration);
}
void SwitchCaseWrapper::addConsequentFunctionDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionDeclarationWrapper* _FunctionDeclaration1 = ObjectWrap::Unwrap<FunctionDeclarationWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->addConsequent(_FunctionDeclaration1->FunctionDeclaration);
}
void SwitchCaseWrapper::addConsequentVariableDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  VariableDeclarationWrapper* _VariableDeclaration1 = ObjectWrap::Unwrap<VariableDeclarationWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->addConsequent(_VariableDeclaration1->VariableDeclaration);
}
void SwitchCaseWrapper::addConsequentBlockStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BlockStatementWrapper* _BlockStatement1 = ObjectWrap::Unwrap<BlockStatementWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->addConsequent(_BlockStatement1->BlockStatement);
}
void SwitchCaseWrapper::addConsequentBreakStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BreakStatementWrapper* _BreakStatement1 = ObjectWrap::Unwrap<BreakStatementWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->addConsequent(_BreakStatement1->BreakStatement);
}
void SwitchCaseWrapper::addConsequentContinueStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ContinueStatementWrapper* _ContinueStatement1 = ObjectWrap::Unwrap<ContinueStatementWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->addConsequent(_ContinueStatement1->ContinueStatement);
}
void SwitchCaseWrapper::addConsequentDebuggerStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  DebuggerStatementWrapper* _DebuggerStatement1 = ObjectWrap::Unwrap<DebuggerStatementWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->addConsequent(_DebuggerStatement1->DebuggerStatement);
}
void SwitchCaseWrapper::addConsequentEmptyStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  EmptyStatementWrapper* _EmptyStatement1 = ObjectWrap::Unwrap<EmptyStatementWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->addConsequent(_EmptyStatement1->EmptyStatement);
}
void SwitchCaseWrapper::addConsequentExpressionStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExpressionStatementWrapper* _ExpressionStatement1 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->addConsequent(_ExpressionStatement1->ExpressionStatement);
}
void SwitchCaseWrapper::addConsequentForInStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ForInStatementWrapper* _ForInStatement1 = ObjectWrap::Unwrap<ForInStatementWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->addConsequent(_ForInStatement1->ForInStatement);
}
void SwitchCaseWrapper::addConsequentForOfStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ForOfStatementWrapper* _ForOfStatement1 = ObjectWrap::Unwrap<ForOfStatementWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->addConsequent(_ForOfStatement1->ForOfStatement);
}
void SwitchCaseWrapper::addConsequentForStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ForStatementWrapper* _ForStatement1 = ObjectWrap::Unwrap<ForStatementWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->addConsequent(_ForStatement1->ForStatement);
}
void SwitchCaseWrapper::addConsequentIfStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IfStatementWrapper* _IfStatement1 = ObjectWrap::Unwrap<IfStatementWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->addConsequent(_IfStatement1->IfStatement);
}
void SwitchCaseWrapper::addConsequentLabeledStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LabeledStatementWrapper* _LabeledStatement1 = ObjectWrap::Unwrap<LabeledStatementWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->addConsequent(_LabeledStatement1->LabeledStatement);
}
void SwitchCaseWrapper::addConsequentReturnStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ReturnStatementWrapper* _ReturnStatement1 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->addConsequent(_ReturnStatement1->ReturnStatement);
}
void SwitchCaseWrapper::addConsequentSwitchStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SwitchStatementWrapper* _SwitchStatement1 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->addConsequent(_SwitchStatement1->SwitchStatement);
}
void SwitchCaseWrapper::addConsequentThrowStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThrowStatementWrapper* _ThrowStatement1 = ObjectWrap::Unwrap<ThrowStatementWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->addConsequent(_ThrowStatement1->ThrowStatement);
}
void SwitchCaseWrapper::addConsequentTryStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TryStatementWrapper* _TryStatement1 = ObjectWrap::Unwrap<TryStatementWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->addConsequent(_TryStatement1->TryStatement);
}
void SwitchCaseWrapper::addConsequentWhileStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  WhileStatementWrapper* _WhileStatement1 = ObjectWrap::Unwrap<WhileStatementWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->addConsequent(_WhileStatement1->WhileStatement);
}
void SwitchCaseWrapper::addConsequentDoWhileStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  DoWhileStatementWrapper* _DoWhileStatement1 = ObjectWrap::Unwrap<DoWhileStatementWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->addConsequent(_DoWhileStatement1->DoWhileStatement);
}
void SwitchCaseWrapper::addConsequentWithStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  WithStatementWrapper* _WithStatement1 = ObjectWrap::Unwrap<WithStatementWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->addConsequent(_WithStatement1->WithStatement);
}
void SwitchCaseWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  SwitchCaseWrapper* _SwitchCase2 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());

  _SwitchCase2->SwitchCase->addComments(_Comment1->Comment);
}
void SwitchCaseWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  SwitchCaseWrapper* _SwitchCase = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _SwitchCase->SwitchCase->getPosition();
  range.setPath( param );
  _SwitchCase->SwitchCase->setPosition( range );
}

void SwitchCaseWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  SwitchCaseWrapper* _SwitchCase = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _SwitchCase->SwitchCase->getPosition();
  range.setLine( ui );
  _SwitchCase->SwitchCase->setPosition( range );
}

void SwitchCaseWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  SwitchCaseWrapper* _SwitchCase = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _SwitchCase->SwitchCase->getPosition();
  range.setCol( ui );
  _SwitchCase->SwitchCase->setPosition( range );
}

void SwitchCaseWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  SwitchCaseWrapper* _SwitchCase = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _SwitchCase->SwitchCase->getPosition();
  range.setEndLine( ui );
  _SwitchCase->SwitchCase->setPosition( range );
}

void SwitchCaseWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  SwitchCaseWrapper* _SwitchCase = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _SwitchCase->SwitchCase->getPosition();
  range.setEndCol( ui );
  _SwitchCase->SwitchCase->setPosition( range );
}

void SwitchCaseWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  SwitchCaseWrapper* _SwitchCase = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _SwitchCase->SwitchCase->getPosition();
  range.setWideLine( ui );
  _SwitchCase->SwitchCase->setPosition( range );
}

void SwitchCaseWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  SwitchCaseWrapper* _SwitchCase = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _SwitchCase->SwitchCase->getPosition();
  range.setWideCol( ui );
  _SwitchCase->SwitchCase->setPosition( range );
}

void SwitchCaseWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  SwitchCaseWrapper* _SwitchCase = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _SwitchCase->SwitchCase->getPosition();
  range.setWideEndLine( ui );
  _SwitchCase->SwitchCase->setPosition( range );
}

void SwitchCaseWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  SwitchCaseWrapper* _SwitchCase = ObjectWrap::Unwrap<SwitchCaseWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _SwitchCase->SwitchCase->getPosition();
  range.setWideEndCol( ui );
  _SwitchCase->SwitchCase->setPosition( range );
}

}}}} //end of namespaces