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

package org.jcolumbus.antwrapper.compilers;

import org.apache.tools.ant.BuildException;
import org.apache.tools.ant.taskdefs.Javac;
import org.apache.tools.ant.taskdefs.compilers.DefaultCompilerAdapter;
import org.apache.tools.ant.types.Commandline;

public class MyCompilerAdapter extends DefaultCompilerAdapter {

	public MyCompilerAdapter(Javac javac) {
		this.attributes = javac;
		setJavac(attributes);
	}

	public String[] createJavacArgumentArray() {
		Commandline args = new Commandline();
		setupModernJavacCommandlineSwitches(args);
		return args.getArguments();
	}

	public String[] createJavacInputArray() {
		Commandline inputs = new Commandline();
		logAndAddFilesToCompile(inputs);
		return inputs.getArguments();
	}

	@Override
	public boolean execute() throws BuildException {
		return false;
	}

}
