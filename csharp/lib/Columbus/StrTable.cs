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
using System.Text;
using System.IO;

namespace Columbus {

    /// <summary>
    /// Contains string values and generates unique keys for them.
    /// </summary>
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class StrTable {

        /// <summary>The number of buckets.</summary>
        protected uint numberOfBuckets;

        /// <summary>Internal counter for each bucket.</summary>
        protected ushort[] count;

        /// <summary>The string table.</summary>
        protected Dictionary<uint, KeyValuePair<string, StrType>>[] strTable;

#if (DOSTAT)
        /// <summary>
        /// Struct for calculating table statistics.
        /// </summary>
        protected struct TableStat {
            /// <summary>The elements in the statistics table.</summary>
            public uint ElementCount;

            /// <summary>The number of searches for the current element.</summary>
            public uint NumberOfSearch;

            /// <summary>The number of iterations for the current element.</summary>
            public ulong NumberOfIt;
        }
        
        /// <summary>Stores the table statistics.</summary>
        protected TableStat[] statisticCounter;
#endif

        /// <summary>
        /// Types of the strings in the table.
        /// </summary>
        public enum StrType {
            /// <summary>Default string.</summary>
            strDefault,

            /// <summary>Temporary string.</summary>
            strTmp,

            /// <summary>The string must be saved.</summary>
            strToSave
        }

        /// <summary>
        /// Default constructor for the StrTable.
        /// </summary>
        public StrTable() : this(511) {
        }

        /// <summary>
        /// Constructor for the StrTable.
        /// </summary>
        /// <param name="buckets">[in] The number of buckets.</param>
        public StrTable(uint buckets) {
            numberOfBuckets = buckets;

            count = new ushort[numberOfBuckets];
            strTable = new Dictionary<uint, KeyValuePair<string, StrType>>[numberOfBuckets];

            for (int i = 0; i < numberOfBuckets; ++i) {
                count[i] = 1;
                strTable[i] = new Dictionary<uint, KeyValuePair<string, StrType>>();
            }
            
#if (DOSTAT)
            statisticCounter = new TableStat[numberOfBuckets];
#endif
        }

        /// <summary>
        /// Copies a StringTable
        /// </summary>
        /// <param name="rhs">[in] The StrTable to copy.</param>
        public void copyFrom(StrTable rhs) {
            numberOfBuckets = rhs.numberOfBuckets;

#if (DOSTAT)
            statisticCounter = new TableStat[numberOfBuckets];
#endif

            count = new ushort[numberOfBuckets];
            strTable = new Dictionary<uint, KeyValuePair<string, StrType>>[numberOfBuckets];

            for (int i = 0; i < numberOfBuckets; ++i) {
                count[i] = rhs.count[i];
                strTable[i] = new Dictionary<uint, KeyValuePair<string, StrType>>();

                foreach (KeyValuePair<uint, KeyValuePair<string, StrType>> entry in rhs.strTable[i])
                    strTable[i].Add(entry.Key, new KeyValuePair<string, StrType>(entry.Value.Key, entry.Value.Value));
            }
        }

        /// <summary>
        /// Gives back the number of buckets.
        /// </summary>
        /// <returns>The number of buckets.</returns>
        public uint NumberOfBuckets {
            get {
                return numberOfBuckets;
            }
        }

        /// <summary>
        /// Inserts the given string into the string table and gives back a "unique" key.
        /// </summary>
        /// <param name="str">[in] The string to insert.</param>
        /// <returns>The given strings "unique" key.</returns>
        public uint set(string str) {
            return set(str, StrType.strDefault);
        }

        /// <summary>
        /// Inserts the given string into the string table and gives back a "unique" key.
        /// </summary>
        /// <param name="str">[in] The string to insert.</param>
        /// <param name="type">[in] The type of the string.</param>
        /// <returns>The given strings "unique" key.</returns>
        public uint set(string str, StrType type) {
            if (str == null || str.Length == 0)
                return 0;

            uint key;

            ushort hashValue = hash(str);
            uint bucketIndex = hashValue % numberOfBuckets;

            if ((key = get(str, hashValue, bucketIndex)) == 0) {
                key = (((uint)hashValue) << 16) | count[bucketIndex]++;

                if (count[bucketIndex] == 0xFFFF)
                    WriteMsg.WriteLine("StrTable: Bucket ({0}) is full!", WriteMsg.MsgLevel.Error, bucketIndex);

                strTable[bucketIndex].Add(key, new KeyValuePair<string, StrType>(str, type));

#if (DOSTAT)
                statisticCounter[bucketIndex].ElementCount++;
#endif
            }

            return key;
        }

        /// <summary>
        /// Sets the type of the given string. If the given string does not exist in the table than it inserts it with a given type.
        /// </summary>
        /// <param name="str">[in] The string.</param>
        /// <param name="type">[in] The type of the string.</param>
        public void setType(string str, StrType type) {
            if (str == null || str.Length == 0)
                return;

            uint key;

            ushort hashValue = hash(str);
            uint bucketIndex = hashValue % numberOfBuckets;

            if ((key = get(str, hashValue, bucketIndex)) == 0) {
                key = (((uint)hashValue) << 16) | count[bucketIndex]++;

                if (count[bucketIndex] == 0xFFFF)
                    WriteMsg.WriteLine("StrTable: Bucket ({0}) is full!", WriteMsg.MsgLevel.Error, bucketIndex);
                if (!strTable[bucketIndex].ContainsKey(key))
                    strTable[bucketIndex].Add(key, new KeyValuePair<string, StrType>(str, type));

#if (DOSTAT)
                statisticCounter[bucketIndex].ElementCount++;
#endif
            } else {
                strTable[bucketIndex][key] = new KeyValuePair<string, StrType>(strTable[bucketIndex][key].Key, type);
            }
        }

        /// <summary>
        /// Sets the type of the string stored in the string table with the given "unique" key.
        /// </summary>
        /// <param name="key">[in] The unique key.</param>
        /// <param name="type">[in] The type of the string.</param>
        public void setType(uint key, StrType type) {
            uint bucketIndex = (key >> 16) % numberOfBuckets;

            if (strTable[bucketIndex].ContainsKey(key))
                strTable[bucketIndex][key] = new KeyValuePair<string, StrType>(strTable[bucketIndex][key].Key, type);
        }

        /// <summary>
        /// Gives back the strings "unique" key.
        /// </summary>
        /// <param name="str">[in] The string.</param>
        /// <returns>The given strings "unique" key.</returns>
        public uint get(string str) {
            if (str == null || str.Length == 0)
                return 0;

            ushort hashValue = hash(str);
            uint bucketIndex = hashValue % numberOfBuckets;

            return get(str, hashValue, bucketIndex);
        }

        /// <summary>
        /// Gives back the "unique" key of the given string if it is in the string table. Otherwise it returns 0.
        /// </summary>
        /// <param name="key">[in] The unique key.</param>
        /// <returns>The string that belongs to the "unique" key.</returns>
        public string get(uint key) {
            uint bucketIndex = (key >> 16) % numberOfBuckets;

            KeyValuePair<string, StrType> kv;
            if (strTable[bucketIndex].TryGetValue(key, out kv))
                return kv.Key;

            return "";
        }

        /// <summary>
        /// Saves the string table to the given file.
        /// </summary>
        /// <param name="io">[in] The file writer.</param>
        public void save(IO io) {
            save(io, StrType.strDefault);
        }

        /// <summary>
        /// Saves the string table to the given file.
        /// </summary>
        /// <param name="io">[in] The file writer.</param>
        /// <param name="filterType">[in] Type of the strings to save.</param>
        public void save(IO io, StrType filterType) {
            try {
                io.writeData("STRTBL", 6);
                io.writeUInt4(numberOfBuckets);

                for (int i = 0; i < numberOfBuckets; ++i)
                    io.writeUShort2(count[i]);

                for (int j = 0; j < numberOfBuckets; ++j) {
                    Dictionary<uint, KeyValuePair<string, StrType>> currentMap = strTable[j];

                    foreach (KeyValuePair<uint, KeyValuePair<string, StrType>> entry in currentMap) {
                        if (filterType == StrType.strTmp) {
                            if (entry.Value.Value == StrType.strTmp)
                                continue;
                        } else {
                            if (filterType == StrType.strToSave)
                                if (entry.Value.Value != StrType.strToSave)
                                    continue;
                        }

                        io.writeUInt4(entry.Key);
                        io.writeUInt4((uint)entry.Value.Key.Length);
                        io.writeData(entry.Value.Key, entry.Value.Key.Length);
                    }
                }

                io.writeUInt4(0);
            } catch {
                WriteMsg.WriteLine("StrTable.save(): Error while writing!", WriteMsg.MsgLevel.Error);
            }
        }

        /// <summary>
        /// Loads the string table from the given file.
        /// </summary>
        /// <param name="io">[in] The file reader.</param>
        public void load(IO io) {
            try {
                string idBytes;
                io.readData(out idBytes, 6);
                if (idBytes != "STRTBL") {
                    WriteMsg.WriteLine("StrTable.load(): Wrong file format!", WriteMsg.MsgLevel.Error);
                    return;
                }

                numberOfBuckets = io.readUInt4();

                strTable = new Dictionary<uint, KeyValuePair<string, StrType>>[numberOfBuckets];
                count = new ushort[numberOfBuckets];
                
#if (DOSTAT)
                statisticCounter = new TableStat[numberOfBuckets];
#endif

                for (int i = 0; i < numberOfBuckets; ++i) {
                    count[i] = io.readUShort2();
                    strTable[i] = new Dictionary<uint, KeyValuePair<string, StrType>>();
                }

                while (true) {
                    uint key = io.readUInt4();
                    if (key == 0) break;
                    int str_size = (int)io.readUInt4();
                    string buffer;
					io.readData(out buffer, str_size);

					int bucket = (int)((key >> 16) % numberOfBuckets);
                    strTable[bucket].Add(key, new KeyValuePair<string, StrType>(buffer, StrType.strDefault));
                }
            } catch {
                WriteMsg.WriteLine("StrTable.load(): Error while reading!", WriteMsg.MsgLevel.Error);
            }
        }

        /// <summary>
        /// Returns true if the given key is valid or false if it is invalid.
        /// </summary>
        /// <param name="key">[in] The unique key.</param>
        /// <returns>The given key is valid or not.</returns>
        public static bool getIsValid(uint key) {
            return (key != 0);
        }

        /// <summary>
        /// Prints out the content of the table.
        /// </summary>
        public void dump() {
            uint i = 0;
            uint totalCounter = 0;

            for (int j = 0; j < numberOfBuckets; ++j) {
                ++i;
                WriteMsg.WriteLine("Bucket: {0} (total number: {1})", WriteMsg.MsgLevel.Debug, i, strTable[j].Count);

                foreach (KeyValuePair<uint, KeyValuePair<string, StrType>> entry in strTable[j])
                    WriteMsg.WriteLine("[{0}]:[{1}][{1}]", WriteMsg.MsgLevel.Debug, entry.Key, entry.Value.Key, entry.Value.Value);

                ++totalCounter;
            }

            WriteMsg.WriteLine("Total Count: {0}", WriteMsg.MsgLevel.Debug, totalCounter);
        }

        /// <summary>
        /// Creates a unique key for the string.
        /// </summary>
        /// <param name="str">[in] The string.</param>
        /// <returns>A "unique" key for the given string.</returns>
        protected ushort hash(string str) {
            if (str == null || str.Length == 0)
                return 0;

            byte[] v = System.Text.Encoding.UTF8.GetBytes(str);
            uint hashHigh = 0;
            uint hashLow = 0;
            int i = 0;

            while (i < str.Length)
                hashHigh = randomNumbers[hashHigh ^ v[i++]];

            hashLow = randomNumbers[hashLow ^ ((v[0] + 1) & 0xFF)];

            for (i = 1; i < str.Length; )
                hashLow = randomNumbers[hashLow ^ v[i++]];

            return (ushort)((hashHigh << 8) | hashLow);
        }

        /// <summary>
        /// Returns the unique key of a string stored in the table.
        /// </summary>
        /// <param name="str">[in] The string.</param>
        /// <param name="hashValue">[in] The hash value of the string.</param>
        /// <param name="bucketIndex">[in] The bucket index of the string.</param>
        /// <returns>The given strings "unique" key.</returns>
        protected uint get(string str, ushort hashValue, uint bucketIndex) {
#if (DOSTAT)
            statisticCounter[bucketIndex].NumberOfSearch++;
#endif

            uint lowerBound = ((uint)hashValue) << 16;
            uint upperBound = lowerBound + 0xFFFF;

            for (uint i = lowerBound; i < upperBound; i++) {
#if (DOSTAT)
                statisticCounter[bucketIndex].NumberOfIt++;
#endif
                KeyValuePair<string, StrType> kv;
                if (strTable[bucketIndex].TryGetValue(i, out kv))
                {
                    if (kv.Key == str)
                        return i;
                }
            }

            return 0;
        }

        /// <summary>
        /// Random numbers for the hash generator.
        /// </summary>
        public static byte[] randomNumbers =
        {
             1, 14,110, 25, 97,174,132,119,138,170,125,118, 27,233,140, 51,
            87,197,177,107,234,169, 56, 68, 30,  7,173, 73,188, 40, 36, 65,
            49,213,104,190, 57,211,148,223, 48,115, 15,  2, 67,186,210, 28,
            12,181,103, 70, 22, 58, 75, 78,183,167,238,157,124,147,172,144,
           176,161,141, 86, 60, 66,128, 83,156,241, 79, 46,168,198, 41,254,
           178, 85,253,237,250,154,133, 88, 35,206, 95,116,252,192, 54,221,
           102,218,255,240, 82,106,158,201, 61,  3, 89,  9, 42,155,159, 93,
           166, 80, 50, 34,175,195,100, 99, 26,150, 16,145,  4, 33,  8,189,
           121, 64, 77, 72,208,245,130,122,143, 55,105,134, 29,164,185,194,
           193,239,101,242,  5,171,126, 11, 74, 59,137,228,108,191,232,139,
             6, 24, 81, 20,127, 17, 91, 92,251,151,225,207, 21, 98,113,112,
            84,226, 18,214,199,187, 13, 32, 94,220,224,212,247,204,196, 43,
           249,236, 45,244,111,182,153,136,129, 90,217,202, 19,165,231, 71,
           230,142, 96,227, 62,179,246,114,162, 53,160,215,205,180, 47,109,
            44, 38, 31,149,135,  0,216, 52, 63, 23, 37, 69, 39,117,146,184,
           163,200,222,235,248,243,219, 10,152,131,123,229,203, 76,120,209
        };

    }

}
