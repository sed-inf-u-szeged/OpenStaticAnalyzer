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

namespace columbus { namespace lim { namespace asg {

  VisitorClassDiagram::VisitorClassDiagram(const Factory& fact, ClassDiagram& cd)
    : _fact(fact), _cd(cd) {}

  void VisitorClassDiagram::visit(const logical::Class& node, bool callVirtualBase)
  {
    VisitorAbstractNodes::visit((const logical::Class&)node, callVirtualBase);
    if(node.getDeclares() != NULL || node.getAggregated() != NULL || !node.getInstanceIsEmpty()) {
      return;
    }
    NodeId from, to;
    from = node.getId();
    for(ListIterator<Member> iter = node.getMemberListIteratorBegin(); iter != node.getMemberListIteratorEnd(); ++iter)
    {
      const Member& elem = *iter;
      if(elem.getDeclares() != NULL || elem.getAggregated() != NULL)  {
        continue;
      }
      to = elem.getId();
      string name = elem.getName();
      if(!_cd.addConnection(from, to, cdlXOwns, name, cdmOne, cdmOne)) {
        continue;
      }
      if(Common::getIsClass(elem))
      {
        _cd.addConnection(from, to, cdlCOwns, name, cdmOne, cdmOne);
        _cd.addConnection(to, from, cdlCOwnedBy, name, cdmOne, cdmOne);
      }
      else if(Common::getIsMethod(elem))
      {
        _cd.addConnection(from, to, cdlMOwns, name, cdmOne, cdmOne);
        _cd.addConnection(to, from, cdlMOwnedBy, name, cdmOne, cdmOne);
      }
      else if(Common::getIsAttribute(elem))
      {
        _cd.addConnection(from, to, cdlAOwns, name, cdmOne, cdmOne);
        _cd.addConnection(to, from, cdlAOwnedBy, name, cdmOne, cdmOne);
      }
    }
    checkForInheritance(node);
    checkForAggrComp(node);
    checkForAssoc(node);
  }

  // felepiti a package hierarchiat
  void VisitorClassDiagram::visit(const logical::Package& node, bool callVirtualBase)
  {
    VisitorAbstractNodes::visit((const logical::Package&)node, callVirtualBase);
    NodeId from, to;
    from = node.getId();

    for(ListIterator<Member> iter = node.getMemberListIteratorBegin(); iter != node.getMemberListIteratorEnd(); ++iter)
    {
      const Member& elem = *iter;
      if(elem.getDeclares() != NULL || elem.getAggregated() != NULL) {
        continue;
      }
      string name = elem.getName();
      to = elem.getId();
      if(!_cd.addConnection(from, to, cdlXOwns, name, cdmOne, cdmOne)) {
        continue;
      }
      if(Common::getIsPackage(elem))
      {
        _cd.addConnection(from, to, cdlPOwns, name, cdmOne, cdmOne);
        _cd.addConnection(to, from, cdlPOwnedBy, name, cdmOne, cdmOne);
      }
      if(Common::getIsClass(elem))
      {
        _cd.addConnection(from, to, cdlCOwns, name, cdmOne, cdmOne);
        _cd.addConnection(to, from, cdlCOwnedBy, name, cdmOne, cdmOne);
      }
      else if(Common::getIsMethod(elem))
      {
        _cd.addConnection(from, to, cdlMOwns, name, cdmOne, cdmOne);
        _cd.addConnection(to, from, cdlMOwnedBy, name, cdmOne, cdmOne);
      }
      else if(Common::getIsAttribute(elem))
      {
        _cd.addConnection(from, to, cdlMOwns, name, cdmOne, cdmOne);
        _cd.addConnection(to, from, cdlAOwnedBy, name, cdmOne, cdmOne);
      }
    }
  }

  void VisitorClassDiagram::postProcess()
  {
    map<NodeId, NodeId>::iterator iter, end;
    NodeId mid, cid;
    for(iter = _methmap.begin(), end = _methmap.end() ; iter != end ; ++iter)
    {
      mid = iter->first;
      cid = iter->second;
      postProcessMethod(mid, cid);
    }
  }
  
