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

#include <clang/AST/ASTContext.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Tooling/Tooling.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include "clang/Frontend/TextDiagnosticPrinter.h"
#include <common/inc/Stat.h>
#include <common/inc/FileSup.h>
#include <common/inc/StringSup.h>
#include <common/inc/WriteMessage.h>
#include <common/inc/DirectoryFilter.h>

#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

#define PROGRAM_NAME "CAN"
#define EXECUTABLE_NAME PROGRAM_NAME


using namespace std;
using namespace llvm;
using namespace clang;
using namespace tooling;
using namespace common;

namespace
{
// Tool CL options.
cl::OptionCategory category(EXECUTABLE_NAME " options");
cl::opt<string> outputFilename("o", cl::desc("AST file to output"), cl::Required, cl::cat(category));
cl::opt<string> statFilename("stat", cl::desc("Statistics file"), cl::cat(category));
cl::opt<string> configFilename("config", cl::desc("Configuration file"), cl::cat(category));
cl::opt<string> changePathFrom("changepathfrom", cl::desc("Part of the paths needed to be replaced"), cl::cat(category));
cl::opt<string> changePathTo("changepathto", cl::desc("New value of the path to be inserted"), cl::cat(category));
cl::opt<string> filterPath("fltp", cl::desc("Path to the softfilter file"), cl::cat(category));

// Handles comments.
class CANAction : public ASTFrontendAction
{
private:
  class MyCommentHandler: public CommentHandler
  {
  public:
    ofstream commentFile;

  private:
    const FileEntry *prevFileEntry;

    bool HandleComment(Preprocessor& pp, SourceRange comment) override
    {
      const SourceManager& sm = pp.getSourceManager();
      const SourceLocation beg = comment.getBegin();
      const SourceLocation end = comment.getEnd();

      const unsigned bl = sm.getSpellingLineNumber(beg);
      const unsigned bc = sm.getSpellingColumnNumber(beg);
      const unsigned el = sm.getSpellingLineNumber(end);
      const unsigned ec = sm.getSpellingColumnNumber(end);

      if (const FileEntry *F = sm.getFileEntryForID(sm.getFileID(beg)))
      {
        if (prevFileEntry != F)
        {
          //new file encountered
          prevFileEntry = F;
          commentFile << (char)1 << ' '; //this marks that the line is for a file

          string filename = F->getName().str();

          // We need to get the canonical (absolute) path for the file, as the CWD could change during build so relative paths make no sense
          filename = common::pathCanonicalize(filename);

          // Unless, there is a "global" string replace on paths (which we sometimes use for relative paths, but these are all relative to one specific "folder")
          if(filename.c_str() && changePathFrom.c_str() && changePathTo.c_str())
            filename = common::replace(filename.c_str(), changePathFrom.c_str(), changePathTo.c_str());

          commentFile << std::quoted(filename) << '\n';
        }

        commentFile << (char)0 << ' '; //this marks that the line is for a comment

        const char* b = sm.getCharacterData(beg);
        const char* e = sm.getCharacterData(end);

        commentFile << bl << ' ' << bc << ' ' << el << ' ' << ec << ' ' << quoted(string(b, e - b)) << '\n';
      }

      return false;
    }

  };
  MyCommentHandler myHandler;

public:
  unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &Compiler, StringRef InFile) override
  {
    // "Empty" class - we do nothing with the AST, but we must have this even if 'usePreprocessorOnly' is true.
    class Consumer : public clang::ASTConsumer
    {
      void HandleTranslationUnit(clang::ASTContext &context) override {}
    };

    // Setup output file according to the tool options and the current TU filename.
    // Binary mode is needed to avoid CR/LF confusion on Windows.
    myHandler.commentFile = ofstream(outputFilename + ".comment", ofstream::binary);
    return unique_ptr<ASTConsumer>(new Consumer());
  }

  bool BeginSourceFileAction(CompilerInstance &ci) override
  {
    // Set comment handler.
    Preprocessor& pp = ci.getPreprocessor();
    pp.addCommentHandler(&myHandler);
    return true;
  }

  void EndSourceFileAction() override
  {
    myHandler.commentFile.close();
  }

};

enum class Language
{
  c,
  cpp,
  objc
};

