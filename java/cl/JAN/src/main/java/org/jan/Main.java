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

package org.jan;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.net.URISyntaxException;
import java.util.ArrayList;
import java.util.List;
import java.util.TreeSet;

import columbus.CsiHeader;
import columbus.StrTable;
import columbus.java.asg.Factory;
import columbus.java.asg.algorithms.AlgorithmPreorder;
import columbus.logger.LoggerHandler;
import columbus.revision.Revision;

import com.lexicalscope.jewel.cli.ArgumentValidationException;
import com.lexicalscope.jewel.cli.CliFactory;
import com.sun.source.tree.CompilationUnitTree;
import com.sun.tools.javac.parser.JavadocTokenizer;
import com.sun.tools.javac.tree.JCTree.JCCompilationUnit;
import com.sun.tools.javac.util.Context;

public class Main {

	private static final LoggerHandler logger = new LoggerHandler(Main.class, OptionParser.getLoggerPropertyFile());

	// max memory usage in MB
	private static long maxTotalMem = 0;
	private static long maxUsedMem = 0;

	public static void updateMemoryUsage() {
		final int mb = 1024 * 1024;
		Runtime runtime = Runtime.getRuntime();
		long total = runtime.totalMemory() / mb;
		long free = runtime.freeMemory() / mb;
		long used = total - free;
		if (logger.isDebugEnabled()) {
			logger.debug("debug.jan.Main.usedMemory", used, total);
		}
		if (total > maxTotalMem) {
			maxTotalMem = total;
		}
		if (used > maxUsedMem) {
			maxUsedMem = used;
		}
	}

