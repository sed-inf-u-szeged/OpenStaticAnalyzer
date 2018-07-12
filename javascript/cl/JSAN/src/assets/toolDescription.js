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

module.exports.banner = 
  "  _  ___  ___  _ _   \n" +
  " | |/ __>| . || \\ | \n" +
  "_| |\\__ \\|   ||   |\n" +
  "\\__/<___/|_|_||_\\_|\n";

module.exports.header = 'JSAN - JavaScript Static Code Analyzer';
module.exports.description = 'A JavaScript Static Analyzer that uses espree in its core to create an AST. Comment attaching, cross references are handled inside. It also transforms the ast into a OpenStaticAnalyzer-style AST.'