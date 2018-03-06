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

#include "../inc/ResultConverter.h"
#include "../inc/RuleConverter.h"
#include "../inc/messages.h"
#include <common/inc/StringSup.h>
#include <common/inc/FileSup.h>
#include <common/inc/WriteMessage.h>
#include <common/inc/PlatformDependentDefines.h>
#include <lim2graph/inc/Lim2GraphConverter.h>
#include <graphsupport/inc/Metric.h>
#include <graphsupport/inc/MetricSum.h>
#include <graphsupport/inc/GraphConstants.h>
#include <graphsupport/inc/RulBuilder.h>

#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/util/XMLString.hpp>

using namespace std;
using namespace common;
using namespace columbus;
using namespace columbus::graph;
using namespace columbus::rul;
using namespace columbus::graphsupport;

XERCES_CPP_NAMESPACE_USE

bool parseXML(const string& filename, DefaultHandler* handler);
bool getAttr(const Attributes& attrs, const char* attrName, string& val);

ResultConverter::ResultConverter(const string& limFileName, const string& rul, const string& rulConfig, const std::string& txtOutputFileName) 
  : limFact(strTable, "", columbus::lim::asg::limLangOther),
    limFileName(limFileName), 
    xRulhandler(NULL),
    graphIndexer(graphsupport::GraphRangeIndexer::getGraphRangeIndexerInstance()),
    txtOutputFileName(txtOutputFileName)
{
  //load the rule file
  string iniFileName = ((pathFindFileName(rul) == rul) ? "." + string(DIRDIVSTRING) : "") + rul;
  xRulhandler = new columbus::rul::RulHandler(iniFileName, rulConfig, "eng", "ISO-8859-1");
}

ResultConverter::~ResultConverter() {
}

void ResultConverter::buildtree(const bool exportRul) {
  std::list<HeaderData*> header;
  WriteMsg::write(CMSG_FINDBUGS2GRAPH_LOADING_LIM, limFileName.c_str());
  //load lim
  try {
    limFact.load(limFileName, header);
  } catch (const lim::asg::LimException& ex) {
    WriteMsg::write(CMSG_FINDBUGS2GRAPH_LOAD_LIM_EXCEPTION, limFileName.c_str(), ex.getLocation().c_str(), ex.getMessage().c_str());
    exit(EXIT_FAILURE);
  }
  //load filter
  string filterFileName = common::replaceExtension(limFileName, ".flim");
  if (common::pathFileExists(filterFileName, false)) {
    WriteMsg::write(CMSG_FINDBUGS2GRAPH_LOADING_LIM_FILTER, filterFileName.c_str());
    if (fileTimeCmp(filterFileName, limFileName) == -1) {
      WriteMsg::write(CMSG_FINDBUGS2GRAPH_FILTER_FILE_IS_DEPRECATED, filterFileName.c_str());
    } else {
      try {
        limFact.loadFilter(filterFileName);
      } catch (const lim::asg::LimException& ex) {
        WriteMsg::write(CMSG_FINDBUGS2GRAPH_LOAD_FILTER_EXCEPTION, filterFileName.c_str(), ex.getLocation().c_str(), ex.getMessage().c_str());
        exit(EXIT_FAILURE);
      }
    }
  }
  WriteMsg::write(CMSG_FINDBUGS2GRAPH_USING_CONFIG, xRulhandler->getConfig().c_str());
  
  lim2graph::convertBaseGraph(limFact, graph, /*edges=*/ true, /*attributes=*/ true, /*components=*/ true, /*variants=*/ false, /*instances=*/ false);
  graphIndexer.turnOn(graph);
  if (exportRul)
    graphsupport::buildRulToGraph(graph, *xRulhandler);
}

