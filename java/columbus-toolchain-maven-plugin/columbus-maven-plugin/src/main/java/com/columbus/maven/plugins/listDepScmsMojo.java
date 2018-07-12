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

import java.io.Closeable;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.PrintStream;
import java.io.UnsupportedEncodingException;

import org.apache.maven.artifact.Artifact;
import org.apache.maven.model.Model;
import org.apache.maven.model.io.xpp3.MavenXpp3Reader;
import org.apache.maven.plugin.AbstractMojo;
import org.apache.maven.plugin.MojoExecutionException;
import org.apache.maven.plugin.MojoFailureException;
import org.apache.maven.plugins.annotations.LifecyclePhase;
import org.apache.maven.plugins.annotations.Mojo;
import org.apache.maven.plugins.annotations.Parameter;
import org.apache.maven.plugins.annotations.ResolutionScope;
import org.apache.maven.project.MavenProject;
import org.apache.maven.project.artifact.ProjectArtifactFactory;

@Mojo(name = "listDependencies", threadSafe = true,requiresDependencyResolution = ResolutionScope.COMPILE_PLUS_RUNTIME)
public class listDepScmsMojo extends AbstractColumbusMojo {

  @Parameter(property = "listFileName", defaultValue = "${project.build.directory}/depList.txt")
  protected File listFileName;

  public void execute() throws MojoExecutionException, MojoFailureException {
    PrintStream fileStream = null;
    try {
      fileStream = new PrintStream(listFileName,"UTF-8");
      
      
      for (Object oLine : project.getArtifacts()) {
        // Deal with the line
        Artifact line = (Artifact) oLine;
        fileStream.print(line.getGroupId() + ":" + line.getArtifactId() + ":"
            + line.getVersion());
        fileStream.print(";");
        
        File pomFile = line.getFile();
        pomFile = new File(pomFile.toString().substring(0, pomFile.toString().lastIndexOf("."))+".pom");
        
        //fileStream.print(pomFile+";");
        
        Model model = null;
        FileReader reader = null;
        MavenXpp3Reader mavenreader = new MavenXpp3Reader();
        try {
          reader = new FileReader(pomFile);
          model = mavenreader.read(reader);
        
          MavenProject project = new MavenProject(model);
          if (project.getScm() != null ) {
            fileStream.print(project.getScm().getUrl());
          }
        
        } catch (Exception ex) {
          fileStream.println();
        }
        
        fileStream.println();
      }

    } catch (FileNotFoundException e) {
      e.printStackTrace();
    } catch (UnsupportedEncodingException e) {
      e.printStackTrace();
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