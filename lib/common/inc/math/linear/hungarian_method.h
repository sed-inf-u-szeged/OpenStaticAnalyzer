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

#ifndef __COLUMBUS__COMMON__MATH_HUNGARIAN_METHOD_H
#define __COLUMBUS__COMMON__MATH_HUNGARIAN_METHOD_H
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <queue>
#include <map>
#include <set>
#include <limits>

namespace common { namespace math {

  template<class nType, typename eType>
  class HungarianMethod {
  public:
    static const int INJECTIVE_KIND=1;
    static const int PARTIAL_KIND=1 << 1;
  private: 
    int kind;
    boost::numeric::ublas::matrix<eType>& m;
    std::map<unsigned int, unsigned int> zero_system;
    std::map<unsigned int, unsigned int> zero_system_inv;
    std::set<unsigned int> lekotott_sorok;
    std::set<unsigned int> lekotott_oszlopok;
    std::set<std::pair<unsigned int, unsigned int> > zero_primes;
    std::map<unsigned int, unsigned int> zero_primes_map;

    bool is_free(unsigned int i, unsigned int j) {
      if (lekotott_sorok.find(i)!=lekotott_sorok.end())
        return false;
      if (lekotott_oszlopok.find(j)!=lekotott_oszlopok.end())
        return false;
      std::map<unsigned int, unsigned int>::iterator iter;
      if ((iter=zero_system.find(j))!=zero_system.end()) {
        if (i==(*iter).second)
          return false;
      }
      std::pair<unsigned int, unsigned int> p(i,j);
      if (zero_primes.find(p)!=zero_primes.end())
        return false;
      return true;
    }
    void dump() {
      std::cout << "M=" << std::endl;
      for (unsigned i = 0; i < m.size1 (); ++ i) {
        boost::numeric::ublas::matrix_row<typename boost::numeric::ublas::matrix<eType> > mr((boost::numeric::ublas::matrix<eType>&)(m), i);
        for (unsigned j = 0; j < mr.size (); ++ j) {
          std::cout << mr(j) << ";";
        }
        std::cout << std::endl;
      }
      std::cout << "Zero System=" << std::endl;
      std::map<unsigned int, unsigned int>::iterator iter=zero_system.begin();
      while (iter!=zero_system.end()) {
        std::cout << "(" << (*iter).first << "," << (*iter).second << ") " ;
        iter++;
      }
      std::cout << std::endl;
    }
    void step_0() {
    /*  std::cout << "Step 0...Starting" << std::endl;
      dump();*/
      double linf=std::numeric_limits<double>::infinity();
      zero_system.clear();
      zero_system_inv.clear();
      for (unsigned i = 0; i < m.size1 (); ++ i) {
        boost::numeric::ublas::matrix_row<typename boost::numeric::ublas::matrix<eType> > mr((boost::numeric::ublas::matrix<eType>&)(m), i);
        eType min=mr(0);
        for (unsigned j = 1; j < mr.size (); ++ j)
          if (mr(j)<min)
            min=mr(j);
        if (min==linf) 
          continue;
        for (unsigned j = 0; j < mr.size (); ++ j) 
          if (mr(j)!=linf)
            mr(j)-=min;
        
      }
      std::set<unsigned int> tmp;
      for (unsigned i = 0; i < m.size2 (); ++ i) {
        boost::numeric::ublas::matrix_column<boost::numeric::ublas::matrix<eType> > mr ((boost::numeric::ublas::matrix<eType>&)m, i);
        eType min=mr(0);
        for (unsigned j = 1; j < mr.size (); ++ j) {
          if (mr(j)<min)
            min=mr(j);
        }
        if (min==linf) 
          continue;
        bool zero=false;
        for (unsigned j = 0; j < mr.size (); ++ j) {
          if (mr(j)!=linf)
            mr(j)-=min;
          if (mr(j)==(eType)0 && !zero) {
            if (tmp.find(j)==tmp.end()) {
              zero=true;
              zero_system.insert(std::map<unsigned int, unsigned int>::value_type(i,j));
              zero_system_inv.insert(std::map<unsigned int, unsigned int>::value_type(j,i));
              tmp.insert(j);
            }
          }
        }
      }
      /*std::cout << "Step 0...Finishing" << std::endl;
      dump();*/
    }
    void run() {
      double linf=std::numeric_limits<double>::infinity();
      step_0();
      std::pair<unsigned int, unsigned int> p;
      unsigned int i,j,k;
      std::map<unsigned int, unsigned int> zero_system_new;
      std::set<std::pair<unsigned int, unsigned int> > lanc;
step_1:
      if (zero_system.size()==m.size1()) {
        //we are ready!!!
        return;
      }
      
      lekotott_oszlopok.clear();
      for (std::map<unsigned int, unsigned int>::iterator iter=zero_system.begin(); iter!=zero_system.end(); iter++) {
        lekotott_oszlopok.insert((*iter).first);
      }
step_2:
      
      for (i=0; i < m.size1 (); ++ i) {
        if (lekotott_sorok.find(i)!=lekotott_sorok.end())
          continue;
        
        boost::numeric::ublas::matrix_row<boost::numeric::ublas::matrix<eType> > mr ((boost::numeric::ublas::matrix<eType>&)(m), i);
        for (j=0; j < mr.size (); ++ j){
          if (mr(j)!=(eType)0)
            continue;
          
          if (lekotott_oszlopok.find(j)!=lekotott_oszlopok.end())
            continue;
          
          std::map<unsigned int, unsigned int>::iterator itery;
          bool hasZeroStar=false;
          if ((itery=zero_system_inv.find(i))!=zero_system_inv.end()) { 
            if ((k=(*itery).second)==j)
              continue;
            else 
              hasZeroStar=true;
          }
          
          if (zero_primes.find(std::pair<unsigned int,unsigned int>(i,j))!=zero_primes.end())
            continue;
          
          if (!hasZeroStar)
            goto step_4;
          goto step_3;
        }
      }      
      goto step_5;
step_3:
      
      p=std::pair<unsigned int, unsigned int>(i,j);
      zero_primes.insert(p);
      zero_primes_map.insert(std::map<unsigned int, unsigned int>::value_type(i,j));
      lekotott_sorok.insert(i);
      lekotott_oszlopok.erase(k);
      goto step_2;
step_4:
      
      lanc.clear();
      p=std::pair<unsigned int, unsigned int>(i,j);
      zero_primes.insert(p);
      zero_primes_map.insert(std::map<unsigned int, unsigned int>::value_type(i,j));
      lanc.clear();
      lanc.insert(p);
      while (true) {
        std::map<unsigned int, unsigned int>::iterator iter=zero_system.find(j);
        if (iter==zero_system.end()) break;
        i=(*iter).second;
        p=std::pair<unsigned int, unsigned int>(i,j);
        lanc.insert(p);
        std::map<unsigned int, unsigned int>::iterator iter2;
        if ((iter2=zero_primes_map.find(i))!=zero_primes_map.end()) {
          j=(*iter2).second;
          lanc.insert(std::pair<unsigned int,unsigned int>(i,j));
          continue;
        }
        break;
      }
      zero_system_new=zero_system;
      zero_system.clear();
      zero_system_inv.clear();
      for (std::map<unsigned int, unsigned int>::iterator iter=zero_system_new.begin(); iter!=zero_system_new.end(); iter++) {
        p.first=(*iter).second;
        p.second=(*iter).first;
        if (lanc.find(p)==lanc.end()) {
          zero_system.insert(std::map<unsigned int, unsigned int>::value_type(p.second, p.first));
          zero_system_inv.insert(std::map<unsigned int, unsigned int>::value_type(p.first, p.second));
        }
      }
      for (std::set<std::pair<unsigned int, unsigned int> >::iterator iter2=zero_primes.begin(); iter2!=zero_primes.end(); iter2++) {
        p=(*iter2);
        if (lanc.find(p)!=lanc.end()) {
          zero_system_inv.insert(std::map<unsigned int, unsigned int>::value_type(p.first, p.second));
          zero_system.insert(std::map<unsigned int, unsigned int>::value_type(p.second, p.first));
        }
      }
      lekotott_oszlopok.clear();
      lekotott_sorok.clear();
      zero_primes.clear();
      zero_primes_map.clear();
      goto step_1;

step_5:
      bool go_on=false;
      eType min = eType();
      bool min_assigned=false;
      for (unsigned i = 0; i < m.size1 (); ++ i) {
        boost::numeric::ublas::matrix_row<boost::numeric::ublas::matrix<eType> > mr ((boost::numeric::ublas::matrix<eType>&)(m), i);
        for (unsigned j = 0; j < mr.size (); ++ j) {
          if (is_free(i,j)) {
            if (!min_assigned || mr(j)<min) 
              min=mr(j);
            min_assigned=true;
          }
        }
      }
      
      for (unsigned i = 0; i < m.size1 (); ++ i) {
        boost::numeric::ublas::matrix_row<boost::numeric::ublas::matrix<eType> > mr ((boost::numeric::ublas::matrix<eType>&)(m), i);
        for (unsigned j = 0; j < mr.size (); ++ j) {
          if (mr(j)==linf) continue;
          if (is_free(i,j)) {
            mr(j)=mr(j)-min;
            go_on=true;
          } 
        }
      }

      for (std::set<unsigned int>::iterator iter=lekotott_sorok.begin(); iter!=lekotott_sorok.end(); iter++) {
        for (std::set<unsigned int>::iterator iter2=lekotott_oszlopok.begin(); iter2!=lekotott_oszlopok.end(); iter2++) {
          if (m((*iter), (*iter2))==linf) continue;
          m((*iter), (*iter2))+=min;
          go_on=true;
        }
      }
      if (!go_on) {
        //cannot go on any more
        return;
      }
      goto step_2;
    }
  public: 
    HungarianMethod(boost::numeric::ublas::matrix<eType>& _m) : m((boost::numeric::ublas::matrix<eType>&)_m) {};
    std::map<unsigned int, unsigned int> solve(int _kind) { 
      double linf=std::numeric_limits<double>::infinity();
      kind=_kind;
      unsigned int prevRows=m.size1();
      unsigned int prevCols=m.size2();
      unsigned int imax=std::max(prevRows,prevCols);
      m.resize(imax, imax);
      for (unsigned int i=prevRows; i<imax; i++) {
        for (unsigned int j=0; j<imax; j++) {
          m(i,j)=linf;
        }
      }
      for (unsigned int i=prevCols; i<imax; i++) {
        for (unsigned int j=0; j<imax; j++) {
          m(j,i)=linf;
        }
      }
      run();

      return zero_system;
    };

  };
}}

#endif
