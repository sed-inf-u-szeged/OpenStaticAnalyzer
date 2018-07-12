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

#ifndef __SUFFIX_ARRAY
#define __SUFFIX_ARRAY
#include<set>
#include<vector>
#include<queue>
#include<stack>
#include<map>

#include "sequence.h"

namespace columbus { namespace suffix_array {

template<class T>
class SuffixArray {

public:

  class CloneClass{
  public:
    unsigned int num;
    unsigned int length;
    unsigned int* position;
    bool hasPartialClones;
  public:
    CloneClass() : num(0), length(0), position(NULL), hasPartialClones(false) {}
    ~CloneClass() {
      delete[] position;
    }
  };

  class CloneVisitor {

  public:
    virtual void visit(CloneClass&) = 0;
    virtual ~CloneVisitor(){}
  };

  class Duplicateiterator {

  private:

    struct IntervalData {
      unsigned lcp;
      int lb;
      int rb;
      IntervalData(unsigned lcp, int lb, int rb) : lcp(lcp), lb(lb), rb(rb) {}
    };


    SuffixArray<T>& suffixArray;
    unsigned int current;
    unsigned int current_lcp;
    unsigned int min_length;
    unsigned int max_length;
    unsigned int min_occurance;
    std::vector<CloneClass> classes;
    bool _extendable;
  public:
    Duplicateiterator(SuffixArray<T>& _suffixArray, unsigned int _min_length, unsigned int _max_length = 0, unsigned int _min_occurance = 0, bool filterextendable = true) : suffixArray(_suffixArray), current(0), current_lcp(0), min_length(_min_length), max_length(_max_length), min_occurance(_min_occurance), _extendable(filterextendable) {}


    /**
     * paper:
     * Replacing suffix trees with enhanced suffix arrays
     * Mohamed Ibrahim Abouelhoda, Stefan Kurtz, Enno Ohlebusch
     *
     *
     * Computation of lcp-intervals
     * push( 0, 0, ⊥ )
     * for i := 1 to n do
     *   lb := i − 1
     *   while lcptab[i] < top.lcp
     *     top.rb := i − 1
     *     interval := pop
     *     report(interval)
     *     lb := interval.lb
     *   if lcptab[i] > top.lcp then
     *     push( lcptab[i], lb, ⊥ )
     *
     */

    void run(CloneVisitor& visitor /*void (*process)(CloneClass&)*/ ) {
      if(suffixArray.sequence.getLength() == 0)
        return;
      bool* leftExt = new bool[suffixArray.sequence.getLength()];

      leftExt[0] = false;

      std::stack<IntervalData> intervalStack;
      intervalStack.push(IntervalData(0, 0, -1));

      for(size_t i = 1; i < suffixArray.sequence.getLength(); ++i) {
        leftExt[i] = !(suffixArray.suffixes[i].position == 0 || suffixArray.suffixes[i-1].position == 0 || (suffixArray.sequence[suffixArray.suffixes[i].position-1]!=suffixArray.sequence[suffixArray.suffixes[i-1].position-1]));
        int lb = i - 1;

        while(suffixArray.suffixes[i].lcp < intervalStack.top().lcp) {
          intervalStack.top().rb = i - 1;
          //process()
          unsigned int num = intervalStack.top().rb - intervalStack.top().lb + 1;
          if(intervalStack.top().lcp >= min_length && ( max_length == 0 ||  intervalStack.top().lcp <= max_length ) && (num >= min_occurance)) {
            // create clone class and instances
            bool leftExtendable = true;
            CloneClass cc;
            cc.length = intervalStack.top().lcp;
            cc.num = num;
            int begin = intervalStack.top().lb;
            int end = intervalStack.top().rb;
            cc.position = new unsigned int[num];
            cc.position[0] = suffixArray.suffixes[begin].position;

            for(int y = begin + 1, pos_count = 1; y <= end; ++y, ++pos_count) {
              leftExtendable = (leftExtendable && (_extendable && leftExt[y]));
              cc.position[pos_count] = (suffixArray.suffixes[y].position);
            }
            if(!leftExtendable) {
              visitor.visit(cc);
            }
          }

          lb = intervalStack.top().lb;
          intervalStack.pop();
        }
        if(suffixArray.suffixes[i].lcp > intervalStack.top().lcp ) {
          intervalStack.push(IntervalData(suffixArray.suffixes[i].lcp, lb, -1));
        }
      }
      while(!intervalStack.empty()) {
        intervalStack.top().rb = suffixArray.sequence.getLength() - 1;
        //process()
        unsigned int num = intervalStack.top().rb - intervalStack.top().lb + 1;
        if(intervalStack.top().lcp >= min_length && ( max_length == 0 ||  intervalStack.top().lcp <= max_length ) && (num >= min_occurance)) {
          // create clone class and instances
          bool leftExtendable = true;
          CloneClass cc;
          cc.length = intervalStack.top().lcp;
          cc.num = 0;
          cc.position = new unsigned int[num];
          int begin = intervalStack.top().lb;
          int end = intervalStack.top().rb;
          cc.num = num;

          cc.position[0] = suffixArray.suffixes[begin].position;
          for(int y = begin+1, pos_count = 1; y <= end; ++y, ++pos_count) {
            leftExtendable = (leftExtendable && (_extendable && leftExt[y]));
            cc.position[pos_count] = (suffixArray.suffixes[y].position);
          }
          if(!leftExtendable) {
            visitor.visit(cc);
          }
        }

        intervalStack.pop();
      }
      delete[] leftExt;
    }
  };

