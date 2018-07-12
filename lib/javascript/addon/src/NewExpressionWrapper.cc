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

#include "../inc/NewExpressionWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> NewExpressionWrapper::constructor;

void NewExpressionWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "NewExpressionWrapper"));             
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
  exports->Set(v8::String::NewFromUtf8(isolate, "NewExpressionWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void NewExpressionWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new NewExpressionWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    NewExpressionWrapper* obj = new NewExpressionWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `NewExpressionWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


NewExpressionWrapper::NewExpressionWrapper(Factory* fact)                        
{                                                   
  NewExpression = fact->getFactory()->createNewExpressionNode();          
}                                                   

NewExpressionWrapper::~NewExpressionWrapper()
{        
}        

void NewExpressionWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void NewExpressionWrapper::setCalleeArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->setCallee(_ArrayExpression1->ArrayExpression);
}
void NewExpressionWrapper::setCalleeArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->setCallee(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void NewExpressionWrapper::setCalleeAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->setCallee(_AssignmentExpression1->AssignmentExpression);
}
void NewExpressionWrapper::setCalleeAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->setCallee(_AwaitExpression1->AwaitExpression);
}
void NewExpressionWrapper::setCalleeBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->setCallee(_BinaryExpression1->BinaryExpression);
}
void NewExpressionWrapper::setCalleeCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->setCallee(_CallExpression1->CallExpression);
}
void NewExpressionWrapper::setCalleeClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->setCallee(_ClassExpression1->ClassExpression);
}
void NewExpressionWrapper::setCalleeConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->setCallee(_ConditionalExpression1->ConditionalExpression);
}
void NewExpressionWrapper::setCalleeFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->setCallee(_FunctionExpression1->FunctionExpression);
}
void NewExpressionWrapper::setCalleeIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->setCallee(_Identifier1->Identifier);
}
void NewExpressionWrapper::setCalleeBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->setCallee(_BooleanLiteral1->BooleanLiteral);
}
void NewExpressionWrapper::setCalleeNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->setCallee(_NullLiteral1->NullLiteral);
}
void NewExpressionWrapper::setCalleeNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->setCallee(_NumberLiteral1->NumberLiteral);
}
void NewExpressionWrapper::setCalleeRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->setCallee(_RegExpLiteral1->RegExpLiteral);
}
void NewExpressionWrapper::setCalleeStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->setCallee(_StringLiteral1->StringLiteral);
}
void NewExpressionWrapper::setCalleeLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->setCallee(_LogicalExpression1->LogicalExpression);
}
void NewExpressionWrapper::setCalleeMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->setCallee(_MemberExpression1->MemberExpression);
}
void NewExpressionWrapper::setCalleeMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->setCallee(_MetaProperty1->MetaProperty);
}
void NewExpressionWrapper::setCalleeNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->setCallee(_NewExpression1->NewExpression);
}
void NewExpressionWrapper::setCalleeObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->setCallee(_ObjectExpression1->ObjectExpression);
}
void NewExpressionWrapper::setCalleeSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->setCallee(_SequenceExpression1->SequenceExpression);
}
void NewExpressionWrapper::setCalleeTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->setCallee(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void NewExpressionWrapper::setCalleeTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->setCallee(_TemplateLiteral1->TemplateLiteral);
}
void NewExpressionWrapper::setCalleeThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->setCallee(_ThisExpression1->ThisExpression);
}
void NewExpressionWrapper::setCalleeUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->setCallee(_UnaryExpression1->UnaryExpression);
}
void NewExpressionWrapper::setCalleeUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->setCallee(_UpdateExpression1->UpdateExpression);
}
void NewExpressionWrapper::setCalleeYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->setCallee(_YieldExpression1->YieldExpression);
}
void NewExpressionWrapper::addArgumentsArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->addArguments(_ArrayExpression1->ArrayExpression);
}
void NewExpressionWrapper::addArgumentsArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->addArguments(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void NewExpressionWrapper::addArgumentsAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->addArguments(_AssignmentExpression1->AssignmentExpression);
}
void NewExpressionWrapper::addArgumentsAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->addArguments(_AwaitExpression1->AwaitExpression);
}
void NewExpressionWrapper::addArgumentsBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->addArguments(_BinaryExpression1->BinaryExpression);
}
void NewExpressionWrapper::addArgumentsCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->addArguments(_CallExpression1->CallExpression);
}
void NewExpressionWrapper::addArgumentsClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->addArguments(_ClassExpression1->ClassExpression);
}
void NewExpressionWrapper::addArgumentsConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->addArguments(_ConditionalExpression1->ConditionalExpression);
}
void NewExpressionWrapper::addArgumentsFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->addArguments(_FunctionExpression1->FunctionExpression);
}
void NewExpressionWrapper::addArgumentsIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->addArguments(_Identifier1->Identifier);
}
void NewExpressionWrapper::addArgumentsBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->addArguments(_BooleanLiteral1->BooleanLiteral);
}
void NewExpressionWrapper::addArgumentsNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->addArguments(_NullLiteral1->NullLiteral);
}
void NewExpressionWrapper::addArgumentsNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->addArguments(_NumberLiteral1->NumberLiteral);
}
void NewExpressionWrapper::addArgumentsRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->addArguments(_RegExpLiteral1->RegExpLiteral);
}
void NewExpressionWrapper::addArgumentsStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->addArguments(_StringLiteral1->StringLiteral);
}
void NewExpressionWrapper::addArgumentsLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->addArguments(_LogicalExpression1->LogicalExpression);
}
void NewExpressionWrapper::addArgumentsMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->addArguments(_MemberExpression1->MemberExpression);
}
void NewExpressionWrapper::addArgumentsMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->addArguments(_MetaProperty1->MetaProperty);
}
void NewExpressionWrapper::addArgumentsNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->addArguments(_NewExpression1->NewExpression);
}
void NewExpressionWrapper::addArgumentsObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->addArguments(_ObjectExpression1->ObjectExpression);
}
void NewExpressionWrapper::addArgumentsSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->addArguments(_SequenceExpression1->SequenceExpression);
}
void NewExpressionWrapper::addArgumentsTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->addArguments(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void NewExpressionWrapper::addArgumentsTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->addArguments(_TemplateLiteral1->TemplateLiteral);
}
void NewExpressionWrapper::addArgumentsThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->addArguments(_ThisExpression1->ThisExpression);
}
void NewExpressionWrapper::addArgumentsUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->addArguments(_UnaryExpression1->UnaryExpression);
}
void NewExpressionWrapper::addArgumentsUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->addArguments(_UpdateExpression1->UpdateExpression);
}
void NewExpressionWrapper::addArgumentsYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->addArguments(_YieldExpression1->YieldExpression);
}
void NewExpressionWrapper::addArgumentsSpreadElement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SpreadElementWrapper* _SpreadElement1 = ObjectWrap::Unwrap<SpreadElementWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->addArguments(_SpreadElement1->SpreadElement);
}
void NewExpressionWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  NewExpressionWrapper* _NewExpression2 = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());

  _NewExpression2->NewExpression->addComments(_Comment1->Comment);
}
void NewExpressionWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  NewExpressionWrapper* _NewExpression = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _NewExpression->NewExpression->getPosition();
  range.setPath( param );
  _NewExpression->NewExpression->setPosition( range );
}

void NewExpressionWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  NewExpressionWrapper* _NewExpression = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _NewExpression->NewExpression->getPosition();
  range.setLine( ui );
  _NewExpression->NewExpression->setPosition( range );
}

void NewExpressionWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  NewExpressionWrapper* _NewExpression = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _NewExpression->NewExpression->getPosition();
  range.setCol( ui );
  _NewExpression->NewExpression->setPosition( range );
}

void NewExpressionWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  NewExpressionWrapper* _NewExpression = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _NewExpression->NewExpression->getPosition();
  range.setEndLine( ui );
  _NewExpression->NewExpression->setPosition( range );
}

void NewExpressionWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  NewExpressionWrapper* _NewExpression = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _NewExpression->NewExpression->getPosition();
  range.setEndCol( ui );
  _NewExpression->NewExpression->setPosition( range );
}

void NewExpressionWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  NewExpressionWrapper* _NewExpression = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _NewExpression->NewExpression->getPosition();
  range.setWideLine( ui );
  _NewExpression->NewExpression->setPosition( range );
}

void NewExpressionWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  NewExpressionWrapper* _NewExpression = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _NewExpression->NewExpression->getPosition();
  range.setWideCol( ui );
  _NewExpression->NewExpression->setPosition( range );
}

void NewExpressionWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  NewExpressionWrapper* _NewExpression = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _NewExpression->NewExpression->getPosition();
  range.setWideEndLine( ui );
  _NewExpression->NewExpression->setPosition( range );
}

void NewExpressionWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  NewExpressionWrapper* _NewExpression = ObjectWrap::Unwrap<NewExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _NewExpression->NewExpression->getPosition();
  range.setWideEndCol( ui );
  _NewExpression->NewExpression->setPosition( range );
}

}}}} //end of namespaces