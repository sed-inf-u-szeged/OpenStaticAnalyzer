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

#ifndef _DCF_M_H_
#define _DCF_M_H_

// error
#define CMSG_SIMPLE_STRING_TRANSMIT_ERR         common::WriteMsg::mlError, "%s\n"
#define CMSG_NO_INPUT_FILES                     common::WriteMsg::mlError, "Error: No input file\n"
#define CMSG_NO_INPUT_LIM_FILE                  common::WriteMsg::mlError, "Error: No input lim file\n"
#define CMSG_FAILED_OPEN_FILE                   common::WriteMsg::mlError, "Error: Cannot open file: \"%s\""
#define CMSG_NO_INFO_FOR_FILE                   common::WriteMsg::mlError, "The information form the %s component is missing in the %s file.\n"
#define CMSG_NO_COMPONET_FILE                   common::WriteMsg::mlError, "The the file of %s component is missing \n"
#define CMSG_DIFFERENT_NODEKINDS                common::WriteMsg::mlError, "Error: Clone position object is a method, but LIM node is not. [%s:%d]\n"
#define CMSG_NO_FILE_FOR_THE_CLONE              common::WriteMsg::mlError, "Error: No file is found for a clone instance (%u)\n"
#define CMSG_TOO_MANY_FILES_FOR_THE_CLONE       common::WriteMsg::mlError, "Error: Too many files are found for a clone instance (%u)\n"

// warning
#define CMSG_GENALOGY_WILL_NOT_BE_SAVED         common::WriteMsg::mlWarning, "%s\n Warning: Genalogy will not be saved!\n" 
#define CMSG_ERROR_IN_SERIALIZED_ASG_SEQUENCE   common::WriteMsg::mlWarning, "Warning: Missing end sequence of the node %d\n"
#define CMSG_FILTER_FILE_CANNOT_BE_LOADED       common::WriteMsg::mlWarning, "Warning: Filter file cannot be loaded: \"%s\"\n"
#define CMSG_FILTER_FILE_OLD                    common::WriteMsg::mlWarning, "Warning: Filter file (%s) is older than the input file. Filter file is not used.\n"
#define CMSG_NOT_ENOUGH_MEMORY_TO_EVOLUTE       common::WriteMsg::mlWarning, "Warning: Not enough memory to find all previous version of clone instances.\n"
#define CMSG_FILENAME_COMPONENT_MATCH           common::WriteMsg::mlWarning, "Warning: Component has found with filename only! (%s)\n"
#define CMSG_ADDING_PATH_TO_FILTER              common::WriteMsg::mlWarning, "Warning: Clone detection in file (%s) need to be skiped due to it seems to contain too much clones. (Probably a generated file.)\n"
#define CMSG_NO_COMPILATION_UNIT_FOUND          common::WriteMsg::mlWarning, "Warning: Can't find compilation unit file: %s\n"

// normal
#define CMSG_GENERATING_CLONE_INSTANCES         common::WriteMsg::mlNormal, "Generating clone instances...\n"

#define CMSG_FAILED                             common::WriteMsg::mlNormal, "Failed\n"
#define CMSG_DONE_N                             common::WriteMsg::mlNormal, "Done\n"
#define CMSG_USE_PATTERNFILTER                  common::WriteMsg::mlNormal, "Using patternFilter...\n"
#define CMSG_DETECTING_CLONES                   common::WriteMsg::mlNormal, "Detecting clones...\n"
#define CMSG_APPLYING_FILTERS                   common::WriteMsg::mlNormal, "Applying filters...\n"
#define CMSG_BUILD_CLONE_TREE                   common::WriteMsg::mlNormal, "Building clone tree...\n"
#define CMSG_LOADING                            common::WriteMsg::mlNormal, "Loading: %s\n"
#define CMSG_LOADING_AND_PERCENTAGE             common::WriteMsg::mlNormal, "Loading (%.2f): %s\n"
#define CMSG_INITIALIZING_LIM                   common::WriteMsg::mlNormal, "Initializing lim...\n"
#define CMSG_STATISTICS                         common::WriteMsg::mlNormal, "\nStatistics:\n"
#define CMSG_DETECTING_TIME                     common::WriteMsg::mlNormal, "\tDetection time      :%lu 1/100sec\n"
#define CMSG_PEAK_MEMORY_USAGE                  common::WriteMsg::mlNormal, "\tPeak memory usage   :%lu MByte\n"
#define CMSG_COMPUTING_COVERED_NODES            common::WriteMsg::mlNormal, "Computing clone coverage...\n"
#define CMSG_START_FINALIZING                   common::WriteMsg::mlNormal, "Finalizing...\n"
#define CMSG_START_EVOLUTION_MAPPING            common::WriteMsg::mlNormal, "Evolution mapping...\n"

