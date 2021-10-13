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

#include "messages.h"
#include <string>
#include <iostream>
#include <common/inc/FileSup.h>
#include <common/inc/StringSup.h>
#include <common/inc/WriteMessage.h>
#include <common/inc/PlatformDependentDefines.h>

using namespace std;
using namespace common;

string bin_dir;

int main(int argc, char **argv) {

    char* bindir = getenv("WRAPPER_BIN_DIR");

    if(!bindir){
        WriteMsg::write(CMSG_VSBUILD_WRAPPER_BIN_DIR_NOT_SET);
        return -1;
    }
    else{
        bin_dir = common::removeQuotes(bindir);
    }

    //get the executed file name
    string fileName = common::pathFindFileName(argv[0]);

    //finding original file
    string originalFile = findFile(fileName.c_str(), bin_dir.c_str());

    if (originalFile.empty()) {
        WriteMsg::write(CMSG_VSBUILD_ORIG_TOOL_NOT_FOUND, argv[0]);
        return -1;
    }

    string parameters = "";

    for (int i = 1; i < argc; ++i) {
        const string arg = string(argv[i]);
        if(arg.find(" ") != string::npos && arg.find(QUOTE) == string::npos)
            parameters += QUOTE + arg + QUOTE + " ";
        else
            parameters += arg + " ";
    }

    if(fileName.compare("msbuild.exe") == 0 || fileName.compare("msbuild") == 0){
        parameters += "/p:UseEnv=True";
    }
    else if(fileName.compare("devenv.exe") == 0 || fileName.compare("devenv") == 0){
        parameters += "/UseEnv";
    }
    else{
        WriteMsg::write(CMSG_VSBUILD_WRONG_TOOL_NAME, argv[0]);
        return -1;
    }

    string commandWithParams = originalFile + " " + parameters;

    //running original command
    return run(commandWithParams, false);
}
