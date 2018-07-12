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

#include "../inc/ReportConverter.h"
#include "../inc/FindLimNode.h"

using namespace std;
using namespace common;
using namespace columbus;
using namespace graph;
using namespace rul;
using namespace graphsupport;
using namespace fxcop2graph;

XERCES_CPP_NAMESPACE_USE

#define SSTR( x ) dynamic_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

bool parseXML(const string& filename, DefaultHandler* handler);
bool getAttr(const Attributes& attrs, const char* attrName, string& val);

ReportConverter::ReportConverter(const Config& config)
	: limFact(strTable, "", lim::asg::limLangCsharp),
	limFileName(config.limFile),
	config(config),
	xRulhandler(NULL),
	graphIndexer(GraphRangeIndexer::getGraphRangeIndexerInstance()),
	txtOutputFileName(config.outTxt)
{

	//load the rule file
	string iniFileName = ((pathFindFileName(config.rulFile) == config.rulFile) ? "." + string(DIRDIVSTRING) : "") + config.rulFile;
	xRulhandler = new RulHandler(iniFileName, "Default", "eng", "ISO-8859-1");
}

ReportConverter::~ReportConverter() {

}

void ReportConverter::buildtree(const bool exportRul) {
	list<HeaderData*> header;
	WriteMsg::write(CMSG_FXCOP2GRAPH_LOADING_LIM, limFileName.c_str());
	//load lim
	try {
		limFact.load(limFileName, header);
	}
	catch (const lim::asg::LimException& ex) {
		WriteMsg::write(CMSG_FXCOP2GRAPH_LOAD_LIM_EXCEPTION, limFileName.c_str(), ex.getLocation().c_str(), ex.getMessage().c_str());
		exit(EXIT_FAILURE);
	}
	//load filter
	string filterFileName = replaceExtension(limFileName, ".flim");
	if (pathFileExists(filterFileName, false)) {
		WriteMsg::write(CMSG_FXCOP2GRAPH_LOADING_LIM_FILTER, filterFileName.c_str());
		if (fileTimeCmp(filterFileName, limFileName) == -1) {
			WriteMsg::write(CMSG_FXCOP2GRAPH_FILTER_FILE_IS_DEPRECATED, filterFileName.c_str());
		}
		else {
			try {
				limFact.loadFilter(filterFileName);
			}
			catch (const lim::asg::LimException& ex) {
				WriteMsg::write(CMSG_FXCOP2GRAPH_LOAD_FILTER_EXCEPTION, filterFileName.c_str(), ex.getLocation().c_str(), ex.getMessage().c_str());
				exit(EXIT_FAILURE);
			}
		}
	}
	WriteMsg::write(CMSG_FXCOP2GRAPH_USING_CONFIG, xRulhandler->getConfig().c_str());

	lim2graph::convertBaseGraph(limFact, graph, /*edges=*/ true, /*attributes=*/ true, /*components=*/ true, /*variants=*/ false, /*instances=*/ false);

	graphIndexer.turnOn(graph);
	if (exportRul)
		buildRulToGraph(graph, *xRulhandler);
}

void ReportConverter::writeWarningLine(const string& id, const string& warningText, const string& path, int line, int endline, int col, int endcol) {
	ofstream txtOutputStream(txtOutputFileName.c_str(), ios::app);
	if (txtOutputStream) {
		txtOutputStream << path << "(" << line << "):" << id << ": " << warningText << "\n";
		txtOutputStream.close();
	}
	else {
		WriteMsg::write(CMSG_FXCOP2GRAPH_UNABLE_TO_APPEND_TO_FILE, txtOutputFileName.c_str());
	}
}

void ReportConverter::addWarningToNode(const string& mangleName, const string& id, const string& group, const string& warningText) {
    FindLimNode fln(mangleName, limFact);
    const lim::asg::logical::Member* member = fln.getLimNode();
    if (member != nullptr) {
        Node graphNode = graph.findNode("L" + SSTR(member->getId()));
        if (graphNode != Graph::invalidNode) {
            lim::asg::ListIteratorAssocSourcePosition<lim::asg::physical::File> it = member->getIsContainedInListIteratorAssocBegin();
            for (; it != member->getIsContainedInListIteratorAssocEnd(); ++it) {
                bool warningAdded = false;
                int line = it.getAssocClass().getLine();
                int endline = it.getAssocClass().getEndLine();
                int col = it.getAssocClass().getColumn();
                int endcol = it.getAssocClass().getEndColumn();
                string fullPath = it->getName();
	            auto asd = static_cast<lim::asg::physical::FSEntry*>(it->getParent());
                while (asd->getNodeKind() != lim::asg::ndkFileSystem) {
                    fullPath = asd->getName() + "\\" + fullPath;
                    asd = static_cast<lim::asg::physical::FSEntry*>(asd->getParent());
                }
                warningAdded = addWarningOnce(graph, graphNode, id, fullPath, line, col, endline, endcol, warningText);

				if (warningAdded) {
					writeWarningLine(id, warningText, fullPath, line, col, endline, endcol);
				}
            }
        }
    }
}

