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

#include "../inc/AssignmentPropertyWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> AssignmentPropertyWrapper::constructor;

void AssignmentPropertyWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "AssignmentPropertyWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "setValueArrayExpression", setValueArrayExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setValueArrowFunctionExpression", setValueArrowFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setValueAssignmentExpression", setValueAssignmentExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setValueAwaitExpression", setValueAwaitExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setValueBinaryExpression", setValueBinaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setValueCallExpression", setValueCallExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setValueClassExpression", setValueClassExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setValueConditionalExpression", setValueConditionalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setValueFunctionExpression", setValueFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setValueIdentifier", setValueIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setValueBooleanLiteral", setValueBooleanLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setValueNullLiteral", setValueNullLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setValueNumberLiteral", setValueNumberLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setValueRegExpLiteral", setValueRegExpLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setValueStringLiteral", setValueStringLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setValueLogicalExpression", setValueLogicalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setValueMemberExpression", setValueMemberExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setValueMetaProperty", setValueMetaProperty);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setValueNewExpression", setValueNewExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setValueObjectExpression", setValueObjectExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setValueSequenceExpression", setValueSequenceExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setValueTaggedTemplateExpression", setValueTaggedTemplateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setValueTemplateLiteral", setValueTemplateLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setValueThisExpression", setValueThisExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setValueUnaryExpression", setValueUnaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setValueUpdateExpression", setValueUpdateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setValueYieldExpression", setValueYieldExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setValueArrayPattern", setValueArrayPattern);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setValueAssignmentPattern", setValueAssignmentPattern);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setValueObjectPattern", setValueObjectPattern);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setValueRestElement", setValueRestElement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyArrayExpression", setKeyArrayExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyArrowFunctionExpression", setKeyArrowFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyAssignmentExpression", setKeyAssignmentExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyAwaitExpression", setKeyAwaitExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyBinaryExpression", setKeyBinaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyCallExpression", setKeyCallExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyClassExpression", setKeyClassExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyConditionalExpression", setKeyConditionalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyFunctionExpression", setKeyFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyIdentifier", setKeyIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyBooleanLiteral", setKeyBooleanLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyNullLiteral", setKeyNullLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyNumberLiteral", setKeyNumberLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyRegExpLiteral", setKeyRegExpLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyStringLiteral", setKeyStringLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyLogicalExpression", setKeyLogicalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyMemberExpression", setKeyMemberExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyMetaProperty", setKeyMetaProperty);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyNewExpression", setKeyNewExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyObjectExpression", setKeyObjectExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeySequenceExpression", setKeySequenceExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyTaggedTemplateExpression", setKeyTaggedTemplateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyTemplateLiteral", setKeyTemplateLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyThisExpression", setKeyThisExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyUnaryExpression", setKeyUnaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyUpdateExpression", setKeyUpdateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyYieldExpression", setKeyYieldExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addCommentsComment", addCommentsComment);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKind", setKind);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setMethod", setMethod);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setShorthand", setShorthand);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "AssignmentPropertyWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void AssignmentPropertyWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new AssignmentPropertyWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    AssignmentPropertyWrapper* obj = new AssignmentPropertyWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `AssignmentPropertyWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


AssignmentPropertyWrapper::AssignmentPropertyWrapper(Factory* fact)                        
{                                                   
  AssignmentProperty = fact->getFactory()->createAssignmentPropertyNode();          
}                                                   

AssignmentPropertyWrapper::~AssignmentPropertyWrapper()
{        
}        

void AssignmentPropertyWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void AssignmentPropertyWrapper::setValueArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setValue(_ArrayExpression1->ArrayExpression);
}
void AssignmentPropertyWrapper::setValueArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setValue(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void AssignmentPropertyWrapper::setValueAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setValue(_AssignmentExpression1->AssignmentExpression);
}
void AssignmentPropertyWrapper::setValueAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setValue(_AwaitExpression1->AwaitExpression);
}
void AssignmentPropertyWrapper::setValueBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setValue(_BinaryExpression1->BinaryExpression);
}
void AssignmentPropertyWrapper::setValueCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setValue(_CallExpression1->CallExpression);
}
void AssignmentPropertyWrapper::setValueClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setValue(_ClassExpression1->ClassExpression);
}
void AssignmentPropertyWrapper::setValueConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setValue(_ConditionalExpression1->ConditionalExpression);
}
void AssignmentPropertyWrapper::setValueFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setValue(_FunctionExpression1->FunctionExpression);
}
void AssignmentPropertyWrapper::setValueIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setValue(_Identifier1->Identifier);
}
void AssignmentPropertyWrapper::setValueBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setValue(_BooleanLiteral1->BooleanLiteral);
}
void AssignmentPropertyWrapper::setValueNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setValue(_NullLiteral1->NullLiteral);
}
void AssignmentPropertyWrapper::setValueNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setValue(_NumberLiteral1->NumberLiteral);
}
void AssignmentPropertyWrapper::setValueRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setValue(_RegExpLiteral1->RegExpLiteral);
}
void AssignmentPropertyWrapper::setValueStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setValue(_StringLiteral1->StringLiteral);
}
void AssignmentPropertyWrapper::setValueLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setValue(_LogicalExpression1->LogicalExpression);
}
void AssignmentPropertyWrapper::setValueMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setValue(_MemberExpression1->MemberExpression);
}
void AssignmentPropertyWrapper::setValueMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setValue(_MetaProperty1->MetaProperty);
}
void AssignmentPropertyWrapper::setValueNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setValue(_NewExpression1->NewExpression);
}
void AssignmentPropertyWrapper::setValueObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setValue(_ObjectExpression1->ObjectExpression);
}
void AssignmentPropertyWrapper::setValueSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setValue(_SequenceExpression1->SequenceExpression);
}
void AssignmentPropertyWrapper::setValueTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setValue(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void AssignmentPropertyWrapper::setValueTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setValue(_TemplateLiteral1->TemplateLiteral);
}
void AssignmentPropertyWrapper::setValueThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setValue(_ThisExpression1->ThisExpression);
}
void AssignmentPropertyWrapper::setValueUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setValue(_UnaryExpression1->UnaryExpression);
}
void AssignmentPropertyWrapper::setValueUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setValue(_UpdateExpression1->UpdateExpression);
}
void AssignmentPropertyWrapper::setValueYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setValue(_YieldExpression1->YieldExpression);
}
void AssignmentPropertyWrapper::setValueArrayPattern(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayPatternWrapper* _ArrayPattern1 = ObjectWrap::Unwrap<ArrayPatternWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setValue(_ArrayPattern1->ArrayPattern);
}
void AssignmentPropertyWrapper::setValueAssignmentPattern(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentPatternWrapper* _AssignmentPattern1 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setValue(_AssignmentPattern1->AssignmentPattern);
}
void AssignmentPropertyWrapper::setValueObjectPattern(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectPatternWrapper* _ObjectPattern1 = ObjectWrap::Unwrap<ObjectPatternWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setValue(_ObjectPattern1->ObjectPattern);
}
void AssignmentPropertyWrapper::setValueRestElement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RestElementWrapper* _RestElement1 = ObjectWrap::Unwrap<RestElementWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setValue(_RestElement1->RestElement);
}
void AssignmentPropertyWrapper::setKeyArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setKey(_ArrayExpression1->ArrayExpression);
}
void AssignmentPropertyWrapper::setKeyArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setKey(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void AssignmentPropertyWrapper::setKeyAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setKey(_AssignmentExpression1->AssignmentExpression);
}
void AssignmentPropertyWrapper::setKeyAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setKey(_AwaitExpression1->AwaitExpression);
}
void AssignmentPropertyWrapper::setKeyBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setKey(_BinaryExpression1->BinaryExpression);
}
void AssignmentPropertyWrapper::setKeyCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setKey(_CallExpression1->CallExpression);
}
void AssignmentPropertyWrapper::setKeyClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setKey(_ClassExpression1->ClassExpression);
}
void AssignmentPropertyWrapper::setKeyConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setKey(_ConditionalExpression1->ConditionalExpression);
}
void AssignmentPropertyWrapper::setKeyFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setKey(_FunctionExpression1->FunctionExpression);
}
void AssignmentPropertyWrapper::setKeyIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setKey(_Identifier1->Identifier);
}
void AssignmentPropertyWrapper::setKeyBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setKey(_BooleanLiteral1->BooleanLiteral);
}
void AssignmentPropertyWrapper::setKeyNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setKey(_NullLiteral1->NullLiteral);
}
void AssignmentPropertyWrapper::setKeyNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setKey(_NumberLiteral1->NumberLiteral);
}
void AssignmentPropertyWrapper::setKeyRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setKey(_RegExpLiteral1->RegExpLiteral);
}
void AssignmentPropertyWrapper::setKeyStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setKey(_StringLiteral1->StringLiteral);
}
void AssignmentPropertyWrapper::setKeyLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setKey(_LogicalExpression1->LogicalExpression);
}
void AssignmentPropertyWrapper::setKeyMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setKey(_MemberExpression1->MemberExpression);
}
void AssignmentPropertyWrapper::setKeyMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setKey(_MetaProperty1->MetaProperty);
}
void AssignmentPropertyWrapper::setKeyNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setKey(_NewExpression1->NewExpression);
}
void AssignmentPropertyWrapper::setKeyObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setKey(_ObjectExpression1->ObjectExpression);
}
void AssignmentPropertyWrapper::setKeySequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setKey(_SequenceExpression1->SequenceExpression);
}
void AssignmentPropertyWrapper::setKeyTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setKey(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void AssignmentPropertyWrapper::setKeyTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setKey(_TemplateLiteral1->TemplateLiteral);
}
void AssignmentPropertyWrapper::setKeyThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setKey(_ThisExpression1->ThisExpression);
}
void AssignmentPropertyWrapper::setKeyUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setKey(_UnaryExpression1->UnaryExpression);
}
void AssignmentPropertyWrapper::setKeyUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setKey(_UpdateExpression1->UpdateExpression);
}
void AssignmentPropertyWrapper::setKeyYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->setKey(_YieldExpression1->YieldExpression);
}
void AssignmentPropertyWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  AssignmentPropertyWrapper* _AssignmentProperty2 = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());

  _AssignmentProperty2->AssignmentProperty->addComments(_Comment1->Comment);
}
void AssignmentPropertyWrapper::setKind(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  AssignmentPropertyWrapper* _AssignmentProperty = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  if( param == "pkInit" ){
    _AssignmentProperty->AssignmentProperty->setKind( pkInit );
  }
  if( param == "pkGet" ){
    _AssignmentProperty->AssignmentProperty->setKind( pkGet );
  }
  if( param == "pkSet" ){
    _AssignmentProperty->AssignmentProperty->setKind( pkSet );
  }
}
void AssignmentPropertyWrapper::setMethod(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  AssignmentPropertyWrapper* _AssignmentProperty = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::transform(param.begin(), param.end(), param.begin(), ::tolower);
  std::istringstream is(param);                                    
  bool b;                                                        
  is >> std::boolalpha >> b;                                     
  _AssignmentProperty->AssignmentProperty->setMethod( b );
}
void AssignmentPropertyWrapper::setShorthand(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  AssignmentPropertyWrapper* _AssignmentProperty = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::transform(param.begin(), param.end(), param.begin(), ::tolower);
  std::istringstream is(param);                                    
  bool b;                                                        
  is >> std::boolalpha >> b;                                     
  _AssignmentProperty->AssignmentProperty->setShorthand( b );
}
void AssignmentPropertyWrapper::setComputed(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  AssignmentPropertyWrapper* _AssignmentProperty = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::transform(param.begin(), param.end(), param.begin(), ::tolower);
  std::istringstream is(param);                                    
  bool b;                                                        
  is >> std::boolalpha >> b;                                     
  _AssignmentProperty->AssignmentProperty->setComputed( b );
}
void AssignmentPropertyWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  AssignmentPropertyWrapper* _AssignmentProperty = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _AssignmentProperty->AssignmentProperty->getPosition();
  range.setPath( param );
  _AssignmentProperty->AssignmentProperty->setPosition( range );
}

void AssignmentPropertyWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  AssignmentPropertyWrapper* _AssignmentProperty = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _AssignmentProperty->AssignmentProperty->getPosition();
  range.setLine( ui );
  _AssignmentProperty->AssignmentProperty->setPosition( range );
}

void AssignmentPropertyWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  AssignmentPropertyWrapper* _AssignmentProperty = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _AssignmentProperty->AssignmentProperty->getPosition();
  range.setCol( ui );
  _AssignmentProperty->AssignmentProperty->setPosition( range );
}

void AssignmentPropertyWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  AssignmentPropertyWrapper* _AssignmentProperty = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _AssignmentProperty->AssignmentProperty->getPosition();
  range.setEndLine( ui );
  _AssignmentProperty->AssignmentProperty->setPosition( range );
}

void AssignmentPropertyWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  AssignmentPropertyWrapper* _AssignmentProperty = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _AssignmentProperty->AssignmentProperty->getPosition();
  range.setEndCol( ui );
  _AssignmentProperty->AssignmentProperty->setPosition( range );
}

void AssignmentPropertyWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  AssignmentPropertyWrapper* _AssignmentProperty = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _AssignmentProperty->AssignmentProperty->getPosition();
  range.setWideLine( ui );
  _AssignmentProperty->AssignmentProperty->setPosition( range );
}

void AssignmentPropertyWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  AssignmentPropertyWrapper* _AssignmentProperty = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _AssignmentProperty->AssignmentProperty->getPosition();
  range.setWideCol( ui );
  _AssignmentProperty->AssignmentProperty->setPosition( range );
}

void AssignmentPropertyWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  AssignmentPropertyWrapper* _AssignmentProperty = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _AssignmentProperty->AssignmentProperty->getPosition();
  range.setWideEndLine( ui );
  _AssignmentProperty->AssignmentProperty->setPosition( range );
}

void AssignmentPropertyWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  AssignmentPropertyWrapper* _AssignmentProperty = ObjectWrap::Unwrap<AssignmentPropertyWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _AssignmentProperty->AssignmentProperty->getPosition();
  range.setWideEndCol( ui );
  _AssignmentProperty->AssignmentProperty->setPosition( range );
}

}}}} //end of namespaces