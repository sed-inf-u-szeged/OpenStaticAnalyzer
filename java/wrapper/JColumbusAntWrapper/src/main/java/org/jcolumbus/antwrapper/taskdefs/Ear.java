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

import java.io.File;

import org.apache.tools.ant.BuildException;
import org.apache.tools.ant.types.FileSet;
import org.apache.tools.ant.types.ZipFileSet;
import org.jcolumbus.antwrapper.ZipHelper;

public class Ear extends org.apache.tools.ant.taskdefs.Ear {

	private String inputList;
	private boolean needToLink = false;

	public void execute() {
		ZipHelper.addExcludes(this);

		super.execute();

		// calling the linker
		ZipHelper.link(this, zipFile, needToLink, inputList);
	}

	protected ArchiveState getResourcesToAdd(FileSet[] filesets, File zipFile, boolean needsUpdate)
			throws BuildException {
		ArchiveState state = super.getResourcesToAdd(filesets, zipFile, needsUpdate);
		needToLink = state.isOutOfDate();
		// creating list file for JANLink
		inputList = ZipHelper.writeListFile(this, state, zipFile);
		return state;
	}

	@Override
	public void addFileset(FileSet set) {
		ZipHelper.addExcludes(set);
		super.addFileset(set);
	}

	@Override
	public void addZipfileset(ZipFileSet set) {
		ZipHelper.addExcludes(set);
		super.addZipfileset(set);
	}

	@Override
	public void addZipGroupFileset(FileSet set) {
		ZipHelper.addExcludes(set);
		super.addZipGroupFileset(set);
	}

	@Override
	public void addMetainf(ZipFileSet set) {
		ZipHelper.addExcludes(set);
		super.addMetainf(set);
	}

	@Override
	public void addArchives(ZipFileSet set) {
		ZipHelper.addExcludes(set);
		super.addArchives(set);
	}

}
