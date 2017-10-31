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

package org.jan;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.StringTokenizer;

import columbus.logger.LoggerHandler;

public class ConfigReader {

	private static final LoggerHandler logger = new LoggerHandler(ConfigReader.class, OptionParser.getLoggerPropertyFile());

	public static String getValue(String fileName, String section, String option) {
		String ret = null;
		try {
			List<String> list = getValues(fileName, section, option);
			if (list == null || list.size() == 0) {
				// error - return null
			} else if (list.size() == 1) {
				ret = list.get(0);
			} else {
				logger.warn("warn.jan.ConfigReader.optionHasMultipleValue", option, section);
			}
		} catch (Exception e) {
			logger.error("error.jan.ConfigReader.configReaderEx", e);
		}

		return ret;
	}

	public static List<String> getValues(String fileName, String section, String option) {
		List<String> values = null;
		try {
			values = new ArrayList<>();
			Map<String, String> sectionMap = readSection(fileName, section);
			String valueString = sectionMap.get(option);
			if (valueString == null) {
				throw new Exception(logger.formatMessage("ex.jan.ConfigReader.cantFindOption", option, fileName, section));
			}

			StringTokenizer st = new StringTokenizer(valueString, " ");
			while (st.hasMoreTokens()) {
				String token = st.nextToken();
				boolean quation = false;
				if (token.startsWith("\"")) {
					quation = true;
					while (!token.endsWith("\"")) {
						String next = st.nextToken();
						token += " " + next;
					}
				}
				if (quation) {
					token = token.substring(1, token.length() - 1);
				}
				values.add(token);
			}

			if (values.size() == 0) {
				logger.debug("debug.jan.ConfigReader.optionDontHaveValue", option, section);
			}

		} catch (FileNotFoundException e) {
			logger.error("error.jan.ConfigReader.configReaderEx", e);
		} catch (IOException e) {
			logger.error("error.jan.ConfigReader.configReaderEx", e);
		} catch (Exception e) {
			logger.error("error.jan.ConfigReader.configReaderEx", e);
		}

		return values;
	}

	public static Map<String, String> readSection(String fileName, String section) throws Exception {
		String line;
		boolean foundSection = false;
		boolean needToRead = false;
		Map<String, String> ret = new HashMap<>();
		BufferedReader br = null;
		try {
			br = new BufferedReader(new FileReader(new File(fileName)));
			while ((line = br.readLine()) != null) {
				line = line.trim();
				if (needToRead) {
					if (line.startsWith("[") && line.endsWith("]")) {
						needToRead = false;
						break;
					}
					if (line.isEmpty() || line.startsWith(";")) {
						continue;
					}
					int firstEquPos = line.indexOf("=");
					ret.put(line.substring(0, firstEquPos), line.substring(++firstEquPos, line.length()));
				}

				if (line.equals("[" + section + "]")) {
					foundSection = true;
					needToRead = true;
				}
			}
			if (!foundSection) {
				throw new Exception(logger.formatMessage("ex.jan.ConfigReader.cantFindSection", section));
			}
		} catch (Exception e){
			logger.error("error.jan.ConfigReader.readingEx", e);
			
		} finally {
			br.close();
		}
		return ret;
	}
}
