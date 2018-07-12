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

#ifndef __ERRORCODES_H
#define __ERRORCODES_H

namespace common
{

enum ErrorCode
{
  // CAN
  retOk                    =  0,  // OK
  retAnalyzerError         =  1,  // Error during analysis
  retFileError             =  2,  // File system error
  retBadArgError           =  3,  // Bad command-line arguments

  // ASG
  dumpOK                   = 10,
  dumpError,
  retIncorrectCSIVersion,
  retCSIOpenError,
  retCSILoadError,

  // CANLink
  retStringTableOpenError  = 20,
  retStringTableLoadError,
  retStringTableLoadOK,
  retASGLoadError,
  retASGLoadWarning,
  retASGLoadOK,
  retASGSaveError,
  retASGSaveOK,
  retLinkingError,
  retLinkingOK,
  retOutOfMemoryError,

  // columbus::cpp
  retColumbusException     = 50,  // General columbus::cpp exception

  // Other
  retLicenceError          = 99,  // Bad or missing licence file
  retOtherError                   // Unspecified error
}; 

};

#endif /* __ERRORCODES_H */
