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

package com.columbus.maven.executor;

import java.util.List;
import java.util.Map;

import org.apache.maven.execution.MavenSession;
import org.apache.maven.model.Plugin;
import org.apache.maven.model.PluginExecution;
import org.apache.maven.plugin.AbstractMojo;
import org.apache.maven.plugin.BuildPluginManager;
import org.apache.maven.plugin.InvalidPluginDescriptorException;
import org.apache.maven.plugin.MojoExecution;
import org.apache.maven.plugin.MojoExecutionException;
import org.apache.maven.plugin.MojoFailureException;
import org.apache.maven.plugin.PluginConfigurationException;
import org.apache.maven.plugin.PluginDescriptorParsingException;
import org.apache.maven.plugin.PluginManagerException;
import org.apache.maven.plugin.PluginNotFoundException;
import org.apache.maven.plugin.PluginResolutionException;
import org.apache.maven.plugin.descriptor.MojoDescriptor;
import org.apache.maven.plugin.descriptor.PluginDescriptor;
import org.apache.maven.plugin.version.DefaultPluginVersionRequest;
import org.apache.maven.plugin.version.PluginVersionRequest;
import org.apache.maven.plugin.version.PluginVersionResolutionException;
import org.apache.maven.plugin.version.PluginVersionResolver;
import org.apache.maven.plugins.annotations.Component;
import org.apache.maven.plugins.annotations.Parameter;
import org.apache.maven.project.MavenProject;
import org.codehaus.plexus.util.xml.Xpp3Dom;
import org.eclipse.aether.RepositorySystemSession;
import org.eclipse.aether.repository.RemoteRepository;
import org.codehaus.plexus.util.xml.Xpp3DomUtils;
import org.codehaus.plexus.component.repository.exception.ComponentLookupException;

import static com.columbus.maven.executor.PlexusConfigurationUtils.toXpp3Dom;

public abstract class MojoExecutorFacilitiesAbstarctMojo extends AbstractMojo {

  
  public static class Element {
    private final Element[] children;
    private final String name;
    private final String text;

    public Element(final String name, final Element... children) {
      this(name, null, children);
    }

    public Element(final String name, final String text,
        final Element... children) {
      this.name = name;
      this.text = text;
      this.children = children;
    }

    public Xpp3Dom toDom() {
      final Xpp3Dom dom = new Xpp3Dom(name);
      if (text != null) {
        dom.setValue(text);
      }
      for (final Element e : children) {
        dom.addChild(e.toDom());
      }
      return dom;
    }

    @Override
    public String toString() {
      StringBuilder sb = new StringBuilder();
      sb.append("name=");
      sb.append(name);
      sb.append(" value=");
      sb.append(text);
      if (children != null && children.length > 0) {
        sb.append(" children=[");
        for (final Element e : children) {
          sb.append(e.toString());
          sb.append("|");
        }
        sb.append("]");
      }
      return sb.toString();
    }
  }

  public static Element element(final String name, final Element... elements) {
    return new Element(name, elements);
  }

  public static Element element(final String name, final String value) {
    return new Element(name, value);
  }

  public Plugin plugin(final String groupId, final String artifactId) throws PluginVersionResolutionException {
    Plugin plugin = plugin(groupId, artifactId, null);
    
    if (plugin.getVersion() == null) {
      resolvePluginVersion(plugin,mavenSession,project);
    }
    return plugin;
  }

  
  private void resolvePluginVersion( Plugin plugin, MavenSession session, MavenProject project )
      throws PluginVersionResolutionException
  {
      PluginVersionRequest versionRequest =
          new DefaultPluginVersionRequest( plugin, session.getRepositorySession(),
                                           project.getRemotePluginRepositories() );
                                           
        if (pluginVersionResolver == null) {
        try {
            pluginVersionResolver = (PluginVersionResolver)mavenSession.lookup("org.apache.maven.plugin.version.PluginVersionResolver");
        } catch (ComponentLookupException e) {
            throw new NullPointerException();
        }
        
        }
        
      plugin.setVersion( pluginVersionResolver.resolve( versionRequest ).getVersion() );
  }
  
  public Plugin plugin(final String groupId, final String artifactId,
      final String version) {
    
    final Plugin plugin = new Plugin();
    plugin.setArtifactId(artifactId);
    plugin.setGroupId(groupId);
    plugin.setVersion(version);
     
    return plugin;
  }

  private static final String FAKE_EXECUTION_ID = "virtual-execution";
  
  @Component
  private PluginVersionResolver pluginVersionResolver;
  
  @Component
  protected BuildPluginManager buildPluginManager;

  @Parameter(defaultValue = "${session}", readonly = true, required = true)
  protected MavenSession mavenSession;

  @Parameter(defaultValue = "${project}", readonly = true, required = true)
  protected MavenProject project;

  @Parameter(defaultValue = "${repositorySystemSession}", readonly = true)
  private RepositorySystemSession repoSession;

