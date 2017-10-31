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
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.StringTokenizer;

import columbus.logger.LoggerHandler;

import com.sun.tools.javac.main.Option;

public class OptionParser {

	private static final String loggerPropertyFile = "JanMessages";
	private static final String logbackXmlFile = "logback.xml";

	private static final LoggerHandler logger = new LoggerHandler(OptionParser.class, loggerPropertyFile);

	private static final String delim = "|";
	private static final String equal = "=";
	private static boolean buildAllExternal = false;
	private static boolean buildExtFromSource = true;
	// build super classes and interfaces for method override edges
	public static boolean buildAllParentForOverrides = true;

	private static boolean keepComments = true;

	private static List<String> inputs = new ArrayList<>();

	private static String outputDir = null;

	private static String columbusResultDir = null;

	private static String extraJsiDir = null;

	private static boolean xmlToEveryClass = false;

	private static String commonJsi = null;

	private static String commonXml = null;

	private static String generatedJsiListFile = null;

	private static String analyzedSourceList = null;

	private static boolean needCheck = true;

	private static List<String> javacOptions = new ArrayList<>();

	private static String configFile;

	private static String statisticFile = null;

	public static String encoding;

	public static boolean wrappedMode = false;

	public static boolean dirAnalyze = false;

	public static String hardFilter = null;

	private static String usedClasspathList = null;

	private static int messageLevel;

	private static String componentId;

	private static String changesetID;

	public static String getLoggerPropertyFile() {
		return loggerPropertyFile;
	}

	public static String getLogbackXml() {
		return logbackXmlFile;
	}

	public static String getConfigFile() {
		return configFile;
	}

	public static String getStatisticFile() {
		return statisticFile;
	}

	public static void setConfigFileDir(String configFile) {
		OptionParser.configFile = configFile;
	}

	public static boolean isBuildAllExternal() {
		return buildAllExternal;
	}

	public static boolean isBuildExtFromSource() {
		return buildExtFromSource;
	}

	public static boolean isKeepComments() {
		return keepComments;
	}

	public static List<String> getInputs() {
		return inputs;
	}

	public static String getOutputDir() {
		return outputDir;
	}

	public static String getColumbusResultDir() {
		return columbusResultDir;
	}

	public static String getExtraJsiDir() {
		return extraJsiDir;
	}

	public static boolean isXmlToEveryClass() {
		return xmlToEveryClass;
	}

	public static String getCommonJsi() {
		return commonJsi;
	}

	public static String getCommonXml() {
		return commonXml;
	}

	public static String getGeneratedJsiListFile() {
		return generatedJsiListFile;
	}

	public static String getAnalyzedSourceList() {
		return analyzedSourceList;
	}

	public static boolean isNeedCheck() {
		return needCheck;
	}

	public static List<String> getJavacOptions() {
		return javacOptions;
	}

	public static String getComponentId() {
		return componentId;
	}

	public static String getChangesetID() {
		return changesetID;
	}

	private static void parseJavacOptions(String str) {
		String[] array = str.split("[|]");
		List<String> list = new ArrayList<>();
		for (String s : array) {
			if (!s.equals("")) {
				list.add(s);
			}
		}
		javacOptions.addAll(list);
	}