	public static void main(String[] args) {
		logger.info("info.jan.Main.janInfo", Revision.getBranchNumber(), Revision.getRevision());

		Timer phaseTimer, totalTimer;
		ArrayList<Timer> timers = new ArrayList<>();
		totalTimer = new Timer(logger.formatMessage("info.jan.Main.statTotalTime"));
		totalTimer.start();
		timers.add(totalTimer);

		String baseDir = null;
		try {
			baseDir = new File(Main.class.getProtectionDomain().getCodeSource().getLocation().toURI()).getParent();
		} catch (URISyntaxException e) {
			logger.error("error.jan.Main.determineLocationOfExecutableEx", e);
			System.exit(1);
		}

		Main.updateMemoryUsage();

		OptionParser.setConfigFileDir(baseDir);

		processArguments(args);

		List<File> fileNames = FileCollector.collectFiles(OptionParser.getInputs());

		Factory fact = new Factory(new StrTable());
		fact.turnFilterOff();

		if (OptionParser.getAnalyzedSourceList() != null) {
			FileCollector.writeSourceFileList(fileNames, OptionParser.getAnalyzedSourceList());
		}

		int inputsBeforeHardFiltering = fileNames.size();
		boolean fillFactory = true;

		if (fileNames.isEmpty()) { // if there is no input -> create empty jsi
			fillFactory = false;
			logger.warn("error.jan.Main.inputMustBeGiven");
		}

		if (OptionParser.hardFilter != null) {
			Filter.filterList(fileNames, OptionParser.hardFilter);
		}

		if (fileNames.isEmpty()) { // if there is no input after filtering -> create empty jsi
			fillFactory = false;
			if (inputsBeforeHardFiltering > 0) {
				logger.warn("warn.jan.Main.allInputFiltered");
			}
		}

		Main.updateMemoryUsage();

		if (fillFactory) {
			// JAVAC Build
			phaseTimer = new Timer(logger.formatMessage("info.jan.Main.statJDKCompileTime"));
			timers.add(phaseTimer);
			phaseTimer.start();
			List<CompilationUnitTree> trees = null;
			JDKTreeMaker jdkTreeMaker = null;
			try {
				jdkTreeMaker = new JDKTreeMaker();
				trees = jdkTreeMaker.build(fileNames, OptionParser.getJavacOptions());
			} catch (Exception e) {
				logger.error("error.jan.Main.JDKTreeMakerEx", e);
				System.exit(1);
			}
			phaseTimer.stop();
			Main.updateMemoryUsage();

			// JAN Build
			logger.info("info.jan.Main.rebuildTrees");
			phaseTimer = new Timer(logger.formatMessage("info.jan.Main.statTreeRebuildingTime"));
			timers.add(phaseTimer);
			phaseTimer.start();
			SymbolMaps symMaps = new SymbolMaps();
			TreeBuilder builder = new TreeBuilder(fact, symMaps, jdkTreeMaker.getContext());
			FileProcessor fprocessor = new FileProcessor();
			TreeSet<Integer> resultSet = new TreeSet<>();
			for (CompilationUnitTree t : trees) {
				try {
					builder.visit((JCCompilationUnit) t);
					//Set the LLOC value on type declaration and method declaration nodes.
					resultSet = fprocessor.processFile(t.getSourceFile().getName());
					builder.setLLOCToSubTree(resultSet);
				} catch (Exception e) {
					logger.error("error.jan.Main.TreeBuilderEx", e);
					System.exit(1);
				}
			}
			phaseTimer.stop();
			Main.updateMemoryUsage();

			// Build comments
			phaseTimer = new Timer(logger.formatMessage("info.jan.Main.statCommentBuilding"));
			timers.add(phaseTimer);
			phaseTimer.start();
			if (OptionParser.isKeepComments()) {
				logger.info("info.jan.Main.buildComments");
				CommentBuilder commentBuilder = new CommentBuilder(fact, JavadocTokenizer.commentMap);
				try {
					commentBuilder.build();
				} catch (Exception e) {
					logger.error("error.jan.Main.commentBuilderEx", e);
					System.exit(1);
				}
			}
			phaseTimer.stop();
			Main.updateMemoryUsage();

			// Build external classes
			phaseTimer = new Timer(logger.formatMessage("info.jan.Main.statExternalClassBuildingTime"));
			timers.add(phaseTimer);
			phaseTimer.start();
			int nodesBeforeExternalClasses = fact.size();
			logger.info("info.jan.Main.createExtClasses");
			try {
				ExternalClassBuilder extClassBuilder = new ExternalClassBuilder(fact, builder, symMaps,
						jdkTreeMaker.getContext());
				extClassBuilder.build();
			} catch (Exception e) {
				logger.error("error.jan.Main.extClassBuildEx", e);
				System.exit(1);
			}
			phaseTimer.stop();
			Main.updateMemoryUsage();

			// release
			builder = null;

			// Set crossedges
			logger.info("info.jan.Main.setCrossEdges");
			phaseTimer = new Timer(logger.formatMessage("info.jan.Main.statCrossedgeSettingTime"));
			timers.add(phaseTimer);
			phaseTimer.start();
			int nodesAfterExternalClasses = fact.size();
			try {
				CrossEdges crossEdges = new CrossEdges(fact, symMaps, jdkTreeMaker.getContext());
				crossEdges.setCrossEdges();
			} catch (Exception e) {
				logger.error("error.jan.Main.crossEdgeEx", e);
				System.exit(1);
			}
			phaseTimer.stop();
			Main.updateMemoryUsage();

			// Build types
			phaseTimer = new Timer(logger.formatMessage("info.jan.Main.statTypeBuildingTime"));
			timers.add(phaseTimer);
			phaseTimer.start();
			logger.info("info.jan.Main.buildTypes");
			try {
				TypeBuilder typeBuilder = new TypeBuilder(fact, symMaps);
				typeBuilder.build();
			} catch (Exception e) {
				logger.error("error.jan.Main.typeBuilderEx", e);
				System.exit(1);
			}
			phaseTimer.stop();
			Main.updateMemoryUsage();

			// release
			symMaps = null;

			// Check ASG
			phaseTimer = new Timer(logger.formatMessage("info.jan.Main.statASGCheckingTime"));
			timers.add(phaseTimer);
			phaseTimer.start();
			if (OptionParser.isNeedCheck()) {
				logger.info("info.jan.Main.CheckAsg");
				check(fact, jdkTreeMaker.getContext());
			}
			phaseTimer.stop();
			Main.updateMemoryUsage();

			// release
			jdkTreeMaker = null;
			trees = null;

			// Create filter
			phaseTimer = new Timer(logger.formatMessage("info.jan.Main.statFilterGeneratingTime"));
			timers.add(phaseTimer);
			phaseTimer.start();
			if (OptionParser.getCommonJsi() != null) { // create filter only if normal jsi is required
				logger.info("info.jan.Main.filter");
				Filter filter = new Filter(fact, nodesBeforeExternalClasses, nodesAfterExternalClasses);
				try {
					fact.turnFilterOn();
					filter.run();
					fact.turnFilterOff();
				} catch (Exception e) {
					logger.error("error.jan.Main.filterEx", e);
					System.exit(1);
				}
			}
			phaseTimer.stop();
			Main.updateMemoryUsage();
		}

		CsiHeader header = new CsiHeader();
		String os = System.getProperty("os.name").toLowerCase();
		if (os.contains("linux")) {
			header.add("platform", "linux");
		} else if (os.contains("windows")) {
			header.add("platform", "windows");
		} else {
			header.add("platform", os);
		}

		// Create one jsi output file
		phaseTimer = new Timer(logger.formatMessage("info.jan.Main.statCommonJsiSavingTime"));
		timers.add(phaseTimer);
		phaseTimer.start();
		if (OptionParser.getCommonJsi() != null) {
			logger.info("info.jan.Main.saveJsi");
			ClassSaver.saveToJsi(fact, OptionParser.getCommonJsi(), header);
		}
		phaseTimer.stop();

		// Create one jml output file
		phaseTimer = new Timer(logger.formatMessage("info.jan.Main.statCommonJmlSavingTime"));
		timers.add(phaseTimer);
		phaseTimer.start();
		if (OptionParser.getCommonXml() != null) {
			logger.info("info.jan.Main.saveJml");
			if (OptionParser.isMinXml())
				ClassSaver.saveMinXml(fact, OptionParser.getCommonXml());
			else
				ClassSaver.saveToXml(fact, OptionParser.getCommonXml());
		}
		phaseTimer.stop();

		// Create one jsi for each input source files
		phaseTimer = new Timer(logger.formatMessage("info.jan.Main.statSmallJsiSavingTime"));
		timers.add(phaseTimer);
		phaseTimer.start();
		if (OptionParser.getOutputDir() != null || OptionParser.wrappedMode) {
			logger.info("info.jan.Main.saveJsiByClasses");
			ClassSaver.saveClasses(fact, OptionParser.getOutputDir(), OptionParser.getExtraJsiDir(), header);
		}
		phaseTimer.stop();
		totalTimer.stop();

		Main.updateMemoryUsage();

		logger.info("info.jan.Main.cpuTimes");
		for (Timer t : timers) {
			logger.infoMsg("  " + t.getInfo() + ": {}", (t.getTotalCpuTime() / 1000.0));
		}
		logger.info("info.jan.Main.userTimes");
		for (Timer t : timers) {
			logger.infoMsg("  " + t.getInfo() + ": {}", (t.getTotalUserTime() / 1000.0));
		}
		logger.info("info.jan.Main.memoryStatistics");
		logger.info("info.jan.Main.maxTotalMemory", maxTotalMem);
		logger.info("info.jan.Main.maxUsedMemory", maxUsedMem);
		logger.info("info.jan.Main.otherStatistics");
		logger.info("info.jan.Main.analyzedFiles", fileNames.size());
		logger.info("info.jan.Main.numOfWarnings", logger.getWarnMessages());
		logger.info("info.jan.Main.numOfErrors", logger.getErrorMessages());

		String statisticFileName = OptionParser.getStatisticFile();
		if (statisticFileName != null) {
			saveStatistics(statisticFileName, timers, args, fileNames);
		}
	}

