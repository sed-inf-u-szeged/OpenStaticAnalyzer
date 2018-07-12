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

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Set;

import org.apache.commons.io.IOUtils;
import org.apache.maven.artifact.Artifact;
import org.apache.maven.artifact.factory.ArtifactFactory;
import org.apache.maven.artifact.metadata.ArtifactMetadataSource;
import org.apache.maven.artifact.repository.ArtifactRepository;
import org.apache.maven.artifact.resolver.ArtifactCollector;
import org.apache.maven.artifact.resolver.ArtifactNotFoundException;
import org.apache.maven.artifact.resolver.ArtifactResolutionException;
import org.apache.maven.artifact.resolver.ArtifactResolver;
import org.apache.maven.artifact.resolver.filter.ArtifactFilter;
import org.apache.maven.model.Model;
import org.apache.maven.model.io.xpp3.MavenXpp3Reader;
import org.apache.maven.plugin.MojoExecutionException;
import org.apache.maven.plugin.dependency.fromConfiguration.ArtifactItem;
import org.apache.maven.plugin.dependency.utils.DependencyStatusSets;
import org.apache.maven.plugin.dependency.utils.filters.ResolveFileFilter;
import org.apache.maven.plugin.dependency.utils.markers.SourcesFileMarkerHandler;
import org.apache.maven.plugin.dependency.utils.resolvers.ArtifactsResolver;
import org.apache.maven.plugin.dependency.utils.resolvers.DefaultArtifactsResolver;
import org.apache.maven.plugin.dependency.utils.translators.ArtifactTranslator;
import org.apache.maven.plugin.dependency.utils.translators.ClassifierTypeTranslator;
import org.apache.maven.plugin.version.PluginVersionResolutionException;
import org.apache.maven.plugins.annotations.Component;
import org.apache.maven.plugins.annotations.LifecyclePhase;
import org.apache.maven.plugins.annotations.Mojo;
import org.apache.maven.plugins.annotations.Parameter;
import org.apache.maven.plugins.annotations.ResolutionScope;
import org.apache.maven.project.MavenProject;
import org.apache.maven.shared.artifact.filter.collection.ArtifactFilterException;
import org.apache.maven.shared.artifact.filter.collection.ArtifactsFilter;
import org.apache.maven.shared.artifact.filter.collection.FilterArtifacts;
import org.apache.maven.shared.artifact.filter.collection.TransitivityFilter;
import org.apache.maven.shared.dependency.tree.DependencyNode;
import org.apache.maven.shared.dependency.tree.DependencyTreeBuilder;
import org.apache.maven.shared.dependency.tree.DependencyTreeBuilderException;
import org.apache.maven.shared.dependency.tree.traversal.DependencyNodeVisitor;
import org.codehaus.plexus.util.FileUtils;

import com.columbus.maven.plugins.tools.CommponentStructureManager;
import com.columbus.maven.plugins.tools.ListFileManager;

/**
 * Goal which analyze files
 * 
 */
@Mojo(name = "link", defaultPhase = LifecyclePhase.PACKAGE, threadSafe = false, requiresDependencyResolution = ResolutionScope.COMPILE_PLUS_RUNTIME, requiresDependencyCollection = ResolutionScope.TEST)
public class LinkMojo extends AbstractColumbusMojo {

  /**
   * Directory to store flag files
   */
  @Parameter(property = "markersDirectory", defaultValue = "${project.build.directory}/dependency-maven-plugin-markers")
  protected File markersDirectory;

