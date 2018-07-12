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

#include "../inc/ExportDefaultDeclarationWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> ExportDefaultDeclarationWrapper::constructor;

void ExportDefaultDeclarationWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "ExportDefaultDeclarationWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationClassDeclaration", setDeclarationClassDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationExportAllDeclaration", setDeclarationExportAllDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationExportDefaultDeclaration", setDeclarationExportDefaultDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationFunctionDeclaration", setDeclarationFunctionDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationVariableDeclaration", setDeclarationVariableDeclaration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationArrayExpression", setDeclarationArrayExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationArrowFunctionExpression", setDeclarationArrowFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationAssignmentExpression", setDeclarationAssignmentExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationAwaitExpression", setDeclarationAwaitExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationBinaryExpression", setDeclarationBinaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationCallExpression", setDeclarationCallExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationClassExpression", setDeclarationClassExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationConditionalExpression", setDeclarationConditionalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationFunctionExpression", setDeclarationFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationIdentifier", setDeclarationIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationBooleanLiteral", setDeclarationBooleanLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationNullLiteral", setDeclarationNullLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationNumberLiteral", setDeclarationNumberLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationRegExpLiteral", setDeclarationRegExpLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationStringLiteral", setDeclarationStringLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationLogicalExpression", setDeclarationLogicalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationMemberExpression", setDeclarationMemberExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationMetaProperty", setDeclarationMetaProperty);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationNewExpression", setDeclarationNewExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationObjectExpression", setDeclarationObjectExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationSequenceExpression", setDeclarationSequenceExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationTaggedTemplateExpression", setDeclarationTaggedTemplateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationTemplateLiteral", setDeclarationTemplateLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationThisExpression", setDeclarationThisExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationUnaryExpression", setDeclarationUnaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationUpdateExpression", setDeclarationUpdateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDeclarationYieldExpression", setDeclarationYieldExpression);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "ExportDefaultDeclarationWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void ExportDefaultDeclarationWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new ExportDefaultDeclarationWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    ExportDefaultDeclarationWrapper* obj = new ExportDefaultDeclarationWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `ExportDefaultDeclarationWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


ExportDefaultDeclarationWrapper::ExportDefaultDeclarationWrapper(Factory* fact)                        
{                                                   
  ExportDefaultDeclaration = fact->getFactory()->createExportDefaultDeclarationNode();          
}                                                   

ExportDefaultDeclarationWrapper::~ExportDefaultDeclarationWrapper()
{        
}        

void ExportDefaultDeclarationWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void ExportDefaultDeclarationWrapper::setDeclarationClassDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassDeclarationWrapper* _ClassDeclaration1 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args[0]->ToObject());
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration2 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());

  _ExportDefaultDeclaration2->ExportDefaultDeclaration->setDeclaration(_ClassDeclaration1->ClassDeclaration);
}
void ExportDefaultDeclarationWrapper::setDeclarationExportAllDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExportAllDeclarationWrapper* _ExportAllDeclaration1 = ObjectWrap::Unwrap<ExportAllDeclarationWrapper>(args[0]->ToObject());
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration2 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());

  _ExportDefaultDeclaration2->ExportDefaultDeclaration->setDeclaration(_ExportAllDeclaration1->ExportAllDeclaration);
}
void ExportDefaultDeclarationWrapper::setDeclarationExportDefaultDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration1 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args[0]->ToObject());
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration2 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());

  _ExportDefaultDeclaration2->ExportDefaultDeclaration->setDeclaration(_ExportDefaultDeclaration1->ExportDefaultDeclaration);
}
void ExportDefaultDeclarationWrapper::setDeclarationFunctionDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionDeclarationWrapper* _FunctionDeclaration1 = ObjectWrap::Unwrap<FunctionDeclarationWrapper>(args[0]->ToObject());
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration2 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());

  _ExportDefaultDeclaration2->ExportDefaultDeclaration->setDeclaration(_FunctionDeclaration1->FunctionDeclaration);
}
void ExportDefaultDeclarationWrapper::setDeclarationVariableDeclaration(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  VariableDeclarationWrapper* _VariableDeclaration1 = ObjectWrap::Unwrap<VariableDeclarationWrapper>(args[0]->ToObject());
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration2 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());

  _ExportDefaultDeclaration2->ExportDefaultDeclaration->setDeclaration(_VariableDeclaration1->VariableDeclaration);
}
void ExportDefaultDeclarationWrapper::setDeclarationArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration2 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());

  _ExportDefaultDeclaration2->ExportDefaultDeclaration->setDeclaration(_ArrayExpression1->ArrayExpression);
}
void ExportDefaultDeclarationWrapper::setDeclarationArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration2 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());

  _ExportDefaultDeclaration2->ExportDefaultDeclaration->setDeclaration(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void ExportDefaultDeclarationWrapper::setDeclarationAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration2 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());

  _ExportDefaultDeclaration2->ExportDefaultDeclaration->setDeclaration(_AssignmentExpression1->AssignmentExpression);
}
void ExportDefaultDeclarationWrapper::setDeclarationAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration2 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());

  _ExportDefaultDeclaration2->ExportDefaultDeclaration->setDeclaration(_AwaitExpression1->AwaitExpression);
}
void ExportDefaultDeclarationWrapper::setDeclarationBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration2 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());

  _ExportDefaultDeclaration2->ExportDefaultDeclaration->setDeclaration(_BinaryExpression1->BinaryExpression);
}
void ExportDefaultDeclarationWrapper::setDeclarationCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration2 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());

  _ExportDefaultDeclaration2->ExportDefaultDeclaration->setDeclaration(_CallExpression1->CallExpression);
}
void ExportDefaultDeclarationWrapper::setDeclarationClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration2 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());

  _ExportDefaultDeclaration2->ExportDefaultDeclaration->setDeclaration(_ClassExpression1->ClassExpression);
}
void ExportDefaultDeclarationWrapper::setDeclarationConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration2 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());

  _ExportDefaultDeclaration2->ExportDefaultDeclaration->setDeclaration(_ConditionalExpression1->ConditionalExpression);
}
void ExportDefaultDeclarationWrapper::setDeclarationFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration2 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());

  _ExportDefaultDeclaration2->ExportDefaultDeclaration->setDeclaration(_FunctionExpression1->FunctionExpression);
}
void ExportDefaultDeclarationWrapper::setDeclarationIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration2 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());

  _ExportDefaultDeclaration2->ExportDefaultDeclaration->setDeclaration(_Identifier1->Identifier);
}
void ExportDefaultDeclarationWrapper::setDeclarationBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration2 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());

  _ExportDefaultDeclaration2->ExportDefaultDeclaration->setDeclaration(_BooleanLiteral1->BooleanLiteral);
}
void ExportDefaultDeclarationWrapper::setDeclarationNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration2 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());

  _ExportDefaultDeclaration2->ExportDefaultDeclaration->setDeclaration(_NullLiteral1->NullLiteral);
}
void ExportDefaultDeclarationWrapper::setDeclarationNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration2 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());

  _ExportDefaultDeclaration2->ExportDefaultDeclaration->setDeclaration(_NumberLiteral1->NumberLiteral);
}
void ExportDefaultDeclarationWrapper::setDeclarationRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration2 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());

  _ExportDefaultDeclaration2->ExportDefaultDeclaration->setDeclaration(_RegExpLiteral1->RegExpLiteral);
}
void ExportDefaultDeclarationWrapper::setDeclarationStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration2 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());

  _ExportDefaultDeclaration2->ExportDefaultDeclaration->setDeclaration(_StringLiteral1->StringLiteral);
}
void ExportDefaultDeclarationWrapper::setDeclarationLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration2 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());

  _ExportDefaultDeclaration2->ExportDefaultDeclaration->setDeclaration(_LogicalExpression1->LogicalExpression);
}
void ExportDefaultDeclarationWrapper::setDeclarationMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration2 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());

  _ExportDefaultDeclaration2->ExportDefaultDeclaration->setDeclaration(_MemberExpression1->MemberExpression);
}
void ExportDefaultDeclarationWrapper::setDeclarationMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration2 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());

  _ExportDefaultDeclaration2->ExportDefaultDeclaration->setDeclaration(_MetaProperty1->MetaProperty);
}
void ExportDefaultDeclarationWrapper::setDeclarationNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration2 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());

  _ExportDefaultDeclaration2->ExportDefaultDeclaration->setDeclaration(_NewExpression1->NewExpression);
}
void ExportDefaultDeclarationWrapper::setDeclarationObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration2 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());

  _ExportDefaultDeclaration2->ExportDefaultDeclaration->setDeclaration(_ObjectExpression1->ObjectExpression);
}
void ExportDefaultDeclarationWrapper::setDeclarationSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration2 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());

  _ExportDefaultDeclaration2->ExportDefaultDeclaration->setDeclaration(_SequenceExpression1->SequenceExpression);
}
void ExportDefaultDeclarationWrapper::setDeclarationTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration2 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());

  _ExportDefaultDeclaration2->ExportDefaultDeclaration->setDeclaration(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void ExportDefaultDeclarationWrapper::setDeclarationTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration2 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());

  _ExportDefaultDeclaration2->ExportDefaultDeclaration->setDeclaration(_TemplateLiteral1->TemplateLiteral);
}
void ExportDefaultDeclarationWrapper::setDeclarationThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration2 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());

  _ExportDefaultDeclaration2->ExportDefaultDeclaration->setDeclaration(_ThisExpression1->ThisExpression);
}
void ExportDefaultDeclarationWrapper::setDeclarationUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration2 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());

  _ExportDefaultDeclaration2->ExportDefaultDeclaration->setDeclaration(_UnaryExpression1->UnaryExpression);
}
void ExportDefaultDeclarationWrapper::setDeclarationUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration2 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());

  _ExportDefaultDeclaration2->ExportDefaultDeclaration->setDeclaration(_UpdateExpression1->UpdateExpression);
}
void ExportDefaultDeclarationWrapper::setDeclarationYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration2 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());

  _ExportDefaultDeclaration2->ExportDefaultDeclaration->setDeclaration(_YieldExpression1->YieldExpression);
}
void ExportDefaultDeclarationWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration2 = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());

  _ExportDefaultDeclaration2->ExportDefaultDeclaration->addComments(_Comment1->Comment);
}
void ExportDefaultDeclarationWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _ExportDefaultDeclaration->ExportDefaultDeclaration->getPosition();
  range.setPath( param );
  _ExportDefaultDeclaration->ExportDefaultDeclaration->setPosition( range );
}

void ExportDefaultDeclarationWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExportDefaultDeclaration->ExportDefaultDeclaration->getPosition();
  range.setLine( ui );
  _ExportDefaultDeclaration->ExportDefaultDeclaration->setPosition( range );
}

void ExportDefaultDeclarationWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExportDefaultDeclaration->ExportDefaultDeclaration->getPosition();
  range.setCol( ui );
  _ExportDefaultDeclaration->ExportDefaultDeclaration->setPosition( range );
}

void ExportDefaultDeclarationWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExportDefaultDeclaration->ExportDefaultDeclaration->getPosition();
  range.setEndLine( ui );
  _ExportDefaultDeclaration->ExportDefaultDeclaration->setPosition( range );
}

void ExportDefaultDeclarationWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExportDefaultDeclaration->ExportDefaultDeclaration->getPosition();
  range.setEndCol( ui );
  _ExportDefaultDeclaration->ExportDefaultDeclaration->setPosition( range );
}

void ExportDefaultDeclarationWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExportDefaultDeclaration->ExportDefaultDeclaration->getPosition();
  range.setWideLine( ui );
  _ExportDefaultDeclaration->ExportDefaultDeclaration->setPosition( range );
}

void ExportDefaultDeclarationWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExportDefaultDeclaration->ExportDefaultDeclaration->getPosition();
  range.setWideCol( ui );
  _ExportDefaultDeclaration->ExportDefaultDeclaration->setPosition( range );
}

void ExportDefaultDeclarationWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExportDefaultDeclaration->ExportDefaultDeclaration->getPosition();
  range.setWideEndLine( ui );
  _ExportDefaultDeclaration->ExportDefaultDeclaration->setPosition( range );
}

void ExportDefaultDeclarationWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExportDefaultDeclarationWrapper* _ExportDefaultDeclaration = ObjectWrap::Unwrap<ExportDefaultDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExportDefaultDeclaration->ExportDefaultDeclaration->getPosition();
  range.setWideEndCol( ui );
  _ExportDefaultDeclaration->ExportDefaultDeclaration->setPosition( range );
}

}}}} //end of namespaces