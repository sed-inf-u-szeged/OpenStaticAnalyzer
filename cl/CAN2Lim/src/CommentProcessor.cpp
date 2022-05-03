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

#include "../inc/CommentProcessor.h"
#include "../inc/ASTConversionInfo.h"

#include <common/inc/DirectoryFilter.h>
#include <common/inc/WriteMessage.h>

#include <iomanip>

extern std::string g_filterfile;
using namespace std;
using namespace common;

CommentProcessor::CommentProcessor(GlobalASTConversionInfo& conversionInfo) : conversionInfo(conversionInfo)
{
}

void CommentProcessor::loadCommentStructure(const std::string& astFile)
{
  DirectoryFilter directoryFilter;
  directoryFilter.openFilterFile(g_filterfile);
  std::string renamedASTFile = cANFilePathRenamer.changeToLIMCompatible(common::pathCanonicalize(astFile));
  std::ifstream file(renamedASTFile + ".comment");

  unsigned prevCommentLineEnd = 0;
  columbus::lim::asg::physical::File *limFile = nullptr;
  if (!file.good())
  {
    WriteMsg::write(WriteMsg::mlDebug, "FILE ERROR: .comment file with name (%s) is missing\n", (renamedASTFile + ".comment").c_str());
  }
  while (file.good())
  {
    char entryMarker;
    file >> entryMarker;
    if (entryMarker == 1) // We encountered a new file
    {
      std::string fileName;
      file >> std::quoted(fileName) >> std::ws;
      if(fileName.c_str() && conversionInfo.changePathFrom.c_str() && conversionInfo.changePathTo.c_str())
        fileName = common::replace(fileName.c_str(), conversionInfo.changePathFrom.c_str(), conversionInfo.changePathTo.c_str());

      // This is doing a replace a second time (it was already done once in CAN). It's required because of the flaws of our testing system.
      if (fileName.c_str() && conversionInfo.changePathFrom.c_str() && conversionInfo.changePathTo.c_str())
        fileName = common::replace(fileName.c_str(), conversionInfo.changePathFrom.c_str(), conversionInfo.changePathTo.c_str());


      prevCommentLineEnd = 0; // needed for overlaps

      limFile = nullptr;
      auto findIt = conversionInfo.correctedFileNameToFileNode.find(fileName);
      if (findIt != conversionInfo.correctedFileNameToFileNode.end() && findIt->second != nullptr)
      {
        limFile = findIt->second;
      }

      if (!limFile)
      {
        WriteMsg::write(WriteMsg::mlDebug, "file error while reading comments : lim filenode with filename(%s) is not found!\n", fileName.c_str());
        continue;
      }
    }
    else //we encountered a comment
    {
      CommentData data;
      string text;
      file >> data.begin.line >> data.begin.column >> data.end.line >> data.end.column >> std::quoted(text) >> std::ws;

      if (!limFile || text.empty()) {
        continue;
      }

      data.text = text;

      auto insertionResult = commentTablePerFile[limFile].insert(data);
      if (insertionResult.second)
      {
        unsigned CLOCToAdd = (data.end.line - data.begin.line) + 1;
        if (prevCommentLineEnd == data.begin.line) //if 2 comments are on the same line, there needs to be a -1 penalty (as it's 2 comments, but only 1 commentLine)
        {
          CLOCToAdd--;
        }
        limFile->setCLOC(limFile->getCLOC() + CLOCToAdd);

        prevCommentLineEnd = data.end.line;
      }
    }
    //if(conversionInfo.filesAlreadyProcessed.count(filename) == 0)
    //  std::cout << "Throwing away comment" << std::endl;
  }
}

void CommentProcessor::addDocumentationToMember(columbus::lim::asg::logical::Member* member, const CommentData& comment, bool postAdd = false)
{
  if (!postAdd)
    docCache.push_back(std::make_pair(member, comment));
  else
  {
    member->addComment(&conversionInfo.limFactory.createComment(comment.text));
  }

}

void CommentProcessor::addCommentToMember(columbus::lim::asg::logical::Member* member, const CommentData &comment, const CommentData *prevComment)
{
  unsigned toAdd = comment.numberOfLines();

  /*common::WriteMsg::write(common::WriteMsg::mlNormal, "DAVID: This comment endline:   %d\n", comment.end.line);
  if (prevComment)
    common::WriteMsg::write(common::WriteMsg::mlNormal, "DAVID: prev comment beginline: %d\n", prevComment->begin.line);*/

    // required for Case: /*comment1*/ /*comment2*/ 
    // as these as 2 comments, but only 1 commentline
  if (prevComment && prevComment->overlaps(comment))
  {
    toAdd--;
  }
  member->setCommentLines(member->getCommentLines() + toAdd);
}

