using System;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

using Columbus.Lim.Asg.Algorithms;

namespace Columbus.Lim.Asg {
    public delegate bool FuncPtrWithBaseParameterType(Nodes.Base.Base node);
    /// <summary>
    /// Collects the inverse relation of any "one way" defined edges.
 ///The reverse relation tells for a given node the non trivial nodes for which it has an incoming edge from.
    /// </summary>
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class ReverseEdges {

        private Factory fact;
        public List<Dictionary<Types.EdgeKind, LinkedList<uint>>> reContainer;
        public FuncPtrWithBaseParameterType selectorFunc;

        #region PossibleEdges
        public readonly bool[,] PossibleEdges ={ // nodes x edges
          {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
          {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,false,false,false,false},
          {false,true,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
          {false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
          {false,false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
          {false,false,false,false,false,true,false,false,true,false,false,false,false,false,false,false,false,false,true,false,false,true,false,true,false,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,false,false,false,false,false},
          {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
          {false,false,false,false,false,true,false,false,false,true,false,false,false,false,false,false,true,false,true,false,false,true,false,true,false,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,false,false,false,false,true},
          {false,false,false,false,false,true,false,false,false,true,false,false,false,false,false,true,true,false,true,false,false,true,false,true,false,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,false,false,false,false,true},
          {false,false,false,false,false,true,false,false,false,true,false,false,false,false,false,false,true,false,true,false,false,true,false,true,false,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,false,false,false,false,true},
          {false,false,false,false,false,true,false,false,false,true,false,false,false,false,false,true,true,false,true,false,false,true,false,true,false,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,false,false,false,false,true},
          {false,false,false,false,false,false,false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
          {false,false,false,false,false,true,false,false,false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,true},
          {false,false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,true,false,true,false,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,false,false,false,false,false},
          {false,false,false,true,false,true,false,false,false,false,false,false,false,false,false,false,true,false,true,false,false,true,false,true,false,true,false,true,false,false,false,false,false,false,false,false,true,false,false,false,false,false,true,false,false,false,false,false,false,false,false},
          {false,false,false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
          {false,false,false,true,false,true,false,false,false,false,false,false,false,false,false,false,true,false,true,false,false,true,false,true,false,true,false,true,false,false,false,false,false,false,false,false,true,false,false,false,true,false,true,false,false,false,false,false,false,false,false},
          {false,false,false,true,false,true,false,false,false,false,false,false,false,false,false,false,true,false,true,false,false,true,false,true,false,true,false,true,false,false,false,false,false,false,false,false,true,false,false,false,false,false,true,false,false,false,false,false,false,false,true},
          {false,false,false,true,false,true,false,false,false,false,false,false,false,false,false,false,true,false,true,false,false,true,false,true,false,true,false,true,false,false,false,false,false,false,false,false,true,false,false,false,true,false,true,false,false,false,false,false,false,false,false},
          {false,false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,true,false,true,false,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,false,false,false,false,false},
          {false,false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
          {false,false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,true,false,true,false,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,false,false,false,false,false},
          {false,false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,true,false,false,false,false},
          {true,false,true,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,true,true,false,false,false,false},
          {false,false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
          {false,false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,true,false,false,false,false},
          {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true},
          {false,false,false,false,false,false,false,true,false,false,false,true,false,true,true,false,false,true,false,false,false,false,false,false,false,false,true,false,false,false,true,false,false,true,true,true,false,false,true,true,false,true,false,false,false,false,false,false,true,true,false},
          {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false},
          {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false},
          {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false},
          {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false},
          {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false},
          {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false}        
};
        #endregion

        public ReverseEdges(Factory factory, FuncPtrWithBaseParameterType selectorFunction)  {
            fact = factory;
            selectorFunc = selectorFunction;
            reContainer = new List<Dictionary<Types.EdgeKind,  LinkedList<uint>>>();
            for (int i = 0; i < fact.Size; i++){
                reContainer.Add(null);
            }
            AlgorithmPreorder ap = new AlgorithmPreorder();
            ap.setSafeMode();
          ap.setVisitSpecialNodes(true, true);
          Visitors.VisitorReverseEdges visitor = new Visitors.VisitorReverseEdges(this);
          Factory.TurnFilterOffSafely tfos = new Factory.TurnFilterOffSafely(fact);
          ap.run(fact, visitor);
        }

        public ListIterator<Columbus.Lim.Asg.Nodes.Base.Base> constIteratorBegin(uint id, Types.EdgeKind edge) {
          if (reContainer.Count <= id || reContainer[(int)id] == null) {
            StackTrace st = new StackTrace(new StackFrame(true));
            StackFrame sf = st.GetFrame(0);
            throw new LimException(sf.GetFileName() + " : " + sf.GetFileLineNumber(),"Invalid NodeId(" + fact.getRef(id) + ")");
          }
          LinkedList<uint> it = null;
          if (reContainer[(int)id].TryGetValue(edge, out it)) {
            return new ListIterator<Columbus.Lim.Asg.Nodes.Base.Base>(it, fact, true);
          } else {
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(id);
            if (PossibleEdges[(int)node.NodeKind, (int)edge]) {
              // creating an empty container and returning with it
              LinkedList<uint> nodeList = new LinkedList<uint>();
              reContainer[(int)id].Add(edge, nodeList);
              return new ListIterator<Columbus.Lim.Asg.Nodes.Base.Base>(nodeList, fact, true);
            } else {
              StackTrace st = new StackTrace(new StackFrame(true));
              StackFrame sf = st.GetFrame(0);
              throw new LimException(sf.GetFileName() + " : " + sf.GetFileLineNumber(), "Invalid edge kind");
            }
          }
        }

        public ListIterator<Columbus.Lim.Asg.Nodes.Base.Base> constIteratorEnd(uint id, Types.EdgeKind edge) {
          if (reContainer.Count <= id || reContainer[(int)id] == null) {
            StackTrace st = new StackTrace(new StackFrame(true));
            StackFrame sf = st.GetFrame(0);
            throw new LimException(sf.GetFileName() + " : " + sf.GetFileLineNumber(),"Invalid NodeId(" + fact.getRef(id) + ")");
          }
          LinkedList<uint> it = null;
          if (reContainer[(int)id].TryGetValue(edge, out it)) {
            return new ListIterator<Columbus.Lim.Asg.Nodes.Base.Base>(it, fact, false);
          } else {
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(id);
            if (PossibleEdges[(int)node.NodeKind, (int)edge]) {
              // creating an empty container and returning with it
              LinkedList<uint> nodeList = new LinkedList<uint>();
              reContainer[(int)id].Add(edge, nodeList);
              return new ListIterator<Columbus.Lim.Asg.Nodes.Base.Base>(nodeList, fact, false);
            } else {
              StackTrace st = new StackTrace(new StackFrame(true));
              StackFrame sf = st.GetFrame(0);
              throw new LimException(sf.GetFileName() + " : " + sf.GetFileLineNumber(), "Invalid edge kind");
            }
          }
        }

        public void getAllExistingEdges(uint id, List<Types.EdgeKind> edges) {
          if (reContainer.Count <= id || reContainer[(int)id] == null) {
            StackTrace st = new StackTrace(new StackFrame(true));
            StackFrame sf = st.GetFrame(0);
            throw new LimException(sf.GetFileName() + " : " + sf.GetFileLineNumber(), "Invalid NodeId(" + fact.getRef(id) + ")");
          }
          edges.Clear();
          foreach (var item in reContainer[(int)id])
            edges.Add(item.Key);
        }

        public void getAllExistingEdges(uint id, HashSet<Types.EdgeKind> edges) {
          if (reContainer.Count <= id || reContainer[(int)id] == null) {
            StackTrace st = new StackTrace(new StackFrame(true));
            StackFrame sf = st.GetFrame(0);
            throw new LimException(sf.GetFileName() + " : " + sf.GetFileLineNumber(), "Invalid NodeId(" + fact.getRef(id) + ")");
          }
          edges.Clear();
          foreach (var item in reContainer[(int)id])
            edges.Add(item.Key);
        }

        public void getAllPossibleEdges(uint kind, List<Types.EdgeKind> edges) {
          edges.Clear();
          for (int i = 0; i < 51; ++i) {
            if (PossibleEdges[(int)kind, i]) {
              edges.Add((Types.EdgeKind)i);
            }
          }
        }

        public void getAllPossibleEdges(uint kind, HashSet<Types.EdgeKind> edges) {
          edges.Clear();
          for (int i = 0; i < 51; ++i) {
            if (PossibleEdges[(int)kind, i]) {
              edges.Add((Types.EdgeKind)i);
            }
          }
        }

        public void insertNode(uint id) {
          Factory.TurnFilterOffSafely turnFilterOffSafely = new Factory.TurnFilterOffSafely(fact);
          if (!fact.getExist(id)) {
            StackTrace st = new StackTrace(new StackFrame(true));
            StackFrame sf = st.GetFrame(0);
            throw new LimException(sf.GetFileName() + " : " + sf.GetFileLineNumber(), "Invalid NodeId (" + fact.getRef(id) + ")");
          }
          if (selectorFunc != null)
            if (!selectorFunc(fact.getRef(id)))
                return;
          for (int i = reContainer.Count; i < id + 1; i++){
              reContainer.Add(null);
          }
          if (reContainer[(int)id] == null){
            reContainer[(int)id] = new Dictionary<Types.EdgeKind, LinkedList<uint>>();
          }
        }

        public void removeNode(uint id) {
          // TODO
          Dictionary<Types.EdgeKind, LinkedList<uint>> pEdges = reContainer[(int)id];
          if (pEdges == null) {
            StackTrace st = new StackTrace(new StackFrame(true));
            StackFrame sf = st.GetFrame(0);
            throw new LimException(sf.GetFileName() + " : " + sf.GetFileLineNumber(), "");
          }
          Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(id);
          foreach (var pEdge in pEdges) {
            while (pEdge.Value.First != pEdge.Value.Last) {
              //fact.getRef(pEdge.Value.First.Value).removeEdge(pEdge.Key, node);
            }
          }
          var edges = reContainer[(int)id];
          edges = null;
        }

        public void insertEdge(uint from, uint to, Types.EdgeKind edge) {
          if (selectorFunc != null)
            if (!selectorFunc(fact.getRef(from)))
      return;
          insertEdge(fact.getRef(from),fact.getRef(to),edge);
        }

        public void insertEdge(Columbus.Lim.Asg.Nodes.Base.Base from, Columbus.Lim.Asg.Nodes.Base.Base to, Types.EdgeKind edge) {
          try {
            if (selectorFunc != null)
              if (!selectorFunc(from))
                 return;

            insertNode(from.Id);
          }
          catch (LimException) {
            StackTrace st = new StackTrace(new StackFrame(true));
            StackFrame sf = st.GetFrame(0);
            throw new LimException(sf.GetFileName() + " : " + sf.GetFileLineNumber(), "Invalid NodeId (" + fact.getRef(from.Id) + ")");
          }
        
          LinkedList<uint> it = null;
          if (reContainer[(int)from.Id].TryGetValue(edge, out it)) {
            it.AddLast(to.Id);
          } else {
            LinkedList<uint> nodeList = new LinkedList<uint>();
            nodeList.AddLast(to.Id);
            reContainer[(int)from.Id].Add(edge, nodeList);
          }
        }

        public void removeEdge(uint from, uint to, Types.EdgeKind edge) {
            if (reContainer.Count < from + 1)
              return;
            if (reContainer[(int)from] == null)
              return;
            LinkedList<uint> itFind = null;
            if (!reContainer[(int)from].TryGetValue(edge, out itFind))
              return;
            itFind.Remove(find(itFind.First, itFind.Last, to));
        }

        private uint find(LinkedListNode<uint> begin, LinkedListNode<uint> end, uint val) {
            while (begin != end){
              if (begin.Value == val) return val;
              begin = begin.Next;
            }
            return end.Value;
        }

    }
}