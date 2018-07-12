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

#ifndef _DCF_CPPNODEEV_H_
#define _DCF_CPPNODEEV_H_

#include "../common.h"
#include <map>
#include <list>

/***
 * \brief This is an abstract class to collect information of clone embedding.
 *  If you want use this it need to implement visit function that is interesting for the clone embedding.
 */

class NodeEmbeddednessVisitorBase : public columbus::LANGUAGE_NAMESPACE::VisitorAbstractNodes {
public :

  //this structure is identify the node form the language asg.
  struct NodeGlobalId {
    NodeId componenetId; //identifier for the component in the lim schema
    NodeId nodeId;       //identifier for the node from the language asg 

    bool operator< (const  NodeGlobalId& other) const {
      if (componenetId != other.componenetId)
        return componenetId < other.componenetId;
     
      return nodeId < other.nodeId;
    }

    bool operator== (const  NodeGlobalId& other) const {
      return  (componenetId == other.componenetId) && ( nodeId == other.nodeId);
    }

    NodeGlobalId(NodeId componenetId,  NodeId nodeId) :componenetId(componenetId),nodeId(nodeId){}
    NodeGlobalId():componenetId(0),nodeId(0){}
  };

  struct NdcWeight {
    unsigned ndc;       // the distance of two node
    bool multiplicity;  // when this flag is true, then all occurrences should be calculate for the clone instance.
    NdcWeight(unsigned ndc ,bool multiplicity):ndc(ndc),multiplicity(multiplicity){}
    NdcWeight():ndc(0),multiplicity(false){}
  };

  struct NodeWithWeight {
     NodeGlobalId nodeUniqueId; //the joined node global identifier
     NdcWeight    ndcWeight;       //the weight of node connection.
     NodeWithWeight ( NodeGlobalId nodeUniqueId, NdcWeight ndcWeight):nodeUniqueId(nodeUniqueId),ndcWeight(ndcWeight){}
     NodeWithWeight ():nodeUniqueId(NodeGlobalId()),ndcWeight(NdcWeight()){}
  };
  /***
   * \brief this structure is store the node connection. The first node id is which in the clone. and it contain the list
   *  which node is connect to the node in the clone instance whit the connected nodeId and the number of directory change.
   */
  typedef std::map< NodeGlobalId, std::list< NodeWithWeight > > ConectedEdgesMap;
  typedef std::map< NodeId, NodeGlobalId > NodeAliasMap; //Component id lim node id and the destination

  NodeEmbeddednessVisitorBase(ConectedEdgesMap& mapTofill,const columbus::dcf::DuplicatedCodeMiner& dcf):
  conectedEdgesMap(mapTofill),limComponenetId(0),dcf(dcf),alias(0,0),aliasMode(false) {}
  virtual ~NodeEmbeddednessVisitorBase(){}
  NodeId LimComponenetId() const { return limComponenetId; }
  void   LimComponenetId(NodeId val) { limComponenetId = val; }

  static int calculateNDC(const std::string& path1,const std::string& path2) {
    boost::filesystem::path p1(path1);
    boost::filesystem::path p2(path2);
    boost::filesystem::path::iterator iterator1=p1.begin();
    boost::filesystem::path::iterator iterator2=p2.begin();

    unsigned int dist=0;
    while (iterator1!=p1.end() && iterator2!=p2.end()) {
      if ((*iterator1)!=(*iterator2))
        break;

      iterator1++;
      iterator2++;
    }

    while (iterator1!=p1.end()) {
      dist++;
      iterator1++;
    }
    while (iterator2!=p2.end()) {
      dist++;
      iterator2++;
    }

    //If the both file is not in the same directory the 2nd file change does not matter
    if (dist > 1)
      dist--;

    dist++;
    return dist;
  }

protected:
  /***
   * \brief this map is filled by the visitor when find the correspond connection.
   */
  ConectedEdgesMap& conectedEdgesMap;
 
  NodeId limComponenetId;
  const columbus::dcf::DuplicatedCodeMiner& dcf;
  NodeGlobalId     alias;
  bool aliasMode;
public:
  NodeAliasMap     aliasMap;
  void setAlias(NodeEmbeddednessVisitorBase::NodeGlobalId val) { aliasMode =true; alias = val; }
  void resetAlias(NodeEmbeddednessVisitorBase::NodeGlobalId val) { aliasMode =false;  }
};

#endif
