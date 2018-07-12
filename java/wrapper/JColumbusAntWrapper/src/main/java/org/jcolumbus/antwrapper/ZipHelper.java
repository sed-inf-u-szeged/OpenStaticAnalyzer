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

import org.apache.tools.ant.taskdefs.Zip;
import org.apache.tools.ant.taskdefs.Zip.ArchiveState;
import org.apache.tools.ant.types.Resource;

import columbus.logger.LoggerHandler;

public class ZipHelper {

	private static final LoggerHandler logger = new LoggerHandler(ZipHelper.class, Options.messagesFile);

	private static String columbusResultDir = Options.columbusResultDir;
	private static String[] excluded = { "**" + File.separator + columbusResultDir + File.separator + "**" };

	private static String getJANLinkListFileName() {
		return Util.getRollingFileName(EnvironmentVariables.WRAPPER_TEMP_DIR, "JANLink_input", ".txt");
	}

	private static String getSuperLinkFileName() {
		return EnvironmentVariables.WRAPPER_LOG_DIR + "/superlinklist.txt";
	}

	public static String writeListFile(Zip zip, ArchiveState state, File zipFile) {
		String inputList = null;
		PrintWriter writer = null;
		try {
			Resource[][] toAdd = state.getResourcesToAdd();
			if (toAdd != null) {
				inputList = getJANLinkListFileName();
				writer = new PrintWriter(new BufferedWriter(new FileWriter(inputList)));
				// FIXME update mode
				if (/* isInUpdateMode() && */new File(zipFile + ".ljsi").exists()) {
					writer.println(zipFile.toString() + ".ljsi");
				}
				String fileName;
				for (Resource[] resources : toAdd) {
					for (Resource res : resources) {
						fileName = res.toString();
						fileName = Util.replaceExtensionAndAddPlusDir(fileName, null);

						if (fileName != null && new File(fileName).exists()) {
							writer.println(fileName);
						}
					}
				}
			}
		} catch (IOException e) {
			logger.error("error.antwrapper.ZipHelper.ioExCreatingInputList", e);
		} catch (Exception e) {
			logger.error("error.antwrapper.ZipHelper.printEx", e);
		} finally {
			if (writer != null) {
				writer.close();
			}
		}
		return inputList;
	}

	public static void link(Zip zip, File zipFile, boolean needToLink, String inputList) {
		File listFile = new File(inputList);
		if (!listFile.exists()) {
			return;
		}

		PrintStream origOut = System.out;
		PrintStream origErr = System.err;

		String logDir = EnvironmentVariables.WRAPPER_LOG_DIR;
		String logfile = logDir + "/" + Options.JWRAPPER_LOG;

		try {
			PrintStream ps = new PrintStream(new FileOutputStream(logfile, true));
			System.setOut(ps);
			System.setErr(ps);
		} catch (FileNotFoundException e) {
			logger.error("error.antwrapper.ZipHelper.couldntOpenLogFile", logfile, e);
		}
		BufferedReader input = null;
		PrintWriter superlinkfile = null;
		try {
			if (needToLink && listFile.length() > 0) {
				zip.getProject().setDescription("JANLink");
				ArrayList<String> args = new ArrayList<>();
				args.add("JANLink");

				String ljsiFile = Util.addDirToPath(zipFile.toString() + ".ljsi", columbusResultDir, false, null);
				File f = new File(ljsiFile);
				if (!f.getParentFile().exists()) {
					f.getParentFile().mkdirs();
				}

				args.add("-out:" + ljsiFile);
				args.add("-inputlist:" + inputList);
				logger.info("info.antwrapper.ZipHelper.exec", args);
				ProcessBuilder pb = new ProcessBuilder(args);
				pb.redirectErrorStream(true);
				Process p = pb.start();

				String line;
				input = new BufferedReader(new InputStreamReader(p.getInputStream()));
				while ((line = input.readLine()) != null) {
					logger.info("info.antwrapper.ZipHelper.janLink", line);
				}

				superlinkfile = new PrintWriter(new BufferedWriter(new FileWriter(getSuperLinkFileName(), true)));
				int exit = p.waitFor();
				if (exit != 0) {
					Util.appendErrorMsg("EXEC: " + args + System.getProperty("line.separator")
							+ "The execution of JANLink is terminated with error code " + exit + ".");
					logger.error("error.antwrapper.ZipHelper.janLinkExecutionError", exit);
				} else {
					superlinkfile.println(ljsiFile);
				}
			}
		} catch (Exception e) {
			Util.appendErrorMsg("There were some Exception while executing JANLink. " + e);
			logger.error("error.antwrapper.ZipHelper.exceptionExecutingJanLink", e);
		} finally {
			if (input != null) {
				try {
					input.close();
				} catch (IOException e) {
					logger.error("error.antwrapper.ZipHelper.couldntCloseStream", e);
				}
			}
			if (superlinkfile != null) {
				superlinkfile.close();
			}
			System.setOut(origOut);
			System.setErr(origErr);
		}
	}

	public static void addExcludes(org.apache.tools.ant.taskdefs.MatchingTask task) {
		for (String s : excluded) {
			task.setExcludes(s);
		}
	}

	public static void addExcludes(org.apache.tools.ant.types.AbstractFileSet set) {
		for (String s : excluded) {
			set.setExcludes(s);
		}
	}

}
