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

#include "../inc/common.h"
#include "../inc/Visitors/CoverageVisitorBase.h"


CoverageVisitorBase::CoverageVisitorBase() 
  : limNodeId(0)
  , fact(NULL)
  , complexity()
  , coverage()
  , all()
  , currentCoverage()
  , currentAll()
  , currentComplexity()
  , lowerPath()
  , coveredNodes(NULL)
  , asg()
{}

int* CoverageVisitorBase::getCounter( CCCounterMap& container, const UniqueNameWithPath& uname )
{
  CCCounterMap::iterator iter = container.find(uname);
  if (iter != container.end()) 
    return &iter->second;
  else
    return &container.insert(CCCounterMap::value_type(uname, 0)).first->second;
}


void CoverageVisitorBase::visitStart( const columbus::lim::asg::logical::Member& node )
{
  for (columbus::lim::asg::ListIterator<columbus::lim::asg::base::Base> itParent = fact->getReverseEdges().constIteratorBegin(node.getId(),columbus::lim::asg::edkScope_HasMember);
    itParent != fact->getReverseEdges().constIteratorEnd(node.getId(),columbus::lim::asg::edkScope_HasMember);
    ++itParent){
      visitStart((const columbus::lim::asg::logical::Member&)*itParent);
  }

  if  (node.getAggregated()){
    visitStart(*node.getAggregated());
  }

  if (   columbus::lim::asg::Common::getIsClass(node) 
    || columbus::lim::asg::Common::getIsMethod(node)
    || columbus::lim::asg::Common::getIsPackage(node)
    || columbus::lim::asg::Common::getIsComponent(node)) {

      UniqueNameWithPath uname;
      uname.uniqueName = node.getMangledName();

      if (!node.getIsContainedInIsEmpty()) {
        uname.line       = node.getIsContainedInListIteratorAssocBegin().getAssocClass().getLine();
        uname.path       = columbus::lim::asg::Common::getFullPath (*node.getIsContainedInListIteratorAssocBegin());
      }

    
      uname.limNodeId  = node.getId();

      common::WriteMsg::write(CMSG_START_VISIST, uname.uniqueName.c_str(), uname.path.c_str(), uname.line, uname.limNodeId, currentCoverage.size(), currentAll.size());
      currentCoverage.push_back(getCounter(coverage, uname));
      currentAll.push_back(getCounter(all, uname));
      currentComplexity.push_back(getCounter(complexity,uname));

     
  }
}

CoverageVisitorBase::~CoverageVisitorBase()
{
  coverage.clear();
  all.clear();
}

void CoverageVisitorBase::setFactory( columbus::lim::asg::Factory * _fact, const std::string& _asg, const std::map<std::string, std::set<NodeId> >& _coveredNodes )
{
  fact = _fact; 
  asg = _asg; 
  std::map<std::string, std::set<NodeId> >::const_iterator iter=_coveredNodes.find(asg);
  if (iter!=_coveredNodes.end())
    coveredNodes=&(iter->second);
  else 
    coveredNodes = NULL;
}

void CoverageVisitorBase::visitBase( const Base& n )
{
  bool cov = (coveredNodes == NULL) ? false : coveredNodes->find(n.getId()) != coveredNodes->end();

  for (CounterContainer::iterator iter1=currentAll.begin(), iter2=currentCoverage.begin(), iter3 = currentComplexity.begin(); iter1!=currentAll.end(); iter1++, iter2++,iter3++) {
    (*(*iter1))++;
    if (cov) {
      (*(*iter2))++;
      if (isIncTheComplexity(n))
        (*(*iter3))++;
    }
  }
 
}

