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
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;

import org.apache.maven.plugin.MojoExecutionException;
import org.apache.maven.plugin.MojoFailureException;
import org.apache.maven.plugins.annotations.LifecyclePhase;
import org.apache.maven.plugins.annotations.Mojo;
import org.apache.maven.plugins.annotations.ResolutionScope;
import org.codehaus.plexus.util.FileUtils;


@Mojo(name = "export", defaultPhase = LifecyclePhase.PACKAGE, threadSafe = true, requiresDependencyResolution = ResolutionScope.COMPILE_PLUS_RUNTIME)
public class ExportMojo extends AbstractColumbusMojo {

  private String replaceExtension(String fileName, String extension) {
    String fileNameWithoutExtension = fileName.substring(0,
                                                         fileName.lastIndexOf("."));
    fileNameWithoutExtension += extension;
    return fileNameWithoutExtension;
  }


  public void execute() throws MojoExecutionException, MojoFailureException {
    if (project.getPackaging().equals("pom")) {
      getLog().info("The" + project.getName() + " is not a jar project");
      return;
    }
    init();
    checkDependecy();
    try {
      // copyCurrentLjsiToWorkDir();

      // generateSuperlinkList();

      runJan2Lim();

      runDCF();

      runLim2Metrics();

      rumPMD2Graph();

      rumGraphMerge();

      if (EnvManager.getInstance().isCreateGraphDump()) {
        createGraphDump();
      }
      
    } catch (FileNotFoundException e) {
      e.printStackTrace();
    } catch (UnsupportedEncodingException e) {
      e.printStackTrace();
    } catch (IOException e) {
      e.printStackTrace();
    }
  }

  private void createGraphDump() {
    ArrayList<String> cmd = new ArrayList<String>();
    cmd.add(new File(EnvManager.getInstance().getToolsDir(), "GraphDump").getAbsolutePath());
    cmd.add(EnvManager.getInstance().getMergedGraphFileName());
    cmd.add("-xml:"+EnvManager.getInstance().getMergedGraphFileName()+".xml");
    EnvManager.getInstance().exec(cmd, "GraphDump", null);
  }


  /**
   * Check the input files is exist and it try to make those.
   * 
   * @throws MojoExecutionException
   */
  private void checkDependecy() throws MojoExecutionException {
    executeMojo(getMyPlugin(),
                   "link");

  }

  private void rumGraphMerge() {
    ArrayList<String> cmd = new ArrayList<String>();
    cmd.add(new File(EnvManager.getInstance().getToolsDir(), "GraphMerge").getAbsolutePath());
    cmd.add(EnvManager.getInstance().getPmdGraphFileName());
    cmd.add(EnvManager.getInstance().getMetricsGraphFileName());
    cmd.add(EnvManager.getInstance().getDcfGraphFileName());

    cmd.add("-out:" + EnvManager.getInstance().getMergedGraphFileName());

    EnvManager.getInstance().exec(cmd, "GraphMerge", null);

  }

  private void rumPMD2Graph() throws FileNotFoundException,
      UnsupportedEncodingException {
    getLog().info("rum PMD2Graph");
    JavaCollector.makeAlistFileFromFiles(new File(EnvManager.getInstance()
                                                            .getTmpPMDDir()),
                                         "-PMD.xml",
                                         new File(EnvManager.getInstance()
                                                            .getPMDListFileName()));

    ArrayList<String> cmd = new ArrayList<String>();
    cmd.add(new File(EnvManager.getInstance().getToolsDir(), "PMD2Graph").getAbsolutePath());
    cmd.add("-makecsv");
    cmd.add("-lst:" + EnvManager.getInstance().getPMDListFileName());
    cmd.add("-lim:" + EnvManager.getInstance().getLimFileName());
    cmd.add("-rul:"
        + new File(EnvManager.getInstance().getToolsDir(), "PMD.rul").getAbsolutePath());
    cmd.add("-exportrul");
    cmd.add("-graph:" + EnvManager.getInstance().getPmdGraphFileName());
    cmd.add("-printstdout");

    EnvManager.getInstance().exec(cmd, "PMD2Graph", null);
  }

