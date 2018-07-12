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

#include "../inc/BinaryExpressionWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> BinaryExpressionWrapper::constructor;

void BinaryExpressionWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "BinaryExpressionWrapper"));             
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
  exports->Set(v8::String::NewFromUtf8(isolate, "BinaryExpressionWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void BinaryExpressionWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new BinaryExpressionWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    BinaryExpressionWrapper* obj = new BinaryExpressionWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `BinaryExpressionWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


BinaryExpressionWrapper::BinaryExpressionWrapper(Factory* fact)                        
{                                                   
  BinaryExpression = fact->getFactory()->createBinaryExpressionNode();          
}                                                   

BinaryExpressionWrapper::~BinaryExpressionWrapper()
{        
}        

void BinaryExpressionWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void BinaryExpressionWrapper::setLeftArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setLeft(_ArrayExpression1->ArrayExpression);
}
void BinaryExpressionWrapper::setLeftArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setLeft(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void BinaryExpressionWrapper::setLeftAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setLeft(_AssignmentExpression1->AssignmentExpression);
}
void BinaryExpressionWrapper::setLeftAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setLeft(_AwaitExpression1->AwaitExpression);
}
void BinaryExpressionWrapper::setLeftBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setLeft(_BinaryExpression1->BinaryExpression);
}
void BinaryExpressionWrapper::setLeftCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setLeft(_CallExpression1->CallExpression);
}
void BinaryExpressionWrapper::setLeftClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setLeft(_ClassExpression1->ClassExpression);
}
void BinaryExpressionWrapper::setLeftConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setLeft(_ConditionalExpression1->ConditionalExpression);
}
void BinaryExpressionWrapper::setLeftFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setLeft(_FunctionExpression1->FunctionExpression);
}
void BinaryExpressionWrapper::setLeftIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setLeft(_Identifier1->Identifier);
}
void BinaryExpressionWrapper::setLeftBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setLeft(_BooleanLiteral1->BooleanLiteral);
}
void BinaryExpressionWrapper::setLeftNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setLeft(_NullLiteral1->NullLiteral);
}
void BinaryExpressionWrapper::setLeftNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setLeft(_NumberLiteral1->NumberLiteral);
}
void BinaryExpressionWrapper::setLeftRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setLeft(_RegExpLiteral1->RegExpLiteral);
}
void BinaryExpressionWrapper::setLeftStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setLeft(_StringLiteral1->StringLiteral);
}
void BinaryExpressionWrapper::setLeftLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setLeft(_LogicalExpression1->LogicalExpression);
}
void BinaryExpressionWrapper::setLeftMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setLeft(_MemberExpression1->MemberExpression);
}
void BinaryExpressionWrapper::setLeftMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setLeft(_MetaProperty1->MetaProperty);
}
void BinaryExpressionWrapper::setLeftNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setLeft(_NewExpression1->NewExpression);
}
void BinaryExpressionWrapper::setLeftObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setLeft(_ObjectExpression1->ObjectExpression);
}
void BinaryExpressionWrapper::setLeftSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setLeft(_SequenceExpression1->SequenceExpression);
}
void BinaryExpressionWrapper::setLeftTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setLeft(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void BinaryExpressionWrapper::setLeftTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setLeft(_TemplateLiteral1->TemplateLiteral);
}
void BinaryExpressionWrapper::setLeftThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setLeft(_ThisExpression1->ThisExpression);
}
void BinaryExpressionWrapper::setLeftUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setLeft(_UnaryExpression1->UnaryExpression);
}
void BinaryExpressionWrapper::setLeftUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setLeft(_UpdateExpression1->UpdateExpression);
}
void BinaryExpressionWrapper::setLeftYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setLeft(_YieldExpression1->YieldExpression);
}
void BinaryExpressionWrapper::setRightArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setRight(_ArrayExpression1->ArrayExpression);
}
void BinaryExpressionWrapper::setRightArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setRight(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void BinaryExpressionWrapper::setRightAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setRight(_AssignmentExpression1->AssignmentExpression);
}
void BinaryExpressionWrapper::setRightAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setRight(_AwaitExpression1->AwaitExpression);
}
void BinaryExpressionWrapper::setRightBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setRight(_BinaryExpression1->BinaryExpression);
}
void BinaryExpressionWrapper::setRightCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setRight(_CallExpression1->CallExpression);
}
void BinaryExpressionWrapper::setRightClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setRight(_ClassExpression1->ClassExpression);
}
void BinaryExpressionWrapper::setRightConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setRight(_ConditionalExpression1->ConditionalExpression);
}
void BinaryExpressionWrapper::setRightFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setRight(_FunctionExpression1->FunctionExpression);
}
void BinaryExpressionWrapper::setRightIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setRight(_Identifier1->Identifier);
}
void BinaryExpressionWrapper::setRightBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setRight(_BooleanLiteral1->BooleanLiteral);
}
void BinaryExpressionWrapper::setRightNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setRight(_NullLiteral1->NullLiteral);
}
void BinaryExpressionWrapper::setRightNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setRight(_NumberLiteral1->NumberLiteral);
}
void BinaryExpressionWrapper::setRightRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setRight(_RegExpLiteral1->RegExpLiteral);
}
void BinaryExpressionWrapper::setRightStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setRight(_StringLiteral1->StringLiteral);
}
void BinaryExpressionWrapper::setRightLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setRight(_LogicalExpression1->LogicalExpression);
}
void BinaryExpressionWrapper::setRightMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setRight(_MemberExpression1->MemberExpression);
}
void BinaryExpressionWrapper::setRightMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setRight(_MetaProperty1->MetaProperty);
}
void BinaryExpressionWrapper::setRightNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setRight(_NewExpression1->NewExpression);
}
void BinaryExpressionWrapper::setRightObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setRight(_ObjectExpression1->ObjectExpression);
}
void BinaryExpressionWrapper::setRightSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setRight(_SequenceExpression1->SequenceExpression);
}
void BinaryExpressionWrapper::setRightTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setRight(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void BinaryExpressionWrapper::setRightTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setRight(_TemplateLiteral1->TemplateLiteral);
}
void BinaryExpressionWrapper::setRightThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setRight(_ThisExpression1->ThisExpression);
}
void BinaryExpressionWrapper::setRightUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setRight(_UnaryExpression1->UnaryExpression);
}
void BinaryExpressionWrapper::setRightUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setRight(_UpdateExpression1->UpdateExpression);
}
void BinaryExpressionWrapper::setRightYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->setRight(_YieldExpression1->YieldExpression);
}
void BinaryExpressionWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  BinaryExpressionWrapper* _BinaryExpression2 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());

  _BinaryExpression2->BinaryExpression->addComments(_Comment1->Comment);
}
void BinaryExpressionWrapper::setOperator(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  BinaryExpressionWrapper* _BinaryExpression = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  if( param == "bioEqualTo" ){
    _BinaryExpression->BinaryExpression->setOperator( bioEqualTo );
  }
  if( param == "bioNotEqual" ){
    _BinaryExpression->BinaryExpression->setOperator( bioNotEqual );
  }
  if( param == "bioEqualValueAndType" ){
    _BinaryExpression->BinaryExpression->setOperator( bioEqualValueAndType );
  }
  if( param == "bioNotEqualValueAndType" ){
    _BinaryExpression->BinaryExpression->setOperator( bioNotEqualValueAndType );
  }
  if( param == "bioLessThan" ){
    _BinaryExpression->BinaryExpression->setOperator( bioLessThan );
  }
  if( param == "bioGreaterThan" ){
    _BinaryExpression->BinaryExpression->setOperator( bioGreaterThan );
  }
  if( param == "bioGreaterThanEqual" ){
    _BinaryExpression->BinaryExpression->setOperator( bioGreaterThanEqual );
  }
  if( param == "bioLessThanEqual" ){
    _BinaryExpression->BinaryExpression->setOperator( bioLessThanEqual );
  }
  if( param == "bioLeftShift" ){
    _BinaryExpression->BinaryExpression->setOperator( bioLeftShift );
  }
  if( param == "bioRightShift" ){
    _BinaryExpression->BinaryExpression->setOperator( bioRightShift );
  }
  if( param == "bioFillNullRightShift" ){
    _BinaryExpression->BinaryExpression->setOperator( bioFillNullRightShift );
  }
  if( param == "bioAddition" ){
    _BinaryExpression->BinaryExpression->setOperator( bioAddition );
  }
  if( param == "bioSubtraction" ){
    _BinaryExpression->BinaryExpression->setOperator( bioSubtraction );
  }
  if( param == "bioMultiplication" ){
    _BinaryExpression->BinaryExpression->setOperator( bioMultiplication );
  }
  if( param == "bioDivision" ){
    _BinaryExpression->BinaryExpression->setOperator( bioDivision );
  }
  if( param == "bioModulus" ){
    _BinaryExpression->BinaryExpression->setOperator( bioModulus );
  }
  if( param == "bioOr" ){
    _BinaryExpression->BinaryExpression->setOperator( bioOr );
  }
  if( param == "bioXor" ){
    _BinaryExpression->BinaryExpression->setOperator( bioXor );
  }
  if( param == "bioAnd" ){
    _BinaryExpression->BinaryExpression->setOperator( bioAnd );
  }
  if( param == "bioIn" ){
    _BinaryExpression->BinaryExpression->setOperator( bioIn );
  }
  if( param == "bioInstanceOf" ){
    _BinaryExpression->BinaryExpression->setOperator( bioInstanceOf );
  }
  if( param == "bioExponentiation" ){
    _BinaryExpression->BinaryExpression->setOperator( bioExponentiation );
  }
}
void BinaryExpressionWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  BinaryExpressionWrapper* _BinaryExpression = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _BinaryExpression->BinaryExpression->getPosition();
  range.setPath( param );
  _BinaryExpression->BinaryExpression->setPosition( range );
}

void BinaryExpressionWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  BinaryExpressionWrapper* _BinaryExpression = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _BinaryExpression->BinaryExpression->getPosition();
  range.setLine( ui );
  _BinaryExpression->BinaryExpression->setPosition( range );
}

void BinaryExpressionWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  BinaryExpressionWrapper* _BinaryExpression = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _BinaryExpression->BinaryExpression->getPosition();
  range.setCol( ui );
  _BinaryExpression->BinaryExpression->setPosition( range );
}

void BinaryExpressionWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  BinaryExpressionWrapper* _BinaryExpression = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _BinaryExpression->BinaryExpression->getPosition();
  range.setEndLine( ui );
  _BinaryExpression->BinaryExpression->setPosition( range );
}

void BinaryExpressionWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  BinaryExpressionWrapper* _BinaryExpression = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _BinaryExpression->BinaryExpression->getPosition();
  range.setEndCol( ui );
  _BinaryExpression->BinaryExpression->setPosition( range );
}

void BinaryExpressionWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  BinaryExpressionWrapper* _BinaryExpression = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _BinaryExpression->BinaryExpression->getPosition();
  range.setWideLine( ui );
  _BinaryExpression->BinaryExpression->setPosition( range );
}

void BinaryExpressionWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  BinaryExpressionWrapper* _BinaryExpression = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _BinaryExpression->BinaryExpression->getPosition();
  range.setWideCol( ui );
  _BinaryExpression->BinaryExpression->setPosition( range );
}

void BinaryExpressionWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  BinaryExpressionWrapper* _BinaryExpression = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _BinaryExpression->BinaryExpression->getPosition();
  range.setWideEndLine( ui );
  _BinaryExpression->BinaryExpression->setPosition( range );
}

void BinaryExpressionWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  BinaryExpressionWrapper* _BinaryExpression = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _BinaryExpression->BinaryExpression->getPosition();
  range.setWideEndCol( ui );
  _BinaryExpression->BinaryExpression->setPosition( range );
}

}}}} //end of namespaces