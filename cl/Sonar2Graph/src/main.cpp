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

#define PROGRAM_NAME "Sonar2Graph"
#define EXECUTABLE_NAME "Sonar2Graph"

#include "../inc/messages.h"

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>

#include <fstream>
#include <sstream>
#include <string>
#include <set>

#include <graphsupport/inc/Metric.h>
#include <graphsupport/inc/MetricSum.h>
#include <graphsupport/inc/GraphConstants.h>
#include <graphsupport/inc/RulBuilder.h>
#include <strtable/inc/RefDistributorStrTable.h>
#include <lim/inc/Factory.h>
#include <lim2graph/inc/Lim2GraphConverter.h>
#include <common/inc/WriteMessage.h>
#include <rul/inc/RulHandler.h>
#include <rul/inc/RulMD.h>
#include <MainCommon.h>

#define MAX_NUMBER_OF_DATA_ON_ONE_PAGE 500
#define MAX_NUMBER_OF_ISSUES 10000

using tcp = boost::asio::ip::tcp;

using namespace common;
using namespace std;
using namespace columbus;
using namespace columbus::graph;
using namespace columbus::lim::asg::base;
using boost::asio::ip::tcp;

namespace ssl = boost::asio::ssl;
namespace http = boost::beast::http;
namespace gs = columbus::graphsupport;
namespace pt = boost::property_tree;

/**
 * @brief Makes the API call with custom API call string.
 * @param callString [in] The API call string.
 * @return The API call result, if exception were ouccured during the api call it returns constans strings "not valid" or "not valid (Exception)".
 */
static string doApiCall(string callString);

/**
 * @brief Replaces the firs occurrence of a substring in input string.
 * @return The modified string. If the substring were not found then returns the original value.
 */
string replaceFirstOccurrence(string& s,                  // [out] The string to be search in.
                              const string& toReplace,    // [in]  The string to search.
                              const string& replaceWith); // [in]  The sting to replace the searched string with.

/**
 * @brief Adds a warning to the graph's node based on the warning's line information.
 * @return true if the addition of the warning has successfully finised, otherwise false.
 */
bool addWarningToNode(string& path,              // [in]  Path of the warning.
                      int line,                  // [in]  Start row of the warning.
                      int col,                   // [in]  Start column of the warning.
                      int endline,               // [in]  End row of the warning.
                      int endcol,                // [in]  End column of the warning.
                      const string& warningID,   // [in]  The unique ID of the warning.
                      const string& warningText, // [in]  Brief description of the warning.
                      Graph& graph);             // [out] The warning will be added to this graph.

/**
 * @brief Modifies the input string, to be capital case.
 * @param name [out] String to be modified.
 */
static void makeCapitalCase(string& name);

/**
 * @brief Extracts the number of pages of issues from the API call result.
 * @return The number of the pages of the issues.
 */
static int extractNumberOfPages(string apiCall,        // [in]  String of the api call
                                bool& isOverTheLimit); // [out] true if the number of issues is above 10000.

/**
 * @brief Calculates if the number of issues under each severity level is below or equals to 10000
 * @param severityList [in] List with the severity names.
 * @return true if the number of issues is below or equals to 10000 under each severity level.
 */
bool precalculation(list<string> severityList);

/**
 * @brief Adds all the issues from SonarQube to the graph, based on the key of the project or file, and the severity.
 * @return false if strict mode is on and the file in SonarQube conatins more than 10000 issues.
 */
bool addIssues(string commonApiCall,        // [in] Common part of the API call.
               string key,                  // [in] Key of the SonarQube project or key of the file.
               string severity,             // [in] Severity level, if severity equals to "none" then the function expects file key.
               rul::RulHandler* rulHandler, // [in] Needed for adding warnings to graph.
               Graph& graph);               // [in] The issues will be added to this graph.

/**
 * @brief Adds all the issues from SonarQube to the graph, by iterating through the project's files.
 */
void addIssuesByFile(string commonApiCall,        // [in] Common part of the API call.
                     string commonApiCallForSH,   // [in] Common part of the API call but only for SECURITY_HOTSPOT typed issues.
                     rul::RulHandler* rulHandler, // [in] Needed for adding warnings to graph.
                     Graph& graph);               // [in] The issues will be added to this graph.

