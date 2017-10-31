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

#ifndef ThresholdReader_H_
#define ThresholdReader_H_

#include <vector>
#include <map>
#include <set>
#include <Exception.h>
#include <iterator>

#include  "Threshold.h"

namespace columbus { namespace rul {

  class ThresholdReaderException : public columbus::Exception {
  public:
    ThresholdReaderException(const std::string &location, const std::string &message) : Exception(location, message) {
    }

    virtual const std::string getClassName() const {
      return "columbus::rul::ThresholdReaderException";
    }
  };

  class ThresholdReader
  {
  private:
    std::vector<Threshold> trs;
    std::set<std::string> entities;
    const std::string _filename;
    bool _xerces_inited;

  public:
    static const std::string _empty_string;
    static int xercesInited;

    ThresholdReader(const std::string& trsFileName);
    ~ThresholdReader();

    std::vector<Threshold> getThresholdVector() const { return trs; }
    std::set<std::string> getDefinedEntites() const { return entities; }

  protected:

    static void xercesInit();
    static void xercesTerminate();
    void parseXML();
  };

} }

#endif /* ThresholdReader_H_ */
