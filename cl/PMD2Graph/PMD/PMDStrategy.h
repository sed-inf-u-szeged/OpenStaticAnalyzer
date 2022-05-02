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

#ifndef _PMDSTRATEGY_H
#define _PMDSTRATEGY_H

#include <set>
#include <xercesc/dom/DOMNodeList.hpp>
#include <rul/inc/RulHandler.h>
#include "../CheckerStrategy.h"

struct PMD2GraphStat {
  typedef list<const char *> ErrorFileList;
  ErrorFileList error_files;
};

extern PMD2GraphStat stats;

class PMDStrategy : public CheckerStrategy{
public:
  PMDStrategy() : CheckerStrategy() { }
  virtual ~PMDStrategy(){}
  virtual void makeRul(File_Names&, std::string& rul, std::string& rulConfig, std::string& rul_option_filename);
  virtual void makeConfig(File_Names& file_names, std::string& rul, std::string& rulConfig, std::string& configFile);
  virtual void makeCsv(std::string& lim, std::string& rul, std::string& rulConfig, File_Names& file_names, std::string& metrics, std::string& groupedmetrics, std::string& monitor, std::string& checkerbasedir, std::string& pathfrom, std::string& pathto, FILE *f);
protected:
  virtual void setConstantData(columbus::rul::RulHandler& rh);
private:
  typedef map<string, string> StringMap;

  std::string pmd2InternalGroupName(const std::string& pmdGroup);

  //makeRul section
  void makeRulByFile(const char*, columbus::rul::RulHandler&);
  void getDescription(std::string& desc, XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* node);
  bool getIsOnlySpaces(std::string& in);
  //makeConfig section
  void builddom(std::map<std::string, std::set<std::string> >& rulesetMap, std::string& configFile);
  //makeCsv section
  void collectdata(std::string& fileName,columbus::rul::RulHandler& rul, std::string& checkerbasedir, std::string& pathfrom, std::string& pathto, FILE *f);

  std::string separateName(const std::string &name);

  columbus::rul::TagKindMetadataContainer *general_tag_metadata_container_;
};

#endif
