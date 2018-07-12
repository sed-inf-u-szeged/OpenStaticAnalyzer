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

#include "../inc/VariableDeclaratorWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> VariableDeclaratorWrapper::constructor;

void VariableDeclaratorWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "VariableDeclaratorWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "setIdentifierIdentifier", setIdentifierIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setIdentifierMemberExpression", setIdentifierMemberExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setIdentifierArrayPattern", setIdentifierArrayPattern);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setIdentifierAssignmentPattern", setIdentifierAssignmentPattern);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setIdentifierObjectPattern", setIdentifierObjectPattern);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setIdentifierRestElement", setIdentifierRestElement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitArrayExpression", setInitArrayExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitArrowFunctionExpression", setInitArrowFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitAssignmentExpression", setInitAssignmentExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitAwaitExpression", setInitAwaitExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitBinaryExpression", setInitBinaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitCallExpression", setInitCallExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitClassExpression", setInitClassExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitConditionalExpression", setInitConditionalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitFunctionExpression", setInitFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitIdentifier", setInitIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitBooleanLiteral", setInitBooleanLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitNullLiteral", setInitNullLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitNumberLiteral", setInitNumberLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitRegExpLiteral", setInitRegExpLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitStringLiteral", setInitStringLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitLogicalExpression", setInitLogicalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitMemberExpression", setInitMemberExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitMetaProperty", setInitMetaProperty);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitNewExpression", setInitNewExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitObjectExpression", setInitObjectExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitSequenceExpression", setInitSequenceExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitTaggedTemplateExpression", setInitTaggedTemplateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitTemplateLiteral", setInitTemplateLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitThisExpression", setInitThisExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitUnaryExpression", setInitUnaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitUpdateExpression", setInitUpdateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setInitYieldExpression", setInitYieldExpression);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "VariableDeclaratorWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void VariableDeclaratorWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new VariableDeclaratorWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    VariableDeclaratorWrapper* obj = new VariableDeclaratorWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `VariableDeclaratorWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


VariableDeclaratorWrapper::VariableDeclaratorWrapper(Factory* fact)                        
{                                                   
  VariableDeclarator = fact->getFactory()->createVariableDeclaratorNode();          
}                                                   

VariableDeclaratorWrapper::~VariableDeclaratorWrapper()
{        
}        

void VariableDeclaratorWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void VariableDeclaratorWrapper::setIdentifierIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->setIdentifier(_Identifier1->Identifier);
}
void VariableDeclaratorWrapper::setIdentifierMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->setIdentifier(_MemberExpression1->MemberExpression);
}
void VariableDeclaratorWrapper::setIdentifierArrayPattern(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayPatternWrapper* _ArrayPattern1 = ObjectWrap::Unwrap<ArrayPatternWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->setIdentifier(_ArrayPattern1->ArrayPattern);
}
void VariableDeclaratorWrapper::setIdentifierAssignmentPattern(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentPatternWrapper* _AssignmentPattern1 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->setIdentifier(_AssignmentPattern1->AssignmentPattern);
}
void VariableDeclaratorWrapper::setIdentifierObjectPattern(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectPatternWrapper* _ObjectPattern1 = ObjectWrap::Unwrap<ObjectPatternWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->setIdentifier(_ObjectPattern1->ObjectPattern);
}
void VariableDeclaratorWrapper::setIdentifierRestElement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RestElementWrapper* _RestElement1 = ObjectWrap::Unwrap<RestElementWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->setIdentifier(_RestElement1->RestElement);
}
void VariableDeclaratorWrapper::setInitArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->setInit(_ArrayExpression1->ArrayExpression);
}
void VariableDeclaratorWrapper::setInitArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->setInit(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void VariableDeclaratorWrapper::setInitAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->setInit(_AssignmentExpression1->AssignmentExpression);
}
void VariableDeclaratorWrapper::setInitAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->setInit(_AwaitExpression1->AwaitExpression);
}
void VariableDeclaratorWrapper::setInitBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->setInit(_BinaryExpression1->BinaryExpression);
}
void VariableDeclaratorWrapper::setInitCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->setInit(_CallExpression1->CallExpression);
}
void VariableDeclaratorWrapper::setInitClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->setInit(_ClassExpression1->ClassExpression);
}
void VariableDeclaratorWrapper::setInitConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->setInit(_ConditionalExpression1->ConditionalExpression);
}
void VariableDeclaratorWrapper::setInitFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->setInit(_FunctionExpression1->FunctionExpression);
}
void VariableDeclaratorWrapper::setInitIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->setInit(_Identifier1->Identifier);
}
void VariableDeclaratorWrapper::setInitBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->setInit(_BooleanLiteral1->BooleanLiteral);
}
void VariableDeclaratorWrapper::setInitNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->setInit(_NullLiteral1->NullLiteral);
}
void VariableDeclaratorWrapper::setInitNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->setInit(_NumberLiteral1->NumberLiteral);
}
void VariableDeclaratorWrapper::setInitRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->setInit(_RegExpLiteral1->RegExpLiteral);
}
void VariableDeclaratorWrapper::setInitStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->setInit(_StringLiteral1->StringLiteral);
}
void VariableDeclaratorWrapper::setInitLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->setInit(_LogicalExpression1->LogicalExpression);
}
void VariableDeclaratorWrapper::setInitMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->setInit(_MemberExpression1->MemberExpression);
}
void VariableDeclaratorWrapper::setInitMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->setInit(_MetaProperty1->MetaProperty);
}
void VariableDeclaratorWrapper::setInitNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->setInit(_NewExpression1->NewExpression);
}
void VariableDeclaratorWrapper::setInitObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->setInit(_ObjectExpression1->ObjectExpression);
}
void VariableDeclaratorWrapper::setInitSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->setInit(_SequenceExpression1->SequenceExpression);
}
void VariableDeclaratorWrapper::setInitTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->setInit(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void VariableDeclaratorWrapper::setInitTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->setInit(_TemplateLiteral1->TemplateLiteral);
}
void VariableDeclaratorWrapper::setInitThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->setInit(_ThisExpression1->ThisExpression);
}
void VariableDeclaratorWrapper::setInitUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->setInit(_UnaryExpression1->UnaryExpression);
}
void VariableDeclaratorWrapper::setInitUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->setInit(_UpdateExpression1->UpdateExpression);
}
void VariableDeclaratorWrapper::setInitYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->setInit(_YieldExpression1->YieldExpression);
}
void VariableDeclaratorWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  VariableDeclaratorWrapper* _VariableDeclarator2 = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());

  _VariableDeclarator2->VariableDeclarator->addComments(_Comment1->Comment);
}
void VariableDeclaratorWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  VariableDeclaratorWrapper* _VariableDeclarator = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _VariableDeclarator->VariableDeclarator->getPosition();
  range.setPath( param );
  _VariableDeclarator->VariableDeclarator->setPosition( range );
}

void VariableDeclaratorWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  VariableDeclaratorWrapper* _VariableDeclarator = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _VariableDeclarator->VariableDeclarator->getPosition();
  range.setLine( ui );
  _VariableDeclarator->VariableDeclarator->setPosition( range );
}

void VariableDeclaratorWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  VariableDeclaratorWrapper* _VariableDeclarator = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _VariableDeclarator->VariableDeclarator->getPosition();
  range.setCol( ui );
  _VariableDeclarator->VariableDeclarator->setPosition( range );
}

void VariableDeclaratorWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  VariableDeclaratorWrapper* _VariableDeclarator = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _VariableDeclarator->VariableDeclarator->getPosition();
  range.setEndLine( ui );
  _VariableDeclarator->VariableDeclarator->setPosition( range );
}

void VariableDeclaratorWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  VariableDeclaratorWrapper* _VariableDeclarator = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _VariableDeclarator->VariableDeclarator->getPosition();
  range.setEndCol( ui );
  _VariableDeclarator->VariableDeclarator->setPosition( range );
}

void VariableDeclaratorWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  VariableDeclaratorWrapper* _VariableDeclarator = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _VariableDeclarator->VariableDeclarator->getPosition();
  range.setWideLine( ui );
  _VariableDeclarator->VariableDeclarator->setPosition( range );
}

void VariableDeclaratorWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  VariableDeclaratorWrapper* _VariableDeclarator = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _VariableDeclarator->VariableDeclarator->getPosition();
  range.setWideCol( ui );
  _VariableDeclarator->VariableDeclarator->setPosition( range );
}

void VariableDeclaratorWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  VariableDeclaratorWrapper* _VariableDeclarator = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _VariableDeclarator->VariableDeclarator->getPosition();
  range.setWideEndLine( ui );
  _VariableDeclarator->VariableDeclarator->setPosition( range );
}

void VariableDeclaratorWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  VariableDeclaratorWrapper* _VariableDeclarator = ObjectWrap::Unwrap<VariableDeclaratorWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _VariableDeclarator->VariableDeclarator->getPosition();
  range.setWideEndCol( ui );
  _VariableDeclarator->VariableDeclarator->setPosition( range );
}

}}}} //end of namespaces