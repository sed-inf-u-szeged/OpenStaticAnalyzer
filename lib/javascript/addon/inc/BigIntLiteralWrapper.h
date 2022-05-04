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

#ifndef _JAVASCRIPT_BigIntLiteralWrapper_H_
#define _JAVASCRIPT_BigIntLiteralWrapper_H_

#include "javascript/inc/javascript.h"
#include <node_api.h>
#include "BaseWrapper.h"
#include "../Factory.h"

namespace columbus { namespace javascript { namespace asg { namespace addon {
  class Factory;

  class BigIntLiteralWrapper : BaseWrapper{
    public:
      static napi_value Init(napi_env env, napi_value& exports);
      static void Destructor(napi_env env, void* nativeObject, void* finalize_hint);
      static napi_status NewInstance(napi_env env, expression::BigIntLiteral* arg, napi_value* instance);
    private:
      explicit BigIntLiteralWrapper(); // Constructor
      ~BigIntLiteralWrapper();
      static napi_ref constructor;
      static napi_value New(napi_env env, napi_callback_info info);
      napi_env env_;
      napi_ref wrapper_;
      static napi_value addComments(napi_env env, napi_callback_info info);
      static napi_value setBigint(napi_env env, napi_callback_info info);
      static napi_value setPath(napi_env env, napi_callback_info info);
      static napi_value setPosition(napi_env env, napi_callback_info info);
      static napi_value setRaw(napi_env env, napi_callback_info info);
  }; //end of BigIntLiteralWrapper

}}}}//end of namespaces
#endif