void ResultConverter::writeWarningLine(const std::string& id, const std::string& warningText, list<AttributeComposite>& sourceLinks, const std::string& path, int line, int endline, int col, int endcol) {
  ofstream txtOutputStream(txtOutputFileName.c_str(), ios::app);
  if (txtOutputStream) {
    txtOutputStream << path << "(" << line << "):" << id << ": " << warningText << "\n";
    for (list<AttributeComposite>::iterator it = sourceLinks.begin(); it != sourceLinks.end(); ++it) {
      txtOutputStream << "  " << it->findAttributeByName(graphconstants::ATTR_PATH).next().getStringValue();
      txtOutputStream << "(" << it->findAttributeByName(graphconstants::ATTR_LINE).next().getStringValue() << "):";
      Attribute::AttributeIterator textIt = it->findAttributeByName(graphconstants::ATTR_SL_TEXT);
      if (textIt.hasNext())
        txtOutputStream << textIt.next().getStringValue() << "\n";
      else
        txtOutputStream << "\n";
    }
    txtOutputStream.close();
  } else {
    WriteMsg::write(CMSG_FINDBUGS2PATH_UNABLE_TO_APPEND_TO_FILE, txtOutputFileName.c_str());
  }
}

void ResultConverter::addWarningToNode(const std::string& path, const std::string& id, const std::string& group, const std::string& warningText, list<AttributeComposite>& sourceLinks, int line, int endline, int col,  int endcol) {
  if (!xRulhandler->getIsEnabled(id)) {
    return; // rule is not enabled
  }

  string fullPath = "";
  if ( !getFullPath(path, fullPath) ) {
    WriteMsg::write(CMSG_FINDBUGS2PATH_NOT_FOUND_IN_LIM, path.c_str());
    return;
  }

  list<Node> nodes;
  
  if (graphIndexer.findNodesByRange(graph,fullPath,line,INT_MIN,endline,INT_MAX,nodes)) {
    int minDist = INT_MAX;
    Node node;
    for(list<Node>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
      vector<graphsupport::Position> positions;
      graphsupport::getPositionAttributes(*it, positions);
      for(vector<graphsupport::Position>::iterator pos = positions.begin(); pos != positions.end(); ++pos) {
        if((abs(line-pos->line) + abs(endline-pos->endline)) < minDist) {
          node = *it;
          minDist = abs(line-pos->line) + abs(endline-pos->endline);
        }
      }
    }
    
    // if the found node is attribute, we use that parent
    if(node != Graph::invalidNode) {
      if(node.getType().getType() == graphsupport::graphconstants::NTYPE_LIM_ATTRIBUTE) {
        Edge::EdgeIterator edgeIt = node.findOutEdges(Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_LOGICALTREE, Edge::edtReverse));
        if(edgeIt.hasNext()) {
          node = edgeIt.next().getToNode();
        }
      }
    }

    if (node != Graph::invalidNode) {
      bool warningAdded = false;
      if (!sourceLinks.empty()) {
        AttributeComposite extraInfo = graph.createAttributeComposite(graphsupport::graphconstants::ATTR_EXTRAINFO, graphsupport::graphconstants::CONTEXT_TRACE);
        for (list<AttributeComposite>::iterator it = sourceLinks.begin(); it != sourceLinks.end(); it++) {
          extraInfo.addAttribute(*it);
        }
        warningAdded = graphsupport::addWarningOnce(graph, node, id, fullPath, line, col, endline, endcol, warningText, extraInfo);

      } else
        warningAdded = graphsupport::addWarningOnce(graph, node, id, fullPath, line, col, endline, endcol, warningText);
    
      if (warningAdded)
        writeWarningLine(id, warningText, sourceLinks, fullPath, line, col, endline, endcol);
      else
        WriteMsg::write(CMSG_FINDBUGS2GRAPH_WARNING_ALREADY_ADDED, id.c_str(), node.getUID().c_str(), fullPath.c_str(), line, col, endline, endcol, warningText.c_str());
    } else {
      //invalid node
    }
  } else {
    // there isn't any nodes in the given range 
  }
}

