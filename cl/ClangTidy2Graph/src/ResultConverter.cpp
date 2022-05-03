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

#include <lim2graph/inc/Lim2GraphConverter.h>
#include <graphsupport/inc/RulBuilder.h>
#include <graphsupport/inc/GraphConstants.h>
#include <graphsupport/inc/MetricSum.h>
#include <common/inc/StringSup.h>
#include <regex>

#include "../inc/ResultConverter.h"
#include "../inc/messages.h"
#include "../inc/defines.h"

using namespace std;
using namespace common;
using namespace columbus;
using namespace columbus::graph;
using namespace columbus::clangtidy2graph;


ResultConverter::ResultConverter(const std::string& limFileName, const std::string& txtOutFile, const std::string& rulFileName, const std::string& rulConfig, const bool exportRul, const std::string& changePathFrom, const std::string& changePathTo):
    handler(),
    rulHandler(rulFileName, rulConfig, "eng"),
    limStrTable(),
    limFactory(limStrTable, "", columbus::lim::asg::limLangOther),
    graphIndexer(graphsupport::GraphRangeIndexer::getGraphRangeIndexerInstance()),
    changePathFrom(changePathFrom),
    changePathTo(changePathTo),
    txtOutFile(txtOutFile)
{
  // Loading lim
  list<HeaderData*> headerDataList;
  limFactory.load(limFileName, headerDataList);
  loadFilter(limFactory, limFileName, ".flim");
  lim2graph::convertBaseGraph(limFactory, graph, true, true, true, true, false);
  graphIndexer.turnOn(graph);
  if(exportRul) {
    graphsupport::buildRulToGraph(graph, rulHandler);
  }
  
  //Debug
  // graph.saveXML(common::pathRemoveExtension("base") + ".xml");
  
  // Creating empty text output file
  if(!txtOutFile.empty()) {
    std::ofstream out(txtOutFile.c_str());
    if(!out) {
      WriteMsg::write(CMSG_FAILED_TO_OPEN_FILE, txtOutFile.c_str());
    } else {
      out << "";
    }
  }
}

ResultConverter::~ResultConverter(){
  WriteMsg::write(WriteMsg::mlNormal, "\nClangTidy2Graph has finished. Some statistics:\n");
  WriteMsg::write(WriteMsg::mlNormal, "  not_defined     = %4d (Number of warnings that are not defined in our rule file and therefore thrown away)\n", not_defined);
  WriteMsg::write(WriteMsg::mlNormal, "  invalid_node    = %4d (Number of warnings that we cannot attach to any node as either their path or line/col is wrong somehow)\n", invalid_node);
  WriteMsg::write(WriteMsg::mlNormal, "  not_found       = %4d (Number of warnings that we cannot attach to any node for some other reason)\n", not_found);
  WriteMsg::write(WriteMsg::mlNormal, "  already_added   = %4d (Number of warnings that we do not add because it is already added)\n", already_added);
  WriteMsg::write(WriteMsg::mlNormal, "  unable_to_add   = %4d (Number of warnings that we are unable to add for some other reason)\n", unable_to_add);
  WriteMsg::write(WriteMsg::mlNormal, "  success         = %4d (Number of successfully added warnings)\n", success);
  WriteMsg::write(WriteMsg::mlNormal, "  num_of_warnings = %4d (Total number of warnings)\n\n", num_of_warnings);

  //WriteMsg::write(WriteMsg::mlNormal, "Number of notes: %d\n", num_notes);
}

void ResultConverter::process(const std::string& resultFileName){
  //TODO XML parsing
  loadXml(resultFileName, handler);
  //Get list of warnings.
  std::list<Warning> warnings = handler.getWarnings();
  
  num_of_warnings += warnings.size();
  for(auto warning : warnings){
    addWarning(warning);
    num_notes += warning.notes.size();
  }
  handler.clearWarnings();
}

void ResultConverter::saveResultGraph(const std::string& graphOutputFilename, bool createXMLdump) {
  graph.saveBinary(graphOutputFilename);
  if (createXMLdump) {
    graph.saveXML(common::pathRemoveExtension(graphOutputFilename) + ".xml");
  }
}