  public void execute() throws MojoExecutionException {
    getLog().info(
        "Linking analyize results " + project.getName() + " included deps"
            + includeDependenciesGroupIds);

    if (project.getPackaging().equals("pom")) {
      getLog().info("The" + project.getName() + " is not a jar project");
      return;
    }
    init();

    if (!needToRun(new File(EnvManager.getInstance().getSuperLinkListFileName()))) {
      getLog().info("it nothing to do.");
      return;
    }

    getLog().info(
        "Linking analyize results " + project.getName() + " included deps: "
            + includeDependenciesGroupIds);

    callReqiredGoals();

    try {
      if (EnvManager.getInstance().isAnalyzeResovableDep()) {
        getLog().info("Analyze dependencies");
        analyzeResolvableDependencies();
      }

      getLog().info("get dependencies ajsi :");
      unpackDependencies(EnvManager.OSA_CLASSIFER_AJSI, EnvManager
          .getInstance().getTmpLjsiDir());

      getLog().info("get dependencies apmd :");
      unpackDependencies(EnvManager.OSA_CLASSIFER_APMD, EnvManager
          .getInstance().getTmpPMDDir());

    } catch (Exception e) {
      e.printStackTrace();
    }

    copyCurrentLjsiToWorkDir();
    writeOutDep();
    try {
      generateSuperlinkList();
    } catch (Exception e) {
      e.printStackTrace();
      throw new MojoExecutionException("Can't create superlink list");
    }

  }

  /**
   * @throws MojoExecutionException
   * @throws IOException
   */
  private void analyzeResolvableDependencies() throws MojoExecutionException,
      IOException {

    DependencyStatusSets ajsiDepts = createDepList(EnvManager.OSA_CLASSIFER_AJSI);
    DependencyStatusSets sourceDepts = createDepList(EnvManager.CLASSIFER_SOURCES);

    ArtifactTranslator translator = new ClassifierTypeTranslator(
        EnvManager.CLASSIFER_SOURCES, "jar", artifactFactory);

    Set unresolvedButHasSourceSet = translator.translate(
        ajsiDepts.getUnResolvedDependencies(), getLog());

    Set resolvedSourceSet = sourceDepts.getResolvedDependencies();
    resolvedSourceSet.retainAll(unresolvedButHasSourceSet);

    installResolvableDeps(resolvedSourceSet);
  }

  private File getsubprojectRootDir(Artifact artifact) {
    return new File(new File(new File(new File(EnvManager.getInstance()
        .getProjectTempDir(), "src"), artifact.getGroupId()),
        artifact.getArtifactId()), artifact.getVersion());
  }

  private String getStringFromFile(File file) {
    String returnVal = null;
    try {
      BufferedReader br;
      br = new BufferedReader(new FileReader(file.getAbsolutePath()));
      returnVal = br.readLine();
      br.close();
    } catch (IOException e) {
      e.printStackTrace();
    }

    return returnVal;
  }

  private String getDownloadName(Artifact arti) {
    StringBuilder s = new StringBuilder();
    s.append(arti.getGroupId());
    s.append(":");
    s.append(arti.getArtifactId());
    s.append(":");
    s.append(arti.getVersion());
    s.append(":");
    s.append(arti.getType());
    s.append(":");
    s.append(arti.getClassifier());
    return s.toString();
  }

