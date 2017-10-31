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

package org.jcolumbus.antwrapper;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

import columbus.logger.LoggerHandler;

public class Util {

	private static final LoggerHandler logger = new LoggerHandler(Util.class, Options.messagesFile);

	private static String[] oldExt = { ".class", ".jar", ".war", ".ear" };
	private static String[] newExt = { ".jsi", ".jar.ljsi", ".war.ljsi", ".ear.ljsi", ".ear.ljsi" };

	private static String columbusResultDir = Options.columbusResultDir;
	private static String errorFile = EnvironmentVariables.WRAPPER_LOG_DIR + "/" + "Error.log";

	public static String getRollingFileName(String dirName, String fileName, String ext) {
		File f;
		int index = 1;
		while ((f = new File(dirName, fileName + index + ext)).exists())
			++index;
		return f.toString();
	}

	public static void appendErrorMsg(String msg) {
		PrintWriter errorWriter = null;
		try {
			errorWriter = new PrintWriter(new BufferedWriter(new FileWriter(new File(errorFile), true)));
			errorWriter.println(msg);
		} catch (IOException e) {
			logger.error("error.antwrapper.Util.printEx", e);
		} finally {
			if (errorWriter != null) {
				errorWriter.close();
			}
		}
	}

	/**
	 * Returns file name with replaced extension if possible, otherwise returns null.
	 * 
	 * @param fileName
	 *            the filename to process
	 * @return filename with replaced extension or null if old extension isn't in the list
	 * @throws Exception
	 */
	public static String replaceExtension(String fileName) throws Exception {
		for (int i = 0; i < oldExt.length; i++) { // iterate over possible extensions
			if (fileName.endsWith(oldExt[i])) {
				fileName = fileName.substring(0, fileName.lastIndexOf(oldExt[i])) + newExt[i];
				return fileName;
			}
		}
		return null; // extension not found
	}

	/**
	 * @param fileName
	 * @param checkWithPrefix
	 *            Only for debug.
	 * @return
	 * @throws Exception
	 */
	public static String replaceExtensionAndAddPlusDir(String fileName, String checkWithPrefix) throws Exception {
		String ret = replaceExtension(fileName);

		if (ret == null) {
			return ret;
		} else {
			return Util.addDirToPath(ret, columbusResultDir, false, checkWithPrefix);
		}
	}

	public static void reWriteListFile(String listFile, String oldLine, String newLine) throws IOException {
		logger.debug("debug.antwrapper.Util.swapFiles", oldLine, newLine);
		BufferedReader br = null;
		PrintWriter pw = null;
		try {
			// read the original superlink list, and create a new one
			br = new BufferedReader(new FileReader(new File(listFile)));
			String line;
			List<String> newList = new ArrayList<>();
			while ((line = br.readLine()) != null) {
				if (line.equals(oldLine)) {
					if (!newLine.equals("")) {
						newList.add(newLine);
					}
				} else {
					newList.add(line);
				}
			}
			// delete the original list
			br.close();
			File f = new File(listFile);
			f.delete();
			// write the new superlink list to the same file
			f = new File(listFile);
			pw = new PrintWriter(new BufferedWriter(new FileWriter(f)));
			for (String s : newList) {
				pw.println(s);
			}
		} catch (Exception e) {
			logger.error("error.antwrapper.Util.printEx", e);
		} finally {
			pw.close();
			br.close();
		}

	}

	/**
	 * @param path
	 *            The original path.
	 * @param extraDir
	 *            The directory, what we want do add to the path.
	 * @param isDir
	 *            True if the given path is a directory(it doesn't have to exist).
	 * @param checkWithPrefix
	 *            Concat the created path with the prefix and check if its exist. Only for debug.
	 * @return
	 * @throws Exception
	 */
	public static String addDirToPath(String path, String extraDir, boolean isDir, String checkWithPrefix)
			throws Exception {
		// if extraDir doesn't exist return the original path
		StringBuilder createdPath = new StringBuilder();
		if (extraDir != null) {
			if (isDir) {
				createdPath.append(path);
				if (!path.endsWith(File.separator)) {
					createdPath.append(File.separator);
				}
				createdPath.append(extraDir);
			} else {
				int lastSlashPos = (path.replace("\\", "/").lastIndexOf("/"));

				if (lastSlashPos == -1) {
					createdPath.append(extraDir).append(File.separator).append(path);
				} else {
					createdPath.append(path.substring(0, lastSlashPos));
					createdPath.append(File.separator).append(extraDir);
					createdPath.append(path.substring(lastSlashPos, path.length()));
				}
			}
		}

		if (checkWithPrefix != null) {
			File f;
			if (checkWithPrefix.isEmpty()) {
				f = new File(createdPath.toString());
			} else {
				f = new File(checkWithPrefix, createdPath.toString());
			}
			if (!f.exists()) {
				String p = f.getAbsolutePath();
				int lastDotPos = p.lastIndexOf(".");
				int lastSlashPos = p.lastIndexOf(File.separator);
				lastSlashPos = lastSlashPos == -1 ? 0 : lastSlashPos;
				int lastDollarPos = p.indexOf("$", lastSlashPos);

				if (lastDollarPos == -1) {
					logger.warn("warn.antwrapper.Util.fileDoesntExist", f.getAbsolutePath());
					return null;
				}

				File classNameWithoutSubClass = new File(p.substring(0, lastDollarPos) + p.substring(lastDotPos));
				if (classNameWithoutSubClass.exists()) {
					return null;
				} else {
					logger.warn("warn.antwrapper.Util.fileDoesntExist", classNameWithoutSubClass.getAbsolutePath());
					return null;
				}
			}
		}

		return createdPath.toString();
	}
}