void CoverageVisitorBase::fillCoverage( CCMap& cov )
{
  for (CCCounterMap::iterator iter=all.begin(); iter!=all.end(); iter++) {
    const UniqueNameWithPath& uname =(*iter).first;
    int surface = iter->second;
    int covered=0;
    CCCounterMap::iterator iter2 = coverage.find(uname);
    if (iter2 != coverage.end())
      covered = iter2->second;

    int mccable=0;
    CCCounterMap::iterator iter3 = complexity.find(uname);
    if (iter3 != complexity.end() && covered > 0)
      mccable = 1 + iter3->second;

    cov.insert(CCMap::value_type(uname, CloneMetricValues((covered)/(float)(surface),mccable)));
    //printf("COV[%s|%s|%d|%d]:covered %d, surface %d, CC %f\n", uname.uniqueName.c_str(), uname.path.c_str(), uname.line,uname.limNodeId, covered, surface, (covered)/(float)(surface));
  }

  
}

void CoverageVisitorBase::acceptNode( Base& b )
{
  b.accept(dynamic_cast<Visitor&>(*this));
}

void CoverageVisitorBase::acceptEndNode( Base& b )
{
  b.acceptEnd(dynamic_cast<Visitor&>(*this));
}

void CoverageVisitorBase::setLimNodeId( NodeId val ) {

  if (limNodeId == val)
    return ;

  currentCoverage.clear();
  currentAll.clear();
  currentComplexity.clear();
  limNodeId = val;
  if ((limNodeId != 0) && ((columbus::lim::asg::Common::getIsMember( fact->getRef(limNodeId)))) ) {

    const columbus::lim::asg::logical::Member& limASmemeber = (const columbus::lim::asg::logical::Member&)fact->getRef(limNodeId);
    visitStart(limASmemeber);

    for (columbus::lim::asg::ListIterator<columbus::lim::asg::base::Component> it = limASmemeber.getBelongsToListIteratorBegin();it != limASmemeber.getBelongsToListIteratorEnd();++it){
      const columbus::lim::asg::base::Component& componenet =*it;
      visitStartComponent(componenet);
    }

  } else if ((limNodeId != 0) && (columbus::lim::asg::Common::getIsComponent( fact->getRef(limNodeId)))) {

    const columbus::lim::asg::base::Component& componenet = dynamic_cast<const columbus::lim::asg::base::Component&>(fact->getRef(limNodeId));
    visitStartComponent(componenet);

    
  }


}

void CoverageVisitorBase::insertLines( std::set<LineIdentifier>* lineSet, const Base& n ) const {
#ifdef SCHEMA_JAVA
  if (!columbus::java::asg::Common::getIsPositioned(n)) 
    return;
  const columbus::java::asg::base::Positioned& p = dynamic_cast<const columbus::java::asg::base::Positioned&>(n);
 
  lineSet->insert(LineIdentifier(p.getPosition().getPathKey(),p.getPosition().getLine()));
  lineSet->insert(LineIdentifier(p.getPosition().getPathKey(),p.getPosition().getEndLine()));

  lineSet->insert(LineIdentifier(p.getPosition().getPathKey(),p.getPosition().getWideLine()));
  lineSet->insert(LineIdentifier(p.getPosition().getPathKey(),p.getPosition().getWideEndLine()));
#endif
}

void CoverageVisitorBase::visitStartComponent( const columbus::lim::asg::base::Component &component )
{
  UniqueNameWithPath uname;
  uname.uniqueName =  component.getName();
  uname.line = 0;
  uname.path = "";
  uname.limNodeId  =  component.getId();

  currentCoverage.push_back(getCounter(coverage, uname));
  currentAll.push_back(getCounter(all, uname));
  currentComplexity.push_back(getCounter(complexity,uname));

  for (columbus::lim::asg::ListIterator<columbus::lim::asg::base::Base> it = fact->getReverseEdges().constIteratorBegin(component.getId(), columbus::lim::asg::edkComponent_Contains); 
         it != fact->getReverseEdges().constIteratorEnd(component.getId(), columbus::lim::asg::edkComponent_Contains); ++it )
  {
    visitStartComponent((columbus::lim::asg::base::Component&)*it);
  }
}





