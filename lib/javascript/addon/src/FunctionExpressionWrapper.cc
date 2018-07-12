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

#include "../inc/FunctionExpressionWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> FunctionExpressionWrapper::constructor;

void FunctionExpressionWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "FunctionExpressionWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "addCommentsComment", addCommentsComment);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addParamsIdentifier", addParamsIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addParamsMemberExpression", addParamsMemberExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addParamsArrayPattern", addParamsArrayPattern);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addParamsAssignmentPattern", addParamsAssignmentPattern);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addParamsObjectPattern", addParamsObjectPattern);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addParamsRestElement", addParamsRestElement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyBlockStatement", setBodyBlockStatement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyArrayExpression", setBodyArrayExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyArrowFunctionExpression", setBodyArrowFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyAssignmentExpression", setBodyAssignmentExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyAwaitExpression", setBodyAwaitExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyBinaryExpression", setBodyBinaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyCallExpression", setBodyCallExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyClassExpression", setBodyClassExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyConditionalExpression", setBodyConditionalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyFunctionExpression", setBodyFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyIdentifier", setBodyIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyBooleanLiteral", setBodyBooleanLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyNullLiteral", setBodyNullLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyNumberLiteral", setBodyNumberLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyRegExpLiteral", setBodyRegExpLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyStringLiteral", setBodyStringLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyLogicalExpression", setBodyLogicalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyMemberExpression", setBodyMemberExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyMetaProperty", setBodyMetaProperty);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyNewExpression", setBodyNewExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyObjectExpression", setBodyObjectExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodySequenceExpression", setBodySequenceExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyTaggedTemplateExpression", setBodyTaggedTemplateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyTemplateLiteral", setBodyTemplateLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyThisExpression", setBodyThisExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyUnaryExpression", setBodyUnaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyUpdateExpression", setBodyUpdateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyYieldExpression", setBodyYieldExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setIdentifierIdentifier", setIdentifierIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setExpression", setExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPath", setPath);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLine", setLine);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setCol", setCol);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setEndLine", setEndLine);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setEndCol", setEndCol);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setWideLine", setWideLine);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setWideCol", setWideCol);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setWideEndLine", setWideEndLine);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setWideEndCol", setWideEndCol);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setGenerator", setGenerator);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAsync", setAsync);
                                                                           
  constructor.Reset(isolate, tpl->GetFunction());                          
  exports->Set(v8::String::NewFromUtf8(isolate, "FunctionExpressionWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void FunctionExpressionWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new FunctionExpressionWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    FunctionExpressionWrapper* obj = new FunctionExpressionWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `FunctionExpressionWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


FunctionExpressionWrapper::FunctionExpressionWrapper(Factory* fact)                        
{                                                   
  FunctionExpression = fact->getFactory()->createFunctionExpressionNode();          
}                                                   

FunctionExpressionWrapper::~FunctionExpressionWrapper()
{        
}        

void FunctionExpressionWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void FunctionExpressionWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->addComments(_Comment1->Comment);
}
void FunctionExpressionWrapper::addParamsIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->addParams(_Identifier1->Identifier);
}
void FunctionExpressionWrapper::addParamsMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->addParams(_MemberExpression1->MemberExpression);
}
void FunctionExpressionWrapper::addParamsArrayPattern(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayPatternWrapper* _ArrayPattern1 = ObjectWrap::Unwrap<ArrayPatternWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->addParams(_ArrayPattern1->ArrayPattern);
}
void FunctionExpressionWrapper::addParamsAssignmentPattern(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentPatternWrapper* _AssignmentPattern1 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->addParams(_AssignmentPattern1->AssignmentPattern);
}
void FunctionExpressionWrapper::addParamsObjectPattern(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectPatternWrapper* _ObjectPattern1 = ObjectWrap::Unwrap<ObjectPatternWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->addParams(_ObjectPattern1->ObjectPattern);
}
void FunctionExpressionWrapper::addParamsRestElement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RestElementWrapper* _RestElement1 = ObjectWrap::Unwrap<RestElementWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->addParams(_RestElement1->RestElement);
}
void FunctionExpressionWrapper::setBodyBlockStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BlockStatementWrapper* _BlockStatement1 = ObjectWrap::Unwrap<BlockStatementWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->setBody(_BlockStatement1->BlockStatement);
}
void FunctionExpressionWrapper::setBodyArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->setBody(_ArrayExpression1->ArrayExpression);
}
void FunctionExpressionWrapper::setBodyArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->setBody(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void FunctionExpressionWrapper::setBodyAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->setBody(_AssignmentExpression1->AssignmentExpression);
}
void FunctionExpressionWrapper::setBodyAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->setBody(_AwaitExpression1->AwaitExpression);
}
void FunctionExpressionWrapper::setBodyBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->setBody(_BinaryExpression1->BinaryExpression);
}
void FunctionExpressionWrapper::setBodyCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->setBody(_CallExpression1->CallExpression);
}
void FunctionExpressionWrapper::setBodyClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->setBody(_ClassExpression1->ClassExpression);
}
void FunctionExpressionWrapper::setBodyConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->setBody(_ConditionalExpression1->ConditionalExpression);
}
void FunctionExpressionWrapper::setBodyFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->setBody(_FunctionExpression1->FunctionExpression);
}
void FunctionExpressionWrapper::setBodyIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->setBody(_Identifier1->Identifier);
}
void FunctionExpressionWrapper::setBodyBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->setBody(_BooleanLiteral1->BooleanLiteral);
}
void FunctionExpressionWrapper::setBodyNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->setBody(_NullLiteral1->NullLiteral);
}
void FunctionExpressionWrapper::setBodyNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->setBody(_NumberLiteral1->NumberLiteral);
}
void FunctionExpressionWrapper::setBodyRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->setBody(_RegExpLiteral1->RegExpLiteral);
}
void FunctionExpressionWrapper::setBodyStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->setBody(_StringLiteral1->StringLiteral);
}
void FunctionExpressionWrapper::setBodyLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->setBody(_LogicalExpression1->LogicalExpression);
}
void FunctionExpressionWrapper::setBodyMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->setBody(_MemberExpression1->MemberExpression);
}
void FunctionExpressionWrapper::setBodyMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->setBody(_MetaProperty1->MetaProperty);
}
void FunctionExpressionWrapper::setBodyNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->setBody(_NewExpression1->NewExpression);
}
void FunctionExpressionWrapper::setBodyObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->setBody(_ObjectExpression1->ObjectExpression);
}
void FunctionExpressionWrapper::setBodySequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->setBody(_SequenceExpression1->SequenceExpression);
}
void FunctionExpressionWrapper::setBodyTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->setBody(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void FunctionExpressionWrapper::setBodyTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->setBody(_TemplateLiteral1->TemplateLiteral);
}
void FunctionExpressionWrapper::setBodyThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->setBody(_ThisExpression1->ThisExpression);
}
void FunctionExpressionWrapper::setBodyUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->setBody(_UnaryExpression1->UnaryExpression);
}
void FunctionExpressionWrapper::setBodyUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->setBody(_UpdateExpression1->UpdateExpression);
}
void FunctionExpressionWrapper::setBodyYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->setBody(_YieldExpression1->YieldExpression);
}
void FunctionExpressionWrapper::setIdentifierIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  FunctionExpressionWrapper* _FunctionExpression2 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());

  _FunctionExpression2->FunctionExpression->setIdentifier(_Identifier1->Identifier);
}
void FunctionExpressionWrapper::setExpression(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  FunctionExpressionWrapper* _FunctionExpression = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::transform(param.begin(), param.end(), param.begin(), ::tolower);
  std::istringstream is(param);                                    
  bool b;                                                        
  is >> std::boolalpha >> b;                                     
  _FunctionExpression->FunctionExpression->setExpression( b );
}
void FunctionExpressionWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  FunctionExpressionWrapper* _FunctionExpression = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _FunctionExpression->FunctionExpression->getPosition();
  range.setPath( param );
  _FunctionExpression->FunctionExpression->setPosition( range );
}

void FunctionExpressionWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  FunctionExpressionWrapper* _FunctionExpression = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _FunctionExpression->FunctionExpression->getPosition();
  range.setLine( ui );
  _FunctionExpression->FunctionExpression->setPosition( range );
}

void FunctionExpressionWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  FunctionExpressionWrapper* _FunctionExpression = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _FunctionExpression->FunctionExpression->getPosition();
  range.setCol( ui );
  _FunctionExpression->FunctionExpression->setPosition( range );
}

void FunctionExpressionWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  FunctionExpressionWrapper* _FunctionExpression = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _FunctionExpression->FunctionExpression->getPosition();
  range.setEndLine( ui );
  _FunctionExpression->FunctionExpression->setPosition( range );
}

void FunctionExpressionWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  FunctionExpressionWrapper* _FunctionExpression = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _FunctionExpression->FunctionExpression->getPosition();
  range.setEndCol( ui );
  _FunctionExpression->FunctionExpression->setPosition( range );
}

void FunctionExpressionWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  FunctionExpressionWrapper* _FunctionExpression = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _FunctionExpression->FunctionExpression->getPosition();
  range.setWideLine( ui );
  _FunctionExpression->FunctionExpression->setPosition( range );
}

void FunctionExpressionWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  FunctionExpressionWrapper* _FunctionExpression = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _FunctionExpression->FunctionExpression->getPosition();
  range.setWideCol( ui );
  _FunctionExpression->FunctionExpression->setPosition( range );
}

void FunctionExpressionWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  FunctionExpressionWrapper* _FunctionExpression = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _FunctionExpression->FunctionExpression->getPosition();
  range.setWideEndLine( ui );
  _FunctionExpression->FunctionExpression->setPosition( range );
}

void FunctionExpressionWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  FunctionExpressionWrapper* _FunctionExpression = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _FunctionExpression->FunctionExpression->getPosition();
  range.setWideEndCol( ui );
  _FunctionExpression->FunctionExpression->setPosition( range );
}

void FunctionExpressionWrapper::setGenerator(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  FunctionExpressionWrapper* _FunctionExpression = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::transform(param.begin(), param.end(), param.begin(), ::tolower);
  std::istringstream is(param);                                    
  bool b;                                                        
  is >> std::boolalpha >> b;                                     
  _FunctionExpression->FunctionExpression->setGenerator( b );
}
void FunctionExpressionWrapper::setAsync(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  FunctionExpressionWrapper* _FunctionExpression = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::transform(param.begin(), param.end(), param.begin(), ::tolower);
  std::istringstream is(param);                                    
  bool b;                                                        
  is >> std::boolalpha >> b;                                     
  _FunctionExpression->FunctionExpression->setAsync( b );
}
}}}} //end of namespaces