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

import java.io.File;
import java.io.FileNotFoundException;
import java.nio.charset.Charset;
import java.util.Scanner;
import java.util.TreeSet;

/**
 * A class which contains methods to process a file and search it for useful lines.
 */
public class FileProcessor {
    private Scanner scanner;
    
    /**
     * @param filePath The path to the file.
     * @return A TreeSet, which contains the line indexes of non-empty and non-comment lines.
     */
    public TreeSet<Integer> processFile(String filePath) {
        File file = new File(filePath);
        Charset encoding = OptionParser.encoding == null ? Charset.defaultCharset() : Charset.forName(OptionParser.encoding);
        
        try {
            scanner = new Scanner(file, encoding.name());
            return searchForLogicalLines(scanner);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        return new TreeSet<>();
    }

    private TreeSet<Integer> searchForLogicalLines(Scanner scanner) {
        TreeSet<Integer> lines = new TreeSet<>();
        int lineIndex = 0;
        boolean[] response = {false, false};
        String line;

        while(scanner.hasNextLine()) {
            line = scanner.nextLine().trim();
            lineIndex++;

            response = processLine(line, response[1]);
            
            if (response[0]) {
                lines.add(lineIndex);
            }
        }

        return lines;
    }

    /**
     * @param line The line to process.
     * @param multi True, if the processing is a multi line comment.
     * @return a boolean array with two values: the first is true, if the line is useful, the second is true, if the processing continues in a multi line comment.
     */
    private boolean[] processLine(String line, boolean multi) {
        /*
         * A boolean array to return two boolean values.
         * 0. The value, which says whether the line is a useful line for LLOC.
         * 1. This says, whether the processing is in a multi line comment. The method will get it back as a parameter on the next call.
         */
        boolean[] responseArray = new boolean[] {false, false};

        if (multi) {
            if (line.contains("*/")) {
                int boundIndex = findInString(line, new char[]{'*', '/'}, true);

                if (boundIndex != -1) {
                    if (boundIndex < line.length() - 2) {
                        line = line.substring(boundIndex + 2).trim();
                    } else {
                        line = "";
                    }
                }
            } else {
                responseArray[1] = true;
                return responseArray;
            }
        }
        
        if (line.isEmpty()) {
            return responseArray;
        } else if (line.length() == 1) {
        	//In this case this line should be a useful one.
        	responseArray[0] = true;
        } else {
	        if (line.charAt(0) == '/') {
	            if (line.charAt(1) == '/') {
	                //It is a simple line comment. The whole line is a comment line.
	                return responseArray;
	            } else if (line.charAt(1) == '*') {
	                //This is the start of a multi line comment. Actually it could be a multi line comment in one line.
	                String l = line.substring(1);
	
	                if (l.contains("*/")) {
	                    int boundIndex = findInString(line, new char[]{'*', '/'}, true);
	
	                    if (boundIndex != -1) {
	                        if (boundIndex < line.length() - 2) {
	                            line = line.substring(boundIndex + 2).trim();
	                            responseArray = processLine(line, false);
	                        }
	                    }
	                } else {
	                    responseArray[1] = true;
	                }
	            }
	        } else if (line.contains("/*")) {
	            boolean r = findMultiLineComments(line, new char[]{'/', '*'}, false);
	            responseArray[1] = r;
	            responseArray[0] = true;
	        } else {
	            responseArray[0] = true;
	        }
        }

        return responseArray;
    }

    /**
     * @param line the line (practically a string) to process
     * @param bound the bound character to search for. It should be either {/, *} or {*, /}
     * @param findClosingTag If true, the method will stop when it founds the first match for the bounds. It is used to find the closing tag of the comment.
     * @return true, if the processing is in a multi line comment, otherwise false.
     */
    private boolean findMultiLineComments(String line, char[] bound, boolean findClosingTag) {
        boolean result = false;
        int commentBound = findInString(line, bound, findClosingTag);

        if (commentBound != -1) {
            String subLine = line.substring(commentBound + 2).trim();
            //Switch the places of the char array and create a string to use in String.contains().
            String boundToLookFor = String.copyValueOf(new char[]{bound[1], bound[0]});

            if (!subLine.isEmpty() && subLine.contains(boundToLookFor)) {
                //The program stores the return value here, but doesn't use it later.
                @SuppressWarnings("unused")
                boolean returnValue = findMultiLineComments(subLine, new char[]{bound[1], bound[0]}, !findClosingTag);
            } else if (!findClosingTag) {
                result = true;
            }
        }

        return result;
    }

    /**
     * @param line the line (practically a string) to process.
     * @param bound the bound character to search for. It should be either or {'/','*'} or {'*', '/'}.
     * @param findClosingTag If true, the method will stop when it founds the first match for the bounds. It is used to find the closing tag of the comment.
     * @return The index of the bound if the program finds it, -1 otherwise.
     */
    private int findInString(String line, char[] bound, boolean findClosingTag) {
        int commentBound = -1;
        boolean inString = false;
        char[] cLine = line.toCharArray();

        for (int i = 0; i < line.length(); i++) {
            if (cLine[i] == '\"') {
                if (i > 0 && cLine[i - 1] == '\\') { //Escaped " doesn't count.
                    continue;
                }

                inString = !inString;
            }

            if (inString) {
                continue;
            }

            //When the program flips the inString value to be false, this condition will run althought it is not needed.
            if (cLine[i] == bound[0] && (i < line.length() - 1) && cLine[i + 1] == bound[1]) {
                commentBound = i;

                if (findClosingTag) {
                    break;
                }
            }
        }

        return commentBound;
    }
}
