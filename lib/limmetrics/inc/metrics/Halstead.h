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

#ifndef _METRICS_HALSTEAD_H_
#define _METRICS_HALSTEAD_H_

#include "../MetricHandler.h"

namespace columbus {
    namespace lim {
        namespace metrics {

            /**
            * Program Vocabulary = number of distinct operators + number of distinct operands
            */
            class HPV : public MetricHandler {
                public:
                    HPV(bool enabled, SharedContainers* shared);
            };

            /**
            * Program Length = total number of operators + total number of operands
            */
            class HPL : public MetricHandler {
                public:
                    HPL(bool enabled, SharedContainers* shared);
            };

            /**
            * Calculated Program Length = n1 * log2(n1) + n2 * log2(n2)
            */
            class HCPL : public MetricHandler {
            public:
                HCPL(bool enabled, SharedContainers* shared);
            };

            /**
            * Volume = PL * log1(PV)
            */
            class HVOL : public MetricHandler {
            public:
                HVOL(bool enabled, SharedContainers* shared);
            };
            
            /**
            * Difficulty = (n1/2) * (N2/n2)
            */
            class HDIF : public MetricHandler {
            public:
                HDIF(bool enabled, SharedContainers* shared);
            };

            /**
            * Effort = DIF * VOL
            */
            class HEFF : public MetricHandler {
            public:
                HEFF(bool enabled, SharedContainers* shared);
            };

            /**
            * Time required to program
            * TRP = EFF / 18 seconds
            */
            class HTRP : public MetricHandler {
            public:
                HTRP(bool enabled, SharedContainers* shared);
            };

            /**
            * Number of Delivered Bugs
            * NDB = E^(2/3)/3000
            */
            class HNDB : public MetricHandler {
            public:
                HNDB(bool enabled, SharedContainers* shared);
            };

        }
    }
}

#endif
