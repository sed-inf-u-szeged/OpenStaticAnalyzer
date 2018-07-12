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

package columbus;

import java.util.Iterator;
import java.util.Map;
import java.util.SortedMap;
import java.util.TreeMap;

/**
 * StrTable class is responsible for storing/loading/saving strings.
 */
public class StrTable {

	public static enum StrType {
		strDefault, strTmp, strToSave
	}

	public StrTable() {
		this(511);
	}

	@SuppressWarnings("unchecked")
	public StrTable(int buckets) {
		noBuckets = buckets;
		strTable = new TreeMap[noBuckets];
		count = new int[noBuckets];

		for (int i = 0; i < noBuckets; i++) {
			strTable[i] = new TreeMap<Integer, Pair>();
			count[i] = 1;
		}
	}

	private int hash(String string) {
		int hashHi = 0;
		int hashLow = 0;

		if (string == null)
			return 0;

		if (string.length() == 0)
			return 0;

		char[] convertedString = string.toCharArray();

		for (int i = 0; i < convertedString.length; i++) {
			convertedString[i] &= 0xFF;
			hashHi = randomNumbers[hashHi ^ convertedString[i]];
		}
		convertedString[0]++;
		convertedString[0] &= 0xFF;

		for (int i = 0; i < convertedString.length; i++)
			hashLow = randomNumbers[hashLow ^ convertedString[i]];

		return (hashHi << 8) | hashLow;
	}

	private int get(String s, int hashValue, int bucketIndex) {
		SortedMap<Integer, Pair> bucket = strTable[bucketIndex];
		SortedMap<Integer, Pair> sm = bucket.subMap(hashValue << 16, (hashValue << 16) + 0xFFFF);

		for (Iterator<Map.Entry<Integer, Pair>> it = sm.entrySet().iterator(); it.hasNext();) {
			Map.Entry<Integer, Pair> entry = it.next();
			if (entry.getValue().string.equals(s))
				return entry.getKey();
		}

		Pair entry = bucket.get((hashValue + 1) << 16);
		if (entry != null && entry.string.equals(s))
			return ((hashValue + 1) << 16);

		return 0;
	}

	public int get(String s) {
		if (s == null)
			return 0;

		if (s.length() == 0)
			return 0;

		int hashValue = hash(s);
		int bucketIndex = hashValue % noBuckets;

		return get(s, hashValue, bucketIndex);
	}

	public String get(int key) {

		if (key == 0)
			return "";

		int bucketIndex = (key >>> 16) % noBuckets;
		Pair value = strTable[bucketIndex].get(key);
		if (value != null)
			return value.string;

		return "";
	}

	public int set(String s) throws ColumbusException {

		if (s == null)
			return 0;

		if (s.length() == 0)
			return 0;

		int key = 0;
		int hashValue = hash(s);
		int bucketIndex = hashValue % noBuckets;

		if ((key = get(s, hashValue, bucketIndex)) == 0) {
			key = (hashValue << 16) | count[bucketIndex]++;

			if (count[bucketIndex] == 0xFFFF) {
				throw new ColumbusException(WarningMessages.BUCKET_FULL);
			}

			strTable[bucketIndex].put(key, new Pair(s, StrType.strDefault));
		}

		return key;
	}

	public void setType(String s, StrType type) throws ColumbusException {

		if (s == null)
			return;

		if (s.length() == 0)
			return;

		int key = 0;
		int hashValue = hash(s);
		int bucketIndex = hashValue % noBuckets;

		if ((key = get(s, hashValue, bucketIndex)) == 0) {
			key = (hashValue << 16) | count[bucketIndex]++;

			if (count[bucketIndex] == 0xFFFF) {
				throw new ColumbusException(WarningMessages.BUCKET_FULL);
			}

			strTable[bucketIndex].put(key, new Pair(s, StrType.strDefault));
		} else
			strTable[bucketIndex].get(key).type = type;
	}

	public void setType(int key, StrType type) {

		int bucket_index = (key >>> 16) % noBuckets;

		Pair value = strTable[bucket_index].get(key);
		if (value != null)
			value.type = type;
	}

