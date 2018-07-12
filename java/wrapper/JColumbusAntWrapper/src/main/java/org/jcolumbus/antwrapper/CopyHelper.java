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

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.HashSet;
import java.util.Set;

import org.apache.tools.ant.taskdefs.Copy;
import org.apache.tools.ant.taskdefs.Move;

import columbus.logger.LoggerHandler;

public class CopyHelper {

	private static final LoggerHandler logger = new LoggerHandler(CopyHelper.class, Options.messagesFile);

	private String superlinkFile;
	private PrintWriter superlinkWriter;
	private String columbusResultDir = Options.columbusResultDir;

	public CopyHelper(String superlinkFile) {
		super();
		this.superlinkFile = superlinkFile;
	}

	public String[] scan(Copy copy, File fromDir, File toDir, String[] files, boolean flatten) {
		logger.debug("debug.antwrapper.CopyHelper.copyList", fromDir, toDir);
		Set<String> allFiles = new HashSet<String>(files.length * 2);
		try {
			openWriter();
			// the name of the file, created by the toolchain
			String newFileName;
			for (String fileName : files) {
				allFiles.add(fileName); // add original
				newFileName = Util.replaceExtensionAndAddPlusDir(fileName, null);
				if (newFileName != null && new File(fromDir, newFileName).exists()) { // add jsi/ljsi if exists
					allFiles.add(newFileName);
					if (fromDir == null) {
						// fromDir is null when copying files from resource collections and these files are given with
						// absolute paths
						newFileName = newFileName.substring(newFileName.lastIndexOf(File.separator) + 1);
					}
					String oldFileName = newFileName;
					if (fromDir != null) {
						oldFileName = fromDir.getAbsolutePath() + File.separator + newFileName;
					}
					// if flatten is true, we dont need the .columbus directory at the and of the destination path
					if (flatten) {
						newFileName = Util.replaceExtension(fileName);
					}
					appendFileName(oldFileName, toDir.getPath() + File.separator + newFileName, copy);
				}
			}
		} catch (IOException e) {
			logger.error("error.antwrapper.CopyHelper.errorCopyingFile", e);
		} catch (Exception e) {
			logger.error("error.antwrapper.CopyHelper.printEx", e);
		} finally {
			closeWriter();
		}
		if (logger.isDebugEnabled()) {
			for (String s : allFiles) {
				logger.debug("debug.antwrapper.CopyHelper.copyEntry", s);
			}
		}
		return allFiles.toArray(new String[allFiles.size()]);
	}

	public void helpSingleCopy(Copy copy, Copy newCopy, File file, File destFile, File destDir) {
		// newCopy can be Copy or Move (extends Copy)
		try {
			openWriter();
			String originalColumbusFile = Util.replaceExtensionAndAddPlusDir(file.getPath(), null);
			File newSrc;
			// copy/move jsi/ljsi if exists
			if (originalColumbusFile != null && (newSrc = new File(originalColumbusFile)).exists()) {
				newCopy.setFile(newSrc);
				newCopy.setProject(copy.getProject());
				newCopy.setTaskName("copy " + newSrc.getName());
				if (destFile != null) {
					// if toDir is empty and toFile is set
					String newDestFile = Util.replaceExtensionAndAddPlusDir(destFile.getPath(), null);
					if (newDestFile != null) { // copy only if the original target file has a replaceable extension
												// TODO: copy always?
						newCopy.setTofile(new File(newDestFile));
						newCopy.execute();

						appendFileName(newSrc.getAbsolutePath(), newDestFile, copy);
					}
				} else {
					// if toDir is set and toFile is empty
					String dest = Util.addDirToPath(destDir.getAbsolutePath(), columbusResultDir, true, null);
					newCopy.setTodir(new File(dest));
					newCopy.setFlatten(false);
					newCopy.execute();
					// a dest-ben van az uj utvonal, csak a columbus file neve kell plusszban
					appendFileName(originalColumbusFile, dest + File.separator + newSrc.getName(), copy);
				}
			}
		} catch (IOException e) {
			logger.error("error.antwrapper.CopyHelper.errorCopyingFile", e);
		} catch (Exception e) {
			logger.error("error.antwrapper.CopyHelper.printEx", e);
		} finally {
			closeWriter();
		}
	}

	private void appendFileName(String oldFileName, String fileName, Copy copy) throws IOException {
		if (!fileName.endsWith(".jsi")) {
			if (copy instanceof Move) {
				Util.reWriteListFile(superlinkFile, oldFileName, fileName);
			} else {
				logger.debug("debug.antwrapper.CopyHelper.addSuperlinklist", fileName);
				superlinkWriter.println(fileName);
			} // only add ljsi
		}
	}

	private void openWriter() throws IOException {
		superlinkWriter = new PrintWriter(new BufferedWriter(new FileWriter(superlinkFile, true)));
	}

	private void closeWriter() {
		if (superlinkWriter != null) {
			superlinkWriter.close();
		}
	}
}
