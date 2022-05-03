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
#ifdef __clang__
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wdelete-non-abstract-non-virtual-dtor"
  #pragma clang diagnostic ignored "-Wtautological-undefined-compare"
#endif

#include "archivecpp/inc/ArchiveHandler.h"
#include "archivecpp/inc/messages.h"
#include <common/inc/WriteMessage.h>
#include <common/inc/FileSup.h>
#include <common/inc/PlatformDependentDefines.h>
#include <Exception.h>

using namespace std;

std::string ZipArchiveEntry::GetFullName() const
{
  return m_filename;
}

uint64_t ZipArchiveEntry::GetUncompressedSize() const
{
  return m_uncomp_size;
}

uint64_t ZipArchiveEntry::GetCompressedSize() const
{
  return m_comp_size;
}

uint32_t ZipArchiveEntry::GetCrc32() const
{
  return m_crc32;
}

MZ_TIME_T ZipArchiveEntry::GetLastWriteTime() const
{
  return m_time;
}

uint32_t ZipArchiveEntry::GetIndex() const
{
  return m_file_index;
}

bool ZipArchive::IsInArchive(const std::string& fileName)
{
  return mz_zip_reader_locate_file(this, fileName.c_str(), nullptr, 0) != -1;
}

unsigned ZipArchive::GetEntriesCount() const
{
  return m_total_files;
}

std::list<ZipArchiveEntry> ZipArchive::GetEntries()
{
    std::list<ZipArchiveEntry> entries;
    for (unsigned i = 0; i < GetEntriesCount(); ++i)
    {
      entries.push_back(ZipArchiveEntry());
      if (mz_zip_reader_file_stat(this, i, &entries.back()) == MZ_FALSE)
        throw columbus::Exception(COLUMBUS_LOCATION, mz_zip_get_error_string(mz_zip_get_last_error(this)));
    }
    return entries;
}

shared_ptr<ZipArchiveEntry> ZipArchive::GetEntry(unsigned index)
{
  auto archiveEntry = make_shared<ZipArchiveEntry>();
  if (mz_zip_reader_file_stat(this, index, archiveEntry.get()) == MZ_FALSE)
    throw columbus::Exception(COLUMBUS_LOCATION, mz_zip_get_error_string(mz_zip_get_last_error(this)));

  return archiveEntry;
}

void ZipArchive::Close()
{
  if (m_zip_mode == MZ_ZIP_MODE_WRITING)
    if (mz_zip_writer_finalize_archive(this) == MZ_FALSE)
      throw columbus::Exception(COLUMBUS_LOCATION, mz_zip_get_error_string(mz_zip_get_last_error(this)));


  if (mz_zip_end(this) == MZ_FALSE)
    throw columbus::Exception(COLUMBUS_LOCATION, mz_zip_get_error_string(mz_zip_get_last_error(this)));
}

void ZipArchive::ExtractFile(const std::string& fileName)
{
  if (mz_zip_reader_extract_file_to_file(this, fileName.c_str(), fileName.c_str(), 0) == MZ_FALSE)
    throw columbus::Exception(COLUMBUS_LOCATION, mz_zip_get_error_string(mz_zip_get_last_error(this)));
}

void ZipArchive::ExtractFile(const std::string& fileName, const std::string& outputName)
{
  if (mz_zip_reader_extract_file_to_file(this, fileName.c_str(), outputName.c_str(), 0) == MZ_FALSE)
    throw columbus::Exception(COLUMBUS_LOCATION, mz_zip_get_error_string(mz_zip_get_last_error(this)));
}

void ZipArchive::ExtractFile(unsigned index, const std::string& outputName)
{
  if (mz_zip_reader_extract_to_file(this, index, outputName.c_str(), 0) == MZ_FALSE)
    throw columbus::Exception(COLUMBUS_LOCATION, mz_zip_get_error_string(mz_zip_get_last_error(this)));
}

void ZipArchive::AddFile(const std::string& fileName)
{
  if (mz_zip_writer_add_file(this, fileName.c_str(),  fileName.c_str(), nullptr, 0, MZ_DEFAULT_COMPRESSION) == MZ_FALSE)
    throw columbus::Exception(COLUMBUS_LOCATION, mz_zip_get_error_string(mz_zip_get_last_error(this)));
}

void ZipArchive::AddFile(const std::string& fileName, const std::string& inArchiveFileName)
{
  if (mz_zip_writer_add_file(this, inArchiveFileName.c_str(),  fileName.c_str(), nullptr, 0, MZ_DEFAULT_COMPRESSION) == MZ_FALSE)
    throw columbus::Exception(COLUMBUS_LOCATION, mz_zip_get_error_string(mz_zip_get_last_error(this)));
}

void ZipArchive::CopyAllFromZip(ZipArchive& srcZip)
{
  for (unsigned index = 0; index < srcZip.GetEntriesCount(); ++index)
    if (mz_zip_writer_add_from_zip_reader(this, &srcZip, index) == MZ_FALSE)
      throw columbus::Exception(COLUMBUS_LOCATION, mz_zip_get_error_string(mz_zip_get_last_error(this)));
}

