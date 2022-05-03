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

#include "lim/inc/lim.h"
#include "common/inc/WriteMessage.h"

using namespace std;
using namespace common;

namespace columbus {
namespace lim {
namespace asg {

ClassDiagram::ClassDiagram(){
  emptyContainer = new ListIteratorAssocContainer::Container();
}

void ClassDiagram::getAllPossibleEdges(NodeKind kind, set<ClassDiagramLinkKind>& edges) const {
  edges.clear();
  switch (kind) {
    case ndkClass:
      edges.insert(cdlUnknown);
      edges.insert(cdlAssoc);
      edges.insert(cdlAggregatedBy);
      edges.insert(cdlAggregates);
      edges.insert(cdlComposedBy);
      edges.insert(cdlComposes);
      edges.insert(cdlParent);
      edges.insert(cdlChild);
      edges.insert(cdlRealizedBy);
      edges.insert(cdlRealizes);
      // a tartalmazott attributumok es metodusokhoz vezeto eltipus
      edges.insert(cdlAOwns);
      edges.insert(cdlMOwns);
      break;

    case ndkMethod:
      edges.insert(cdlUnknown);
      edges.insert(cdlAssoc);
      edges.insert(cdlRealizedBy);
      edges.insert(cdlRealizes);
      // a tartalmazohoz vezeto eltipus
      edges.insert(cdlMOwnedBy);
      // a tartalmazott lokalis valtozokhoz vezeto eltipus
      edges.insert(cdlAOwns);
      // a visszateresi ertek tipusahoz vezeto eltipus
      edges.insert(cdlHasType);
      break;

    case ndkAttribute:
      edges.insert(cdlUnknown);
      edges.insert(cdlAssoc);
      edges.insert(cdlAOwnedBy);
      edges.insert(cdlHasType);
      break;

    default:
      edges.insert(cdlUnknown);
      edges.insert(cdlAssoc);
      break;
  }
}

void ClassDiagram::getAllExistingEdges(NodeId id, std::set<ClassDiagramLinkKind>& edges) const {
  edges.clear();
  ClassDiagramContainer::const_iterator iter = _model.find(id);
  if (iter != _model.end())
  {
    ClassDiagramNode::const_iterator niter = iter->second.begin();
    ClassDiagramNode::const_iterator nend = iter->second.end();
    while (niter != nend)
    {
      edges.insert(niter->first);
      ++niter;
    }
  }
}

void ClassDiagram::getAllIDs(std::set<NodeId>& ids, NodeKind kind) const {
  ids.clear();
  ClassDiagramContainer::const_iterator iter, end;
  NodeId id;
  for (iter = _model.begin(), end = _model.end(); iter != end; ++iter)
  {
    id = iter->first;
    if (_fact->getExist(id))
    {
      if ((_fact->getRef(id).getNodeKind()) == kind)
      {
        ids.insert(id);
      }
    }
  }
}

const ListIteratorAssocACDEdge ClassDiagram::constIteratorBegin(NodeId id, ClassDiagramLinkKind ltype) const {
  ClassDiagramContainer::const_iterator iter = _model.find(id);
  if (iter == _model.end())
  {
    // id not found, returning empty iterator
    return ListIteratorAssocACDEdge(emptyContainer, _fact, true);
  }

  ClassDiagramNode::const_iterator niter = iter->second.find(ltype);
  if (niter == iter->second.end())
  {
    // id found but ltype not found, returning empty iterator
    return ListIteratorAssocACDEdge(emptyContainer, _fact, true);
  }

  // both id and ltype found
  return ListIteratorAssocACDEdge((ListIteratorAssocContainer::Container*) &(niter->second), _fact, true);
}

const ListIteratorAssocACDEdge ClassDiagram::constIteratorEnd(NodeId id, ClassDiagramLinkKind ltype) const {
  ClassDiagramContainer::const_iterator iter = _model.find(id);
  if (iter == _model.end())
  {
    // id not found, returning empty iterator
    return ListIteratorAssocACDEdge(emptyContainer, _fact, false);
  }

  ClassDiagramNode::const_iterator niter = iter->second.find(ltype);
  if (niter == iter->second.end())
  {
    // id found but ltype not found, returning empty iterator
    return ListIteratorAssocACDEdge(emptyContainer, _fact, false);
  }

  // both id and ltype found
  return ListIteratorAssocACDEdge(  (ListIteratorAssocContainer::Container*) &(niter->second), _fact, false);
}

void ClassDiagram::createClassDiagram(Factory& fact) {
  _fact = &fact;
  VisitorClassDiagram *visitor = new VisitorClassDiagram(fact, *this);
  AlgorithmPreorder alg ;
  alg.setSafeMode();
  alg.setCrossEdgeToTraversal(lim::asg::edkScope_HasMember);
  alg.run(fact, *visitor,fact.getRoot()->getId());
  visitor->postProcess();
  delete visitor;
}

const std::pair<NodeId, ClassDiagramAttrType> ClassDiagram::resolveSimpleType(const NodeId type, const Factory& fact) {
  const Factory::TurnFilterOffSafely tfos(fact);
  std::pair<NodeId, ClassDiagramAttrType> result(0, cdtValue);

  if (!Common::getIsValid(type))
    return result;

  const base::Base& check = fact.getRef(type);
  if (check.getNodeKind() == ndkType)
  {
    type::Type& typenode = (type::Type&) check;

    if (typenode.getTypeFormerIsEmpty())
    {
      return result;
    }

    ListIterator<type::TypeFormer> iter = typenode.getTypeFormerListIteratorBegin();
    for(iter = typenode.getTypeFormerListIteratorBegin(); iter != typenode.getTypeFormerListIteratorEnd(); ++iter)
    {
      const base::Base& icheck = *iter;//.next();
      NodeKind nk = icheck.getNodeKind();
      if (nk == ndkTypeFormerPointer)
      {
        const type::TypeFormerPointer& tformp = (const type::TypeFormerPointer&) icheck;
        PointerKind ptk = tformp.getPointerKind();
        if (ptk == ptkReference)
        {
          result.second = cdtReference;
        }
        else
        {
          result.second = cdtPointer;
        }
      }
      else if (nk == ndkTypeFormerType)
      {
        const type::TypeFormerType& tft = (const type::TypeFormerType&) icheck;
        result.first = tft.getRefersTo()->getId();

        //////////////////////////////////////////////////////////////////////
        //Erre a reszre lim hiba miatt van szukseg.                         //
        //C# eseten elofordul hogy nem referenciakent epul at               //
        //egy osztaly tipus. Egyelore csak a lim2dpm-nel lenyeges.          //
        //////////////////////////////////////////////////////////////////////
        if (fact.getExist(result.first))
        {
          const base::Base& b = fact.getRef(result.first);

          if (Common::getIsClass(b) && (fact.getLanguage() == limLangCsharp))
          {
            result.second = cdtReference;
          }
        }
        ///////////////////////////////////////////////////////////////////////

      }
      else if (nk == ndkTypeFormerArray)
      {
        result.second = cdtPointer;
      }
    }
  }
  return result;
}

const std::pair<short, short> ClassDiagram::resolveMult(ClassDiagramAttrType cdt) {
  std::pair<short, short> res(0, 0);
  switch (cdt) {
    case cdtValue:
      res.first = res.second = cdmOne;
      break;
    case cdtReference:
      res.first = cdmZero;
      res.second = cdmOne;
      break;
    case cdtPointer:
      res.first = cdmZero;
      res.second = cdmAny;
      break;
    default:
      res.first = res.second = cdmOne;
      break;
  }
  return res;
}

bool ClassDiagram::addConnection(NodeId from, NodeId to, ClassDiagramLinkKind ltype, const std::string& lname, int mullow, int mulhigh) {
  if(ltype == cdlXOwns) {
    if(!id_set.insert(to).second) {
	  WriteMsg::write(WriteMsg::mlDDDDebug, "Connection couldn't be set from id%d to id%d, the to edge already have a parent.\n", to, from);
      return false;
    }
  }

  ClassDiagramContainer::iterator iter = _model.find(from);
  if (iter == _model.end())
  {
    _model.insert(ClassDiagramPair(from, ClassDiagramNode()));
    iter = _model.find(from);
  }

  ClassDiagramNode::iterator niter = iter->second.find(ltype);
  if (niter == iter->second.end())
  {
    iter->second.insert(ClassDiagramNodePair(ltype, ListIteratorAssocContainer::Container()));
    niter = iter->second.find(ltype);
  }

  int key = _fact->getStringTable().set(lname);
  acdLinkInfo linfo;
  linfo.high = mulhigh;
  linfo.low = mullow;
  linfo.name_key = key;
  AssocEdge<NodeId, acdLinkInfo> aedge( to, linfo);
  
  niter->second.push_back(aedge);
  return true;
}

}
}
} // columbus::lim::asg
