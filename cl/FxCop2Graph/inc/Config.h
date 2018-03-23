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

#ifndef _CONFIG_H
#define _CONFIG_H

#define PROGRAM_NAME "FxCop2Graph"
#define EXECUTABLE_NAME "FxCop2Graph"

#include <iostream>

using namespace std;

namespace columbus {
	namespace fxcop2graph {
		struct Config {

			Config() : makerul(false){}

			bool makerul;
			string outTxt;
			string outGraph;
			string rulFile;
			string rulConfig;
			string limFile;
			bool exportRul;
			string statFile;
			string inputFile;
			string changepathfrom;
			string changepathto;
			string messagesXML;
			string findbugsXML;
			string rulesXML;
			string pathDir;
		};
	}
}

#endif