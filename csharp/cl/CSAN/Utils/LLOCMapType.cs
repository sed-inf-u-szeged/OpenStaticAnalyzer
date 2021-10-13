using System.Collections.Generic;

namespace Columbus.CSAN.Utils
{

    using PathLineMapType = Dictionary<uint, HashSet<uint>>;

    class LLOCMapType : IEnumerable<KeyValuePair<uint, PathLineMapType>>
    {
        Dictionary<uint, PathLineMapType> map;

        public LLOCMapType()
        {
            map = new Dictionary<uint, Dictionary<uint, HashSet<uint>>>();
        }

        public void Add(uint NodeId, uint pathKey, uint line)
        {
            if (map.ContainsKey(NodeId))
            {
                if (map[NodeId].ContainsKey(pathKey))
                {
                    map[NodeId][pathKey].Add(line);
                }
                else
                {
                    HashSet<uint> lines = new HashSet<uint>();
                    lines.Add(line);
                    map[NodeId].Add(pathKey, lines);
                }
            }
            else
            {
                Dictionary<uint, HashSet<uint>> lloc = new Dictionary<uint, HashSet<uint>>();
                HashSet<uint> lines = new HashSet<uint>();
                lines.Add(line);
                lloc.Add(pathKey, lines);
                map.Add(NodeId, lloc);
            }
        }

        public bool ContainsKey(uint key)
        {
            return map.ContainsKey(key);
        }

        public PathLineMapType this[uint key]
        {
            get { return map[key]; }
        }

        public IEnumerator<KeyValuePair<uint, PathLineMapType>> GetEnumerator()
        {
            return map.GetEnumerator();
        }

        System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        public void Clear()
        {
            map.Clear();
        }
    }
}