  /**
   * @param unresolvedButHasSource
   * @throws MojoExecutionException
   * @throws IOException
   */
  private void installResolvableDeps(Set unresolvedButHasSource)
      throws MojoExecutionException, IOException {
    for (Object articatObject : unresolvedButHasSource) {
      Artifact arti = (Artifact) articatObject;
      if (arti != null) {
        getLog().info("Download the  " + arti.toString() + " .");

        String artiFileName = arti.getFile().getAbsolutePath();
        String artiPomFileName = artiFileName.substring(0,
            artiFileName.lastIndexOf("-sources.jar"))
            + ".pom";
        File artiPomFile = new File(artiPomFileName);
        if (artiPomFile.exists()) {
          FileUtils.copyFile(artiPomFile, new File(getsubprojectRootDir(arti),
              "/pom.xml"));
        }
      }
      getLog().info("Download the  " + arti.toString() + " srcs. to "+getsubprojectRootDir(arti));

      ArrayList<String> cmd = new ArrayList<String>();
      cmd.add(EnvManager.getInstance().getMvnBin());
      cmd.add(MY_PLUGIN_PREFIX+":compile");
      cmd.add("-DjustReportSrc=SrcDirName.txt");

      if (EnvManager.getInstance().exec(cmd,
          getLogFileNameSubBuild(arti, "getSrcDir"), null,
          getsubprojectRootDir(arti)) != 0) {
        throw new MojoExecutionException("The src dir find out falied");
      }

      String srcDirName = getStringFromFile(new File(
          getsubprojectRootDir(arti), "SrcDirName.txt"));
      // download the sources
      downloadArtifact(getDownloadName(arti), srcDirName);

      // build

      cmd = new ArrayList<String>();
      cmd.add(EnvManager.getInstance().getMvnBin());
      cmd.add(MY_PLUGIN_PREFIX+":"
          + (EnvManager.getInstance().isDeployTheDept() ? "deploy" : "install"));
      cmd.add("-DnoExportGraph=true");

      if (EnvManager.getInstance().exec(cmd, getLogFileNameSubBuild(arti, ""),
          null, getsubprojectRootDir(arti)) != 0) {
        if (EnvManager.getInstance().isDeployTheDept()) {
          cmd = new ArrayList<String>();
          cmd.add(EnvManager.getInstance().getMvnBin());
          cmd.add(MY_PLUGIN_NAME + ":install");
          cmd.add("-DnoExportGraph=true");

          if (EnvManager.getInstance().exec(cmd,
              getLogFileNameSubBuild(arti, "2nd"), null,
              getsubprojectRootDir(arti)) != 0) {

            getLog().error(
                "Build dep " + getsubprojectRootDir(arti) + " is fault 2nd.");
          }

        } else {

          getLog().error(
              "Build dep " + getsubprojectRootDir(arti) + " is fault.");
        }
      }
    }
  }

  private String getLogFileNameSubBuild(Artifact arti, String prefix) {
    StringBuilder logFileNameFindOutSrcDir = new StringBuilder();
    logFileNameFindOutSrcDir.append("install_dep_");
    logFileNameFindOutSrcDir.append(prefix);
    logFileNameFindOutSrcDir.append("_");
    logFileNameFindOutSrcDir.append(arti.getGroupId());
    logFileNameFindOutSrcDir.append("_");
    logFileNameFindOutSrcDir.append(arti.getArtifactId());
    logFileNameFindOutSrcDir.append("_");
    logFileNameFindOutSrcDir.append(arti.getVersion());
    return logFileNameFindOutSrcDir.toString();
  }

  /**
   * @param ArticatName
   *          A string of the form
   *          groupId:artifactId:version[:packaging][:classifier].
   * @param destDirectory
   * @throws MojoExecutionException
   */

  private Element getArtifactByElement(String ArticatName, String destDirectory) {
    String[] splited = ArticatName.split(":");
    return element(
        "artifactItems",
        element("artifactItem", element("groupId", splited[0]),
            element("artifactId", splited[1]), element("version", splited[2]),
            element("type", splited[3]), element("classifier", splited[4]),
            element("overWrite", "true"),
            element("outputDirectory", destDirectory)

        ));
  }

  private void downloadArtifact(String ArticatName, String destDirectory)
      throws MojoExecutionException {
    try {

      Element artifactItems = getArtifactByElement(ArticatName, destDirectory);

      executeMojo(
          plugin("org.apache.maven.plugins", "maven-dependency-plugin"),
          "unpack", artifactItems

      );
    } catch (MojoExecutionException e) {
      e.printStackTrace();
      throw e;
    } catch (PluginVersionResolutionException e) {
      e.printStackTrace();
    }
  }

  protected ArtifactsFilter getMarkedArtifactFilter() {
    return new ResolveFileFilter(new SourcesFileMarkerHandler(
        this.markersDirectory));
  }

  /**
   * @param typeClassifier
   * @param outputFile
   * @throws MojoExecutionException
   */

  protected DependencyStatusSets filterMarkedDependencies(Set artifacts)
      throws MojoExecutionException {
    // remove files that have markers already
    FilterArtifacts filter = new FilterArtifacts();
    filter.clearFilters();
    filter.addFilter(getMarkedArtifactFilter());

    Set unMarkedArtifacts;
    try {
      unMarkedArtifacts = filter.filter(artifacts);
    } catch (ArtifactFilterException e) {
      throw new MojoExecutionException(e.getMessage(), e);
    }

    // calculate the skipped artifacts
    Set skippedArtifacts = new HashSet();
    skippedArtifacts.addAll(artifacts);
    skippedArtifacts.removeAll(unMarkedArtifacts);

    return new DependencyStatusSets(unMarkedArtifacts, null, skippedArtifacts);
  }

