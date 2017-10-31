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

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.io.UnsupportedEncodingException;
import java.net.URL;
import java.net.URLDecoder;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.xpath.XPath;
import javax.xml.xpath.XPathExpressionException;
import javax.xml.xpath.XPathFactory;

import org.apache.maven.artifact.Artifact;
import org.apache.maven.artifact.factory.ArtifactFactory;
import org.apache.maven.artifact.metadata.ArtifactMetadataSource;
import org.apache.maven.artifact.repository.ArtifactRepository;
import org.apache.maven.artifact.repository.metadata.ArtifactRepositoryMetadata;
import org.apache.maven.artifact.repository.metadata.GroupRepositoryMetadata;
import org.apache.maven.artifact.repository.metadata.RepositoryMetadataStoreException;
import org.apache.maven.plugin.MojoExecutionException;
import org.apache.maven.plugin.dependency.utils.resolvers.ArtifactsResolver;
import org.apache.maven.plugin.dependency.utils.resolvers.DefaultArtifactsResolver;
import org.apache.maven.plugin.version.PluginVersionResolutionException;
import org.apache.maven.plugins.annotations.Execute;
import org.apache.maven.plugins.annotations.LifecyclePhase;
import org.apache.maven.plugins.annotations.Mojo;
import org.apache.maven.plugins.annotations.Parameter;
import org.apache.maven.plugins.annotations.ResolutionScope;
import org.apache.maven.shared.dependency.tree.DependencyNode;
import org.apache.maven.shared.dependency.tree.DependencyTreeBuilder;
import org.apache.maven.shared.dependency.tree.DependencyTreeBuilderException;
import org.apache.maven.shared.dependency.tree.traversal.BuildingDependencyNodeVisitor;
import org.apache.maven.shared.dependency.tree.traversal.DependencyNodeVisitor;
import org.apache.maven.plugins.annotations.Component;
import org.codehaus.plexus.util.FileUtils;
import org.codehaus.plexus.util.xml.Xpp3Dom;
import org.w3c.dom.Document;
import org.w3c.dom.Node;
import org.xml.sax.SAXException;
import org.apache.maven.artifact.repository.metadata.Versioning;
import org.apache.maven.artifact.resolver.ArtifactCollector;
import org.apache.maven.artifact.resolver.filter.ArtifactFilter;
import org.apache.maven.plugins.annotations.Component;
import com.columbus.maven.plugins.tools.ListFileManager;

/**
 * Goal which analyze files with JAN.
 * 
 */

@Mojo(name = "compile", defaultPhase = LifecyclePhase.COMPILE, threadSafe = true,  requiresDependencyResolution = ResolutionScope.COMPILE_PLUS_RUNTIME)
public class ColumbusMojo extends AbstractColumbusMojo {

  private static final String FAKE_EXECUTION_ID = "virtual-execution";
 
  
  @Parameter(defaultValue = "${project.build.outputDirectory}", property = "outputDir", required = true)
  private File outputDirectory;

  /**
   * The plugin create the file with the name of the src diretory with the given
   * name
   */

  @Parameter(defaultValue = "${justReportSrc}")
  private File justReportSrcDirectoryOutFile;

  /**
   * The plugin is install itself with columbus prefix
   */

  @Parameter(defaultValue = "${justInstallPlugin}")
  private boolean installPlugin;

  /**
   * The source directories containing the sources to be compiled.
   */
  @Parameter(defaultValue = "${project.compileSourceRoots}", readonly = true, required = true)
  private List<String> compileSourceRoots;

  private List<String> compileSourceRootsCopy;

  @Parameter(defaultValue = "${project.compileClasspathElements}", readonly = true, required = true)
  private List<String> classpathElements;
  