vector<string> loadSystemIncludeConfiguration(Language language, const string& filename)
{
  vector<string> includeDirs;
  constexpr int MAX_BUFFER_SIZE = 8192;
  char buffer[MAX_BUFFER_SIZE];

  if (language == Language::cpp)
    getPrivateProfileSection("IncludePath_cpp", buffer, MAX_BUFFER_SIZE, filename.c_str());
  else if (language == Language::c)
    getPrivateProfileSection("IncludePath_c", buffer, MAX_BUFFER_SIZE, filename.c_str());
  else
    return includeDirs;

  list<string> keyValueList;
  convertZeroTerminatedStringList(buffer, keyValueList);

  for (const auto& kv : keyValueList)
  {
    auto equalSignPos = kv.find_first_of('=');
    if (equalSignPos != string::npos)
    {
      string directoryName;
      pathCanonicalize(directoryName, kv.substr(equalSignPos + 1));
      includeDirs.push_back(directoryName);
    }
  }
  return includeDirs;
}

int run(int argc, const char** argv)
{
  WriteMsg::setAutomaticFlush(true);

  // Parse options with the common parser.
  CommonOptionsParser parser(argc, argv, category);
  const std::vector<string>& files = parser.getSourcePathList();

  if (files.size() != 1)
    throw std::runtime_error("program requires exactly one input file");

  for (const auto& x : parser.getCompilations().getCompileCommands(files.front()))
  {
    for (auto y : x.CommandLine)
      WriteMsg::write(WriteMsg::mlNormal, "%s ", y.c_str());

    WriteMsg::write(WriteMsg::mlNormal, "\n");
  }

  auto sysIncludes = loadSystemIncludeConfiguration(Language::cpp, configFilename);

  CommandLineArguments cla;

  for (const auto& sysInclude: sysIncludes)
  {
    cla.push_back("-Xclang");
    cla.push_back("-internal-isystem" + sysInclude);
  }
  
  // Create Clang tool.
  ClangTool tool(parser.getCompilations(), files);

  //this may not work
  if (!cla.empty()){
    tool.clearArgumentsAdjusters(); //this may not be needed
    tool.appendArgumentsAdjuster(tooling::getInsertArgumentAdjuster(cla, tooling::ArgumentInsertPosition::BEGIN));
  }

  class MyTextDiagnosticPrinter  : public TextDiagnosticPrinter
  {
  public:
    MyTextDiagnosticPrinter(raw_ostream &os, DiagnosticOptions *diags) : TextDiagnosticPrinter(os, diags) {}
    void HandleDiagnostic(DiagnosticsEngine::Level DiagLevel, const Diagnostic &Info) override 
    {
      DirectoryFilter directoryFilter;
      directoryFilter.openFilterFile(filterPath);
      string canonicalFileName = common::pathCanonicalize(Info.getSourceManager().getFilename(Info.getLocation()).str());
      
      // If the error is not in a filtered file.
      if (!directoryFilter.isFilteredOut(canonicalFileName))
        TextDiagnosticPrinter::HandleDiagnostic(DiagLevel, Info);
    }
  };

  // ToolAction to create binary AST and comment files.
  class : public FrontendActionFactory
  {
  public:
    // This variable is incremented during each invocation and effectively works as an index into the input file array.
    int myHack = 0;
    //unordered_map<string, vector<CommentData>> commentsForFile;

    // Stores the input file names.
    const vector<string>* pMyInputs;

    bool runInvocation(shared_ptr<CompilerInvocation> inv, FileManager* files, shared_ptr<PCHContainerOperations> pch, DiagnosticConsumer* dgc) override
    {
      auto opts = &inv->getDiagnosticOpts();
      auto dc = CompilerInstance::createDiagnostics(opts, dgc, false);

      MyTextDiagnosticPrinter consumer(llvm::errs(), opts);
      dc->setClient(&consumer);

      auto ast = ASTUnit::LoadFromCompilerInvocationAction(std::move(inv), std::move(pch), dc, create().get());
      if (ast == nullptr)
        return false;

      if (ast->Save(outputFilename))
        return false;

      if (dc->hasErrorOccurred() ||
          dc->hasUncompilableErrorOccurred() ||
          dc->hasFatalErrorOccurred() ||
          dc->hasUnrecoverableErrorOccurred())
      {
        return false;
      }

      return true;
    }

    unique_ptr<FrontendAction> create() override { return unique_ptr<FrontendAction>(new CANAction()); }
  } factory;
  factory.pMyInputs = &files;

  // Run the tool.
  int ret = tool.run(&factory);

  return ret;
}

} // anonymous namespace

int main(int argc, const char** argv)
{
  try
  {
    int ret = run(argc, argv);
    common::writeMinimalStatFile(statFilename);
    return ret;
  }
  catch (const exception& ex)
  {
    cerr << "Error: " << ex.what() << endl;
  }
  catch (...)
  {
    cerr << "Error: unknown exception." << endl;
  }
  return EXIT_FAILURE;
}
