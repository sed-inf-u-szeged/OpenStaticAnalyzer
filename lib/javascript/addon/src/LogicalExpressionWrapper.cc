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

#include "../inc/LogicalExpressionWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> LogicalExpressionWrapper::constructor;

void LogicalExpressionWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "LogicalExpressionWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftArrayExpression", setLeftArrayExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftArrowFunctionExpression", setLeftArrowFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftAssignmentExpression", setLeftAssignmentExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftAwaitExpression", setLeftAwaitExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftBinaryExpression", setLeftBinaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftCallExpression", setLeftCallExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftClassExpression", setLeftClassExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftConditionalExpression", setLeftConditionalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftFunctionExpression", setLeftFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftIdentifier", setLeftIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftBooleanLiteral", setLeftBooleanLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftNullLiteral", setLeftNullLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftNumberLiteral", setLeftNumberLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftRegExpLiteral", setLeftRegExpLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftStringLiteral", setLeftStringLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftLogicalExpression", setLeftLogicalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftMemberExpression", setLeftMemberExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftMetaProperty", setLeftMetaProperty);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftNewExpression", setLeftNewExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftObjectExpression", setLeftObjectExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftSequenceExpression", setLeftSequenceExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftTaggedTemplateExpression", setLeftTaggedTemplateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftTemplateLiteral", setLeftTemplateLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftThisExpression", setLeftThisExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftUnaryExpression", setLeftUnaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftUpdateExpression", setLeftUpdateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftYieldExpression", setLeftYieldExpression);
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
  NODE_SET_PROTOTYPE_METHOD(tpl, "addCommentsComment", addCommentsComment);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setOperator", setOperator);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "LogicalExpressionWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void LogicalExpressionWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new LogicalExpressionWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    LogicalExpressionWrapper* obj = new LogicalExpressionWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `LogicalExpressionWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


LogicalExpressionWrapper::LogicalExpressionWrapper(Factory* fact)                        
{                                                   
  LogicalExpression = fact->getFactory()->createLogicalExpressionNode();          
}                                                   

LogicalExpressionWrapper::~LogicalExpressionWrapper()
{        
}        

void LogicalExpressionWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void LogicalExpressionWrapper::setLeftArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setLeft(_ArrayExpression1->ArrayExpression);
}
void LogicalExpressionWrapper::setLeftArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setLeft(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void LogicalExpressionWrapper::setLeftAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setLeft(_AssignmentExpression1->AssignmentExpression);
}
void LogicalExpressionWrapper::setLeftAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setLeft(_AwaitExpression1->AwaitExpression);
}
void LogicalExpressionWrapper::setLeftBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setLeft(_BinaryExpression1->BinaryExpression);
}
void LogicalExpressionWrapper::setLeftCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setLeft(_CallExpression1->CallExpression);
}
void LogicalExpressionWrapper::setLeftClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setLeft(_ClassExpression1->ClassExpression);
}
void LogicalExpressionWrapper::setLeftConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setLeft(_ConditionalExpression1->ConditionalExpression);
}
void LogicalExpressionWrapper::setLeftFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setLeft(_FunctionExpression1->FunctionExpression);
}
void LogicalExpressionWrapper::setLeftIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setLeft(_Identifier1->Identifier);
}
void LogicalExpressionWrapper::setLeftBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setLeft(_BooleanLiteral1->BooleanLiteral);
}
void LogicalExpressionWrapper::setLeftNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setLeft(_NullLiteral1->NullLiteral);
}
void LogicalExpressionWrapper::setLeftNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setLeft(_NumberLiteral1->NumberLiteral);
}
void LogicalExpressionWrapper::setLeftRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setLeft(_RegExpLiteral1->RegExpLiteral);
}
void LogicalExpressionWrapper::setLeftStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setLeft(_StringLiteral1->StringLiteral);
}
void LogicalExpressionWrapper::setLeftLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setLeft(_LogicalExpression1->LogicalExpression);
}
void LogicalExpressionWrapper::setLeftMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setLeft(_MemberExpression1->MemberExpression);
}
void LogicalExpressionWrapper::setLeftMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setLeft(_MetaProperty1->MetaProperty);
}
void LogicalExpressionWrapper::setLeftNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setLeft(_NewExpression1->NewExpression);
}
void LogicalExpressionWrapper::setLeftObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setLeft(_ObjectExpression1->ObjectExpression);
}
void LogicalExpressionWrapper::setLeftSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setLeft(_SequenceExpression1->SequenceExpression);
}
void LogicalExpressionWrapper::setLeftTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setLeft(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void LogicalExpressionWrapper::setLeftTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setLeft(_TemplateLiteral1->TemplateLiteral);
}
void LogicalExpressionWrapper::setLeftThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setLeft(_ThisExpression1->ThisExpression);
}
void LogicalExpressionWrapper::setLeftUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setLeft(_UnaryExpression1->UnaryExpression);
}
void LogicalExpressionWrapper::setLeftUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setLeft(_UpdateExpression1->UpdateExpression);
}
void LogicalExpressionWrapper::setLeftYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setLeft(_YieldExpression1->YieldExpression);
}
void LogicalExpressionWrapper::setRightArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setRight(_ArrayExpression1->ArrayExpression);
}
void LogicalExpressionWrapper::setRightArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setRight(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void LogicalExpressionWrapper::setRightAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setRight(_AssignmentExpression1->AssignmentExpression);
}
void LogicalExpressionWrapper::setRightAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setRight(_AwaitExpression1->AwaitExpression);
}
void LogicalExpressionWrapper::setRightBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setRight(_BinaryExpression1->BinaryExpression);
}
void LogicalExpressionWrapper::setRightCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setRight(_CallExpression1->CallExpression);
}
void LogicalExpressionWrapper::setRightClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setRight(_ClassExpression1->ClassExpression);
}
void LogicalExpressionWrapper::setRightConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setRight(_ConditionalExpression1->ConditionalExpression);
}
void LogicalExpressionWrapper::setRightFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setRight(_FunctionExpression1->FunctionExpression);
}
void LogicalExpressionWrapper::setRightIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setRight(_Identifier1->Identifier);
}
void LogicalExpressionWrapper::setRightBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setRight(_BooleanLiteral1->BooleanLiteral);
}
void LogicalExpressionWrapper::setRightNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setRight(_NullLiteral1->NullLiteral);
}
void LogicalExpressionWrapper::setRightNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setRight(_NumberLiteral1->NumberLiteral);
}
void LogicalExpressionWrapper::setRightRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setRight(_RegExpLiteral1->RegExpLiteral);
}
void LogicalExpressionWrapper::setRightStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setRight(_StringLiteral1->StringLiteral);
}
void LogicalExpressionWrapper::setRightLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setRight(_LogicalExpression1->LogicalExpression);
}
void LogicalExpressionWrapper::setRightMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setRight(_MemberExpression1->MemberExpression);
}
void LogicalExpressionWrapper::setRightMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setRight(_MetaProperty1->MetaProperty);
}
void LogicalExpressionWrapper::setRightNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setRight(_NewExpression1->NewExpression);
}
void LogicalExpressionWrapper::setRightObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setRight(_ObjectExpression1->ObjectExpression);
}
void LogicalExpressionWrapper::setRightSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setRight(_SequenceExpression1->SequenceExpression);
}
void LogicalExpressionWrapper::setRightTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setRight(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void LogicalExpressionWrapper::setRightTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setRight(_TemplateLiteral1->TemplateLiteral);
}
void LogicalExpressionWrapper::setRightThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setRight(_ThisExpression1->ThisExpression);
}
void LogicalExpressionWrapper::setRightUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setRight(_UnaryExpression1->UnaryExpression);
}
void LogicalExpressionWrapper::setRightUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setRight(_UpdateExpression1->UpdateExpression);
}
void LogicalExpressionWrapper::setRightYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->setRight(_YieldExpression1->YieldExpression);
}
void LogicalExpressionWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  LogicalExpressionWrapper* _LogicalExpression2 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());

  _LogicalExpression2->LogicalExpression->addComments(_Comment1->Comment);
}
void LogicalExpressionWrapper::setOperator(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  LogicalExpressionWrapper* _LogicalExpression = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  if( param == "looAnd" ){
    _LogicalExpression->LogicalExpression->setOperator( looAnd );
  }
  if( param == "looOr" ){
    _LogicalExpression->LogicalExpression->setOperator( looOr );
  }
}
void LogicalExpressionWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  LogicalExpressionWrapper* _LogicalExpression = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _LogicalExpression->LogicalExpression->getPosition();
  range.setPath( param );
  _LogicalExpression->LogicalExpression->setPosition( range );
}

void LogicalExpressionWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  LogicalExpressionWrapper* _LogicalExpression = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _LogicalExpression->LogicalExpression->getPosition();
  range.setLine( ui );
  _LogicalExpression->LogicalExpression->setPosition( range );
}

void LogicalExpressionWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  LogicalExpressionWrapper* _LogicalExpression = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _LogicalExpression->LogicalExpression->getPosition();
  range.setCol( ui );
  _LogicalExpression->LogicalExpression->setPosition( range );
}

void LogicalExpressionWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  LogicalExpressionWrapper* _LogicalExpression = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _LogicalExpression->LogicalExpression->getPosition();
  range.setEndLine( ui );
  _LogicalExpression->LogicalExpression->setPosition( range );
}

void LogicalExpressionWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  LogicalExpressionWrapper* _LogicalExpression = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _LogicalExpression->LogicalExpression->getPosition();
  range.setEndCol( ui );
  _LogicalExpression->LogicalExpression->setPosition( range );
}

void LogicalExpressionWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  LogicalExpressionWrapper* _LogicalExpression = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _LogicalExpression->LogicalExpression->getPosition();
  range.setWideLine( ui );
  _LogicalExpression->LogicalExpression->setPosition( range );
}

void LogicalExpressionWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  LogicalExpressionWrapper* _LogicalExpression = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _LogicalExpression->LogicalExpression->getPosition();
  range.setWideCol( ui );
  _LogicalExpression->LogicalExpression->setPosition( range );
}

void LogicalExpressionWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  LogicalExpressionWrapper* _LogicalExpression = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _LogicalExpression->LogicalExpression->getPosition();
  range.setWideEndLine( ui );
  _LogicalExpression->LogicalExpression->setPosition( range );
}

void LogicalExpressionWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  LogicalExpressionWrapper* _LogicalExpression = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _LogicalExpression->LogicalExpression->getPosition();
  range.setWideEndCol( ui );
  _LogicalExpression->LogicalExpression->setPosition( range );
}

}}}} //end of namespaces