  void VisitorClassDiagram::checkForInheritance(const logical::Class& node)
  {
    bool isdefined = !node.getIsAbstract();

    for(ListIterator<type::Type> iter = node.getIsSubclassListIteratorBegin(); iter != node.getIsSubclassListIteratorEnd(); ++iter)
    {
      NodeId id = ClassDiagram::resolveSimpleType(iter->getId(), _fact).first;
      
      if (!_fact.getExist(id))
        continue;

      const base::Base& element = _fact.getRef(id);
      if(Common::getIsClass(element))
      {
        logical::Class& celement = (logical::Class&)element;
        ClassDiagramLinkKind ltype1, ltype2;
        string name;
        // celement a node gyerek osztalya
        //ha celement nem abstract, node viszont az, akkor realizacio
        if((!celement.getIsAbstract() && isdefined) || (celement.getIsAbstract() && !isdefined))
        {
          ltype1 = cdlChild;
          ltype2 = cdlParent;
          name = "specializes";
        }
        else
        {
          ltype1 = cdlRealizedBy;
          ltype2 = cdlRealizes;
          name = "realizes";
        }
        _cd.addConnection(node.getId(), celement.getId(), ltype1, name, cdmZero, cdmZero);
        _cd.addConnection(celement.getId(), node.getId(), ltype2, name, cdmZero, cdmZero);
      }
    }
  }

  void VisitorClassDiagram::checkForAggrComp(const logical::Class& node)
  {
    NodeId nid, aid, tid;
    nid = node.getId();
    short low1, low2, high1, high2;
    //ClassDiagramLinkKind ltypeA = cdlUnknown, ltypeB = cdlUnknown;
    for(ListIterator<Member> iter = node.getMemberListIteratorBegin(); iter != node.getMemberListIteratorEnd(); ++iter)
    {
      const base::Base& elem = *iter;
      aid = elem.getId();
      //NodeKind ekind = elem.getNodeKind();
      string name;
      if(elem.getNodeKind() == ndkAttribute)
      {
        bool attrisref = true;
        logical::Attribute& attr = (logical::Attribute&)elem;
        name = attr.getName();
        const pair<NodeId, ClassDiagramAttrType> attdata = ClassDiagram::resolveSimpleType(attr.getTypeListIteratorBegin()->getId(), _fact);
        const pair<short, short> multdata = ClassDiagram::resolveMult(attdata.second);
        tid = attdata.first;
        if(_fact.getExist(aid))
        {
          low1 = cdmOne, high1 = cdmOne;
          low2 = multdata.first, high2 = multdata.second;
          if(_fact.getLanguage() != limLangJava && (attdata.second == cdtValue || attdata.second == cdtReference))
          {
            attrisref = false;
          }
          ClassDiagramLinkKind ltype1, ltype2;
          string name = attr.getName();
          if(attrisref)
          {
            ltype1 = cdlAggregates;
            ltype2 = cdlAggregatedBy;
          }
          else
          {
            ltype1 = cdlComposes;
            ltype2 = cdlComposedBy;
          }
          if(_fact.getExist(tid) && Common::getIsClass(_fact.getRef(tid)) && static_cast<Class &>(_fact.getRef(tid)).getClassKind() != clkEnum)
          {
            //building aggregation/composition
            _cd.addConnection(nid, tid, ltype1, name, low1, high1);
            _cd.addConnection(tid, nid, ltype2, name, low2, high2);
          }
          // egy metodus/attributum tipusanak multiplicitasa 0, mivel ez nem az osztalyok kozti kapcsolat multiplicitasa
          _cd.addConnection(aid, tid, cdlHasType, "type", cdmZero, cdmZero);
        }
      }
      else if(Common::getIsMethod(elem))
      {
        //get methods return type and store it as type
       const logical::Method& method = static_cast<const logical::Method &>(elem);
        _methmap.insert(pair<NodeId, NodeId>(aid, nid));
        processMethod((logical::Method&)elem, nid);
        if(!method.getReturnsIsEmpty()) {
          tid = ClassDiagram::resolveSimpleType(method.getReturnsListIteratorBegin()->getId(), _fact).first;
          _cd.addConnection(aid, tid, cdlHasType, "type", cdmZero, cdmZero);
        }
      }
    }
  }
  