  private class ArtifactsRegexpFilter implements ArtifactsFilter {

    public ArtifactsRegexpFilter(String pattern) {
      this.pattern = pattern;
    }

    private String pattern;

    public Set filter(Set artifacts) throws ArtifactFilterException {
      Set result = new HashSet();

      Iterator iter = artifacts.iterator();

      while (iter.hasNext()) {
        Artifact artifact = (Artifact) iter.next();
        if (isArtifactIncluded(artifact)) {
          result.add(artifact);
        }
      }
      return result;

    }

    public boolean isArtifactIncluded(Artifact arti)
        throws ArtifactFilterException {

      StringBuilder s = new StringBuilder();
      s.append(arti.getGroupId());
      s.append(":");
      s.append(arti.getArtifactId());
      s.append(":");
      s.append(arti.getVersion());

      // default the filter is allow all.
      if (pattern == null) {
        System.out.println("The " + s.toString() + " is a dependency");
        return true;
      }

      if (s.toString().matches(pattern)) {
        System.out.println("The " + s.toString()
            + " is a dependency not filtered");
        return true;
      }
      System.out.println("The " + s.toString()
          + "is skipped dependency by filter");
      return false;
    }

  }

  private DependencyStatusSets createDepList(String typeClassifier)
      throws MojoExecutionException {

    Set unResolvedArtifacts = new HashSet();

    FilterArtifacts filter = new FilterArtifacts();

    filter.addFilter(new ArtifactsRegexpFilter(EnvManager.getInstance()
        .getDependencyFilter()));

    Set artifacts = project.getArtifacts();
    Set artifacts2 = project.getDependencyArtifacts();
    artifacts.addAll(artifacts2);
    // perform filtering
    try {
      artifacts = filter.filter(artifacts);
    } catch (ArtifactFilterException e) {
      throw new MojoExecutionException(e.getMessage(), e);
    }

    Set resolvedArtifacts = artifacts;
    DependencyStatusSets status = new DependencyStatusSets();

    // possibly translate artifacts into a new set of artifacts based on the
    // classifier and type
    // if this did something, we need to resolve the new artifacts

    ArtifactTranslator translator = new ClassifierTypeTranslator(
        typeClassifier, "jar", artifactFactory);
    artifacts = translator.translate(artifacts, getLog());

    status = filterMarkedDependencies(artifacts);

    // the unskipped artifacts are in the resolved set.
    artifacts = status.getResolvedDependencies();

    // resolve the rest of the artifacts
    ArtifactsResolver artifactsResolver = new DefaultArtifactsResolver(
        artifactResolver, localRepository,
        project.getRemoteArtifactRepositories(), false);
    resolvedArtifacts = artifactsResolver.resolve(artifacts, getLog());

    // calculate the artifacts not resolved.
    unResolvedArtifacts.addAll(artifacts);
    unResolvedArtifacts.removeAll(resolvedArtifacts);

    // return a bean of all 3 sets.
    status.setResolvedDependencies(resolvedArtifacts);
    status.setUnResolvedDependencies(unResolvedArtifacts);

    return status;

  }

  boolean isArtifactResolvable(Artifact pomArtifact) {
    try {

      artifactResolver.resolve(pomArtifact,
          project.getRemoteArtifactRepositories(), localRepository);
    } catch (ArtifactResolutionException e) {
      return false;

    } catch (ArtifactNotFoundException e) {
      return false;
    }
    return true;
  }

