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


import org.apache.maven.archiver.MavenArchiveConfiguration;
import org.apache.maven.archiver.MavenArchiver;
import org.apache.maven.plugin.AbstractMojo;
import org.apache.maven.plugin.MojoExecutionException;
import org.apache.maven.plugins.annotations.Component;
import org.apache.maven.plugins.annotations.LifecyclePhase;
import org.apache.maven.plugins.annotations.Mojo;
import org.apache.maven.plugins.annotations.ResolutionScope;
import org.apache.maven.project.MavenProject;
import org.apache.maven.project.MavenProjectHelper;
import org.codehaus.plexus.archiver.jar.JarArchiver;
import org.apache.maven.plugins.annotations.LifecyclePhase;
import org.apache.maven.plugins.annotations.Mojo;
import org.apache.maven.plugins.annotations.Parameter;

import java.io.File;

/**
 * Base class for creating a jar from project classes.
 * 
 */
@Mojo(name = "packagejar", defaultPhase = LifecyclePhase.PACKAGE, threadSafe = false, requiresDependencyResolution = ResolutionScope.NONE)
public class JarMojo extends AbstractMojo {

  private static final String[] DEFAULT_EXCLUDES = new String[] { "**/package.html" };

  private static final String[] DEFAULT_INCLUDES = new String[] { "**/**" };

  /**
   * List of files to include. Specified as fileset patterns.
   * 
   * 
   */

  @Parameter()
  private String[] includes;

  /**
   * List of files to exclude. Specified as fileset patterns.
   * 
   * @parameter
   */
  @Parameter()
  private String[] excludes;

  /**
   * Directory containing the generated JAR.
   */
  @Parameter(defaultValue = "project.build.directory", required = true)
  private File outputDirectory;

  /**
   * Name of the generated JAR.
   * 
   */
  @Parameter( defaultValue = "${project.build.finalName}", alias = "jarName", required = true)
  private String finalName;

  /**
   * The Jar archiver.
   */
  @Component(role = org.codehaus.plexus.archiver.Archiver.class, hint = "jar")
  private JarArchiver jarArchiver;

  /**
   * The Maven project.
   * 
   */
  @Parameter(property = "project", required = true, readonly = true)
  private MavenProject project;

  /**
   * The archive configuration to use.
   * 
   * See <a href="http://maven.apache.org/shared/maven-archiver/index.html">the
   * documentation for Maven Archiver</a>.
   * 
   * @parameter
   */
  private MavenArchiveConfiguration archive = new MavenArchiveConfiguration();

  /**
   * Path to the default MANIFEST file to use. It will be used if
   * <code>useDefaultManifestFile</code> is set to <code>true</code>.
   * 
   * @parameter 
   *            expression="${project.build.outputDirectory}/META-INF/MANIFEST.MF"
   * @required
   * @readonly
   * @since 2.2
   */
  private File defaultManifestFile;

  /**
   * Set this to <code>true</code> to enable the use of the
   * <code>defaultManifestFile</code>.
   * 
   * @parameter expression="${jar.useDefaultManifestFile}" default-value="false"
   * 
   * @since 2.2
   */
  private boolean useDefaultManifestFile;

  /**
   * @component
   */
  private MavenProjectHelper projectHelper;

  /**
   * Whether creating the archive should be forced.
   * 
   * @parameter expression="${jar.forceCreation}" default-value="false"
   */
  private boolean forceCreation;


  protected final MavenProject getProject() {
    return project;
  }


  protected static File getJarFile(File basedir, String finalName,
                                   String classifier) {
    if (classifier == null) {
      classifier = "";
    } else if (classifier.trim().length() > 0 && !classifier.startsWith("-")) {
      classifier = "-" + classifier;
    }

    return new File(basedir, finalName + classifier + ".jar");
  }

  /**
   * Default Manifest location. Can point to a non existing file. Cannot return
   * null.
   */
  protected File getDefaultManifestFile() {
    return defaultManifestFile;
  }

  /**
   * Generates the JAR.
   * 
   * @todo Add license files in META-INF directory.
   */
  public File createArchive() throws MojoExecutionException {
    File jarFile = getJarFile(outputDirectory, finalName, getClassifier());

    MavenArchiver archiver = new MavenArchiver();

    archiver.setArchiver(jarArchiver);

    archiver.setOutputFile(jarFile);

    archive.setForced(forceCreation);

    try {
      File contentDirectory = getClassesDirectory();
      if (!contentDirectory.exists()) {
        getLog().warn("JAR will be empty - no content was marked for inclusion!");
      } else {
        archiver.getArchiver().addDirectory(contentDirectory,
                                            getIncludes(),
                                            getExcludes());
      }

      File existingManifest = getDefaultManifestFile();

      if (existingManifest != null && useDefaultManifestFile && existingManifest.exists()
          && archive.getManifestFile() == null) {
        getLog().info("Adding existing MANIFEST to archive. Found under: "
            + existingManifest.getPath());
        archive.setManifestFile(existingManifest);
      }

      archiver.createArchive(project, archive);

      return jarFile;
    } catch (Exception e) {
      // TODO: improve error handling
      throw new MojoExecutionException("Error assembling JAR", e);
    }
  }

  /**
   * Generates the JAR.
   * 
   * @todo Add license files in META-INF directory.
   */
  public void execute() throws MojoExecutionException {
    File jarFile = createArchive();

    String classifier = getClassifier();
    if (classifier != null) {
      projectHelper.attachArtifact(getProject(), getType(), classifier, jarFile);
    } else {
      getProject().getArtifact().setFile(jarFile);
    }
  }

  private String[] getIncludes() {
    if (includes != null && includes.length > 0) {
      return includes;
    }
    return DEFAULT_INCLUDES;
  }

  private String[] getExcludes() {
    if (excludes != null && excludes.length > 0) {
      return excludes;
    }
    return DEFAULT_EXCLUDES;
  }

  /**
   * Directory containing the classes.
   * 
   */
  @Parameter(property = "project.build.outputDirectory", required = true)
  private File classesDirectory;

  /**
   * Classifier to add to the artifact generated. If given, the artifact will be
   * an attachment instead.
   * 
   * @parameter
   */
  private String classifier;

  protected String getClassifier() {
    return classifier;
  }

  /**
   * @return type of the generated artifact
   */
  protected String getType() {
    return "jar";
  }

  /**
   * Return the main classes directory, so it's used as the root of the jar.
   */
  protected File getClassesDirectory() {
    return classesDirectory;
  }

}
