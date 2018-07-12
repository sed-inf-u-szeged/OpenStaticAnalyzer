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

#include "../inc/AssignmentPatternWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> AssignmentPatternWrapper::constructor;

void AssignmentPatternWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "AssignmentPatternWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftIdentifier", setLeftIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLeftMemberExpression", setLeftMemberExpression);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "AssignmentPatternWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void AssignmentPatternWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new AssignmentPatternWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    AssignmentPatternWrapper* obj = new AssignmentPatternWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `AssignmentPatternWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


AssignmentPatternWrapper::AssignmentPatternWrapper(Factory* fact)                        
{                                                   
  AssignmentPattern = fact->getFactory()->createAssignmentPatternNode();          
}                                                   

AssignmentPatternWrapper::~AssignmentPatternWrapper()
{        
}        

void AssignmentPatternWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void AssignmentPatternWrapper::setLeftIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->setLeft(_Identifier1->Identifier);
}
void AssignmentPatternWrapper::setLeftMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->setLeft(_MemberExpression1->MemberExpression);
}
void AssignmentPatternWrapper::setLeftArrayPattern(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayPatternWrapper* _ArrayPattern1 = ObjectWrap::Unwrap<ArrayPatternWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->setLeft(_ArrayPattern1->ArrayPattern);
}
void AssignmentPatternWrapper::setLeftAssignmentPattern(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentPatternWrapper* _AssignmentPattern1 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->setLeft(_AssignmentPattern1->AssignmentPattern);
}
void AssignmentPatternWrapper::setLeftObjectPattern(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectPatternWrapper* _ObjectPattern1 = ObjectWrap::Unwrap<ObjectPatternWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->setLeft(_ObjectPattern1->ObjectPattern);
}
void AssignmentPatternWrapper::setLeftRestElement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RestElementWrapper* _RestElement1 = ObjectWrap::Unwrap<RestElementWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->setLeft(_RestElement1->RestElement);
}
void AssignmentPatternWrapper::setRightArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->setRight(_ArrayExpression1->ArrayExpression);
}
void AssignmentPatternWrapper::setRightArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->setRight(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void AssignmentPatternWrapper::setRightAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->setRight(_AssignmentExpression1->AssignmentExpression);
}
void AssignmentPatternWrapper::setRightAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->setRight(_AwaitExpression1->AwaitExpression);
}
void AssignmentPatternWrapper::setRightBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->setRight(_BinaryExpression1->BinaryExpression);
}
void AssignmentPatternWrapper::setRightCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->setRight(_CallExpression1->CallExpression);
}
void AssignmentPatternWrapper::setRightClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->setRight(_ClassExpression1->ClassExpression);
}
void AssignmentPatternWrapper::setRightConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->setRight(_ConditionalExpression1->ConditionalExpression);
}
void AssignmentPatternWrapper::setRightFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->setRight(_FunctionExpression1->FunctionExpression);
}
void AssignmentPatternWrapper::setRightIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->setRight(_Identifier1->Identifier);
}
void AssignmentPatternWrapper::setRightBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->setRight(_BooleanLiteral1->BooleanLiteral);
}
void AssignmentPatternWrapper::setRightNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->setRight(_NullLiteral1->NullLiteral);
}
void AssignmentPatternWrapper::setRightNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->setRight(_NumberLiteral1->NumberLiteral);
}
void AssignmentPatternWrapper::setRightRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->setRight(_RegExpLiteral1->RegExpLiteral);
}
void AssignmentPatternWrapper::setRightStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->setRight(_StringLiteral1->StringLiteral);
}
void AssignmentPatternWrapper::setRightLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->setRight(_LogicalExpression1->LogicalExpression);
}
void AssignmentPatternWrapper::setRightMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->setRight(_MemberExpression1->MemberExpression);
}
void AssignmentPatternWrapper::setRightMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->setRight(_MetaProperty1->MetaProperty);
}
void AssignmentPatternWrapper::setRightNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->setRight(_NewExpression1->NewExpression);
}
void AssignmentPatternWrapper::setRightObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->setRight(_ObjectExpression1->ObjectExpression);
}
void AssignmentPatternWrapper::setRightSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->setRight(_SequenceExpression1->SequenceExpression);
}
void AssignmentPatternWrapper::setRightTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->setRight(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void AssignmentPatternWrapper::setRightTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->setRight(_TemplateLiteral1->TemplateLiteral);
}
void AssignmentPatternWrapper::setRightThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->setRight(_ThisExpression1->ThisExpression);
}
void AssignmentPatternWrapper::setRightUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->setRight(_UnaryExpression1->UnaryExpression);
}
void AssignmentPatternWrapper::setRightUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->setRight(_UpdateExpression1->UpdateExpression);
}
void AssignmentPatternWrapper::setRightYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->setRight(_YieldExpression1->YieldExpression);
}
void AssignmentPatternWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  AssignmentPatternWrapper* _AssignmentPattern2 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());

  _AssignmentPattern2->AssignmentPattern->addComments(_Comment1->Comment);
}
void AssignmentPatternWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  AssignmentPatternWrapper* _AssignmentPattern = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _AssignmentPattern->AssignmentPattern->getPosition();
  range.setPath( param );
  _AssignmentPattern->AssignmentPattern->setPosition( range );
}

void AssignmentPatternWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  AssignmentPatternWrapper* _AssignmentPattern = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _AssignmentPattern->AssignmentPattern->getPosition();
  range.setLine( ui );
  _AssignmentPattern->AssignmentPattern->setPosition( range );
}

void AssignmentPatternWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  AssignmentPatternWrapper* _AssignmentPattern = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _AssignmentPattern->AssignmentPattern->getPosition();
  range.setCol( ui );
  _AssignmentPattern->AssignmentPattern->setPosition( range );
}

void AssignmentPatternWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  AssignmentPatternWrapper* _AssignmentPattern = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _AssignmentPattern->AssignmentPattern->getPosition();
  range.setEndLine( ui );
  _AssignmentPattern->AssignmentPattern->setPosition( range );
}

void AssignmentPatternWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  AssignmentPatternWrapper* _AssignmentPattern = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _AssignmentPattern->AssignmentPattern->getPosition();
  range.setEndCol( ui );
  _AssignmentPattern->AssignmentPattern->setPosition( range );
}

void AssignmentPatternWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  AssignmentPatternWrapper* _AssignmentPattern = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _AssignmentPattern->AssignmentPattern->getPosition();
  range.setWideLine( ui );
  _AssignmentPattern->AssignmentPattern->setPosition( range );
}

void AssignmentPatternWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  AssignmentPatternWrapper* _AssignmentPattern = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _AssignmentPattern->AssignmentPattern->getPosition();
  range.setWideCol( ui );
  _AssignmentPattern->AssignmentPattern->setPosition( range );
}

void AssignmentPatternWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  AssignmentPatternWrapper* _AssignmentPattern = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _AssignmentPattern->AssignmentPattern->getPosition();
  range.setWideEndLine( ui );
  _AssignmentPattern->AssignmentPattern->setPosition( range );
}

void AssignmentPatternWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  AssignmentPatternWrapper* _AssignmentPattern = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _AssignmentPattern->AssignmentPattern->getPosition();
  range.setWideEndCol( ui );
  _AssignmentPattern->AssignmentPattern->setPosition( range );
}

}}}} //end of namespaces