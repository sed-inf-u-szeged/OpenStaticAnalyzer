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
import java.io.File;
import java.io.FileReader;
import java.io.PrintWriter;
import java.util.List;

import org.apache.maven.artifact.repository.ArtifactRepository;
import org.apache.maven.artifact.resolver.ArtifactResolver;
import org.apache.maven.execution.MavenSession;
import org.apache.maven.model.Plugin;
import org.apache.maven.plugin.AbstractMojo;
import org.apache.maven.plugin.MojoExecutionException;
import org.apache.maven.plugin.PluginManager;
import org.apache.maven.plugins.annotations.Component;
import org.apache.maven.plugins.annotations.Parameter;
import org.apache.maven.project.MavenProject;
import org.codehaus.plexus.util.xml.Xpp3Dom;
import com.columbus.maven.executor.MojoExecutorFacilitiesAbstarctMojo;

public abstract class AbstractColumbusMojo extends
    MojoExecutorFacilitiesAbstarctMojo {

  /**
   * Project classpath.
   */
  @Parameter(defaultValue = "${project.compileClasspathElements}", readonly = true, required = true)
  protected List<String> classpathElements;
  private static final String FAKE_EXECUTION_ID = "virtual-execution";



  protected static final String ORG_APACHE_MAVEN_PLUGINS = "org.apache.maven.plugins";
  private static final String MAVEN_DEPENDENCY_PLUGIN = "maven-dependency-plugin";
  private static final String BUILD_CLASSPATH = "build-classpath";
  protected static final String MY_PLUGIN_NAME = "OpenStaticAnalyzer-maven-plugin";
  protected static final String MY_PLUGIN_PREFIX = "OpenStaticAnalyzer";
  protected static final String MY_PLUGIN_GROUP_NAME = "org.apache.maven.plugins";
  protected static final String MY_PLUGIN_VERSION = "2.0";
  /**
   * Collect the given groupid when export the results of analysis.
   */
  @Parameter(defaultValue = "${includeDependenciesGroupIds}")
  protected String includeDependenciesGroupIds;

  @Component
  protected ArtifactResolver artifactResolver;

  @Parameter(property = "localRepository")
  protected ArtifactRepository localRepository;

  /**
   * Dep filter This is the regexp for the groupid artifactid and version.
   */
  @Parameter(defaultValue = "${depFilt}")
  protected String dependencyFilter;

  /**
   * When this file is set The goal don run when the goal result is new than
   * this file
   */

  @Parameter(defaultValue = "${timeFlagFile}")
  protected File timeFlagFile;

  /**
   * Try the analyze all dependency (if has any what has not been use
   * includeDependenciesGroupIds)
   */
  @Parameter(defaultValue = "${tryAnalyzeAllDep}")
  protected Boolean tryAnaliseAllDep;

  /**
   * Build the component structure
   */
  
  @Parameter(defaultValue = "${struct}")
  protected Boolean buildComponentStructure;
  
  @Parameter(defaultValue = "${dumpGraph}")
  protected Boolean createGraphDump;
  


  protected boolean needToRun(File goalResultFile) {
    if (timeFlagFile != null && goalResultFile.exists()
        && timeFlagFile.exists()
        && timeFlagFile.lastModified() < goalResultFile.lastModified()) {
      return false;
    }

    return true;
  }

  boolean clreateClassPathFile() {
    boolean hasClassPathFile = false;

    try {

      Xpp3Dom xmlConfig = project.getGoalConfiguration("org.apache.maven.plugins",
                                                       "maven-compiler-plugin",
                                                       FAKE_EXECUTION_ID,
                                                       "compile");

      executeMojo(getMyPlugin(),
                  is3XMaven() ? "compileArgs3" : "compileArgs",
                     xmlConfig,
                     element("outputClassFile",
                                          EnvManager.getInstance()
                                                    .getClassPathListName()));
      hasClassPathFile = true;
    } catch (MojoExecutionException e) {
      e.printStackTrace();
    }

    return hasClassPathFile;
  }

  protected Plugin getMyPlugin() {
    return plugin(MY_PLUGIN_GROUP_NAME, MY_PLUGIN_NAME, MY_PLUGIN_VERSION);
  }

  protected String classPath;

  public String getClassPath() {
    if (classPath == null) {
      clreateClassPathFile();
    }
    return classPath;
  }

  void init() throws MojoExecutionException {
    EnvManager.getInstance().init(project.getBuild().getOutputDirectory(),
                                  project,
                                  includeDependenciesGroupIds,
                                  dependencyFilter,
                                  tryAnaliseAllDep,getLog());
   
    if (createGraphDump != null) {
      EnvManager.getInstance().setCreateGraphDump(createGraphDump);
    }
    
    if (buildComponentStructure != null) {
      EnvManager.getInstance().setBuildComponentStructure(buildComponentStructure);
    }
    
    if (EnvManager.getInstance().getToolchainBinDir() == null)
      throw new MojoExecutionException("The toolchain dir not found");
  }

  public MavenProject getMavenProject() {
    return project;
  }

  public MavenSession getMavenSession() {
    return mavenSession;
  }
 
  public String getIncludePaternTocompiler() {
    // project.getGoalConfiguration("", "", arg2, arg3)
    return null;
  }

}
