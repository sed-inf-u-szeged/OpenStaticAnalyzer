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

#include "../inc/CsvExporter.h"
#include "../inc/Metric.h"
#include "../inc/RulBuilder.h"
#include "../inc/GraphConstants.h"
#include <common/inc/FileSup.h>
#include <io/inc/IO.h>
#include "rul/inc/RulTagString.h"
#include "../inc/messages.h"
#include <iostream>
#include <string_view>

using namespace columbus::io;
using namespace columbus::graph;
using namespace std;

namespace columbus { namespace graphsupport {

  static void exportImpactSetAll(graph::Graph& graph, const string& filename, graph::Edge::EdgeTypeSet& edgeTypes, const std::set<graph::Node>* const parentNodes) {
    CsvIO csvOut(filename, IOBase::omWrite);
    // write header information
    csvOut.writeColumn( CMSG_STAT_HEADER_NAME);
    csvOut.writeColumn( CMSG_STAT_HEADER_PATH);
    csvOut.writeColumn( CMSG_STAT_HEADER_LINE);
    csvOut.writeColumn( CMSG_STAT_HEADER_DESCRIPTION);
    csvOut.writeNewLine();
    Node::NodeIterator nodes = graph.getNodes();
    set<Node> impactedNodes;
    while(nodes.hasNext()) {
      Node node = nodes.next();
      Edge::EdgeIterator edges = node.findOutEdges(edgeTypes);
      while(edges.hasNext()) {
        Edge edge = edges.next();
        if( (parentNodes != NULL) && (parentNodes->find(edge.getFromNode()) == parentNodes->end()) ) {
          continue;
        }
        impactedNodes.insert(edge.getToNode());
      }
    }
    for(set<Node>::iterator it = impactedNodes.begin(); it != impactedNodes.end(); ++it) {
      string name = "", path = "";
      int line =0, col = 0, endLine = 0, endCol = 0;
      getNodeNameAttribute(*it, name);
      getPositionAttribute(*it, path, line, col, endLine, endCol);
      if(!name.empty()) {
        csvOut.writeColumn(name);
        csvOut.writeColumn(path);
        csvOut.writeColumn(line);
        csvOut.writeColumn( CMSG_STAT_HEADER_IMPACTED);
      }
      csvOut.writeNewLine();
    }
    csvOut.flush();
    csvOut.close();
  }

  void exportImpactSet(graph::Graph& graph, const string& filename, graph::Edge::EdgeTypeSet& edgeTypes, const std::set<graph::Node>& parentNodes) {
    exportImpactSetAll(graph, filename, edgeTypes, &parentNodes);
  }

  void exportImpactSet(graph::Graph& graph, const string& filename, graph::Edge::EdgeTypeSet& edgeTypes) {
    exportImpactSetAll(graph, filename, edgeTypes, NULL);
  }

  static string csvName(const string& fname, const string& fext, const string& nodeType) {
    return fname + "-" + nodeType + fext;
  }

  struct ColumnNameComparator {
    bool operator()(const std::string &lhs, const std::string &rhs) const noexcept {
      const auto lhs_tag = lhs.front() == '/';
      const auto rhs_tag = rhs.front() == '/';

      if (lhs_tag) {
        if (!rhs_tag) { return false; }
      } else {
        if (rhs_tag) { return true; }
      }

      return lhs < rhs;
    }
  };

  static void writeTagMetricsHeader(const std::set<std::string, ColumnNameComparator> &tags, io::CsvIO &csvHeader) {
    for (const auto &tag_name : tags) {
      auto after_last_slash_pos = tag_name.rend() - std::find(tag_name.rbegin(), tag_name.rend(), '/');
      const std::string_view last_part(tag_name.data() + after_last_slash_pos, tag_name.size() - after_last_slash_pos);
      csvHeader.writeColumn(last_part);
    }
  }

