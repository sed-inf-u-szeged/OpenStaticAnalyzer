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

#include "common/inc/math/common.h"
#include <iostream>
#include <cstdlib>

namespace common { namespace math {

/**
* Forward declaration needed
**/  
uint32_t ExpModDWORD(uint32_t value, uint32_t exp, uint32_t mod);

bool isPrime(uint32_t prime)
{

      // randomWitness = witness that the "prime" is NOT composite
      // 1 < randomWitness < prime-1
      uint32_t totalWitness = 15;
      uint32_t randomWitness[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
      uint32_t primeMinusOne = prime - 1;
      uint32_t oddMultiplier;
      uint32_t bitLength;
      uint32_t i, j;
      uint32_t result;

      // find oddMultiplier, defined as "prime - 1 = (2^B) * M"
      // get bitLength (B) and find the oddMultiplier (M)

      // init value multiplier
      oddMultiplier = primeMinusOne;

      bitLength = 0; // reset
      while(!(oddMultiplier & 1))
      { // it is even

            oddMultiplier >>= 1; // right shift
            bitLength++;
      }

      for(i = 0; i < totalWitness; i++)
      {

          // init value of result = (randomWitness ^ oddMultiplier) mod prime
          result = ExpModDWORD(randomWitness[i], oddMultiplier, prime);

          // is y = 1 ?
          if(result == 1)
                continue; // maybe prime


            // is y = prime-1 ?
            if(result == primeMinusOne)
                  continue; // maybe prime

            // loop to get AT LEAST one "result = primeMinusOne"
            for(j = 1; j <= bitLength; j++)
            {
                  // square of result
                  result = ExpModDWORD(result, 2, prime);

                  // is result = primeMinusOne ?
                  if(result == primeMinusOne)
                        break; // maybe prime
            }

            if(result != primeMinusOne)
                  return true; // COMPOSITE
      }

      // it may be pseudoprime/prime
      return false;

}

uint32_t ExpModDWORD(uint32_t value, uint32_t exp, uint32_t mod)
{

      // use uint64_t 64bits to prevent overflow when calculate 32bit x 32bit
      uint64_t ullResult = 1;
      uint64_t ullValue = value;

      while(exp)
      {
            if(exp & 1)
            { // odd
                  // result = (result * value) % mod
                  ullResult *= ullValue;
                  ullResult %= mod;
            }

            // value = (value * value) % mod
            ullValue *= ullValue;
            ullValue %= mod;

            // exp = exp / 2
            exp >>= 1;
      }

      return((uint32_t) ullResult);
}


unsigned int editDistanceRec(const std::vector<int>& v1, unsigned int lastV1, const std::vector<int>& v2, unsigned int lastV2) {
  if (lastV1==0 && lastV2==0) return 0;
  if (lastV1==0) return lastV2;
  if (lastV2==0) return lastV1;
  int ch1=v1[lastV1-1];
  int ch2=v2[lastV2-1];
  unsigned int temp = editDistanceRec(v1, lastV1-1, v2, lastV2-1);
  if (ch1!=ch2) temp++;
  unsigned int temp2 = editDistanceRec(v1, lastV1, v2, lastV2-1) + 1;
  if (temp2<temp) temp=temp2;
  temp2 = editDistanceRec(v1, lastV1-1, v2, lastV2) + 1;
  if (temp2<temp) temp=temp2;
  return temp;
}
size_t editDistance(const std::vector<int>& v1, const std::vector<int>& v2, unsigned int bound) {
  if (v1.size()==0) return v2.size();
  if (v2.size()==0) return v1.size();
  
  unsigned int* T1=(unsigned int*)malloc((v2.size()+1)*sizeof(unsigned int));
  unsigned int* T2=(unsigned int*)malloc((v2.size()+1)*sizeof(unsigned int));
  unsigned int *T[2];
  T[0]=T1;
  T[1]=T2;
  
  unsigned int i=0;
  unsigned int j=0;
  unsigned int limit = std::numeric_limits<unsigned>::max();
  for (i=0; i<=v1.size(); i++) {
    unsigned int imod2=i%2;
    unsigned int iMinusOne=(i+1)%2;
    for (j=0; j<=v2.size(); j++) {
      if (i==0 && j==0)
        T[imod2][j]=0;
      else if (i==0) {
        if (j>bound) {
          T[imod2][j]=bound;
          limit=j;
          break;
        }
        T[imod2][j]=j;
      }
      else if (j==0) {
        T[imod2][j]=i;
      }
      else {
        unsigned int temp;
        if (j-1<limit) {
          temp=T[iMinusOne][j-1];
          if (v1[i-1]!=v2[j-1]) temp++;
        } else 
          temp=bound;

        unsigned int temp2;
        if (j<limit) {
          temp2=T[iMinusOne][j]+1;
        } else
          temp2=bound;
        if (temp2<temp) temp=temp2;

        temp2=T[imod2][j-1]+1;
        if (temp2<temp) temp=temp2;
        T[imod2][j]=temp;
        if (temp>=bound && j>=limit) {
          if (i==v1.size()) {
            free(T1);
            free(T2);
            return bound;
          }
          T[imod2][j]=bound;
          limit=j;
          break;
        }
      }
    }
  }
  unsigned int ret=T[v1.size()%2][v2.size()];
  free(T1);
  free(T2);
  return ret;
}
size_t editDistance(const std::string& v1, const std::string& v2, unsigned int bound) {
  std::vector<int> i1;
  std::vector<int> i2;
  for (unsigned int i=0; i<v1.size(); i++) {
    i1.push_back(v1[i]);
  }
  for (unsigned int j=0; j<v2.size(); j++) {
    i2.push_back(v2[j]);
  }
  return editDistance(i1,i2, bound);
}

}}
