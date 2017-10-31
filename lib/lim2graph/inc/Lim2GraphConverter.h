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

#ifndef _LIM2graph_GRAPHCONVERTER_H_
#define _LIM2graph_GRAPHCONVERTER_H_

#include "lim/inc/lim.h"
#include "graph/inc/graph.h"

/**
* \file GraphConverter.h
* \brief Contains declaration of graph converter functions.
*/

namespace columbus { namespace lim2graph { 
      /**
      * \brief Function to convert the ASG to graph .
      * \param factory [in] The factory of the ASG.
      * \param graph   [in] The graph into the ASG will be converted.
      */
      void convertBaseGraph(lim::asg::Factory& factory, graph::Graph& graph, bool edges, bool attributes, bool components, bool variants, bool instances = false);

      /**
      * \brief Function to convert RPG spool info into the graph.
      * \param factory   [in] The factory of the ASG.
      * \param limOrigin [in] The lim origin.
      * \param graph     [in] The graph.
      */
      void convertRPGSpoolInfo(lim::asg::Factory& factory, LimOrigin& limOrigin, graph::Graph& graph);


}}
#endif

