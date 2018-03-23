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
#include "../inc/Visitors/CloneVisitorBase.h"

using namespace columbus;
using namespace common;

CloneVisitorBase::CloneVisitorBase(
  std::set<LineIdentifier>& visitedLines
  , std::set<columbus::NodeId>& visitedLimNodes
  , columbus::LimOrigin& limOrigin
  , std::vector<int>& _resultSequence
  , std::vector<ClonePositioned*>& _nodeIdSequence
  , CloneKind _ck /*= schemaOnly*/
  , bool _analizeNode/* = false*/
  , bool _lowMemUsage /*= false*/
  , columbus::lim::asg::Factory* limFactory/*= NULL*/
  )
  : visitedLines(visitedLines)
  , logicalLines(NULL)
  , visitedLimNodes(visitedLimNodes)
  , prevPath()
  , prevLine (0)
  , blockedNode(0)
  , blockNodeKind (BK_none)
  , currentLimNode()
  , depth(0)
  , factory(NULL)
  , limFactory(limFactory)
  , limOrigin(limOrigin)
  , resultSequence(_resultSequence)
  , nodeIdSequence(_nodeIdSequence)
  , inside(0)
  , analizeNode(_analizeNode)
  , block_paths()
  , out(NULL)
  , decDepthSign(-2)
  , separatorCounter(-3)
  , uniqueValue(-1)
  , path ("")
  , time(common::getProcessUsedTime())
  , currentLimComponent(0)
  , filter(NULL)
  , lastFiltered(0)
  , lastIsFilteredOut(false)
  , filterIsOn(false)
  , filterBegin(0)
  , visitedNodesNumber(0)
{}

CloneVisitorBase::~CloneVisitorBase() {}

bool CloneVisitorBase::isAnalizeNode(const Base& node) {
  if(analizeNode) {
#if defined SCHEMA_JAVA
    return columbus::java::asg::Common::getIsMethodDeclaration(node);
#elif defined SCHEMA_PYTHON
    return columbus::python::asg::Common::getIsFunctionDef(node);
#elif defined SCHEMA_CSHARP
    return columbus::csharp::asg::Common::getIsBaseMethodDeclarationSyntax(node)
        || columbus::csharp::asg::Common::getIsBasePropertyDeclarationSyntax(node)
        || columbus::csharp::asg::Common::getIsAnonymousFunctionExpressionSyntax(node);
#endif
  }
  return false;
}

int CloneVisitorBase::getSeparator() {
  --separatorCounter;
  CHECK_SEPARATOR(separatorCounter);
  return separatorCounter;
}

void CloneVisitorBase::addToResultSequence(int kind) {
  resultSequence.push_back(kind);
}

ClonePositioned* CloneVisitorBase::createClonePositioned(const Positioned* p) {
  ClonePositioned* px;
#ifdef SCHEMA_JAVA
  if (columbus::java::asg::Common::getIsPackage(*p)) {
    px = new ClonePositioned("unknown", 0, 0, 0, 0, p->getNodeKind(), p->getId(), currentLimNode.empty()?currentLimComponent:currentLimNode.top(),currentLimComponent);
  } else {
    px = new ClonePositioned(p->getPosition().getPath(), p->getPosition().getWideLine(), p->getPosition().getWideCol(), p->getPosition().getWideEndLine(), p->getPosition().getWideEndCol(), p->getNodeKind(), p->getId(),currentLimNode.empty()?currentLimComponent:currentLimNode.top(),currentLimComponent);
  }
#elif defined SCHEMA_PYTHON
  px = new ClonePositioned(p->getPosition().getPath(), p->GET_LINE_OF_POSITIONS, p->GET_COLUMN_OF_POSITIONS, p->GET_END_LINE_OF_POSITIONS, p->GET_END_COLUMN_OF_POSITIONS, p->getNodeKind(), p->getId(),currentLimNode.empty()?currentLimComponent:currentLimNode.top(),currentLimComponent);
#elif defined SCHEMA_CSHARP
  px=new ClonePositioned(p->getPosition().getFileName(), p->GET_LINE_OF_POSITIONS, p->GET_COLUMN_OF_POSITIONS, p->GET_END_LINE_OF_POSITIONS, p->GET_END_COLUMN_OF_POSITIONS, p->getNodeKind(), p->getId(),currentLimNode.empty()?currentLimComponent:currentLimNode.top(),currentLimComponent);
#endif
  return px;
}

