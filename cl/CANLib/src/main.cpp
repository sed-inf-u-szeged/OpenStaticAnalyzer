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

#define PROGRAM_NAME "CANLib"
#define EXECUTABLE_NAME "CANLib"

#ifdef __clang__
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wdelete-non-abstract-non-virtual-dtor"
  #pragma clang diagnostic ignored "-Wtautological-undefined-compare"
#endif

#include <ReleaseVersion.h>
#include <common/inc/Arguments.h>
#include <common/inc/FileSup.h>
#include <common/inc/Stat.h>
#include <common/inc/PlatformDependentDefines.h>
#include <MainCommon.h>
#include <ctime>
#include <archivecpp/inc/ArchiveHandler.h>
#include <boost/filesystem.hpp>
#include "../inc/messages.h"


using namespace std;
using namespace common;
using namespace columbus;

namespace
{
  enum class OperationMode
  {
    None,
    Add,
    Extract,
    Delete,
    List
  } operationMode = OperationMode::None;


  bool replaceEnabled = true;
  bool filenameOnly = false;
  bool noWriteTime = false;
  bool oneLevelOnly = false;
  list<string> listOfInputFiles;
  string archiveFilename;
  string outputFilename;

  bool ppDisableReplace( const Option *o, char *argv[])
  {
    replaceEnabled = false;
    return true;
  }

  bool ppOMAdd( const Option *o, char *argv[])
  {
    operationMode = OperationMode::Add;
    return true;
  }

  bool ppOMDelete( const Option *o, char *argv[])
  {
    operationMode = OperationMode::Delete;
    return true;
  }

  bool ppOMExtract( const Option *o, char *argv[])
  {
    operationMode = OperationMode::Extract;
    return true;
  }

  bool ppOMList( const Option *o, char *argv[])
  {
    operationMode = OperationMode::List;
    return true;
  }

  bool ppList (const Option *o, char *argv[])
  {
    return loadStringListFromFile(argv[0], listOfInputFiles);
  }

  bool ppOutput (const Option *o, char *argv[])
  {
    outputFilename = argv[0];
    return true;
  }

  bool ppFilenameOnly(const Option *o, char *argv[])
  {
    filenameOnly = true;
    return true;
  }

  bool ppOneLevelOnly(const Option *o, char *argv[])
  {
    oneLevelOnly = true;
    return true;
  }

  bool ppNoTime(const Option *o, char *argv[])
  {
    noWriteTime = true;
    return true;
  }
}

static void ppFile( char *filename)
{
  if (archiveFilename.empty())
    archiveFilename = filename;
  else
    listOfInputFiles.push_back(filename);
}


const Option OPTIONS_OBJ [] = {
  { false,  "-add",                     0, "",                 1, OT_WS,          ppOMAdd,               NULL,   "Operation: add ast files to the archive"},
  { false,  "-delete",                  0, "",                 1, OT_WS,          ppOMDelete,            NULL,   "Operation: delete ast files from the archive"},
  { false,  "-extract",                 0, "",                 1, OT_WS,          ppOMExtract,           NULL,   "Operation: extract ast files from the archive"},
  { false,  "-list",                    0, "",                 1, OT_WS,          ppOMList,              NULL,   "Operation: list the content of the archive"},
  { false,  "-nowritetime",             0, "",                 1, OT_WS,          ppNoTime,              NULL,   "Do not print the TIME column during the list operation"},
  { false,  "-output",                  1, "",                 0, OT_WC,          ppOutput,              NULL,   "Output filename for extraction operation"},
  { false,  "-disablereplace",          0, "",                 0, OT_WS,          ppDisableReplace,      NULL,   "Disable replacing files, which already exist in the archive"},
  { false,  "-filenameonly",            0, "",                 0, OT_WS,          ppFilenameOnly,        NULL,   "Store and extract files with the filename only"},
  { false,  "-onelevelonly",            0, "",                 0, OT_WS,          ppOneLevelOnly,        NULL,   "Store files with maximum one subdirectory only"},
  CL_INPUT_LIST
  COMMON_CL_ARGS
};


namespace
{