// debug
#define CMSG_RUL_FILE_NOT_SET                   common::WriteMsg::mlDebug, "Debug: .rul file not specified. \"%s\" is used.\n"
#define CMSG_RUL_FILE_FOUND                     common::WriteMsg::mlDebug, "Debug: .rul file found: \"%s\"\n"
#define CMSG_FILTERED_OUT                       common::WriteMsg::mlDebug, "Debug: File filtered out: %s\n"
#define CMSG_THE_LIM_INPUT_FILE                 common::WriteMsg::mlDebug, "Debug: The LIM input file: \"%s\"\n"
#define CMSG_LINE_INFO_CASE                     common::WriteMsg::mlDebug, "Debug: Line info capitalization: %s\n"

#define CMSG_PROBALBLY_CLONES_FOUND             common::WriteMsg::mlDebug,"Debug: Probalbly clones found done. Building instances\n"
#define CMSG_LOAD_ASG_DONE                      common::WriteMsg::mlDebug,"Debug: Loading of the ASG is done"
#define CMSG_CONVERTING_TO_GRAPH                common::WriteMsg::mlDebug,"Debug: Converting to graph\n"
#define CMSG_BUILD_CE                           common::WriteMsg::mlDebug, "Debug: The CE cache"
#define CMSG_CLONE_INSTANCE                     common::WriteMsg::mlDDDDebug,"Debug: CloneInstance%d:\n"
#define CMSG_SD_ON                              common::WriteMsg::mlDDDDebug,"%s(%d) on %d %d %s ,%d\n"
#define CMSG_CURRENT_COMPONENT_ID               common::WriteMsg::mlDebug, "Debug: The ID of the current component node in LIM:%d\n"

#define CMSG_LINE_INFO_CASE_LOWERED             "lower case" 
#define CMSG_LINE_INFO_CASE_DEFAULT             "default case"
#define CMSG_MINIMUM_NUMBER_OF_LINES            common::WriteMsg::mlDebug, "Debug: The minimum lines of clones: %d\n"
#define CMSG_MINIMUM_NUMBER_OF_ASG_NODES        common::WriteMsg::mlDebug, "Debug: The minimum ASG nodes of clones: %d\n"
#define CMSG_MAXIMUM_PATTERN_SIZE               common::WriteMsg::mlDebug, "Debug: Maximum of the single pattern size: %d\n"
#define CMSG_MINIMUM_PATTERN_FULL_LENGTH        common::WriteMsg::mlDebug, "Debug: Minimum of the full length of the repeating pattern: %d\n"
#define CMSG_DETECTING_CODE_DUPLICATIONS        common::WriteMsg::mlDebug, "Debug: Detecting code duplications\n"
#define CMSG_FILTER_RESULT_REDIRECTED_TO_STANDARD_OUT   common::WriteMsg::mlDebug, "Debug: Filter result redirected to standard out\n"
#define CMSG_FILTER_RESULT_REDIRECTED_INTO_FILE common::WriteMsg::mlDebug, "Debug: Filter result redirected into file: \"%s\" \n"
#define CMSG_DUMPING_OUTPUT_TO_FILE             common::WriteMsg::mlDebug, "Debug: Dumping output to file: \"%s\"\n"
#define CMSG_DUMPING_OUTPUT_TO_STANDARD_OUTPUT  common::WriteMsg::mlDebug, "Debug: Dumping output to standard out\n"
#define CMSG_DONE_D                             common::WriteMsg::mlDebug, "Debug: Done\n"
#define CMSG_DONE_IN                            common::WriteMsg::mlDebug, "Debug: Done in %lu (1/100sec)\n"
#define CMSG_NEED_TO_SKIP                       common::WriteMsg::mlDebug, "Debug: Need to skip:%s\n"
#define CMSG_NODE_FILTERED_OUT                  common::WriteMsg::mlDebug, "Debug: %lu node(s) were filtered out\n"
#define CMSG_CLONE_DETECTION_DONE_IN            common::WriteMsg::mlDebug, "Debug: Clone detection done in %lu (1/100sec)\n"
#define CMSG_MEM_USED                           common::WriteMsg::mlDebug, "Debug: Mem used:%lu (MByte) \n"
#define CMSG_FINALIZE_DONE_IN                   common::WriteMsg::mlDebug, "Debug: Finalization is done in %lu (1/100sec)\n"
#define CMSG_CLONE_VISITOR_RUNNING              common::WriteMsg::mlDebug, "Debug: Clone visitor running...\n"
#define CMSG_INITIALIZING_GENEALOGY             common::WriteMsg::mlDebug, "Debug: Initializing Genealogy...\n"
#define CMSG_START_CLONE_NAMING                 common::WriteMsg::mlDebug, "Debug: Start clone naming...\n"
#define CMSG_COMPUTING_COVERAGE_AND_GENERATE_GRAPH_FORM_LIM   common::WriteMsg::mlDebug,"Debug: Computing coverage and generate graph from lim...\n"
#define CMSG_COMPUTING_COVERAGE_DONE            common::WriteMsg::mlDebug, "Debug: Coverage calculation is done\n"
#define CMSG_CREATE_BACKUP                      common::WriteMsg::mlDebug, "Debug: Creating backup...\n"
#define CMSG_SAVE_GENEALOGY                     common::WriteMsg::mlDebug, "Debug: Saving genealogy...\n"
#define CMSG_EXPORT_METRICS                     common::WriteMsg::mlDebug, "Debug: Exporting metrics...\n"
#define CMSG_CAUSE                              common::WriteMsg::mlDebug, "Debug: Cause: %s\n"
#define CMSG_INC_CE                             common::WriteMsg::mlDDebug, "Debug: Increasing CE on %d because it is connected to the %d:%d which distance is %d. %s\n"
#define CMSG_INC_CE_ALWAYS                      "It has to be counted always."
#define CMSG_INC_CE_ONCE                        "It has to be counted only once."

