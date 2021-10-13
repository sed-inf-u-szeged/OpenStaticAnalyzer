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

#include "common/inc/Arguments.h"
#include "ReleaseVersion.h"
#include "strtable/inc/StrTable.h"
#include "java/inc/java.h"
#include "common/inc/FileSup.h"
#include "common/inc/StringSup.h"
#include "common/inc/WriteMessage.h"
#include <common/inc/Stat.h>
#include <io/inc/CsvIO.h>
#include <boost/filesystem.hpp>


#include <iostream>
#include <string>
#include <list>

#define PROGRAM_NAME "JAN2ChangePath"
#define EXECUTABLE_NAME "JAN2ChangePath"

#include "MainCommon.h"
#include "messages.h"

using namespace std;
using namespace common;
using namespace columbus;
using namespace columbus::java::asg;

struct Config {
  string from;
  string to;

  Config() : from(""), to("") {}
};

static string statFile;
static list<string> input_files;
static Config config;

static bool ppFrom(const Option *o, char *argv[]) {
#if defined(__unix__)
  config.from = argv[0];
#else
  config.from = common::stringLower(argv[0]);
#endif
  return true;
}

static bool ppTo(const Option *o, char *argv[]) {
  config.to = argv[0];
  return true;
}

static void ppFile(char *filename) {
  input_files.push_back(filename);
}

static bool ppList(const Option *o, char *argv[]) {
  return common::loadStringListFromFile(argv[0], input_files);
}

const Option OPTIONS_OBJ[] = {
  { false,  "-from",     1, "path",      1, OT_WC,     ppFrom,       NULL,    "Set the path fragment, which will be replaced."},
  { false,  "-to",       1, "path",      2, OT_WC,     ppTo,         NULL,    "The new value of the replaced path fragment."},
  CL_INPUT_LIST
  COMMON_CL_ARGS
};


#define CHANGE_PATH_VISIT_BEGIN(SCOPE, NODE) \
  virtual void visit(const SCOPE::NODE& node, bool callVirtualBase) { \
    VisitorAbstractNodes::visit(node, callVirtualBase); \
    SCOPE::NODE &n = const_cast<SCOPE::NODE&>(node);

#define CHANGE_PATH_ATTR(ATTR) \
  { \
    Range r = node.get##ATTR(); \
    string path = r.getPath(); \
    if (common::changePath(path, config.from, config.to)) { \
      r.setPath(path); \
      n.set##ATTR(r); \
    } \
  }

#define CHANGE_PATH_VISIT_END \
  }


class ChangePathVisitor: public VisitorAbstractNodes {
public:
  // base
  CHANGE_PATH_VISIT_BEGIN(base, PositionedWithoutComment) // simple position
  CHANGE_PATH_ATTR(Position)
  CHANGE_PATH_VISIT_END

  CHANGE_PATH_VISIT_BEGIN(base, Named)
  CHANGE_PATH_ATTR(NamePosition)
  CHANGE_PATH_VISIT_END

  // expr
  CHANGE_PATH_VISIT_BEGIN(expr, Conditional)
  CHANGE_PATH_ATTR(ColonPosition)
  CHANGE_PATH_VISIT_END

  CHANGE_PATH_VISIT_BEGIN(expr, NewArray)
  CHANGE_PATH_ATTR(LeftBracePosition)
  CHANGE_PATH_VISIT_END

  // statm
  CHANGE_PATH_VISIT_BEGIN(statm, Assert)
  CHANGE_PATH_ATTR(ColonPosition)
  CHANGE_PATH_VISIT_END

  CHANGE_PATH_VISIT_BEGIN(statm, BasicFor)
  CHANGE_PATH_ATTR(FirstSemiPosition)
  CHANGE_PATH_ATTR(SecondSemiPosition)
  CHANGE_PATH_VISIT_END

  CHANGE_PATH_VISIT_BEGIN(statm, Do)
  CHANGE_PATH_ATTR(WhilePosition)
  CHANGE_PATH_VISIT_END

  CHANGE_PATH_VISIT_BEGIN(statm, EnhancedFor)
  CHANGE_PATH_ATTR(ColonPosition)
  CHANGE_PATH_VISIT_END

  CHANGE_PATH_VISIT_BEGIN(statm, For)
  CHANGE_PATH_ATTR(LeftParenPosition)
  CHANGE_PATH_ATTR(RightParenPosition)
  CHANGE_PATH_VISIT_END

  CHANGE_PATH_VISIT_BEGIN(statm, Handler)
  CHANGE_PATH_ATTR(LeftParenPosition)
  CHANGE_PATH_ATTR(RightParenPosition)
  CHANGE_PATH_VISIT_END

  CHANGE_PATH_VISIT_BEGIN(statm, If)
  CHANGE_PATH_ATTR(ElsePosition)
  CHANGE_PATH_VISIT_END

  CHANGE_PATH_VISIT_BEGIN(statm, Jump)
  CHANGE_PATH_ATTR(LabelPosition)
  CHANGE_PATH_VISIT_END

  CHANGE_PATH_VISIT_BEGIN(statm, LabeledStatement)
  CHANGE_PATH_ATTR(ColonPosition)
  CHANGE_PATH_VISIT_END

  CHANGE_PATH_VISIT_BEGIN(statm, Switch)
  CHANGE_PATH_ATTR(BlockStartPosition)
  CHANGE_PATH_VISIT_END

  CHANGE_PATH_VISIT_BEGIN(statm, SwitchLabel)
  CHANGE_PATH_ATTR(ColonPosition)
  CHANGE_PATH_VISIT_END

