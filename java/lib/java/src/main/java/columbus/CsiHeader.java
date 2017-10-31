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

package columbus;

import java.util.TreeMap;
import java.util.Map.Entry;
import columbus.logger.LoggerHandler;

/**
 * CsiHeader class is responsible for storing/loading/saving the columbus schema instance headers.
 */
public class CsiHeader {

	private static final LoggerHandler logger = new LoggerHandler(CsiHeader.class, "ColumbusMessages");
	public static final String csih_True = "1";
	public static final String csih_False = "0";

	public static final String csih_Type = "Type";
	public static final String csih_BinaryVersion = "BinaryVersion";
	public static final String csih_APIVersion = "APIVersion";
	public static final String csih_FullAnalysis = "FullAnalysis";
	public static final String csih_SchemaFilter = "SchemaFilter";
	public static final String csih_PrecompiledHeader = "PrecompiledHeader";
	public static final String csih_UsePrecompiledHeader = "UsePrecompileHeader";
	public static final String csih_NumOfIncrLinked = "NumberOfIncrLinked";
	public static final String csih_PreanalyzedIncludesUsed = "PreanalyzedIncludesUsed";
	public static final String csih_OriginalLocation = "OriginalLocation";
	public static final String csih_PsiKind = "PsiKind";
	public static final String csih_Language = "Language";
	public static final String csih_ChangesetID = "ChangesetID";

	protected TreeMap<String, String> header = new TreeMap<String, String>();

	public CsiHeader() {
	}

	public boolean add(String key, String value) {
		if (header.containsKey(key))
			return false;
		header.put(key, value);
		return true;
	}

	public boolean addBoolean(String key, boolean value) {
		return add(key, value ? csih_True : csih_False);
	}

	public boolean addInt(String key, int value) {
		return add(key, Integer.toString(value));
	}

	public String get(String key) {
		return header.get(key);
	}

	public Boolean getBoolean(String key) {
		String value = header.get(key);
		if (value == null)
			return null;
		return value.equals(csih_True) ? true : false;
	}

	public Integer getInt(String key) {
		String value = header.get(key);
		if (value == null)
			return null;
		return Integer.parseInt(value);
	}

	public void write(IO io) {
		io.writeInt4(header.size());
		for (Entry<String, String> entry : header.entrySet()) {
			io.writeShortString(entry.getKey());
			io.writeShortString(entry.getValue());
		}
	}

	public void read(IO io) {
		int num = io.readInt4();
		for (int i = 0; i < num; i++) {
			String key = io.readShortString();
			String value = io.readShortString();
			add(key, value);
		}
	}

	public void dump() {
		for (Entry<String, String> entry : header.entrySet()) {
			logger.info("info.java.CSI.dump", entry.getKey(), entry.getValue());
		}
	}
}
