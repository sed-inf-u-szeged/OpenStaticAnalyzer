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

#ifndef _ARCHCPP_AH_H_
#define _ARCHCPP_AH_H_

#include <memory>
#include <string>
#include <list>
#include <miniz.h>
#include <miniz_zip.h>

class ZipArchiveEntry : public mz_zip_archive_file_stat
{
  public:
    std::string GetFullName() const;
    uint64_t GetUncompressedSize() const;
    uint64_t GetCompressedSize() const;
    uint32_t GetCrc32() const;
    MZ_TIME_T GetLastWriteTime() const;
    uint32_t GetIndex() const;
};


class ZipArchive : public mz_zip_archive
{
  public:
    bool IsInArchive(const std::string& fileName);
    unsigned GetEntriesCount() const;
    std::list<ZipArchiveEntry> GetEntries();
    std::shared_ptr<ZipArchiveEntry> GetEntry(unsigned index);
    void Close();
    void ExtractFile(const std::string& fileName);
    void ExtractFile(const std::string& fileName, const std::string& outputName);
    void ExtractFile(unsigned index, const std::string& outputName);
    void AddFile(const std::string& fileName);
    void AddFile(const std::string& fileName, const std::string& inArchiveFileName);
    void CopyAllFromZip(ZipArchive& srcZip);
    void CopyFromZip(ZipArchive& srcZip, int index);
    ~ZipArchive();
};


class ZipFile
{
  public:
    static bool IsInArchive(const std::string& zipPath, const std::string& fileName);
    static bool AddFile(const std::string& zipPath, const std::string& fileName);
    static bool AddFile(const std::string& zipPath, const std::string& fileName, const std::string& inArchiveName);
    static std::unique_ptr<ZipArchive> OpenForReading(const std::string& zipPath);
    static std::unique_ptr<ZipArchive> OpenForWriting(const std::string& zipPath);
    static void ExtractFile(const std::string& zipPath, const std::string& fileName);
    static void ExtractFile(const std::string& zipPath, const std::string& fileName, const std::string& outputName);
};

class TemporalArhiveExtractor
{
  public:
    TemporalArhiveExtractor(const std::string& archiveFilename, const std::string& directoryName = "", bool cleanup = true);
    TemporalArhiveExtractor(const TemporalArhiveExtractor&) = delete;
    const TemporalArhiveExtractor& operator=(const TemporalArhiveExtractor&) = delete;
    TemporalArhiveExtractor(TemporalArhiveExtractor&&);
    ~TemporalArhiveExtractor();

    const std::list<std::string>& getFileList() const;
    void appendFileList(std::list<std::string>& fileListToExtend) const;

  private:
    std::list<std::string> contentFileList;
    std::string tempDirectoryName;
    const bool cleanup;
};

#endif
