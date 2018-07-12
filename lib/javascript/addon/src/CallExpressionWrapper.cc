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

#include "../inc/CallExpressionWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> CallExpressionWrapper::constructor;

void CallExpressionWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "CallExpressionWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "setCalleeArrayExpression", setCalleeArrayExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setCalleeArrowFunctionExpression", setCalleeArrowFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setCalleeAssignmentExpression", setCalleeAssignmentExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setCalleeAwaitExpression", setCalleeAwaitExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setCalleeBinaryExpression", setCalleeBinaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setCalleeCallExpression", setCalleeCallExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setCalleeClassExpression", setCalleeClassExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setCalleeConditionalExpression", setCalleeConditionalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setCalleeFunctionExpression", setCalleeFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setCalleeIdentifier", setCalleeIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setCalleeBooleanLiteral", setCalleeBooleanLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setCalleeNullLiteral", setCalleeNullLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setCalleeNumberLiteral", setCalleeNumberLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setCalleeRegExpLiteral", setCalleeRegExpLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setCalleeStringLiteral", setCalleeStringLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setCalleeLogicalExpression", setCalleeLogicalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setCalleeMemberExpression", setCalleeMemberExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setCalleeMetaProperty", setCalleeMetaProperty);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setCalleeNewExpression", setCalleeNewExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setCalleeObjectExpression", setCalleeObjectExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setCalleeSequenceExpression", setCalleeSequenceExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setCalleeTaggedTemplateExpression", setCalleeTaggedTemplateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setCalleeTemplateLiteral", setCalleeTemplateLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setCalleeThisExpression", setCalleeThisExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setCalleeUnaryExpression", setCalleeUnaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setCalleeUpdateExpression", setCalleeUpdateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setCalleeYieldExpression", setCalleeYieldExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setCalleeSuper", setCalleeSuper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addArgumentsArrayExpression", addArgumentsArrayExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addArgumentsArrowFunctionExpression", addArgumentsArrowFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addArgumentsAssignmentExpression", addArgumentsAssignmentExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addArgumentsAwaitExpression", addArgumentsAwaitExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addArgumentsBinaryExpression", addArgumentsBinaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addArgumentsCallExpression", addArgumentsCallExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addArgumentsClassExpression", addArgumentsClassExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addArgumentsConditionalExpression", addArgumentsConditionalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addArgumentsFunctionExpression", addArgumentsFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addArgumentsIdentifier", addArgumentsIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addArgumentsBooleanLiteral", addArgumentsBooleanLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addArgumentsNullLiteral", addArgumentsNullLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addArgumentsNumberLiteral", addArgumentsNumberLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addArgumentsRegExpLiteral", addArgumentsRegExpLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addArgumentsStringLiteral", addArgumentsStringLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addArgumentsLogicalExpression", addArgumentsLogicalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addArgumentsMemberExpression", addArgumentsMemberExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addArgumentsMetaProperty", addArgumentsMetaProperty);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addArgumentsNewExpression", addArgumentsNewExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addArgumentsObjectExpression", addArgumentsObjectExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addArgumentsSequenceExpression", addArgumentsSequenceExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addArgumentsTaggedTemplateExpression", addArgumentsTaggedTemplateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addArgumentsTemplateLiteral", addArgumentsTemplateLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addArgumentsThisExpression", addArgumentsThisExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addArgumentsUnaryExpression", addArgumentsUnaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addArgumentsUpdateExpression", addArgumentsUpdateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addArgumentsYieldExpression", addArgumentsYieldExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addArgumentsSpreadElement", addArgumentsSpreadElement);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "CallExpressionWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void CallExpressionWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new CallExpressionWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    CallExpressionWrapper* obj = new CallExpressionWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `CallExpressionWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


CallExpressionWrapper::CallExpressionWrapper(Factory* fact)                        
{                                                   
  CallExpression = fact->getFactory()->createCallExpressionNode();          
}                                                   

CallExpressionWrapper::~CallExpressionWrapper()
{        
}        

void CallExpressionWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void CallExpressionWrapper::setCalleeArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->setCallee(_ArrayExpression1->ArrayExpression);
}
void CallExpressionWrapper::setCalleeArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->setCallee(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void CallExpressionWrapper::setCalleeAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->setCallee(_AssignmentExpression1->AssignmentExpression);
}
void CallExpressionWrapper::setCalleeAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->setCallee(_AwaitExpression1->AwaitExpression);
}
void CallExpressionWrapper::setCalleeBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->setCallee(_BinaryExpression1->BinaryExpression);
}
void CallExpressionWrapper::setCalleeCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->setCallee(_CallExpression1->CallExpression);
}
void CallExpressionWrapper::setCalleeClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->setCallee(_ClassExpression1->ClassExpression);
}
void CallExpressionWrapper::setCalleeConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->setCallee(_ConditionalExpression1->ConditionalExpression);
}
void CallExpressionWrapper::setCalleeFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->setCallee(_FunctionExpression1->FunctionExpression);
}
void CallExpressionWrapper::setCalleeIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->setCallee(_Identifier1->Identifier);
}
void CallExpressionWrapper::setCalleeBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->setCallee(_BooleanLiteral1->BooleanLiteral);
}
void CallExpressionWrapper::setCalleeNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->setCallee(_NullLiteral1->NullLiteral);
}
void CallExpressionWrapper::setCalleeNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->setCallee(_NumberLiteral1->NumberLiteral);
}
void CallExpressionWrapper::setCalleeRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->setCallee(_RegExpLiteral1->RegExpLiteral);
}
void CallExpressionWrapper::setCalleeStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->setCallee(_StringLiteral1->StringLiteral);
}
void CallExpressionWrapper::setCalleeLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->setCallee(_LogicalExpression1->LogicalExpression);
}
void CallExpressionWrapper::setCalleeMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->setCallee(_MemberExpression1->MemberExpression);
}
void CallExpressionWrapper::setCalleeMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->setCallee(_MetaProperty1->MetaProperty);
}
void CallExpressionWrapper::setCalleeNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->setCallee(_NewExpression1->NewExpression);
}
void CallExpressionWrapper::setCalleeObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->setCallee(_ObjectExpression1->ObjectExpression);
}
void CallExpressionWrapper::setCalleeSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->setCallee(_SequenceExpression1->SequenceExpression);
}
void CallExpressionWrapper::setCalleeTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->setCallee(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void CallExpressionWrapper::setCalleeTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->setCallee(_TemplateLiteral1->TemplateLiteral);
}
void CallExpressionWrapper::setCalleeThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->setCallee(_ThisExpression1->ThisExpression);
}
void CallExpressionWrapper::setCalleeUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->setCallee(_UnaryExpression1->UnaryExpression);
}
void CallExpressionWrapper::setCalleeUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->setCallee(_UpdateExpression1->UpdateExpression);
}
void CallExpressionWrapper::setCalleeYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->setCallee(_YieldExpression1->YieldExpression);
}
void CallExpressionWrapper::setCalleeSuper(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SuperWrapper* _Super1 = ObjectWrap::Unwrap<SuperWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->setCallee(_Super1->Super);
}
void CallExpressionWrapper::addArgumentsArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->addArguments(_ArrayExpression1->ArrayExpression);
}
void CallExpressionWrapper::addArgumentsArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->addArguments(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void CallExpressionWrapper::addArgumentsAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->addArguments(_AssignmentExpression1->AssignmentExpression);
}
void CallExpressionWrapper::addArgumentsAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->addArguments(_AwaitExpression1->AwaitExpression);
}
void CallExpressionWrapper::addArgumentsBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->addArguments(_BinaryExpression1->BinaryExpression);
}
void CallExpressionWrapper::addArgumentsCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->addArguments(_CallExpression1->CallExpression);
}
void CallExpressionWrapper::addArgumentsClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->addArguments(_ClassExpression1->ClassExpression);
}
void CallExpressionWrapper::addArgumentsConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->addArguments(_ConditionalExpression1->ConditionalExpression);
}
void CallExpressionWrapper::addArgumentsFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->addArguments(_FunctionExpression1->FunctionExpression);
}
void CallExpressionWrapper::addArgumentsIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->addArguments(_Identifier1->Identifier);
}
void CallExpressionWrapper::addArgumentsBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->addArguments(_BooleanLiteral1->BooleanLiteral);
}
void CallExpressionWrapper::addArgumentsNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->addArguments(_NullLiteral1->NullLiteral);
}
void CallExpressionWrapper::addArgumentsNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->addArguments(_NumberLiteral1->NumberLiteral);
}
void CallExpressionWrapper::addArgumentsRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->addArguments(_RegExpLiteral1->RegExpLiteral);
}
void CallExpressionWrapper::addArgumentsStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->addArguments(_StringLiteral1->StringLiteral);
}
void CallExpressionWrapper::addArgumentsLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->addArguments(_LogicalExpression1->LogicalExpression);
}
void CallExpressionWrapper::addArgumentsMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->addArguments(_MemberExpression1->MemberExpression);
}
void CallExpressionWrapper::addArgumentsMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->addArguments(_MetaProperty1->MetaProperty);
}
void CallExpressionWrapper::addArgumentsNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->addArguments(_NewExpression1->NewExpression);
}
void CallExpressionWrapper::addArgumentsObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->addArguments(_ObjectExpression1->ObjectExpression);
}
void CallExpressionWrapper::addArgumentsSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->addArguments(_SequenceExpression1->SequenceExpression);
}
void CallExpressionWrapper::addArgumentsTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->addArguments(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void CallExpressionWrapper::addArgumentsTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->addArguments(_TemplateLiteral1->TemplateLiteral);
}
void CallExpressionWrapper::addArgumentsThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->addArguments(_ThisExpression1->ThisExpression);
}
void CallExpressionWrapper::addArgumentsUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->addArguments(_UnaryExpression1->UnaryExpression);
}
void CallExpressionWrapper::addArgumentsUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->addArguments(_UpdateExpression1->UpdateExpression);
}
void CallExpressionWrapper::addArgumentsYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->addArguments(_YieldExpression1->YieldExpression);
}
void CallExpressionWrapper::addArgumentsSpreadElement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SpreadElementWrapper* _SpreadElement1 = ObjectWrap::Unwrap<SpreadElementWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->addArguments(_SpreadElement1->SpreadElement);
}
void CallExpressionWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  CallExpressionWrapper* _CallExpression2 = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());

  _CallExpression2->CallExpression->addComments(_Comment1->Comment);
}
void CallExpressionWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  CallExpressionWrapper* _CallExpression = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _CallExpression->CallExpression->getPosition();
  range.setPath( param );
  _CallExpression->CallExpression->setPosition( range );
}

void CallExpressionWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  CallExpressionWrapper* _CallExpression = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _CallExpression->CallExpression->getPosition();
  range.setLine( ui );
  _CallExpression->CallExpression->setPosition( range );
}

void CallExpressionWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  CallExpressionWrapper* _CallExpression = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _CallExpression->CallExpression->getPosition();
  range.setCol( ui );
  _CallExpression->CallExpression->setPosition( range );
}

void CallExpressionWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  CallExpressionWrapper* _CallExpression = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _CallExpression->CallExpression->getPosition();
  range.setEndLine( ui );
  _CallExpression->CallExpression->setPosition( range );
}

void CallExpressionWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  CallExpressionWrapper* _CallExpression = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _CallExpression->CallExpression->getPosition();
  range.setEndCol( ui );
  _CallExpression->CallExpression->setPosition( range );
}

void CallExpressionWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  CallExpressionWrapper* _CallExpression = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _CallExpression->CallExpression->getPosition();
  range.setWideLine( ui );
  _CallExpression->CallExpression->setPosition( range );
}

void CallExpressionWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  CallExpressionWrapper* _CallExpression = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _CallExpression->CallExpression->getPosition();
  range.setWideCol( ui );
  _CallExpression->CallExpression->setPosition( range );
}

void CallExpressionWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  CallExpressionWrapper* _CallExpression = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _CallExpression->CallExpression->getPosition();
  range.setWideEndLine( ui );
  _CallExpression->CallExpression->setPosition( range );
}

void CallExpressionWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  CallExpressionWrapper* _CallExpression = ObjectWrap::Unwrap<CallExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _CallExpression->CallExpression->getPosition();
  range.setWideEndCol( ui );
  _CallExpression->CallExpression->setPosition( range );
}

}}}} //end of namespaces