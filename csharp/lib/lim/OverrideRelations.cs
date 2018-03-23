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

using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Columbus.Lim.Asg
{
    public enum FlagType { Single, Multi }

    public class OverrideRelations : IHeaderData
    {
        protected class OverrideStruct
        {
            public FlagType Flag { get; set; }
            public uint Id { get; set; }
            public LinkedList<uint> List { get; set; }

            public OverrideStruct()
            {
                List = new LinkedList<uint>();
            }
        }

        protected Dictionary<uint, OverrideStruct> _overrides;

        protected Factory _factory;

        public OverrideRelations(Factory fact)
        {
            _overrides = new Dictionary<uint, OverrideStruct>();
            _factory = fact;
        }

        public void save(IO binIo)
        {
            binIo.writeUInt4((uint)_overrides.Count);
            foreach (var @override in _overrides)
            {
                binIo.writeUInt4(@override.Key);
                if (@override.Value.Flag == FlagType.Single)
                {
                    binIo.writeUInt4(1);
                    binIo.writeUInt4(@override.Value.Id);
                }
                else
                {
                    binIo.writeUInt4((uint)@override.Value.List.Count);
                    foreach (uint ids in @override.Value.List)
                    {
                        binIo.writeUInt4(ids);
                    }
                }
            }
        }

        public void load(IO binIo)
        {
            uint size = binIo.readUInt4();
            for (int i = 0; i < size; i++)
            {
                uint id = binIo.readUInt4();
                uint numOfOverrides = binIo.readUInt4();
                OverrideStruct oStruct = new OverrideStruct();
                if (numOfOverrides == 1)
                {
                    oStruct.Flag = FlagType.Single;
                    oStruct.Id = binIo.readUInt4();
                }
                else
                {
                    oStruct.Flag = FlagType.Multi;
                    oStruct.List = new LinkedList<uint>();
                    for (int j = 0; j < numOfOverrides; j++)
                    {
                        oStruct.List.AddLast(binIo.readUInt4());
                    }
                }
                _overrides.Add(id, oStruct);
            }

        }

        public HeaderDataTypeKind Type
        {
            get { return HeaderDataTypeKind.hdkOverride; }
        }

        public void AddOverride(uint mid, uint omid)
        {
            if (!_factory.getExist(mid) || !_factory.getExist(omid))
            {
                throw new LimException("", "The end point of the override edge does not exist");
            }
            Nodes.Base.Base mnode = _factory.getRef(mid);
            Nodes.Base.Base onode = _factory.getRef(omid);

            if (Common.getIsMethod(mnode) && Common.getIsMethod(onode))
            {
                if (!_overrides.ContainsKey(mid))
                {
                    OverrideStruct oStruct = new OverrideStruct();
                    oStruct.Flag = FlagType.Single;
                    oStruct.Id = omid;
                    _overrides.Add(mid, oStruct);
                }
                else
                {
                    if (_overrides[mid].Flag == FlagType.Single)
                    {
                        uint id = _overrides[mid].Id;
                        _overrides[mid].List.AddLast(id);
                        _overrides[mid].Flag = FlagType.Multi;
                    }
                }
            }
            else
            {
                throw new LimException("", "Invalid NodeKind (" + mnode.NodeKind + " " + onode.NodeKind + ")");
            }
        }

        public void AddOverride(Nodes.Logical.Method m, Nodes.Logical.Method mo)
        {
            AddOverride(m.Id, mo.Id);
        }

        public bool GetIsOverride(uint id)
        {
            return _overrides.ContainsKey(id);
        }

        public uint GetOverride(uint id)
        {
            if (!_overrides.ContainsKey(id))
            {
                return 0;
            }
            if (_overrides[id].Flag == FlagType.Single)
            {
                return _overrides[id].Id;
            }
            else
            {
                return _overrides[id].List.First.Value;
            }
        }

        public LinkedList<uint> getOverrideList(uint id)
        {
            if (!_overrides.ContainsKey(id))
            {
                return new LinkedList<uint>();
            }
            if (_overrides[id].Flag == FlagType.Single)
            {
                LinkedList<uint> l = new LinkedList<uint>();
                l.AddLast(_overrides[id].Id);
                return l;
            }
            return _overrides[id].List;
        }

        public int getNumberOfOverrides(uint id)
        {
            if (!_overrides.ContainsKey(id))
            {
                return 0;
            }
            if (_overrides[id].Flag == FlagType.Single)
            {
                return 1;
            }
            return _overrides[id].List.Count;
        }

        public override string ToString()
        {
            return "";
        }
    }
}
