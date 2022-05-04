#include "../inc/LogicalExpressionWrapper.h"
#include <string>   
namespace columbus { namespace javascript { namespace asg { namespace addon {

napi_ref LogicalExpressionWrapper::constructor;

LogicalExpressionWrapper::LogicalExpressionWrapper(): env_(nullptr), wrapper_(nullptr) {}

LogicalExpressionWrapper::~LogicalExpressionWrapper(){ napi_delete_reference(env_, wrapper_); }

void LogicalExpressionWrapper::Destructor(napi_env env, void* nativeObject, void* ){
  LogicalExpressionWrapper* obj = reinterpret_cast<LogicalExpressionWrapper*>(nativeObject);
  //delete obj->_nativeObj;
  obj->~LogicalExpressionWrapper();
}
napi_value LogicalExpressionWrapper::Init(napi_env env, napi_value& exports) {
  napi_status status;
  napi_property_descriptor props [] = {
  DECLARE_NAPI_METHOD( "setLeft", setLeft),
  DECLARE_NAPI_METHOD( "setRight", setRight),
  DECLARE_NAPI_METHOD( "addComments", addComments),
    DECLARE_NAPI_METHOD("setOperator", setOperator),
    DECLARE_NAPI_METHOD("setPath", setPath),
    DECLARE_NAPI_METHOD("setPosition", setPosition),
  };

  napi_value cons;
  status = napi_define_class(env, "LogicalExpressionWrapper", NAPI_AUTO_LENGTH, New, nullptr, sizeof(props) / sizeof(*props), props, &cons );
  assert(status == napi_ok);

  status = napi_create_reference(env, cons, 1, &constructor);
  assert(status == napi_ok);

  return exports;
}
napi_value LogicalExpressionWrapper::New(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value jsthis;

  status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
  assert(status == napi_ok);

  LogicalExpressionWrapper* obj = new LogicalExpressionWrapper();
  obj->env_ = env;
  status = napi_wrap(env, jsthis, reinterpret_cast<void*>(obj), LogicalExpressionWrapper::Destructor, nullptr, &obj->wrapper_);
  assert(status == napi_ok);

  return jsthis;
}


napi_status LogicalExpressionWrapper::NewInstance(napi_env env, expression::LogicalExpression* arg, napi_value* instance) {

  napi_status status;
  napi_value cons;

  status = napi_get_reference_value(env, constructor, &cons);
  if(status != napi_ok) return status;

  status = napi_new_instance(env, cons, 0, nullptr, instance);
  if(status != napi_ok) return status;

  LogicalExpressionWrapper* obj;
  status = napi_unwrap(env, *instance, reinterpret_cast<void**>(&obj));
  obj->_nativeObj = arg;
  return napi_ok;
}

napi_value LogicalExpressionWrapper::setLeft(napi_env env, napi_callback_info info){
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

  LogicalExpressionWrapper* obj;
  BaseWrapper* param;
  status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
  assert(status == napi_ok);

  status = napi_unwrap(env, args[0], reinterpret_cast<void**>(&param));
  assert(status == napi_ok);

  columbus::javascript::asg::expression::LogicalExpression* source = dynamic_cast<columbus::javascript::asg::expression::LogicalExpression*>(obj->_nativeObj);
  columbus::javascript::asg::expression::Expression* target = dynamic_cast<columbus::javascript::asg::expression::Expression*>(param->_nativeObj);

  if(source == nullptr){
    status = napi_throw_error(env, nullptr, "Cannot cast expression::LogicalExpression" );
  }
  if(target == nullptr){
    status = napi_throw_error(env, nullptr, "Cannot cast expression::Expression" );
  }

  source->setLeft(target);
  return nullptr;
}
napi_value LogicalExpressionWrapper::setRight(napi_env env, napi_callback_info info){
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

  LogicalExpressionWrapper* obj;
  BaseWrapper* param;
  status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
  assert(status == napi_ok);

  status = napi_unwrap(env, args[0], reinterpret_cast<void**>(&param));
  assert(status == napi_ok);

  columbus::javascript::asg::expression::LogicalExpression* source = dynamic_cast<columbus::javascript::asg::expression::LogicalExpression*>(obj->_nativeObj);
  columbus::javascript::asg::expression::Expression* target = dynamic_cast<columbus::javascript::asg::expression::Expression*>(param->_nativeObj);

  if(source == nullptr){
    status = napi_throw_error(env, nullptr, "Cannot cast expression::LogicalExpression" );
  }
  if(target == nullptr){
    status = napi_throw_error(env, nullptr, "Cannot cast expression::Expression" );
  }

  source->setRight(target);
  return nullptr;
}
napi_value LogicalExpressionWrapper::addComments(napi_env env, napi_callback_info info){
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

  LogicalExpressionWrapper* obj;
  BaseWrapper* param;
  status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
  assert(status == napi_ok);

  status = napi_unwrap(env, args[0], reinterpret_cast<void**>(&param));
  assert(status == napi_ok);

  columbus::javascript::asg::expression::LogicalExpression* source = dynamic_cast<columbus::javascript::asg::expression::LogicalExpression*>(obj->_nativeObj);
  columbus::javascript::asg::base::Comment* target = dynamic_cast<columbus::javascript::asg::base::Comment*>(param->_nativeObj);

  if(source == nullptr){
    status = napi_throw_error(env, nullptr, "Cannot cast expression::LogicalExpression" );
  }
  if(target == nullptr){
    status = napi_throw_error(env, nullptr, "Cannot cast base::Comment" );
  }

  source->addComments(target);
  return nullptr;
}
napi_value LogicalExpressionWrapper::setOperator(napi_env env, napi_callback_info info){ 
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

  LogicalExpressionWrapper* obj;
  status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
  assert(status == napi_ok);

  napi_valuetype paramtype;
  status = napi_typeof(env, args[0], &paramtype);
  assert(status == napi_ok);

  if(paramtype != napi_string){
    napi_throw_type_error(env, nullptr, "Argument should be a string!"); 
    return nullptr;
  }

  char buffer[1024];
  size_t buffer_size = 1024, result_size = 0;
  status = napi_get_value_string_utf8(env, args[0], buffer, buffer_size, &result_size);
  assert(status == napi_ok);

  std::string param(buffer);

  if( param == "looAnd" ){
    dynamic_cast<columbus::javascript::asg::expression::LogicalExpression*>(obj->_nativeObj)->setOperator( looAnd );
  }
  if( param == "looOr" ){
    dynamic_cast<columbus::javascript::asg::expression::LogicalExpression*>(obj->_nativeObj)->setOperator( looOr );
  }
  if( param == "looNullishCoalescing" ){
    dynamic_cast<columbus::javascript::asg::expression::LogicalExpression*>(obj->_nativeObj)->setOperator( looNullishCoalescing );
  }
  return nullptr;
}
napi_value LogicalExpressionWrapper::setPath(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value jsthis;
  size_t argc = 1;
  napi_value args[1];
  status = napi_get_cb_info(env, info, &argc, args, &jsthis, nullptr);
  assert(status == napi_ok);

  if (argc != 1) {
    napi_throw_type_error(env, nullptr, "Wrong number of arguments");
    return nullptr;
  }

  LogicalExpressionWrapper* obj;
  napi_valuetype valuetype;
  status = napi_typeof(env, args[0], &valuetype);
  assert(status == napi_ok);

  if (valuetype != napi_string) {
    napi_throw_type_error(env, nullptr, "Argument should be a string!");
    return nullptr;
  }

  char buffer[1024];
  size_t buffer_size = 1024, result_size = 0;
  status = napi_get_value_string_utf8(env, args[0], buffer, buffer_size, &result_size);
  assert(status == napi_ok);

  std::string path(buffer);
  status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
  assert(status == napi_ok);

  Range range = dynamic_cast<columbus::javascript::asg::base::Positioned*>(obj->_nativeObj)->getPosition();
  range.setPath( path );
  dynamic_cast<columbus::javascript::asg::base::Positioned*>(obj->_nativeObj)->setPosition( range );
  return nullptr;
}


napi_value LogicalExpressionWrapper::setPosition(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value jsthis;
  size_t argc = 8;
  napi_value args[8];
  status = napi_get_cb_info(env, info, &argc, args, &jsthis, nullptr);
  assert(status == napi_ok);

  if (argc != 1 && argc != 8) {
    napi_throw_type_error(env, nullptr, "Wrong number of arguments. Use a simple object with the positions or pass 8 parameters: line, col, endline, endcol and their wide equivalents!");
    return nullptr;
  }

  LogicalExpressionWrapper* obj;
  napi_valuetype valuetype[8];
  int32_t position[8];
  bool hasProp[8];
  if(argc == 1){
    status = napi_typeof(env, args[0], &valuetype[0]);
    assert(status == napi_ok);

    if(valuetype[0] != napi_object){
      napi_throw_type_error(env, nullptr, "Argument should be an object!");
      return nullptr;
    }

    std::string props[] = {"line", "col", "endline", "endcol", "wideline", "widecol", "wideendline", "wideendcol",};

    for(int i = 0; i < 8; ++i){
      status = napi_has_named_property(env, args[0], props[i].c_str(), &hasProp[i]);
      assert(status == napi_ok);
      napi_value value;
      if(hasProp[i]){
        status = napi_get_named_property(env, args[0], props[i].c_str(), &value);
        assert(status == napi_ok);
        status = napi_get_value_int32(env, value, &position[i]);
        assert(status == napi_ok);
      }

    }
  }
  else{
    for(int i = 0; i < 8; ++i){
      status = napi_typeof(env, args[i], &valuetype[i]);
      assert(status == napi_ok);
      if(valuetype[i] != napi_number){
        napi_throw_type_error(env, nullptr, "Argument should be an integer!");
        return nullptr;
      }
      status = napi_get_value_int32(env, args[i], &position[i]);
      assert(status == napi_ok);
    }
    for(int i = 0; i < 8; ++i){
      hasProp[i] = true;
    }
  }
  status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
  assert(status == napi_ok);

  Range range = dynamic_cast<columbus::javascript::asg::base::Positioned*>(obj->_nativeObj)->getPosition();

  if(hasProp[0])
    range.setLine( (int)position[0] );
  if(hasProp[1])
    range.setCol( (int)position[1] );
  if(hasProp[2])
    range.setEndLine( (int)position[2] );
  if(hasProp[3])
    range.setEndCol( (int)position[3] );
  if(hasProp[4])
    range.setWideLine( (int)position[4] );
  if(hasProp[5])
    range.setWideCol( (int)position[5] );
  if(hasProp[6])
    range.setWideEndLine( (int)position[6] );
  if(hasProp[7])
    range.setWideEndCol( (int)position[7] );
  dynamic_cast<columbus::javascript::asg::base::Positioned*>(obj->_nativeObj)->setPosition( range );
  return nullptr;
}


}}}} //end of namespaces