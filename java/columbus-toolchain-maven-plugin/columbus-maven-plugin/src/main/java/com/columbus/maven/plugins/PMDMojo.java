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

package com.columbus.maven.plugins;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;

import org.apache.maven.plugin.MojoExecutionException;
import org.apache.maven.plugins.annotations.LifecyclePhase;
import org.apache.maven.plugins.annotations.Mojo;
import org.apache.maven.plugins.annotations.Parameter;
import org.apache.maven.plugins.annotations.ResolutionScope;
import org.apache.maven.project.MavenProject;

/**
 * Goal which is calling PMD tool.
 * 
 */
@Mojo(name = "pmd", defaultPhase = LifecyclePhase.COMPILE, threadSafe = true,requiresDependencyResolution = ResolutionScope.COMPILE_PLUS_RUNTIME)
public class PMDMojo extends AbstractColumbusMojo {

  @Parameter(defaultValue = "${project.build.outputDirectory}", property = "outputDir", required = true)
  private File outputDirectory;

  private void executePMD(String srcDir) {
    boolean hasClassPathFile = clreateClassPathFile();
    // create a build script

    ArrayList<String> cmd = new ArrayList<String>();
    cmd.add("java");
    
    if (EnvManager.getInstance().getJANJVMOptions() != null) {
        cmd.addAll(EnvManager.getInstance().getJANJVMOptions());
    }
    
    cmd.add("-Djava.ext.dirs="
        + new File(EnvManager.getInstance().getWrapperToolsDir(), "PMD/lib/").getAbsolutePath());
    cmd.add("net.sourceforge.pmd.PMD");
    cmd.add("-d");
    cmd.add(srcDir);
    if (hasClassPathFile) {
      cmd.add("-auxclasspath");
      cmd.add("file:///"
          +  EnvManager.getInstance()
          .getClassPathListName());
    }
    cmd.add("-f");
    cmd.add("xml");
    cmd.add("-R");
    cmd.add(EnvManager.getInstance().getPmdConfigFile());
    cmd.add("-r");
    cmd.add(EnvManager.getInstance().getPmdResXml());

    if (EnvManager.getInstance().getLastAnalyzedEnc() != null) {
    	cmd.add("-e");
		cmd.add(EnvManager.getInstance().getLastAnalyzedEnc());
    }
    
    
    if (EnvManager.getInstance().getLastAnalyzedSource() != null) {
    	cmd.add("-v");
		cmd.add(EnvManager.getInstance().getLastAnalyzedSource());
    }

    EnvManager.getInstance().exec(cmd, "PMD", null);

  }

  private void savePmdStats(long pmdTime) {
    if (EnvManager.getInstance().getPmdStat() == null )
      return ;
    final String delim = ";";
    String statPath = new File(EnvManager.getInstance().getProjectLogDir(),EnvManager.getInstance().getPmdStat()).getPath();
    File statFile = new File(statPath);
    boolean writeHeader = !statFile.exists();
    PrintWriter writer = null;
    try {
      writer = new PrintWriter(new BufferedWriter(new FileWriter(statFile, true))); 
    
      if (writeHeader) {
        writer.println("Total cpu time (s)" + delim + "Peak memory usage (MB)");
      }
      writer.println((pmdTime / 1000.0) + delim + 0);
    } catch (IOException e) {
      //logger.error("warn.antwrapper.Javac.couldntSavePMDStat", statPath, e);
    } 
    finally{
      if (writer != null) {
        writer.close();
      }
    }
  }
  
  public void execute() throws MojoExecutionException {
    if (project.getPackaging().equals("pom")) {
      getLog().info("The" + project.getName() + " is not a jar project");
      return;
    }
    init();

    if (!needToRun(new File(EnvManager.getInstance().getPmdResXml()))) {
      getLog().info("it nothing to do.");
      return;
    }

    String srcDir = project.getBuild().getSourceDirectory();
    getLog().info("Analyzing with pmd output dir: " + outputDirectory
        + " input " + srcDir);
    
    long pmdStartTime = System.currentTimeMillis();
    executePMD(srcDir);
    long pmdEndTime = System.currentTimeMillis();
    long pmdTime = pmdEndTime - pmdStartTime;
    savePmdStats(pmdTime);
    
    if (new File(EnvManager.getInstance().getPmdResXml()).exists()) { 
    getLog().info("Call PMD2ChangePath:");
    
    String toPathPart = EnvManager.getInstance().getProjectId();
    
    if (null != System.getenv(EnvManager.OSA_MAVEN_ADD_FULL_SRC_DIR) ) {
      
      toPathPart = new File( EnvManager.getInstance().getProjectId(), project.getBuild().getSourceDirectory().substring((int)project.getBasedir().toString().length()) ).toString()  ;
    } else {
      toPathPart =  EnvManager.getInstance().getProjectId() ;
    }
    
    
    
    changePmdPath(project.getBuild().getSourceDirectory(),
        toPathPart );
    }
    
    
    
  }

  /**
   * 
   */
  private void changePmdPath(String _from, String _to) {
    try {
      String from = new String(_from);
      String to = new String(_to);
      PrintWriter writer = new PrintWriter(EnvManager.getInstance()
                                                     .getPmdResXml() + ".tmp",
                                           "UTF-8");
      BufferedReader br = new BufferedReader(new FileReader(EnvManager.getInstance()
                                                                      .getPmdResXml()));
      String line;
      while ((line = br.readLine()) != null) {
        String s = new String(line);
        if (line.startsWith("<file name=\"")) {
          if (EnvManager.getInstance().isWindows()) {
            s = s.toLowerCase();
            from = from.toLowerCase();
            // to = to.toLowerCase();
          }
          int pos = s.indexOf(from);
          if (pos > -1) {
            writer.print(line.substring(0, pos));
            writer.print(to);
            writer.println(line.substring(pos + _from.length()));
          } else {
            writer.println(line);
          }
        } else {
          writer.println(line);
        }

      }
      br.close();
      writer.close();
      if (new File(EnvManager.getInstance().getPmdResXml()).delete()) {
        new File(EnvManager.getInstance().getPmdResXml() + ".tmp").renameTo(new File(EnvManager.getInstance()
                                                                                               .getPmdResXml()));
      }

    } catch (Exception e2) {
      e2.printStackTrace();
    }

  }

}