bool ResultConverter::getFullPath(const string& path, string& fullPath) {
  //search in map 
  if (pathMap.find(path) != pathMap.end()){
    fullPath = pathMap[path];
    return true;
  }
  //tokenize path
  string pathToTokenize = path;
  while (pathToTokenize.find_first_of('/') != string::npos) {
    pathFB.push_back(pathToTokenize.substr(0,pathToTokenize.find_first_of('/')));
    pathToTokenize = pathToTokenize.substr(pathToTokenize.find_first_of('/')+1, pathToTokenize.length());
  }
  pathFB.push_back(pathToTokenize);

  //call the recursive function
  if (!findPath((lim::asg::physical::FSEntry&)limFact.getRef(limFact.getFileSystemRoot()))) {
    pathFB.clear();
    pathLim.clear();
    return false;
  }

  //build the fullPath
  for (vector<string>::iterator it = pathLim.begin(); it != pathLim.end(); it++) {
    fullPath += DIRDIVSTRING + *it;
  }
  fullPath = fullPath.substr(1,fullPath.length());

  //clear the vectors
  pathFB.clear();
  pathLim.clear();

  //add the found path to the map
  pathMap[path] = fullPath;
  return true;
}

bool ResultConverter::findPath(const columbus::lim::asg::physical::FSEntry& item) {
  lim::asg::physical::Folder *folder = 0;
  lim::asg::physical::FileSystem *fs = 0;
  switch (item.getNodeKind()) {
    case lim::asg::ndkFolder:
      folder = &(lim::asg::physical::Folder&)item;
      pathLim.push_back(folder->getName());
      for (lim::asg::ListIterator<lim::asg::physical::FSEntry> it = folder->getContainsListIteratorBegin(); it != folder->getContainsListIteratorEnd(); ++it){
        if (findPath(*it)) {
          return true;
        }
      }
      pathLim.pop_back();
      return false;
      break;
    case lim::asg::ndkFile:
      if (pathFB[pathFB.size()-1].compare(item.getName()) == 0 && pathFB.size() < pathLim.size()) {
        for (size_t i = 1; i < pathFB.size(); i++) {
          if (pathFB[pathFB.size()-i-1].compare(pathLim[pathLim.size()-i]) != 0){
            return false;
          }
        }
        pathLim.push_back(item.getName());
        return true;
      } else {
        return false;
      }
      break;
    case lim::asg::ndkFileSystem:
      fs = &(lim::asg::physical::FileSystem&)limFact.getRef(limFact.getFileSystemRoot());
      for (lim::asg::ListIterator<lim::asg::physical::FSEntry> it = fs->getFSEntryListIteratorBegin(); it != fs->getFSEntryListIteratorEnd(); ++it) {
        if (findPath(*it)) {
          return true;
        }
      }
      return false;
      break;
    default:
      return false;
  }
}

void ResultConverter::saveGraph(const string& fileName){
  graph.saveBinary(fileName);
}

//Handler class to process the output xml of the FindBugs
class WarningHandler : public DefaultHandler {
  private:
    RulHandler* rul;
    ResultConverter* rc;

    enum SourceLevel {
      slNone,
      slClass,
      slMethod,
      slField,
      slBugInstance,
      slSourceLine,
      slLongMessage
    } actualSourceLvl;

    stack<SourceLevel> actualTagLvl;
    map<string, SourceLevel> tag2Int;
   
    //attributes to addWarningToNode
    int line;
    int endLine;
    string path;
    string id;
    string group;
    string warningText;
    list<AttributeComposite> sourceLinks;
    string content;
    string message;
  public:
    WarningHandler(RulHandler* xRulHandler, ResultConverter* rc) : DefaultHandler(), rul(xRulHandler), rc(rc), actualSourceLvl(slNone) { 
      tag2Int.insert(make_pair("LongMessage",slLongMessage));
      tag2Int.insert(make_pair("SourceLine", slSourceLine));
      tag2Int.insert(make_pair("BugInstance", slBugInstance));
      tag2Int.insert(make_pair("Field", slField));
      tag2Int.insert(make_pair("Method", slMethod));
      tag2Int.insert(make_pair("Class", slClass));
    }