	public static void processCmdLine(JANCmdLine cmd) {
		String config = null;
		if (cmd.isConfigfile()) {
			String configFileFromCmd = cmd.getConfigfile();
			// search as an absolute path
			if ((new File(configFileFromCmd).exists())) {
				config = configFileFromCmd;
			} else { // search near the JAN.jar with the given name
				config = OptionParser.configFile.replace("\\", "/") + "/" + configFileFromCmd;
			}
		} else { // search near the JAN.jar with a default name
			config = OptionParser.configFile.replace("\\", "/") + "/" + "toolchain.ini";
		}

		try {
			if (new File(config).exists()) {
				parseOptionsFromConfig(config);
			} else {
				config = null;
				logger.warn("warn.jan.OptionParser.noConfigFile");
			}
		} catch (Exception e) {
			logger.error("error.jan.OptionParser.configParseError", e);
		}

		
		if (cmd.isMessagelevel()) {
			messageLevel = cmd.getMessagelevel();
		}
		if (messageLevel < 0 || messageLevel > 6) {
			logger.warn("warn.jan.OptionParser.badLogLevel", messageLevel);
			messageLevel = 3;
		}

		logger.info("info.jan.OptionParser.setLogLevel", messageLevel);
		LoggerHandler.setMessageLevel(messageLevel);

		if (cmd.isJanoptions()) {
			parseOptionsFromCmd(cmd.getJanoptions());
		}

		if (cmd.isConfigfile() && cmd.isJanoptions()) {
			logger.warn("warn.jan.OptionParser.overrideValuesFromConfigFile");
		}

		if (cmd.isInput()) {
			inputs = cmd.getInput();
		}

		if (cmd.isOutputdir()) {
			outputDir = cmd.getOutputdir();
		}

		if (cmd.isJavacargumentfiles()) {
			for (String s : cmd.getJavacargumentfiles()) {
				if (!s.isEmpty()) {
					if (s.charAt(0) == '@')
						s = s.substring(1);
					try (BufferedReader br = new BufferedReader(new FileReader(new File(s)))) {
						processArgFile(br);
					} catch (Exception e) {
						logger.error("error.jan.OptionParser.cantOpenArgFile", s, e);
					}
				}
			}
		}
		if (cmd.isExtrajsidir()) {
			extraJsiDir = cmd.getExtrajsidir();
		}
		if (cmd.isOutputjsi()) {
			commonJsi = cmd.getOutputjsi();
		}
		if (cmd.isOutputxml()) {
			commonXml = cmd.getOutputxml();
		}
		if (cmd.isJsilistfile()) {
			generatedJsiListFile = cmd.getJsilistfile();
		}
		if (cmd.isAnalyzedsourcelist()) {
			analyzedSourceList = cmd.getAnalyzedsourcelist();
		}

		if (cmd.isUsedclasspathlist()) {
			usedClasspathList = cmd.getUsedclasspathlist();
		}

		if (cmd.isJavacoptions()) {
			parseJavacOptions(cmd.getJavacoptions());
		}

		wrappedMode = cmd.isWrappedmode();

		dirAnalyze = cmd.isDirecotryAnalyzeMode();

		if (cmd.isHardfilter()) {
			hardFilter = cmd.getHardfilter();
		}

		if (cmd.isJavacargumentfiles() && cmd.isJavacoptions()) {
			logger.warn("warn.jan.OptionParser.overrideValuesFromArgFile");
		}

		if (cmd.isStatisticfile()) {
			statisticFile = cmd.getStatisticfile();
		}

		if (cmd.isJavacoptions() && cmd.isJavacargumentfiles()) {
			logger.warn("warn.jan.OptionParser.overrideValuesFromTheListFile");
		}

		postProcessJavacOptions(config);

	}

	private static void postProcessJavacOptions(String config) {
		if (config != null && !config.isEmpty()) {
			List<String> forcedSingleOpts = ConfigReader.getValues(config, "JAVAC", "FORCE_SINGLE_OPT");
			List<String> forcedMultiOpts = ConfigReader.getValues(config, "JAVAC", "FORCE_MULTI_OPT");
			addForcedJavacOptions(forcedSingleOpts, forcedMultiOpts, true);
			List<String> defaultSingleOpts = ConfigReader.getValues(config, "JAVAC", "DEFAULT_SINGLE_OPT");
			List<String> defaultMultiOpts = ConfigReader.getValues(config, "JAVAC", "DEFAULT_MULTI_OPT");
			addForcedJavacOptions(defaultSingleOpts, defaultMultiOpts, false);
		}

		for (int i = 0; i < javacOptions.size(); ++i) {
			if (javacOptions.get(i).equals(Option.ENCODING.getText()) && i + 1 < javacOptions.size()) {
				OptionParser.encoding = javacOptions.get(i + 1);
				logger.info("info.jan.OptionParser.javacOptionFound", Option.ENCODING.getText(),
						OptionParser.encoding);
			}
		}

		checkJavacOptions();
	}

	private static void addForcedJavacOptions(List<String> singleOpts, List<String> multiOpts, boolean force) {

		for (int i = 0; i < javacOptions.size(); i++) {
			String act = javacOptions.get(i);
			if (multiOpts.contains(act) && act.startsWith("-")) {
				int pos = multiOpts.indexOf(act);
				multiOpts.remove(pos);
				if (force) {
					javacOptions.set(i + 1, multiOpts.get(pos));
				}
				multiOpts.remove(pos);
			}

			if (singleOpts.contains(act)) {
				singleOpts.remove(act);
			}
		}

		javacOptions.addAll(singleOpts);
		javacOptions.addAll(multiOpts);
	}

