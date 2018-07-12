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

#include "../../inc/metrics/McCC.h"

using namespace std;
using namespace columbus::lim::asg;
using namespace columbus::graphsupport::graphconstants;

namespace columbus { namespace lim { namespace metrics {

  McCC::McCC( bool enabled, SharedContainers* shared ) : MetricHandler( "McCC", mdtInt, enabled, shared ) {

    this->registerHandler( phaseVisit, NTYPE_LIM_METHOD, limLangOther, false, [this]( NodeWrapper& node ) {

      const logical::Method& method = node.getLimNode<logical::Method>();

      // propagate the Number of Branches attribute from the LIM
      addMetric( node, (int) method.getNumberOfBranches() );

      // sum the McCC of every Method to File level
      ListIteratorAssocSourcePosition<physical::File> files = method.getIsContainedInListIteratorAssocBegin(),
                                                      filesEnd = method.getIsContainedInListIteratorAssocEnd();
      for ( ; files != filesEnd; ++files ) {
        const physical::File* file = &(*files);
        this->shared->files[file].ints[name] += max( (int) method.getNumberOfBranches() - 1, 0 );
      }

    });

    this->registerHandler( phaseFinishVisit, NTYPE_LIM_FILE, limLangOther, false, [this]( NodeWrapper& node ) {

      // Add the previously collected File level McCC to the node
      // ( Plus 1, as it should have started from 1, not 0 )
      const physical::File* file = &node.getLimNode<physical::File>();
      Info& fileInfo = this->shared->files[file];
      addMetric( node, fileInfo.ints[this->name] + 1 );
    });
  }

}}}