void CloneVisitorBase::addToNodeIdSequence(const Positioned* p) {

  if (p!=NULL) {
    ClonePositioned* px = createClonePositioned(p);
    nodeIdSequence.push_back(px);
    common::WriteMsg::write(CMSG_ADD_NODE_TO_SEQ,nodeIdSequence.size()-1,LANGUAGE_NAMESPACE::Common::toString(p->getNodeKind()).c_str(),px->getStringPath().c_str(),px->getLine());
  } else {
    nodeIdSequence.push_back(NULL);
    common::WriteMsg::write(CMSG_ADD_NODE_TO_SEQ_END ,nodeIdSequence.size()-1);
  }
}

void CloneVisitorBase::addPattern(const  Base& n) {
  int kind = n.getNodeKind();

  if (analizeNode && isAnalizeNode(n))
    inside++;

  if (inside == 0 && analizeNode)
    addToResultSequence(getSeparator());
  else {
    addToResultSequence((int)kind);
  }

  //it must be a positioned.....checked before addPattern is called
  addToNodeIdSequence(dynamic_cast<const Positioned*>(&n));
}

void CloneVisitorBase::decreaseDepth(const Base& n) {

  addToResultSequence(decDepthSign);
  addToNodeIdSequence(NULL);

  if (analizeNode && isAnalizeNode(n)) {
    if (inside>0) {
      inside--;
      if (inside == 0) {
        addBeginEndSeparator();
      }
    }
  }
}

void CloneVisitorBase::addFileSeparator() {

  addToResultSequence(/*globalFileSeparator*/getSeparator());
  addToNodeIdSequence(NULL);
}

void CloneVisitorBase::addBeginEndSeparator() {

  addToResultSequence(/*beginEndSeparator*/getSeparator());
  addToNodeIdSequence(NULL);
}

void CloneVisitorBase::blockNode(const Base& b) {

  if (!AlgorithmCommon::getIsPositioned(b))
    return;
  const Positioned& pos= dynamic_cast<const Positioned&>(b);
  /**
   *the next part blocks the generated code
   */

#if defined(SCHEMA_JAVA)
  std::string lPath=pos.getPosition().getPath();
  unsigned line = pos.getPosition().getWideLine();
#elif defined(SCHEMA_PYTHON)
  std::string lPath=pos.getPosition().getPath();
  unsigned line = pos.getPosition().getLine();
#elif defined(SCHEMA_CSHARP)
  std::string lPath=pos.getPosition().getFileName();
  LowerStringOnWindows(lPath);
  unsigned line = pos.getPosition().getStartLine();
#endif
  if ((prevPath!=lPath) && fileNamesByComponent) {
    assignSrcFileToComponenet(lPath,currentLimComponent);
  }

  if (logicalLines) {
#if defined(SCHEMA_JAVA)
    logicalLines->insert(LineIdentifier(limFactory->getStringTable().set(lPath.c_str()),pos.getPosition().getLine()));
    logicalLines->insert(LineIdentifier(limFactory->getStringTable().set(lPath.c_str()),pos.getPosition().getEndLine()));
    logicalLines->insert(LineIdentifier(limFactory->getStringTable().set(lPath.c_str()),pos.getPosition().getWideLine()));
    logicalLines->insert(LineIdentifier(limFactory->getStringTable().set(lPath.c_str()),pos.getPosition().getWideEndLine()));
#elif defined (SCHEMA_PYTHON)
    logicalLines->insert(LineIdentifier(limFactory->getStringTable().set(lPath.c_str()),pos.getPosition().getLine()));
    logicalLines->insert(LineIdentifier(limFactory->getStringTable().set(lPath.c_str()),pos.getPosition().getEndLine()));
#elif defined SCHEMA_CSHARP
    logicalLines->insert(LineIdentifier(limFactory->getStringTable().set(lPath.c_str()),pos.getPosition().getStartLine()));
    logicalLines->insert(LineIdentifier(limFactory->getStringTable().set(lPath.c_str()),pos.getPosition().getEndLine()));
#endif
  }

  if ((prevPath!=lPath || line!=prevLine) && lPath!="") {
    visitedLines.insert(LineIdentifier(limFactory->getStringTable().set(prevPath.c_str()),prevLine));
    prevPath = lPath;
    prevLine = line;

    if (visitedLines.count(LineIdentifier(limFactory->getStringTable().get(lPath),line))!=0) {
      blockNodeKind = BK_asgNodeBlock;
      blockedNode   = b.getId();

      common::WriteMsg::write(common::WriteMsg::mlDDebug,"\nThe %s %d has already been visited.\n", lPath.c_str(),line);
    return;
    }
  }

  if (!currentLimNode.empty() && (visitedLimNodes.count(currentLimNode.top()) > 0))
  {
    columbus::NodeId  posibelBlockedNode   = currentLimNode.top();
    if (limFactory->getRef(posibelBlockedNode ).getNodeKind() != lim::asg::ndkPackage) {
      blockNodeKind = BK_limNodeBlock;
      blockedNode   = posibelBlockedNode;
      common::WriteMsg::write(common::WriteMsg::mlDDebug,"The lim node %s %s %d  already visited java %d",lim::asg::Common::toString(limFactory->getRef(blockedNode ).getNodeKind()).c_str(),lPath.c_str(),line,b.getId());

    }
    return;
  }


  for (std::set<std::string>::iterator s_iter=block_paths.begin();s_iter!=block_paths.end();++s_iter) {
    std::string b_path=(*s_iter);
    if (lPath.find(b_path)!=std::string::npos) {
      common::WriteMsg::write(CMSG_FILTERED_OUT, lPath.c_str());
      blockNodeKind = BK_file;
      blockedNode   = 0;
      return;
    }
  }
  return;
}