void ReportConverter::addWarningToNode(const string& path, const string& id, const string& group, const string& warningText, int line, int endline, int col, int endcol) {
	
	if (!xRulhandler->getIsEnabled(id)) {
		return; // rule is not enabled
	}

	string relativeOrAbsolutePath = path;
	if (config.changepathfrom != "") {
		changePath(relativeOrAbsolutePath, config.changepathfrom, config.changepathto);
	}

	string fullPath = "";
	if (!getFullPath(relativeOrAbsolutePath, fullPath)) {
		WriteMsg::write(CMSG_FXCOP2GRAPH_NOT_FOUND_IN_LIM, relativeOrAbsolutePath.c_str());
		return;
	}

	list<Node> nodes;

    if (graphIndexer.findNodesByRange(graph, fullPath, line, INT_MIN, endline, INT_MAX, nodes)) {
		int minDist = INT_MAX;
		Node node;
		for (list<Node>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
			vector<Position> positions;
			getPositionAttributes(*it, positions);
			for (vector<Position>::iterator pos = positions.begin(); pos != positions.end(); ++pos) {
				if ((abs(line - pos->line) + abs(endline - pos->endline)) < minDist) {
					node = *it;
					minDist = abs(line - pos->line) + abs(endline - pos->endline);
				}
			}
		}

		if (node != Graph::invalidNode) {
			bool warningAdded = false;
			warningAdded = addWarningOnce(graph, node, id, fullPath, line, col, endline, endcol, warningText);

			if (warningAdded)
				writeWarningLine(id, warningText, fullPath, line, col, endline, endcol);
			else
				WriteMsg::write(CMSG_FXCOP2GRAPH_WARNING_ALREADY_ADDED, id.c_str(), node.getUID().c_str(), fullPath.c_str(), line, col, endline, endcol, warningText.c_str());
		}
		else {
			//invalid node
		}
	}
	else {
		// there isn't any nodes in the given range 
	}
}

bool ReportConverter::getFullPath(const string& path, string& fullPath) {
	//search in map 
	if (pathMap.find(path) != pathMap.end()){
		fullPath = pathMap[path];
		return true;
	}
	//tokenize path
	string pathToTokenize = path;
	while (pathToTokenize.find_first_of('\\') != string::npos) {
		pathFB.push_back(pathToTokenize.substr(0, pathToTokenize.find_first_of('\\')));
		pathToTokenize = pathToTokenize.substr(pathToTokenize.find_first_of('\\') + 1, pathToTokenize.length());
	}
	pathFB.push_back(pathToTokenize);

	//call the recursive function
	if (!findPath(static_cast<lim::asg::physical::FSEntry&>(limFact.getRef(limFact.getFileSystemRoot())))) {
		pathFB.clear();
		pathLim.clear();
		return false;
	}

	//build the fullPath
	for (vector<string>::iterator it = pathLim.begin(); it != pathLim.end(); ++it) {
		fullPath += DIRDIVSTRING + *it;
	}
	fullPath = fullPath.substr(1, fullPath.length());

	//clear the vectors
	pathFB.clear();
	pathLim.clear();

	//add the found path to the map
	pathMap[path] = fullPath;
	return true;
}

bool ReportConverter::findPath(const lim::asg::physical::FSEntry& item) {
	lim::asg::physical::Folder *folder = nullptr;
	lim::asg::physical::FileSystem *fs = nullptr;
	switch (item.getNodeKind()) {
	case lim::asg::ndkFolder:
		folder = &static_cast<lim::asg::physical::Folder&>(const_cast<lim::asg::physical::FSEntry&>(item));
		pathLim.push_back(folder->getName());
		for (auto it = folder->getContainsListIteratorBegin(); it != folder->getContainsListIteratorEnd(); ++it){
			if (findPath(*it)) {
				return true;
			}
		}
		pathLim.pop_back();
		return false;
	case lim::asg::ndkFile:
		if (pathFB[pathFB.size() - 1].compare(item.getName()) == 0 && pathFB.size() > pathLim.size()) {
			for (size_t i = 1; i < pathFB.size() && pathLim.size() >= i; i++) {
				if (pathFB[pathFB.size() - i - 1].compare(pathLim[pathLim.size() - i]) != 0){
					return false;
				}
			}
			pathLim.push_back(item.getName());
			return true;
		}
		return false;
	case lim::asg::ndkFileSystem:
		fs = &static_cast<lim::asg::physical::FileSystem&>(limFact.getRef(limFact.getFileSystemRoot()));
		for (auto it = fs->getFSEntryListIteratorBegin(); it != fs->getFSEntryListIteratorEnd(); ++it) {
			if (findPath(*it)) {
				return true;
			}
		}
		return false;
	default:
		return false;
	}
}

