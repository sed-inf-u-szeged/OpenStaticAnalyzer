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

#include "../inc/AssignmentExpressionWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> AssignmentExpressionWrapper::constructor;

void AssignmentExpressionWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "AssignmentExpressionWrapper"));             
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
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftArrayPattern", setLeftArrayPattern);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftAssignmentPattern", setLeftAssignmentPattern);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftObjectPattern", setLeftObjectPattern);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftRestElement", setLeftRestElement);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "AssignmentExpressionWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void AssignmentExpressionWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new AssignmentExpressionWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    AssignmentExpressionWrapper* obj = new AssignmentExpressionWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `AssignmentExpressionWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


AssignmentExpressionWrapper::AssignmentExpressionWrapper(Factory* fact)                        
{                                                   
  AssignmentExpression = fact->getFactory()->createAssignmentExpressionNode();          
}                                                   

AssignmentExpressionWrapper::~AssignmentExpressionWrapper()
{        
}        

void AssignmentExpressionWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void AssignmentExpressionWrapper::setLeftArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setLeft(_ArrayExpression1->ArrayExpression);
}
void AssignmentExpressionWrapper::setLeftArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setLeft(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void AssignmentExpressionWrapper::setLeftAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setLeft(_AssignmentExpression1->AssignmentExpression);
}
void AssignmentExpressionWrapper::setLeftAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setLeft(_AwaitExpression1->AwaitExpression);
}
void AssignmentExpressionWrapper::setLeftBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setLeft(_BinaryExpression1->BinaryExpression);
}
void AssignmentExpressionWrapper::setLeftCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setLeft(_CallExpression1->CallExpression);
}
void AssignmentExpressionWrapper::setLeftClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setLeft(_ClassExpression1->ClassExpression);
}
void AssignmentExpressionWrapper::setLeftConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setLeft(_ConditionalExpression1->ConditionalExpression);
}
void AssignmentExpressionWrapper::setLeftFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setLeft(_FunctionExpression1->FunctionExpression);
}
void AssignmentExpressionWrapper::setLeftIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setLeft(_Identifier1->Identifier);
}
void AssignmentExpressionWrapper::setLeftBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setLeft(_BooleanLiteral1->BooleanLiteral);
}
void AssignmentExpressionWrapper::setLeftNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setLeft(_NullLiteral1->NullLiteral);
}
void AssignmentExpressionWrapper::setLeftNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setLeft(_NumberLiteral1->NumberLiteral);
}
void AssignmentExpressionWrapper::setLeftRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setLeft(_RegExpLiteral1->RegExpLiteral);
}
void AssignmentExpressionWrapper::setLeftStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setLeft(_StringLiteral1->StringLiteral);
}
void AssignmentExpressionWrapper::setLeftLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setLeft(_LogicalExpression1->LogicalExpression);
}
void AssignmentExpressionWrapper::setLeftMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setLeft(_MemberExpression1->MemberExpression);
}
void AssignmentExpressionWrapper::setLeftMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setLeft(_MetaProperty1->MetaProperty);
}
void AssignmentExpressionWrapper::setLeftNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setLeft(_NewExpression1->NewExpression);
}
void AssignmentExpressionWrapper::setLeftObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setLeft(_ObjectExpression1->ObjectExpression);
}
void AssignmentExpressionWrapper::setLeftSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setLeft(_SequenceExpression1->SequenceExpression);
}
void AssignmentExpressionWrapper::setLeftTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setLeft(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void AssignmentExpressionWrapper::setLeftTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setLeft(_TemplateLiteral1->TemplateLiteral);
}
void AssignmentExpressionWrapper::setLeftThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setLeft(_ThisExpression1->ThisExpression);
}
void AssignmentExpressionWrapper::setLeftUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setLeft(_UnaryExpression1->UnaryExpression);
}
void AssignmentExpressionWrapper::setLeftUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setLeft(_UpdateExpression1->UpdateExpression);
}
void AssignmentExpressionWrapper::setLeftYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setLeft(_YieldExpression1->YieldExpression);
}
void AssignmentExpressionWrapper::setLeftArrayPattern(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayPatternWrapper* _ArrayPattern1 = ObjectWrap::Unwrap<ArrayPatternWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setLeft(_ArrayPattern1->ArrayPattern);
}
void AssignmentExpressionWrapper::setLeftAssignmentPattern(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentPatternWrapper* _AssignmentPattern1 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setLeft(_AssignmentPattern1->AssignmentPattern);
}
void AssignmentExpressionWrapper::setLeftObjectPattern(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectPatternWrapper* _ObjectPattern1 = ObjectWrap::Unwrap<ObjectPatternWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setLeft(_ObjectPattern1->ObjectPattern);
}
void AssignmentExpressionWrapper::setLeftRestElement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RestElementWrapper* _RestElement1 = ObjectWrap::Unwrap<RestElementWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setLeft(_RestElement1->RestElement);
}
void AssignmentExpressionWrapper::setRightArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setRight(_ArrayExpression1->ArrayExpression);
}
void AssignmentExpressionWrapper::setRightArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setRight(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void AssignmentExpressionWrapper::setRightAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setRight(_AssignmentExpression1->AssignmentExpression);
}
void AssignmentExpressionWrapper::setRightAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setRight(_AwaitExpression1->AwaitExpression);
}
void AssignmentExpressionWrapper::setRightBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setRight(_BinaryExpression1->BinaryExpression);
}
void AssignmentExpressionWrapper::setRightCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setRight(_CallExpression1->CallExpression);
}
void AssignmentExpressionWrapper::setRightClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setRight(_ClassExpression1->ClassExpression);
}
void AssignmentExpressionWrapper::setRightConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setRight(_ConditionalExpression1->ConditionalExpression);
}
void AssignmentExpressionWrapper::setRightFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setRight(_FunctionExpression1->FunctionExpression);
}
void AssignmentExpressionWrapper::setRightIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setRight(_Identifier1->Identifier);
}
void AssignmentExpressionWrapper::setRightBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setRight(_BooleanLiteral1->BooleanLiteral);
}
void AssignmentExpressionWrapper::setRightNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setRight(_NullLiteral1->NullLiteral);
}
void AssignmentExpressionWrapper::setRightNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setRight(_NumberLiteral1->NumberLiteral);
}
void AssignmentExpressionWrapper::setRightRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setRight(_RegExpLiteral1->RegExpLiteral);
}
void AssignmentExpressionWrapper::setRightStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setRight(_StringLiteral1->StringLiteral);
}
void AssignmentExpressionWrapper::setRightLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setRight(_LogicalExpression1->LogicalExpression);
}
void AssignmentExpressionWrapper::setRightMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setRight(_MemberExpression1->MemberExpression);
}
void AssignmentExpressionWrapper::setRightMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setRight(_MetaProperty1->MetaProperty);
}
void AssignmentExpressionWrapper::setRightNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setRight(_NewExpression1->NewExpression);
}
void AssignmentExpressionWrapper::setRightObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setRight(_ObjectExpression1->ObjectExpression);
}
void AssignmentExpressionWrapper::setRightSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setRight(_SequenceExpression1->SequenceExpression);
}
void AssignmentExpressionWrapper::setRightTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setRight(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void AssignmentExpressionWrapper::setRightTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setRight(_TemplateLiteral1->TemplateLiteral);
}
void AssignmentExpressionWrapper::setRightThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setRight(_ThisExpression1->ThisExpression);
}
void AssignmentExpressionWrapper::setRightUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setRight(_UnaryExpression1->UnaryExpression);
}
void AssignmentExpressionWrapper::setRightUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setRight(_UpdateExpression1->UpdateExpression);
}
void AssignmentExpressionWrapper::setRightYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->setRight(_YieldExpression1->YieldExpression);
}
void AssignmentExpressionWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  AssignmentExpressionWrapper* _AssignmentExpression2 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());

  _AssignmentExpression2->AssignmentExpression->addComments(_Comment1->Comment);
}
void AssignmentExpressionWrapper::setOperator(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  AssignmentExpressionWrapper* _AssignmentExpression = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  if( param == "asoAssign" ){
    _AssignmentExpression->AssignmentExpression->setOperator( asoAssign );
  }
  if( param == "asoAdd" ){
    _AssignmentExpression->AssignmentExpression->setOperator( asoAdd );
  }
  if( param == "asoSubtract" ){
    _AssignmentExpression->AssignmentExpression->setOperator( asoSubtract );
  }
  if( param == "asoMultiplication" ){
    _AssignmentExpression->AssignmentExpression->setOperator( asoMultiplication );
  }
  if( param == "asoDivision" ){
    _AssignmentExpression->AssignmentExpression->setOperator( asoDivision );
  }
  if( param == "asoModulus" ){
    _AssignmentExpression->AssignmentExpression->setOperator( asoModulus );
  }
  if( param == "asoLeftShift" ){
    _AssignmentExpression->AssignmentExpression->setOperator( asoLeftShift );
  }
  if( param == "asoRightShift" ){
    _AssignmentExpression->AssignmentExpression->setOperator( asoRightShift );
  }
  if( param == "asoFillNullRightShift" ){
    _AssignmentExpression->AssignmentExpression->setOperator( asoFillNullRightShift );
  }
  if( param == "asoBitwiseOr" ){
    _AssignmentExpression->AssignmentExpression->setOperator( asoBitwiseOr );
  }
  if( param == "asoBitwiseXor" ){
    _AssignmentExpression->AssignmentExpression->setOperator( asoBitwiseXor );
  }
  if( param == "asoBitwiseAnd" ){
    _AssignmentExpression->AssignmentExpression->setOperator( asoBitwiseAnd );
  }
  if( param == "asoExponentiation" ){
    _AssignmentExpression->AssignmentExpression->setOperator( asoExponentiation );
  }
}
void AssignmentExpressionWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  AssignmentExpressionWrapper* _AssignmentExpression = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _AssignmentExpression->AssignmentExpression->getPosition();
  range.setPath( param );
  _AssignmentExpression->AssignmentExpression->setPosition( range );
}

void AssignmentExpressionWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  AssignmentExpressionWrapper* _AssignmentExpression = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _AssignmentExpression->AssignmentExpression->getPosition();
  range.setLine( ui );
  _AssignmentExpression->AssignmentExpression->setPosition( range );
}

void AssignmentExpressionWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  AssignmentExpressionWrapper* _AssignmentExpression = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _AssignmentExpression->AssignmentExpression->getPosition();
  range.setCol( ui );
  _AssignmentExpression->AssignmentExpression->setPosition( range );
}

void AssignmentExpressionWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  AssignmentExpressionWrapper* _AssignmentExpression = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _AssignmentExpression->AssignmentExpression->getPosition();
  range.setEndLine( ui );
  _AssignmentExpression->AssignmentExpression->setPosition( range );
}

void AssignmentExpressionWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  AssignmentExpressionWrapper* _AssignmentExpression = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _AssignmentExpression->AssignmentExpression->getPosition();
  range.setEndCol( ui );
  _AssignmentExpression->AssignmentExpression->setPosition( range );
}

void AssignmentExpressionWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  AssignmentExpressionWrapper* _AssignmentExpression = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _AssignmentExpression->AssignmentExpression->getPosition();
  range.setWideLine( ui );
  _AssignmentExpression->AssignmentExpression->setPosition( range );
}

void AssignmentExpressionWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  AssignmentExpressionWrapper* _AssignmentExpression = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _AssignmentExpression->AssignmentExpression->getPosition();
  range.setWideCol( ui );
  _AssignmentExpression->AssignmentExpression->setPosition( range );
}

void AssignmentExpressionWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  AssignmentExpressionWrapper* _AssignmentExpression = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _AssignmentExpression->AssignmentExpression->getPosition();
  range.setWideEndLine( ui );
  _AssignmentExpression->AssignmentExpression->setPosition( range );
}

void AssignmentExpressionWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  AssignmentExpressionWrapper* _AssignmentExpression = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _AssignmentExpression->AssignmentExpression->getPosition();
  range.setWideEndCol( ui );
  _AssignmentExpression->AssignmentExpression->setPosition( range );
}

}}}} //end of namespaces