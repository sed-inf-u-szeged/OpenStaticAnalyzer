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

#ifndef __COVERAGE_VISITOR_BASE_H
#define __COVERAGE_VISITOR_BASE_H

#include "../common.h"
#include "../messages.h"

struct UniqueNameWithPath {
  std::string uniqueName;
  std::string path;
  int line;
  NodeId limNodeId;
  static const int BAD_PATH = -1;

  UniqueNameWithPath()
    : uniqueName()
    , path()
    , line(0)
    , limNodeId(0)  { };
  
  UniqueNameWithPath(const std::string& uniqueName, const std::string& path, int line) : 
    uniqueName(uniqueName), 
    path(path),
    line(line),
    limNodeId(0) { };

  bool operator<(const UniqueNameWithPath& second) const {
    if (line != second.line) 
      return line < second.line;

    int uniqueNameCompare = uniqueName.compare(second.uniqueName);
    if (uniqueNameCompare != 0)
      return uniqueNameCompare < 0;

    if (limNodeId != second.limNodeId)
      return limNodeId < second.limNodeId;

    return path < second.path;
  }
};


/**
 * \brief CoverageVisitorBase
 * This class is corresponding for calculate the all member node (lim) clone coverage, and McCabe complexity. 
 * 
 **/

class CoverageVisitorBase {
private:
  CoverageVisitorBase(const CoverageVisitorBase&);
  CoverageVisitorBase& operator=(const CoverageVisitorBase&);
protected :
  NodeId limNodeId;
  columbus::lim::asg::Factory* fact;
  typedef std::map<UniqueNameWithPath, int> CCCounterMap;
  typedef std::vector<int*> CounterContainer;

  CCCounterMap complexity;
  CCCounterMap coverage;
  CCCounterMap all;

  CounterContainer currentCoverage;
  CounterContainer currentAll;
  CounterContainer currentComplexity;


  bool lowerPath;
  
  int* getCounter(CCCounterMap& container, const UniqueNameWithPath& uname);
  

  void visitStart(const columbus::lim::asg::logical::Member&  node);
  void insertLines(std::set<LineIdentifier>* lineSet, const Base& n) const;
  const std::set<NodeId>* coveredNodes;
  std::string asg;

public:
  struct CloneMetricValues {
    CloneMetricValues():cc(0),cco(0){}
    CloneMetricValues(float cc,int cco):cc(cc),cco(cco){}
    float cc;
   
    int   cco;
  };

  typedef std::map<UniqueNameWithPath, CloneMetricValues> CCMap;

  CoverageVisitorBase();
  virtual ~CoverageVisitorBase();

  void visitBase   (const Base& n);
  virtual void acceptNode(Base& b);
  virtual void acceptEndNode(Base& b);

  virtual bool isIncTheComplexity (const Base& node) {return isIncTheComplexity(node.getNodeKind());}
  virtual bool isIncTheComplexity (int nodeKind) = 0;

  void visitStartComponent( const columbus::lim::asg::base::Component &componenet );
  void setFactory(columbus::lim::asg::Factory * _fact, const std::string& _asg, const std::map<std::string, std::set<NodeId> >& _coveredNodes);
  void setLimNodeId(NodeId val);
  void fillCoverage(CCMap& cov);

};




#endif
