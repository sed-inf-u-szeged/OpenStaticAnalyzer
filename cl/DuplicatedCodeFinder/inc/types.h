/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2017 Department of Software Engineering - University of Szeged
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

#ifndef DCF_TYPES_H
#define DCF_TYPES_H

#include "common.h"
#include "genealogy/inc/genealogy.h"

typedef columbus::NodeId NodeId;
typedef columbus::LANGUAGE_NAMESPACE::Factory Factory;
typedef columbus::LANGUAGE_NAMESPACE::NodeKind NodeKind;

typedef columbus::LANGUAGE_NAMESPACE::BASE_NAMESPACE::Base Base;

typedef columbus::LANGUAGE_NAMESPACE::BASE_NAMESPACE::Positioned Positioned;
typedef columbus::LANGUAGE_NAMESPACE::BASE_NAMESPACE::Named Named;

typedef columbus::LANGUAGE_NAMESPACE::AlgorithmPreorder AlgorithmPreorder;
typedef columbus::LANGUAGE_NAMESPACE::Visitor Visitor;
typedef columbus::LANGUAGE_NAMESPACE::VisitorAbstractNodes VisitorAbstractNodes;

#define LIM_FILTER_FILE_EXTENSION ".flim"
#define AlgorithmCommon columbus::LANGUAGE_NAMESPACE::Common

#if defined(SCHEMA_JAVA)
  #define FILTER_FILE_EXTENSION ".fjsi"
  #define FILTER_FILE_EXTENSION_W L".fjsi"
  #define LANGUAGE columbus::java::JavaLanguage
  #define LANGUAGE_NS columbus::java
  #define getUniqueName_v1 AlgorithmCommon::getUniqueNameForBase
  #define UNIQUE_NAME_FOR_MEMBER AlgorithmCommon::getUniqueNameForBase
  #define NAMED_VISITOR NamedVisitor

#elif defined(SCHEMA_PYTHON)
  #define FILTER_FILE_EXTENSION ".fpsi"
  #define FILTER_FILE_EXTENSION_W L".fpsi"
  #define LANGUAGE columbus::python::PythonLanguage
  #define LANGUAGE_NS columbus::python
  #define getUniqueName_v1 AlgorithmCommon::getUniqueNameForBase
  #define UNIQUE_NAME_FOR_MEMBER AlgorithmCommon::getUniqueName
  #define NAMED_VISITOR NamedVisitor

#endif

#endif

