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

#ifndef _FX2G_RPC_H_
#define _FX2G_RPC_H_

#include "FxCop2Graph.h"

namespace columbus {
	namespace fxcop2graph {
		class ReportConverter {
			public:
				ReportConverter(const Config& limFileName);
				virtual ~ReportConverter();
				void buildtree(const bool exportRul);
				void saveGraph(const std::string& fileName);

				void addWarningToNode(const std::string& mangleName, const std::string& id, const std::string& group, const std::string& warningText);
				void addWarningToNode(const std::string& path, const std::string& id, const std::string& group, const std::string& warningText, int line, int endline, int col = 0, int endcol = INT_MAX);
				bool collectData(const std::vector<std::string>&);

				bool getFullPath(const std::string& path, std::string& fullPath);
				bool findPath(const columbus::lim::asg::physical::FSEntry& item);
				columbus::graph::Graph* getGraph() { return &graph; }
				void aggregateWarnings(bool createGroups);
			protected:
				Config config;
				void writeWarningLine(const std::string& id, const std::string& warningText, const std::string& path, int line, int endline, int col, int endcol);
				columbus::RefDistributorStrTable strTable;
				columbus::lim::asg::Factory limFact;
				std::string limFileName;
				columbus::rul::RulHandler* xRulhandler;

				columbus::graph::Graph graph;
				columbus::graphsupport::GraphRangeIndexer& graphIndexer;

				std::vector<std::string> pathFB;
				std::vector<std::string> pathLim;
				std::map<std::string, std::string> pathMap;
				std::string txtOutputFileName;
				graphsupport::WarningCache warningCache;
		};
	}
}

#endif
