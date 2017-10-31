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

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import columbus.logger.LoggerHandler;

public class FileCollector {

	private static final LoggerHandler logger = new LoggerHandler(FileCollector.class,
			OptionParser.getLoggerPropertyFile());

	private static String IN_COLUMBUS_REGTEST_ENV_VAR = "IN_COLUMBUS_REGTEST";
	private static boolean IN_COLUMBUS_REGTEST = System.getenv(IN_COLUMBUS_REGTEST_ENV_VAR) != null;

	public static List<File> collectFiles(List<String> fileNames) {
		Set<File> inputFiles = new HashSet<>();
		for (String s : fileNames) {
			if (s.contains("*")) {
				// if there is a * in the path, we add the parent directory as the input list
				int lastSlashPos = s.replace("\\", "/").lastIndexOf("/");
				String parentDir = null;
				if (lastSlashPos == -1) {
					parentDir = ".";
				} else {
					parentDir = s.substring(0, lastSlashPos);
				}

				collectFiles(inputFiles, new File(parentDir), false, s.substring(lastSlashPos + 1).split("\\*"));
			} else {
				collectFiles(inputFiles, new File(s), true, null);
			}
		}

		File[] fileList = inputFiles.toArray(new File[inputFiles.size()]);
		Arrays.sort(fileList, new Comparator<File>() {
			@Override
			public int compare(File o1, File o2) {
				return o1.getPath().compareToIgnoreCase(o2.getPath());
			}
		});

		return new ArrayList<>(Arrays.asList(fileList));
	}

	public static void writeSourceFileList(List<File> inputFiles, String listFileName) {
		try (BufferedWriter bw = new BufferedWriter(new FileWriter(new File(listFileName)))) {
			for (File f : inputFiles) {
				bw.write(f.getAbsolutePath());
				bw.newLine();
			}
		} catch (IOException e) {
			logger.error("error.jan.FileCollector.fileListWritingErr", e);
		}
	}

	private static void collectFiles(Set<File> inputFiles, File file, boolean recursively, String[] patternFragments) {

		if (!file.exists()) {
			logger.error("error.jan.FileCollector.fileOrDirDoesNotExist", file);
			return;
		}

		if (file.isDirectory()) {
			for (File f : file.listFiles()) {
				// according to the description of File.listFiles(), the result array is not (necessarily) sorted
				// but the final list will be sorted later, so we don't bother with it
				if (f.isFile()) {
					collectFiles(inputFiles, f, recursively, patternFragments);
				} else {
					if (recursively) {
						collectFiles(inputFiles, f, recursively, patternFragments);
					}
				}
			}
		} else {
			if ((patternFragments != null && matches(file.getName(), patternFragments))
					|| (patternFragments == null && file.getName().endsWith(".java"))) {
				if (OptionParser.wrappedMode) {
					if (IN_COLUMBUS_REGTEST) {
						inputFiles.add(file);
					} else {
						try {
							inputFiles.add(file.getCanonicalFile());
						} catch (IOException e) {
							logger.error("error.jan.FileCollector.couldntDetermineCanonicalPath", file, e);
							inputFiles.add(file.getAbsoluteFile());
						}
					}
				} else {
					inputFiles.add(file);
				}
			}
		}
	}

	private static boolean matches(String str, String[] patternFragments) {
		int startpos = 0;
		for (String fragment : patternFragments) {
			if ((startpos = str.indexOf(fragment, startpos)) != -1) {
				startpos += fragment.length();
			} else {
				return false;
			}
		}
		return true;
	}

}
