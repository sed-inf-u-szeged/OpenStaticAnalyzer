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

#include "../../inc/metrics/Aggregates.h"
#include <iostream>

#include <cmath>
#include <algorithm>

using namespace std;
using namespace columbus::lim::asg;
using namespace columbus::graphsupport::graphconstants;

namespace columbus {
  namespace lim {
    namespace metrics {

      AvgBase::AvgBase(const string& name, const string& a, const string& b, bool enabled, SharedContainers* shared) : MetricHandler(name, mdtFloat, enabled, shared)
      {

        dependencies.insert(a);
        dependencies.insert(b);

        this->registerHandler(phaseFinalize, NTYPE_LIM_PACKAGE, limLangOther, false, [this, name, a, b](NodeWrapper& node) {


          int numerator = this->findValue(node, a);
          int denominator = this->findValue(node, b);

          cout << "Package: " << node.getLimNode<base::Named>().getName() << endl;
          cout << a << " --> " << numerator << endl;
          cout << b << " --> " << denominator << endl;


          double ratio = denominator == 0 ? 0 : numerator / (double)denominator;
          addMetric(node, ratio);

        });

      }

      int AvgBase::findValue(NodeWrapper& node, const std::string & name)
      {
        const logical::Scope& scope = node.getLimNode<logical::Scope>();

        if (!this->shared) throw new Exception("columbus::lim::metrtics::AvgBase::findValue", "Shared containers is NULL");

        Info& info = this->shared->scopes.map[&scope];

        if (info.ints.find(name) != info.ints.end()) return info.ints[name];
        if (info.sets.find(name) != info.sets.end()) return (int)info.sets[name].size();
        if (info.maps.find(name) != info.maps.end()) return info.mapCount(name);
        return 0;
      }
    }
  }
}
