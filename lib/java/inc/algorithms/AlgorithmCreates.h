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

#ifndef _ALGORITHMCREATES_JAVA_H
#define _ALGORITHMCREATES_JAVA_H

/*! \file AlgorithmCreates.h
    \brief Contains the class `AlgorithmCreates' which collects the class instantiation relations in the ASG.
*/

namespace columbus { namespace java { namespace asg {

/** 
* \en
* Collects the class instantiation relations in the ASG.
* Traverses the whole ASG and collects create relations (nested class ::Relation represents it).
* Create relationship exists between a XXXX and a class when the function instantiates object of the class.
* After the run of the algorithm for each function the instantiated class 
* nodes can be enumerated using AlgorithmCreates::constIterator(NodeId function) and similarly
* for each class the functions which instantiate the class can be enumerated using the AlgorithmCreates::constInIterator(NodeId function).
* The Algorithm does not modify the ASG. The relation edges are stored separately,
* they only points to appropriate nodes in the ASG.
* Therefore the Algorithm should be run once on the ASG and the collected information can be used after.
* Do not run the algorithm more times to get information on different classes/functions.
* \_en
*
* \hu
* .
* \_hu
*/  
class AlgorithmCreates : public Algorithm {
public:
  
protected:
  typedef std::set<NodeId>     Creates;
  typedef std::map<NodeId, Creates>  Container;

public:
  /** 
  * \en
  * Nested constant iterator class which enumerates the created classes.
  * \_en
  *
  * \hu
  * .
  * \_hu
  */  
  class ConstIterator {
    friend class AlgorithmCreates;
  private:
    ConstIterator(const Container*, const Factory* , NodeId );
  public:
    /** 
    * \en
    * Returns true if there is other instantiation place
    * \_en
    *
    * \hu
    * Visszatérési érték true, ha még van meg nem mutatott példányosítási pont.
    * \_hu
    */  
    bool hasNext() const;
    /** 
    * \en
    * Returns the constant id of the next instantiation point.
    * \_en
    *
    * \hu
    * Visszatér a következo példányosítás hely id-jával.
    * \_hu
    */  
    const NodeId next();
  private:
    const Container  *createsCont;
    const Factory    *factory;
    Container::const_iterator i;
    Creates::const_iterator j;
  };

  const ConstIterator constIterator(NodeId classId) const  {return ConstIterator(&createsCont, factory, classId);}
  bool isEmpty() const  {return createsCont.size() == 0;}
  int size() const  {return createsCont.size();}
  int size(NodeId node) const  {
      Container::const_iterator iter = createsCont.find(node);
      return (iter != createsCont.end())? iter->second.size() : 0;
  }

public:
  AlgorithmCreates() : createsCont(), factory (NULL) {}
  virtual ~AlgorithmCreates()  {}

  void run(Factory& fact);

  void getTypeIdKeys(std::set<NodeId>& keySet) const {
      keySet.clear();
      for(Container::const_iterator iter = createsCont.begin(); iter != createsCont.end(); ++ iter)
          keySet.insert(iter->first);
  }

protected:
  Container createsCont;
  Factory* factory;
private:
  AlgorithmCreates(const AlgorithmCreates&);
  AlgorithmCreates& operator=(const AlgorithmCreates&);
};

}}}

#endif