	public void save(IO io, StrType filterType) throws ColumbusException {
		io.writeString("STRTBL");
		io.writeInt4(noBuckets);

		for (int i = 0; i < noBuckets; i++)
			io.writeUShort2(count[i]);

		// write out each element
		for (int i = 0; i < noBuckets; i++) {
			save(io, filterType, i, false);
			save(io, filterType, i, true);
		}

		// Write out the end of StringTable sign
		io.writeInt4(0);
	}

	private void save(IO io, StrType filterType, int bucketIndex, boolean negative) throws ColumbusException {
		for (Map.Entry<Integer, Pair> entry : strTable[bucketIndex].entrySet()) {
			if (negative && entry.getKey() >= 0)
				continue;
			else if (!negative && entry.getKey() < 0)
				continue;

			if (filterType == StrType.strTmp) { // In tmp mode nodes with tmp flag will be skipped.
				if (entry.getValue().type == StrType.strTmp)
					continue;
			} else if (filterType == StrType.strToSave) { // In save mode only nodes with save flag will be written out.
				if (entry.getValue().type != StrType.strToSave)
					continue;
			}

			io.writeInt4(entry.getKey()); // The key (4)
			io.writeLongString(entry.getValue().string); // Size and characters of the string (4 + n)
		}
	}

	@SuppressWarnings("unchecked")
	public void load(IO io) throws ColumbusException {
		String id = io.readString(6);
		if (!"STRTBL".equals(id)) {
			throw new ColumbusException(WarningMessages.WRONG_FILE_FORMAT);
		}

		noBuckets = io.readInt4();
		strTable = new TreeMap[noBuckets];
		count = new int[noBuckets];

		for (int i = 0; i < noBuckets; i++) {
			strTable[i] = new TreeMap<Integer, Pair>();
			count[i] = io.readUShort2();
		}

		int key;
		String str;
		int bucketIndex;

		while ((key = io.readInt4()) != 0) {
			str = io.readLongString();
			bucketIndex = (key >>> 16) % noBuckets;
			strTable[bucketIndex].put(key, new Pair(str, StrType.strDefault));
		}
	}

	protected static class Pair {
		String string;
		StrType type;

		public Pair(String s, StrType st) {
			string = s;
			type = st;
		}
	}

	protected static final int randomNumbers[] = { 1, 14, 110, 25, 97, 174, 132, 119, 138, 170, 125, 118, 27, 233, 140, 51,
			87, 197, 177, 107, 234, 169, 56, 68, 30, 7, 173, 73, 188, 40, 36, 65, 49, 213, 104, 190, 57, 211, 148, 223,
			48, 115, 15, 2, 67, 186, 210, 28, 12, 181, 103, 70, 22, 58, 75, 78, 183, 167, 238, 157, 124, 147, 172, 144,
			176, 161, 141, 86, 60, 66, 128, 83, 156, 241, 79, 46, 168, 198, 41, 254, 178, 85, 253, 237, 250, 154, 133,
			88, 35, 206, 95, 116, 252, 192, 54, 221, 102, 218, 255, 240, 82, 106, 158, 201, 61, 3, 89, 9, 42, 155, 159,
			93, 166, 80, 50, 34, 175, 195, 100, 99, 26, 150, 16, 145, 4, 33, 8, 189, 121, 64, 77, 72, 208, 245, 130,
			122, 143, 55, 105, 134, 29, 164, 185, 194, 193, 239, 101, 242, 5, 171, 126, 11, 74, 59, 137, 228, 108, 191,
			232, 139, 6, 24, 81, 20, 127, 17, 91, 92, 251, 151, 225, 207, 21, 98, 113, 112, 84, 226, 18, 214, 199, 187,
			13, 32, 94, 220, 224, 212, 247, 204, 196, 43, 249, 236, 45, 244, 111, 182, 153, 136, 129, 90, 217, 202, 19,
			165, 231, 71, 230, 142, 96, 227, 62, 179, 246, 114, 162, 53, 160, 215, 205, 180, 47, 109, 44, 38, 31, 149,
			135, 0, 216, 52, 63, 23, 37, 69, 39, 117, 146, 184, 163, 200, 222, 235, 248, 243, 219, 10, 152, 131, 123,
			229, 203, 76, 120, 209 };

	protected int noBuckets;
	protected int count[];
	protected TreeMap<Integer, Pair> strTable[];
}
