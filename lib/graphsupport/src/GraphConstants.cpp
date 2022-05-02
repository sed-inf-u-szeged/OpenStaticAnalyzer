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

#include "../inc/GraphConstants.h"

using namespace std;

namespace columbus { 
  namespace graphsupport { 

    namespace graphconstants {
      
      // Context constants
      const string CONTEXT_WARNING       = "warning";
      const string CONTEXT_METRIC        = "metric";
      const string CONTEXT_METRICGROUP   = "metricgroup";
      const string CONTEXT_ATTRIBUTE     = "attribute";
      const string CONTEXT_RUL           = "rul";
      const string CONTEXT_TRACE         = "trace";
      
      // Attribute name constants
      const string ATTR_WARNINGTEXT      = "WarningText";
      const string ATTR_POSITION         = "Position";
      const string ATTR_NAME             = "Name";
      const string ATTR_LONGNAME         = "LongName";
      const string ATTR_PATH             = "Path";
      const string ATTR_LINE             = "Line";
      const string ATTR_COLUMN           = "Column";
      const string ATTR_ENDLINE          = "EndLine";
      const string ATTR_ENDCOLUMN        = "EndColumn";
      const string ATTR_REALIZATIONLEVEL = "RealizationLevel";
      const string ATTR_ANONYMOUS        = "Anonymous";
      const string ATTR_SPOOLFILE        = "SpoolFile";
      const string ATTR_CHANGESETID      = "ChangesetID";
      const string ATTR_ANALYSISTIME     = "AnalysisTime";
      const string ATTR_DEPENDENCYTYPE   = "DependencyType";
      
      const string ATTR_RUL_DESCRIPTION  = "Description";
      const string ATTR_RUL_DISPLAYNAME  = "DisplayName";
      const string ATTR_RUL_ENABLED      = "Enabled";
      const string ATTR_RUL_GROUPTYPE    = "GroupType";
      const string ATTR_RUL_HELPTEXT     = "HelpText";
      const string ATTR_RUL_SETTINGS     = "Settings";
      const string ATTR_RUL_PRIORITY     = "Priority";
      const string ATTR_RUL_WARNING      = "Warning";
      const string ATTR_RUL_CALCULATED   = "Calculated";
      const string ATTR_RUL_CALCULATEDFOR= "CalculatedFor";
      const string ATTR_RUL_TAGS         = "Tags";
      const string ATTR_RUL_TAG          = "Tag";
      const string ATTR_RUL_TAG_METADATA_URL              = "url";
      const string ATTR_RUL_TAG_METADATA_DESCRIPTION      = "description";
      const string ATTR_RUL_TAG_METADATA_SUMMARIZED       = "summarized";
      const string ATTR_RUL_TAG_METADATA_SUMMARIZED_TRUE  = "true";
      const string ATTR_RUL_TAG_METADATA_SUMMARIZED_FALSE = "false";
      
      const string ATTR_DCF_CLONESMELLTYPE = "CloneSmellType";
      
      const string ATTR_UUID             = "UUID";
      const string ATTR_TUID             = "TUID";
      
      const string ATTR_EXTRAINFO        = "ExtraInfo";
      const string ATTR_SOURCELINK       = "SourceLink";
      const string ATTR_CALLSTACKDEPTH   = "CallStackDepth";
      const string ATTR_SL_TEXT          = "Message";
      
      // Node type constants
      const string NTYPE_ROOT            = "TreeRoot";

      const string NTYPE_RUL_METRIC      = "RulMetric";
      const string NTYPE_RUL_TOOL        = "RulTool";
      const string NTYPE_RUL_TREE_NODE   = "RulTreeNode";
      const string NTYPE_RUL_METADATA    = "RulMetadata";
      