/* GLOBALS */
RefDistributorStrTable strTable;
lim::asg::Factory limFact(strTable, "", columbus::lim::asg::limLangOther);
graphsupport::GraphRangeIndexer& graphIndexer = graphsupport::GraphRangeIndexer::getGraphRangeIndexerInstance();
set<string> setOfAddedRules;
list<string> severityList = { "BLOCKER", "CRITICAL", "MAJOR", "MINOR", "INFO" };
int countAddedRules = 0;
bool isHttps;
string issuesSearch = "/api/issues/search?statuses=OPEN,REOPENED,CONFIRMED&types=BUG,VULNERABILITY,CODE_SMELL&";
string issuesSearchForSH = "/api/issues/search?types=SECURITY_HOTSPOT&";
graphsupport::WarningCache warningCache;


static string host;
static string port;
static string project_key;
static string lim_path;
static string save_graph;
static string project_prefix;
static string language;
static string username;
static string password;
static string json_path;
static bool strict;
static list<string> inputFiles;

static bool ppHost(const Option *o, char *argv[]) {
  host = argv[0];
  return true;
}

static bool ppPort(const Option *o, char *argv[]) {
  port = argv[0];
  return true;
}

static bool ppProjectKey(const Option *o, char *argv[]) {
  project_key = argv[0];
  return true;
}

static bool ppLim_path(const Option *o, char *argv[]) {
  lim_path = argv[0];
  return true;
}

static bool ppGraph(const Option *o, char *argv[]) {
  save_graph = argv[0];
  return true;
}

static bool ppProjectPrefix(const Option *o, char *argv[]) {
  project_prefix = argv[0];
  return true;
}

static bool ppLanguageKey(const Option *o, char *argv[]) {
  language = argv[0];
  return true;
}

static bool ppSqUsername(const Option *o, char *argv[]) {
  username = argv[0];
  return true;
}

static bool ppSqPassword(const Option *o, char *argv[]) {
  password = argv[0];
  return true;
}

static bool ppJsonPath(const Option *o, char *argv[]) {
  json_path = argv[0];
  return true;
}

static bool ppStrict(const Option *o, char *argv[]) {
  if(strcmp(argv[0], "true") == 0) {
    strict = true;
  } else {
    strict = false;
  }
  return true;
}

static void ppFile(char *filename) {
  inputFiles.push_back(filename);
}


const Option OPTIONS_OBJ [] = {
  // options for making rul file
  { false,  "-graph",           1, "file",      0,  OT_WC,      ppGraph,          NULL,  "Path to save the graph."},
  { false,  "-lim",             1, "file",      0,  OT_WC,      ppLim_path,       NULL,  "Path of the lim file."},
  CL_SONAR2GRAPH_ARGS
  COMMON_CL_ARGS
};