  int execute()
  {
    int result = EXIT_SUCCESS;

    if (archiveFilename.empty())
    {
      WriteMsg::write(CMSG_MSG_MISSING_ARCHIVE_NAME_ERROR);
      return EXIT_FAILURE;
    }
    if (operationMode == OperationMode::None)
    {
      return EXIT_FAILURE;
    }

    if (operationMode == OperationMode::Add)
    {
      string directoryname = common::pathRemoveFileSpec(archiveFilename);
      if (archiveFilename != directoryname)
        common::makeDirectory(directoryname);

      list<ZipArchiveEntry> srcEntries;
      unique_ptr<ZipArchive> srcZip;
      unique_ptr<ZipArchive> tempZip;
      string tempZipPath = archiveFilename + ".tmp";
      map<string, string> filesToAdd;

      if (common::pathFileExists(archiveFilename))
      {
        try
        {
          srcZip = ZipFile::OpenForReading(archiveFilename);
          srcEntries = srcZip->GetEntries();
        }
        catch (const columbus::Exception& error)
        {
          printf("ERROR: %s\n", error.getMessage().c_str());
        }
      }

      tempZip = ZipFile::OpenForWriting(tempZipPath);

      for (auto filename : listOfInputFiles)
      {
        string modifiedFilename;
        filename = correctDirDivsToUnix(filename);

        if (filenameOnly)
          modifiedFilename = common::pathFindFileName(filename);

        else if (oneLevelOnly)
        {
          std::stack<boost::filesystem::path> pathPartStack;

          for (const auto& part : boost::filesystem::path(filename))
            pathPartStack.push(part);

          boost::filesystem::path shortName;
          for (int i = 0; i < 2 && !pathPartStack.empty(); ++i)
          {
            shortName = pathPartStack.top() / shortName;
            pathPartStack.pop();
          }

          modifiedFilename = shortName.string();
        }
        else
           modifiedFilename = filename;

        if (auto sameSrcEntryIt = find_if(srcEntries.begin(), srcEntries.end(), [&modifiedFilename](const ZipArchiveEntry& v) { return v.GetFullName() == modifiedFilename; }); sameSrcEntryIt != srcEntries.end())
        {
          if (!replaceEnabled)
          {
            WriteMsg::write(CMSG_MSG_FILE_ALREADY_EXISTS_WARNING, modifiedFilename.c_str());
            continue;
          }
          else
          {
            srcEntries.erase(sameSrcEntryIt);
          }

        }

        if (filenameOnly)
          filesToAdd[filename] = filename;
        else if (oneLevelOnly)
          filesToAdd[filename] = modifiedFilename;
        else
          filesToAdd[filename] = filename;
      }

      for (const auto& srcZipEntry : srcEntries)
        tempZip->CopyFromZip(*srcZip, srcZipEntry.GetIndex());

      for (const auto& fileToAdd : filesToAdd)
      {
        try
        {
          tempZip->AddFile(fileToAdd.first, fileToAdd.second);
        }
        catch (const columbus::Exception& error)
        {
          WriteMsg::write(CMSG_MSG_FAILED_TO_ADD_ERROR, fileToAdd.first.c_str(), error.toString().c_str());
          result = EXIT_FAILURE;
          break;
        }
      }

      tempZip->Close();
      if (srcZip)
        srcZip->Close();

      remove(archiveFilename.c_str());
      rename(tempZipPath.c_str(), archiveFilename.c_str());

    }
    else if (operationMode == OperationMode::Extract)
    {
      const bool dirOutput = common::pathIsDirectory(outputFilename);

      if (listOfInputFiles.size() > size_t(1) && !dirOutput)
      {
        WriteMsg::write(CMSG_MSG_OUTPUT_MUST_BE_A_DIRECTORY_ERROR, outputFilename.c_str());
        return EXIT_FAILURE;
      }

      if (listOfInputFiles.empty())
      {
        auto zipArchive = ZipFile::OpenForReading(archiveFilename);
        for (size_t entryIndex = 0; entryIndex < zipArchive->GetEntriesCount(); ++entryIndex)
        {
          auto zipEntry = zipArchive->GetEntry(entryIndex);
          listOfInputFiles.push_back(zipEntry->GetFullName());
        }
      }

      auto zipArchive = ZipFile::OpenForReading(archiveFilename);
      for (auto filename : listOfInputFiles)
      {
        filename = correctDirDivsToUnix(filename);
        if (!zipArchive->IsInArchive(filename))
        {
          WriteMsg::write(CMSG_MSG_NO_SUCH_FILE_IN_THE_ARCHIVE_ERROR, filename.c_str());
          return EXIT_FAILURE;
        }

        try
        {
          if (filenameOnly && outputFilename.empty())
          {
            zipArchive->ExtractFile(filename);
          }
          else if (outputFilename.empty())
          {
            string directoryname = common::pathRemoveFileSpec(filename);
            if (filename != directoryname)
              common::makeDirectory(directoryname);
            zipArchive->ExtractFile(filename, filename);
          }
          else  //  filenameOnly && !outputFilename.empty()
          {     // !filenameOnly && !outputFilename.empty()
            if (dirOutput)
            {
              if (filenameOnly)
              {
                string nameWithoutDirectory = common::pathFindFileName(filename);
                zipArchive->ExtractFile(filename, outputFilename + DIRDIVCHAR + nameWithoutDirectory);
              }
              else
              {
                string directoryname = common::pathRemoveFileSpec(filename);
                if (filename != directoryname)
                  common::makeDirectory(outputFilename + DIRDIVCHAR + directoryname);
                zipArchive->ExtractFile(filename, outputFilename + DIRDIVCHAR + filename);
              }
            }
            else
            {
              zipArchive->ExtractFile(filename, outputFilename);
            }
          }
        }
        catch (const std::runtime_error& error)
        {
          WriteMsg::write(CMSG_MSG_FAILED_TO_EXTRACT_ERROR, filename.c_str(), error.what());
          return EXIT_FAILURE;
        }
      }
    }
    else if (operationMode == OperationMode::Delete)
    {
      auto zipArchive = ZipFile::OpenForReading(archiveFilename);
      auto srcEntries = zipArchive->GetEntries();

      for (auto filename : listOfInputFiles)
      {
        filename = correctDirDivsToUnix(filename);

        if (auto sameSrcEntryIt = find_if(srcEntries.begin(), srcEntries.end(), [&filename](const ZipArchiveEntry& v) { return v.GetFullName() == filename; }); sameSrcEntryIt != srcEntries.end())
        {
          srcEntries.erase(sameSrcEntryIt);
        }
        else
        {
          WriteMsg::write(CMSG_MSG_NO_SUCH_FILE_IN_THE_ARCHIVE_ERROR, filename.c_str());
          return EXIT_FAILURE;
        }
      }

      string tempZipPath = archiveFilename + ".tmp";
      auto tempZip = ZipFile::OpenForWriting(tempZipPath);

      for (const auto& srcZipEntry : srcEntries)
        tempZip->CopyFromZip(*zipArchive, srcZipEntry.GetIndex());

      tempZip->Close();
      zipArchive->Close();

      remove(archiveFilename.c_str());
      rename(tempZipPath.c_str(), archiveFilename.c_str());
    }
    else if (operationMode == OperationMode::List)
    {
      try
      {
        FILE *outputFile = nullptr;
        if (!outputFilename.empty())
        {
          outputFile = fopen(outputFilename.c_str(), "wt");
          if (outputFile == nullptr)
          {
            WriteMsg::write(CMSG_MSG_FILE_ERROR, outputFilename.c_str(), "Failed to open");
            return EXIT_FAILURE;
          }
          WriteMsg::setOuputFile(outputFile);
        }

        auto zipArchive = ZipFile::OpenForReading(archiveFilename);
        if (noWriteTime)
        {
          WriteMsg::write(WriteMsg::mlNormal, "  #    ORIG SIZE   CMPR  CRC-32  NAME\n");
          WriteMsg::write(WriteMsg::mlNormal, "----- ------------ ---- -------- ------\n");
          for (uint32_t entryIndex = 0; entryIndex < zipArchive->GetEntriesCount(); ++entryIndex)
          {
            auto zipEntry = zipArchive->GetEntry(entryIndex);
            WriteMsg::write(WriteMsg::mlNormal, "%5zu %12zu %3zu%% %8X %s\n",
              entryIndex,
              zipEntry->GetUncompressedSize(),
              zipEntry->GetUncompressedSize() > 0 ? zipEntry->GetCompressedSize() * 100 / zipEntry->GetUncompressedSize() : 0,
              zipEntry->GetCrc32(),
              zipEntry->GetFullName().c_str()
            );
          }
        }
        else
        {
          WriteMsg::write(WriteMsg::mlNormal, "  #    ORIG SIZE   CMPR    DATE       TIME       CRC-32  NAME\n");
          WriteMsg::write(WriteMsg::mlNormal, "----- ------------ ---- ---------- ------------ -------- ------\n");
          for (uint32_t entryIndex = 0; entryIndex < zipArchive->GetEntriesCount(); ++entryIndex)
          {
            auto zipEntry = zipArchive->GetEntry(entryIndex);
            time_t lastWriteTime = zipEntry->GetLastWriteTime();
            char buffer[30];
            strftime(buffer, 30, "%Y-%m-%d %H:%M:%S %Z", localtime(&lastWriteTime));

            WriteMsg::write(WriteMsg::mlNormal, "%5zu %12zu %3zu%% %s %8X %s\n",
              entryIndex,
              zipEntry->GetUncompressedSize(),
              zipEntry->GetUncompressedSize() > 0 ? zipEntry->GetCompressedSize() * 100 / zipEntry->GetUncompressedSize() : 0,
              buffer,
              zipEntry->GetCrc32(),
              zipEntry->GetFullName().c_str()
            );
          }
        }

        if (outputFile != nullptr)
        {
          WriteMsg::setOuputFile(stdout);
          fclose(outputFile);
        }
      }
      catch (const std::runtime_error& error)
      {
        WriteMsg::write(CMSG_MSG_FILE_ERROR, archiveFilename.c_str(), error.what());
        return EXIT_FAILURE;
      }
    }
    else if (operationMode == OperationMode::None)
    {
      WriteMsg::write(CMSG_MSG_NO_OPERATION_MODE_ERROR);
      return EXIT_FAILURE;
    }

    return result;
  }
}

int main( int argc, char *argv[]) {
  int result;
  WriteMsg::setAutomaticFlush(true);
  MAIN_BEGIN
    MainInit( argc, argv, "-");
    result = execute();

  MAIN_END

  fflush(stdout);
  return result;
}