void CloneVisitorBase::resetVisitedNodesNumber()
{
  visitedNodesNumber = 0;
}

unsigned long long CloneVisitorBase::getVisitedNodesNumber()
{
  return visitedNodesNumber ;
}

void CloneVisitorBase::setOutputStream(std::ostream& out) {
  this->out = &out;
}

void CloneVisitorBase::incDepth() {
  depth++;
}

void CloneVisitorBase::decDepth() {
  depth--;
}

void CloneVisitorBase::setFactory(  columbus::LANGUAGE_NAMESPACE::Factory* _factory, columbus::NodeId currentLimComponentId) {
  factory             = _factory;
  currentLimComponent = currentLimComponentId;
  lastIsFilteredOut   = false;
}

int CloneVisitorBase::getUniqueValue() {
  return uniqueValue;
}

int CloneVisitorBase::getGlobalFileSeparator() {
  return 0;
}

int CloneVisitorBase::getBeginEndSeparator() {
  return 0;
}

bool CloneVisitorBase::isSepCharacter(int s) {
  return (s>INT_MIN+separatorCounter && s!=decDepthSign);
}

bool CloneVisitorBase::isSepDecDepthSign(int s) {
  return (s==decDepthSign);
}

int CloneVisitorBase::getDecDepthSign() {
  return decDepthSign;
}

void CloneVisitorBase::addBlockPath(const std::string& path) {
  block_paths.insert(path);
}

void CloneVisitorBase::dumpFilterRange(columbus::NodeId from,columbus::NodeId to) {
  if(out != NULL) {
    Positioned* begin = dynamic_cast<Positioned*>(factory->getPointer(from));
    Positioned* end = dynamic_cast<Positioned*>(factory->getPointer(to));
    if (begin && end) {
      ClonePositioned* beginPos = createClonePositioned(begin);
      ClonePositioned* endPos = createClonePositioned(end);
      (*out) << "Filtered:" << beginPos->getStringPath() << "(" << beginPos->getLine() << "," <<  beginPos->getCol() << ")" << " - " << endPos->getStringPath() << "(" << endPos->getEndLine() << "," << endPos->getEndCol() << ")\n";
      delete beginPos;
      delete endPos;
    }
  }
}