  /**
   * @throws MojoExecutionException
   * @throws IOException
   * @throws FileNotFoundException
   */
  private void unpackDependencies(String typeClassifier, String outputDirectory)
      throws MojoExecutionException, FileNotFoundException, IOException {
    new File(outputDirectory).mkdirs();

    DependencyStatusSets depsSet = createDepList(typeClassifier);

    // unpack it.

    for (Object oart : depsSet.getResolvedDependencies()) {
      Artifact artifact = (Artifact) oart;
      String artId = artifact.getGroupId() + ":" + artifact.getArtifactId()
          + ":" + artifact.getVersion() + ":" + artifact.getType() + ":"
          + artifact.getClassifier();
      getLog().info("The " + artId + " is downloading...");
      try {
        downloadArtifact(artId, outputDirectory);
      } catch (MojoExecutionException e) {
        getLog().info("The " + artId + " has not downloaded.");
      }
    }
  }

  /**
   * @throws MojoExecutionException
   */
  private void callReqiredGoals() throws MojoExecutionException {
    getLog().info("Call compile..");

    executeMojo(getMyPlugin(), "compile");

    getLog().info("Call PMD..");
    executeMojo(getMyPlugin(), "pmd"

    );
  }

  private void copyCurrentLjsiToWorkDir() {
    getLog().info(
        "Copy analyized files.."
            + EnvManager.getInstance().getProjectLjsiFileName());

    try {
      FileUtils.copyFile(new File(EnvManager.getInstance()
          .getProjectLjsiFileName()), new File(EnvManager.getInstance()
          .getTmpLjsiDir(), new File(EnvManager.getInstance()
          .getProjectLjsiFileName()).getName()));

      String filterFile = replaceExtension(EnvManager.getInstance()
          .getProjectLjsiFileName(), ".fjsi");

      FileUtils.copyFile(new File(filterFile), new File(EnvManager
          .getInstance().getTmpLjsiDir(), new File(filterFile).getName()));

      String infoFile = EnvManager.getInstance().getProjectLjsiFileName()
          + ".info";

      FileUtils.copyFile(new File(infoFile),
                         new File(EnvManager.getInstance().getTmpLjsiDir(),
                                  new File(infoFile).getName()));

    } catch (IOException e) {
      getLog().info("The ljsi files not found for this project");
    }
    try {
      new File(EnvManager.getInstance().getTmpPMDDir()).mkdirs();
      FileUtils.copyFile(new File(EnvManager.getInstance().getPmdResXml()),
          new File(EnvManager.getInstance().getTmpPMDDir(), new File(EnvManager
              .getInstance().getPmdResXml()).getName()));
    } catch (IOException e) {
      getLog().info("The pmd result files not found for this project");
    }
  }

  protected void chanegJsiPathForQg(File srcList) throws MojoExecutionException {

    getLog().info("Changing Path for remi");

    BufferedReader br = null;
    try {
      br = new BufferedReader(new FileReader(srcList));
      String lineLjsiFfile;
      while ((lineLjsiFfile = br.readLine()) != null) {
        lineLjsiFfile = lineLjsiFfile.trim();
        File ljsiName = new File(lineLjsiFfile + ".info");
        if (ljsiName.exists()) {
          getLog().info("Parse " + ljsiName + "file.");
          BufferedReader infoFile = null;
          try {
            infoFile = new BufferedReader(new FileReader(ljsiName));
            String theComponentName = infoFile.readLine();
            String VCS_URL = infoFile.readLine();
            String ProjectBaseDir = infoFile.readLine()
                                            .substring("Analyzis_ROOT:".length());

            String ArtifactSRC = infoFile.readLine()
                                         .substring("Artifact_SRC_ROOT:".length());
            String realtivSrcDir = ArtifactSRC.substring(ProjectBaseDir.length() + 1);

            if (new File(lineLjsiFfile).exists()) {
              getLog().info("Call JAN2ChangePath:");

              ArrayList<String> cmd = new ArrayList<String>();
              cmd.add(new File(EnvManager.getInstance().getToolsDir(),
                               "JAN2ChangePath").getAbsolutePath());
              cmd.add("-from:" + theComponentName);

              cmd.add("-to:" + realtivSrcDir);

              cmd.add(lineLjsiFfile);
              EnvManager.getInstance().exec(cmd, "JAN2ChangePath", null);

            }

            File thexmlPath = new File(lineLjsiFfile, "../../PMDs/"
                + theComponentName + "-PMD.xml");

            getLog().info("The pmf file " + thexmlPath.getAbsolutePath()
                + "file not valid");

            EnvManager.getInstance()
                      .changePmdPath(thexmlPath.getAbsolutePath(),
                                     theComponentName,
                                     ArtifactSRC);

          } catch (IOException e) {
            getLog().warn("The " + ljsiName + "file not valid");
          } finally {
            IOUtils.closeQuietly(infoFile);
          }
        } else {
          getLog().warn("The " + ljsiName + "file not exsist");
        }
      }
    } catch (IOException e) {
      getLog().warn("The src list not exsist" + e);
    } finally {
      IOUtils.closeQuietly(br);
    }

  }

