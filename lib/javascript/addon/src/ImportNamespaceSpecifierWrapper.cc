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

#include "../inc/ImportNamespaceSpecifierWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> ImportNamespaceSpecifierWrapper::constructor;

void ImportNamespaceSpecifierWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "ImportNamespaceSpecifierWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
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
  exports->Set(v8::String::NewFromUtf8(isolate, "ImportNamespaceSpecifierWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void ImportNamespaceSpecifierWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new ImportNamespaceSpecifierWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    ImportNamespaceSpecifierWrapper* obj = new ImportNamespaceSpecifierWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `ImportNamespaceSpecifierWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


ImportNamespaceSpecifierWrapper::ImportNamespaceSpecifierWrapper(Factory* fact)                        
{                                                   
  ImportNamespaceSpecifier = fact->getFactory()->createImportNamespaceSpecifierNode();          
}                                                   

ImportNamespaceSpecifierWrapper::~ImportNamespaceSpecifierWrapper()
{        
}        

void ImportNamespaceSpecifierWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void ImportNamespaceSpecifierWrapper::setLocalIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  ImportNamespaceSpecifierWrapper* _ImportNamespaceSpecifier2 = ObjectWrap::Unwrap<ImportNamespaceSpecifierWrapper>(args.This());

  _ImportNamespaceSpecifier2->ImportNamespaceSpecifier->setLocal(_Identifier1->Identifier);
}
void ImportNamespaceSpecifierWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  ImportNamespaceSpecifierWrapper* _ImportNamespaceSpecifier2 = ObjectWrap::Unwrap<ImportNamespaceSpecifierWrapper>(args.This());

  _ImportNamespaceSpecifier2->ImportNamespaceSpecifier->addComments(_Comment1->Comment);
}
void ImportNamespaceSpecifierWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  ImportNamespaceSpecifierWrapper* _ImportNamespaceSpecifier = ObjectWrap::Unwrap<ImportNamespaceSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _ImportNamespaceSpecifier->ImportNamespaceSpecifier->getPosition();
  range.setPath( param );
  _ImportNamespaceSpecifier->ImportNamespaceSpecifier->setPosition( range );
}

void ImportNamespaceSpecifierWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ImportNamespaceSpecifierWrapper* _ImportNamespaceSpecifier = ObjectWrap::Unwrap<ImportNamespaceSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ImportNamespaceSpecifier->ImportNamespaceSpecifier->getPosition();
  range.setLine( ui );
  _ImportNamespaceSpecifier->ImportNamespaceSpecifier->setPosition( range );
}

void ImportNamespaceSpecifierWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ImportNamespaceSpecifierWrapper* _ImportNamespaceSpecifier = ObjectWrap::Unwrap<ImportNamespaceSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ImportNamespaceSpecifier->ImportNamespaceSpecifier->getPosition();
  range.setCol( ui );
  _ImportNamespaceSpecifier->ImportNamespaceSpecifier->setPosition( range );
}

void ImportNamespaceSpecifierWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ImportNamespaceSpecifierWrapper* _ImportNamespaceSpecifier = ObjectWrap::Unwrap<ImportNamespaceSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ImportNamespaceSpecifier->ImportNamespaceSpecifier->getPosition();
  range.setEndLine( ui );
  _ImportNamespaceSpecifier->ImportNamespaceSpecifier->setPosition( range );
}

void ImportNamespaceSpecifierWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ImportNamespaceSpecifierWrapper* _ImportNamespaceSpecifier = ObjectWrap::Unwrap<ImportNamespaceSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ImportNamespaceSpecifier->ImportNamespaceSpecifier->getPosition();
  range.setEndCol( ui );
  _ImportNamespaceSpecifier->ImportNamespaceSpecifier->setPosition( range );
}

void ImportNamespaceSpecifierWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ImportNamespaceSpecifierWrapper* _ImportNamespaceSpecifier = ObjectWrap::Unwrap<ImportNamespaceSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ImportNamespaceSpecifier->ImportNamespaceSpecifier->getPosition();
  range.setWideLine( ui );
  _ImportNamespaceSpecifier->ImportNamespaceSpecifier->setPosition( range );
}

void ImportNamespaceSpecifierWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ImportNamespaceSpecifierWrapper* _ImportNamespaceSpecifier = ObjectWrap::Unwrap<ImportNamespaceSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ImportNamespaceSpecifier->ImportNamespaceSpecifier->getPosition();
  range.setWideCol( ui );
  _ImportNamespaceSpecifier->ImportNamespaceSpecifier->setPosition( range );
}

void ImportNamespaceSpecifierWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ImportNamespaceSpecifierWrapper* _ImportNamespaceSpecifier = ObjectWrap::Unwrap<ImportNamespaceSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ImportNamespaceSpecifier->ImportNamespaceSpecifier->getPosition();
  range.setWideEndLine( ui );
  _ImportNamespaceSpecifier->ImportNamespaceSpecifier->setPosition( range );
}

void ImportNamespaceSpecifierWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ImportNamespaceSpecifierWrapper* _ImportNamespaceSpecifier = ObjectWrap::Unwrap<ImportNamespaceSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ImportNamespaceSpecifier->ImportNamespaceSpecifier->getPosition();
  range.setWideEndCol( ui );
  _ImportNamespaceSpecifier->ImportNamespaceSpecifier->setPosition( range );
}

}}}} //end of namespaces