	private static void checkJavacOptions() {
		List<String> newList = new ArrayList<>();

		// collapse multiple cp/classpath options into a single one, if there are more than one
		String cp = "";
		for (int i = 0; i < javacOptions.size(); i++) {
			String o = javacOptions.get(i);
			if (o.startsWith("-classpath") || o.startsWith("-cp")) {
				if (!cp.isEmpty()) {
					cp += File.pathSeparator;
				}
				cp += javacOptions.get(i + 1);
				++i;
			} else {
				newList.add(o);
			}
		}
		if (cp.isEmpty()) {
			cp = ".";
		}
		newList.add("-cp");
		newList.add(cp);

		createClasspathListFile(cp);

		javacOptions = newList;
		newList = new ArrayList<>();

		for (int i = 0; i < javacOptions.size(); i++) {
			String o = javacOptions.get(i);
			if (o.startsWith("-J") && !o.startsWith("-JAN_")) // keep the spec JAN options of javac
				continue;
			if (o.equals("-version"))
				continue;
			if (o.equals("-help"))
				continue;
			if (o.equals("-Xprint"))
				continue;
			if (o.equals("-Xstdout")) {
				i++;
				continue;
			}
			if (o.equals("-target")) {
				if (i + 1 < javacOptions.size()) {
					String targetValue = javacOptions.get(i + 1);
					// these target options have been removed in JDK 8
					if ("jsr14".equals(targetValue) || "1.4.1".equals(targetValue) || "1.4.2".equals(targetValue)) {
						logger.error("error.jan.OptionParser.removedUndocumentedTargetOption", targetValue);
						i++;
						continue;
					}
				}
			}
			if (o.startsWith("-g")) {
				newList.add("-g");
				continue;
			}
			newList.add(o);
		}

		javacOptions = newList;
	}

