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

package com.columbus.maven.plugins.tools;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.Closeable;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintStream;
import java.io.Reader;
import java.util.HashSet;
import java.util.Set;
import java.util.TreeSet;

public class ListFileManager {

  private Set<String> items;

  public ListFileManager() {
    items = new TreeSet<String>();
  }

  public void clear() {
    items.clear();
  }

  public void append(String inputLine) throws IOException {
    items.add(inputLine);
  }
  
  public void append(File inputfile) throws IOException {
    BufferedReader inputFileReader = null;
    try {
      inputFileReader = new BufferedReader(new FileReader(inputfile));
      String line;
      while ((line = inputFileReader.readLine()) != null) {
        // Deal with the line
        items.add(line);
      }

    } catch (FileNotFoundException e) {
      e.printStackTrace();
      throw e;
    } catch (IOException e) {
      e.printStackTrace();
      throw e;
    } finally {
      closeQuietly(inputFileReader);
    }

  }

  public void save(File outputfile) throws FileNotFoundException {
    PrintStream fileStream = null;
    try {
      fileStream = new PrintStream(new FileOutputStream(outputfile));
      for (String line : items) {
        // Deal with the line
        fileStream.println(line);
      }

    } catch (FileNotFoundException e) {
      e.printStackTrace();
      throw e;
    } finally {
      closeQuietly(fileStream);
    }
  }

  public static void closeQuietly(Closeable... closeables) {
    for (Closeable c : closeables) {
      if (c != null)
        try {
          c.close();
        } catch (Exception ex) {
        }
    }
  }
}
