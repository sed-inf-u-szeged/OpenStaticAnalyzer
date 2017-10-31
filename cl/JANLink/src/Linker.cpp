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

#include <fstream>
#include <time.h>
#include <ErrorCodes.h>
#include <common/inc/FileSup.h>
#include <common/inc/Stat.h>
#include <common/inc/WriteMessage.h>
#include <common/inc/PlatformDependentDefines.h>
#include "../inc/Linker.h"
#include "../inc/messages.h"
#include "../inc/VisitorStrMap.h"
#include "../inc/VisitorLinker.h"
#include "boost/date_time/posix_time/posix_time.hpp"

using namespace std;
using namespace common;
using namespace columbus;
using namespace columbus::java::linker;
using namespace columbus::java::asg;

const std::string Linker::TIME_STAMP = "TimeStamp";


static boost::posix_time::time_duration::tick_type milliseconds_since_epoch() {
  using boost::gregorian::date;
  using boost::posix_time::ptime;
  using boost::posix_time::microsec_clock;

  static ptime const epoch(date(1970, 1, 1));
  return (microsec_clock::universal_time() - epoch).total_milliseconds();
}

Linker::Linker(std::string OutputPath,
               std::string OutputFilterPath,
               bool bDumpJML,
               std::string mem,
               DirectoryFilter& filter,
               bool filterRefl,
               bool safemode,
               JANLinkStat& janlinkStat,
               std::string changesetID)
  : filter(filter),
    filterRefl(filterRefl),
    _OutputPath(OutputPath),
    _OutputFilterPath(OutputFilterPath),
    _bDumpJML(bDumpJML),
    _maxMemMB(mem.length() ? atol(mem.c_str()) : 0), // 0: do not check
    _safemode(safemode),
    _stt(0),
    _fact(0),
    janlinkStat(janlinkStat),
    _changesetID(changesetID)
{
  updateMemoryStat();
}

Linker::~Linker() {
  if (_stt) delete _stt;
  if (_fact) delete _fact;
}

columbus::java::asg::Factory* Linker::getFactory() {
  return _fact;
}

void Linker::updateMemoryStat() {
  memstat mstat = getProcessUsedMemSize();
  if (janlinkStat.peakMemory < mstat.size)
    janlinkStat.peakMemory = mstat.size;
}

ErrorCode Linker::link(std::list<std::string>& csiList) {
  ErrorCode ec = retLinkingOK;
  ErrorCode save_ec;

  ec = loadASG(csiList);

  save_ec = saveASG();
  if (ec == retASGLoadOK)
    ec = save_ec;

  // create JML dump
  if (_bDumpJML)
    saveJML();

  return (ec == retASGSaveOK) ? retLinkingOK : ec;
}

ErrorCode Linker::loadASG(std::list<std::string>& JSIList) {
  ErrorCode ec = retASGLoadOK;

  _stt = new columbus::RefDistributorStrTable();
  _fact = new columbus::java::asg::Factory(*_stt);
  if (JSIList.empty()) return retASGLoadOK;

  // reverse edges are required for deleting nodes
  _fact->enableReverseEdges();

  // generate non-generic unique name for methods
  Common::setGenerateNonGenericSignatureForMethods(true);

  // collect unique strings
  columbus::java::linker::UniqueMap _strmap;
  columbus::java::linker::StrNodeIdMap _pathMap;

  VisitorStrMap vstr(_strmap, _pathMap);
  AlgorithmPreorder algPre;
  if(_safemode)
    algPre.setSafeMode();
  algPre.run(*_fact,vstr);

  updateMemoryStat();

  std::set<std::string> extraAsgs;
  for (std::list<std::string>::iterator i = JSIList.begin(); i != JSIList.end(); ++i) {
    WriteMsg::write(CMSG_LOAD_FILE, i->c_str());

    columbus::RefDistributorStrTable tmpStt;
    columbus::java::asg::Factory tmpFact(tmpStt);

    CsiHeader tmpHeader;
#ifndef _DEBUG
    try {
#endif
      tmpFact.load(*i, tmpHeader);
#ifndef _DEBUG
    } catch (IOException e) {
      WriteMsg::write(CMSG_CANNOT_OPEN_FILE, i->c_str());
      ec = retASGLoadWarning;
      continue;
    }
#endif

    //adding the extra jsi to the input list
    std::string extra;
    if (tmpHeader.get("ExtraAsg", extra)) {
      if (extraAsgs.insert(extra).second)
        JSIList.push_back(extra);
    }

    janlinkStat.inputFiles++;

    VisitorLinker vlinker(_strmap, _pathMap, *_fact, tmpFact);
    columbus::java::asg::AlgorithmPreorder algPre;
    if (_safemode)
      algPre.setSafeMode();
    algPre.run(tmpFact,vlinker);

    updateMemoryStat();
  }

  return ec;
}

ErrorCode Linker::saveASG() {
  WriteMsg::write(CMSG_SAVING_MERGED_ASG, _OutputPath.c_str());

  // delete the old filter file (if any)
  pathDeleteFile(_OutputFilterPath);

  //if (filterRefl || !filter.isEmpty())
  {
    bool tmpFiltRefl = filterRefl;
    if (!filterRefl && filter.isEmpty())
      tmpFiltRefl = true;
    _fact->initializeFilter();
    JANFilter janFilter(*_fact, filter, tmpFiltRefl);
    AlgorithmPreorder ap;
    ap.setVisitSpecialNodes(true, true);
    ap.run(*_fact, janFilter, *_fact->getRoot());
  }

  _fact->sort();

  CsiHeader header;
  std::stringstream ss;
  ss << milliseconds_since_epoch();
  header.add(TIME_STAMP, ss.str());
  if (!_changesetID.empty()) {
    header.add(CsiHeader::csih_ChangesetID, _changesetID);
  }
  _fact->save(_OutputPath, header);

  if (filterRefl || !filter.isEmpty()){
    WriteMsg::write(CMSG_SAVING_FILTER_FILE, _OutputFilterPath.c_str());
    _fact->saveFilter(_OutputFilterPath);
  }

  return retASGSaveOK;
}

void Linker::saveJML() {
  std::string filename = pathRemoveExtension(_OutputPath);
  pathAddExtension(filename, jmlext);

  std::ofstream ofs(filename.c_str());
  if (!ofs.is_open()) return;

  WriteMsg::write(CMSG_SAVING_MERGED_JML, filename.c_str());
  columbus::java::asg::VisitorJAVAML* v = new columbus::java::asg::VisitorJAVAML(ofs, "");
  columbus::java::asg::AlgorithmPreorder algPre;
  if(_safemode)
    algPre.setSafeMode();
  algPre.run(*_fact,*v,*_fact->getRoot());
  delete v;
  ofs.close();
}