  static void writeTagMetrics(const std::set<std::string, ColumnNameComparator> &tags, const Node &node,
                              io::CsvIO &csvOut) {
    for (const auto &tag_name : tags) {
      auto tag_metric_attr_it = node.findAttributeByName(tag_name);
      if (tag_metric_attr_it.hasNext()) {
        if (auto &tag_metric_attr = tag_metric_attr_it.next(); isINVALID(tag_metric_attr)) {
          csvOut.writeColumn("");
        } else if (tag_metric_attr.getType() == Attribute::atInt) {
          csvOut.writeColumn(static_cast<AttributeInt &>(tag_metric_attr).getValue());
        } else if (tag_metric_attr.getType() == Attribute::atFloat) {
          csvOut.writeColumn(static_cast<AttributeFloat &>(tag_metric_attr).getValue());
        } else {
          csvOut.writeColumn(tag_metric_attr.getStringValue());
        }
      } else {
        csvOut.writeColumn(0);
      }
    }
  }

  static void writePositionColumns(const Node& node, io::CsvIO& csvOut, bool writeRealizationLevel = false) {
    string path;
    int line = 0, col = 0, endLine = 0, endCol = 0;
    bool realizationLevel = false, definition = false;
    getPositionAttribute(node, path, line, col, endLine, endCol, realizationLevel, definition);
    if (writeRealizationLevel) {
      if (realizationLevel) {
        if (definition)
          csvOut.writeColumn(graphconstants::ATTRVALUE_LIM_RELDEFINES);
        else
          csvOut.writeColumn(graphconstants::ATTRVALUE_LIM_RELDECLARES);
      } else
        csvOut.writeColumn("-");
    }
    csvOut.writeColumn(path);
    csvOut.writeColumn(line);
    csvOut.writeColumn(col);
    csvOut.writeColumn(endLine);
    csvOut.writeColumn(endCol);
  }


  static void writeComponents(const Node& node, io::CsvIO& csvOut) {
    string components;
    Edge::EdgeIterator componentIt = node.findOutEdges(Edge::EdgeType(graphconstants::ETYPE_LIM_COMPONENT, Edge::edtDirectional));
    while (componentIt.hasNext()) {
      Edge componentEdge = componentIt.next();
      components.append(componentEdge.getToNode().getUID());
      if (componentIt.hasNext())
        components.append(", ");
    }
    csvOut.writeColumn(components);
  }


  static const Node getParent(const Node& node, const Edge::EdgeType& edgeType) {
    Edge::EdgeIterator componentIt = node.findOutEdges(edgeType);
    if (componentIt.hasNext()) {
      return componentIt.next().getToNode();
    }
    return Graph::invalidNode;
  }

  static void writeParent(const Node& node, io::CsvIO& csvOut, const Edge::EdgeType& edgeType) {
    Node parentNode = getParent(node, edgeType);
    if (parentNode != Graph::invalidNode)
      csvOut.writeColumn(parentNode.getUID());
    else
      csvOut.writeColumn("");
  }

  static void setCsvStyle(io::CsvIO& csv, char separator, char dmark) {
    csv.setSeparator(separator);
    csv.setDecimalMark(dmark);
    csv.setQuotationMode(true);
  }