int main(int argc, char** argv) {
  MAIN_BEGIN

  MainInit(argc, argv, "-");

  // Check if http or https
  if (host.find("https://") != string::npos) {
    host = replaceFirstOccurrence(host, "https://", "");
    isHttps = true;
  } else if (host.find("http://") != string::npos) {
    if (port.empty()) {
      port = "80";
    }
    host = replaceFirstOccurrence(host, "http://", "");
    isHttps = false;
  }

  string graph_name = project_key + ".graph";

  rul::RulHandler* rulHandler = new rul::RulHandler("sonar_tag_metadata.md", "Default", "eng");
  rulHandler->setToolDescription("ID", "Sonar2Graph");

  list<HeaderData*> header;
  Graph graph;

  limFact.load(lim_path, header);
  string filter_file_path = common::replaceExtension(lim_path, ".flim");

  int timeCompareResult = common::fileTimeCmp(filter_file_path, lim_path);
  if (timeCompareResult == -1)
    common::WriteMsg::write(CMSG_SONAR2GRAPH_FILTER_OLDER, filter_file_path.c_str());
  else if (timeCompareResult >= 0)
  {
    try {
      limFact.loadFilter(filter_file_path);
    } catch (const IOException&) {
      common::WriteMsg::write(CMSG_SONAR2GRAPH_FILTER_CANNOT_BE_LOADED, filter_file_path.c_str());
      return EXIT_FAILURE;
    }
  }
  // Creating the graph
  lim2graph::convertBaseGraph(limFact, graph, /*edges=*/ true, /*attributes=*/ true, /*components=*/ true, /*variants=*/ false, /*instances=*/ false);
  graphIndexer.turnOn(graph);

  bool lessThenThreshold = precalculation(severityList);
  bool addedSH = false;

  if (lessThenThreshold) {
    for (string severity_temp : severityList) {
      addIssues(issuesSearch, project_key, severity_temp, rulHandler, graph);
    }
  } else { // Get the issues form files
    addIssuesByFile(issuesSearch, issuesSearchForSH, rulHandler, graph);
    addedSH = true;
  }

  if (!addedSH) {
    bool isOverTheLimit;
    extractNumberOfPages(
      (boost::format(issuesSearchForSH + "componentKeys=%1%&languages=%2%&ps=1&p=1")
                     % project_key % language).str(), isOverTheLimit);

    if (!isOverTheLimit) {
      addIssues(issuesSearchForSH, project_key, "none", rulHandler, graph);
    } else {
      addIssuesByFile("none", issuesSearchForSH, rulHandler, graph);
    }
  }

  auto sonar_tag = rulHandler->getTagStore().create_or_get(rul::SplitTagStringView{"tool", "Sonar"});

  // Get rule from the API
  for (string warningID : setOfAddedRules) {
    rulHandler->defineMetric(warningID);
    rulHandler->createConfiguration(warningID, "Default");
    rulHandler->setIsEnabled(warningID, true);
    rulHandler->setIsVisible(warningID, true);
    rulHandler->setGroupType(warningID, "false");
    rulHandler->addTag(warningID, sonar_tag);
    rulHandler->createLanguage(warningID, "eng");
    rulHandler->setHasWarningText(warningID, true);
    rulHandler->setDescription(warningID, "");
    rulHandler->setOriginalId(warningID, warningID);

    string ruleApiCallResult = doApiCall((boost::format("/api/rules/search?rule_key=%1%")
                                                        % warningID ).str());

    pt::ptree ruleRoot;

    stringstream ruleSs;
    ruleSs << ruleApiCallResult;
    pt::read_json(ruleSs, ruleRoot);

    string htmlDesc;
    string severity;
    string name;

    // Extracting rule from JSON
    for (pt::ptree::value_type& rule : ruleRoot.get_child("rules")) {
      for (pt::ptree::value_type& rule_property : rule.second) {
        if (rule_property.first == "name") {
          name = rule_property.second.data();
        } else if (rule_property.first == "htmlDesc") {
          htmlDesc = rule_property.second.data();
        } else if (rule_property.first == "severity") {
          severity = rule_property.second.data();
          makeCapitalCase(severity);
        } else if (rule_property.first == "sysTags") {
          for (auto &tag : rule_property.second) {
            rulHandler->addTag(warningID, rul::SplitTagStringView{"collection", "Sonar", tag.second.data()});
          }
        }
      }
    }

    rulHandler->setSettingValue(warningID, "Priority", severity, true);
    rulHandler->setDisplayName(warningID, name);
    rulHandler->setHelpText(warningID, htmlDesc);
  }

  columbus::graphsupport::buildRulToGraph(graph, *rulHandler);

  graphsupport::cumSum(graph, graph::Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_COMPONENT, graph::Edge::edtDirectional), true, std::set<std::string>(), true);
  graphsupport::cumSum(graph, graph::Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_LOGICALTREE, graph::Edge::edtReverse), false);
  graphsupport::createGroupMetrics(graph, *rulHandler);

  graph.saveBinary(save_graph);

  return EXIT_SUCCESS;
  MAIN_END
}

static void makeCapitalCase(string& name) {
  if (name.empty()) {
    return;
  }

  name[0] = toupper(name[0]);
  for (size_t i = 1, len = name.size(); i < len; i++) {
    name[i] = tolower(name[i]);
  }
}

static string base64(string to_encode) {
  using namespace boost::archive::iterators;

  stringstream os;

  typedef base64_from_binary<transform_width<const char*, 6, 8>> base64_text;

  copy(base64_text(to_encode.c_str()),
                   base64_text(to_encode.c_str() + to_encode.size()),
                   ostream_iterator<char>(os));

  return os.str();
}

