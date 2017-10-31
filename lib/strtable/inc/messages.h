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

#ifndef _STRTABLE_M_H_
#define _STRTABLE_M_H_

#define CMSG_BUCKET_IS_FULL                           common::WriteMsg::mlError, "Error: StrTable: Bucket (%d) is full\n"
#define CMSG_WRONG_FILE_FORMAT                        common::WriteMsg::mlError, "Error: StrTable::load(): Wrong file format\n"
#define CMSG_LOAD_ERROR                               common::WriteMsg::mlError, "Error: StrTable::load(): Memory allocation error\n"
#define CMSG_ERROR_MEMORY_ALLOCATION                  common::WriteMsg::mlError, "Error: StrTable: Memory allocation error\n"
#define CMSG_READ_ERR                                                            "Error: StrTable::load(): Error while reading\n"
#define CMSG_WRITE_ERR                                                           "Error: StrTable::save(): Error while writing\n"
#define CMSG_BUCKET_TOTAL_NUMBER                      common::WriteMsg::mlNormal,"Bucket:%u (total number:%zu)\n"
#define CMSG_TOTAL_COUNT                              common::WriteMsg::mlNormal,"Total Count: %zu\n"

#endif
