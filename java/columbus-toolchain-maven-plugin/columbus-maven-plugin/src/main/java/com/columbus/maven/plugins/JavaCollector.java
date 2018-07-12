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

package com.columbus.maven.plugins;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.List;

public class JavaCollector {
  /**
   * This function is collect all files in the given with the given extension
   * @param dir      The directory where need to search 
   * @param extension The File extension
   * @return return a list of the found files.
   */
  public static List<File> collectFiles (File dir, String extension ) {
    List<File>  ret = new ArrayList<File>();
    collectFiles (dir,extension,ret);
    return ret;
  }
  
  /**
   * This function is collect all files in the given with the given extension and make the file form the found list.
   * @param dir
   * @param extension
   * @param listFile
   * @throws UnsupportedEncodingException 
   * @throws FileNotFoundException 
   */  
  public static void makeAlistFileFromFiles (File dir, String extension, File listFile ) throws FileNotFoundException, UnsupportedEncodingException {
    List<File>  ret = new ArrayList<File>();
    collectFiles (dir,extension,ret);
    
    PrintWriter writer = new PrintWriter(listFile, "UTF-8");
    
    for (File f:ret){
      if (EnvManager.getInstance().isWindows()) {
        writer.print("\\\\?\\");  
      }
      
      
      writer.println(f.getAbsolutePath());
    }
    
    writer.close();
   
  }
  
  protected static void collectFiles (File dir, String extension,List<File> ret) {
    File[] paths;
    
    try{      
      paths = dir.listFiles();
      if (paths != null) {
        for(File path:paths) {
          if (path.isFile() && path.getName().endsWith(extension)) {
            ret.add(path);
          } else {
            collectFiles(path,extension,ret);
          }
        }
      }
   }catch(Exception e){
      // if any error occurs
      e.printStackTrace();
   }
    
  }
}
