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

#include "../inc/MemberExpressionWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> MemberExpressionWrapper::constructor;

void MemberExpressionWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "MemberExpressionWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPropertyArrayExpression", setPropertyArrayExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPropertyArrowFunctionExpression", setPropertyArrowFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPropertyAssignmentExpression", setPropertyAssignmentExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPropertyAwaitExpression", setPropertyAwaitExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPropertyBinaryExpression", setPropertyBinaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPropertyCallExpression", setPropertyCallExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPropertyClassExpression", setPropertyClassExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPropertyConditionalExpression", setPropertyConditionalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPropertyFunctionExpression", setPropertyFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPropertyIdentifier", setPropertyIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPropertyBooleanLiteral", setPropertyBooleanLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPropertyNullLiteral", setPropertyNullLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPropertyNumberLiteral", setPropertyNumberLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPropertyRegExpLiteral", setPropertyRegExpLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPropertyStringLiteral", setPropertyStringLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPropertyLogicalExpression", setPropertyLogicalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPropertyMemberExpression", setPropertyMemberExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPropertyMetaProperty", setPropertyMetaProperty);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPropertyNewExpression", setPropertyNewExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPropertyObjectExpression", setPropertyObjectExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPropertySequenceExpression", setPropertySequenceExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPropertyTaggedTemplateExpression", setPropertyTaggedTemplateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPropertyTemplateLiteral", setPropertyTemplateLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPropertyThisExpression", setPropertyThisExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPropertyUnaryExpression", setPropertyUnaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPropertyUpdateExpression", setPropertyUpdateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPropertyYieldExpression", setPropertyYieldExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setObjectSuper", setObjectSuper);
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
  NODE_SET_PROTOTYPE_METHOD(tpl, "addCommentsComment", addCommentsComment);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setComputed", setComputed);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "MemberExpressionWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void MemberExpressionWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new MemberExpressionWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    MemberExpressionWrapper* obj = new MemberExpressionWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `MemberExpressionWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


MemberExpressionWrapper::MemberExpressionWrapper(Factory* fact)                        
{                                                   
  MemberExpression = fact->getFactory()->createMemberExpressionNode();          
}                                                   

MemberExpressionWrapper::~MemberExpressionWrapper()
{        
}        

void MemberExpressionWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void MemberExpressionWrapper::setPropertyArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setProperty(_ArrayExpression1->ArrayExpression);
}
void MemberExpressionWrapper::setPropertyArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setProperty(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void MemberExpressionWrapper::setPropertyAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setProperty(_AssignmentExpression1->AssignmentExpression);
}
void MemberExpressionWrapper::setPropertyAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setProperty(_AwaitExpression1->AwaitExpression);
}
void MemberExpressionWrapper::setPropertyBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setProperty(_BinaryExpression1->BinaryExpression);
}
void MemberExpressionWrapper::setPropertyCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setProperty(_CallExpression1->CallExpression);
}
void MemberExpressionWrapper::setPropertyClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setProperty(_ClassExpression1->ClassExpression);
}
void MemberExpressionWrapper::setPropertyConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setProperty(_ConditionalExpression1->ConditionalExpression);
}
void MemberExpressionWrapper::setPropertyFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setProperty(_FunctionExpression1->FunctionExpression);
}
void MemberExpressionWrapper::setPropertyIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setProperty(_Identifier1->Identifier);
}
void MemberExpressionWrapper::setPropertyBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setProperty(_BooleanLiteral1->BooleanLiteral);
}
void MemberExpressionWrapper::setPropertyNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setProperty(_NullLiteral1->NullLiteral);
}
void MemberExpressionWrapper::setPropertyNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setProperty(_NumberLiteral1->NumberLiteral);
}
void MemberExpressionWrapper::setPropertyRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setProperty(_RegExpLiteral1->RegExpLiteral);
}
void MemberExpressionWrapper::setPropertyStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setProperty(_StringLiteral1->StringLiteral);
}
void MemberExpressionWrapper::setPropertyLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setProperty(_LogicalExpression1->LogicalExpression);
}
void MemberExpressionWrapper::setPropertyMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setProperty(_MemberExpression1->MemberExpression);
}
void MemberExpressionWrapper::setPropertyMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setProperty(_MetaProperty1->MetaProperty);
}
void MemberExpressionWrapper::setPropertyNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setProperty(_NewExpression1->NewExpression);
}
void MemberExpressionWrapper::setPropertyObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setProperty(_ObjectExpression1->ObjectExpression);
}
void MemberExpressionWrapper::setPropertySequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setProperty(_SequenceExpression1->SequenceExpression);
}
void MemberExpressionWrapper::setPropertyTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setProperty(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void MemberExpressionWrapper::setPropertyTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setProperty(_TemplateLiteral1->TemplateLiteral);
}
void MemberExpressionWrapper::setPropertyThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setProperty(_ThisExpression1->ThisExpression);
}
void MemberExpressionWrapper::setPropertyUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setProperty(_UnaryExpression1->UnaryExpression);
}
void MemberExpressionWrapper::setPropertyUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setProperty(_UpdateExpression1->UpdateExpression);
}
void MemberExpressionWrapper::setPropertyYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setProperty(_YieldExpression1->YieldExpression);
}
void MemberExpressionWrapper::setObjectSuper(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SuperWrapper* _Super1 = ObjectWrap::Unwrap<SuperWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setObject(_Super1->Super);
}
void MemberExpressionWrapper::setObjectArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setObject(_ArrayExpression1->ArrayExpression);
}
void MemberExpressionWrapper::setObjectArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setObject(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void MemberExpressionWrapper::setObjectAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setObject(_AssignmentExpression1->AssignmentExpression);
}
void MemberExpressionWrapper::setObjectAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setObject(_AwaitExpression1->AwaitExpression);
}
void MemberExpressionWrapper::setObjectBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setObject(_BinaryExpression1->BinaryExpression);
}
void MemberExpressionWrapper::setObjectCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setObject(_CallExpression1->CallExpression);
}
void MemberExpressionWrapper::setObjectClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setObject(_ClassExpression1->ClassExpression);
}
void MemberExpressionWrapper::setObjectConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setObject(_ConditionalExpression1->ConditionalExpression);
}
void MemberExpressionWrapper::setObjectFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setObject(_FunctionExpression1->FunctionExpression);
}
void MemberExpressionWrapper::setObjectIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setObject(_Identifier1->Identifier);
}
void MemberExpressionWrapper::setObjectBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setObject(_BooleanLiteral1->BooleanLiteral);
}
void MemberExpressionWrapper::setObjectNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setObject(_NullLiteral1->NullLiteral);
}
void MemberExpressionWrapper::setObjectNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setObject(_NumberLiteral1->NumberLiteral);
}
void MemberExpressionWrapper::setObjectRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setObject(_RegExpLiteral1->RegExpLiteral);
}
void MemberExpressionWrapper::setObjectStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setObject(_StringLiteral1->StringLiteral);
}
void MemberExpressionWrapper::setObjectLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setObject(_LogicalExpression1->LogicalExpression);
}
void MemberExpressionWrapper::setObjectMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setObject(_MemberExpression1->MemberExpression);
}
void MemberExpressionWrapper::setObjectMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setObject(_MetaProperty1->MetaProperty);
}
void MemberExpressionWrapper::setObjectNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setObject(_NewExpression1->NewExpression);
}
void MemberExpressionWrapper::setObjectObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setObject(_ObjectExpression1->ObjectExpression);
}
void MemberExpressionWrapper::setObjectSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setObject(_SequenceExpression1->SequenceExpression);
}
void MemberExpressionWrapper::setObjectTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setObject(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void MemberExpressionWrapper::setObjectTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setObject(_TemplateLiteral1->TemplateLiteral);
}
void MemberExpressionWrapper::setObjectThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setObject(_ThisExpression1->ThisExpression);
}
void MemberExpressionWrapper::setObjectUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setObject(_UnaryExpression1->UnaryExpression);
}
void MemberExpressionWrapper::setObjectUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setObject(_UpdateExpression1->UpdateExpression);
}
void MemberExpressionWrapper::setObjectYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->setObject(_YieldExpression1->YieldExpression);
}
void MemberExpressionWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  MemberExpressionWrapper* _MemberExpression2 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());

  _MemberExpression2->MemberExpression->addComments(_Comment1->Comment);
}
void MemberExpressionWrapper::setComputed(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  MemberExpressionWrapper* _MemberExpression = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::transform(param.begin(), param.end(), param.begin(), ::tolower);
  std::istringstream is(param);                                    
  bool b;                                                        
  is >> std::boolalpha >> b;                                     
  _MemberExpression->MemberExpression->setComputed( b );
}
void MemberExpressionWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  MemberExpressionWrapper* _MemberExpression = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _MemberExpression->MemberExpression->getPosition();
  range.setPath( param );
  _MemberExpression->MemberExpression->setPosition( range );
}

void MemberExpressionWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  MemberExpressionWrapper* _MemberExpression = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _MemberExpression->MemberExpression->getPosition();
  range.setLine( ui );
  _MemberExpression->MemberExpression->setPosition( range );
}

void MemberExpressionWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  MemberExpressionWrapper* _MemberExpression = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _MemberExpression->MemberExpression->getPosition();
  range.setCol( ui );
  _MemberExpression->MemberExpression->setPosition( range );
}

void MemberExpressionWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  MemberExpressionWrapper* _MemberExpression = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _MemberExpression->MemberExpression->getPosition();
  range.setEndLine( ui );
  _MemberExpression->MemberExpression->setPosition( range );
}

void MemberExpressionWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  MemberExpressionWrapper* _MemberExpression = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _MemberExpression->MemberExpression->getPosition();
  range.setEndCol( ui );
  _MemberExpression->MemberExpression->setPosition( range );
}

void MemberExpressionWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  MemberExpressionWrapper* _MemberExpression = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _MemberExpression->MemberExpression->getPosition();
  range.setWideLine( ui );
  _MemberExpression->MemberExpression->setPosition( range );
}

void MemberExpressionWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  MemberExpressionWrapper* _MemberExpression = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _MemberExpression->MemberExpression->getPosition();
  range.setWideCol( ui );
  _MemberExpression->MemberExpression->setPosition( range );
}

void MemberExpressionWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  MemberExpressionWrapper* _MemberExpression = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _MemberExpression->MemberExpression->getPosition();
  range.setWideEndLine( ui );
  _MemberExpression->MemberExpression->setPosition( range );
}

void MemberExpressionWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  MemberExpressionWrapper* _MemberExpression = ObjectWrap::Unwrap<MemberExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _MemberExpression->MemberExpression->getPosition();
  range.setWideEndCol( ui );
  _MemberExpression->MemberExpression->setPosition( range );
}

}}}} //end of namespaces