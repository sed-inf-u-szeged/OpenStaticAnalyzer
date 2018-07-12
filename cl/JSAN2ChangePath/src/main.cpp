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


#define PROGRAM_NAME "JSAN2ChangePath"
#define EXECUTABLE_NAME "JSAN2ChangePath"

#include <MainCommon.h>
#include <common/inc/WriteMessage.h>
#include <javascript/inc/javascript.h>
#include "../inc/messages.h"

using namespace std;
using namespace common;
using namespace columbus;
using namespace columbus::javascript::asg;


static list<string> files;
static string changepathfrom;
static string changepathto;


static void ppFile(char *filename) {
  files.push_back(filename);
}

static bool ppChangePathFrom(const Option *o, char *argv[]) {
#if defined(__unix__)
  changepathfrom = argv[0];
#else
  changepathfrom = common::stringLower(argv[0]);
#endif
  return true;
}

static bool ppChangePathTo(const Option *o, char *argv[]) {
  changepathto = argv[0];
  return true;
}

const common::Option OPTIONS_OBJ [] = {
    { true,   "-changepathfrom", 1, CL_KIND_STRING, 0,  OT_WC,        ppChangePathFrom, NULL, "Set the path fragment, which will be replaced." },\
    { true,   "-changepathto",   1, CL_KIND_STRING, 0,  OT_WC,        ppChangePathTo,   NULL, "The new value of the replaced path fragment."},
    COMMON_CL_ARGS
};


class ChangePathVisitor: public VisitorAbstractNodes {
public:
  ChangePathVisitor() {}
  virtual ~ChangePathVisitor() {}

  virtual void visit(const base::Positioned& node, bool callVirtualBase) {
    VisitorAbstractNodes::visit(node, callVirtualBase);

    base::Positioned& n = const_cast<base::Positioned&>(node);
    Range r = node.getPosition();
    string path = r.getPath();
    if (common::changePath(path, changepathfrom, changepathto)) {
      r.setPath(path);
      n.setPosition(r);
    }
  }
};


int main(int argc, char* argv[]) {

  MAIN_BEGIN

    MainInit(argc, argv, "-");

    if (files.empty()) {
      WriteMsg::write(CMSG_MISSING_INPUT_FILES);
      clError();
    }

    if (changepathfrom.empty()) {
      WriteMsg::write(CMSG_MISSING_FROM_PARAMETER);
      clError();
    }

    for (list<string>::iterator it = files.begin(); it != files.end(); ++it) {
      RefDistributorStrTable strTable;
      Factory factory(strTable);

      columbus::PropertyData header;
      std::list<HeaderData*> listData;
      listData.push_back(&header);
      try {
          factory.load(it->c_str(), listData);
      }
      catch (IOException e) {
          WriteMsg::write(CMSG_MISSING_INPUT_FILES, it->c_str());
          continue;
      }

      WriteMsg::write(CMSG_REPLACING_PATH);
      ChangePathVisitor cpv;
      AlgorithmPreorder().run(factory, cpv);

      WriteMsg::write(CMSG_SAVING_FILE, it->c_str());
      factory.save(it->c_str(), listData);

    }

  MAIN_END

  return 0;
}