void addIssuesByFile(string commonApiCall, string commonApiCallForSH, rul::RulHandler* rulHandler, Graph& graph) {
  string restApiResult = doApiCall((boost::format("/api/components/tree?component=%1%&qualifiers=FIL")
                                                    % project_key).str());
  pt::ptree root;
  stringstream fileTreeSs;
  fileTreeSs << restApiResult;
  // Load the json file in this ptree
  pt::read_json(fileTreeSs, root);

  string numOfFiles;
  for (pt::ptree::value_type& component : root.get_child("paging")) {
    if (component.first == "total") {
      numOfFiles = component.second.data();
      break;
    }
  }

  int maxPage = ceil(atof(numOfFiles.c_str()) / MAX_NUMBER_OF_DATA_ON_ONE_PAGE);
  bool isSucceeded = true;
  for (int curPage = 1; curPage <= maxPage; curPage++) {

    string restApiResult = doApiCall(
      (boost::format("/api/components/tree?qualifiers=FIL&component=%1%&ps=%2%&p=%3%")
                     % project_key % MAX_NUMBER_OF_DATA_ON_ONE_PAGE % curPage).str());

    stringstream fileTreeSs;
    fileTreeSs << restApiResult;
    // Load the json file in this ptree
    pt::read_json(fileTreeSs, root);

    list<string> fileKeyList; // KEY: key of the file VALUE: number of the issues in this file

    for (pt::ptree::value_type& component : root.get_child("components")) {
      for (pt::ptree::value_type& componentProperty : component.second) {
        if (componentProperty.first == "key") {
          string fileKey = componentProperty.second.data();
          fileKeyList.push_back(fileKey);
        }
      }
    }
    for (list<string>::iterator keysIt = fileKeyList.begin(); keysIt != fileKeyList.end(); ++keysIt) {
      string key = keysIt->c_str();

      if (commonApiCall != "none") {
        if (!addIssues(commonApiCall, key, "none", rulHandler, graph) || !addIssues(commonApiCallForSH, key, "none", rulHandler, graph)) {
          isSucceeded = false;
          break;
        }
      } else {
        if (!addIssues(commonApiCallForSH, key, "none", rulHandler, graph)) {
          isSucceeded = false;
          break;
        }
      }

    }
    if (!isSucceeded) {
      break;
    }
  }
}

bool addWarningToNode(string& path,
                      int line,
                      int col,
                      int endline,
                      int endcol,
                      const string& warningID,
                      const string& warningText,
                      Graph& graph) {

  path = correctDirDivs(path);

  if (line < 0 || col < 0 ||endline < 0 || endcol < 0) {
    WriteMsg::write(CMSG_SONAR2GRAPH_WARNING_DO_NOT_HAVE_LINE_INFO, warningID.c_str(), path.c_str(), warningText.c_str());
    return false;
  }

  // The column should be indexed from 1, but in the case of SonarQube(TM) warnings, it is indexed from 0. Thats why incrementation is needed.
  col++;
  endcol++;

  list<Node> nodes;

  graphIndexer.findNodesByRange(graph, path, line, INT_MIN, endline, INT_MAX, nodes);

  int minDist = INT_MAX;
  Node node;
  for (list<Node>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
    vector<graphsupport::Position> positions;
    graphsupport::getPositionAttributes(*it, positions);
    for (vector<graphsupport::Position>::iterator pos = positions.begin(); pos != positions.end(); ++pos) {
      int dist = abs(line - pos->line) + abs(endline - pos->endline);
      if(dist < minDist) {
        node = *it;
        minDist = dist;
      }
    }
  }
  if (node == Graph::invalidNode) { // could not find the node by range, skip this warning
    WriteMsg::write(CMSG_SONAR2GRAPH_NO_NODE_FOUND_AT_PATH, warningID.c_str(), path.c_str(), line, col, endline, endcol);
    return false;
  } else {
    // if the found node is attribute, we use that parent
    if (node.getType().getType() == columbus::graphsupport::graphconstants::NTYPE_LIM_ATTRIBUTE) {
      Edge::EdgeIterator edgeIt =
        node.findOutEdges(Edge::EdgeType(columbus::graphsupport::graphconstants::ETYPE_LIM_LOGICALTREE, Edge::edtReverse));
      if (edgeIt.hasNext()) {
        node = edgeIt.next().getToNode();
      }
    }
    if (node != Graph::invalidNode &&
        !graphsupport::addWarningOnce(graph, node, warningID, path,
          line, col, endline, endcol, warningText, &warningCache)) {
      WriteMsg::write(CMSG_SONAR2GRAPH_WARNING_ALREADY_ADDED,
        warningID.c_str(), node.getUID().c_str(), path.c_str(),
        line, col, endline, endcol, warningText.c_str());
      return false;
    } else {
      return true;
    }
  }
}

