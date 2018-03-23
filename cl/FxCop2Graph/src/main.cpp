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

#define PROGRAM_NAME "FxCop2Graph"
#define EXECUTABLE_NAME "FxCop2Graph"

#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "../inc/messages.h"
#include <common/inc/Stat.h>

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/util/XMLString.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp>

#include "../inc/RuleConverter.h"
#include "../inc/ReportConverter.h"
#include "../inc/Config.h"
#include <MainCommon.h>

using namespace std;
using namespace common;
using namespace columbus;
using namespace fxcop2graph;


XERCES_CPP_NAMESPACE_USE

Config config;
typedef std::vector<std::string> File_Names;

static File_Names* files = new File_Names();

static bool ppMakeRul(const Option *o, char *argv[]) {
    config.makerul = true;
    config.pathDir = argv[0];
    return true;
}

static bool ppGraph(const Option *o, char *argv[]) {
    config.outGraph = argv[0];
    return true;
}

static bool ppOut(const Option *o, char *argv[]) {
    config.outTxt = argv[0];
    return true;
}

static bool ppLimFile(const Option *o, char *argv[]) {
    config.limFile = argv[0];
    return true;
}

static bool ppRul(const Option *o, char *argv[]) {
    config.rulFile = argv[0];
    return true;
}

static bool ppRulConfig(const Option *o, char *argv[]) {
    config.rulConfig = argv[0];
    return true;
}

static bool ppExportRul(const Option *o, char *argv[]) {
    config.exportRul = true;
    return true;
}

static void ppFile(char *filename) {
    config.inputFile = filename;
}

const Option OPTIONS_OBJ[] = {
        { false, "-makerul", 1, "pathDir", 0, OT_WS, ppMakeRul, NULL, "Makes rul file from the FxCop xmls and the configuration xml of the sonar." },
        { false, "-graph", 1, "file", 1, OT_WC, ppGraph, NULL, "Save binary graph output." },
        { false, "-out", 1, "file", 0, OT_WC, ppOut, NULL, "Specify the name of the output file. The list of rule violations will be dumped in it.\n" },
        CL_LIM
        CL_RUL_AND_RULCONFIG("FxCop.rul")
        CL_EXPORTRUL
        COMMON_CL_ARGS
};

static File_Names getFileNames(string dirPath){
    File_Names* files = new File_Names();

    namespace fs = boost::filesystem;
    boost::filesystem::path someDir(dirPath);
    boost::filesystem::directory_iterator end_iter;

    typedef std::multimap<std::time_t, fs::path> result_set_t;
    result_set_t result_set;

    if (fs::exists(someDir) && fs::is_directory(someDir))
    {
        for (fs::directory_iterator dir_iter(someDir); dir_iter != end_iter; ++dir_iter)
        {
            if (dir_iter->path().extension().generic_string() == ".xml" &&  fs::is_regular_file(dir_iter->status()))
            {
                files->push_back(dir_iter->path().generic_string());
                updateMemoryStat();
            }
        }
    }

    return *files;
}

bool parseXML(const string& filename, DefaultHandler* handler) {
    SAX2XMLReader* parser = XMLReaderFactory::createXMLReader();

    parser->setFeature(XMLUni::fgSAX2CoreValidation, true);
    parser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
    parser->setFeature(XMLUni::fgXercesSchema, false);
    parser->setFeature(XMLUni::fgXercesLoadExternalDTD, false);
    parser->setContentHandler(handler);
    parser->setErrorHandler(handler);

    try {
        parser->parse(filename.c_str());
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        WriteMsg::write(CMSG_FILE_PARSE_ERROR, filename.c_str(), message);
        XMLString::release(&message);
        return false;
    }
    catch (const SAXParseException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        WriteMsg::write(CMSG_FILE_PARSE_ERROR, filename.c_str(), message);
        XMLString::release(&message);
        return false;
    }

    delete parser;
    return true;
}

bool getAttr(const Attributes& attrs, const char* attrName, string& val) {
    bool ret = false;
    XMLCh* nameCh = XMLString::transcode(attrName);
    char* value = XMLString::transcode(attrs.getValue(nameCh));
    if (value != NULL) {
        val = value;
        ret = true;
    }
    XMLString::release(&nameCh);
    XMLString::release(&value);
    return ret;
}

int main(int argc, char *argv[]) {

    MAIN_BEGIN

    MainInit(argc, argv, "-");
    if (!config.makerul) {
        if (config.inputFile.empty()) {
            WriteMsg::write(CMSG_FXCOP2GRAPH_MISSING_ASG);
            clError();
        }

        if (config.limFile.empty()) {
            WriteMsg::write(CMSG_FXCOP2GRAPH_MISSING_LIM);
            clError();
        }
    }
    // init xerces
    try {
        XMLPlatformUtils::Initialize();
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        WriteMsg::write(CMSG_XERCES_ERROR, message);
        string exceptionMessage = "Error during XERCES initialization! ";
        exceptionMessage += message;
        XMLString::release(&message);
        throw Exception("initxerces()", exceptionMessage);
    }

    updateMemoryStat(true);

    //make rule
    if (config.makerul) {
        RuleConverter ruleConverter;
        ruleConverter.convertRuleFile(getFileNames(config.pathDir), config);
        updateMemoryStat();
    } else {

        //process fxcop output
        if (!config.outTxt.empty()) {
            ofstream txtOutputStream(config.outTxt.c_str(), std::ofstream::trunc);
        }

        ReportConverter rc(config);
        updateMemoryStat();
        rc.buildtree(config.exportRul);

        if (rc.collectData(getFileNames(config.inputFile))) {
            rc.aggregateWarnings(true);
            updateMemoryStat();
        }
        rc.saveGraph(config.outGraph);
    }

    // terminate xerces
    XMLPlatformUtils::Terminate();

    MAIN_END
    return 0;
}
