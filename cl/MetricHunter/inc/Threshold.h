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

#ifndef Threshold_H_
#define Threshold_H_

#include <vector>
#include <map>
#include <set>
#include <cstdlib>
#include <Exception.h>

namespace columbus { namespace rul {

  class Threshold {

  private:
    std::string m_id;
    std::string relation;
    std::string value;
    std::vector<std::string> entities;
    double val;

  public:
    const std::string& getMid() const { return m_id; }
    const std::string& getRelation() const { return relation; }
    const std::string& getValue() const { return value; }
    const std::vector<std::string>& getEntities() const { return entities; }
    std::string info() const;
    Threshold(const std::string cmid, const std::string crelation, const std::string cvalue, const std::vector<std::string>& centities) : m_id(cmid), relation(crelation), value(cvalue), entities(centities), val(atof(cvalue.c_str())) { };
    ~Threshold();

  }; //class


} } //rul, columbus
#endif /* Threshold_H_ */