	private static void processArguments(String[] args) {
		JANCmdLine cmd = null;

		args = OptionParser.preProcessArgs(args);

		if (args.length == 0) {
			logger.error("error.jan.Main.cliFactError", CliFactory.createCli(JANCmdLine.class).getHelpMessage());
			System.exit(1);
		}

		try {
			cmd = CliFactory.parseArguments(JANCmdLine.class, args);
		} catch (ArgumentValidationException e) {
			logger.error("error.jan.Main.cannotParseArgs", e);
			System.exit(1);
		}

		if (cmd.isVersion()) {
			System.exit(0);
		}

		try {
			OptionParser.processCmdLine(cmd);
		} catch (Exception e) {
			logger.error("error.jan.Main.cannotProcessCmdArgs", e);
			System.exit(1);
		}

	}

	private static void check(Factory fact, Context context) {
		Checker checker = new Checker(fact, context);
		AlgorithmPreorder algPre = new AlgorithmPreorder();
		algPre.run(fact, checker);
	}

	private static void saveStatistics(String fileName, ArrayList<Timer> timers, String[] args, List<File> fileNames) {
		final String delimiter = ";";
		File file = new File(fileName);

		try (BufferedWriter writer = new BufferedWriter(new FileWriter(file, true))) {
			boolean writer_header = !file.exists();

			int i, size = timers.size();
			Timer timer;

			// header
			if (writer_header) {
				timer = timers.get(0);
				writer.write(timer.getInfo() + "(total cpu)" + delimiter + "Memory usage(MB)" + delimiter
						+ timer.getInfo() + "(user)");
				writer.write(delimiter);
				for (i = 1; i < size; i++) {
					timer = timers.get(i);
					writer.write(timer.getInfo() + "(total cpu)" + delimiter + timer.getInfo() + "(user)");
					writer.write(delimiter);
				}
				writer.write("Number of sources" + delimiter + "Number of errors" + delimiter + "Number of warnings"
						+ delimiter + "args");
				writer.newLine();
			}

			// data
			timer = timers.get(0);
			writer.write((timer.getTotalCpuTime() / 1000.0) + delimiter + maxUsedMem + delimiter
					+ (timer.getTotalUserTime() / 1000.0));
			writer.write(delimiter);
			for (i = 1; i < size; i++) {
				timer = timers.get(i);
				writer.write((timer.getTotalCpuTime() / 1000.0) + delimiter + (timer.getTotalUserTime() / 1000.0));
				writer.write(delimiter);

			}
			writer.write(fileNames.size() + delimiter);
			writer.write(logger.getErrorMessages() + delimiter);
			writer.write(logger.getWarnMessages() + delimiter);
			for (String str : args) {
				writer.write("\"" + str + "\" ");
			}
			writer.newLine();
		} catch (IOException e) {
			logger.error("error.jan.Main.savingStatisticsEx", e);
		}
	}
}
