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

#include "../inc/ImportSpecifierWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> ImportSpecifierWrapper::constructor;

void ImportSpecifierWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "ImportSpecifierWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "setImportedIdentifier", setImportedIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLocalIdentifier", setLocalIdentifier);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "ImportSpecifierWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void ImportSpecifierWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new ImportSpecifierWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    ImportSpecifierWrapper* obj = new ImportSpecifierWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `ImportSpecifierWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


ImportSpecifierWrapper::ImportSpecifierWrapper(Factory* fact)                        
{                                                   
  ImportSpecifier = fact->getFactory()->createImportSpecifierNode();          
}                                                   

ImportSpecifierWrapper::~ImportSpecifierWrapper()
{        
}        

void ImportSpecifierWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void ImportSpecifierWrapper::setImportedIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  ImportSpecifierWrapper* _ImportSpecifier2 = ObjectWrap::Unwrap<ImportSpecifierWrapper>(args.This());

  _ImportSpecifier2->ImportSpecifier->setImported(_Identifier1->Identifier);
}
void ImportSpecifierWrapper::setLocalIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  ImportSpecifierWrapper* _ImportSpecifier2 = ObjectWrap::Unwrap<ImportSpecifierWrapper>(args.This());

  _ImportSpecifier2->ImportSpecifier->setLocal(_Identifier1->Identifier);
}
void ImportSpecifierWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  ImportSpecifierWrapper* _ImportSpecifier2 = ObjectWrap::Unwrap<ImportSpecifierWrapper>(args.This());

  _ImportSpecifier2->ImportSpecifier->addComments(_Comment1->Comment);
}
void ImportSpecifierWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  ImportSpecifierWrapper* _ImportSpecifier = ObjectWrap::Unwrap<ImportSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _ImportSpecifier->ImportSpecifier->getPosition();
  range.setPath( param );
  _ImportSpecifier->ImportSpecifier->setPosition( range );
}

void ImportSpecifierWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ImportSpecifierWrapper* _ImportSpecifier = ObjectWrap::Unwrap<ImportSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ImportSpecifier->ImportSpecifier->getPosition();
  range.setLine( ui );
  _ImportSpecifier->ImportSpecifier->setPosition( range );
}

void ImportSpecifierWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ImportSpecifierWrapper* _ImportSpecifier = ObjectWrap::Unwrap<ImportSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ImportSpecifier->ImportSpecifier->getPosition();
  range.setCol( ui );
  _ImportSpecifier->ImportSpecifier->setPosition( range );
}

void ImportSpecifierWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ImportSpecifierWrapper* _ImportSpecifier = ObjectWrap::Unwrap<ImportSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ImportSpecifier->ImportSpecifier->getPosition();
  range.setEndLine( ui );
  _ImportSpecifier->ImportSpecifier->setPosition( range );
}

void ImportSpecifierWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ImportSpecifierWrapper* _ImportSpecifier = ObjectWrap::Unwrap<ImportSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ImportSpecifier->ImportSpecifier->getPosition();
  range.setEndCol( ui );
  _ImportSpecifier->ImportSpecifier->setPosition( range );
}

void ImportSpecifierWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ImportSpecifierWrapper* _ImportSpecifier = ObjectWrap::Unwrap<ImportSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ImportSpecifier->ImportSpecifier->getPosition();
  range.setWideLine( ui );
  _ImportSpecifier->ImportSpecifier->setPosition( range );
}

void ImportSpecifierWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ImportSpecifierWrapper* _ImportSpecifier = ObjectWrap::Unwrap<ImportSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ImportSpecifier->ImportSpecifier->getPosition();
  range.setWideCol( ui );
  _ImportSpecifier->ImportSpecifier->setPosition( range );
}

void ImportSpecifierWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ImportSpecifierWrapper* _ImportSpecifier = ObjectWrap::Unwrap<ImportSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ImportSpecifier->ImportSpecifier->getPosition();
  range.setWideEndLine( ui );
  _ImportSpecifier->ImportSpecifier->setPosition( range );
}

void ImportSpecifierWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ImportSpecifierWrapper* _ImportSpecifier = ObjectWrap::Unwrap<ImportSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ImportSpecifier->ImportSpecifier->getPosition();
  range.setWideEndCol( ui );
  _ImportSpecifier->ImportSpecifier->setPosition( range );
}

}}}} //end of namespaces