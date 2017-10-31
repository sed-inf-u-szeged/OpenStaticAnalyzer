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

#ifndef _JANFILTER_JAVA_H
#define _JANFILTER_JAVA_H

#include "java/inc/java.h"
#include <common/inc/DirectoryFilter.h>

namespace columbus { namespace java { namespace asg {

  /**
  * \brief Creates a new filter or refines the existing filter.
  */
  class JANFilter : public VisitorAbstractNodes {
  public:

    /**
    * \brief Constructor.
    * \param factory          [in] Reference to the Factory.
    * \param fltpInclPaths    [in] Needed paths.
    * \param fltpExclPaths    [in] Excluded paths.
    * \param filterRefl       [in] Filter nodes that had been built during reflection.
    */
    JANFilter(Factory &factory, DirectoryFilter& filter, const bool filterRefl);

    /**
    * \brief Destructor.
    */
    virtual ~JANFilter();

    /**
    * \brief Finalize the running of the JANFilter.
    */
    void finishVisit();

    /**
    */
    virtual void visit(const base::Base& node, bool callVirtualBase);

    /**
    * \brief Filters out subtree if the node is filterable.
    * \param node [in] The node which is visited.
    */
    virtual void visit(const struc::Member& node, bool callVirtualBase);

    /**
    * \brief Filters out subtree if the node is filterable.
    * \param node [in] The node which is visited.
    */
    virtual void visit(const struc::CompilationUnit& node, bool callVirtualBase);

    /**
    * \brief Filters out subtree if the node is filterable.
    * \param node [in] The node which is visited.
    */
    virtual void visit(const base::Comment& node, bool callVirtualBase);

    /**
    * \brief If all the members and compilation units of a package is filtered out,
    *        the package itself is filtered out as well (except the root package).
    * \param node [in] The node which is visited.
    */
    virtual void visitEnd(const struc::Package& node, bool callVirtualBase);

  private:

    /**
    * \internal
    * \brief Tells whether the node has to be filtered out or not.
    * \param node [in] The node which is examined.
    * \return Returns true if the node has to be kept and returns false if it has to be filtered.
    */
    bool keepTheNode(const base::Base& node) const;

    /** \internal \brief Reference to the Factory. */
    Factory &fact;

    /** \internal \brief Store the filter paths. */
    DirectoryFilter &filter;

    /** \internal \brief Filter nodes that had been built during reflection. */
    const bool filterRefl;

    /** \internal \brief The not visitedNodes will be filtered.*/
    std::vector<bool> visitedNodes;

  };

}}}

#endif // _JANFILTER_H_