string replaceFirstOccurrence(string& s,
                              const string& toReplace,
                              const string& replaceWith) {

  size_t pos = s.find(toReplace);
  if (pos == string::npos) {
    return s;
  }
  return s.replace(pos, toReplace.length(), replaceWith);
}

static int extractNumberOfPages(string apiCall, bool& isOverTheLimit) {
  pt::ptree root;
  string restApiResult = doApiCall(apiCall);

  stringstream numberOfPagesSs;
  numberOfPagesSs << restApiResult;
  // Load the json file in this ptree
  pt::read_json(numberOfPagesSs, root);

  double numberOfIssues = root.get<int>("total", 0);
  if (numberOfIssues > MAX_NUMBER_OF_ISSUES) {
    isOverTheLimit = true;
    WriteMsg::write(CMSG_SONAR2GRAPH_WARNING_GREATER_THEN, numberOfIssues, MAX_NUMBER_OF_ISSUES);
  } else {
    isOverTheLimit = false;
  }
  return ceil(numberOfIssues / MAX_NUMBER_OF_DATA_ON_ONE_PAGE);
}

bool precalculation(list<string> severityList) {
  bool isOverTheLimit = false;

  // Iterate over the map using c++11 range based for loop
  for (string severity_temp : severityList) {
    extractNumberOfPages(
      (boost::format(issuesSearch + "componentKeys=%1%&languages=%2%&ps=1&p=1&severities=%3%")
                     % project_key % language % severity_temp).str(), isOverTheLimit);

    if (isOverTheLimit) {
      return false; // we have to get issues by files
    }
  }
  return true; // all severities contain less then 10000 issue we can use the severityList
}

bool addIssues(string commonApiCall, string key, string severity,
  rul::RulHandler* rulHandler, Graph& graph) {
  string apiCallString;
  if (severity != "none") {
    apiCallString = (boost::format(commonApiCall + "componentKeys=%1%&languages=%2%&ps=%3%&p=%4%&severities=%5%")
                                   % key % language % MAX_NUMBER_OF_DATA_ON_ONE_PAGE % 1 % severity).str();
  } else {
    apiCallString = (boost::format(commonApiCall + "componentKeys=%1%&languages=%2%&ps=%3%&p=%4%")
                                   % key % language % MAX_NUMBER_OF_DATA_ON_ONE_PAGE % 1).str();
  }

  string restApiResult = doApiCall(apiCallString);
  pt::ptree root;
  stringstream issuesSs;
  issuesSs << restApiResult;
  // Load the json file in this ptree
  pt::read_json(issuesSs, root);

  int numberOfIssues = root.get<int>("total", 0);

  if (numberOfIssues == 0) {
    return true;
  } else if (numberOfIssues > MAX_NUMBER_OF_ISSUES) {
    WriteMsg::write(CMSG_SONAR2GRAPH_WARNING_GREATER_THEN_IN_FILE,
      numberOfIssues, key.c_str(), MAX_NUMBER_OF_ISSUES);
    if (strict) {
      return false;
    }
  }

  string path;
  int startLine = -1;
  int endLine = -1;
  int startOffset = -1;
  int endOffset = -1;
  string warningID;
  string warningText;

  int curPage = 2;
  do {
    // Extracting issues from JSON
    for (pt::ptree::value_type& issue : root.get_child("issues")) {
      for (pt::ptree::value_type& issue_property : issue.second) {
        if (issue_property.first == "component") {
          path = issue_property.second.data();
          replaceFirstOccurrence(path, project_key + ":", "");
          path = project_prefix + path;
        } else if (issue_property.first == "textRange") {
          for (pt::ptree::value_type& text_range : issue_property.second) {
            if (text_range.first == "startLine") {
              startLine = stoi(text_range.second.data());
            } else if (text_range.first == "endLine") {
              endLine = stoi(text_range.second.data());
            } else if (text_range.first == "startOffset") {
              startOffset = stoi(text_range.second.data());
            } else {
              endOffset = stoi(text_range.second.data());
            }
          }
        } else if (issue_property.first == "rule") {
          warningID = issue_property.second.data();
        } else if (issue_property.first == "message") {
          warningText = issue_property.second.data();
        } else if (issue_property.first == "tags") {
          std::cout << "issue tags\n";
          for (auto &tag : issue_property.second) {
            std::cout << tag.second.get_value<std::string>() << ", ";
          }
          std::cout << '\n';
        }
      }

      if (addWarningToNode(path,
                           startLine,
                           startOffset,
                           endLine,
                           endOffset,
                           warningID,
                           warningText,
                           graph)) {
        setOfAddedRules.insert(warningID);
      }

      startLine = -1;
      endLine = -1;
      startOffset = -1;
      endOffset = -1;

    }
    if (severity != "none") {
      apiCallString = (boost::format(commonApiCall + "componentKeys=%1%&languages=%2%&ps=%3%&p=%4%&severities=%5%")
                                     % key % language % MAX_NUMBER_OF_DATA_ON_ONE_PAGE % curPage % severity).str();
    } else {
      apiCallString = (boost::format(commonApiCall + "componentKeys=%1%&languages=%2%&ps=%3%&p=%4%")
                                     % key % language % MAX_NUMBER_OF_DATA_ON_ONE_PAGE % curPage).str();
    }
    restApiResult = doApiCall(apiCallString);
    stringstream ssInLoop;
    ssInLoop << restApiResult;
    // Load the json file in this ptree
    pt::read_json(ssInLoop, root);

    curPage++;

  } while (curPage <= ceil(numberOfIssues / MAX_NUMBER_OF_DATA_ON_ONE_PAGE) + 2 && curPage <= 21);
  return true;
}