  CHANGE_PATH_VISIT_BEGIN(statm, Try)
  CHANGE_PATH_ATTR(ResourceLeftParenPosition)
  CHANGE_PATH_ATTR(ResourceRightParenPosition)
  CHANGE_PATH_ATTR(FinallyPosition)
  CHANGE_PATH_VISIT_END

  // struc
  CHANGE_PATH_VISIT_BEGIN(struc, AnnotationType)
  CHANGE_PATH_ATTR(AtSignPosition)
  CHANGE_PATH_VISIT_END

  CHANGE_PATH_VISIT_BEGIN(struc, AnnotationTypeElement)
  CHANGE_PATH_ATTR(DefaultPosition)
  CHANGE_PATH_VISIT_END

  CHANGE_PATH_VISIT_BEGIN(struc, Enum)
  CHANGE_PATH_ATTR(SemiPosition)
  CHANGE_PATH_VISIT_END

  CHANGE_PATH_VISIT_BEGIN(struc, Import)
  CHANGE_PATH_ATTR(StaticPosition)
  CHANGE_PATH_VISIT_END

  CHANGE_PATH_VISIT_BEGIN(struc, MethodDeclaration)
  CHANGE_PATH_ATTR(AbstractPosition)
  CHANGE_PATH_ATTR(StrictfpPosition)
  CHANGE_PATH_ATTR(ParametersStartPosition)
  CHANGE_PATH_ATTR(ParametersEndPosition)
  CHANGE_PATH_VISIT_END

  CHANGE_PATH_VISIT_BEGIN(struc, NamedDeclaration)
  CHANGE_PATH_ATTR(AccessibilityPosition)
  CHANGE_PATH_ATTR(StaticPosition)
  CHANGE_PATH_ATTR(FinalPosition)
  CHANGE_PATH_VISIT_END

  CHANGE_PATH_VISIT_BEGIN(struc, NormalMethod)
  CHANGE_PATH_ATTR(SynchronizedPosition)
  CHANGE_PATH_ATTR(NativePosition)
  CHANGE_PATH_ATTR(ThrowsPosition)
  CHANGE_PATH_VISIT_END

  CHANGE_PATH_VISIT_BEGIN(struc, Parameter)
  CHANGE_PATH_ATTR(VarargsPosition)
  CHANGE_PATH_VISIT_END

  CHANGE_PATH_VISIT_BEGIN(struc, StaticInitializerBlock)
  CHANGE_PATH_ATTR(BlockStartPosition)
  CHANGE_PATH_VISIT_END

  CHANGE_PATH_VISIT_BEGIN(struc, TypeDeclaration)
  CHANGE_PATH_ATTR(TypeNamePosition)
  CHANGE_PATH_ATTR(AbstractPosition)
  CHANGE_PATH_ATTR(StrictfpPosition)
  CHANGE_PATH_ATTR(ExtendsPosition)
  CHANGE_PATH_ATTR(ImplementsPosition)
  CHANGE_PATH_ATTR(BodyStartPosition)
  CHANGE_PATH_VISIT_END

  CHANGE_PATH_VISIT_BEGIN(struc, Variable)
  CHANGE_PATH_ATTR(TransientPosition)
  CHANGE_PATH_ATTR(VolatilePosition)
  CHANGE_PATH_ATTR(EqualSignPosition)
  CHANGE_PATH_VISIT_END
};

int main(int argc, char* argv[]) {
  int exit_code = EXIT_SUCCESS;

  MAIN_BEGIN

    MainInit(argc, argv, "-");

    if (input_files.empty()) {
      WriteMsg::write(CMSG_MISSING_INPUT_FILES);
      clError();
    }

    if (config.from.empty()) {
      WriteMsg::write(CMSG_MISSING_FROM_PARAMETER);
      clError();
    }
    
    WriteMsg::write(CMSG_START_JAN2CHANGEPATH, config.from.c_str(), config.to.c_str());

    for (list<string>::const_iterator it = input_files.begin(); it != input_files.end(); ++it) {
      RefDistributorStrTable strTable;
      Factory fact(strTable);
      CsiHeader header;
      WriteMsg::write(CMSG_LOADING, it->c_str());
  #ifndef _DEBUG
      try {
  #endif
        fact.load(*it, header);
  #ifndef _DEBUG
      } catch (const IOException&) {
        WriteMsg::write(CMSG_CANNOT_LOAD_FILE, it->c_str());
        exit_code = EXIT_FAILURE;
        continue;
      }
  #endif
      WriteMsg::write(CMSG_REPLACING_PATH);
      ChangePathVisitor cpv;
      AlgorithmPreorder().run(fact, cpv);
      string newName = *it;
      WriteMsg::write(CMSG_WRITING_PATH, newName.c_str());
  #ifndef _DEBUG
      try {
  #endif
       fact.save(newName, header);
  #ifndef _DEBUG
      } catch (const IOException&) {
        WriteMsg::write(CMSG_CANNOT_SAVE_FILE, newName.c_str());
        exit_code = EXIT_FAILURE;
        continue;
      }
  #endif
      WriteMsg::write(CMSG_DONE);

      // touch the filter file
      string filterFile = replaceExtension(newName, ".fjsi");
      if (common::pathFileExists(filterFile, false)) {
        WriteMsg::write(CMSG_TOUCHING_FILTER, filterFile.c_str());
        try {
          time_t asgFileTime = boost::filesystem::last_write_time(newName);
          boost::filesystem::last_write_time(filterFile, asgFileTime + 1);
        } catch (const boost::filesystem::filesystem_error& e) {
          WriteMsg::write(CMSG_ERROR_WHILE_TOUCHING_FILTER, filterFile.c_str(), e.what());
          exit_code = EXIT_FAILURE;
        }
      }
    }

  MAIN_END

  return exit_code;
}

