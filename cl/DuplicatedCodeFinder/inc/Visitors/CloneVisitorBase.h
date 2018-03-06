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

#ifndef CLONE_VISITOR_BASE_H
#define CLONE_VISITOR_BASE_H

#include "../common.h"
#include <map>
#include <iostream>
#include <common/inc/WriteMessage.h>
#include <lim/inc/LimOrigin.h>


/*
 * This class it can identification the line.
 */

struct LineIdentifier {

  LineIdentifier ():path(0),line(0) {

  }

  LineIdentifier (const LineIdentifier & p):path(p.path),line(p.line) {

  }
  LineIdentifier ( columbus::Key path,
                  int line): path(path),line(line) {}

  bool operator<(const LineIdentifier& second) const {
   if (line != second.line) {
     return line < second.line;
   }
   return path < second.path;
  }
  //This is the key of the path string (in the lim asg string table)
  columbus::Key path;
  int line;

};

#ifndef NDEBUG
#define CHECK_SEPARATOR if(separatorCounter == INT_MIN) throw columbus::Exception(COLUMBUS_LOCATION,"Too many separator character created!");
#else
#define CHECK_SEPARATOR
#endif


class CloneVisitorBase :  public columbus::LANGUAGE_NAMESPACE::VisitorAbstractNodes {
public:
  enum CloneKind {
      schemaOnly
    , exactMatch
    , customMatch
  };

  enum BlockKind {
      BK_limNodeBlock
    , BK_asgNodeBlock
    , BK_file
    , BK_none
  };
  /** 
  * \en
  * .
  * \_en
  *
  * \hu
  * \_hu
  */  
  CloneVisitorBase( std::set<LineIdentifier>& visitedLines
    , std::set<NodeId>&             visitedLimNodes
    , columbus::LimOrigin&          limOrigin
    , std::vector<int>&             _resultSequence
    , std::vector<ClonePositioned*>& _nodeIdSequence
    , CloneKind _ck = schemaOnly
    , bool _analizeNode = false
    , bool _lowMemUsage = false
    , columbus::lim::asg::Factory* limFactory = NULL
  );

  /** 
  * \en
  * \_en
  *
  * \hu
  * \_hu
  */  
  virtual ~CloneVisitorBase();

private:
  CloneVisitorBase(const CloneVisitorBase&);
  CloneVisitorBase& operator=(const CloneVisitorBase&);
protected: 
   
  std::set<LineIdentifier>& visitedLines;
  std::set<LineIdentifier>* logicalLines;
  std::map<NodeId,std::set<columbus::Key> >* fileNamesByComponent;
  
  

  std::set<NodeId>& visitedLimNodes;
  std::string  prevPath;
  unsigned int prevLine;
  /**
   * \internal
   * \brief Give a differently meaning to the block node 
   * if this flags is true it need to serialize the asg. 
   **/
  NodeId             blockedNode;
  BlockKind          blockNodeKind;
  std::stack<NodeId> currentLimNode;

  int depth;
  columbus::LANGUAGE_NAMESPACE::Factory* factory;
  columbus::lim::asg::Factory*           limFactory;
  columbus::LimOrigin&                   limOrigin;
  std::vector<int>&                      resultSequence;
  std::vector<ClonePositioned* >&        nodeIdSequence;
  int inside;
  bool analizeNode;
  std::set<std::string> block_paths;
  std::ostream* out;
  int decDepthSign;
  //int globalFileSeparator;
  //int beginEndSeparator;
  int separatorCounter;
  //this value should be unique...for suffix tree only!!!
  int uniqueValue;
  std::string path;
  common::timestat time;
  columbus::NodeId currentLimComponent;
  std::set<columbus::NodeId>* filter;
  columbus::NodeId lastFiltered;
  bool lastIsFilteredOut;
  bool filterIsOn;
  columbus::NodeId filterBegin;
  unsigned long long visitedNodesNumber;

////////////Protected functions////////////
  
  bool isAnalizeNode(const Base& node);

  int  getSeparator();

  void addToResultSequence(int kind) ;

  ClonePositioned* createClonePositioned(const Positioned* p);

  void addToNodeIdSequence(const Positioned* p);

  void addPattern(const  Base& n);

  void decreaseDepth(const Base& n) ;

  void addFileSeparator() ;

  void addBeginEndSeparator() ;

  bool isThisVariantNoneVisitedVarinat(const Base& b,  columbus::NodeId* limId = NULL) ;

  void blockNode(const Base& b);

  void assignSrcFileToComponenet( std::string &lPath ,NodeId currentLimComponent);

public:
  void setLogicalLines(std::set<LineIdentifier>* val) { logicalLines = val; }
  void setFileNamesByComponent(std::map<NodeId,std::set<columbus::Key> >* val) { fileNamesByComponent = val; }
  void resetVisitedNodesNumber();

  unsigned long long getVisitedNodesNumber();

  void setOutputStream(std::ostream& out);

  // --- visit Nodes ---
  // struc
  /** 
  * \en
  * This function is called automatically by the traversal algorithm when a Class node is reached.
  * \_en
  *
  * \hu
  * 
  * \_hu
  */  
  void incDepth() ;
  void decDepth() ;

  void setFactory( columbus::LANGUAGE_NAMESPACE::Factory* _factory, NodeId currentLimComponentId) ;

  int getUniqueValue() ;

  int getGlobalFileSeparator() ;

  int getBeginEndSeparator() ;

  bool isSepCharacter(int s) ;

  bool isSepDecDepthSign(int s);

  int getDecDepthSign() ;

  void addBlockPath(const std::string& path) ;

  void dumpFilterRange(NodeId from, NodeId to);
  
  virtual void visit   (const  Positioned& n,bool callVirtualParent);

  void visitEnd(const  Positioned& n, bool callVirtualParent) ;

  void setFilter(std::set<columbus::NodeId>& filter);

  void clearFilter();

  bool evoluteLimNode( const Base& n , bool end);

  bool parseLimNodeId (const Base& n, NodeId& limNodeID );
};


#endif
