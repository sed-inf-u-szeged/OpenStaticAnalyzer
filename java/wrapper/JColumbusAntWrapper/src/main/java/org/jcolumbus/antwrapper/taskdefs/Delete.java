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

package org.jcolumbus.antwrapper.taskdefs;

import java.io.File;
import java.io.IOException;

import org.apache.tools.ant.BuildException;
import org.apache.tools.ant.DirectoryScanner;
import org.apache.tools.ant.types.FileSet;
import org.jcolumbus.antwrapper.EnvironmentVariables;
import org.jcolumbus.antwrapper.Options;
import org.jcolumbus.antwrapper.Util;

import columbus.logger.LoggerHandler;

public class Delete extends org.apache.tools.ant.taskdefs.Delete {
	
	private static final LoggerHandler logger = new LoggerHandler(Delete.class, Options.messagesFile);

	String superlinkFile = EnvironmentVariables.WRAPPER_LOG_DIR + "/superlinklist.txt";

	@Override
	public void execute() throws BuildException {
		try {
			if (file != null) {
				logger.debug("debug.antwrapper.Delete.deleteFile", file.getAbsolutePath());
				if (file.exists() && file.isFile()) {
					deleteFile(file);
				}
			}

			if (dir != null) {
				if (dir.exists() && dir.isDirectory()) {
					logger.debug("debug.antwrapper.Delete.deleteDir", dir.getAbsolutePath());
					deleteDir(dir);
				}
			}

			for (int i = 0; i < filesets.size(); i++) {
				try {
					FileSet fs = (FileSet) filesets.get(i);
					DirectoryScanner ds = fs.getDirectoryScanner(getProject());
					final String[] files = ds.getIncludedFiles();
					final String[] dirs = ds.getIncludedDirectories();
					File parentDir = fs.getDir(getProject());

					for (String s : files) {
						File f = new File(parentDir, s);
						if (f.exists()) {
							deleteFile(f);
						}
					}
					for (String d : dirs) {
						File f = new File(parentDir, d);
						if (f.exists()) {
							deleteDir(f);
						}
					}
				} catch (BuildException e) {
					logger.error("error.antwrapper.Delete.printEx", e);
				}

			}

		} catch (IOException e) {
			logger.error("error.antwrapper.Delete.cantModifySuperLinkList", e);
		}

		super.execute();
	}

	// call the proper delete function to all files in a dir
	private void deleteDir(File dir) throws IOException {
		String[] list = dir.list();
		if (list == null) {
			list = new String[0];
		}
		for (int i = 0; i < list.length; i++) {
			String s = list[i];
			File f = new File(dir, s);
			if (f.isDirectory()) {
				deleteDir(f);
			} else {
				deleteFile(f);
			}
		}
	}

	// create the columbus file from the original file and delete it
	private void deleteFile(File file) throws IOException {
		try {
			String columbusFile = null;
			if ((columbusFile = Util.replaceExtensionAndAddPlusDir(file.getAbsolutePath(), null)) != null) {
				File f = new File(columbusFile);
				logger.debug("debug.antwrapper.Delete.deleteColumbusFile", f.getAbsolutePath());
				if (f.delete()) {
					if (columbusFile.endsWith("ljsi") && (new File(superlinkFile)).exists()) {
						Util.reWriteListFile(superlinkFile, columbusFile, "");
					}
				} else {
					if (f.exists()) {
						logger.warn("warn.antwrapper.Delete.cantDeleteFile", f.getAbsolutePath());
					}
				}
			}
		} catch (Exception e) {
			logger.error("error.antwrapper.Delete.printEx", e);
		}
	}
}