void ResultConverter::addWarning(Warning& warning){
  string ruleId;
  try{
    ruleId = rulHandler.getRuleIdByOriginalId(warning.name);
  }catch(rul::RulHandlerException &){
    WriteMsg::write(CMSG_RULE_NOT_DEFINED, warning.name.c_str());
    not_defined++;
    return;
  }
  if (!rulHandler.getIsDefined(ruleId)) {
    WriteMsg::write(CMSG_RULE_NOT_DEFINED, warning.name.c_str());
   not_defined++;
    return;
  }
  if (!rulHandler.getIsEnabled(ruleId)) {
    not_defined++;
    return; //rule is not enabled
  }
  
  list<Node> nodes;

  // Set up proper path format
  warning.file = common::pathCanonicalize(warning.file);

  // this patches up the problem of paths starting with C: here but c: in the LIM... but its not the best fix...
  LowerDriveLetterOnWindows(warning.file);

  common::changePath(warning.file, changePathFrom, changePathTo);

  if (graphIndexer.findNodesByRange(graph, warning.file, warning.line, 0, warning.line, INT_MAX, nodes)) {
    int minDist = INT_MAX;
    Node node;
    
    // Find the closest one
    for(list<Node>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
      vector<graphsupport::Position> positions;
      graphsupport::getPositionAttributes(*it, positions);
      
      int lMinDist = INT_MAX;//debug
      for(vector<graphsupport::Position>::iterator pos = positions.begin(); pos != positions.end(); ++pos){
        if(pos->path.compare(warning.file) == 0){
          //Namespace erroroknál a col position sokszor a namespace után van. Ezért a findeNodesByRande függvényt nem
          //0 col-lal hívjuk, hanem a warning-hoz tartozó értékkel, akkor lesznek olyan hibák, amelyekhez nem talál node-ot.
          //távolság számításkor ezt figyelembe kell venni.
            
          if( ((abs(warning.line - pos->line) + abs(warning.line - pos->endline)) + (abs(warning.column - pos->col) + abs(warning.column - pos->endcol))) < minDist ) {
            node = *it;
            minDist = abs(warning.line - pos->line) + abs(warning.line - pos->endline) + abs(warning.column - pos->col) + abs(warning.column - pos->endcol); 
          }
          //debug
          if( ((abs(warning.line - pos->line) + abs(warning.line - pos->endline)) + (abs(warning.column - pos->col) + abs(warning.column - pos->endcol))) < lMinDist ) {
            lMinDist = abs(warning.line - pos->line) + abs(warning.line - pos->endline) + abs(warning.column - pos->col) + abs(warning.column - pos->endcol); 
          }
          
        }
      }
      // cout << it->getUID() << ": " << lMinDist << endl; //debug
    }
    
    // cout << endl;
    //cout << "Found nodes: " << nodes.size() << endl << endl;
    
    // If the found node is an attribute, we use its parent
    if(node != Graph::invalidNode) {
      if(node.getType().getType() == graphsupport::graphconstants::NTYPE_LIM_ATTRIBUTE){
        Edge::EdgeIterator edgeIt = node.findOutEdges(Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_LOGICALTREE, Edge::edtReverse));
        if(edgeIt.hasNext()) {
          node = edgeIt.next().getToNode();
        }
      }
    }
    
    if (node != Graph::invalidNode) {
      bool warningAdded = false;
      
      // If there are notes, then we adding them as extraInfo attribute
      if( warning.notes.size() != 0){
        AttributeComposite extraInfo = graph.createAttributeComposite(graphsupport::graphconstants::ATTR_EXTRAINFO, graphsupport::graphconstants::CONTEXT_TRACE);
        for(list<Note>::iterator it = warning.notes.begin(); it != warning.notes.end(); ++it)
        {
          common::changePath(it->file, changePathFrom, changePathTo);
          AttributeComposite sl = graph.createAttributeComposite(graphsupport::graphconstants::ATTR_SOURCELINK, "");
          sl.addAttribute(graph.createAttributeString(graphsupport::graphconstants::ATTR_PATH, "", it->file));
          sl.addAttribute(graph.createAttributeInt(graphsupport::graphconstants::ATTR_LINE, "", it->line));
          sl.addAttribute(graph.createAttributeInt(graphsupport::graphconstants::ATTR_COLUMN, "", it->column));
          sl.addAttribute(graph.createAttributeInt(graphsupport::graphconstants::ATTR_ENDLINE, "", it->line));
          sl.addAttribute(graph.createAttributeInt(graphsupport::graphconstants::ATTR_ENDCOLUMN, "", it->column));
          sl.addAttribute(graph.createAttributeString(graphsupport::graphconstants::ATTR_WARNINGTEXT, "", it->message));
          extraInfo.addAttribute(sl);
        }

        warningAdded = graphsupport::addWarningOnce(graph, node, ruleId, warning.file, warning.line, warning.column, warning.line, 10000, warning.message, extraInfo, &warningCache);
      }else{
        warningAdded = graphsupport::addWarningOnce(graph, node, ruleId, warning.file, warning.line, warning.column, warning.line, 10000, warning.message, &warningCache);
      }
      if (warningAdded){
        success++;
        if(!txtOutFile.empty()) {
          std::ofstream out(txtOutFile.c_str(), std::ofstream::out | std::ofstream::app);
          if(!out) {
            WriteMsg::write(CMSG_FAILED_TO_OPEN_FILE, txtOutFile.c_str());
          }else{
            out << warning.file << "(" << warning.line << "): " << ruleId << ": " << warning.message << std::endl;
          }
        }
      }else{
        //Unable to add
        Attribute::AttributeIterator it = node.findAttributeByName(ruleId);
        if(!it.hasNext()){
          unable_to_add++;
          WriteMsg::write(CMSG_UNABLE_TO_ADD_WARNING_AT_LOCATION, warning.file.c_str(), warning.line);
        }
        else{
          already_added++;
        }
      }
      
    }
    else
    {
      //[DEBUG] a teljes else ág
      invalid_node++;
//      std::ofstream out("invalid_node.txt", std::ofstream::out | std::ofstream::app);
//      if(!out) {
//        WriteMsg::write(CMSG_FAILED_TO_OPEN_FILE, "invalid_node.txt");
//      }
//      else
//      {
//        out << warning.file << "(" << warning.line << "): " << ruleId << ": " << warning.message << std::endl;
//
//        for(list<Node>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
//          vector<graphsupport::Position> positions;
//          graphsupport::getPositionAttributes(*it, positions);
//          for(vector<graphsupport::Position>::iterator pos = positions.begin(); pos != positions.end(); ++pos){
//              out << pos->line << " (" << pos->line << " | " << pos->endline << ")" << endl;
//          }
//        }
//      }
    }
    
  }
  else
  {
    //cout << "[DEBUG] Node not found. " << endl;
    not_found++;
//    std::ofstream out("not_found.txt", std::ofstream::out | std::ofstream::app);
//    if(!out) {
//      WriteMsg::write(CMSG_FAILED_TO_OPEN_FILE, "not_found.txt");
//    } else {
//      out << warning.file << "(" << warning.line << "): " << ruleId << ": " << warning.message << std::endl;
//    }
  }
}

