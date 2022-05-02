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

#ifndef _UDM_MESSAGES_H_
#define _UDM_MESSAGES_H_

#define CMSG_UDM_NO_FORMULA_EXPRESSION                    WriteMsg::mlWarning, "Warning: The '%s' metric has no 'Formula' setting!\n"
#define CMSG_UDM_NO_FORMULA_TYPE                          WriteMsg::mlWarning, "Warning: The '%s' metric has no 'Type' setting!\n"
#define CMSG_UDM_WRONG_FORMULA_TYPE                       WriteMsg::mlWarning, "Warning: Invalid 'Type' setting inside the '%s' metric (expected 'Float' or 'Integer')!\n"
#define CMSG_UDM_CANT_ADD_VARIABLE                        WriteMsg::mlWarning, "Warning: Cannot add variable '%s' to the variable table!\n"
#define CMSG_UDM_INVALID_ATTRIBUTE                        WriteMsg::mlWarning, "Warning: The '%s' metric at node '%s' is INVALID!\n"
#define CMSG_UDM_NO_CALCULATED_FOR_SETTINGS               WriteMsg::mlWarning, "Warning: The '%s' metric has no 'CalculatedFor' setting!\n"
#define CMSG_UDM_EX_NO_FORMULA_NAME                       "Error: Unnamed metric!\n"
#define CMSG_UDM_EX_WRONG_FORMULA_EXPRESSION              "Error: "+parser.error()+" in the formula of the '"+metricName+"' metric!\n"
#define CMSG_UDM_EX_WRONG_FORMULA_CALCFOR_ATTR            "Error: The '"+metricName+"' formula is not calculable for its 'CalculatedFor' attribute, because its '"+variable+"' dependency has different 'CalculatedFor' attributes!\n"
#define CMSG_UDM_EX_VARIABLE_COULDNT_BE_FOUND             "Error: The variable '"+*varIter+"' in the formula of the '"+metricName+"' metric couldn't be found either in the graph or in other formulas!\n"
#define CMSG_UDM_EX_LOOP_FOUND                            "Error: A loop is found within the metric dependencies: "
#define CMSG_UDM_EX_OCCUPIED_FORMULA_NAME                 "Error: The '"+ruleId+"' metric name is already in the graph!\n"
#define CMSG_UDM_STATISTICS                               WriteMsg::mlNormal, "\nStatistics:\n"
#define CMSG_UDM_READING_TIME                             WriteMsg::mlNormal, "\tReading the inputs          : %10.2fs\n"
#define CMSG_UDM_BUILDING_TIME                            WriteMsg::mlNormal, "\tBuilding dependency         : %10.2fs\n"
#define CMSG_UDM_CALCULATION_TIME                         WriteMsg::mlNormal, "\tCalculating formulas        : %10.2fs\n"
#define CMSG_UDM_EXPORT_TIME                              WriteMsg::mlNormal, "\tExporting graph             : %10.2fs\n"
#define CMSG_UDM_TOTAL_TIME                               WriteMsg::mlNormal, "\tTotal time                  : %10.2fs\n"
#define CMSG_UDM_PEAK_MEMORY                              WriteMsg::mlNormal, "\tPeak memory usage           : %10.2fMB\n"

#define CMSG_UDM_CANT_ADD_FUNCTION                        WriteMsg::mlDebug, "Warning: Cannot add function '%s' to the variable table!\n"
#define CMSG_UDM_INVALID_REC_DEF                          WriteMsg::mlWarning, "Warning: Invalid definition for recursion : '%s' !\n"
#define CMSG_UDM_EX_INVALID_CHILD_TYPE                      "Error: The '"+childType+"' child type is INVALID in '"+metric+"' 'Metric'!\n"
#define CMSG_UDM_EX_WRONG_AGGR_CALCFOR                      "Error: The '"+formula+"' formula's aggregation function is not calculable, because its '"+variable+"' metric has different 'CalculatedFor' attributes than the defined ChildTypes!\n"
#define CMSG_UDM_EX_AGGR_VARIABLE_COULDNT_BE_FOUND        "Error: The variable '"+reqMetric+"' from an aggregate function in the '"+metricName+"' metric couldn't be found either in the graph or in other formulas!\n"


#endif