	private static void createClasspathListFile(String fullCp) {
		if (usedClasspathList != null) {
			try (PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(new File(usedClasspathList))))) {
				String[] splittedCp = fullCp.split(File.pathSeparator);
				StringBuilder pathPrefix = new StringBuilder();
				for (String cpFragment : splittedCp) {
					pathPrefix.append(cpFragment);
					if (new File(pathPrefix.toString()).exists()) {
						pw.println(pathPrefix);
						pathPrefix = new StringBuilder();
					} else {
						// because ; is a valid character in directory names in windows
						pathPrefix.append(File.pathSeparator);
					}
				}
			} catch (IOException e) {
				logger.error("error.jan.OptionParser.cpListWriteError", e);
			}
		}
	}

	private static void processArgFile(BufferedReader br) throws IOException {
		String line;
		while ((line = br.readLine()) != null) {
			StringTokenizer st = new StringTokenizer(line, " ");
			boolean storeDestDir = false;
			while (st.hasMoreTokens()) {
				String token = st.nextToken();
				boolean pars = false;
				if (token.startsWith("\"")) {
					pars = true;
					while (!token.endsWith("\"")) {
						String next = st.nextToken();
						token += " " + next;
					}
				}
				if (pars) {
					token = token.substring(1, token.length() - 1);
				}
				if (storeDestDir) {
					storeDestDir = false;
					outputDir = token;
				}
				if (token.equals("-d")) {
					storeDestDir = true;
				}
				if (token.endsWith(".java")) {
					File f = new File(token);
					if (f.getAbsoluteFile().isFile() || token.contains("*")) {
						inputs.add(token);
						continue;
					}
				}
				javacOptions.add(token);
			}
		}
	}

	private static void parseOptionsFromConfig(String fileName) throws Exception {
		Map<String, String> options = ConfigReader.readSection(fileName, "JAN");
		String optionsLikeCmd = "";
		if (options != null) {
			if (options.size() > 0) {
				for (Entry<String, String> e : options.entrySet()) {
					optionsLikeCmd += "|" + e.getKey() + "=" + e.getValue();
				}
			}
		}
		if (!optionsLikeCmd.isEmpty()) {
			parseOptionsFromCmd(optionsLikeCmd);
		}
	}

	private static void parseOptionsFromCmd(String str) {
		Field f;
		StringTokenizer t = new StringTokenizer(str, delim);
		logger.info("info.jan.OptionParser.janOptions");
		while (t.hasMoreTokens()) {
			String token = t.nextToken();
			try {
				String[] parts = token.split(equal);
				logger.info("info.jan.OptionParser.janOption", token);
				f = OptionParser.class.getDeclaredField(parts[0]);

				if (f.getType() == Integer.TYPE) {
					f.setInt(null, Integer.parseInt(parts[1]));
				} else if (f.getType() == Boolean.TYPE) {
					try {
						f.setBoolean(null, Integer.parseInt(parts[1]) == 1 ? true : false);
					} catch (NumberFormatException e) {
						if (parts[1].equals("true")) {
							f.setBoolean(null, true);
						} else if (parts[1].equals("false")) {
							f.setBoolean(null, false);
						} else {
							throw e;
						}
					}
				} else if (f.getType().equals(String.class)) {
					if (parts.length == 1) {
						f.set(null, null);
					} else {
						f.set(null, parts[1]);
					}
				} else {
					throw new Exception(logger.formatMessage("ex.jan.OptionParser.unexpectedOptionType"));
				}
			} catch (Exception e) {
				logger.error("error.jan.OptionParser.errorParsingJANArgs", token, e);
				System.exit(1);
			}
		}
	}

	public static String changePath(String params, String workingDir) {
		String result = "";
		if (workingDir.isEmpty())
			return params;

		String[] array = params.split("[|]");
		for (int i = 0; i < array.length; i++) {
			String s = array[i];
			if (!s.equals("")) {
				result += "|" + s;
				if (s.equals("-cp") || s.equals("-classpath") || s.equals("-sourcepath") || s.equals("-bootclasspath")
						|| s.equals("-processorpath")) {
					String path = array[++i];
					String delim = ":";
					if (path.contains(";")) {
						delim = ";";
					} else if (path.contains(":")) {
						delim = ":";
					}
					String[] paths = path.split("[;:]");
					String tmp = "";
					for (String p : paths) {
						if (p.equals(".")) {
							tmp += delim + workingDir;
						} else {
							tmp += delim + workingDir + p;
						}
					}
					result += "|" + tmp.substring(1);
				}
			}
		}

		return result;
	}

	public static String[] preProcessArgs(String[] args) {
		List<String> ret = new ArrayList<>();
		String janOptsWithDelims = "";
		String javacOptsWithDelims = "";
		String workingDir = "";
		// find working directory
		try {
			for (int i = 0; i < args.length; i++) {
				String s = args[i];
				if (s.startsWith("--workingDirectory:")) {
					workingDir = s.substring(18);
				} else if (s.startsWith("-w:")) {
					workingDir = s.substring(3);
				} else if (s.equals("--workingDirectory") || s.equals("-w")) {
					workingDir = args[i + 1];
				}
			}
		} catch (Exception e) {
			// Cannot find working directory
			workingDir = "";
		}
		for (int i = 0; i < args.length; i++) {
			String s = args[i];

			if (s.isEmpty()) {
				continue;
			}

			if (s.startsWith("--javacoptions") || s.startsWith("-j")) {
				if (s.startsWith("-j:|")) {
					StringTokenizer st = new StringTokenizer(s.substring(4));
					while (st.hasMoreTokens()) {
						javacOptsWithDelims += "|" + st.nextToken();
					}
					continue;
				} else if (s.startsWith("-j:")) {
					javacOptsWithDelims += "|" + s.substring(3);
					continue;
				} else if (s.startsWith("--javacoptions:")) {
					javacOptsWithDelims += "|" + s.substring(15);
					continue;
				} else {
					javacOptsWithDelims += "|" + args[++i];
					continue;
				}
			}
			if (s.startsWith("--janoptions") || s.startsWith("-a")) {
				if (s.startsWith("-a:")) {
					janOptsWithDelims += "|" + s.substring(3);
					continue;
				} else if (s.startsWith("--janoptions:")) {
					janOptsWithDelims += "|" + s.substring(13);
					continue;
				} else {
					janOptsWithDelims += "|" + args[++i];
					continue;
				}
			}
			ret.add(s);
		}

		if (javacOptsWithDelims != "") {
			ret.add("-j");
			javacOptsWithDelims = changePath(javacOptsWithDelims, workingDir);
			ret.add(javacOptsWithDelims);
		}

		if (janOptsWithDelims != "") {
			ret.add("-a");
			ret.add(janOptsWithDelims);
		}

		return ret.toArray(new String[ret.size()]);
	}
}
