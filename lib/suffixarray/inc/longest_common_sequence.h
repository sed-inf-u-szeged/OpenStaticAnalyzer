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

#ifndef LCS_H
#define LCS_H

namespace columbus { namespace suffix_array {

template<class T>
class LCS {

private:
  T* first;
  T* second;
  unsigned int min;
  unsigned int max;

public:
  LCS(T* _first, T* _second, unsigned int _min, unsigned int _max) : first(_first), second(_second), min(_min), max(_max) { }
  double isDistant() {
    double ret=max+1;
    T* T1=new T[max+1];
    T* T2=new T[max+1];
    T* Q[2];
    Q[0]=T1;
    Q[1]=T2;
    unsigned int i=0;
    unsigned int j=0;
    for (i=0; i<=max; i++) {
      unsigned int imod2=i%2;
      unsigned int iMinusOne=(i+1)%2;
      for (j=0; j<=max; j++) {
        if (i==0 && j==0)
          Q[imod2][j]=0;
        else if (i==0) {
          Q[imod2][j]=j;
        }
        else if (j==0) {
          Q[imod2][j]=i;
        }
        else {
          T temp;
          temp=Q[iMinusOne][j-1];
          if (first[i-1]!=second[j-1]) temp++;
          T temp2=Q[iMinusOne][j]+1;
          if (temp2<temp) temp=temp2;

          temp2=Q[imod2][j-1]+1;
          if (temp2<temp) temp=temp2;
          Q[imod2][j]=temp;
          unsigned int max=i;
          if (j<i) max=j;
          if (i>=min && j>=min)
            if (ret>(double)temp/max)
              ret=(double)temp/max;
        }
      }
    }
    
    delete[] T1;
    delete[] T2;
    return ret;
  }
};

}}

#endif
