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

#include "../../inc/metrics/Halstead.h"

using namespace std;
using namespace columbus::lim::asg;
using namespace columbus::graphsupport::graphconstants;

namespace columbus {
    namespace lim {
        namespace metrics {

            HPV::HPV(bool enabled, SharedContainers* shared) : MetricHandler("HPV", mdtInt, enabled, shared) {

                this->registerHandler(phaseVisit, NTYPE_LIM_METHOD, limLangOther, false, [this](NodeWrapper& node) {

                    const logical::Method& method = node.getLimNode<logical::Method>();

                    // propagate the Sum of Distinct Operators and Operands attribute from the LIM
                    addMetric(node, (int)method.getDistinctOperands() + (int)method.getDistinctOperators());

                });

            }



            HPL::HPL(bool enabled, SharedContainers* shared) : MetricHandler("HPL", mdtInt, enabled, shared) {

                this->registerHandler(phaseVisit, NTYPE_LIM_METHOD, limLangOther, false, [this](NodeWrapper& node) {

                    const logical::Method& method = node.getLimNode<logical::Method>();

                    // propagate the Sum of Total Operators and Total Operands attribute from the LIM
                    addMetric(node, (int)method.getTotalOperands() + (int)method.getTotalOperators());
                });
            }

            HCPL::HCPL(bool enabled, SharedContainers* shared) : MetricHandler("HCPL", mdtFloat, enabled, shared) {

                this->registerHandler(phaseVisit, NTYPE_LIM_METHOD, limLangOther, false, [this](NodeWrapper& node) {

                    const logical::Method& method = node.getLimNode<logical::Method>();

                    // calculate calculated program length and add metric
                    double n1 = method.getDistinctOperators();
                    double n2 = method.getDistinctOperands();
                    double cpl = (n1 * log2(n1)) + (n2 * log2(n2));
                    addMetric(node, cpl);

                });

            }

            HVOL::HVOL(bool enabled, SharedContainers* shared) : MetricHandler("HVOL", mdtFloat, enabled, shared) {

                this->registerHandler(phaseVisit, NTYPE_LIM_METHOD, limLangOther, false, [this](NodeWrapper& node) {

                    const logical::Method& method = node.getLimNode<logical::Method>();

                    unsigned n = method.getDistinctOperators() + method.getDistinctOperands();
                    unsigned N = method.getTotalOperators() + method.getTotalOperands();

                    double vol = N * log2(n);
                    addMetric(node, vol);

                });
            }

            HDIF::HDIF(bool enabled, SharedContainers* shared) : MetricHandler("HDIF", mdtFloat, enabled, shared) {

                this->registerHandler(phaseVisit, NTYPE_LIM_METHOD, limLangOther, false, [this](NodeWrapper& node) {

                    const logical::Method& method = node.getLimNode<logical::Method>();

                    unsigned n1 = method.getDistinctOperators();
                    unsigned n2 = method.getDistinctOperands();
                    unsigned N2 = method.getTotalOperands();

                    //null check
                    if (n2 == 0) {
                        n2 = 1;
                    }

                    double difficulty = (n1 / 2.0) * ((double)N2 / n2);
                    addMetric(node, difficulty);
                });
            }

            HEFF::HEFF(bool enabled, SharedContainers* shared) : MetricHandler("HEFF", mdtFloat, enabled, shared) {

                this->registerHandler(phaseVisit, NTYPE_LIM_METHOD, limLangOther, false, [this](NodeWrapper& node) {

                    const logical::Method& method = node.getLimNode<logical::Method>();

                    unsigned n1 = method.getDistinctOperators();
                    unsigned n2 = method.getDistinctOperands();
                    unsigned N1 = method.getTotalOperators();
                    unsigned N2 = method.getTotalOperands();

                    unsigned n = n1 + n2;
                    unsigned N = N1 + N2;

                    double vol = N * log2(n);
                    
                    //null check
                    if (n2 == 0) {
                        n2 = 1;
                    }

                    double difficulty = (n1 / 2.0) * ((double)N2 / n2);
                    double effort = difficulty * vol;

                    addMetric(node, effort);
                });
            }

            HTRP::HTRP(bool enabled, SharedContainers* shared) : MetricHandler("HTRP", mdtFloat, enabled, shared) {

                this->registerHandler(phaseVisit, NTYPE_LIM_METHOD, limLangOther, false, [this](NodeWrapper& node) {

                    const logical::Method& method = node.getLimNode<logical::Method>();

                    unsigned n1 = method.getDistinctOperators();
                    unsigned n2 = method.getDistinctOperands();
                    unsigned N1 = method.getTotalOperators();
                    unsigned N2 = method.getTotalOperands();

                    unsigned n = n1 + n2;
                    unsigned N = N1 + N2;

                    double vol = N * log2(n);
                    //null check
                    if (n2 == 0) {
                        n2 = 1;
                    }
                    double difficulty = (n1 / 2.0) * ((double)N2 / n2);
                    double effort = difficulty * vol;
                    double trp = effort / 18;

                    addMetric(node, trp);
                });
            }

            HNDB::HNDB(bool enabled, SharedContainers* shared) : MetricHandler("HNDB", mdtFloat, enabled, shared) {

                this->registerHandler(phaseVisit, NTYPE_LIM_METHOD, limLangOther, false, [this](NodeWrapper& node) {

                    const logical::Method& method = node.getLimNode<logical::Method>();

                    unsigned n1 = method.getDistinctOperators();
                    unsigned n2 = method.getDistinctOperands();
                    unsigned N1 = method.getTotalOperators();
                    unsigned N2 = method.getTotalOperands();

                    unsigned n = n1 + n2;
                    unsigned N = N1 + N2;

                    double vol = N * log2(n);
                    //null check
                    if (n2 == 0) {
                        n2 = 1;
                    }
                    double difficulty = (n1 / 2.0) * ((double)N2 / n2);
                    double effort = difficulty * vol;
                    double ndb = pow(effort, (float)2/3);

                    addMetric(node, ndb);
                });
            }

        }
    }
}
