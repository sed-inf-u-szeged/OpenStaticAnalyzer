#include "../inc/SystemWrapper.h"
#include <string>   
namespace columbus { namespace javascript { namespace asg { namespace addon {

napi_ref SystemWrapper::constructor;

SystemWrapper::SystemWrapper(): env_(nullptr), wrapper_(nullptr) {}

SystemWrapper::~SystemWrapper(){ napi_delete_reference(env_, wrapper_); }

void SystemWrapper::Destructor(napi_env env, void* nativeObject, void* ){
  SystemWrapper* obj = reinterpret_cast<SystemWrapper*>(nativeObject);
  //delete obj->_nativeObj;
  obj->~SystemWrapper();
}
napi_value SystemWrapper::Init(napi_env env, napi_value& exports) {
  napi_status status;
  napi_property_descriptor props [] = {
  DECLARE_NAPI_METHOD( "addPrograms", addPrograms),
  };

  napi_value cons;
  status = napi_define_class(env, "SystemWrapper", NAPI_AUTO_LENGTH, New, nullptr, sizeof(props) / sizeof(*props), props, &cons );
  assert(status == napi_ok);

  status = napi_create_reference(env, cons, 1, &constructor);
  assert(status == napi_ok);

  return exports;
}
napi_value SystemWrapper::New(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value jsthis;

  status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
  assert(status == napi_ok);

  SystemWrapper* obj = new SystemWrapper();
  obj->env_ = env;
  status = napi_wrap(env, jsthis, reinterpret_cast<void*>(obj), SystemWrapper::Destructor, nullptr, &obj->wrapper_);
  assert(status == napi_ok);

  return jsthis;
}


napi_status SystemWrapper::NewInstance(napi_env env, base::System* arg, napi_value* instance) {

  napi_status status;
  napi_value cons;

  status = napi_get_reference_value(env, constructor, &cons);
  if(status != napi_ok) return status;

  status = napi_new_instance(env, cons, 0, nullptr, instance);
  if(status != napi_ok) return status;

  SystemWrapper* obj;
  status = napi_unwrap(env, *instance, reinterpret_cast<void**>(&obj));
  obj->_nativeObj = arg;
  return napi_ok;
}

napi_value SystemWrapper::addPrograms(napi_env env, napi_callback_info info){
  napi_status status;
  napi_value jsthis;
  size_t argc = 1;
  napi_value args[1];
  status = napi_get_cb_info(env, info, &argc, args, &jsthis, nullptr);
  assert(status == napi_ok);

  if (argc != 1) {
    napi_throw_type_error(env, nullptr, "Wrong number of arguments.");
    return nullptr;
  }

  SystemWrapper* obj;
  BaseWrapper* param;
  status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
  assert(status == napi_ok);

  status = napi_unwrap(env, args[0], reinterpret_cast<void**>(&param));
  assert(status == napi_ok);

  columbus::javascript::asg::base::System* source = dynamic_cast<columbus::javascript::asg::base::System*>(obj->_nativeObj);
  columbus::javascript::asg::base::Program* target = dynamic_cast<columbus::javascript::asg::base::Program*>(param->_nativeObj);

  if(source == nullptr){
    status = napi_throw_error(env, nullptr, "Cannot cast base::System" );
  }
  if(target == nullptr){
    status = napi_throw_error(env, nullptr, "Cannot cast base::Program" );
  }

  source->addPrograms(target);
  return nullptr;
}
}}}} //end of namespaces