    virtual void startElement (const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname, const Attributes &attrs) {
      content.clear();
      string name = XMLString::transcode(localname);

      if (tag2Int.find(name) != tag2Int.end()) {
        // get value of primary attribute
        string primaryValue = "";
        bool isPrimary = getAttr(attrs,"primary",primaryValue);
        if ( !(isPrimary && primaryValue == "true") ) {
          isPrimary = false;
        }

        switch(tag2Int[name]){
        case slLongMessage:
          // LongMessage
          actualTagLvl.push(tag2Int[name]);
          break;
        case slSourceLine: {
          SourceLevel level = slNone;
          // SourceLine
          if (!actualTagLvl.empty() && ((actualTagLvl.top() == slBugInstance && isPrimary)
            || (actualTagLvl.top() > actualSourceLvl) )) {
            //get the line info
            string newPath, newLine, newEndLine;
            if (getAttr(attrs,"sourcepath", newPath) && getAttr(attrs,"start", newLine) && getAttr(attrs,"end", newEndLine)) {
              actualSourceLvl = actualTagLvl.top();
              line = atoi(newLine.c_str());
              endLine = atoi(newEndLine.c_str());
              path = newPath;
            }
          } else {
            // get SourceLink
            if (!actualTagLvl.empty() && actualTagLvl.top() == slBugInstance) {
              string path, line, endLine;
              if (getAttr(attrs,"sourcepath", path) && getAttr(attrs,"start", line) && getAttr(attrs,"end", endLine)) {
                string fullPath = "";
                rc->getFullPath(path, fullPath);
                sourceLinks.push_back(graphsupport::createSourceLinkAttribute(*(rc->getGraph()),fullPath,atoi(line.c_str()),0,atoi(endLine.c_str()),INT_MAX));
                level = slSourceLine;
              }
            }
          }
          //push 5 into the stack -> a pop() call enough in endElement
          actualTagLvl.push(level);
          break;
        }
        case slBugInstance:
          // BugInstance
          getAttr(attrs,"type", id);
          id = rul->getRuleIdByOriginalId(id);
          getAttr(attrs,"category", group);
          actualTagLvl.push(tag2Int[name]);
          break;
        default:
          //Class, Method, Field
          if (isPrimary) {
            actualTagLvl.push(tag2Int[name]);
          } else {
            //if not primary then we are not interested in it's source info
            actualTagLvl.push(slNone);
          }
        }
      } else {
        // element does not matter
        actualTagLvl.push(slNone);
      }
    }

    virtual void  characters (const XMLCh *const chars, const XMLSize_t length) {
      content += XMLString::transcode(chars);
    }

    virtual void endElement(const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname){
      string element = XMLString::transcode(localname);
      if (element == "Message")
        message = content;
        
      if (actualTagLvl.top() == slLongMessage)
        warningText = content;
      
      else if(actualTagLvl.top() == slSourceLine) {
        if (element == "SourceLine" && !sourceLinks.empty())
          sourceLinks.back().addAttribute(rc->getGraph()->createAttributeString(graphconstants::ATTR_SL_TEXT, "", message));
      } else if(actualTagLvl.top() == slBugInstance){
        //End of BugInstance
        if (actualSourceLvl) {
          rc->addWarningToNode(path, id, group, warningText, sourceLinks, line, endLine);
          actualSourceLvl = slNone;
          sourceLinks.clear();
        } else {
          WriteMsg::write(CMSG_FINDBUGS2GRAPH_NO_SOURCEINFO_FOUND);
        }
      }
      actualTagLvl.pop();
    }
};

void ResultConverter::collectData(const std::string& fbOutFile){
  WarningHandler wh(xRulhandler, this);
  parseXML(fbOutFile, &wh);
}


void ResultConverter::aggregateWarnings(bool createGroups) {
  // summarize warnings
  graphsupport::cumSum(graph, graph::Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_COMPONENT, graph::Edge::edtDirectional), true);
  graphsupport::cumSum(graph, graph::Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_COMPONENTTREE, graph::Edge::edtReverse), false);
  graphsupport::cumSum(graph, graph::Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_LOGICALTREE, graph::Edge::edtReverse), false);

  // create group metrics
  if (createGroups)
    columbus::graphsupport::createGroupMetrics(graph, *xRulhandler);
}