  Duplicateiterator iterator(unsigned int _min_length, unsigned int _max_length = 0, unsigned int _min_occurance = 0, bool filterextendable = true) {
    return  Duplicateiterator(*this, _min_length, _max_length, _min_occurance, filterextendable);
  }

protected:

  typedef struct {
    unsigned int position;
    unsigned int lcp;
  } SuffixArrayElement;


  Sequence<T>& sequence;
  SuffixArrayElement* suffixes;

  SuffixArray(Sequence<T>& _sequence) : sequence(_sequence), suffixes(NULL) {}


public:

  virtual ~SuffixArray() {
    delete [] suffixes;
  }

};


template<class T>
class LinearSuffixArray : public SuffixArray<T> {

  using SuffixArray<T>::sequence;
  using SuffixArray<T>::suffixes;

protected:
  inline bool leq(unsigned a1, unsigned a2, unsigned b1, unsigned b2) { // lexic. order for pairs
    return(a1 < b1 || (a1 == b1 && a2 <= b2));
  }

  // and triples
  inline bool leq(unsigned a1, unsigned a2, unsigned a3, unsigned b1, unsigned b2, unsigned b3) {
    return(a1 < b1 || (a1 == b1 && leq(a2,a3, b2,b3)));
  }

  // stably sort a[0..n-1] to b[0..n-1] with keys in 0..K from r
  static void radixPass(unsigned* a, unsigned* b, unsigned* r, unsigned n, unsigned K) {
    int* c = new int[K + 1];                          // counter array
    for (unsigned i = 0;  i <= K;  i++) c[i] = 0;         // reset counters
    for (unsigned i = 0;  i < n;  i++) c[r[a[i]]]++;    // count occurences
    for (unsigned i = 0, sum = 0;  i <= K;  i++) { // exclusive prefix sums
       int t = c[i];  c[i] = sum;  sum += t;
    }
    for (unsigned i = 0;  i < n;  i++) b[c[r[a[i]]]++] = a[i];      // sort
    delete [] c;
  }