void ReportConverter::saveGraph(const string& fileName){
	graph.saveBinary(fileName);
}

//Handler class to process the output xml of the FindBugs
class WarningHandler : public DefaultHandler {
private:
	RulHandler* rul;
	ReportConverter* rc;

	//attributes to addWarningToNode
	int line;
	int endLine;
	string path;
	string filename;
	string id;
	string group;
	string warningText;
	string content;
	string message;

    string targetName;
    string actualNamespace;
    string actualType;
    string actualMember;
   
public:
	WarningHandler(RulHandler* xRulHandler, ReportConverter* rc, lim::asg::Factory& limFactory) : 
        DefaultHandler(), 
        rul(xRulHandler), 
        rc(rc)
    {
	}

	virtual void startElement(const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname, const Attributes &attrs) {
		content.clear();
		string name = XMLString::transcode(localname);

        path = filename = "";

		if (name == "Message") {
			getAttr(attrs, "CheckId", id);
			getAttr(attrs, "Category", group);
		}
		else if (name == "Issue")
		{
			getAttr(attrs, "Path", path);
			getAttr(attrs, "File", filename);
			path += "\\"+ filename;
			string l;
			getAttr(attrs, "Line", l);
			line = atoi(l.c_str());
			endLine = line;
        }
        else if (name == "Namespace") {
            getAttr(attrs, "Name", actualNamespace);
            actualType = "";
            actualMember = "";
        }
        else if (name == "Type") {
            getAttr(attrs, "Name", actualType);
            actualMember = "";
        }
        else if (name == "Member") {
            getAttr(attrs, "Name", actualMember);
        }
	}

	virtual void  characters(const XMLCh *const chars, const XMLSize_t length) {
		content += XMLString::transcode(chars);
	}

	virtual void endElement(const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname){
		string element = XMLString::transcode(localname);

		if (element == "Issue"){
			warningText = content;
		}
		else if (element == "Message" && path.length() > 5){
			try{
				rc->addWarningToNode(path, rul->getRuleIdByOriginalId(id), group, warningText, line, endLine);
			}catch(Exception ex){
				WriteMsg::write(CMSG_FXCOP2GRAPH_MISSIG_RUL(id));
				return;
			}
        }
        else if (element == "Message" && path == "\\") {
            string mangleName;
            if (actualNamespace != "" && actualType == "" && actualMember == "") {
                mangleName = actualNamespace;
            }
            else if (actualNamespace != "" && actualType != "" && actualMember == "") {
                mangleName = actualNamespace + "." + actualType;
            }
            else if (actualNamespace != "" && actualType != "" && actualMember != "") {
                mangleName = actualNamespace + "." + actualType + "." + actualMember.substr(1, actualMember.length() - 1);
            }
            if (mangleName != "") {
//				rc->addWarningToNode(mangleName, rul->getRuleIdByOriginalId(id), group, warningText);
            }
        }

	}
};

bool ReportConverter::collectData(const vector<string>& file_names){
  WarningHandler wh(xRulhandler, this, limFact);
  if (file_names.size() == 0) return false;
  for (const auto& filename : file_names){
    parseXML(filename, &wh);
  }
  return true;
}

void ReportConverter::aggregateWarnings(bool createGroups) {
	// summarize warnings
	cumSum(graph, Edge::EdgeType(graphconstants::ETYPE_LIM_COMPONENT, Edge::edtDirectional), true);
	cumSum(graph, Edge::EdgeType(graphconstants::ETYPE_LIM_COMPONENTTREE, Edge::edtReverse), false);
	cumSum(graph, Edge::EdgeType(graphconstants::ETYPE_LIM_LOGICALTREE, Edge::edtReverse), false);

	// create group metrics
	if (createGroups)
		createGroupMetrics(graph, *xRulhandler);
}

void ReportConverter::addLicenseTypeToTheGraphHeader(const string& toolName, const string& headerMode) {
    graph.setHeaderInfo(toolName + graphconstants::HEADER_MODE_KEY_SUFFIX, headerMode);
}