  public void executeJAN(List<String> dir) {

    try {
      executeMojo(plugin("org.apache.maven.plugins", "maven-compiler-plugin"),
          "compile"

      );
    } catch (MojoExecutionException e1) {
      getLog().info("The original compile was failed..." + dir);
      e1.printStackTrace();
    } catch (PluginVersionResolutionException e) {
      e.printStackTrace();
    }

    getLog().info("Analyzing sources..." + dir);

    ArrayList<String> JANCmd = new ArrayList<String>();
    JANCmd.add("java");
    JANCmd.add("-version");

    EnvManager.getInstance().exec(JANCmd, "JavaVersion", null);

    JANCmd = new ArrayList<String>();

    JANCmd.add("java");
    
    if (EnvManager.getInstance().getJANJVMOptions() != null) {
        JANCmd.addAll(EnvManager.getInstance().getJANJVMOptions());
    }
    
    
    JANCmd.add("-jar");
    JANCmd.add(new File(EnvManager.getInstance().getWrapperToolsDir(),
        "JAN.jar").getAbsolutePath());
    JANCmd.add("-i");

    for (String s : dir) {
        JANCmd.add(s);
    }
    JANCmd.add("-o");
    JANCmd.add(EnvManager.getInstance().getProjectLjsiFileName());
    if (EnvManager.getInstance().getJANOptions() != null) {
      JANCmd.addAll(EnvManager.getInstance().getJANOptions());
    }
    
    
    String stat = EnvManager.getInstance().getJanStat();
    
    if (stat != null) {
      JANCmd.add("-t");
      JANCmd.add(new File (EnvManager.getInstance().getProjectLogDir() , stat).getPath());
    } 
    
    try {
      getLog().info("Collect compiler args..." + dir);
      Xpp3Dom xmlConfig = project.getGoalConfiguration(
          "org.apache.maven.plugins", "maven-compiler-plugin",
          FAKE_EXECUTION_ID, "compile");
      new File( EnvManager.getInstance().getArgFileName()).getParentFile().mkdirs();
      executeMojo(getMyPlugin(),
                  is3XMaven() ? "compileArgs3" : "compileArgs",
                  xmlConfig,
              element("outputArgFile", EnvManager.getInstance().getArgFileName()));
      
    } catch (MojoExecutionException e) {
      e.printStackTrace();
    }
    
    JANCmd.add("-a:componentId="+EnvManager.getInstance().getProjectId() );

    if (new File(EnvManager.getInstance().getArgFileName()).exists()) {
        JANCmd.add("-f");
        JANCmd.add("@" + EnvManager.getInstance().getArgFileName());
    }

    EnvManager.getInstance().exec(JANCmd, "JAN", null);

    PrintStream fileStream = null;
    try {
      fileStream = new PrintStream(new FileOutputStream(EnvManager.getInstance().getProjectLjsiFileName()+EnvManager.INFO_EXTENSION));
      fileStream.println(EnvManager.getInstance().getProjectId());
      fileStream.println("VCS_ROOT:"+System.getenv(EnvManager.OSA_MAVEN_VCS_SRC_DIR));
      fileStream.println("Analyzis_ROOT:"+ System.getenv(EnvManager.PROJECT_BASE_DIR));
      fileStream.println("Artifact_SRC_ROOT:"+project.getBuild().getSourceDirectory());
      
      
    } catch (FileNotFoundException e) {
      e.printStackTrace();
    } finally {
      ListFileManager.closeQuietly(fileStream);
    }
    
  }

  @Parameter(defaultValue = "${project.artifact}", required = true, readonly = true)
  private Artifact artifact;

  @Parameter(property = "localRepository")
  protected ArtifactRepository localRepository;

  public void execute() throws MojoExecutionException {
    compileSourceRootsCopy = new ArrayList<String>();
    compileSourceRootsCopy.addAll(compileSourceRoots);

	  System.out.println("Deps"+classpathElements.toString());
    if (project.getPackaging().equals("pom")) {
      getLog().info("The" + project.getName() + " is not a jar project");
      return;
    }

    init();

    if (justReportSrcDirectoryOutFile != null) {
      PrintWriter writer;
      try {
        writer = new PrintWriter(
            justReportSrcDirectoryOutFile.getAbsolutePath(), "UTF-8");
        writer.println(project.getBuild().getSourceDirectory());
        writer.close();
        getLog().info(
            "The" + project.getName() + " src dir("
                + project.getBuild().getSourceDirectory()
                + ") has been written to "
                + justReportSrcDirectoryOutFile.getAbsolutePath());
      } catch (FileNotFoundException e) {
        e.printStackTrace();
      } catch (UnsupportedEncodingException e) {
        e.printStackTrace();
      }
      return;
    }

    if (project.getPackaging().equals("pom")) {
      getLog().info("The" + project.getName() + " is not a jar project");
      return;
    }

    if (!needToRun(new File(EnvManager.getInstance().getProjectLjsiFileName()))) {
      getLog().info("it nothing to do.");
      return;
    }

    getLog().info("Analyzing output dir: " + outputDirectory);
    String srcDir = project.getBuild().getSourceDirectory();

    if (!compileSourceRootsCopy.isEmpty()) {
        getLog().info("compileSourceRoots: " + compileSourceRootsCopy);
        executeJAN(compileSourceRootsCopy);
    }

    if (null != System.getenv(EnvManager.OSA_MAVEN_ADD_WHOLE_SRC_DIR) )
    return ;
   
    if (new File(EnvManager.getInstance().getProjectLjsiFileName()).exists()) {
      getLog().info("Call JAN2ChangePath:");
    
      ArrayList<String> cmd = new ArrayList<String>();
      cmd.add(new File(EnvManager.getInstance().getToolsDir(), "JAN2ChangePath")
          .getAbsolutePath());
      cmd.add("-from:" + project.getBuild().getSourceDirectory());
      if (null != System.getenv(EnvManager.OSA_MAVEN_ADD_FULL_SRC_DIR) ) {
        
        cmd.add("-to:" + new File( EnvManager.getInstance().getProjectId(), project.getBuild().getSourceDirectory().substring((int)project.getBasedir().toString().length()) ).toString()  );
      } else {
        cmd.add("-to:" + EnvManager.getInstance().getProjectId() );
      }
      cmd.add(EnvManager.getInstance().getProjectLjsiFileName());
      EnvManager.getInstance().exec(cmd, "JAN2ChangePath", null);
    }
  }

  

}