  private void generateSuperlinkList() throws FileNotFoundException,
      UnsupportedEncodingException {
    getLog().info("Generate List Files.");
    JavaCollector.makeAlistFileFromFiles(new File(EnvManager.getInstance()
        .getTmpLjsiDir()), ".ljsi", new File(EnvManager.getInstance()
        .getSuperLinkListFileName()));


    appendMainSuperlinkList();

    if (System.getenv("remi") != null) {
      try {
        chanegJsiPathForQg(new File(EnvManager.getInstance()
                                              .getSuperLinkListFileName()));
      } catch (MojoExecutionException e) {
        e.printStackTrace();
      }
    }

    JavaCollector.makeAlistFileFromFiles(new File(EnvManager.getInstance()
        .getTmpPMDDir()), "-PMD.xml", new File(EnvManager.getInstance()
        .getPMDListFileName()));

    if (EnvManager.getInstance().getMainComponetList() != null) {
      generateComponentsInfo();
    }
    appendMainSuperPMDList();

  }

  private void generateComponentsInfo() {
    try {
      ListFileManager listfile = new ListFileManager();
      
      if (EnvManager.getInstance().getisCurrentComponetInList()) {
        listfile.append(getComponenetInfoLine(project));
      }
      
      

      DependencyStatusSets ajsiDepts = createDepList(EnvManager.OSA_CLASSIFER_AJSI);
      
      
      
      
      for (Object oLine : ajsiDepts.getResolvedDependencies()) {
        // Deal with the line
        Artifact line = (Artifact) oLine;
       

        File pomFile = line.getFile();
        pomFile = new File(pomFile.toString().substring(0,
            pomFile.toString().lastIndexOf("-OpenStaticAnalyzer-ajsi.jar"))
            + ".pom");

        // fileStream.print(pomFile+";");

        Model model = null;
        FileReader reader = null;
        MavenXpp3Reader mavenreader = new MavenXpp3Reader();
        try {
          reader = new FileReader(pomFile);
          model = mavenreader.read(reader);

          MavenProject project = new MavenProject(model);
          
          listfile.append(getComponenetInfoLine(project));
          
        } catch (Exception ex) {
          ex.printStackTrace();
        }
      }
      if (EnvManager.getInstance().getMainComponetList().exists()) {
        listfile.append(EnvManager.getInstance().getMainComponetList());
      }
      listfile.save(EnvManager.getInstance().getMainComponetList());
    } catch (IOException e) {
      e.printStackTrace();
    } catch (MojoExecutionException e) {
      e.printStackTrace();
    }
  }

  private String getComponenetInfoLine(MavenProject project) {
    StringBuilder stringLine = new StringBuilder();
    stringLine.append(project.getGroupId());
    stringLine.append(":");
    stringLine.append(project.getArtifactId());
    stringLine.append(":");
    stringLine.append(project.getVersion());
    stringLine.append(";");
    
    
    if (project.getScm() != null) {
      stringLine.append(project.getScm().getUrl());
    }
    return stringLine.toString();
  }

  private void appendMainSuperPMDList() {
    if (EnvManager.getInstance().getMainSuperPMDList() != null) {
      // filltoSet
      ListFileManager listfile = new ListFileManager();
      try {
        listfile
            .append(new File(EnvManager.getInstance().getPMDListFileName()));

        if (EnvManager.getInstance().getMainSuperPMDList().exists()) {
          listfile.append(EnvManager.getInstance().getMainSuperPMDList());
        }

        listfile.save(EnvManager.getInstance().getMainSuperPMDList());
      } catch (IOException e) {
        e.printStackTrace();
      }
    }
  }

