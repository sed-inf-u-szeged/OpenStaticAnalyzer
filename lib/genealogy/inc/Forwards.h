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

#ifndef _GENEALOGY_Forwards_H_
#define _GENEALOGY_Forwards_H_

/**
* \file Forwards.h
* \brief Contains forward declarations of the classes.
*/

namespace columbus { namespace genealogy { 

  class Algorithm;
  class AlgorithmPreorder;
  class ReverseEdges;

  class Visitor;
  class VisitorAbstractNodes;
  class VisitorGraphml;
  class VisitorGENEALOGYML;
  class VisitorReverseEdges;
  class VisitorSave;

  template <typename T>
  class ListIterator;
  class Factory;

  class Base;
  class Project;
  class Trackable;
  class Component;
  class SourceCodeElement;
  class System;
  class Clone;
  class StructuralClone;
  class CloneClass;
  class CloneInstance;
  class DataClumpsClass;
  class DataClumps;
  class DataElement;
  class SwitchStatementClass;
  class SwitchStatement;
  class CaseLabel;

}}

#endif

