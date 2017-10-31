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

import org.jcolumbus.antwrapper.CopyHelper;
import org.jcolumbus.antwrapper.EnvironmentVariables;

public class Copy extends org.apache.tools.ant.taskdefs.Copy {
	private String superlinkFile;

	// copy single file
	public void execute() {
		String logDir = EnvironmentVariables.WRAPPER_LOG_DIR;
		superlinkFile = logDir + "/superlinklist.txt";

		if (file != null) {
			CopyHelper copyHelper = new CopyHelper(superlinkFile);
			copyHelper.helpSingleCopy(this, new org.apache.tools.ant.taskdefs.Copy(), file, destFile, destDir);
		}
		super.execute();
	}

	// copy fileSet
	// TODO: copy from non-file resources (from ant 1.7)?
	@Override
	protected void scan(File fromDir, File toDir, String[] files, String[] dirs) {
		// called from execute()
		CopyHelper copyHelper = new CopyHelper(superlinkFile);
		String[] allFiles = copyHelper.scan(this, fromDir, toDir, files, this.flatten);
		
		super.scan(fromDir, toDir, allFiles, dirs);
	}

}