/*
  Based on the commentsTable collected from the .comment file earlier and the now almost complete lim tree, we must now
  decide which comments belongs to which Member/scope.
  Comments before Members (such as classes or functions) are documentation comments and they must be inserted
  with a hasComment edge to that Member.
  The regular comments are simply added to the scopes commentLines attribute.
  The algorithm simplified:
    Traverses the commentTable and the scopeList (vector of scope beginnings and endings) from BOTTOM UPWARDS!
    Meanwhile, a stack of scopes is being built, so that we track which scopes are we in.
    For each comment, we iterate upwards the scopes, so that at each point, we have the relevant information.
    At the end, the added documentation comments need to be reversed (to adhere with the rule, that comment edges are ordered by id)
  By the way, the reason the iteration is bottom-up (and not top-down), is that this way it is easier to deal with chains (comments on consecutive lines)
*/
void CommentProcessor::bindCommentsToLimTree(columbus::lim::asg::physical::File *file) {
  std::set<CommentData, CommentData::Compare> &commentTable = commentTablePerFile[file];
  std::vector<ScopeGuard> &scopeList = conversionInfo.scopeListPerFile[file];
  conversionInfo.addGlobalNamespaceToScopeList(scopeList);

  std::sort(scopeList.begin(), scopeList.end());

  /*for (ScopeGuard sg : scopeList) { //DEBUG
    common::WriteMsg::write(common::WriteMsg::mlNormal, "DAVID: ScopeGuard name = %s, type = %s, line = %d, column = %d\n",
      sg.scope.member->getName().c_str(),
      (sg.guardType == ScopeGuard::BEGIN ? "BEGIN" : "END"),
      sg.getSourcePoint().line,
      sg.getSourcePoint().column
    );
  }*/

  docCache.clear();
  std::stack<MyScope> scopeStack;
  auto scopeGuard = scopeList.rbegin();
  scopeStack.push(scopeGuard->scope); //itt majd pointerekkel kéne
  bool chaining = false;
  const CommentData *prevComment = nullptr;

  for (auto comment = commentTable.rbegin(); comment != commentTable.rend(); ++comment)
  {
    //step the scopeGuards upwards until it reaches the comment
    while (scopeGuard != prev(scopeList.rend()) && comment->begin < next(scopeGuard)->getSourcePoint())
    {
      ++scopeGuard;
      if (scopeStack.top() == scopeGuard->scope)
        scopeStack.pop();
      else
        scopeStack.push(scopeGuard->scope);
      chaining = false; // scopechange breaks chaining
      prevComment = nullptr; // scopechange breaks comment line duplications
    }

    //  Case: class B{}; /* comment */ class C{};
    //  The comment should belong to C as documentation
    if (scopeGuard->guardType == ScopeGuard::BEGIN
      && scopeGuard->getSourcePoint().line == comment->end.line)
    {
      addDocumentationToMember(scopeGuard->scope.member, *comment);
    }
    //  Case: //comment line above member
    //        class B{ 
    //  This comment should belong to B as documentation; Also this might be the beginning of a documentation comment-chain
    else if (scopeGuard->guardType == ScopeGuard::BEGIN
      && scopeGuard->getSourcePoint().line == comment->end.line + 1
      && next(scopeGuard)->scope.begin.line + 1 != scopeGuard->getSourcePoint().line)
    {
      addDocumentationToMember(scopeGuard->scope.member, *comment);
      chaining = true;
    }
    //  Case: class C{ //doc comment
    //  This comment belongs to C as documentation.
    else if (next(scopeGuard)->guardType == ScopeGuard::BEGIN
      && next(scopeGuard)->getSourcePoint().line == comment->begin.line)
    {
      addDocumentationToMember(next(scopeGuard)->scope.member, *comment);
    }
    //  Case: int x, k; //doc comment
    //  This comment belongs to k as documentation
    else if (next(scopeGuard)->guardType == ScopeGuard::END
      && next(scopeGuard)->scope.begin.line == comment->begin.line)
    {
      addDocumentationToMember(next(scopeGuard)->scope.member, *comment);
    }
    //  Case: // 1 the comment we inspect
    //        // 2 blablablabla
    //        class B{
    //  Comment 1 belongs to B as documentation, as it's is chained to comment 2
    else if (chaining && prev(comment)->begin.line <= comment->end.line + 1)
    {
      addDocumentationToMember(scopeGuard->scope.member, *comment);
    }
    //  Case: class A{
    //           //comment
    //  This comment belongs to A as regular comment
    else if (next(scopeGuard)->guardType == ScopeGuard::BEGIN)
    {
      chaining = false;
      addCommentToMember(next(scopeGuard)->scope.member, *comment, prevComment);
      prevComment = &(*comment);
    }
    //  Case: class A{
    //          class B{
    //          }
    //          //comment
    //        }
    // This comment belongs to A as regular comment
    else if (next(scopeGuard)->guardType == ScopeGuard::END)
    {
      chaining = false;
      addCommentToMember(scopeStack.top().member, *comment, prevComment);
      prevComment = &(*comment);
    }
    else
    {
      //common::WriteMsg::write(common::WriteMsg::mlNormal, "DAVID: Impossible comment case\n");
    }
  }

  // we need to apply the edges in an increasing id order, so we reverse the cache, and add them
  // also, we we concatenate multiline doc comments
  std::string chain;
  for (auto it = docCache.rbegin(); it != docCache.rend(); ++it)
  {
    if ( it != prev(docCache.rend())
         && it->first == next(it)->first
         && (it->second.begin.column == next(it)->second.begin.column
             || it->second.begin.line == next(it)->second.end.line))
    {
      chain += it->second.text;
      if(!(it->second.begin.line == next(it)->second.end.line))
        chain += char(10);
    }
    else
    {
      if (!chain.empty())
      {
        chain += it->second.text;
        it->second.text = chain;
        chain = "";
      }
      addDocumentationToMember(it->first, it->second, true);
    }
  }
}