#define CMSG_MORE_END_THEN_BEGIN                common::WriteMsg::mlDebug, "Debug: There is a problem with the lim node traversal (more lim node end exist than begin)."
#define CMSG_NODE_NO_POS_CACHE                  common::WriteMsg::mlDebug, "Debug: The %d NodeId is not found in the position cache\n"

// ddd debug
#define CMSG_START_VISIST                       common::WriteMsg::mlDDDDebug, "DDDDebug: START:[%s|%s|%d L:%d] CD:%d AD:%d\n"
#define CMSG_START_EVOLUTION_MAPPING_SYSTEM_SET(PHASE) common::WriteMsg::mlDDDDebug, "DDDDebug: Start evolution mapping ["#PHASE"]...\n"
#define CMSG_ADD_NODE_TO_SEQ                    common::WriteMsg::mlDDDDebug, "DDDDebug: %d node %s [%s:%d ]\n"
#define CMSG_ADD_NODE_TO_SEQ_END                common::WriteMsg::mlDDDDebug, "DDDDebug: %d node end \n"
#define CMSG_FUND_REPEATING_SEQ                 common::WriteMsg::mlDDDDebug, "Found cl on %d to %d :%d\n"
#define CMSG_FUND_REPEATING_SEQ_2               common::WriteMsg::mlDDDDebug, "         on %d to %d\n"
#define CMSG_FUND_REPEATING_SEQ_3               common::WriteMsg::mlDDDDebug, "  create with %d id\n"
#define CMSG_FUND_REPEATING_SEQ_4               common::WriteMsg::mlDDDDebug, "    the instance start %d found align to %d - %d id\n"
#define CMSG_FUND_REPEATING_SEQ_5               common::WriteMsg::mlDDDDebug, "    the interval is to short %d \n"
#define CMSG_FUND_REPEATING_SEQ_6               common::WriteMsg::mlDDDDebug, "    on %d space does not matter.\n"

#define CMSG_SETTING_METRICS_FOR                common::WriteMsg::mlDDDDebug, "Setting metric for: %s(%d):%s\n"
#define CMSG_M_CLONECOVERAGE                    common::WriteMsg::mlDDDDebug, "\tClone coverage (CC): %f\n"
#define CMSG_M_CLONEEMBEDDEDNESS                common::WriteMsg::mlDDDDebug, "\tClone embeddedness (CE): %d\n"


// exception
#define CMSG_EX_UNABLE_TO_DETERMINE_THE_LINE_INFO   "Unable to determine the line info!"
#define CMSG_EX_HASH_CODE_MISMATCH(FNAME)           "Hash code mismatch!(" + FNAME + ")"
#define CMSG_EX_MISSING_COMPONENT_FOR_CI            "Component node is missing for the clone instance!"
#define CMSG_EX_THIS_METHOD_SHOULD_NOT_BE_CALLED    "This method should not be called!"
#define CMSG_EX_NO_COMPILATION_UNIT_FOUND(COMPUNIT) "Can't find compilation unit (" + COMPUNIT + ") in the LIM!"


// other
#define CMSG_OS_RUNNING_CLONE_LENGTH_FILTER     "Running \"Clone length filter\""
#define CMSG_OS_RUNNING_OCCURANCE_FILTER        "Running \"Occurance filter\""
#define CMSG_OS_RUNNING_CROSSING_FILTER         "Running \"Crossing filter\""
#define CMSG_OS_FILTERING_CLONES_WITH_REPEATING_LINES "Filtering clones with repeating lines"

#endif
