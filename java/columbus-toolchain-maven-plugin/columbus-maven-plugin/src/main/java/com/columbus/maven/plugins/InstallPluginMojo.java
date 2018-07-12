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

import java.util.HashSet;
import java.util.List;
import java.util.Set;

import org.apache.maven.artifact.Artifact;
import org.apache.maven.artifact.repository.metadata.ArtifactRepositoryMetadata;
import org.apache.maven.artifact.repository.metadata.GroupRepositoryMetadata;
import org.apache.maven.artifact.repository.metadata.RepositoryMetadataStoreException;
import org.apache.maven.artifact.repository.metadata.Versioning;
import org.apache.maven.plugin.AbstractMojo;
import org.apache.maven.plugin.MojoExecutionException;
import org.apache.maven.plugin.MojoFailureException;
import org.apache.maven.plugin.dependency.utils.resolvers.ArtifactsResolver;
import org.apache.maven.plugin.dependency.utils.resolvers.DefaultArtifactsResolver;
import org.apache.maven.plugins.annotations.Mojo;
import org.apache.maven.plugins.annotations.Parameter;

@Mojo(name = "installyourself", requiresProject = false, threadSafe = true)
public class InstallPluginMojo extends AbstractColumbusMojo {

  @Parameter(defaultValue = "${project.artifact}", required = true, readonly = true)
  private Artifact artifact;
  
  public void execute() throws MojoExecutionException, MojoFailureException {
      try {
        List<?> remoteReposList = project.getRemoteArtifactRepositories();
        // resolve the rest of the artifacts
        ArtifactsResolver artifactsResolver = new DefaultArtifactsResolver(
            artifactResolver, localRepository, remoteReposList, false);

        Set<Artifact> artifacts = new HashSet<Artifact>();
        artifact.setArtifactId(MY_PLUGIN_NAME);
        artifact.setGroupId(MY_PLUGIN_GROUP_NAME);
        artifact.setVersion(MY_PLUGIN_VERSION );
        artifacts.add(artifact);

        Set<?> resolvedArtifacts = artifactsResolver.resolve(artifacts,
            getLog());

        Artifact resolvedArtifact = (Artifact) resolvedArtifacts.iterator()
            .next();

        // ArtifactRepositoryMetadata
        GroupRepositoryMetadata metadata = new GroupRepositoryMetadata(
            MY_PLUGIN_GROUP_NAME);
        metadata.addPluginMapping(MY_PLUGIN_PREFIX, MY_PLUGIN_NAME);
        metadata.storeInLocalRepository(localRepository, localRepository);
        Versioning version = new Versioning();
        version.addVersion(resolvedArtifact.getVersion());
        version.setLatest(resolvedArtifact.getVersion());
        ArtifactRepositoryMetadata artiMeta = new ArtifactRepositoryMetadata(
            resolvedArtifact, version);
        artiMeta.storeInLocalRepository(localRepository, localRepository);
      } catch (RepositoryMetadataStoreException e) {
        e.printStackTrace();
      }
  }
}