void ResultConverter::aggregateWarnings() {
  graphsupport::cumSum(graph, graph::Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_COMPONENT, graph::Edge::edtDirectional), true);
  graphsupport::cumSum(graph, graph::Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_COMPONENTTREE, graph::Edge::edtReverse), false);
  graphsupport::cumSum(graph, graph::Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_LOGICALTREE, graph::Edge::edtReverse), false);

  graphsupport::createGroupMetrics(graph, rulHandler);
}

//////////////////////////// Handler functions //////////////////

void Handler::beginTag(const std::string& name, const AttributeList& list){
  currentTag = name;
  if(name.compare(_DIAGNOSTIC) == 0){
    //insert new warning
    Warning warning;
    warning.line = 0;
    warning.column = 0;
    warning.file = "";
    warning.message = "";
    warning.name = "";
    warnings.push_back(warning);
    
    hasToSkip = false;
  }else if(name.compare(_DIAGNOSTIC_NOTE) == 0){
    isNote = true;
    Note note;
    note.line = 0;
    note.column = 0;
    note.file = "";
    note.message = "";

    // If the warning has an invalid line, then content handler removes it.
    // Due to that the warnings can be empty here.
    if (!warnings.empty())
      warnings.back().notes.push_back(note);
  }
}

void Handler::content(const std::string& content){
  if(!hasToSkip){
    if(currentTag.compare(_DIAGNOSTIC_LOCATION_FILE) == 0){
      if(isNote)
        warnings.back().notes.back().file = content;
      else
      warnings.back().file = content;
    }else if(currentTag.compare(_DIAGNOSTIC_LOCATION_LINE) == 0){
      //Invalid location
      if(std::stoi(content) > 0){
        if(isNote)
          warnings.back().notes.back().line = std::stoi(content);
        else
          warnings.back().line = std::stoi(content);
      }else{
        if(isNote)
          warnings.back().notes.pop_back();
        else
          warnings.pop_back();
        
        hasToSkip = true;
      }
    }else if(currentTag.compare(_DIAGNOSTIC_LOCATION_COLUMN) == 0){
      //Invalid location
      if(std::stoi(content) > 0){
        if(isNote)
          warnings.back().notes.back().column = std::stoi(content);
        else
          warnings.back().column = std::stoi(content);
      }else{
        if(isNote)
          warnings.back().notes.back().column = 0;
        else
          warnings.back().column = 0;
      }
    }else if(currentTag.compare(_DIAGNOSTIC_MSG) == 0){
      if(isNote)
        warnings.back().notes.back().message = resolveEscapeChars(content);
      else
        warnings.back().message = resolveEscapeChars(content);
    }else if(currentTag.compare(_DIAGNOSTIC_NAME) == 0){
      warnings.back().name = content;
    }
  }
}

void Handler::endTag(const std::string& name){
  currentTag = "";
  if(name.compare(_DIAGNOSTIC_NOTE) == 0)
    isNote = false;
}

std::list<Warning> Handler::getWarnings(){
   return warnings;
}

void Handler::clearWarnings(){
  warnings.clear();
}

std::string Handler::resolveEscapeChars(std::string content){
  vector<pair<regex,string>> escapeChars;
  escapeChars.push_back(make_pair(regex("&amp;"), "&"));
  escapeChars.push_back(make_pair(regex("&gt;"), ">"));
  escapeChars.push_back(make_pair(regex("&lt;"), "<"));
  escapeChars.push_back(make_pair(regex("&apos;"), "\'"));
  escapeChars.push_back(make_pair(regex("&quot;"), "\""));
  escapeChars.push_back(make_pair(regex("\\n"), "\n"));
  for(auto it : escapeChars){
          content = regex_replace(content,it.first,it.second);
  }
  return content;
}

Handler::~Handler(){}