  void exportReadableMetricsCSV(graph::Graph& graph, const string& filename, char separator, char dmark) {
    string fname, fext;
    common::splitExt(filename, fname, fext);

    std::unordered_set<std::string> tag_should_summarize;
    if (auto metadata_node = graph.findNode(graphconstants::UID_RUL_TAG_METADATA);
        metadata_node != Graph::invalidNode) {
      auto metadata_attr_it = metadata_node.getAttributes();
      while (metadata_attr_it.hasNext()) {
        auto &metadata_attr = metadata_attr_it.next();
        if (metadata_attr.getType() != Attribute::atComposite) { continue; }
        if (auto summarized_it = static_cast<AttributeComposite &>(metadata_attr)
                              .findAttribute(Attribute::atString, graphconstants::ATTR_RUL_TAG_METADATA_SUMMARIZED,
                                             graphconstants::CONTEXT_RUL);
            summarized_it.hasNext() && static_cast<AttributeString &>(summarized_it.next()).getValue() ==
                                    graphconstants::ATTR_RUL_TAG_METADATA_SUMMARIZED_TRUE) {
          tag_should_summarize.insert(metadata_attr.getName());
        }
      }
    }

    const auto &asg = graph.getHeaderInfo(graphconstants::HEADER_ASG_KEY);

    // put metrics before tags
    std::map<std::string, std::set<std::string, ColumnNameComparator>> calc_of_columns;
    auto metric_nodes = graph.findNodes(graphconstants::NTYPE_RUL_METRIC);
    while (metric_nodes.hasNext()) {
      auto metric_node = metric_nodes.next();
      if (auto enabled_it = metric_node.findAttribute(Attribute::atString, graphconstants::ATTR_RUL_ENABLED,
                                                      graphconstants::CONTEXT_RUL);
          !enabled_it.hasNext() || static_cast<AttributeString &>(enabled_it.next()).getValue() != "true") {
        continue;
      }
      
      std::vector<std::string> tag_names;
      if (auto tags_it = metric_node.findAttribute(Attribute::atComposite, graphconstants::ATTR_RUL_TAGS,
                                                   graphconstants::CONTEXT_RUL);
          tags_it.hasNext()) {

        auto tag_it = static_cast<AttributeComposite &>(tags_it.next()).getAttributes();
        while (tag_it.hasNext()) {
          auto &tag = dynamic_cast<AttributeString &>(tag_it.next());
          auto [kind, value, detail] = rul::split_tag_string(tag.getValue());
          if (!kind.empty() && !value.empty()) {
            if (auto value_tag = rul::create_tag_string({kind, value});
                tag_should_summarize.find(value_tag) != tag_should_summarize.end()) {
              tag_names.push_back(std::move(value_tag));
            }

            if (!detail.empty()) {
              if (auto detail_tag = rul::create_tag_string({kind, value, detail});
                  tag_should_summarize.find(detail_tag) != tag_should_summarize.end()) {
                tag_names.push_back(std::move(detail_tag));
              }
            }

            if (kind == "internal" && value == "csv_column") { tag_names.push_back(metric_node.getUID()); }
          }
        }
      }

      if (auto calc_it = metric_node.findAttribute(Attribute::atComposite, graphconstants::ATTR_RUL_CALCULATED,
                                                   graphconstants::CONTEXT_RUL);
          calc_it.hasNext()) {
        auto &calc = static_cast<AttributeComposite &>(calc_it.next());
        auto calc_for_it = calc.findAttribute(Attribute::atString, graphconstants::ATTR_RUL_CALCULATEDFOR,
                                              graphconstants::CONTEXT_RUL);

        if (calc_for_it.hasNext()) {
          do {
            const auto &calc_for_name = static_cast<AttributeString &>(calc_for_it.next()).getValue();
            calc_of_columns[calc_for_name].insert(tag_names.begin(), tag_names.end());
          } while(calc_for_it.hasNext());
        } else {
          if (asg == graphconstants::HEADER_ASG_VALUE_JAVA) {
            // inserting empty sets if these types are not exists
            calc_of_columns[graphconstants::NTYPE_LIM_CLASS].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_ENUM].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_INTERFACE].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_ANNOTATION].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_METHOD].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_ATTRIBUTE].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_COMPONENT].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_PACKAGE].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_FILE];
            calc_of_columns[graphconstants::NTYPE_LIM_FOLDER];
            calc_of_columns[graphconstants::NTYPE_DCF_CLONECLASS];
            calc_of_columns[graphconstants::NTYPE_DCF_CLONEINSTANCE];

          } else if (asg == graphconstants::HEADER_ASG_VALUE_CPP) {
            calc_of_columns[graphconstants::NTYPE_LIM_CLASS].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_ENUM].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_INTERFACE].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_UNION].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_STRUCTURE].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_METHOD].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_FUNCTION].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_ATTRIBUTE].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_COMPONENT].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_NAMESPACE].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_FILE];
            calc_of_columns[graphconstants::NTYPE_LIM_FOLDER];
            calc_of_columns[graphconstants::NTYPE_DCF_CLONECLASS];
            calc_of_columns[graphconstants::NTYPE_DCF_CLONEINSTANCE];

          } else if (asg == graphconstants::HEADER_ASG_VALUE_C) {
            calc_of_columns[graphconstants::NTYPE_LIM_ENUM].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_STRUCTURE].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_FUNCTION].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_ATTRIBUTE].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_COMPONENT].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_NAMESPACE].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_FILE];
            calc_of_columns[graphconstants::NTYPE_LIM_FOLDER];
            calc_of_columns[graphconstants::NTYPE_DCF_CLONECLASS];
            calc_of_columns[graphconstants::NTYPE_DCF_CLONEINSTANCE];

          } else if (asg == graphconstants::HEADER_ASG_VALUE_RPG) {
            calc_of_columns[graphconstants::NTYPE_RPG_SYSTEM].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_RPG_PROGRAM].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_RPG_PROCEDURE].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_RPG_SUBROUTINE].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_COMPONENT].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_DCF_CLONECLASS];
            calc_of_columns[graphconstants::NTYPE_DCF_CLONEINSTANCE];

          } else if (asg == graphconstants::HEADER_ASG_VALUE_PYTHON) {
            calc_of_columns[graphconstants::NTYPE_LIM_CLASS].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_METHOD].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_FUNCTION].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_ATTRIBUTE].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_COMPONENT].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_PACKAGE].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_MODULE].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_FILE];
            calc_of_columns[graphconstants::NTYPE_LIM_FOLDER];
            calc_of_columns[graphconstants::NTYPE_DCF_CLONECLASS];
            calc_of_columns[graphconstants::NTYPE_DCF_CLONEINSTANCE];

          } else if (asg == graphconstants::HEADER_ASG_VALUE_CSHARP) {
            calc_of_columns[graphconstants::NTYPE_LIM_CLASS].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_ENUM].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_INTERFACE].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_STRUCTURE].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_DELEGATE].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_METHOD].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_ATTRIBUTE].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_COMPONENT].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_NAMESPACE].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_FILE];
            calc_of_columns[graphconstants::NTYPE_LIM_FOLDER];
            calc_of_columns[graphconstants::NTYPE_DCF_CLONECLASS];
            calc_of_columns[graphconstants::NTYPE_DCF_CLONEINSTANCE];

          } else if (asg == graphconstants::HEADER_ASG_VALUE_JAVASCRIPT) {
            calc_of_columns[graphconstants::NTYPE_LIM_CLASS].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_METHOD].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_FUNCTION].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_ATTRIBUTE].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_COMPONENT].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_PACKAGE].insert(tag_names.begin(), tag_names.end());
            calc_of_columns[graphconstants::NTYPE_LIM_FILE];
            calc_of_columns[graphconstants::NTYPE_LIM_FOLDER];
            calc_of_columns[graphconstants::NTYPE_DCF_CLONECLASS];
            calc_of_columns[graphconstants::NTYPE_DCF_CLONEINSTANCE];
          } else [[unlikely]] {
            throw Exception(COLUMBUS_LOCATION, CMSG_EX_UNHANDLED_ASG_TYPE(asg));
          }
        }
      }
    }



    // Create the csv file headers
    const char *const IDColumn = "ID";
    const char *const ParentColumn = "Parent";
    for (auto nodeTypeIterator = calc_of_columns.begin(); nodeTypeIterator != calc_of_columns.end(); ++nodeTypeIterator) {
      if (nodeTypeIterator->first == graphconstants::NTYPE_LIM_CLASS ||
        nodeTypeIterator->first == graphconstants::NTYPE_LIM_STRUCTURE ||
        nodeTypeIterator->first == graphconstants::NTYPE_LIM_DELEGATE ||
        nodeTypeIterator->first == graphconstants::NTYPE_LIM_UNION ||
        nodeTypeIterator->first == graphconstants::NTYPE_LIM_ENUM ||
        nodeTypeIterator->first == graphconstants::NTYPE_LIM_INTERFACE ||
        nodeTypeIterator->first == graphconstants::NTYPE_LIM_ANNOTATION ||
        nodeTypeIterator->first == graphconstants::NTYPE_LIM_METHOD ||
        nodeTypeIterator->first == graphconstants::NTYPE_LIM_FUNCTION ||
        nodeTypeIterator->first == graphconstants::NTYPE_LIM_ATTRIBUTE ||
        nodeTypeIterator->first == graphconstants::NTYPE_RPG_PROGRAM ||
        nodeTypeIterator->first == graphconstants::NTYPE_RPG_MODULE ||
        nodeTypeIterator->first == graphconstants::NTYPE_RPG_PROCEDURE ||
        nodeTypeIterator->first == graphconstants::NTYPE_RPG_SUBROUTINE ||
        nodeTypeIterator->first == graphconstants::NTYPE_LIM_MODULE)
      {
        io::CsvIO csvHeader(csvName(fname, fext, nodeTypeIterator->first), io::IOBase::omWrite);
        setCsvStyle(csvHeader, separator, dmark);
        csvHeader.writeColumn(IDColumn);
        csvHeader.writeColumn(graphconstants::ATTR_NAME);
        csvHeader.writeColumn(graphconstants::ATTR_LONGNAME);
        csvHeader.writeColumn(ParentColumn);
        csvHeader.writeColumn(graphconstants::NTYPE_LIM_COMPONENT);

        if (asg == graphconstants::HEADER_ASG_VALUE_CPP) {
          csvHeader.writeColumn(graphconstants::ATTR_REALIZATIONLEVEL);
        }
       
        csvHeader.writeColumn(graphconstants::ATTR_PATH);
        csvHeader.writeColumn(graphconstants::ATTR_LINE);
        csvHeader.writeColumn(graphconstants::ATTR_COLUMN);
        csvHeader.writeColumn(graphconstants::ATTR_ENDLINE);
        csvHeader.writeColumn(graphconstants::ATTR_ENDCOLUMN);
       
        writeTagMetricsHeader(nodeTypeIterator->second, csvHeader);
        csvHeader.writeNewLine();
        csvHeader.close();

      } else if (nodeTypeIterator->first == graphconstants::NTYPE_DCF_CLONECLASS) {
        io::CsvIO csvHeader(csvName(fname, fext, nodeTypeIterator->first), io::IOBase::omWrite);
        setCsvStyle(csvHeader, separator, dmark);
        csvHeader.writeColumn(IDColumn);
        csvHeader.writeColumn(graphconstants::ATTR_NAME);
        csvHeader.writeColumn(graphconstants::NTYPE_LIM_COMPONENT);
        writeTagMetricsHeader(nodeTypeIterator->second, csvHeader);
        csvHeader.writeNewLine();
        csvHeader.close();

      } else if (nodeTypeIterator->first == graphconstants::NTYPE_DCF_CLONEINSTANCE) {
        io::CsvIO csvHeader(csvName(fname, fext, nodeTypeIterator->first), io::IOBase::omWrite);
        setCsvStyle(csvHeader, separator, dmark);
        csvHeader.writeColumn(IDColumn);
        csvHeader.writeColumn(graphconstants::ATTR_NAME);
        csvHeader.writeColumn(ParentColumn);
        csvHeader.writeColumn(graphconstants::NTYPE_LIM_COMPONENT);

        csvHeader.writeColumn(graphconstants::ATTR_PATH);
        csvHeader.writeColumn(graphconstants::ATTR_LINE);
        csvHeader.writeColumn(graphconstants::ATTR_COLUMN);
        csvHeader.writeColumn(graphconstants::ATTR_ENDLINE);
        csvHeader.writeColumn(graphconstants::ATTR_ENDCOLUMN);

        writeTagMetricsHeader(nodeTypeIterator->second, csvHeader);
        csvHeader.writeNewLine();
        csvHeader.close();

      } else if (nodeTypeIterator->first == graphconstants::NTYPE_LIM_COMPONENT) {
        io::CsvIO csvHeader(csvName(fname, fext, nodeTypeIterator->first), io::IOBase::omWrite);
        setCsvStyle(csvHeader, separator, dmark);
        csvHeader.writeColumn(IDColumn);
        csvHeader.writeColumn(graphconstants::ATTR_NAME);
        csvHeader.writeColumn(graphconstants::ATTR_LONGNAME);
        writeTagMetricsHeader(nodeTypeIterator->second, csvHeader);
        csvHeader.writeNewLine();
        csvHeader.close();

      } else if (nodeTypeIterator->first == graphconstants::NTYPE_LIM_PACKAGE ||
        nodeTypeIterator->first == graphconstants::NTYPE_RPG_SYSTEM ||
        nodeTypeIterator->first == graphconstants::NTYPE_LIM_NAMESPACE)
      {
        io::CsvIO csvHeader(csvName(fname, fext, nodeTypeIterator->first), io::IOBase::omWrite);
        setCsvStyle(csvHeader, separator, dmark);
        csvHeader.writeColumn(IDColumn);
        csvHeader.writeColumn(graphconstants::ATTR_NAME);
        csvHeader.writeColumn(graphconstants::ATTR_LONGNAME);
        csvHeader.writeColumn(ParentColumn);
        csvHeader.writeColumn(graphconstants::NTYPE_LIM_COMPONENT);
        writeTagMetricsHeader(nodeTypeIterator->second, csvHeader);
        csvHeader.writeNewLine();
        csvHeader.close();
      } else if (nodeTypeIterator->first == graphconstants::NTYPE_LIM_FILE ||
        nodeTypeIterator->first == graphconstants::NTYPE_LIM_FOLDER)
      {
        io::CsvIO csvHeader(csvName(fname, fext, nodeTypeIterator->first), io::IOBase::omWrite);
        setCsvStyle(csvHeader, separator, dmark);
        csvHeader.writeColumn(IDColumn);
        csvHeader.writeColumn(graphconstants::ATTR_NAME);
        csvHeader.writeColumn(graphconstants::ATTR_LONGNAME);
        csvHeader.writeColumn(ParentColumn);
        writeTagMetricsHeader(nodeTypeIterator->second, csvHeader);
        csvHeader.writeNewLine();
        csvHeader.close();
      }
    }

    // Write out the metric values
    auto all_nodes = graph.getNodes();
    while (all_nodes.hasNext()) {
      Node node = all_nodes.next();
      string nodeType = node.getType().getType();
      if (nodeType == graphconstants::NTYPE_LIM_CLASS ||
        nodeType == graphconstants::NTYPE_LIM_STRUCTURE ||
        nodeType == graphconstants::NTYPE_LIM_DELEGATE ||
        nodeType == graphconstants::NTYPE_LIM_UNION ||
        nodeType == graphconstants::NTYPE_LIM_ENUM ||
        nodeType == graphconstants::NTYPE_LIM_INTERFACE ||
        nodeType == graphconstants::NTYPE_LIM_ANNOTATION ||
        nodeType == graphconstants::NTYPE_LIM_METHOD ||
        nodeType == graphconstants::NTYPE_LIM_FUNCTION ||
        nodeType == graphconstants::NTYPE_LIM_ATTRIBUTE ||
        nodeType == graphconstants::NTYPE_RPG_PROGRAM ||
        nodeType == graphconstants::NTYPE_RPG_MODULE ||
        nodeType == graphconstants::NTYPE_RPG_PROCEDURE ||
        nodeType == graphconstants::NTYPE_RPG_SUBROUTINE ||
        nodeType == graphconstants::NTYPE_LIM_MODULE)
      {
        io::CsvIO csvOut(csvName(fname, fext, nodeType), io::IOBase::omAppend);
        setCsvStyle(csvOut, separator, dmark);
        csvOut.writeColumn(node.getUID());
        string name;
        getNodeNameAttribute(node, name);
        csvOut.writeColumn(name);

        getNodeLongNameAttribute(node, name);
        csvOut.writeColumn(name);

        writeParent(node, csvOut, Edge::EdgeType(graphconstants::ETYPE_LIM_LOGICALTREE, Edge::edtReverse));

        
        writeComponents(node, csvOut);

        writePositionColumns(node, csvOut, asg == graphconstants::HEADER_ASG_VALUE_CPP);
        writeTagMetrics(calc_of_columns[nodeType], node, csvOut);
        csvOut.writeNewLine();
        csvOut.close();

      } else if (nodeType == graphconstants::NTYPE_DCF_CLONECLASS) {
        const Attribute& cloneSmellAttr = getNodeAttribute(node, Attribute::atString, graphconstants::ATTR_DCF_CLONESMELLTYPE, graphconstants::CONTEXT_ATTRIBUTE);
        if (cloneSmellAttr.getStringValue() != "cstDisappearing") {
          io::CsvIO csvOut(csvName(fname, fext, nodeType), io::IOBase::omAppend);
          setCsvStyle(csvOut, separator, dmark);
          csvOut.writeColumn(node.getUID());
          string name;
          getNodeNameAttribute(node, name);
          csvOut.writeColumn(name);
          writeComponents(node, csvOut);
          writeTagMetrics(calc_of_columns[nodeType], node, csvOut);
          csvOut.writeNewLine();
          csvOut.close();
        }
      } else if (nodeType == graphconstants::NTYPE_DCF_CLONEINSTANCE) {
        const Attribute& cloneSmellAttr = getNodeAttribute(node, Attribute::atString, graphconstants::ATTR_DCF_CLONESMELLTYPE, graphconstants::CONTEXT_ATTRIBUTE);
        bool fakeInstance = cloneSmellAttr.getStringValue() == "cstDisappearing";
        if (!fakeInstance) {
          Node parentNode = getParent(node,  Edge::EdgeType(graphconstants::ETYPE_DCF_CLONETREE, Edge::edtReverse));
          const Attribute& cloneSmellAttr = getNodeAttribute(parentNode, Attribute::atString, graphconstants::ATTR_DCF_CLONESMELLTYPE, graphconstants::CONTEXT_ATTRIBUTE);
          fakeInstance = cloneSmellAttr.getStringValue() == "cstDisappearing";
        }
        if (!fakeInstance) {
          io::CsvIO csvOut(csvName(fname, fext, nodeType), io::IOBase::omAppend);
          setCsvStyle(csvOut, separator, dmark);
          csvOut.writeColumn(node.getUID());
          string name;
          getNodeNameAttribute(node, name);
          csvOut.writeColumn(name);        
          writeParent(node, csvOut, Edge::EdgeType(graphconstants::ETYPE_DCF_CLONETREE, Edge::edtReverse));
          writeComponents(node, csvOut);
          writePositionColumns(node, csvOut);
          writeTagMetrics(calc_of_columns[nodeType], node, csvOut);
          csvOut.writeNewLine();
          csvOut.close();
        }
      } else if (nodeType == graphconstants::NTYPE_LIM_COMPONENT) {
        io::CsvIO csvOut(csvName(fname, fext, nodeType), io::IOBase::omAppend);
        setCsvStyle(csvOut, separator, dmark);
        csvOut.writeColumn(node.getUID());
        string name;
        getNodeNameAttribute(node, name);
        csvOut.writeColumn(name);

        getNodeLongNameAttribute(node, name);
        csvOut.writeColumn(name);

        writeTagMetrics(calc_of_columns[nodeType], node, csvOut);
        csvOut.writeNewLine();
        csvOut.close();

      } else if (nodeType == graphconstants::NTYPE_LIM_PACKAGE ||
        nodeType == graphconstants::NTYPE_RPG_SYSTEM ||
        nodeType == graphconstants::NTYPE_LIM_NAMESPACE)
      {
        io::CsvIO csvOut(csvName(fname, fext, nodeType), io::IOBase::omAppend);
        setCsvStyle(csvOut, separator, dmark);
        csvOut.writeColumn(node.getUID());
        string name;
        getNodeNameAttribute(node, name);
        csvOut.writeColumn(name);

        getNodeLongNameAttribute(node, name);
        csvOut.writeColumn(name);

        writeParent(node, csvOut, Edge::EdgeType(graphconstants::ETYPE_LIM_LOGICALTREE, Edge::edtReverse));
        writeComponents(node, csvOut);
        writeTagMetrics(calc_of_columns[nodeType], node, csvOut);
        csvOut.writeNewLine();
        csvOut.close();

      } else if (nodeType == graphconstants::NTYPE_LIM_FILE ||
        nodeType == graphconstants::NTYPE_LIM_FOLDER)
      {
        io::CsvIO csvOut(csvName(fname, fext, nodeType), io::IOBase::omAppend);
        setCsvStyle(csvOut, separator, dmark);
        csvOut.writeColumn(node.getUID());
        string name;
        getNodeNameAttribute(node, name);
        csvOut.writeColumn(name);

        getNodeLongNameAttribute(node, name);
        csvOut.writeColumn(name);

        writeParent(node, csvOut, Edge::EdgeType(graphconstants::ETYPE_LIM_PHYSICALTREE, Edge::edtReverse));
        writeTagMetrics(calc_of_columns[nodeType], node, csvOut);
        csvOut.writeNewLine();
        csvOut.close();

      }
    }
  }
}}