void ZipArchive::CopyFromZip(ZipArchive& srcZip, int index)
{
  if (mz_zip_writer_add_from_zip_reader(this, &srcZip, index) == MZ_FALSE)
    throw columbus::Exception(COLUMBUS_LOCATION, mz_zip_get_error_string(mz_zip_get_last_error(this)));
}

ZipArchive::~ZipArchive()
{
  mz_zip_end(this);
}

bool ZipFile::IsInArchive(const std::string& zipPath, const std::string& fileName)
{
  return OpenForReading(zipPath)->IsInArchive(fileName);
}

bool ZipFile::AddFile(const std::string& zipPath, const std::string& fileName)
{
  return AddFile(zipPath, fileName, fileName);
}

bool ZipFile::AddFile(const std::string& zipPath, const std::string& fileName, const std::string& inArchiveName)
{
  string tempzipPath = zipPath + ".tmp";
  try {
    auto tempzip = OpenForWriting(tempzipPath);
    try {
      auto srczip = OpenForReading(zipPath);
      tempzip->CopyAllFromZip(*srczip);
      srczip->Close();
    }
    catch (const columbus::Exception& error)
    {
      common::WriteMsg::write(CMSG_MSG_ERROR_DURING_ADDING_TO_ARCHIVE_WARNING, error.getMessage().c_str());
    }
    tempzip->AddFile(fileName, fileName);
    tempzip->Close();
    remove(zipPath.c_str());
    rename(tempzipPath.c_str(), zipPath.c_str());
  }
  catch (const columbus::Exception& error)
  {
    common::WriteMsg::write(CMSG_MSG_ERROR_DURING_ADDING_TO_ARCHIVE_WARNING, error.getMessage().c_str());
    return false;
  }
  return true;
}

unique_ptr<ZipArchive> ZipFile::OpenForReading(const std::string& zipPath)
{
  auto archive = make_unique<ZipArchive>();
  mz_zip_zero_struct(archive.get());
  if (mz_zip_reader_init_file(archive.get(), zipPath.c_str(), 0) == MZ_FALSE)
    throw columbus::Exception(COLUMBUS_LOCATION, mz_zip_get_error_string(mz_zip_get_last_error(archive.get())));

  return archive;
}

unique_ptr<ZipArchive> ZipFile::OpenForWriting(const std::string& zipPath)
{
  auto archive = make_unique<ZipArchive>();
  mz_zip_zero_struct(archive.get());
  if (mz_zip_writer_init_file_v2(archive.get(), zipPath.c_str(), 0, MZ_ZIP_FLAG_WRITE_ZIP64) == MZ_FALSE)
    throw columbus::Exception(COLUMBUS_LOCATION, mz_zip_get_error_string(mz_zip_get_last_error(archive.get())));

  return archive;
}


void ZipFile::ExtractFile(const std::string& zipPath, const std::string& fileName)
{
    OpenForReading(zipPath)->ExtractFile(fileName);
}

void ZipFile::ExtractFile(const std::string& zipPath, const std::string& fileName, const std::string& outputName)
{
    OpenForReading(zipPath)->ExtractFile(fileName, outputName);
}

TemporalArhiveExtractor::TemporalArhiveExtractor(const string& archiveFilename, const string& directoryName, bool cleanup)
  : tempDirectoryName (directoryName.empty() ? common::getTemporaryName() : directoryName)
  , cleanup (cleanup)
{
  common::makeDirectory(tempDirectoryName);

  auto zipArchive = ZipFile::OpenForReading(archiveFilename);
  for (size_t entryIndex = 0; entryIndex < zipArchive->GetEntriesCount(); ++entryIndex)
  {
    auto zipEntry = zipArchive->GetEntry(entryIndex);

    /* Because the paths are too long, we have to do a little hack, and store these files with short paths as possible
        im not sure if this is going to lead to conflicting filenames tho... (BUG)

    string filename = zipEntryPtr->GetFullName();

    // We don't for sure, wether the filename stored in the zip is absolute or relative.
    // So we must check, because in the end, we want to work with an absolute path.
    if (common::pathIsRelative(filename))
      filename = tempDirectoryName + DIRDIVCHAR + filename;

    */
    // this is the hack, for shorter paths: (only get the filename from zip, without path)
    string filename = tempDirectoryName + DIRDIVCHAR + common::pathFindFileName(zipEntry->GetFullName());
    string directoryname = common::pathRemoveFileSpec(filename);

    if (filename != directoryname)
      common::makeDirectory(directoryname);

    contentFileList.push_back(filename);
    zipArchive->ExtractFile(zipEntry->GetIndex(), filename);
  }
}

TemporalArhiveExtractor::TemporalArhiveExtractor(TemporalArhiveExtractor&& b)
  : contentFileList(move(b.contentFileList))
  , tempDirectoryName(move(b.tempDirectoryName))
  , cleanup(b.cleanup)
{
}

TemporalArhiveExtractor::~TemporalArhiveExtractor()
{
  if (!tempDirectoryName.empty() && cleanup)
    common::pathDeleteFile(tempDirectoryName, true);
}

const std::list<std::string>& TemporalArhiveExtractor::getFileList() const
{
  return contentFileList;
}

void TemporalArhiveExtractor::appendFileList(std::list<std::string>& fileListToExtend) const
{
  for (const auto& filename : contentFileList)
    fileListToExtend.push_back(filename);
}
