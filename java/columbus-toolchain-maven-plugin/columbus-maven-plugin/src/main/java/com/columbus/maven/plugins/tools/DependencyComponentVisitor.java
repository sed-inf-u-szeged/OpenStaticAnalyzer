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

package com.columbus.maven.plugins.tools;

import org.apache.maven.shared.dependency.tree.DependencyNode;


  public interface DependencyComponentVisitor
  {
      /**
       * Starts the visit to the specified dependency node.
       * 
       * @param node
       *            the dependency node to visit
       * @return <code>true</code> to visit the specified dependency node's children, <code>false</code> to skip the
       *         specified dependency node's children and proceed to its next sibling
       */
      boolean visit( DependencyComponent node );

      /**
       * Ends the visit to to the specified dependency node.
       * 
       * @param node
       *            the dependency node to visit
       * @return <code>true</code> to visit the specified dependency node's next sibling, <code>false</code> to skip
       *         the specified dependency node's next siblings and proceed to its parent
       */
      boolean endVisit( DependencyComponent node );

}
