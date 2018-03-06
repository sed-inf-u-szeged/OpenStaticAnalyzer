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

/*
 * DistanceVisitor.h
 *
 *  Created on: Feb 25, 2011
 *      Author: lucla
 */

#ifndef DISTANCEVISITOR_H_
#define DISTANCEVISITOR_H_

#ifdef GENEALOGY
//when genealogy is maintained the previous factory is also needed

//DistanceVisitor used only when genealogy is needed!!!
class DistanceVisitor : public columbus::LANGUAGE_NAMESPACE::VisitorAbstractNodes {

    private:

      columbus::NodeId child;
      unsigned int l1;
      unsigned int l2;
      unsigned int l3;

      short state;
    public:
      DistanceVisitor(columbus::NodeId _child) : child(_child) ,l1(0), l2(0), l3(0), state(0) { };
    virtual void visit   (const Base& b , bool callParent) {
      if (b.getId()==child && state==0) {
        state=1;
        l2++;
      } else if (state==0) {
        l1++;
      } else if (state==1) {
        l2++;
      } else if (state==2) {
        l3++;
      }
      return;
    }
      virtual void visitEnd(const Base& b,bool callParent) {
        if (b.getId()==child && state==1) {
          state=2;
        } 
      }

      inline unsigned int getL1() const {
        return l1;
      }
      inline unsigned int getL2() const {
        return l2;
      }
      inline unsigned int getL3() const {
        return l3;
      }
    };
#endif

#endif /* DISTANCEVISITOR_H_ */