  void VisitorClassDiagram::checkForAssoc(const logical::Class& node)
  {
    
    NodeId from, to;
    from = node.getId();
    string name;
    ListIteratorAssocSourcePosition<physical::File> aiter = node.getIsContainedInListIteratorAssocBegin();
    for(ListIterator<type::Type> iter = node.getUsesListIteratorBegin(); iter != node.getUsesListIteratorEnd(); ++iter)
    {
      const base::Base& next = *iter;
      switch(next.getNodeKind())
      {
      case ndkClass:
        to = next.getId();
        name = ((logical::Class&)next).getName();
        break;
      case ndkMethod:
        aiter = ((logical::Method&)next).getIsContainedInListIteratorAssocBegin();
        if(aiter != node.getIsContainedInListIteratorAssocEnd())
        {
          to = aiter->getId(); //TODO ell
        }else
        {
          to = 0;
        }
        name = ((logical::Method&)next).getName();
        break;
      case ndkAttribute:
        aiter = ((logical::Attribute&)next).getIsContainedInListIteratorAssocBegin();
        if(aiter != ((logical::Attribute&)next).getIsContainedInListIteratorAssocEnd())
        {
          to = aiter->getId(); //TODO ell
        }else
        {
          to = 0;
        }
        name = ((logical::Attribute&)next).getName();
        break;
      default:
        to = 0;
        name = "noname";
      }
      if(_fact.getExist(from) && _fact.getExist(to))
      {
        if(Common::getIsClass(_fact.getRef(from)) && Common::getIsClass(_fact.getRef(to)))
        {
          _cd.addConnection(from, to, cdlAssoc, name, cdmOne, cdmOne);
          _cd.addConnection(to, from, cdlAssoc, name, cdmOne, cdmOne);
        }
      }
    }

    for(ListIterator<Member> members_it = node.getMemberListIteratorBegin(); members_it != node.getMemberListIteratorEnd(); ++members_it)
    {
      const base::Base& b = *members_it;
      if (Common::getIsMethod(b))
      {
        const logical::Method& m = static_cast<const logical::Method&>(b);

        for(ListIterator<type::Type> instantiates_it = m.getInstantiatesListIteratorBegin(); instantiates_it != m.getInstantiatesListIteratorEnd(); ++instantiates_it)
        {
          const base::Base& created = *instantiates_it;
          if (Common::getIsClass(created))
          {
            const logical::Class& cc = static_cast<const logical::Class&>(created);
            name = cc.getName();

            _cd.addConnection(from, cc.getId(), cdlAssoc, name, cdmOne, cdmOne);
            _cd.addConnection(cc.getId(), from, cdlAssoc, name, cdmOne, cdmOne);
          }
        }
      }
    }
  }

  void VisitorClassDiagram::processMethod(const logical::Method& node, NodeId classid)
  {
    NodeId nid = node.getId();
    NodeId aid;
    
    string name;
    for(ListIterator<Member> iter = node.getMemberListIteratorBegin(); iter != node.getMemberListIteratorEnd(); ++iter)
    {
      const base::Base& elem = *iter;
      NodeKind ekind = elem.getNodeKind();
      aid = elem.getId();
      name = ((base::Named&)elem).getName();
      _cd.addConnection(nid, aid, cdlXOwns, name, cdmOne, cdmOne);
      if(ekind == ndkMethod)
      {
        _cd.addConnection(nid, aid, cdlMOwns, name, cdmOne, cdmOne);
        _cd.addConnection(aid, nid, cdlMOwnedBy, name, cdmOne, cdmOne);
      }
      else if(ekind == ndkAttribute)
      {
        _cd.addConnection(nid, aid, cdlAOwns, name, cdmOne, cdmOne);
        _cd.addConnection(aid, nid, cdlAOwnedBy, name, cdmOne, cdmOne);
      }
    }
    if(!node.getReturnsIsEmpty()) {
      const pair<NodeId, ClassDiagramAttrType> retdata = ClassDiagram::resolveSimpleType(node.getReturnsListIteratorBegin()->getId(), _fact);
      const pair<short, short> retmultdata = ClassDiagram::resolveMult(retdata.second);
      NodeId rid = retdata.first;
      string mname = node.getName();
      if(_fact.getExist(rid) && Common::getIsClass(_fact.getRef(rid)))
      {
        // asszociacio a visszateresi ertek menten, ha "ertelmes"
        _cd.addConnection(classid, rid, cdlAssoc, mname, retmultdata.first, retmultdata.second);
        _cd.addConnection(rid, classid, cdlAssocD, mname, cdmZero, cdmZero);
      }
    }
  }

  // mid: a hivo fuggveny
  // cid: a hivo fuggveny osztalya
  void VisitorClassDiagram::postProcessMethod(const NodeId mid, const NodeId cid)
  {
    logical::Method& ometh = (logical::Method&)(_fact.getRef(mid));
    
    NodeId cid2;
    string name;
    map<NodeId, NodeId>::iterator finditer;
    for(ListIterator<MethodCall> iter = ometh.getCallsListIteratorBegin(); iter != ometh.getCallsListIteratorEnd();++iter)
    {
      logical::Method* meth = iter->getMethod();
      if(meth == NULL) {
        continue;
      }
      name = meth->getName();
      finditer = _methmap.find(meth->getId());
      if(finditer != _methmap.end())
      {
        // ha a metodus nem szerepelne a map-ben (osztalyon kivuli fuggveny peldaul)
        cid2 = finditer->second;
        if(_fact.getExist(cid) && _fact.getExist(cid2) && Common::getIsClass(_fact.getRef(cid)) && Common::getIsClass(_fact.getRef(cid2)))
        {
          _cd.addConnection(cid, cid2, cdlAssoc, name, cdmOne, cdmOne);
          _cd.addConnection(cid2, cid, cdlAssocD, name, cdmOne, cdmOne);
        }
      }
    }
  }

}}} // columbus::lim::asg
