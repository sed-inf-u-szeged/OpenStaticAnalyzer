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
#include "../inc/Lim2GraphConverter.h"
#include "../inc/VisitorGraphConverter.h"
#include "../inc/messages.h"
#include <common/inc/WriteMessage.h>
#include <graphsupport/inc/GraphConstants.h>
#include <graphsupport/inc/Metric.h>

using namespace std;


namespace columbus { namespace lim2graph {

void convertBaseGraph(lim::asg::Factory& factory, graph::Graph& graph, bool edges, bool attributes, bool components, bool variants, bool instances /*=false*/) {
  VisitorGraphConverter vgc(factory, graph, edges, attributes, components, variants);
  lim::asg::AlgorithmPreorder ap;
  ap.setCrossEdgeToTraversal(lim::asg::edkScope_HasMember);
  if (variants) {
    ap.setCrossEdgeToTraversal(lim::asg::edkMember_Variant);
  }
  if (instances) {
    ap.setCrossEdgeToTraversal(lim::asg::edkMember_Instance);
  }
  ap.run(factory, vgc, *factory.getRoot());

  switch(factory.getLanguage()) {
    default:
    case lim::asg::limLangOther:
      graph.setHeaderInfo(graphsupport::graphconstants::HEADER_ASG_KEY, "unknown");
      break;
    case lim::asg::limLangC:
      graph.setHeaderInfo(graphsupport::graphconstants::HEADER_ASG_KEY, graphsupport::graphconstants::HEADER_ASG_VALUE_C);
      break;
    case lim::asg::limLangCpp:
      graph.setHeaderInfo(graphsupport::graphconstants::HEADER_ASG_KEY, graphsupport::graphconstants::HEADER_ASG_VALUE_CPP);
      break;
    case lim::asg::limLangJava:
      graph.setHeaderInfo(graphsupport::graphconstants::HEADER_ASG_KEY, graphsupport::graphconstants::HEADER_ASG_VALUE_JAVA);
      break;
    case lim::asg::limLangRpg:
      graph.setHeaderInfo(graphsupport::graphconstants::HEADER_ASG_KEY, graphsupport::graphconstants::HEADER_ASG_VALUE_RPG);
      break;
    case lim::asg::limLangPython:
      graph.setHeaderInfo(graphsupport::graphconstants::HEADER_ASG_KEY, graphsupport::graphconstants::HEADER_ASG_VALUE_PYTHON);
      break;
    case lim::asg::limLangCsharp:
      graph.setHeaderInfo(graphsupport::graphconstants::HEADER_ASG_KEY, graphsupport::graphconstants::HEADER_ASG_VALUE_CSHARP);
      break;
    case lim::asg::limLangJavaScript:
      graph.setHeaderInfo(graphsupport::graphconstants::HEADER_ASG_KEY, graphsupport::graphconstants::HEADER_ASG_VALUE_JAVASCRIPT);
      break;
  }
}

void convertRPGSpoolInfo(lim::asg::Factory& factory, LimOrigin& limOrigin, graph::Graph& graph) {
  for (lim::asg::Factory::const_iterator it = factory.begin(), itEnd = factory.end(); it != itEnd; ++it) {
    const lim::asg::base::Base& node = **it;
    if (lim::asg::Common::getIsClass(node)) {
      Key pathKey = limOrigin.getExtraPath(node.getId());
      if (pathKey) {
        const string& path = factory.getStringTable().get(pathKey);
        graphsupport::setStringAttribute(graph, VisitorGraphConverter::determineNodeName(node), graphsupport::graphconstants::ATTR_SPOOLFILE, path);
      }
    }
  }
}

}}