bool verify_callback(bool preverified, // True if the certificate passed pre-verification.
                     ssl::verify_context& ctx // The peer certificate and other context.
                    ) {
  return true;
}

static string doApiCall(string callString) {

  string retVal = "";
  string apiCall = callString;
  int version  = 10;

  if (!isHttps) {
    // The io_context is required for all I/O
    boost::asio::io_context ioc;

    // These objects perform our I/O
    tcp::resolver resolver{ioc};
    tcp::socket socket{ioc};

    // Look up the domain name
    boost::asio::ip::basic_resolver<boost::asio::ip::tcp>::results_type results;

    results = resolver.resolve(host, port);

    // Make the connection on the IP address we get from a lookup
    boost::asio::connect(socket, results.begin(), results.end());

    // Set up an HTTP GET request message
    http::request<http::string_body> req{http::verb::get, apiCall, version};
    req.set(http::field::host, host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    if (!username.empty() && !password.empty()) {
      req.set(http::field::authorization, "Basic " + base64(username + ":" + password));
    }

    // Send the HTTP request to the remote host
    http::write(socket, req);

    // This buffer is used for reading and must be persisted
    boost::beast::flat_buffer buffer;

    // Declare a container to hold the response
    http::response<http::dynamic_body> res;

    // Receive the HTTP response
    http::read(socket, buffer, res);

    retVal = boost::beast::buffers_to_string(res.body().data());

    // Gracefully close the socket
    boost::system::error_code ec;
    socket.shutdown(tcp::socket::shutdown_both, ec);

    if (ec && ec != boost::system::errc::not_connected) {
      throw boost::system::system_error{ec};
    }
  } else {
    typedef ssl::stream<tcp::socket> ssl_socket;

    // Create a context that uses the default paths for
    // finding CA certificates.
    ssl::context ctx(ssl::context::sslv23);
    ctx.set_default_verify_paths();

    // Open a socket and connect it to the remote host.
    boost::asio::io_service io_service;
    ssl_socket sock(io_service, ctx);
    tcp::resolver resolver(io_service);
    tcp::resolver::query query(host, "https");
    boost::asio::connect(sock.lowest_layer(), resolver.resolve(query));
    sock.lowest_layer().set_option(tcp::no_delay(true));

    // Perform SSL handshake and verify the remote host's
    // certificate.
    sock.set_verify_mode(ssl::verify_peer);
    sock.set_verify_callback(verify_callback);
    sock.handshake(ssl_socket::client);
    // ... read and write as normal ...
    // Set up an HTTP GET request message
    http::request<http::string_body> req{ http::verb::get, apiCall, version };
    req.set(http::field::host, host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    if (!username.empty() && !password.empty()) {
      req.set(http::field::authorization, "Basic " + base64(username + ":" + password));
    }

    // Send the HTTP request to the remote host
    http::write(sock, req);

    // This buffer is used for reading and must be persisted
    boost::beast::flat_buffer buffer;

    // Declare a container to hold the response
    http::response<http::dynamic_body> res;

    // Receive the HTTP response
    http::read(sock, buffer, res);

    retVal = boost::beast::buffers_to_string(res.body().data());
  }
  // If we get here then the connection is closed gracefully

  return retVal;
}
