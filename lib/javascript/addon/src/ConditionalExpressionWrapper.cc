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

#include "../inc/ConditionalExpressionWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> ConditionalExpressionWrapper::constructor;

void ConditionalExpressionWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "ConditionalExpressionWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateArrayExpression", setAlternateArrayExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateArrowFunctionExpression", setAlternateArrowFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateAssignmentExpression", setAlternateAssignmentExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateAwaitExpression", setAlternateAwaitExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateBinaryExpression", setAlternateBinaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateCallExpression", setAlternateCallExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateClassExpression", setAlternateClassExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateConditionalExpression", setAlternateConditionalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateFunctionExpression", setAlternateFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateIdentifier", setAlternateIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateBooleanLiteral", setAlternateBooleanLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateNullLiteral", setAlternateNullLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateNumberLiteral", setAlternateNumberLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateRegExpLiteral", setAlternateRegExpLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateStringLiteral", setAlternateStringLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateLogicalExpression", setAlternateLogicalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateMemberExpression", setAlternateMemberExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateMetaProperty", setAlternateMetaProperty);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateNewExpression", setAlternateNewExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateObjectExpression", setAlternateObjectExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateSequenceExpression", setAlternateSequenceExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateTaggedTemplateExpression", setAlternateTaggedTemplateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateTemplateLiteral", setAlternateTemplateLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateThisExpression", setAlternateThisExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateUnaryExpression", setAlternateUnaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateUpdateExpression", setAlternateUpdateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAlternateYieldExpression", setAlternateYieldExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentArrayExpression", setConsequentArrayExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentArrowFunctionExpression", setConsequentArrowFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentAssignmentExpression", setConsequentAssignmentExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentAwaitExpression", setConsequentAwaitExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentBinaryExpression", setConsequentBinaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentCallExpression", setConsequentCallExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentClassExpression", setConsequentClassExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentConditionalExpression", setConsequentConditionalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentFunctionExpression", setConsequentFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentIdentifier", setConsequentIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentBooleanLiteral", setConsequentBooleanLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentNullLiteral", setConsequentNullLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentNumberLiteral", setConsequentNumberLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentRegExpLiteral", setConsequentRegExpLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentStringLiteral", setConsequentStringLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentLogicalExpression", setConsequentLogicalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentMemberExpression", setConsequentMemberExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentMetaProperty", setConsequentMetaProperty);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentNewExpression", setConsequentNewExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentObjectExpression", setConsequentObjectExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentSequenceExpression", setConsequentSequenceExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentTaggedTemplateExpression", setConsequentTaggedTemplateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentTemplateLiteral", setConsequentTemplateLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentThisExpression", setConsequentThisExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentUnaryExpression", setConsequentUnaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentUpdateExpression", setConsequentUpdateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setConsequentYieldExpression", setConsequentYieldExpression);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "ConditionalExpressionWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void ConditionalExpressionWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new ConditionalExpressionWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    ConditionalExpressionWrapper* obj = new ConditionalExpressionWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `ConditionalExpressionWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


ConditionalExpressionWrapper::ConditionalExpressionWrapper(Factory* fact)                        
{                                                   
  ConditionalExpression = fact->getFactory()->createConditionalExpressionNode();          
}                                                   

ConditionalExpressionWrapper::~ConditionalExpressionWrapper()
{        
}        

void ConditionalExpressionWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void ConditionalExpressionWrapper::setAlternateArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setAlternate(_ArrayExpression1->ArrayExpression);
}
void ConditionalExpressionWrapper::setAlternateArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setAlternate(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void ConditionalExpressionWrapper::setAlternateAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setAlternate(_AssignmentExpression1->AssignmentExpression);
}
void ConditionalExpressionWrapper::setAlternateAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setAlternate(_AwaitExpression1->AwaitExpression);
}
void ConditionalExpressionWrapper::setAlternateBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setAlternate(_BinaryExpression1->BinaryExpression);
}
void ConditionalExpressionWrapper::setAlternateCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setAlternate(_CallExpression1->CallExpression);
}
void ConditionalExpressionWrapper::setAlternateClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setAlternate(_ClassExpression1->ClassExpression);
}
void ConditionalExpressionWrapper::setAlternateConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setAlternate(_ConditionalExpression1->ConditionalExpression);
}
void ConditionalExpressionWrapper::setAlternateFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setAlternate(_FunctionExpression1->FunctionExpression);
}
void ConditionalExpressionWrapper::setAlternateIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setAlternate(_Identifier1->Identifier);
}
void ConditionalExpressionWrapper::setAlternateBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setAlternate(_BooleanLiteral1->BooleanLiteral);
}
void ConditionalExpressionWrapper::setAlternateNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setAlternate(_NullLiteral1->NullLiteral);
}
void ConditionalExpressionWrapper::setAlternateNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setAlternate(_NumberLiteral1->NumberLiteral);
}
void ConditionalExpressionWrapper::setAlternateRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setAlternate(_RegExpLiteral1->RegExpLiteral);
}
void ConditionalExpressionWrapper::setAlternateStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setAlternate(_StringLiteral1->StringLiteral);
}
void ConditionalExpressionWrapper::setAlternateLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setAlternate(_LogicalExpression1->LogicalExpression);
}
void ConditionalExpressionWrapper::setAlternateMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setAlternate(_MemberExpression1->MemberExpression);
}
void ConditionalExpressionWrapper::setAlternateMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setAlternate(_MetaProperty1->MetaProperty);
}
void ConditionalExpressionWrapper::setAlternateNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setAlternate(_NewExpression1->NewExpression);
}
void ConditionalExpressionWrapper::setAlternateObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setAlternate(_ObjectExpression1->ObjectExpression);
}
void ConditionalExpressionWrapper::setAlternateSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setAlternate(_SequenceExpression1->SequenceExpression);
}
void ConditionalExpressionWrapper::setAlternateTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setAlternate(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void ConditionalExpressionWrapper::setAlternateTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setAlternate(_TemplateLiteral1->TemplateLiteral);
}
void ConditionalExpressionWrapper::setAlternateThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setAlternate(_ThisExpression1->ThisExpression);
}
void ConditionalExpressionWrapper::setAlternateUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setAlternate(_UnaryExpression1->UnaryExpression);
}
void ConditionalExpressionWrapper::setAlternateUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setAlternate(_UpdateExpression1->UpdateExpression);
}
void ConditionalExpressionWrapper::setAlternateYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setAlternate(_YieldExpression1->YieldExpression);
}
void ConditionalExpressionWrapper::setConsequentArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setConsequent(_ArrayExpression1->ArrayExpression);
}
void ConditionalExpressionWrapper::setConsequentArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setConsequent(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void ConditionalExpressionWrapper::setConsequentAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setConsequent(_AssignmentExpression1->AssignmentExpression);
}
void ConditionalExpressionWrapper::setConsequentAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setConsequent(_AwaitExpression1->AwaitExpression);
}
void ConditionalExpressionWrapper::setConsequentBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setConsequent(_BinaryExpression1->BinaryExpression);
}
void ConditionalExpressionWrapper::setConsequentCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setConsequent(_CallExpression1->CallExpression);
}
void ConditionalExpressionWrapper::setConsequentClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setConsequent(_ClassExpression1->ClassExpression);
}
void ConditionalExpressionWrapper::setConsequentConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setConsequent(_ConditionalExpression1->ConditionalExpression);
}
void ConditionalExpressionWrapper::setConsequentFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setConsequent(_FunctionExpression1->FunctionExpression);
}
void ConditionalExpressionWrapper::setConsequentIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setConsequent(_Identifier1->Identifier);
}
void ConditionalExpressionWrapper::setConsequentBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setConsequent(_BooleanLiteral1->BooleanLiteral);
}
void ConditionalExpressionWrapper::setConsequentNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setConsequent(_NullLiteral1->NullLiteral);
}
void ConditionalExpressionWrapper::setConsequentNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setConsequent(_NumberLiteral1->NumberLiteral);
}
void ConditionalExpressionWrapper::setConsequentRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setConsequent(_RegExpLiteral1->RegExpLiteral);
}
void ConditionalExpressionWrapper::setConsequentStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setConsequent(_StringLiteral1->StringLiteral);
}
void ConditionalExpressionWrapper::setConsequentLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setConsequent(_LogicalExpression1->LogicalExpression);
}
void ConditionalExpressionWrapper::setConsequentMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setConsequent(_MemberExpression1->MemberExpression);
}
void ConditionalExpressionWrapper::setConsequentMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setConsequent(_MetaProperty1->MetaProperty);
}
void ConditionalExpressionWrapper::setConsequentNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setConsequent(_NewExpression1->NewExpression);
}
void ConditionalExpressionWrapper::setConsequentObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setConsequent(_ObjectExpression1->ObjectExpression);
}
void ConditionalExpressionWrapper::setConsequentSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setConsequent(_SequenceExpression1->SequenceExpression);
}
void ConditionalExpressionWrapper::setConsequentTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setConsequent(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void ConditionalExpressionWrapper::setConsequentTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setConsequent(_TemplateLiteral1->TemplateLiteral);
}
void ConditionalExpressionWrapper::setConsequentThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setConsequent(_ThisExpression1->ThisExpression);
}
void ConditionalExpressionWrapper::setConsequentUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setConsequent(_UnaryExpression1->UnaryExpression);
}
void ConditionalExpressionWrapper::setConsequentUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setConsequent(_UpdateExpression1->UpdateExpression);
}
void ConditionalExpressionWrapper::setConsequentYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setConsequent(_YieldExpression1->YieldExpression);
}
void ConditionalExpressionWrapper::setTestArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setTest(_ArrayExpression1->ArrayExpression);
}
void ConditionalExpressionWrapper::setTestArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setTest(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void ConditionalExpressionWrapper::setTestAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setTest(_AssignmentExpression1->AssignmentExpression);
}
void ConditionalExpressionWrapper::setTestAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setTest(_AwaitExpression1->AwaitExpression);
}
void ConditionalExpressionWrapper::setTestBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setTest(_BinaryExpression1->BinaryExpression);
}
void ConditionalExpressionWrapper::setTestCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setTest(_CallExpression1->CallExpression);
}
void ConditionalExpressionWrapper::setTestClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setTest(_ClassExpression1->ClassExpression);
}
void ConditionalExpressionWrapper::setTestConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setTest(_ConditionalExpression1->ConditionalExpression);
}
void ConditionalExpressionWrapper::setTestFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setTest(_FunctionExpression1->FunctionExpression);
}
void ConditionalExpressionWrapper::setTestIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setTest(_Identifier1->Identifier);
}
void ConditionalExpressionWrapper::setTestBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setTest(_BooleanLiteral1->BooleanLiteral);
}
void ConditionalExpressionWrapper::setTestNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setTest(_NullLiteral1->NullLiteral);
}
void ConditionalExpressionWrapper::setTestNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setTest(_NumberLiteral1->NumberLiteral);
}
void ConditionalExpressionWrapper::setTestRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setTest(_RegExpLiteral1->RegExpLiteral);
}
void ConditionalExpressionWrapper::setTestStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setTest(_StringLiteral1->StringLiteral);
}
void ConditionalExpressionWrapper::setTestLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setTest(_LogicalExpression1->LogicalExpression);
}
void ConditionalExpressionWrapper::setTestMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setTest(_MemberExpression1->MemberExpression);
}
void ConditionalExpressionWrapper::setTestMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setTest(_MetaProperty1->MetaProperty);
}
void ConditionalExpressionWrapper::setTestNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setTest(_NewExpression1->NewExpression);
}
void ConditionalExpressionWrapper::setTestObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setTest(_ObjectExpression1->ObjectExpression);
}
void ConditionalExpressionWrapper::setTestSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setTest(_SequenceExpression1->SequenceExpression);
}
void ConditionalExpressionWrapper::setTestTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setTest(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void ConditionalExpressionWrapper::setTestTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setTest(_TemplateLiteral1->TemplateLiteral);
}
void ConditionalExpressionWrapper::setTestThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setTest(_ThisExpression1->ThisExpression);
}
void ConditionalExpressionWrapper::setTestUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setTest(_UnaryExpression1->UnaryExpression);
}
void ConditionalExpressionWrapper::setTestUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setTest(_UpdateExpression1->UpdateExpression);
}
void ConditionalExpressionWrapper::setTestYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->setTest(_YieldExpression1->YieldExpression);
}
void ConditionalExpressionWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  ConditionalExpressionWrapper* _ConditionalExpression2 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());

  _ConditionalExpression2->ConditionalExpression->addComments(_Comment1->Comment);
}
void ConditionalExpressionWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  ConditionalExpressionWrapper* _ConditionalExpression = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _ConditionalExpression->ConditionalExpression->getPosition();
  range.setPath( param );
  _ConditionalExpression->ConditionalExpression->setPosition( range );
}

void ConditionalExpressionWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ConditionalExpressionWrapper* _ConditionalExpression = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ConditionalExpression->ConditionalExpression->getPosition();
  range.setLine( ui );
  _ConditionalExpression->ConditionalExpression->setPosition( range );
}

void ConditionalExpressionWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ConditionalExpressionWrapper* _ConditionalExpression = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ConditionalExpression->ConditionalExpression->getPosition();
  range.setCol( ui );
  _ConditionalExpression->ConditionalExpression->setPosition( range );
}

void ConditionalExpressionWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ConditionalExpressionWrapper* _ConditionalExpression = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ConditionalExpression->ConditionalExpression->getPosition();
  range.setEndLine( ui );
  _ConditionalExpression->ConditionalExpression->setPosition( range );
}

void ConditionalExpressionWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ConditionalExpressionWrapper* _ConditionalExpression = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ConditionalExpression->ConditionalExpression->getPosition();
  range.setEndCol( ui );
  _ConditionalExpression->ConditionalExpression->setPosition( range );
}

void ConditionalExpressionWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ConditionalExpressionWrapper* _ConditionalExpression = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ConditionalExpression->ConditionalExpression->getPosition();
  range.setWideLine( ui );
  _ConditionalExpression->ConditionalExpression->setPosition( range );
}

void ConditionalExpressionWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ConditionalExpressionWrapper* _ConditionalExpression = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ConditionalExpression->ConditionalExpression->getPosition();
  range.setWideCol( ui );
  _ConditionalExpression->ConditionalExpression->setPosition( range );
}

void ConditionalExpressionWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ConditionalExpressionWrapper* _ConditionalExpression = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ConditionalExpression->ConditionalExpression->getPosition();
  range.setWideEndLine( ui );
  _ConditionalExpression->ConditionalExpression->setPosition( range );
}

void ConditionalExpressionWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ConditionalExpressionWrapper* _ConditionalExpression = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ConditionalExpression->ConditionalExpression->getPosition();
  range.setWideEndCol( ui );
  _ConditionalExpression->ConditionalExpression->setPosition( range );
}

}}}} //end of namespaces