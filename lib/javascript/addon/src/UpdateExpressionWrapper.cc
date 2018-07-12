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

#include "../inc/UpdateExpressionWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> UpdateExpressionWrapper::constructor;

void UpdateExpressionWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "UpdateExpressionWrapper"));             
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
  exports->Set(v8::String::NewFromUtf8(isolate, "UpdateExpressionWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void UpdateExpressionWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new UpdateExpressionWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    UpdateExpressionWrapper* obj = new UpdateExpressionWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `UpdateExpressionWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


UpdateExpressionWrapper::UpdateExpressionWrapper(Factory* fact)                        
{                                                   
  UpdateExpression = fact->getFactory()->createUpdateExpressionNode();          
}                                                   

UpdateExpressionWrapper::~UpdateExpressionWrapper()
{        
}        

void UpdateExpressionWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void UpdateExpressionWrapper::setArgumentArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  UpdateExpressionWrapper* _UpdateExpression2 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());

  _UpdateExpression2->UpdateExpression->setArgument(_ArrayExpression1->ArrayExpression);
}
void UpdateExpressionWrapper::setArgumentArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  UpdateExpressionWrapper* _UpdateExpression2 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());

  _UpdateExpression2->UpdateExpression->setArgument(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void UpdateExpressionWrapper::setArgumentAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  UpdateExpressionWrapper* _UpdateExpression2 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());

  _UpdateExpression2->UpdateExpression->setArgument(_AssignmentExpression1->AssignmentExpression);
}
void UpdateExpressionWrapper::setArgumentAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  UpdateExpressionWrapper* _UpdateExpression2 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());

  _UpdateExpression2->UpdateExpression->setArgument(_AwaitExpression1->AwaitExpression);
}
void UpdateExpressionWrapper::setArgumentBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  UpdateExpressionWrapper* _UpdateExpression2 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());

  _UpdateExpression2->UpdateExpression->setArgument(_BinaryExpression1->BinaryExpression);
}
void UpdateExpressionWrapper::setArgumentCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  UpdateExpressionWrapper* _UpdateExpression2 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());

  _UpdateExpression2->UpdateExpression->setArgument(_CallExpression1->CallExpression);
}
void UpdateExpressionWrapper::setArgumentClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  UpdateExpressionWrapper* _UpdateExpression2 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());

  _UpdateExpression2->UpdateExpression->setArgument(_ClassExpression1->ClassExpression);
}
void UpdateExpressionWrapper::setArgumentConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  UpdateExpressionWrapper* _UpdateExpression2 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());

  _UpdateExpression2->UpdateExpression->setArgument(_ConditionalExpression1->ConditionalExpression);
}
void UpdateExpressionWrapper::setArgumentFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  UpdateExpressionWrapper* _UpdateExpression2 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());

  _UpdateExpression2->UpdateExpression->setArgument(_FunctionExpression1->FunctionExpression);
}
void UpdateExpressionWrapper::setArgumentIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  UpdateExpressionWrapper* _UpdateExpression2 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());

  _UpdateExpression2->UpdateExpression->setArgument(_Identifier1->Identifier);
}
void UpdateExpressionWrapper::setArgumentBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  UpdateExpressionWrapper* _UpdateExpression2 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());

  _UpdateExpression2->UpdateExpression->setArgument(_BooleanLiteral1->BooleanLiteral);
}
void UpdateExpressionWrapper::setArgumentNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  UpdateExpressionWrapper* _UpdateExpression2 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());

  _UpdateExpression2->UpdateExpression->setArgument(_NullLiteral1->NullLiteral);
}
void UpdateExpressionWrapper::setArgumentNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  UpdateExpressionWrapper* _UpdateExpression2 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());

  _UpdateExpression2->UpdateExpression->setArgument(_NumberLiteral1->NumberLiteral);
}
void UpdateExpressionWrapper::setArgumentRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  UpdateExpressionWrapper* _UpdateExpression2 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());

  _UpdateExpression2->UpdateExpression->setArgument(_RegExpLiteral1->RegExpLiteral);
}
void UpdateExpressionWrapper::setArgumentStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  UpdateExpressionWrapper* _UpdateExpression2 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());

  _UpdateExpression2->UpdateExpression->setArgument(_StringLiteral1->StringLiteral);
}
void UpdateExpressionWrapper::setArgumentLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  UpdateExpressionWrapper* _UpdateExpression2 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());

  _UpdateExpression2->UpdateExpression->setArgument(_LogicalExpression1->LogicalExpression);
}
void UpdateExpressionWrapper::setArgumentMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  UpdateExpressionWrapper* _UpdateExpression2 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());

  _UpdateExpression2->UpdateExpression->setArgument(_MemberExpression1->MemberExpression);
}
void UpdateExpressionWrapper::setArgumentMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  UpdateExpressionWrapper* _UpdateExpression2 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());

  _UpdateExpression2->UpdateExpression->setArgument(_MetaProperty1->MetaProperty);
}
void UpdateExpressionWrapper::setArgumentNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  UpdateExpressionWrapper* _UpdateExpression2 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());

  _UpdateExpression2->UpdateExpression->setArgument(_NewExpression1->NewExpression);
}
void UpdateExpressionWrapper::setArgumentObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  UpdateExpressionWrapper* _UpdateExpression2 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());

  _UpdateExpression2->UpdateExpression->setArgument(_ObjectExpression1->ObjectExpression);
}
void UpdateExpressionWrapper::setArgumentSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  UpdateExpressionWrapper* _UpdateExpression2 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());

  _UpdateExpression2->UpdateExpression->setArgument(_SequenceExpression1->SequenceExpression);
}
void UpdateExpressionWrapper::setArgumentTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  UpdateExpressionWrapper* _UpdateExpression2 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());

  _UpdateExpression2->UpdateExpression->setArgument(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void UpdateExpressionWrapper::setArgumentTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  UpdateExpressionWrapper* _UpdateExpression2 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());

  _UpdateExpression2->UpdateExpression->setArgument(_TemplateLiteral1->TemplateLiteral);
}
void UpdateExpressionWrapper::setArgumentThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  UpdateExpressionWrapper* _UpdateExpression2 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());

  _UpdateExpression2->UpdateExpression->setArgument(_ThisExpression1->ThisExpression);
}
void UpdateExpressionWrapper::setArgumentUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  UpdateExpressionWrapper* _UpdateExpression2 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());

  _UpdateExpression2->UpdateExpression->setArgument(_UnaryExpression1->UnaryExpression);
}
void UpdateExpressionWrapper::setArgumentUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  UpdateExpressionWrapper* _UpdateExpression2 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());

  _UpdateExpression2->UpdateExpression->setArgument(_UpdateExpression1->UpdateExpression);
}
void UpdateExpressionWrapper::setArgumentYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  UpdateExpressionWrapper* _UpdateExpression2 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());

  _UpdateExpression2->UpdateExpression->setArgument(_YieldExpression1->YieldExpression);
}
void UpdateExpressionWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  UpdateExpressionWrapper* _UpdateExpression2 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());

  _UpdateExpression2->UpdateExpression->addComments(_Comment1->Comment);
}
void UpdateExpressionWrapper::setOperator(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  UpdateExpressionWrapper* _UpdateExpression = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  if( param == "upoIncrement" ){
    _UpdateExpression->UpdateExpression->setOperator( upoIncrement );
  }
  if( param == "upoDecrement" ){
    _UpdateExpression->UpdateExpression->setOperator( upoDecrement );
  }
}
void UpdateExpressionWrapper::setPrefix(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  UpdateExpressionWrapper* _UpdateExpression = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::transform(param.begin(), param.end(), param.begin(), ::tolower);
  std::istringstream is(param);                                    
  bool b;                                                        
  is >> std::boolalpha >> b;                                     
  _UpdateExpression->UpdateExpression->setPrefix( b );
}
void UpdateExpressionWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  UpdateExpressionWrapper* _UpdateExpression = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _UpdateExpression->UpdateExpression->getPosition();
  range.setPath( param );
  _UpdateExpression->UpdateExpression->setPosition( range );
}

void UpdateExpressionWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  UpdateExpressionWrapper* _UpdateExpression = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _UpdateExpression->UpdateExpression->getPosition();
  range.setLine( ui );
  _UpdateExpression->UpdateExpression->setPosition( range );
}

void UpdateExpressionWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  UpdateExpressionWrapper* _UpdateExpression = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _UpdateExpression->UpdateExpression->getPosition();
  range.setCol( ui );
  _UpdateExpression->UpdateExpression->setPosition( range );
}

void UpdateExpressionWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  UpdateExpressionWrapper* _UpdateExpression = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _UpdateExpression->UpdateExpression->getPosition();
  range.setEndLine( ui );
  _UpdateExpression->UpdateExpression->setPosition( range );
}

void UpdateExpressionWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  UpdateExpressionWrapper* _UpdateExpression = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _UpdateExpression->UpdateExpression->getPosition();
  range.setEndCol( ui );
  _UpdateExpression->UpdateExpression->setPosition( range );
}

void UpdateExpressionWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  UpdateExpressionWrapper* _UpdateExpression = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _UpdateExpression->UpdateExpression->getPosition();
  range.setWideLine( ui );
  _UpdateExpression->UpdateExpression->setPosition( range );
}

void UpdateExpressionWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  UpdateExpressionWrapper* _UpdateExpression = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _UpdateExpression->UpdateExpression->getPosition();
  range.setWideCol( ui );
  _UpdateExpression->UpdateExpression->setPosition( range );
}

void UpdateExpressionWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  UpdateExpressionWrapper* _UpdateExpression = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _UpdateExpression->UpdateExpression->getPosition();
  range.setWideEndLine( ui );
  _UpdateExpression->UpdateExpression->setPosition( range );
}

void UpdateExpressionWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  UpdateExpressionWrapper* _UpdateExpression = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _UpdateExpression->UpdateExpression->getPosition();
  range.setWideEndCol( ui );
  _UpdateExpression->UpdateExpression->setPosition( range );
}

}}}} //end of namespaces