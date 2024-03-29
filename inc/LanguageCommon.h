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

#ifndef LANGUAGECOMMON_H
#define LANGUAGECOMMON_H


#define HAS_LANGUAGE_CONFIG

#ifdef SCHEMA_JAVA
  #define LANGUAGE_STR "Java"
#elif defined SCHEMA_JAVASCRIPT
  #define LANGUAGE_STR "JavaScript"
#elif defined SCHEMA_PYTHON
  #define LANGUAGE_STR "Python"
#elif defined SCHEMA_CSHARP
  #define LANGUAGE_STR "C#"
#else
  #define LANGUAGE_STR ""
  #undef HAS_LANGUAGE_CONFIG
#endif

#endif
