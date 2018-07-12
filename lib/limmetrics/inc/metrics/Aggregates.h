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

#ifndef _METRICS_AGGREGATES_H_
#define _METRICS_AGGREGATES_H_

#include "../MetricHandler.h"

namespace columbus {
  namespace lim {
    namespace metrics {

      class AvgBase : public MetricHandler {
      public:
        AvgBase(const std::string& name, const std::string& a, const std::string& b, bool enabled, SharedContainers* shared);
      private:
        int findValue(NodeWrapper& node, const std::string& name);
      };



      class AvgLCOM5 : public AvgBase {
      public:
        AvgLCOM5(bool enabled, SharedContainers* shared) : AvgBase("AvgLCOM5", "TLCOM5", "TNCL", enabled, shared) {}
      };


      class AvgCBO : public AvgBase {
      public:
        AvgCBO(bool enabled, SharedContainers* shared) : AvgBase("AvgCBO", "TCBO", "TNCL", enabled, shared) {}
      };



      class AvgRFC : public AvgBase {
      public:
        AvgRFC(bool enabled, SharedContainers* shared) : AvgBase("AvgRFC", "TRFC", "TNCL", enabled, shared) {}
      };



      class AvgWMC : public AvgBase {
      public:
        AvgWMC(bool enabled, SharedContainers* shared) : AvgBase("AvgWMC", "TWMC", "TNCL", enabled, shared) {}
      };

      // Maintainability indices

      class MIBase : public MetricHandler {
      public:
        MIBase(const std::string& name, bool enabled, SharedContainers* shared);
      protected:
        virtual double calc(double hvol, int mccc, int lloc, double cd) = 0;
      };

      class MI : public MIBase {
      public:
        MI(bool enabled, SharedContainers* shared) : MIBase("MI", enabled, shared) {}
      protected:
        double calc(double hvol, int mccc, int lloc, double cd) override;
      };

      class MISEI : public MIBase {
      public:
        MISEI(bool enabled, SharedContainers* shared) : MIBase("MISEI", enabled, shared) {}
      protected:
        double calc(double hvol, int mccc, int lloc, double cd) override;
      };

      class MIMS : public MIBase {
      public:
        MIMS(bool enabled, SharedContainers* shared) : MIBase("MIMS", enabled, shared) {}
      protected:
        double calc(double hvol, int mccc, int lloc, double cd) override;
      };

      class MISM : public MIBase {
      public:
        MISM(bool enabled, SharedContainers* shared) : MIBase("MISM", enabled, shared) {}
      protected:
        double calc(double hvol, int mccc, int lloc, double cd) override;
      };
    }
  }
}

#endif