  // find the suffix array SA of s[0..n-1] in {1..K}^n
  // require s[n]=s[n+1]=s[n+2]=0, n>=2
  void suffixArray(unsigned* s, unsigned* SA, unsigned n, unsigned K) {
    unsigned n0=(n+2)/3, n1=(n+1)/3, n2=n/3, n02=n0+n2;
    unsigned* s12  = new unsigned[n02 + 3];  s12[n02]= s12[n02+1]= s12[n02+2]=0;
    unsigned* SA12 = new unsigned[n02 + 3]; SA12[n02]=SA12[n02+1]=SA12[n02+2]=0;
    unsigned* s0   = new unsigned[n0];
    unsigned* SA0  = new unsigned[n0];

      // generate positions of mod 1 and mod  2 suffixes
      // the "+(n0-n1)" adds a dummy mod 1 suffix if n%3 == 1
      for (unsigned i=0, j=0;  i < n+(n0-n1);  i++) if (i%3 != 0) s12[j++] = i;

      // lsb radix sort the mod 1 and mod 2 triples
      radixPass(s12 , SA12, s+2, n02, K);
      radixPass(SA12, s12 , s+1, n02, K);
      radixPass(s12 , SA12, s  , n02, K);

      // find lexicographic names of triples
      unsigned name = 0, c0 = -1, c1 = -1, c2 = -1;
      for (unsigned i = 0;  i < n02;  i++) {
        if (s[SA12[i]] != c0 || s[SA12[i]+1] != c1 || s[SA12[i]+2] != c2) {
          name++;  c0 = s[SA12[i]];  c1 = s[SA12[i]+1];  c2 = s[SA12[i]+2];
        }
        if (SA12[i] % 3 == 1) { s12[SA12[i]/3]      = name; } // left half
        else                  { s12[SA12[i]/3 + n0] = name; } // right half
      }

      // recurse if names are not yet unique
      if (name < n02) {
        suffixArray(s12, SA12, n02, name);
        // store unique names in s12 using the suffix array
        for (unsigned i = 0;  i < n02;  i++) s12[SA12[i]] = i + 1;
      } else // generate the suffix array of s12 directly
        for (unsigned i = 0;  i < n02;  i++) SA12[s12[i] - 1] = i;

      // stably sort the mod 0 suffixes from SA12 by their first character
      for (unsigned i=0, j=0;  i < n02;  i++) if (SA12[i] < n0) s0[j++] = 3*SA12[i];
      radixPass(s0, SA0, s, n0, K);

      // merge sorted SA0 suffixes and sorted SA12 suffixes
      for (unsigned p=0,  t=n0-n1,  k=0;  k < n;  k++) {
    #define GetI() (SA12[t] < n0 ? SA12[t] * 3 + 1 : (SA12[t] - n0) * 3 + 2)
        unsigned i = GetI(); // pos of current offset 12 suffix
        unsigned j = SA0[p]; // pos of current offset 0  suffix
        if (SA12[t] < n0 ?
            leq(s[i],       s12[SA12[t] + n0], s[j],       s12[j/3]) :
            leq(s[i],s[i+1],s12[SA12[t]-n0+1], s[j],s[j+1],s12[j/3+n0]))
        { // suffix from SA12 is smaller
          SA[k] = i;  t++;
          if (t == n02) { // done --- only SA0 suffixes left
            for (k++;  p < n0;  p++, k++) SA[k] = SA0[p];
          }
        } else {
          SA[k] = j;  p++;
          if (p == n0)  { // done --- only SA12 suffixes left
            for (k++;  t < n02;  t++, k++) SA[k] = GetI();
          }
        }
      }
      delete [] s12; delete [] SA12; delete [] SA0; delete [] s0;
  }

