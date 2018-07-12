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

#ifndef _LIM_ListIteratorAssocCD_H_
#define _LIM_ListIteratorAssocCD_H_

#include "lim/inc/lim.h"


namespace columbus { namespace lim { namespace asg {

  class ListIteratorAssocACDEdge : public ListIteratorAssoc<base::Base, acdLinkInfo>
  {

  public:
    ListIteratorAssocACDEdge (const ListIteratorAssocACDEdge& iterator);
    virtual ~ListIteratorAssocACDEdge();
    short getLowMul() ;
    short getHighMul() ;
    const std::string& getName() ;

  protected:
    //Container::iterator it;

    //ListIteratorAssocACDEdge(AssocContainer *assocContainer, AssocIteratorContainer *aitContainer, const Factory* factory);
    ListIteratorAssocACDEdge(const Container *container, const Factory* factory, bool createAsBegin);

    // ez szerintem felesleges, mert "nem lehet elrontani", es az ellenorzest a bellitasnal kell csinalni
    // elvegzi a szukseges ellenorzeseket mielott visszaadna egy asszociacios erteket
    // a ListIteratorAssocUShort::getAssocClass is elvegzi ezeket az ellenorzeseket,
    // en csak kiraktam ezt egy kulon metodusba, hogy elkeruljem a copy-pastinget
    void selfTest() const;

    StrTable& _stable;
    
    friend class ClassDiagram;
  };


}}}
#endif

