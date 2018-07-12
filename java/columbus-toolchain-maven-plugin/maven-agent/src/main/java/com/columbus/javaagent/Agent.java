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

package com.columbus.javaagent;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.lang.instrument.Instrumentation;
import java.util.ArrayList;
import java.util.Map;

public class Agent {

  private static final String PLUGIN_PREFIX = "OpenStaticAnalyzer";
  private static final String OSA_LOG_DIR = "OSA_LOG_DIR";
  private static final String COLUMBUS_JAVA_TOOLCHAIN_WRAPPER_BATCH = "OSA_WRAPPER_BATCH";
  public static void premain(String agentArgs, Instrumentation inst) {

    // registers the transformer
    inst.addTransformer(new SleepingClassFileTransformer());
  }

  static private String getMvnBin() {
    if (System.getProperty("os.name").startsWith("Windows")) {
      return "mvn.bat";
    } else {
      return "mvn";
    }
  }

  enum  PhasesLevel {
    NOTHING,
    COMPILE,
    PACKAGE,
    INSTALL,
    DEPLOY
  }
  static private PhasesLevel phasesLevel = PhasesLevel.NOTHING;
  
  
  
  static public int execMaven(String arg, File logPath, String logName,
                              String wokrDir ,String pomFile) {
    ArrayList<String> cmd = new ArrayList<String>();
    cmd.add(getMvnBin());
    cmd.add(arg);

    if (pomFile != null) {
      cmd.add("-f");
      cmd.add(pomFile);
    }
    
    cmd.add("-DtimeFlagFile="
        + System.getenv(COLUMBUS_JAVA_TOOLCHAIN_WRAPPER_BATCH));
    if ( System.getenv(OSA_LOG_DIR) != null ) {
      logPath = new File(System.getenv(OSA_LOG_DIR),"wrapper.log") ;
    } else {
      logPath = new File(logPath,logName) ;
    }
    
    cmd.add("-DnoExportGraph");

    ProcessBuilder pb = new ProcessBuilder(cmd);
    Map<String, String> env = pb.environment();
    env.remove("MAVEN_OPTS");
    env.put("MAVEN_OPTS", "");

    pb.redirectErrorStream(true);
    if (wokrDir != null) {
      pb.directory(new File(wokrDir));
    }
    PrintWriter writer = null;
    Process p;
    try {
      String line;
      p = pb.start();
      BufferedReader input = new BufferedReader(new InputStreamReader(p.getInputStream()));

      try {
        logPath.getParentFile().mkdirs();
        writer = new PrintWriter(new FileOutputStream(
            logPath, 
            true /* append = true */));

        for (String s : cmd) {
          writer.print(s + " ");
        }

        writer.println();
        writer.println();
      } catch (FileNotFoundException e) {
        e.printStackTrace();
        writer = null;
      }

      while ((line = input.readLine()) != null) {
        writer.println(line);

      }
      int retCode = p.waitFor();

      if (writer != null) {
        writer.close();
      }
      return retCode;
    } catch (IOException e) {
      e.printStackTrace();
    } catch (InterruptedException e) {
      e.printStackTrace();
    }

    return -1;
  }
  
  
  public static void executeMavenHook(String baseDirectory, String pom ) {
    if (phasesLevel == PhasesLevel.NOTHING) {
      System.out.println("It nothing to do.");
    }
    
    if (phasesLevel == PhasesLevel.COMPILE) {
      execMaven(PLUGIN_PREFIX+":compile",
                new File(baseDirectory),
                "columbus_compile_wrap",
                baseDirectory, pom);

      execMaven(PLUGIN_PREFIX+":pmd",
                new File(baseDirectory),
                "columbus_compile_wrap_pmd",
                baseDirectory, pom);
    }

    if (phasesLevel == PhasesLevel.PACKAGE) {
      execMaven(PLUGIN_PREFIX+":link",
          new File(baseDirectory),
                "columbus_compile_wrap_link",
                baseDirectory, pom);
    }

    if (phasesLevel == PhasesLevel.INSTALL) {
      execMaven(PLUGIN_PREFIX+":install",
          new File(baseDirectory),
                "columbus_compile_wrap_install",
                baseDirectory, pom);
    }

    if (phasesLevel == PhasesLevel.DEPLOY) {
      execMaven(PLUGIN_PREFIX+":deploy",
          new File(baseDirectory),
                "columbus_compile_wrap_deploy",
                baseDirectory, pom);
    }
  }

  public static void runTask(String taskName, File targetPath, String workPath) {
    System.out.println("The request to run " + taskName + "has been received.");
    if (  taskName.contentEquals("compile") 
        && phasesLevel == PhasesLevel.NOTHING) {
      
      phasesLevel = PhasesLevel.COMPILE;
      
    }

    if (taskName.contentEquals("link")
        && (    phasesLevel == PhasesLevel.NOTHING
             || phasesLevel == PhasesLevel.COMPILE
           )
        ) {
      phasesLevel = PhasesLevel.PACKAGE;
    }

    if (taskName.contentEquals("install")
        && (    phasesLevel == PhasesLevel.NOTHING
        || phasesLevel == PhasesLevel.COMPILE
        || phasesLevel == PhasesLevel.PACKAGE
      )
   ) {
      phasesLevel = PhasesLevel.INSTALL;
    }

    if (taskName.contentEquals("deploy")
        && (    phasesLevel == PhasesLevel.NOTHING
        || phasesLevel == PhasesLevel.COMPILE
        || phasesLevel == PhasesLevel.PACKAGE
        || phasesLevel == PhasesLevel.INSTALL
      )
   ) {
      phasesLevel = PhasesLevel.DEPLOY;
    }
  }
}