  /*
   * paper:
   * Toru Kasai, Gunho Lee, Hiroki Arimura, Setsuo Arikawa, and Kunsoo Park
   * Linear-Time Longest-Common-Prefix Computation in Suffix Arrays and Its Applications
   *
   * Algorithm GetHeight
   * input: A text A and its suffix array Pos
   * 1 for i:=1 to n do
   * 2 Rank[Pos[i]] := i
   * 3 od
   * 4 h:=0
   * 5 for i:=1 to n do
   * 6 if Rank[i] > 1 then
   * 7 k := Pos[Rank[i]-1]
   * 8 while A[i+h] = A[k+h] do
   * 9 h := h+1
   * 10 od
   * 11 Height[Rank[i]] := h
   * 12 if h > 0 then h := h-1 fi
   * 13 fi
   * 14 od
   */
    void computeLCP(unsigned* normSeq, unsigned* sa, int n) {
      //suffixes = new SuffixArray<T>::SuffixArrayElement()[n];
      suffixes = new typename SuffixArray<T>::SuffixArrayElement[n];
      unsigned* Rank = new unsigned[n];
      for(int i = 0; i < n; ++i) {
        Rank[sa[i]] = i;
        suffixes[i].position = sa[i];
      }
      int h = 0;
      int k = 0;
      suffixes[0].lcp = 0;
      for(int i = 0; i < n; ++i) {
        if(Rank[i] > 0) {
          k = sa[Rank[i]-1];
          while(normSeq[i+h] == normSeq[k+h]) h++;
          suffixes[Rank[i]].lcp = h;
          if( h > 0) h--;
        }
      }
      delete[] Rank;
    }

public:

    /**
     * Paper:
     * Two Efficient Algorithms for Linear Suffix Array Construction
     * Ge Nong, Sen Zhang, Wai Hong Chan
     *
     */
  LinearSuffixArray(Sequence<T>& _sequence) : SuffixArray<T>(_sequence) {
    if(_sequence.getLength() > 1) {
      unsigned* sa = new unsigned[sequence.getLength()];

      std::map<T, size_t> seqMap;
      std::set<T> values;
      // create normalize map
      for(size_t i = 0; i < sequence.getLength(); ++i) {
        values.insert(sequence[i]);
      }

      size_t seqCounter = 1;
      for(typename std::set<T>::iterator it = values.begin(); it != values.end(); ++it) {
        seqMap.insert(std::make_pair(*it, seqCounter++));
      }

      // create normalized sequence
      unsigned* normSeq = new unsigned[sequence.getLength() + 3];


      for(size_t i = 0; i < sequence.getLength(); ++i) {
        typename std::map<T, size_t>::iterator it = seqMap.find(sequence[i]);
        if(it != seqMap.end()) {
          normSeq[i] = it->second;
        } else {
          // it can't be
        }
      }
      normSeq[sequence.getLength()] = normSeq[sequence.getLength() + 1] = normSeq[sequence.getLength() + 2] = 0;
      suffixArray(normSeq, sa, sequence.getLength(), seqCounter);
      computeLCP(normSeq, sa, sequence.getLength());
      delete[] sa;
      delete[] normSeq;
    }
  }
};


template<class T>
class UniversalSuffixArray : public SuffixArray<T> {

  using SuffixArray<T>::sequence;
  using SuffixArray<T>::suffixes;

public:

  UniversalSuffixArray(Sequence<T>& _sequence) : SuffixArray<T>(_sequence) {
    std::set<SubSequence<T> > subsequences;
    for (unsigned int i=0; i<sequence.getLength(); i++) {
      subsequences.insert(sequence.createSubSequence(i));
    }
    suffixes=new typename SuffixArray<T>::SuffixArrayElement[subsequences.size()];
    typename std::set<SubSequence<T> >::const_iterator iter=subsequences.begin();
    unsigned int count=0;
    while (iter!=subsequences.end()) {
      const SubSequence<T>& current=*iter;
      suffixes[count].position=current.getFirst();
      suffixes[count].lcp=0;
      if (count!=0) {
        unsigned int offset=0;
        while ((suffixes[count-1].position+offset<sequence.getLength() && suffixes[count].position+offset<sequence.getLength()) && (sequence[suffixes[count-1].position+offset] == sequence[suffixes[count].position+offset])) {
          offset++;
        }
        suffixes[count].lcp=offset;
      }
      count++;
      iter++;
    }
  }
};

}}
#endif
