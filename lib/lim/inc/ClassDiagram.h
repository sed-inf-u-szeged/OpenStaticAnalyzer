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

#ifndef _LIM_ClassDiagram_H_
#define _LIM_ClassDiagram_H_

#include "lim.h"
#include "ListIteratorClassDiagram.h"

namespace columbus { namespace lim { namespace asg {

  class ClassDiagram {
  public:
  
    ClassDiagram();
    // Az adott tipusu NodeKind-hoz visszaadja az osszes lehetseges kapocslatot
    // az 'edges'-ben lesz visszaadva az eredmeny
    void getAllPossibleEdges(NodeKind kind, std::set<ClassDiagramLinkKind>& edges) const;

    // Azon eltipusok, ami az adott node-nak van
    // az 'edges'-ben lesz visszaadva az eredmeny
    void getAllExistingEdges(NodeId id, std::set<ClassDiagramLinkKind>& edges) const;

    // Az osszes a modellben szereplo kind tipusu node id-je
    // az 'ids'-ben lesz visszaadva az eredmeny
    void getAllIDs(std::set<NodeId>& ids, NodeKind kind) const;

    // iterator eg bizonyos csucs (NodeId) meghatarozott tipusu kapcsolatain (ClassDiagramLinkKind)
    const ListIteratorAssocACDEdge constIteratorBegin(NodeId id, ClassDiagramLinkKind ltype) const;

    const ListIteratorAssocACDEdge constIteratorEnd(NodeId id, ClassDiagramLinkKind ltype) const;

    // run helyett
    // felepiti a modellt a VisitorClassDiagram hasznalataval
    void createClassDiagram(Factory& fact);

    static const std::pair<NodeId, ClassDiagramAttrType> resolveSimpleType(const NodeId type, const Factory& fact);

    static const std::pair<short, short> resolveMult(ClassDiagramAttrType cdt);

    // dumpolo
    // 'writer': egy IWriter implementaciora hivatkozo referencia
    // az IWriter interface egyes implementacioi kulonfele formatumokban valo dumpolasra hasznaltak
    //void dump(IWriter& writer) const;

  protected:
    /** \brief Set of ids that already have a parent. */
    std::set<NodeId> id_set;

    /** \brief Type definition to store a ListIteratorAssoc container. */
    typedef ListIteratorAssoc<base::Base, acdLinkInfo> ListIteratorAssocContainer;

    // letrehoz egy kapcsolatot 'from' es 'to' kozott a megadott parameterekkel
    // ez a metodus lecsereli a Unit/Link-en keresztuli kapcsolatfelepitest es reprezentaciot
    bool addConnection(NodeId from, NodeId to, ClassDiagramLinkKind ltype, const std::string& lname, int mullow, int mulhigh);

    // unit es link helyett
    // egy fajta kapcsolatokbol allo listat reprezental
    //typedef std::pair<ListIteratorAssocContainer::AssocContainer, ListIteratorAssocContainer::AssocIteratorContainer> ClassDiagramRelations;

    // egy egyseget reprezental
    typedef std::map<ClassDiagramLinkKind, ListIteratorAssocContainer::Container> ClassDiagramNode; // ListIterator -> sajat ListIteratorAssoc...
    typedef std::pair<ClassDiagramLinkKind, ListIteratorAssocContainer::Container> ClassDiagramNodePair;

    // ez az egyseg lista
    typedef std::map<NodeId, ClassDiagramNode> ClassDiagramContainer;
    typedef std::pair<NodeId, ClassDiagramNode> ClassDiagramPair;

    ClassDiagramContainer _model;

    // szukseges a ListIteratorAssocACDEdge letrehozasahoz
    Factory* _fact;

    ListIteratorAssocContainer::Container* emptyContainer;
    //ListIteratorAssocContainer::AssocIteratorContainer* emptyIteratorContainer;

    friend class VisitorClassDiagram;
    //friend class ListIteratorAssoc;
  };

}}} // columbus::lim::asg

#endif