  private void runLim2Metrics() {
    getLog().info("Run lim2metrics");

    ArrayList<String> cmd = new ArrayList<String>();
    cmd.add(new File(EnvManager.getInstance().getToolsDir(), "LIM2Metrics").getAbsolutePath());
    cmd.add("-graph:" + EnvManager.getInstance().getMetricsGraphFileName());
    cmd.add("-rul:"
        + new File(EnvManager.getInstance().getToolsDir(), "MET.rul").getAbsolutePath());
    cmd.add("-rulconfig:java");
    cmd.add("-exportrul");
    cmd.add(EnvManager.getInstance().getLimFileName());
    EnvManager.getInstance().exec(cmd, "LIM2Metrics", null);
  }

  private void runDCF() {
    getLog().info("Run duplicatedcode finder");
    ArrayList<String> cmd = new ArrayList<String>();
    cmd.add(new File(EnvManager.getInstance().getToolsDir(),
                     "JAVADuplicatedCodeFinder").getAbsolutePath());
    cmd.add("-inputlist:" + EnvManager.getInstance().getSuperLinkListFileName());
    cmd.add("-lim:" + EnvManager.getInstance().getLimFileName());
    cmd.add("-graph:" + EnvManager.getInstance().getDcfGraphFileName());
    cmd.add("-metrics");
    cmd.add("-multipleasgroot");
    cmd.add("-onlyfunctionclone");
    cmd.add("-patternfilter");
    cmd.add("10");
    cmd.add("100");
    cmd.add("-rul:"
        + new File(EnvManager.getInstance().getToolsDir(), "DCF.rul").getAbsolutePath());
    cmd.add("-rulconfig:java");
    cmd.add("-exportrul");
    EnvManager.getInstance().exec(cmd, "JavaDcf", null);
  }

  private void copyCurrentLjsiToWorkDir() {
    getLog().info("Copy analyized files.."
        + EnvManager.getInstance().getProjectLjsiFileName());

    try {
      FileUtils.copyFile(new File(EnvManager.getInstance()
                                            .getProjectLjsiFileName()),
                         new File(EnvManager.getInstance().getTmpLjsiDir(),
                                  new File(EnvManager.getInstance()
                                                     .getProjectLjsiFileName()).getName()));

      String filterFile = replaceExtension(EnvManager.getInstance()
                                                     .getProjectLjsiFileName(),
                                           ".fjsi");

      FileUtils.copyFile(new File(filterFile),
                         new File(EnvManager.getInstance().getTmpLjsiDir(),
                                  new File(filterFile).getName()));

    } catch (IOException e) {
      getLog().info("The ljsi files not found for this project");
    }
    try {
      new File(EnvManager.getInstance().getTmpPMDDir()).mkdirs();
      FileUtils.copyFile(new File(EnvManager.getInstance().getPmdResXml()),
                         new File(EnvManager.getInstance().getTmpPMDDir(),
                                  new File(EnvManager.getInstance()
                                                     .getPmdResXml()).getName()));
    } catch (IOException e) {
      getLog().info("The pmd result files not found for this project");
    }
  }

  private void generateSuperlinkList() throws FileNotFoundException,
      UnsupportedEncodingException {
    getLog().info("Generate List Files.");
    JavaCollector.makeAlistFileFromFiles(new File(EnvManager.getInstance()
                                                            .getTmpLjsiDir()),
                                         ".ljsi",
                                         new File(EnvManager.getInstance()
                                                            .getSuperLinkListFileName()));
  }

  private void runJan2Lim() {
    getLog().info("Run jan2lim.");

    ArrayList<String> cmd = new ArrayList<String>();
    cmd.add(new File(EnvManager.getInstance().getToolsDir(), "JAN2Lim").getAbsolutePath());
    if (EnvManager.getInstance().isBuildComponentStructure()){
      cmd.add("-struct:" + EnvManager.getInstance()
          .getProjectLjsiDepFileName());
    } 
    cmd.add("-out:" + EnvManager.getInstance().getLimFileName());
    cmd.add("-inputlist:" + EnvManager.getInstance().getSuperLinkListFileName());
    EnvManager.getInstance().exec(cmd, "JAN2Lim", null);
  }

}
