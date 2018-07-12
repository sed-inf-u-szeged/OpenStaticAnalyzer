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

package org.jcolumbus.antwrapper;

import java.util.List;

public class Options {
	public static final String messagesFile = "AntWrapperMessages";
	public static final String logbackConfigFile = "logback.xml";

	public static String configFile = EnvironmentVariables.WRAPPER_BIN_DIR + "/" + "toolchain.ini";

	public static final String columbusResultDir = ConfigReader.getValue(configFile, "JAN", "columbusResultDir");
	public static final List<String> JAN_OPTIONS = ConfigReader.getValues(configFile, "JAN_CALL", "JAN_OPTIONS");
	public static final String CALL_PMD = ConfigReader.getValue(configFile, "OTHER_TOOLS", "CALL_PMD");
	public static final String RECOMPILE_ALL = ConfigReader.getValue(configFile, "ANT_WRAPPER", "RECOMPILE_ALL");
	public static final List<String> JAN_JVM_OPTS = ConfigReader.getValues(configFile, "JAN_CALL", "JAN_JVM_OPTS");
	public static final String JWRAPPER_LOG = ConfigReader.getValue(configFile, "ENVIRONMENT", "JWRAPPER_LOG");
	public static final String janStat = ConfigReader.getValue(configFile, "STATISTICS", "janStatisticFile");
	public static final String pmdStat = ConfigReader.getValue(configFile, "STATISTICS", "pmdStatisticFile");
}
