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

      MIBase::MIBase(const std::string& name, bool enabled, SharedContainers* shared) : MetricHandler(name, mdtFloat, enabled, shared)
      {
        dependencies.insert("HVOL");
        dependencies.insert("McCC");
        dependencies.insert("LLOC");
        dependencies.insert("CD");

        this->registerHandler(phaseVisitEnd, NTYPE_LIM_METHOD, limLangOther, false, [this](NodeWrapper& node) {

          double hvol = node.getFloatMetric("HVOL");
          int mccc = node.getIntMetric("McCC");
          int lloc = node.getIntMetric("LLOC");
          double cd = node.getFloatMetric("CD");

          double mi = 0;
          if (hvol > 0 && lloc > 0) {
            mi = this->calc(hvol, mccc, lloc, cd);
          }

          addMetric(node, mi);

        });
      }

      double MI::calc(double hvol, int mccc, int lloc, double cd)
      {
        return 171 - 5.2 * log(hvol) - 0.23 * mccc - 16.2 * log(lloc);
      }

      double MISEI::calc(double hvol, int mccc, int lloc, double cd)
      {
        return 171 - 5.2 * log2(hvol) - 0.23 * mccc - 16.2 * log2(lloc) + 50 * sin(sqrt(2.4 * cd));
      }

      double MIMS::calc(double hvol, int mccc, int lloc, double cd)
      {
        return max(.0, (171 - 5.2 * log(hvol) - 0.23 * mccc - 16.2 * log(lloc)) * 100 / 171);
      }

      double MISM::calc(double hvol, int mccc, int lloc, double cd)
      {
        return max(.0, (171 - 5.2 * log2(hvol) - 0.23 * mccc - 16.2 * log2(lloc) + 50 * sin(sqrt(2.4 * cd))) * 100 / 171);
      }
    }
  }
}