void CloneVisitorBase::visit(const  Positioned& n,bool callVirtualParent){
#if defined (SCHEMA_JAVA)
  if (n.getIsCompilerGenerated())
    return;
#endif

  visitedNodesNumber++;
  evoluteLimNode(n,false);

  if (blockNodeKind !=  BK_none) {
    return;
  }
  blockNode(n);

  if (blockNodeKind !=  BK_none) {
    return;
  }

  // filter
  if(filter != NULL) {
    if(!filterIsOn) {
      if(filter->find(n.getId()) != filter->end()) {
        // node is filtered out
        lastFiltered = n.getId();
        filterIsOn = true;
        if(!lastIsFilteredOut) {
          filterBegin = n.getId();
        }
        lastIsFilteredOut = true;
        return;
      }
    } else {
      return;
    }
  }

  if(lastIsFilteredOut) {
    // replace filtered segment with unique char
    // dump range
    dumpFilterRange(filterBegin, lastFiltered?lastFiltered:filterBegin);
    addBeginEndSeparator();
  }
  lastIsFilteredOut = false;


#if defined(SCHEMA_JAVA)
  if (columbus::java::asg::Common::getIsPackage(n)) {
#elif defined SCHEMA_CSHARP
  if (n.getNodeKind() == columbus::LANGUAGE_NAMESPACE::ndkNamespaceDeclarationSyntax) {
#endif
#if defined SCHEMA_JAVA || defined SCHEMA_CSHARP
    addFileSeparator();
    addPattern(n);
    path="";
    return;
  }
#endif

#if  defined SCHEMA_JAVA
#define getPath getPosition().getPath
#elif  defined SCHEMA_PYTHON
#define getPath getPosition().getPath
#elif  defined SCHEMA_CSHARP
#define getPath getPosition().getFileName
#endif
  if (AlgorithmCommon::getIsPositioned(n)) {
    const Positioned& posNodeRef = dynamic_cast<const Positioned&>(n);
    if (path.empty()) {
      path = posNodeRef.getPath();
    }

    if ( posNodeRef.getPath() != path && !posNodeRef.getPath().empty()) {
        addFileSeparator();
        path = posNodeRef.getPath();
    }
  } else {
#ifdef SCHEMA_CSHARP
    if (n.getNodeKind() != columbus::LANGUAGE_NAMESPACE::ndkNamespaceDeclarationSyntax)
#endif
      return;
  }
#undef getPath
  addPattern(n);
  return;
}

void CloneVisitorBase::visitEnd(const  Positioned& n, bool callVirtualParent) {
#if defined(SCHEMA_JAVA)
  if (n.getIsCompilerGenerated())
    return;
#endif

  if ((blockNodeKind == BK_asgNodeBlock) && ( n.getId() == blockedNode )) {
    blockedNode = 0;
    blockNodeKind = BK_none;
  }

  if (blockNodeKind != BK_none) {
    if (evoluteLimNode(n,true)) {
      if (blockNodeKind == BK_none) {
        return ;
      }
    }
  }

  evoluteLimNode(n,true);


  if (blockNodeKind != BK_none)
    return;

  if(filterIsOn && lastFiltered != 0) {
    if(lastFiltered == n.getId()) {
      filterIsOn = false;
    }
    return;
  }

  decreaseDepth(n);
}

void CloneVisitorBase::setFilter(std::set<columbus::NodeId>& filter) {
  this->filter = &filter;
}

void CloneVisitorBase::clearFilter() {
  this->filter = NULL;
}

bool CloneVisitorBase::evoluteLimNode( const Base& n ,bool end){
  columbus::NodeId parsedLimNodeID = 0;
  if (parseLimNodeId(n,parsedLimNodeID)) {
    if (end) {
      if (currentLimNode.size()) {

        if (currentLimNode.size() > 0) {
          if (!lim::asg::Common::getIsPackage( limFactory->getRef(currentLimNode.top()))) {
            visitedLimNodes.insert(currentLimNode.top());
          }
        }

        if ( (blockNodeKind == BK_limNodeBlock) &&  blockedNode == currentLimNode.top()) {

          blockedNode=0;
          blockNodeKind = BK_none;
        }

        currentLimNode.pop() ;
        return true;
      } else {
        common::WriteMsg::write(CMSG_MORE_END_THEN_BEGIN );
      }
    } else {
      currentLimNode.push(parsedLimNodeID) ;
      return true;
    }
  } else if (currentLimNode.empty()) {
     currentLimNode.push(limFactory->getRoot()->getId());
  }
  return false;
}

bool CloneVisitorBase::parseLimNodeId( const Base& n, columbus::NodeId& limNodeID ){
  columbus::NodeId tmpNode = limOrigin.getLimIdToCompIdAndCppId( currentLimComponent,n.getId());
  if (tmpNode != 0) {
    limNodeID = tmpNode;
    return true;
  }
  return false;
}

void CloneVisitorBase::assignSrcFileToComponenet( std::string &lPath ,columbus::NodeId currentLimComponent)
{
  (*fileNamesByComponent)[currentLimComponent].insert(limFactory->getStringTable().set(lPath.c_str()));
  for ( columbus::lim::asg::ListIterator<columbus::lim::asg::base::Base>
    it = limFactory->getReverseEdges().constIteratorBegin(currentLimComponent,columbus::lim::asg::edkComponent_Contains);
    it != limFactory->getReverseEdges().constIteratorEnd(currentLimComponent,columbus::lim::asg::edkComponent_Contains);
  ++it) {
    assignSrcFileToComponenet(lPath,it->getId());
  }
}
