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
import java.util.List;

import org.apache.maven.plugin.MojoExecutionException;
import org.apache.maven.plugins.annotations.LifecyclePhase;
import org.apache.maven.plugins.annotations.Mojo;
import org.apache.maven.plugins.annotations.Parameter;
import org.apache.maven.plugins.annotations.ResolutionScope;


@Mojo(name = "ajsi", defaultPhase = LifecyclePhase.COMPILE, threadSafe = true, requiresDependencyResolution = ResolutionScope.COMPILE_PLUS_RUNTIME)
public class PackageAjsiMojo extends AbstractColumbusMojo {

  @Parameter(defaultValue = "${project.build.outputDirectory}", property = "outputDir", required = true)
  private File outputDirectory;

  @Parameter(defaultValue = "${justReportSrc}")
  private File justReportSrcDirectoryOutFile;

  /**
   * The source directories containing the sources to be compiled.
   */
  @Parameter(defaultValue = "${project.compileSourceRoots}", required = true)
  private List<String> compileSourceRoots;

  public void execute() throws MojoExecutionException {
    if (project.getPackaging().equals("pom")) {
      getLog().info("The" + project.getName() + " is not a jar project");
      return;
    }
    init();

    getLog().info("Call pervision phase create jsi goal:");
    executeMojo(getMyPlugin(),
                   "compile");

    getLog().info("Create ajsi :");
    executeMojo(getMyPlugin(),
                   "packagejar",
                   element("classesDirectory",
                                        EnvManager.getInstance()
                                                  .getOutputJsiDir()),
                   element("finalName",
                                        EnvManager.getInstance()
                                                  .getProjectAjsiFileNameFilepart()),
                   element("outputDirectory",
                                        EnvManager.getInstance()
                                                  .getOpenStaticAnalyzerDir()));
    getLog().info("Create ajsi done.");
    new File(EnvManager.getInstance().getProjectAjsiFileName()).delete();

    if (!(new File(EnvManager.getInstance().getOpenStaticAnalyzerDir(),
                   EnvManager.getInstance().getProjectAjsiFileNameFilepart()
                       + ".jar").renameTo(new File(EnvManager.getInstance()
                                                             .getProjectAjsiFileName())))) {
      getLog().error("Can' rename jar file to ajsi  :"
          + EnvManager.getInstance().getProjectAjsiFileNameFilepart() + ".jar");
    }
  }

}