  private void appendMainSuperlinkList() {
    if (EnvManager.getInstance().getMainSuperlinkList() != null) {
      // filltoSet
      ListFileManager listfile = new ListFileManager();
      try {
        listfile.append(new File(EnvManager.getInstance()
            .getSuperLinkListFileName()));
        if (EnvManager.getInstance().getMainSuperlinkList().exists()) {
          listfile.append(EnvManager.getInstance().getMainSuperlinkList());
        }

        listfile.save(EnvManager.getInstance().getMainSuperlinkList());
      } catch (IOException e) {
        e.printStackTrace();
      }
      try {
        mergeDeptSuperDeptStruct();
      } catch (DependencyTreeBuilderException e) {
        e.printStackTrace();
      }
    }
  }

  private String replaceExtension(String fileName, String extension) {
    String fileNameWithoutExtension = fileName.substring(0,
        fileName.lastIndexOf("."));
    fileNameWithoutExtension += extension;
    return fileNameWithoutExtension;
  }

  /**
   * The dependency tree builder to use for verbose output.
   */
  @Component
  private DependencyTreeBuilder dependencyTreeBuilder;
  @Component
  private ArtifactFactory artifactFactory;
  @Component
  private ArtifactMetadataSource artifactMetadataSource;
  @Component
  private ArtifactCollector artifactCollector;

  private void mergeDeptSuperDeptStruct() throws DependencyTreeBuilderException {
    ArtifactFilter artifactFilter = null;
    DependencyNode rootNode = dependencyTreeBuilder.buildDependencyTree(
        project, localRepository, artifactFactory, artifactMetadataSource,
        artifactFilter, artifactCollector);
    CommponentStructureManager depManager = new CommponentStructureManager(
        artifactFactory, getLog(), project, artifactResolver, localRepository);
    depManager.merge(rootNode);
    try {
      depManager.merge(new File(EnvManager.getInstance().getMainSuperlinkList()
          + EnvManager.INFO_EXTENSION));

      PrintWriter writer = null;
      try {
        writer = new PrintWriter(new File(EnvManager.getInstance()
            .getMainSuperlinkList() + EnvManager.INFO_EXTENSION), "UTF-8");
        writer.append(depManager.serialiseDependencyTree());

      } finally {
        if (writer != null) {
          ListFileManager.closeQuietly(writer);
        }
      }

    } catch (Exception e) {
      e.printStackTrace();
    }
  }

  private void writeOutDep() {
    getLog().info("Write out the dependencies...");
    PrintWriter writer = null;
    try {
      writer = new PrintWriter(EnvManager.getInstance()
          .getProjectLjsiDepFileName(), "UTF-8");

      CommponentStructureManager depManager = new CommponentStructureManager(
          artifactFactory, getLog(), project, artifactResolver, localRepository);

      DependencyNode rootNode;
      ArtifactFilter artifactFilter = null;
      rootNode = dependencyTreeBuilder.buildDependencyTree(project,
          localRepository, artifactFactory, artifactMetadataSource,
          artifactFilter, artifactCollector);
      depManager.merge(rootNode);
      String dependencyTreeString = depManager.serialiseDependencyTree();
      // project.getDependencies()
      writer.println(dependencyTreeString);
    } catch (FileNotFoundException e) {
      e.printStackTrace();
    } catch (UnsupportedEncodingException e) {
      e.printStackTrace();
    } catch (DependencyTreeBuilderException e) {
      e.printStackTrace();
    } finally {
      if (writer != null) {
        writer.close();
      }
    }
  }

  /**
   * Findout teh file name of the artifact id
   * 
   * @param arti
   * @return
   */
  public String getArtifactId(Artifact arti) {
    return new File(new File(EnvManager.getInstance().getTmpLjsiDir()),
        (arti.getGroupId() + "-" + arti.getArtifactId() + "-"
            + arti.getVersion() + ".ljsi")).getAbsolutePath();
  }

}
