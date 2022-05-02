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

#include <string>
#include "../inc/VisitorGraphConverter.h"
#include <graphsupport/inc/Metric.h>
#include <common/inc/WriteMessage.h>
#include <lim2graph/inc/messages.h>
#include <graphsupport/inc/GraphConstants.h>
#include <boost/algorithm/string/predicate.hpp>

using namespace std;
using namespace columbus;
using namespace graphsupport;

namespace columbus { namespace lim2graph { 

// TODO variants
VisitorGraphConverter::VisitorGraphConverter(lim::asg::Factory& factory, graph::Graph &graph, bool edges, bool attributes, bool components, bool variants, bool instances /*=false*/)
  : factory(factory),
    g(graph),
    edges(edges),
    attributes(attributes),
    components(components),
    variants(variants),
    instances(instances),
    alreadyConverted(),
    convertedVariantEdges(),
    convertedAggregateEdges(),
    convertedDeclaresEdges(),
    convertedInstanceEdges(),
    convertedComponentEdges(),
    convertedComponentComponentEdges(),
    duplicatedNodes(),
    edgesToConvert(),
    logicalRoot(graph::Graph::invalidNode)
{
  common::WriteMsg::write(CMSG_VISITORGRAPHCONVERTER);
  
  logicalRoot = g.findNode(graphconstants::UID_LOGICAL_ROOT);
  if (logicalRoot == graph::Graph::invalidNode) {
    logicalRoot = g.createNode(graphconstants::UID_LOGICAL_ROOT, graphconstants::NTYPE_ROOT);
  }
  
  physicalRoot = g.findNode(graphconstants::UID_PHYSICAL_ROOT);
  if (physicalRoot == graph::Graph::invalidNode) {
    physicalRoot = g.createNode(graphconstants::UID_PHYSICAL_ROOT, graphconstants::NTYPE_ROOT);
  }
  
}

void VisitorGraphConverter::finishVisit() {
  convertEdges();

  for (set<NodeId>::const_iterator rpIt = rootPackages.begin(); rpIt != rootPackages.end(); ++rpIt) {
    
    graph::Node gNode = g.findNode(determineNodeName(factory.getRef(*rpIt)));
    if (gNode != graph::Graph::invalidNode) {
      g.createDirectedEdge(logicalRoot,gNode , graphconstants::ETYPE_LIM_LOGICALTREE, true);
    }else {
      common::WriteMsg::write(common::WriteMsg::mlWarning,"Can't create edge");
    }
  }
}

void VisitorGraphConverter::visit(const lim::asg::base::Component& node, bool b) {

  common::WriteMsg::write(CMSG_COMPONENT,node.getId() , node.getName().c_str() );
  if (needToConvert(node)) {
    string uid = determineNodeName(node);
    graph::Node builtNode = g.findNode(uid);
    
    if (!(builtNode == graph::Graph::invalidNode)) {
      alreadyConverted.insert(make_pair(node.getId(), builtNode));
      duplicatedNodes.insert(node.getId());
      return;
    }

      graph::Node gnode;
      switch (factory.getLanguage()) {
        default:
        case lim::asg::limLangOther:
          gnode = g.createNode(determineNodeName(node), graph::Node::NodeType(graphconstants::NTYPE_LIM_COMPONENT));
          return;
        case lim::asg::limLangRpg:
          gnode = g.createNode(determineNodeName(node), graph::Node::NodeType(graphconstants::NTYPE_LIM_COMPONENT));
          break;
        case lim::asg::limLangJava:
        case lim::asg::limLangC:
        case lim::asg::limLangCpp:
        case lim::asg::limLangCsharp:
        case lim::asg::limLangPython:
        case lim::asg::limLangJavaScript:
          gnode = g.createNode(determineNodeName(node), graph::Node::NodeType(graphconstants::NTYPE_LIM_COMPONENT));
          break;
        case lim::asg::limLangFsql:
          gnode = g.createNode(determineNodeName(node), graph::Node::NodeType(graphconstants::NTYPE_LIM_MODULE));
          break;
      }

      if (attributes) {
        if (factory.getLanguage() == lim::asg::limLangCsharp) {
          addNodeNameAttribute(g, gnode, node.getShortName());
          addNodeLongNameAttribute(g, gnode, node.getName());
        } else {
          addNodeNameAttribute(g, gnode, node.getName());
          addNodeLongNameAttribute(g, gnode, lim::asg::Common::getScopedName(node));
        }

        if (factory.getLanguage() == lim::asg::limLangJava) {
          gnode.addAttribute(g.createAttributeString(graphconstants::ATTR_CHANGESETID, graphconstants::CONTEXT_ATTRIBUTE, node.getChangesetID()));
          switch (node.getAnalysisTime()) {
            case lim::asg::atkBefore:
              gnode.addAttribute(g.createAttributeString(graphconstants::ATTR_ANALYSISTIME, graphconstants::CONTEXT_ATTRIBUTE, graphconstants::ATTRVALUE_LIM_BEFORE));
              break;
            case lim::asg::atkNow:
              gnode.addAttribute(g.createAttributeString(graphconstants::ATTR_ANALYSISTIME, graphconstants::CONTEXT_ATTRIBUTE, graphconstants::ATTRVALUE_LIM_NOW));
              break;
            case lim::asg::atkNever:
              gnode.addAttribute(g.createAttributeString(graphconstants::ATTR_ANALYSISTIME, graphconstants::CONTEXT_ATTRIBUTE, graphconstants::ATTRVALUE_LIM_NEVER));
              break;
            default:
              gnode.addAttribute(g.createAttributeString(graphconstants::ATTR_ANALYSISTIME, graphconstants::CONTEXT_ATTRIBUTE, graphconstants::ATTRVALUE_INVALID));
          }
        }
      }

      if (edges) {
        for (lim::asg::ListIterator<lim::asg::base::Component> it = node.getContainsListIteratorBegin(); it != node.getContainsListIteratorEnd(); ++it) {
          if (convertedComponentComponentEdges.insert(make_pair(&node, &*it)).second) {
            edgesToConvert.push_back(edge_t(node.getId(), it->getId(), graphconstants::ETYPE_LIM_COMPONENTTREE, true, ""));
          }
        }
      }

      alreadyConverted.insert(make_pair(node.getId(), gnode));
      extraConversion(node, gnode);
  }
}

void VisitorGraphConverter::visit(const lim::asg::logical::Package& node, bool b) {
  common::WriteMsg::write(CMSG_PACKAGE ,node.getId() , node.getName().c_str(), node.getMangledName().c_str() );
  if (needToConvert(node)) {
    string uid = determineNodeName(node);
    graph::Node builtNode = g.findNode(uid);
    if (!(builtNode == graph::Graph::invalidNode)) {
      alreadyConverted.insert(make_pair(node.getId(), builtNode));
      duplicatedNodes.insert(node.getId());
      return;
    }

      graph::Node gnode;
      switch (factory.getLanguage()) {
        default:
        case lim::asg::limLangOther:
          gnode = g.createNode(determineNodeName(node), graph::Node::NodeType(graphconstants::NTYPE_LIM_ROOT));
          break;
        case lim::asg::limLangC:
        case lim::asg::limLangCpp:
          gnode = g.createNode(determineNodeName(node), graph::Node::NodeType(graphconstants::NTYPE_LIM_NAMESPACE));
          break;
        case lim::asg::limLangJava:
          gnode = g.createNode(determineNodeName(node), graph::Node::NodeType(graphconstants::NTYPE_LIM_PACKAGE));
          break;
        case lim::asg::limLangJavaScript:
          gnode = g.createNode(determineNodeName(node), graph::Node::NodeType(graphconstants::NTYPE_LIM_PACKAGE));
          break;
        case lim::asg::limLangCsharp:
          gnode = g.createNode(determineNodeName(node), graph::Node::NodeType(graphconstants::NTYPE_LIM_NAMESPACE));
          break;
        case lim::asg::limLangFsql:
          gnode = g.createNode("Global space", graph::Node::NodeType(graphconstants::NTYPE_LIM_ROOT));
          break;
        case lim::asg::limLangPython:
          if (boost::ends_with(node.getDemangledName(), "~Mo")) {
            gnode = g.createNode(determineNodeName(node), graph::Node::NodeType(graphconstants::NTYPE_LIM_MODULE));
          } else {
            gnode = g.createNode(determineNodeName(node), graph::Node::NodeType(graphconstants::NTYPE_LIM_PACKAGE));
          }
          break;
      }

      if (attributes) {
        graphsupport::addNodeNameAttribute(g, gnode, node.getName());
        graphsupport::addNodeLongNameAttribute(g, gnode, node.getDemangledName());
      }

      rootPackages.insert(node.getId());

      alreadyConverted.insert(make_pair(node.getId(), gnode));
      extraConversion(node, gnode);
  }
}

void VisitorGraphConverter::visit(const lim::asg::logical::Class& node, bool b) {
  common::WriteMsg::write(CMSG_CLASS,  node.getId(),  node.getName().c_str() , node.getMangledName().c_str() );
  if (needToConvert(node)) {
    string uid = determineNodeName(node);
    graph::Node builtNode = g.findNode(uid);
    if (!(builtNode == graph::Graph::invalidNode)) {
      alreadyConverted.insert(make_pair(node.getId(), builtNode));
      duplicatedNodes.insert(node.getId());
      return;
    }

      graph::Node gnode;
      switch (factory.getLanguage()) {
        default:
        case lim::asg::limLangOther:
          gnode = g.createNode(determineNodeName(node), graph::Node::NodeType(graphconstants::NTYPE_LIM_CLASS));
          break;
        case lim::asg::limLangRpg:
          gnode = g.createNode(determineNodeName(node), graph::Node::NodeType(graphconstants::NTYPE_RPG_PROGRAM));
          break;
        case lim::asg::limLangC:
        case lim::asg::limLangCpp:
        case lim::asg::limLangJava:
        case lim::asg::limLangCsharp:
          switch (node.getClassKind()) {
            case lim::asg::clkClass:
              gnode = g.createNode(determineNodeName(node), graph::Node::NodeType(graphconstants::NTYPE_LIM_CLASS));
              break;
            case lim::asg::clkStruct:
              gnode = g.createNode(determineNodeName(node), graph::Node::NodeType(graphconstants::NTYPE_LIM_STRUCTURE));
              break;
            case lim::asg::clkUnion:
              gnode = g.createNode(determineNodeName(node), graph::Node::NodeType(graphconstants::NTYPE_LIM_UNION));
              break;
            case lim::asg::clkInterface:
              gnode = g.createNode(determineNodeName(node), graph::Node::NodeType(graphconstants::NTYPE_LIM_INTERFACE));
              break;
            case lim::asg::clkEnum:
              gnode = g.createNode(determineNodeName(node), graph::Node::NodeType(graphconstants::NTYPE_LIM_ENUM));
              break;
            case lim::asg::clkAnnotation:
              gnode = g.createNode(determineNodeName(node), graph::Node::NodeType(graphconstants::NTYPE_LIM_ANNOTATION));
              break;
            case lim::asg::clkDelegate:
              gnode = g.createNode(determineNodeName(node), graph::Node::NodeType(graphconstants::NTYPE_LIM_DELEGATE));
              break;
            case lim::asg::clkProtocol:
              gnode = g.createNode(determineNodeName(node), graph::Node::NodeType(graphconstants::NTYPE_LIM_INTERFACE));
              break;
            case lim::asg::clkCategory:
              gnode = g.createNode(determineNodeName(node), graph::Node::NodeType(graphconstants::NTYPE_LIM_CLASS));
              break;
            case lim::asg::clkExtension:
              gnode = g.createNode(determineNodeName(node), graph::Node::NodeType(graphconstants::NTYPE_LIM_INTERFACE));
              break;
            default:
              break;
          }
          break;
        case lim::asg::limLangFsql:
          switch (node.getClassKind()) {
            case lim::asg::clkClass:
              gnode = g.createNode(determineNodeName(node), graph::Node::NodeType(graphconstants::NTYPE_LIM_SOURCEFILE));
              break;
            default:
              return;
              break;
          }
          break;
        case lim::asg::limLangPython:
          gnode = g.createNode(determineNodeName(node), graph::Node::NodeType(graphconstants::NTYPE_LIM_CLASS));
          break;
        case lim::asg::limLangJavaScript:
          gnode = g.createNode(determineNodeName(node), graph::Node::NodeType(graphconstants::NTYPE_LIM_CLASS));
          break;
      }

      if (attributes) {
        graphsupport::addNodeNameAttribute(g, gnode, node.getName());
        graphsupport::addNodeLongNameAttribute(g, gnode, node.getDemangledName());
        if (factory.getLanguage() == lim::asg::limLangJava ||
            factory.getLanguage() == lim::asg::limLangCpp ||
            factory.getLanguage() == lim::asg::limLangC ||
            factory.getLanguage() == lim::asg::limLangCsharp ||
            factory.getLanguage() == lim::asg::limLangJavaScript)
        {
          graphsupport::setAnonymousAttribute(g, gnode, node.getIsAnonymous());
        }
      }

      alreadyConverted.insert(make_pair(node.getId(), gnode));
      extraConversion(node, gnode);
  }
}

void VisitorGraphConverter::visit(const lim::asg::logical::Method& node, bool b) {
  common::WriteMsg::write(CMSG_METHODE,node.getId() , node.getName().c_str() , node.getMangledName().c_str() );
  if (needToConvert(node)) {
    string uid = determineNodeName(node);
    graph::Node builtNode = g.findNode(uid);
    if (!(builtNode == graph::Graph::invalidNode)) {
      alreadyConverted.insert(make_pair(node.getId(), builtNode));
      duplicatedNodes.insert(node.getId());
      return;
    }

      graph::Node gnode;
      switch (factory.getLanguage()) {
        default:
        case lim::asg::limLangOther:
          gnode = g.createNode(determineNodeName(node), graph::Node::NodeType(graphconstants::NTYPE_LIM_METHOD));

          break;
        case lim::asg::limLangRpg:{
            string nodeType;
            if (node.getMethodKind() == lim::asg::mekSubroutine) {
              nodeType = graphconstants::NTYPE_RPG_SUBROUTINE;
            } else {
              nodeType = graphconstants::NTYPE_RPG_PROCEDURE;
            }
            gnode = g.createNode(determineNodeName(node), graph::Node::NodeType(nodeType));
          }
          break;
        case lim::asg::limLangC:
          gnode = g.createNode(determineNodeName(node), graph::Node::NodeType(graphconstants::NTYPE_LIM_FUNCTION));
          break;
        case lim::asg::limLangCpp:
        case lim::asg::limLangPython:
        case lim::asg::limLangJavaScript:
          {
            string nodeType = graphconstants::NTYPE_LIM_FUNCTION;
            const lim::asg::ReverseEdges& revEdges = factory.getReverseEdges();
            lim::asg::ListIterator<lim::asg::base::Base> it = revEdges.constIteratorBegin(node.getId(), lim::asg::edkScope_HasMember);
            if (it != revEdges.constIteratorEnd(node.getId(), lim::asg::edkScope_HasMember)) {
              if (lim::asg::Common::getIsClass(*it)) {
                nodeType = graphconstants::NTYPE_LIM_METHOD;
              }
            }
            gnode = g.createNode(determineNodeName(node), graph::Node::NodeType(nodeType));
          }
          break;
        case lim::asg::limLangJava:
        case lim::asg::limLangCsharp:
          gnode = g.createNode(determineNodeName(node), graph::Node::NodeType(graphconstants::NTYPE_LIM_METHOD));
          break;
        case lim::asg::limLangFsql:
          switch(node.getMethodKind()) {
            case lim::asg::mekNormal:
              gnode = g.createNode(determineNodeName(node), graph::Node::NodeType(graphconstants::NTYPE_LIM_PROCEDURE));
            break;
            default:
              return;
            break;
          }
          break;
      }

      if (attributes) {
        graphsupport::addNodeNameAttribute(g, gnode, node.getName());
        graphsupport::addNodeLongNameAttribute(g, gnode, node.getDemangledName());

        if (factory.getLanguage() == lim::asg::limLangJava ||
            factory.getLanguage() == lim::asg::limLangCpp ||
            factory.getLanguage() == lim::asg::limLangC ||
            factory.getLanguage() == lim::asg::limLangCsharp ||
            factory.getLanguage() == lim::asg::limLangJavaScript)
        {
          graphsupport::setAnonymousAttribute(g, gnode, node.getIsAnonymous());
        }
      }

      alreadyConverted.insert(make_pair(node.getId(), gnode));
      extraConversion(node, gnode);
  }

}

void VisitorGraphConverter::visit(const lim::asg::logical::Attribute& node, bool b) {
  common::WriteMsg::write(CMSG_ATTRIBUTE, node.getId() , node.getName().c_str() , node.getMangledName().c_str() );
  if (needToConvert(node)) {
    string uid = determineNodeName(node);
    graph::Node builtNode = g.findNode(uid);
    if (!(builtNode == graph::Graph::invalidNode)) {
      alreadyConverted.insert(make_pair(node.getId(), builtNode));
      duplicatedNodes.insert(node.getId());
      return;
    }

    graph::Node gnode;
    gnode = g.createNode(determineNodeName(node), graph::Node::NodeType(graphconstants::NTYPE_LIM_ATTRIBUTE));

    if (attributes) {
      graphsupport::addNodeNameAttribute(g, gnode, node.getName());
      graphsupport::addNodeLongNameAttribute(g, gnode, node.getDemangledName());
    }

    alreadyConverted.insert(make_pair(node.getId(), gnode));
    extraConversion(node, gnode);
  }
}

void VisitorGraphConverter::visit(const lim::asg::physical::FileSystem& node, bool b) {
  graph::Node fileSystemNode = g.createNode(determineNodeName(node), graph::Node::NodeType(graphconstants::NTYPE_LIM_FILESYSTEM));
  g.createDirectedEdge(physicalRoot, fileSystemNode, graphconstants::ETYPE_LIM_PHYSICALTREE, true);
  if (attributes) {
    graphsupport::addNodeNameAttribute(g, fileSystemNode, node.getName());
    graphsupport::addNodeLongNameAttribute(g, fileSystemNode, node.getName());
  }
}

void VisitorGraphConverter::visitMember_BelongsTo(const lim::asg::logical::Member& begin, const lim::asg::base::Component& end) {
  if (edges && components) {
    if (convertedComponentEdges.insert(make_pair(&end, &begin)).second) {
      edgesToConvert.push_back(edge_t(begin.getId(), end.getId(), graphconstants::ETYPE_LIM_COMPONENT, true, ""));
    }
  }
}

void VisitorGraphConverter::visitScope_HasMember(const lim::asg::logical::Scope& begin, const lim::asg::logical::Member& end) {
  if (edges) {
    if (duplicatedNodes.find(end.getId()) == duplicatedNodes.end()) {
      edgesToConvert.push_back(edge_t(begin.getId(), end.getId(), graphconstants::ETYPE_LIM_LOGICALTREE, true, ""));
    }
  }
}


void VisitorGraphConverter::visitEndScope_HasMember(const lim::asg::logical::Scope& begin, const lim::asg::logical::Member& end) {
  if (lim::asg::Common::getIsPackage(end))
    rootPackages.erase(end.getId());
}

void VisitorGraphConverter::visitMember_Variant(const lim::asg::logical::Member& begin, const lim::asg::logical::Member& end) {
  if (edges && variants) {
    if (convertedVariantEdges.insert(make_pair(&begin, &end)).second) {
      edgesToConvert.push_back(edge_t(begin.getId(), end.getId(), graphconstants::ETYPE_LIM_VARIANT, true, ""));
    }
  }
}

void VisitorGraphConverter::visitMember_Aggregated(const lim::asg::logical::Member& begin, const lim::asg::logical::Member& end) {
  if (edges && variants) {
    if (convertedAggregateEdges.insert(make_pair(&begin, &end)).second) {
      edgesToConvert.push_back(edge_t(begin.getId(), end.getId(), graphconstants::ETYPE_LIM_AGGREGATED, true, ""));
    }
  }
}

void VisitorGraphConverter::visitMember_Declares(const lim::asg::logical::Member& begin, const lim::asg::logical::Member& end) {
  if (edges) {
    if (convertedDeclaresEdges.insert(make_pair(&begin, &end)).second) {
      edgesToConvert.push_back(edge_t(begin.getId(), end.getId(), graphconstants::ETYPE_LIM_DECLARES, true, ""));
    }
  }
}

void VisitorGraphConverter::visitMember_Instance(const lim::asg::logical::Member& begin, const lim::asg::logical::Member& end) {
  if (edges && instances) {
    if (convertedInstanceEdges.insert(make_pair(&begin, &end)).second) {
      edgesToConvert.push_back(edge_t(begin.getId(), end.getId(), graphconstants::ETYPE_LIM_INSTANCE, true, ""));
    }
  }
}

void VisitorGraphConverter::visitNamed_DependsOn(const lim::asg::base::Named& begin, const lim::asg::base::Named& end, const std::string& ac) {
  if (edges) {
    if (convertedDependsOnEdges.insert(make_pair(&begin, &end)).second) {
      edgesToConvert.push_back(edge_t(begin.getId(), end.getId(), graphconstants::ETYPE_LIM_DEPENDSON, true, ac));
    }
  }
}

void VisitorGraphConverter::buildPhysicalTree(const lim::asg::base::Named& begin, const lim::asg::base::Named& end) {
  if  (factory.getLanguage() !=  lim::asg::limLangRpg) {
    graph::Node fsEntryNode;

    if (lim::asg::Common::getIsFolder(end))
      fsEntryNode = g.createNode(determineNodeName(end), graph::Node::NodeType(graphconstants::NTYPE_LIM_FOLDER));
    else if (lim::asg::Common::getIsFile(end))
      fsEntryNode = g.createNode(determineNodeName(end), graph::Node::NodeType(graphconstants::NTYPE_LIM_FILE));
    else
      return;

    if (attributes) {
      graphsupport::addNodeNameAttribute(g, fsEntryNode, end.getName());
      graphsupport::addNodeLongNameAttribute(g, fsEntryNode, lim::asg::Common::getFullPath(dynamic_cast<const lim::asg::physical::FSEntry&>(end), '/'));
    }

    if (edges)
      g.createDirectedEdge(g.findNode(determineNodeName(begin)), fsEntryNode, graphconstants::ETYPE_LIM_PHYSICALTREE, true);
  }
}

void VisitorGraphConverter::visitFileSystem_HasFSEntry(const lim::asg::physical::FileSystem& begin, const lim::asg::physical::FSEntry& end) {
  buildPhysicalTree(begin, end);
}

void VisitorGraphConverter::visitFolder_Contains(const lim::asg::physical::Folder& begin, const lim::asg::physical::FSEntry& end) {
  buildPhysicalTree(begin, end);
}



void VisitorGraphConverter::extraConversion(const lim::asg::base::Base &node, graph::Node& gnode) {
  if (attributes) {
    if (lim::asg::Common::getIsMember(node)) {
      const lim::asg::logical::Member& memberNode = static_cast<const lim::asg::logical::Member&>(node);
      for (lim::asg::ListIteratorAssocSourcePosition<lim::asg::physical::File> it = memberNode.getIsContainedInListIteratorAssocBegin(); it != memberNode.getIsContainedInListIteratorAssocEnd(); ++it) {
        const lim::asg::SourcePosition& position = it.getAssocClass();
        string path = lim::asg::Common::getFullPath(*it);
        graphsupport::addPositionAttribute(g, gnode, path, position.getLine(), position.getColumn(), position.getEndLine(), position.getEndColumn(), true, position.getRealizationLevel() == lim::asg::relDefines );
      }
    }
  }
}

const std::string VisitorGraphConverter::determineNodeName(const lim::asg::base::Base &node)
{
  return determineNodeName(node.getId());
}

const std::string VisitorGraphConverter::determineNodeName(NodeId nodeId)
{
  return "L" + std::to_string(nodeId);
}


bool VisitorGraphConverter::needToConvert(const lim::asg::base::Base &node) const {
  if (lim::asg::Common::getIsComponent(node))
    return components;
  return true;
}

void VisitorGraphConverter::convertEdges() {
  if (!edges)
    return;

  for (std::list<edge_t>::iterator it = edgesToConvert.begin(); it != edgesToConvert.end(); ++it) {
    NodeMap::const_iterator from = alreadyConverted.find(it->fromId);
    NodeMap::const_iterator to = alreadyConverted.find(it->toId);
    if (from != alreadyConverted.end() && to != alreadyConverted.end()) {
      graph::Edge edge = g.createDirectedEdge(from->second, to->second, it->edgeType, it->reverse);
      if (!it->edgeAttr.empty()) 
        edge.addAttribute(g.createAttributeString(graphconstants::ATTR_DEPENDENCYTYPE, graphconstants::CONTEXT_ATTRIBUTE, it->edgeAttr));
    }
  }

  edgesToConvert.clear();
}




}}
