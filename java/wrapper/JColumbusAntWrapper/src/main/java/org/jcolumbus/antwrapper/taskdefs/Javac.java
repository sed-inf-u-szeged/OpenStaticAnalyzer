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

package org.jcolumbus.antwrapper.taskdefs;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

import org.apache.tools.ant.BuildException;
import org.apache.tools.ant.util.FileUtils;
import org.jcolumbus.antwrapper.EnvironmentVariables;
import org.jcolumbus.antwrapper.Options;
import org.jcolumbus.antwrapper.Util;
import org.jcolumbus.antwrapper.compilers.MyCompilerAdapter;

import columbus.logger.LoggerHandler;

/**
 * Wrapper class of org.apache.tools.ant.taskdefs.Javac class
 */
public class Javac extends org.apache.tools.ant.taskdefs.Javac {

	private static final LoggerHandler logger = new LoggerHandler(Javac.class, Options.messagesFile);

	private String forkedExecutable;

	private static String getExtraArgFileName() {
		return Util.getRollingFileName(EnvironmentVariables.WRAPPER_TEMP_DIR, "extra_arg_file", ".arg");
	}

	private void runJANWrapper() {
		BufferedReader input = null;
		try {
			String logdir = EnvironmentVariables.WRAPPER_LOG_DIR;
			String tempDir = EnvironmentVariables.WRAPPER_TEMP_DIR;
			String binDir = EnvironmentVariables.WRAPPER_BIN_DIR;
			String callPmd = Options.CALL_PMD;

			ArrayList<String> JANCmd = new ArrayList<String>();
			JANCmd.add("java");

			if (Options.JAN_JVM_OPTS != null) {
				JANCmd.addAll(Options.JAN_JVM_OPTS);
			}

			JANCmd.add("-jar");
			JANCmd.add(EnvironmentVariables.WRAPPER_BIN_DIR + "/JAN.jar");

			if (Options.JAN_OPTIONS != null) {
				JANCmd.addAll(Options.JAN_OPTIONS);
			}

			if (getDestdir() != null) {
				JANCmd.add("-d");
				JANCmd.add(getDestdir().toString());
			}

			JANCmd.add("-e");
			JANCmd.add(tempDir);

			JANCmd.add("-p");

			String stat = Options.janStat;
			if (stat != null) {
				JANCmd.add("-t");
				JANCmd.add(logdir + File.separator + stat);
			}

			MyCompilerAdapter javac = new MyCompilerAdapter(this);
			String[] antJavacArgs = javac.createJavacArgumentArray();
			String[] antJavacInputs = javac.createJavacInputArray();

			if (antJavacInputs.length == 0) {
				logger.error("error.antwrapper.Javac.noFileToAnalyze");
				return;
			}

			String argFile = getExtraArgFileName();
			try (BufferedWriter bw = new BufferedWriter(new FileWriter(new File(argFile)))) {
				for (String s : antJavacArgs) {
					bw.write("\"" + s + "\"");
					bw.newLine();
				}
				for (String s : antJavacInputs) {
					bw.write("\"" + s + "\"");
					bw.newLine();
				}

				JANCmd.add("-f");
				JANCmd.add("@" + argFile);
			} catch (Exception e) {
				logger.error("error.antwrapper.Javac.errorWritingArgFile", e);
				System.exit(1);
			}

			String sourceList = null;
			String cpList = null;
			if (callPmd != null && callPmd.equals("1")) {
				sourceList = Util.getRollingFileName(tempDir, "source_file_list", ".lst");
				JANCmd.add("-s");
				JANCmd.add(sourceList);

				cpList = Util.getRollingFileName(tempDir, "classpath_list", ".lst");
				JANCmd.add("-u");
				JANCmd.add(cpList);
			}

			logger.info("info.antwrapper.Javac.exec", JANCmd);
			ProcessBuilder pb = new ProcessBuilder(JANCmd);
			pb.redirectErrorStream(true);
			Process p = pb.start();

			String line;
			input = new BufferedReader(new InputStreamReader(p.getInputStream()));
			while ((line = input.readLine()) != null) {
				logger.info("info.antwrapper.Javac.writeLine", line);
			}

			int exit = p.waitFor();
			if (exit != 0) {
				Util.appendErrorMsg(logger.formatMessage("info.antwrapper.Javac.exec", JANCmd)
						+ System.getProperty("line.separator")
						+ logger.formatMessage("error.antwrapper.Javac.errorExecutingJan", exit));
				logger.error("error.antwrapper.Javac.errorExecutingJan", exit);
			}

			if (callPmd != null && callPmd.equals("1")) {
				PrintWriter pw = null;
				try {
					ArrayList<String> PMDCmd = new ArrayList<String>();
					String pmdDir = binDir + File.separator + "PMD";

					PMDCmd.add("java");
					if (Options.JAN_JVM_OPTS != null) {
						PMDCmd.addAll(Options.JAN_JVM_OPTS);
					}
					PMDCmd.add("-Djava.ext.dirs=" + pmdDir + File.separator + "lib");
					PMDCmd.add("net.sourceforge.pmd.PMD");
					PMDCmd.add("-V");
					PMDCmd.add("-d");
					PMDCmd.add(sourceList);
					PMDCmd.add("-f");
					PMDCmd.add("xml");
					PMDCmd.add("-R");
					PMDCmd.add(pmdDir + "/PMD-config.xml");
					PMDCmd.add("-r");
					String pmdOutput = Util.getRollingFileName(tempDir, "PMD-out", ".xml");
					PMDCmd.add(pmdOutput);

					if (getSource() != null && !getSource().isEmpty()) {
						PMDCmd.add("-v");
						PMDCmd.add(getSource());
					}

					if (getEncoding() != null && !getEncoding().isEmpty()) {
						PMDCmd.add("-e");
						PMDCmd.add(getEncoding());
					}

					PMDCmd.add("-auxclasspath");
					PMDCmd.add("file:///" + cpList);

					logger.info("info.antwrapper.Javac.exec", PMDCmd);
					ProcessBuilder pbPMD = new ProcessBuilder(PMDCmd);
					pbPMD.redirectErrorStream(true);

					long pmdStartTime = System.currentTimeMillis();
					Process pPMD = pbPMD.start();

					String linePMD;
					BufferedReader inputPMD = new BufferedReader(new InputStreamReader(pPMD.getInputStream()));
					while ((linePMD = inputPMD.readLine()) != null) {
						logger.info("info.antwrapper.Javac.writeLine", linePMD);
					}

					pw = new PrintWriter(new BufferedWriter(new FileWriter(new File(logdir + "/pmd-output-list.txt"),
							true)));
					int exitPMD = pPMD.waitFor();

					if (Options.pmdStat != null) {
						long pmdEndTime = System.currentTimeMillis();
						long pmdTime = pmdEndTime - pmdStartTime;
						savePmdStats(pmdTime);
					}

					if (exitPMD != 0) {
						Util.appendErrorMsg(logger.formatMessage("info.antwrapper.Javac.exec", PMDCmd)
								+ System.getProperty("line.separator")
								+ logger.formatMessage("error.antwrapper.Javac.errorExecutingPmd", exitPMD));
						logger.error("error.antwrapper.Javac.errorExecutingPmd", exitPMD);
					} else {
						pw.println(pmdOutput);
					}
				} catch (Exception e) {
					Util.appendErrorMsg(logger.formatMessage("error.antwrapper.Javac.exDuringPmdAnalyzation"));
					logger.error("error.antwrapper.Javac.exDuringPmdAnalyzation", e);
				} finally {
					if (pw != null) {
						pw.close();
					}
				}
			}

		} catch (Throwable e) {
			Util.appendErrorMsg(logger.formatMessage("error.antwrapper.Javac.exDuringAnalyzation"));
			logger.error("error.antwrapper.Javac.exDuringAnalyzation", e);
		} finally {
			if (input != null) {
				try {
					input.close();
				} catch (IOException e) {
					logger.error("warn.antwrapper.Javac.couldntCloseStream", e);
				}
			}
		}
	}

