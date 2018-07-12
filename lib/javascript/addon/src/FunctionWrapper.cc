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

#include "../inc/FunctionWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> FunctionWrapper::constructor;

void FunctionWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "FunctionWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
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
  NODE_SET_PROTOTYPE_METHOD(tpl, "addCommentsComment", addCommentsComment);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setGenerator", setGenerator);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setAsync", setAsync);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "FunctionWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void FunctionWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new FunctionWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    FunctionWrapper* obj = new FunctionWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `FunctionWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


FunctionWrapper::FunctionWrapper(Factory* fact)                        
{                                                   
  Function = fact->getFactory()->createFunctionNode();          
}                                                   

FunctionWrapper::~FunctionWrapper()
{        
}        

void FunctionWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void FunctionWrapper::addParamsIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->addParams(_Identifier1->Identifier);
}
void FunctionWrapper::addParamsMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->addParams(_MemberExpression1->MemberExpression);
}
void FunctionWrapper::addParamsArrayPattern(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayPatternWrapper* _ArrayPattern1 = ObjectWrap::Unwrap<ArrayPatternWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->addParams(_ArrayPattern1->ArrayPattern);
}
void FunctionWrapper::addParamsAssignmentPattern(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentPatternWrapper* _AssignmentPattern1 = ObjectWrap::Unwrap<AssignmentPatternWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->addParams(_AssignmentPattern1->AssignmentPattern);
}
void FunctionWrapper::addParamsObjectPattern(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectPatternWrapper* _ObjectPattern1 = ObjectWrap::Unwrap<ObjectPatternWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->addParams(_ObjectPattern1->ObjectPattern);
}
void FunctionWrapper::addParamsRestElement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RestElementWrapper* _RestElement1 = ObjectWrap::Unwrap<RestElementWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->addParams(_RestElement1->RestElement);
}
void FunctionWrapper::setBodyBlockStatement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BlockStatementWrapper* _BlockStatement1 = ObjectWrap::Unwrap<BlockStatementWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->setBody(_BlockStatement1->BlockStatement);
}
void FunctionWrapper::setBodyArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->setBody(_ArrayExpression1->ArrayExpression);
}
void FunctionWrapper::setBodyArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->setBody(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void FunctionWrapper::setBodyAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->setBody(_AssignmentExpression1->AssignmentExpression);
}
void FunctionWrapper::setBodyAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->setBody(_AwaitExpression1->AwaitExpression);
}
void FunctionWrapper::setBodyBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->setBody(_BinaryExpression1->BinaryExpression);
}
void FunctionWrapper::setBodyCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->setBody(_CallExpression1->CallExpression);
}
void FunctionWrapper::setBodyClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->setBody(_ClassExpression1->ClassExpression);
}
void FunctionWrapper::setBodyConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->setBody(_ConditionalExpression1->ConditionalExpression);
}
void FunctionWrapper::setBodyFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->setBody(_FunctionExpression1->FunctionExpression);
}
void FunctionWrapper::setBodyIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->setBody(_Identifier1->Identifier);
}
void FunctionWrapper::setBodyBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->setBody(_BooleanLiteral1->BooleanLiteral);
}
void FunctionWrapper::setBodyNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->setBody(_NullLiteral1->NullLiteral);
}
void FunctionWrapper::setBodyNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->setBody(_NumberLiteral1->NumberLiteral);
}
void FunctionWrapper::setBodyRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->setBody(_RegExpLiteral1->RegExpLiteral);
}
void FunctionWrapper::setBodyStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->setBody(_StringLiteral1->StringLiteral);
}
void FunctionWrapper::setBodyLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->setBody(_LogicalExpression1->LogicalExpression);
}
void FunctionWrapper::setBodyMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->setBody(_MemberExpression1->MemberExpression);
}
void FunctionWrapper::setBodyMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->setBody(_MetaProperty1->MetaProperty);
}
void FunctionWrapper::setBodyNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->setBody(_NewExpression1->NewExpression);
}
void FunctionWrapper::setBodyObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->setBody(_ObjectExpression1->ObjectExpression);
}
void FunctionWrapper::setBodySequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->setBody(_SequenceExpression1->SequenceExpression);
}
void FunctionWrapper::setBodyTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->setBody(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void FunctionWrapper::setBodyTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->setBody(_TemplateLiteral1->TemplateLiteral);
}
void FunctionWrapper::setBodyThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->setBody(_ThisExpression1->ThisExpression);
}
void FunctionWrapper::setBodyUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->setBody(_UnaryExpression1->UnaryExpression);
}
void FunctionWrapper::setBodyUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->setBody(_UpdateExpression1->UpdateExpression);
}
void FunctionWrapper::setBodyYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->setBody(_YieldExpression1->YieldExpression);
}
void FunctionWrapper::setIdentifierIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->setIdentifier(_Identifier1->Identifier);
}
void FunctionWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  FunctionWrapper* _Function2 = ObjectWrap::Unwrap<FunctionWrapper>(args.This());

  _Function2->Function->addComments(_Comment1->Comment);
}
void FunctionWrapper::setGenerator(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  FunctionWrapper* _Function = ObjectWrap::Unwrap<FunctionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::transform(param.begin(), param.end(), param.begin(), ::tolower);
  std::istringstream is(param);                                    
  bool b;                                                        
  is >> std::boolalpha >> b;                                     
  _Function->Function->setGenerator( b );
}
void FunctionWrapper::setAsync(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  FunctionWrapper* _Function = ObjectWrap::Unwrap<FunctionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::transform(param.begin(), param.end(), param.begin(), ::tolower);
  std::istringstream is(param);                                    
  bool b;                                                        
  is >> std::boolalpha >> b;                                     
  _Function->Function->setAsync( b );
}
void FunctionWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  FunctionWrapper* _Function = ObjectWrap::Unwrap<FunctionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _Function->Function->getPosition();
  range.setPath( param );
  _Function->Function->setPosition( range );
}

void FunctionWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  FunctionWrapper* _Function = ObjectWrap::Unwrap<FunctionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _Function->Function->getPosition();
  range.setLine( ui );
  _Function->Function->setPosition( range );
}

void FunctionWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  FunctionWrapper* _Function = ObjectWrap::Unwrap<FunctionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _Function->Function->getPosition();
  range.setCol( ui );
  _Function->Function->setPosition( range );
}

void FunctionWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  FunctionWrapper* _Function = ObjectWrap::Unwrap<FunctionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _Function->Function->getPosition();
  range.setEndLine( ui );
  _Function->Function->setPosition( range );
}

void FunctionWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  FunctionWrapper* _Function = ObjectWrap::Unwrap<FunctionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _Function->Function->getPosition();
  range.setEndCol( ui );
  _Function->Function->setPosition( range );
}

void FunctionWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  FunctionWrapper* _Function = ObjectWrap::Unwrap<FunctionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _Function->Function->getPosition();
  range.setWideLine( ui );
  _Function->Function->setPosition( range );
}

void FunctionWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  FunctionWrapper* _Function = ObjectWrap::Unwrap<FunctionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _Function->Function->getPosition();
  range.setWideCol( ui );
  _Function->Function->setPosition( range );
}

void FunctionWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  FunctionWrapper* _Function = ObjectWrap::Unwrap<FunctionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _Function->Function->getPosition();
  range.setWideEndLine( ui );
  _Function->Function->setPosition( range );
}

void FunctionWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  FunctionWrapper* _Function = ObjectWrap::Unwrap<FunctionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _Function->Function->getPosition();
  range.setWideEndCol( ui );
  _Function->Function->setPosition( range );
}

}}}} //end of namespaces