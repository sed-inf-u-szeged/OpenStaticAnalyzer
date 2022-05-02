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


#ifndef _GRAPH_CONSTANTS_H_
#define _GRAPH_CONSTANTS_H_

#include <string>

namespace columbus { 
  namespace graphsupport { 

    namespace graphconstants {

      // Context constants
      extern const std::string CONTEXT_WARNING;
      extern const std::string CONTEXT_METRIC;
      extern const std::string CONTEXT_METRICGROUP;
      extern const std::string CONTEXT_ATTRIBUTE;
      extern const std::string CONTEXT_RUL;
      extern const std::string CONTEXT_TRACE;
      
      // Attribute name constants
      extern const std::string ATTR_WARNINGTEXT;
      extern const std::string ATTR_POSITION;
      extern const std::string ATTR_NAME;
      extern const std::string ATTR_LONGNAME;
      extern const std::string ATTR_PATH;
      extern const std::string ATTR_LINE;
      extern const std::string ATTR_COLUMN;
      extern const std::string ATTR_ENDLINE;
      extern const std::string ATTR_ENDCOLUMN;  
      extern const std::string ATTR_REALIZATIONLEVEL;  
      extern const std::string ATTR_ANONYMOUS;
      extern const std::string ATTR_SPOOLFILE;
      extern const std::string ATTR_CHANGESETID;
      extern const std::string ATTR_ANALYSISTIME;
      extern const std::string ATTR_DEPENDENCYTYPE;

      extern const std::string ATTR_RUL_DESCRIPTION;
      extern const std::string ATTR_RUL_DISPLAYNAME;
      extern const std::string ATTR_RUL_ENABLED;
      extern const std::string ATTR_RUL_GROUPTYPE;
      extern const std::string ATTR_RUL_HELPTEXT;
      extern const std::string ATTR_RUL_SETTINGS;
      extern const std::string ATTR_RUL_PRIORITY;
      extern const std::string ATTR_RUL_WARNING;
      extern const std::string ATTR_RUL_CALCULATED;
      extern const std::string ATTR_RUL_CALCULATEDFOR;
      extern const std::string ATTR_RUL_TAGS;
      extern const std::string ATTR_RUL_TAG;
      extern const std::string ATTR_RUL_TAG_METADATA_URL;
      extern const std::string ATTR_RUL_TAG_METADATA_DESCRIPTION;
      extern const std::string ATTR_RUL_TAG_METADATA_SUMMARIZED;
      extern const std::string ATTR_RUL_TAG_METADATA_SUMMARIZED_TRUE;
      extern const std::string ATTR_RUL_TAG_METADATA_SUMMARIZED_FALSE;
      
      extern const std::string ATTR_DCF_CLONESMELLTYPE;
      
      extern const std::string ATTR_UUID;
      extern const std::string ATTR_TUID;
      
      extern const std::string ATTR_EXTRAINFO;
      extern const std::string ATTR_SOURCELINK;
      extern const std::string ATTR_CALLSTACKDEPTH;
      extern const std::string ATTR_SL_TEXT;
            
      // Node type constants
      extern const std::string NTYPE_ROOT;

      extern const std::string NTYPE_RUL_METRIC;
      extern const std::string NTYPE_RUL_TOOL;
      extern const std::string NTYPE_RUL_TREE_NODE;
      extern const std::string NTYPE_RUL_METADATA;

