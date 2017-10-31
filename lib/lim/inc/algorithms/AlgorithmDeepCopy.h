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

#ifndef _LIM_ALGORITHMDEEPCOPY_H_
#define _LIM_ALGORITHMDEEPCOPY_H_

#include "lim/inc/lim.h"

#include <map>
#include <set>

/**
* \file AlgorithmDeepCopy.h
* \brief Contains the class `AlgorithmDeepCopy' which implements deep-copying of an arbitary subtree of an ASG.
*/

namespace columbus { namespace lim { namespace asg {
  /**
  * \brief Implements the deep-copying of a part of the ASG.
  */
  class AlgorithmDeepCopy: public Algorithm {
    private:
      /** \internal \brief The source factory of the ASG. */
      Factory& srcFact;
    private:
      /** \internal \brief The target factory of the ASG. */
      Factory& targetFact;
      /** \internal \brief The id of the node identifying the subtree to be copied. */
      NodeId what;
      /** \internal \brief The last NodeId which was returned by the Factory::createNode method.  */
      base::Base* lastNode;
      /** \internal \brief The cross-reference between the old nodes and the already copied ones. */
      std::map<const base::Base*,base::Base*>& mapped_nodes;
      /**
      * \brief Disable copy of object.
      */
      AlgorithmDeepCopy(const AlgorithmDeepCopy&);

      /**
      * \brief Disable copy of object.
      */
      AlgorithmDeepCopy& operator=(const AlgorithmDeepCopy&);

    public:
      /**
      * \brief Constructor.
      * \param what [in] The id of the node which is to be copied.
      * \param srcFact [in] The source factory belonging to the ASG.
      * \param targetFact [in] The target factory belonging to the ASG.
      * \param mapped_nodes [in] A map (NodeId->NodeId) to store the bijection of original and cloned nodes.
      */
      AlgorithmDeepCopy(NodeId what, Factory& srcFact, Factory& targetFact, std::map<const base::Base*, base::Base*>& mapped_nodes);

      /**
      * \brief Virtual destructor.
      */
      virtual ~AlgorithmDeepCopy();

      /**
      * \brief Executes the cloning algorithm. Returns the NodeId of the newly created copy of the required node
      */
      base::Base* clone();

      /**
      * \brief Returns the mapping between the original subtree and the cloned one.
      */
      std::map<const base::Base*,base::Base* >& getMapping();
    private:
      base::Base* createNode(const base::Base* oldNode, NodeKind ndk);
      base::Base* clone(const base::Base* old);
      base::Base* getMappedNode(const base::Base* old);
      void clone(base::Base* dest, const base::Base* src);
      void clone(base::Comment* dest, const base::Comment* src);
      void clone(base::Component* dest, const base::Component* src);
      void clone(base::ControlFlowBlock* dest, const base::ControlFlowBlock* src);
      void clone(base::Named* dest, const base::Named* src);
      void clone(logical::Attribute* dest, const logical::Attribute* src);
      void clone(logical::AttributeAccess* dest, const logical::AttributeAccess* src);
      void clone(logical::Class* dest, const logical::Class* src);
      void clone(logical::ClassGeneric* dest, const logical::ClassGeneric* src);
      void clone(logical::ClassGenericInstance* dest, const logical::ClassGenericInstance* src);
      void clone(logical::ClassGenericSpec* dest, const logical::ClassGenericSpec* src);
      void clone(logical::Friendship* dest, const logical::Friendship* src);
      void clone(logical::GenericParameter* dest, const logical::GenericParameter* src);
      void clone(logical::Member* dest, const logical::Member* src);
      void clone(logical::Method* dest, const logical::Method* src);
      void clone(logical::MethodCall* dest, const logical::MethodCall* src);
      void clone(logical::MethodGeneric* dest, const logical::MethodGeneric* src);
      void clone(logical::MethodGenericInstance* dest, const logical::MethodGenericInstance* src);
      void clone(logical::MethodGenericSpec* dest, const logical::MethodGenericSpec* src);
      void clone(logical::Package* dest, const logical::Package* src);
      void clone(logical::Parameter* dest, const logical::Parameter* src);
      void clone(logical::Scope* dest, const logical::Scope* src);
      void clone(physical::FSEntry* dest, const physical::FSEntry* src);
      void clone(physical::File* dest, const physical::File* src);
      void clone(physical::FileSystem* dest, const physical::FileSystem* src);
      void clone(physical::Folder* dest, const physical::Folder* src);
      void clone(type::SimpleType* dest, const type::SimpleType* src);
      void clone(type::Type* dest, const type::Type* src);
      void clone(type::TypeFormer* dest, const type::TypeFormer* src);
      void clone(type::TypeFormerArray* dest, const type::TypeFormerArray* src);
      void clone(type::TypeFormerMethod* dest, const type::TypeFormerMethod* src);
      void clone(type::TypeFormerNonType* dest, const type::TypeFormerNonType* src);
      void clone(type::TypeFormerPointer* dest, const type::TypeFormerPointer* src);
      void clone(type::TypeFormerType* dest, const type::TypeFormerType* src);
  }; // AlgorithmDeepCopy


}}}
#endif