  public void executeMojo(final Plugin plugin, String goal,
      final Xpp3Dom configuration) throws MojoExecutionException {
  
    Map<String, PluginExecution> executionMap = null;

    try {
      final List<?> buildPlugins = project.getBuildPlugins();

      String executionId = null;

      if ((goal != null) && (goal.length() > 0) && (goal.indexOf('#') > -1)) {
        final int pos = goal.indexOf('#');
        executionId = goal.substring(pos + 1);
        goal = goal.substring(0, pos);
      }

      if ((buildPlugins != null) && (executionId == null)) {
        for (final Object buildPlugin : buildPlugins) {
          final Plugin pomPlugin = (Plugin) buildPlugin;

          if (plugin.getGroupId().equals(pomPlugin.getGroupId())
              && plugin.getArtifactId().equals(pomPlugin.getArtifactId())) {
            final PluginExecution exec = new PluginExecution();
            exec.setConfiguration(configuration);
            executionMap = pomPlugin.getExecutionsAsMap();
            executionMap.put(FAKE_EXECUTION_ID, exec);
            executionId = FAKE_EXECUTION_ID;
          }
        }
      }
       
         if (buildPluginManager == null) {
        try {
            buildPluginManager = (BuildPluginManager)mavenSession.lookup("org.apache.maven.plugin.BuildPluginManager");
        } catch (ComponentLookupException e) {
            throw new NullPointerException();
        }
        
        }
       repoSession = mavenSession.getRepositorySession() ;
      final PluginDescriptor pluginDescriptor = buildPluginManager.loadPlugin(
          plugin, project.getRemotePluginRepositories(), repoSession);
      
      final MojoDescriptor mojoDescriptor = pluginDescriptor.getMojo(goal);
      if (mojoDescriptor == null) {
        throw new MojoExecutionException("Unknown mojo goal: " + goal);
      }
      final MojoExecution exec = mojoExecution(mojoDescriptor, executionId,
          configuration);
      /*
       * System.out.println("tp1" + exec.toString() + "goal:  " +
       * plugin.getGroupId() + ":" + plugin.getArtifactId() + ":" + goal +
       * " config " + configuration.toString());
       */
        
      buildPluginManager.executeMojo(mavenSession, exec);
    } catch (final Exception e) {

      throw new MojoExecutionException("Unable to execute mojo"
          + e.getMessage(), e);
    } finally {
      if (executionMap != null) {
        executionMap.remove(FAKE_EXECUTION_ID);
      }
    }

  }

  private static MojoExecution mojoExecution(
      MojoDescriptor mojoDescriptor, String executionId,
      Xpp3Dom configuration) {
      configuration = Xpp3DomUtils.mergeXpp3Dom(configuration, toXpp3Dom(mojoDescriptor.getMojoConfiguration()));
      return new MojoExecution(mojoDescriptor, configuration);
  }
  
  /**
   * @param plugin
   * @param goal
   * @param configurationElements
   * @throws MojoExecutionException
   * @throws PluginManagerException 
   * @throws PluginConfigurationException 
   * @throws InvalidPluginDescriptorException 
   * @throws PluginDescriptorParsingException 
   * @throws PluginResolutionException 
   * @throws MojoFailureException 
   * @throws PluginNotFoundException 
   */
  public void executeMojo(final Plugin plugin, final String goal,
                          final Element... configurationElements)
      throws MojoExecutionException {
    
    Xpp3Dom xmlConfig = project.getGoalConfiguration (plugin.getGroupId(),
        plugin.getArtifactId(),
        FAKE_EXECUTION_ID,
        goal);
    
    executeMojo(plugin,
                goal,
                configuration(configurationElements));
  }

  /**
   * @param plugin
   * @param goal
   * @param configurationElements
   * @param xmlConfig
   *          merget into this
   * @throws MojoExecutionException
   * @throws PluginManagerException 
   * @throws PluginConfigurationException 
   * @throws InvalidPluginDescriptorException 
   * @throws PluginDescriptorParsingException 
   * @throws PluginResolutionException 
   * @throws MojoFailureException 
   * @throws PluginNotFoundException 
   */
  public void executeMojo(final Plugin plugin, final String goal,
                          final Xpp3Dom xmlConfig,
                          final Element... configurationElements)
      throws MojoExecutionException {
    
    executeMojo(plugin,
                goal,
                configuration(xmlConfig, configurationElements));
  }
  
  public static Xpp3Dom configuration(final Element... elements) {
    return configuration(null, elements);
  }

  public static Xpp3Dom configuration(Xpp3Dom dom, final Element... elements) {

    if (dom == null) {
      dom = new Xpp3Dom("configuration");
    }
    for (final Element e : elements) {
      dom.addChild(e.toDom());
    }
    return dom;
  }

   protected boolean is3XMaven() {
    
    return true;
  }
}
