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

#ifndef _GENEALOGY_Common_H_
#define _GENEALOGY_Common_H_

#include "genealogy/inc/genealogy.h"

/**
* \file Common.h
* \brief Contains declaration of Common namespace.
*/

namespace columbus { namespace genealogy { 
  typedef unsigned int NodeHashType;
  /**
  * \brief Common contains general graph algorithms and common functions
  */
  namespace Common {
      /**
      * \brief Decides whether the node is Trackable or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is Trackable.
      */
      bool getIsTrackable(const Base& node);

      /**
      * \brief Decides whether the node is SourceCodeElement or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is SourceCodeElement.
      */
      bool getIsSourceCodeElement(const Base& node);

      /**
      * \brief Decides whether the node is Clone or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is Clone.
      */
      bool getIsClone(const Base& node);

      /**
      * \brief Decides whether the node is StructuralClone or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is StructuralClone.
      */
      bool getIsStructuralClone(const Base& node);

      /**
      * \brief Decides whether the 'base' is one of the base kinds (transitive) of 'what'.
      * \param what [in] The examined node kind.
      * \param base [in] The base node kind.
      * \return Returns true if 'base' is a base kind of 'what'.
      */
      bool getIsBaseClassKind(NodeKind what, NodeKind base);

      /**
      * \brief Decides whether the node is composite or not.
      * \param node [in] The node which is being examined.
      * \return Returns true if the node is composite.
      */
      bool getIsComposite(const Base& node);

      /**
      * \brief Decides whether the node is composite or not.
      * \param node [in] The node which is being examined.
      * \return Returns true if the node is not composite.
      */
      bool getIsNotComposite(const Base& node);

      /**
      * \brief Gives back the string representation of the NodeId.
      * \param nodeId [in] The NodeId.
      * \return The string representation of the nodeId given in the parameter.
      */
      const std::string toString(NodeId nodeId);

      /**
      * \brief Gives back the string representation of the CloneType kind.
      * \param kind               [in] The CloneType.
      * \throw GenealogyException If the kind is not "valid" GenealogyException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(CloneType kind);

      /**
      * \brief Gives back the string representation of the CloneSmellType kind.
      * \param kind               [in] The CloneSmellType.
      * \throw GenealogyException If the kind is not "valid" GenealogyException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(CloneSmellType kind);

      /**
      * \brief Gives back the string representation of the DataClumpsKind kind.
      * \param kind               [in] The DataClumpsKind.
      * \throw GenealogyException If the kind is not "valid" GenealogyException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(DataClumpsKind kind);

      /**
      * \brief Gives back the string representation of the NodeKind kind.
      * \param kind               [in] The NodeKind.
      * \throw GenealogyException If the kind is not "valid" GenealogyException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(NodeKind kind);

      /**
      * \brief Gives back the string representation of the EdgeKind kind.
      * \param kind               [in] The EdgeKind.
      * \throw GenealogyException If the kind is not "valid" GenealogyException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(EdgeKind kind);

      /**
      * \brief Returns true if the node exists and is not filtered out.
      * \param id [in] The examined node ID.
      * \return True if the node exists and is not filtered out.
      */
      bool getIsValid(NodeId id);

      /**
      * \brief Minimum of same type node similarity.
      */
      extern double SimilarityMinimum;

      /**
      * \brief Returns the minimum similarity value of same type nodes.
      * \return Minimum of same type node similarity.
      */
      double getSimilarityMinimum();

      /**
      * \brief Sets the minimum similarity value of same type nodes.
      * \param value [in] Minimum of same type node similarity.
      */
      void setSimilarityMinimum(double value);

      /**
      * \brief Minimum similarity for string type attributes.
      */
      extern double SimilarityMinForStrings;

      /**
      * \brief Returns the minimum similarity value for string type attributes.
      * \return Minimum similarity for string type attributes.
      */
      double getSimilarityMinForStrings();

      /**
      * \brief Sets the minimum similarity value for string type attributes.
      * \param value [in] Minimum similarity for string type attributes.
      */
      void setSimilarityMinForStrings(double value);

      /**
      * \brief Minimum similarity for AP spec edges.
      */
      extern double SimilarityMinForEdges;

      /**
      * \brief Returns the minimum similarity value for AP spec edges.
      * \return Minimum similarity for AP spec edges.
      */
      double getSimilarityMinForEdges();

      /**
      * \brief Sets the minimum similarity value for AP spec edges.
      * \param value [in] Minimum similarity for AP spec edges.
      */
      void setSimilarityMinForEdges(double value);


  } // Common


}}
#endif