	private void savePmdStats(long pmdTime) {
		final String delim = ";";
		String statPath = EnvironmentVariables.WRAPPER_LOG_DIR + File.separator + Options.pmdStat;
		File statFile = new File(statPath);
		boolean writeHeader = !statFile.exists();
		try (PrintWriter writer = new PrintWriter(new BufferedWriter(new FileWriter(statFile, true)))) {
			if (writeHeader) {
				writer.println("Total cpu time (s)" + delim + "Peak memory usage (MB)");
			}
			writer.println((pmdTime / 1000.0) + delim + 0);
		} catch (IOException e) {
			logger.error("warn.antwrapper.Javac.couldntSavePMDStat", statPath, e);
		}
	}

	@Override
	protected void scanDir(File srcDir, File destDir, String[] files) {
		if (Options.RECOMPILE_ALL != null && !Options.RECOMPILE_ALL.equals("0")) {
			List<File> scannedFiles = new ArrayList<File>();
			FileUtils fileUtils = FileUtils.getFileUtils();
			File file;
			for (String fileName : files) {
				file = fileUtils.resolveFile(srcDir, fileName);
				if (file.getName().endsWith(".java")) {
					scannedFiles.add(file);
				}
			}
			File[] newFiles = scannedFiles.toArray(new File[scannedFiles.size()]);
			if (newFiles.length > 0) {
				File[] newCompileList = new File[compileList.length + newFiles.length];
				System.arraycopy(compileList, 0, newCompileList, 0, compileList.length);
				System.arraycopy(newFiles, 0, newCompileList, compileList.length, newFiles.length);
				compileList = newCompileList;
			}
		} else {
			super.scanDir(srcDir, destDir, files);
		}
	}

	public void compile() throws BuildException {
		PrintStream origOut = System.out;
		PrintStream origErr = System.err;

		String logfile = EnvironmentVariables.WRAPPER_LOG_DIR + "/" + Options.JWRAPPER_LOG;
		try {
			PrintStream ps = new PrintStream(new FileOutputStream(logfile, true));
			System.setOut(ps);
			System.setErr(ps);
		} catch (FileNotFoundException e) {
			logger.error("warn.antwrapper.Javac.couldntOpenLogFile", e);
		}

		try {
			runJANWrapper();
		} finally {
			System.setOut(origOut);
			System.setErr(origErr);
		}

		super.compile();
	}

	// FIXME: always has to be the same as the overrided method
	@Override
	public String getJavacExecutable() {
		if (forkedExecutable == null && isForkedJavac()) {
			forkedExecutable = getSystemJavac();
		} else if (forkedExecutable != null && !isForkedJavac()) {
			forkedExecutable = null;
		}
		return forkedExecutable;
	}
}
