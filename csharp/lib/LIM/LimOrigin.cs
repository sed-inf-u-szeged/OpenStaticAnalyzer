using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Columbus.Lim.Asg
{
    public class LimOrigin : IHeaderData
    {
        protected Dictionary<KeyValuePair<uint, uint>, uint> compIdCSharpId2LimIdMap;
        protected Dictionary<uint, uint> extraPathMap;

        public LimOrigin()
        {
            compIdCSharpId2LimIdMap = new Dictionary<KeyValuePair<uint, uint>, uint>();
            extraPathMap = new Dictionary<uint, uint>();
        }

        public void save(IO binIo)
        {
            binIo.writeUInt4((uint)compIdCSharpId2LimIdMap.Count);
            foreach (var item in compIdCSharpId2LimIdMap)
            {
                binIo.writeUInt4(item.Key.Key);
                binIo.writeUInt4(item.Key.Value);
                binIo.writeUInt4(item.Value);
            }
            binIo.writeUInt4((uint)extraPathMap.Count);
            foreach (var it in extraPathMap)
            {
                binIo.writeUInt4(it.Key);
                binIo.writeUInt4(it.Value);
            }
        }

        public void load(IO binIo)
        {
            uint sizeCompIdCsharpId2LimIdMap = binIo.readUInt4();
            uint compId, csharpId, limId;
            for (int i = 0; i < sizeCompIdCsharpId2LimIdMap; i++)
            {
                compId = binIo.readUInt4();
                csharpId = binIo.readUInt4();
                limId = binIo.readUInt4();
                KeyValuePair<uint, uint> compId2CsharpId = new KeyValuePair<uint, uint>(compId, csharpId);
                compIdCSharpId2LimIdMap.Add(compId2CsharpId, limId);
            }
            uint sizeExtraPathMap = binIo.readUInt4();
            for (int i = 0; i < sizeExtraPathMap; i++)
            {
                uint nodeId = binIo.readUInt4();
                uint pathKey = binIo.readUInt4();
                extraPathMap.Add(nodeId, pathKey);
            }
        }

        public HeaderDataTypeKind Type
        {
            get { return HeaderDataTypeKind.hdkLimOrigin; }
        }

        public bool addCompIdCsharpIdLimIdToMap(uint compId, uint csharpId, uint limId)
        {
            KeyValuePair<uint, uint> compId2CsharpId = new KeyValuePair<uint, uint>(compId, csharpId);
            if (!compIdCSharpId2LimIdMap.ContainsKey(compId2CsharpId))
            {
                compIdCSharpId2LimIdMap.Add(compId2CsharpId, limId);
                return true;
            }
            return false;
        }

        public uint getLimIdToCompIdAndCsharpId(uint compId, uint CsharpId)
        {
            uint limId = 0;
            KeyValuePair<uint, uint> compId2CsharpId = new KeyValuePair<uint, uint>(compId, CsharpId);
            if (compIdCSharpId2LimIdMap.ContainsKey(compId2CsharpId))
            {
                limId = compIdCSharpId2LimIdMap[compId2CsharpId];
            }
            return limId;
        }

        public override string ToString()
        {
            string str = "";
            foreach (var item in compIdCSharpId2LimIdMap)
            {
                str += "Component (LIM)ID:" + item.Key.Key + " C# ASG ID:" + item.Key.Value + " LIM ID:" + item.Value + "\n";
            }
            return str;
        }
    }
}