      extern const std::string NTYPE_LIM_COMPONENT;
      extern const std::string NTYPE_LIM_MODULE;
      extern const std::string NTYPE_LIM_NAMESPACE;
      extern const std::string NTYPE_LIM_PACKAGE;
      extern const std::string NTYPE_LIM_ROOT;
      extern const std::string NTYPE_LIM_CLASS;
      extern const std::string NTYPE_LIM_STRUCTURE;
      extern const std::string NTYPE_LIM_DELEGATE;
      extern const std::string NTYPE_LIM_UNION;
      extern const std::string NTYPE_LIM_INTERFACE;
      extern const std::string NTYPE_LIM_ENUM;
      extern const std::string NTYPE_LIM_ANNOTATION;
      extern const std::string NTYPE_LIM_SOURCEFILE;
      extern const std::string NTYPE_LIM_CLASSDEF;
      extern const std::string NTYPE_LIM_FUNCTION;
      extern const std::string NTYPE_LIM_METHOD;
      extern const std::string NTYPE_LIM_FUNCTIONMEMBER;
      extern const std::string NTYPE_LIM_PROCEDURE;
      extern const std::string NTYPE_LIM_FUNCTIONDEF;
      extern const std::string NTYPE_LIM_METHODDEF;
      extern const std::string NTYPE_LIM_ATTRIBUTE;
      extern const std::string NTYPE_LIM_FILESYSTEM;
      extern const std::string NTYPE_LIM_FOLDER;
      extern const std::string NTYPE_LIM_FILE;

      extern const std::string NTYPE_DCF_CLONECLASS;
      extern const std::string NTYPE_DCF_CLONEINSTANCE;

      extern const std::string NTYPE_RPG_SYSTEM;
      extern const std::string NTYPE_RPG_PROGRAM;
      extern const std::string NTYPE_RPG_MODULE;
      extern const std::string NTYPE_RPG_PROCEDURE;
      extern const std::string NTYPE_RPG_SUBROUTINE;
      
      // Edge type constants
      extern const std::string ETYPE_RUL_GROUPCONTAINS;
      extern const std::string ETYPE_RUL_TREE;

      extern const std::string ETYPE_LIM_LOGICALTREE;
      extern const std::string ETYPE_LIM_PHYSICALTREE;
      extern const std::string ETYPE_LIM_COMPONENT;
      extern const std::string ETYPE_LIM_COMPONENTTREE;
      extern const std::string ETYPE_LIM_VARIANT;
      extern const std::string ETYPE_LIM_AGGREGATED;
      extern const std::string ETYPE_LIM_INSTANCE;
      extern const std::string ETYPE_LIM_DECLARES;
      extern const std::string ETYPE_LIM_DEPENDSON;

      extern const std::string ETYPE_DCF_CLONETREE;
      extern const std::string ETYPE_DCF_HASCLONE;
            
      // Attribute value constants 
      extern const std::string ATTRVALUE_INVALID;

      extern const std::string ATTRVALUE_LIM_RELDECLARES;
      extern const std::string ATTRVALUE_LIM_RELDEFINES;
      extern const std::string ATTRVALUE_LIM_BEFORE;
      extern const std::string ATTRVALUE_LIM_NEVER;
      extern const std::string ATTRVALUE_LIM_NOW;

      // Node UID constans
      extern const std::string UID_RUL_ROOT;
      extern const std::string UID_CLONE_ROOT;
      extern const std::string UID_LOGICAL_ROOT;
      extern const std::string UID_PHYSICAL_ROOT;
      extern const std::string UID_RUL_GROUPS;
      extern const std::string UID_RUL_TAG_METADATA;

      // Header Attributes
      extern const std::string HEADER_ASG_KEY;
      extern const std::string HEADER_ASG_VALUE_JAVA;
      extern const std::string HEADER_ASG_VALUE_CPP;
      extern const std::string HEADER_ASG_VALUE_C;
      extern const std::string HEADER_ASG_VALUE_RPG;
      extern const std::string HEADER_ASG_VALUE_PYTHON;
      extern const std::string HEADER_ASG_VALUE_CSHARP;
      extern const std::string HEADER_ASG_VALUE_JAVASCRIPT;

      extern const std::string HEADER_MODE_KEY_SUFFIX;
      extern const std::string HEADER_MODE_VALUE_INACTIVE;
      extern const std::string HEADER_MODE_VALUE_LIMITED;
      extern const std::string HEADER_MODE_VALUE_FULL;
    }
  }
}

#endif
