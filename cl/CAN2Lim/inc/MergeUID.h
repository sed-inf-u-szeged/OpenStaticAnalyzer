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

#ifndef __CAN2LIM_MERGE_UID_H__
#define __CAN2LIM_MERGE_UID_H__

#include <clang/Metrics/UID.h>
#include <clang/Metrics/UIDFactory.h>

#include <clang/AST/AST.h>
#include <clang/AST/Mangle.h>

#include <boost/thread.hpp>

#include <string>


namespace clang
{
  class CompilerInstance;
}

class MergeUID : public clang::metrics::UID
{
public:
  MergeUID(const std::string& mangledName, std::string fileName, unsigned lineNumber, unsigned columnNumber, bool isNamespace);

  const std::string& getMangledName() const { return mangledName; }

  const std::string& getFilename() const { return fileName; }

  bool noPositionEquals(const MergeUID& o) const
  {
    return mangledName == o.mangledName;
    //return (isNamespace ? true : fileName == o.fileName) && mangledName == o.mangledName;
  }

private:
  bool equals(const UID& rhs) const override;
  std::size_t hash() const override;

  std::string getName() const override
  {
    return mangledName;
  }

private:
  const std::string mangledName;
  mutable std::string fileName;
  const unsigned lineNumber, columnNumber;
  const size_t hashValue;
  static boost::mutex m;

  const bool isNamespace;
public:
  //helpers for hashing in maps, unordered_maps, etc...
  // Helper for UID hashing.
  struct UIDHasher
  {
    typedef std::shared_ptr<const clang::metrics::UID> argument_type;
    typedef size_t result_type;

    result_type operator()(const argument_type& o) const
    {
      if (!o)
        return 0;

      return o->hash();
    }
  };

  // Helper for UID equivalence.
  struct UIDEq
  {
    typedef std::shared_ptr<const clang::metrics::UID> first_argument_type;
    typedef std::shared_ptr<const clang::metrics::UID> second_argument_type;
    typedef bool result_type;

    result_type operator()(const first_argument_type& lhs, const second_argument_type& rhs) const
    {
      if (!lhs || !rhs)
        return lhs.get() == rhs.get();

      return lhs->equals(*rhs);
    }
  };

  // Helper for UID equivalence.
  struct NoPosUIDEq
  {
    typedef std::shared_ptr<const MergeUID> first_argument_type;
    typedef std::shared_ptr<const MergeUID> second_argument_type;
    typedef bool result_type;

    result_type operator()(const first_argument_type& lhs, const second_argument_type& rhs) const
    {
      if (!lhs || !rhs)
        return lhs.get() == rhs.get();

      return lhs->noPositionEquals(*rhs);
    }
  };
};

class MergeUIDFactory : public clang::metrics::UIDFactory
{
public:
  std::unique_ptr<clang::metrics::UID> create(const clang::Decl* decl, std::shared_ptr<clang::MangleContext> mangleContext) override;
  std::unique_ptr<clang::metrics::UID> createTypeId(const clang::QualType type, std::shared_ptr<clang::MangleContext> mangleContext);

private:
  static void declContextName(clang::SourceManager& sm, llvm::raw_string_ostream& ss, const clang::DeclContext* parent);

  void mangleTypeName(const clang::Type* type, llvm::raw_string_ostream& ss, std::shared_ptr<clang::MangleContext> mangleContext);

private:
  std::string declToFileName(const clang::Decl* decl, clang::ASTContext& astContext);
  std::atomic<size_t> itsMissingIdCounter { 0 };
};


#endif