      const string NTYPE_LIM_COMPONENT   = "Component";
      const string NTYPE_LIM_MODULE      = "Module";
      const string NTYPE_LIM_NAMESPACE   = "Namespace";
      const string NTYPE_LIM_PACKAGE     = "Package";
      const string NTYPE_LIM_ROOT        = "Root";
      const string NTYPE_LIM_CLASS       = "Class";
      const string NTYPE_LIM_STRUCTURE   = "Structure";
      const string NTYPE_LIM_DELEGATE    = "Delegate";
      const string NTYPE_LIM_UNION       = "Union"; 
      const string NTYPE_LIM_INTERFACE   = "Interface";
      const string NTYPE_LIM_ENUM        = "Enum";
      const string NTYPE_LIM_ANNOTATION  = "Annotation";
      const string NTYPE_LIM_SOURCEFILE  = "SourceFile";
      const string NTYPE_LIM_CLASSDEF    = "ClassDef";
      const string NTYPE_LIM_FUNCTION    = "Function";
      const string NTYPE_LIM_METHOD      = "Method";
      const string NTYPE_LIM_FUNCTIONMEMBER = "FunctionMember";
      const string NTYPE_LIM_PROCEDURE   = "Procedure";
      const string NTYPE_LIM_FUNCTIONDEF = "FunctionDef";
      const string NTYPE_LIM_METHODDEF   = "MethodDef";
      const string NTYPE_LIM_ATTRIBUTE   = "Attribute";
      const string NTYPE_LIM_FILESYSTEM  = "FileSystem";
      const string NTYPE_LIM_FOLDER      = "Folder";
      const string NTYPE_LIM_FILE        = "File";

      const string NTYPE_DCF_CLONECLASS  = "CloneClass";
      const string NTYPE_DCF_CLONEINSTANCE = "CloneInstance";

      const string NTYPE_RPG_SYSTEM      = "System";
      const string NTYPE_RPG_PROGRAM     = "Program";
      const string NTYPE_RPG_MODULE      = "Module";
      const string NTYPE_RPG_PROCEDURE   = "Procedure";
      const string NTYPE_RPG_SUBROUTINE  = "Subroutine";
      
      // Edge type constants
      const string ETYPE_RUL_GROUPCONTAINS  = "RulGroupContains";
      const string ETYPE_RUL_TREE           = "RulTree";

      const string ETYPE_LIM_LOGICALTREE    = "LogicalTree";
      const string ETYPE_LIM_PHYSICALTREE   = "PhysicalTree";
      const string ETYPE_LIM_COMPONENTTREE  = "ComponentTree";
      const string ETYPE_LIM_COMPONENT      = "Component";
      const string ETYPE_LIM_VARIANT        = "Variant";
      const string ETYPE_LIM_AGGREGATED     = "Aggregated";
      const string ETYPE_LIM_INSTANCE       = "Instance";
      const string ETYPE_LIM_DECLARES       = "Declares";
      const string ETYPE_LIM_DEPENDSON      = "DependsOn";
      
      const string ETYPE_DCF_CLONETREE      = "CloneTree";
      const string ETYPE_DCF_HASCLONE       = "Clone";
      
      // Attribute value constants 
      const string ATTRVALUE_INVALID         = "__INVALID__";

      const string ATTRVALUE_LIM_RELDECLARES = "declaration";
      const string ATTRVALUE_LIM_RELDEFINES  = "definition";
      const string ATTRVALUE_LIM_BEFORE      = "before";
      const string ATTRVALUE_LIM_NEVER       = "never";
      const string ATTRVALUE_LIM_NOW         = "now";

      // Node UID constans
      const string UID_RUL_ROOT             = "__RulRoot__";
      const string UID_CLONE_ROOT           = "__CloneRoot__";
      const string UID_LOGICAL_ROOT         = "__LogicalRoot__";
      const string UID_PHYSICAL_ROOT        = "__PhysicalRoot__";
      const string UID_RUL_GROUPS           = "__RulGroups__";
      const string UID_RUL_TAG_METADATA     = "__RulTagMetadata__";
      
      // Header Attributes
      const string HEADER_ASG_KEY               = "asg";
      const string HEADER_ASG_VALUE_JAVA        = "java";
      const string HEADER_ASG_VALUE_CPP         = "cpp";
      const string HEADER_ASG_VALUE_C           = "c";
      const string HEADER_ASG_VALUE_RPG         = "rpg";
      const string HEADER_ASG_VALUE_PYTHON      = "python";
      const string HEADER_ASG_VALUE_CSHARP      = "cs";
      const string HEADER_ASG_VALUE_JAVASCRIPT  = "javascript";

      const string HEADER_MODE_KEY_SUFFIX       = "-mode";
      const string HEADER_MODE_VALUE_INACTIVE   = "inactive";
      const string HEADER_MODE_VALUE_LIMITED    = "limited";
      const string HEADER_MODE_VALUE_FULL       = "full";
      
    }
  }
}
