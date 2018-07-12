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

#include "../inc/UnaryExpressionWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> UnaryExpressionWrapper::constructor;

void UnaryExpressionWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "UnaryExpressionWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentArrayExpression", setArgumentArrayExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentArrowFunctionExpression", setArgumentArrowFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentAssignmentExpression", setArgumentAssignmentExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentAwaitExpression", setArgumentAwaitExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentBinaryExpression", setArgumentBinaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentCallExpression", setArgumentCallExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentClassExpression", setArgumentClassExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentConditionalExpression", setArgumentConditionalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentFunctionExpression", setArgumentFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentIdentifier", setArgumentIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentBooleanLiteral", setArgumentBooleanLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentNullLiteral", setArgumentNullLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentNumberLiteral", setArgumentNumberLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentRegExpLiteral", setArgumentRegExpLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentStringLiteral", setArgumentStringLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentLogicalExpression", setArgumentLogicalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentMemberExpression", setArgumentMemberExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentMetaProperty", setArgumentMetaProperty);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentNewExpression", setArgumentNewExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentObjectExpression", setArgumentObjectExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentSequenceExpression", setArgumentSequenceExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentTaggedTemplateExpression", setArgumentTaggedTemplateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentTemplateLiteral", setArgumentTemplateLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentThisExpression", setArgumentThisExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentUnaryExpression", setArgumentUnaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentUpdateExpression", setArgumentUpdateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentYieldExpression", setArgumentYieldExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addCommentsComment", addCommentsComment);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setOperator", setOperator);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPrefix", setPrefix);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "UnaryExpressionWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void UnaryExpressionWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new UnaryExpressionWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    UnaryExpressionWrapper* obj = new UnaryExpressionWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `UnaryExpressionWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


UnaryExpressionWrapper::UnaryExpressionWrapper(Factory* fact)                        
{                                                   
  UnaryExpression = fact->getFactory()->createUnaryExpressionNode();          
}                                                   

UnaryExpressionWrapper::~UnaryExpressionWrapper()
{        
}        

void UnaryExpressionWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void UnaryExpressionWrapper::setArgumentArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  UnaryExpressionWrapper* _UnaryExpression2 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());

  _UnaryExpression2->UnaryExpression->setArgument(_ArrayExpression1->ArrayExpression);
}
void UnaryExpressionWrapper::setArgumentArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  UnaryExpressionWrapper* _UnaryExpression2 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());

  _UnaryExpression2->UnaryExpression->setArgument(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void UnaryExpressionWrapper::setArgumentAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  UnaryExpressionWrapper* _UnaryExpression2 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());

  _UnaryExpression2->UnaryExpression->setArgument(_AssignmentExpression1->AssignmentExpression);
}
void UnaryExpressionWrapper::setArgumentAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  UnaryExpressionWrapper* _UnaryExpression2 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());

  _UnaryExpression2->UnaryExpression->setArgument(_AwaitExpression1->AwaitExpression);
}
void UnaryExpressionWrapper::setArgumentBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  UnaryExpressionWrapper* _UnaryExpression2 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());

  _UnaryExpression2->UnaryExpression->setArgument(_BinaryExpression1->BinaryExpression);
}
void UnaryExpressionWrapper::setArgumentCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  UnaryExpressionWrapper* _UnaryExpression2 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());

  _UnaryExpression2->UnaryExpression->setArgument(_CallExpression1->CallExpression);
}
void UnaryExpressionWrapper::setArgumentClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  UnaryExpressionWrapper* _UnaryExpression2 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());

  _UnaryExpression2->UnaryExpression->setArgument(_ClassExpression1->ClassExpression);
}
void UnaryExpressionWrapper::setArgumentConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  UnaryExpressionWrapper* _UnaryExpression2 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());

  _UnaryExpression2->UnaryExpression->setArgument(_ConditionalExpression1->ConditionalExpression);
}
void UnaryExpressionWrapper::setArgumentFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  UnaryExpressionWrapper* _UnaryExpression2 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());

  _UnaryExpression2->UnaryExpression->setArgument(_FunctionExpression1->FunctionExpression);
}
void UnaryExpressionWrapper::setArgumentIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  UnaryExpressionWrapper* _UnaryExpression2 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());

  _UnaryExpression2->UnaryExpression->setArgument(_Identifier1->Identifier);
}
void UnaryExpressionWrapper::setArgumentBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  UnaryExpressionWrapper* _UnaryExpression2 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());

  _UnaryExpression2->UnaryExpression->setArgument(_BooleanLiteral1->BooleanLiteral);
}
void UnaryExpressionWrapper::setArgumentNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  UnaryExpressionWrapper* _UnaryExpression2 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());

  _UnaryExpression2->UnaryExpression->setArgument(_NullLiteral1->NullLiteral);
}
void UnaryExpressionWrapper::setArgumentNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  UnaryExpressionWrapper* _UnaryExpression2 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());

  _UnaryExpression2->UnaryExpression->setArgument(_NumberLiteral1->NumberLiteral);
}
void UnaryExpressionWrapper::setArgumentRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  UnaryExpressionWrapper* _UnaryExpression2 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());

  _UnaryExpression2->UnaryExpression->setArgument(_RegExpLiteral1->RegExpLiteral);
}
void UnaryExpressionWrapper::setArgumentStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  UnaryExpressionWrapper* _UnaryExpression2 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());

  _UnaryExpression2->UnaryExpression->setArgument(_StringLiteral1->StringLiteral);
}
void UnaryExpressionWrapper::setArgumentLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  UnaryExpressionWrapper* _UnaryExpression2 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());

  _UnaryExpression2->UnaryExpression->setArgument(_LogicalExpression1->LogicalExpression);
}
void UnaryExpressionWrapper::setArgumentMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  UnaryExpressionWrapper* _UnaryExpression2 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());

  _UnaryExpression2->UnaryExpression->setArgument(_MemberExpression1->MemberExpression);
}
void UnaryExpressionWrapper::setArgumentMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  UnaryExpressionWrapper* _UnaryExpression2 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());

  _UnaryExpression2->UnaryExpression->setArgument(_MetaProperty1->MetaProperty);
}
void UnaryExpressionWrapper::setArgumentNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  UnaryExpressionWrapper* _UnaryExpression2 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());

  _UnaryExpression2->UnaryExpression->setArgument(_NewExpression1->NewExpression);
}
void UnaryExpressionWrapper::setArgumentObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  UnaryExpressionWrapper* _UnaryExpression2 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());

  _UnaryExpression2->UnaryExpression->setArgument(_ObjectExpression1->ObjectExpression);
}
void UnaryExpressionWrapper::setArgumentSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  UnaryExpressionWrapper* _UnaryExpression2 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());

  _UnaryExpression2->UnaryExpression->setArgument(_SequenceExpression1->SequenceExpression);
}
void UnaryExpressionWrapper::setArgumentTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  UnaryExpressionWrapper* _UnaryExpression2 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());

  _UnaryExpression2->UnaryExpression->setArgument(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void UnaryExpressionWrapper::setArgumentTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  UnaryExpressionWrapper* _UnaryExpression2 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());

  _UnaryExpression2->UnaryExpression->setArgument(_TemplateLiteral1->TemplateLiteral);
}
void UnaryExpressionWrapper::setArgumentThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  UnaryExpressionWrapper* _UnaryExpression2 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());

  _UnaryExpression2->UnaryExpression->setArgument(_ThisExpression1->ThisExpression);
}
void UnaryExpressionWrapper::setArgumentUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  UnaryExpressionWrapper* _UnaryExpression2 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());

  _UnaryExpression2->UnaryExpression->setArgument(_UnaryExpression1->UnaryExpression);
}
void UnaryExpressionWrapper::setArgumentUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  UnaryExpressionWrapper* _UnaryExpression2 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());

  _UnaryExpression2->UnaryExpression->setArgument(_UpdateExpression1->UpdateExpression);
}
void UnaryExpressionWrapper::setArgumentYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  UnaryExpressionWrapper* _UnaryExpression2 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());

  _UnaryExpression2->UnaryExpression->setArgument(_YieldExpression1->YieldExpression);
}
void UnaryExpressionWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  UnaryExpressionWrapper* _UnaryExpression2 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());

  _UnaryExpression2->UnaryExpression->addComments(_Comment1->Comment);
}
void UnaryExpressionWrapper::setOperator(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  UnaryExpressionWrapper* _UnaryExpression = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  if( param == "unoMinus" ){
    _UnaryExpression->UnaryExpression->setOperator( unoMinus );
  }
  if( param == "unoPlus" ){
    _UnaryExpression->UnaryExpression->setOperator( unoPlus );
  }
  if( param == "unoNot" ){
    _UnaryExpression->UnaryExpression->setOperator( unoNot );
  }
  if( param == "unoTypeOf" ){
    _UnaryExpression->UnaryExpression->setOperator( unoTypeOf );
  }
  if( param == "unoVoid" ){
    _UnaryExpression->UnaryExpression->setOperator( unoVoid );
  }
  if( param == "unoDelete" ){
    _UnaryExpression->UnaryExpression->setOperator( unoDelete );
  }
  if( param == "unoBitwiseNot" ){
    _UnaryExpression->UnaryExpression->setOperator( unoBitwiseNot );
  }
}
void UnaryExpressionWrapper::setPrefix(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  UnaryExpressionWrapper* _UnaryExpression = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::transform(param.begin(), param.end(), param.begin(), ::tolower);
  std::istringstream is(param);                                    
  bool b;                                                        
  is >> std::boolalpha >> b;                                     
  _UnaryExpression->UnaryExpression->setPrefix( b );
}
void UnaryExpressionWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  UnaryExpressionWrapper* _UnaryExpression = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _UnaryExpression->UnaryExpression->getPosition();
  range.setPath( param );
  _UnaryExpression->UnaryExpression->setPosition( range );
}

void UnaryExpressionWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  UnaryExpressionWrapper* _UnaryExpression = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _UnaryExpression->UnaryExpression->getPosition();
  range.setLine( ui );
  _UnaryExpression->UnaryExpression->setPosition( range );
}

void UnaryExpressionWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  UnaryExpressionWrapper* _UnaryExpression = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _UnaryExpression->UnaryExpression->getPosition();
  range.setCol( ui );
  _UnaryExpression->UnaryExpression->setPosition( range );
}

void UnaryExpressionWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  UnaryExpressionWrapper* _UnaryExpression = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _UnaryExpression->UnaryExpression->getPosition();
  range.setEndLine( ui );
  _UnaryExpression->UnaryExpression->setPosition( range );
}

void UnaryExpressionWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  UnaryExpressionWrapper* _UnaryExpression = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _UnaryExpression->UnaryExpression->getPosition();
  range.setEndCol( ui );
  _UnaryExpression->UnaryExpression->setPosition( range );
}

void UnaryExpressionWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  UnaryExpressionWrapper* _UnaryExpression = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _UnaryExpression->UnaryExpression->getPosition();
  range.setWideLine( ui );
  _UnaryExpression->UnaryExpression->setPosition( range );
}

void UnaryExpressionWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  UnaryExpressionWrapper* _UnaryExpression = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _UnaryExpression->UnaryExpression->getPosition();
  range.setWideCol( ui );
  _UnaryExpression->UnaryExpression->setPosition( range );
}

void UnaryExpressionWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  UnaryExpressionWrapper* _UnaryExpression = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _UnaryExpression->UnaryExpression->getPosition();
  range.setWideEndLine( ui );
  _UnaryExpression->UnaryExpression->setPosition( range );
}

void UnaryExpressionWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  UnaryExpressionWrapper* _UnaryExpression = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _UnaryExpression->UnaryExpression->getPosition();
  range.setWideEndCol( ui );
  _UnaryExpression->UnaryExpression->setPosition( range );
}

}}}} //end of namespaces