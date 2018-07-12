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

import java.util.List;

import com.lexicalscope.jewel.cli.CommandLineInterface;
import com.lexicalscope.jewel.cli.Option;

@CommandLineInterface(application = "JAN")
public interface JANCmdLine {

	@Option(shortName = "i", description = "The input file(s) or directory(ies)")
	List<String> getInput();
	boolean isInput();

	@Option(shortName = "a", description = "JAN options.")
	String getJanoptions();
	boolean isJanoptions();

	@Option(shortName = "d", description = "The output directory for .jsi classes.")
	String getOutputdir();
	boolean isOutputdir();

	@Option(shortName = "e", description = "The output directory for extra .jsi file.")
	String getExtrajsidir();
	boolean isExtrajsidir();

	@Option(shortName = "o", description = "The output .jsi file.")
	String getOutputjsi();
	boolean isOutputjsi();

	@Option(shortName = "x", description = "The output .xml file.")
	String getOutputxml();
	boolean isOutputxml();

	@Option(shortName = "j", description = "The extra arguments for javac.")
	String getJavacoptions();
	boolean isJavacoptions();

	@Option(shortName = "c", description = "The config.ini file.")
	String getConfigfile();
	boolean isConfigfile();

	@Option(shortName = "l", description = "The name of the jsi list file.")
	String getJsilistfile();
	boolean isJsilistfile();

	@Option(shortName = "f", description = "Javac Argument files")
	List<String> getJavacargumentfiles();
	boolean isJavacargumentfiles();

	@Option(shortName = "s", description = "The name of the source list file")
	String getAnalyzedsourcelist();
	boolean isAnalyzedsourcelist();
	
	@Option(shortName = "u", description = "The name of the classpath list file")
	String getUsedclasspathlist();
	boolean isUsedclasspathlist();

	@Option(shortName = "t", description = "The path of the statistic file.")
	String getStatisticfile();
	boolean isStatisticfile();

	@Option(shortName = "w", description = "The path of the current working directory.")
	String getWorkingdirectory();
	boolean isWorkingdirectory();

	@Option(shortName = "p", hidden = true, description = "Don't set it manually")
	boolean isWrappedmode();
	
	@Option(shortName = "r", hidden = true, description = "Don't set it manually")
	boolean isDirecotryAnalyzeMode();
	
	@Option(shortName = "g", hidden = true, description = "Don't set it manually")
	boolean isDevelopermode();

	@Option(shortName = "h", description = "The path of the hard filter file.")
	String getHardfilter();
	boolean isHardfilter();

	@Option(shortName = "v", description = "Print version informations.")
	boolean isVersion();
	
	@Option(shortName = "m", description = "The log level from 0 to 3, ( silent, error, warn, info).")
	int getMessagelevel();
	boolean isMessagelevel();

}
