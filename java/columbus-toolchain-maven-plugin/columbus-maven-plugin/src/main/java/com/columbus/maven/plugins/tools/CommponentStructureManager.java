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

package com.columbus.maven.plugins.tools;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;
import java.io.StringWriter;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.Stack;
import java.util.TreeSet;
import java.util.jar.JarEntry;
import java.util.jar.JarFile;

import org.apache.maven.artifact.Artifact;
import org.apache.maven.artifact.DefaultArtifact;
import org.apache.maven.artifact.factory.ArtifactFactory;
import org.apache.maven.artifact.repository.ArtifactRepository;
import org.apache.maven.artifact.resolver.ArtifactResolver;
import org.apache.maven.artifact.versioning.VersionRange;
import org.apache.maven.plugin.MojoExecutionException;
import org.apache.maven.plugin.dependency.utils.resolvers.ArtifactsResolver;
import org.apache.maven.plugin.dependency.utils.resolvers.DefaultArtifactsResolver;
import org.apache.maven.plugin.dependency.utils.translators.ArtifactTranslator;
import org.apache.maven.plugin.dependency.utils.translators.ClassifierTypeTranslator;
import org.apache.maven.plugin.logging.Log;
import org.apache.maven.plugins.annotations.Component;
import org.apache.maven.plugins.annotations.Parameter;
import org.apache.maven.project.MavenProject;
import org.apache.maven.shared.dependency.tree.DependencyNode;
import org.apache.maven.shared.dependency.tree.traversal.DependencyNodeVisitor;

import com.columbus.maven.plugins.EnvManager;
import com.columbus.maven.plugins.tools.DependencyComponent.AnalysisType;
import com.columbus.maven.plugins.tools.DependencyComponent.IncludeType;

public class CommponentStructureManager {
	
  public static final String DEFAULT = "Default";
  
  public CommponentStructureManager(ArtifactFactory artifactFactory, Log log,
      MavenProject project, ArtifactResolver artifactResolver,
      ArtifactRepository localRepository) {
    this.artifactFactory = artifactFactory;
    this.log = log;
    this.project = project;
    this.artifactResolver = artifactResolver;
    this.localRepository = localRepository;
  }

  /**
   * This folder is contain the ljsi files.
   */
  private File ljsiDepoDir;

  /**
   * The name of the list/struct file
   */
  private File outputFile;

  private Log log;

  protected MavenProject project;

  protected ArtifactResolver artifactResolver;

  protected ArtifactRepository localRepository;

  private DependencyComponent rootNode;

  private ArtifactFactory artifactFactory;

  private DependencyComponent buildDependencyComponentTree(
      DependencyComponent compNode, DependencyNode otherRootNode, boolean nowComplied)
      throws MojoExecutionException {
    compNode.setComponentId(getComponentId(otherRootNode.getArtifact()));
    
    compNode.setDependencyKind(otherRootNode.getArtifact().getScope() == null?DEFAULT:otherRootNode.getArtifact().getScope());
    
    compNode.setIncludeType(isInclude(otherRootNode) ? IncludeType.INCLUDE
        : IncludeType.DEPEND);
    if (nowComplied) {
    	compNode.setAnalysisType(AnalysisType.CURRENT);
    	
    }
    for (Iterator<DependencyNode> idepNode = otherRootNode.getChildren()
        .iterator(); idepNode.hasNext();) {
      DependencyNode depNode = idepNode.next();
      compNode.add(buildDependencyComponentTree(new DependencyComponent(),
          depNode,false));
    }
    return compNode;
  }

  private DependencyComponent getDependencyComponentTree(
      DependencyNode otherRootNode) throws MojoExecutionException {
    return buildDependencyComponentTree(new DependencyComponent(),
        otherRootNode,true);
  }

  private boolean isInclude(DependencyNode artifact) {
    if (artifact.getParent() == null)
      return false;
    
    if (artifact.getParent().getArtifact().getArtifactHandler()
        .isIncludesDependencies()) {
      // TODO: find the better solution to decide a filter.
      if ((artifact.getArtifact().getScope() != null)
          && artifact.getArtifact().getScope().endsWith("test"))
        return false;

      return true;
    }
    return false;
  }

  public void merge(DependencyNode otherRootNode) {
    try {
      initroot();
      log.info("merge structs");
      rootNode.add(getDependencyComponentTree(otherRootNode));
      
    } catch (MojoExecutionException e) {
      e.printStackTrace();
    }
  }

  private void initroot() {
    if (rootNode == null) {
      rootNode = new DependencyComponent();
      rootNode.setComponentId("System");
      rootNode.setIncludeType(IncludeType.INCLUDE);
      rootNode.setDependencyKind(DEFAULT);
    }
  }

  public String getComponentId(Artifact arti) throws MojoExecutionException {
    String componenetID = EnvManager.getInstance().getNameByArtifact(arti);
    ArtifactTranslator translator = new ClassifierTypeTranslator(
        EnvManager.OSA_CLASSIFER_AJSI, "jar", artifactFactory);
    Set<Artifact> artifacts = new HashSet<Artifact>();
    artifacts.add(arti);

    Set<Artifact> artifactLjsis = translator.translate(artifacts, log);
    ArtifactsResolver artifactsResolver = new DefaultArtifactsResolver(
        artifactResolver, localRepository,
        project.getRemoteArtifactRepositories(), false);
    @SuppressWarnings("unchecked")
    Set<Artifact> resolvedArtifacts = artifactsResolver.resolve(artifactLjsis,
        log);

    if (!resolvedArtifacts.isEmpty()) {
      Artifact resolved = resolvedArtifacts.iterator().next();

      if (resolved.getFile() != null) {
        JarFile jarFile = null;
        try {
          jarFile = new JarFile(resolved.getFile());
          JarEntry infoFileEntry = jarFile.getJarEntry(EnvManager.getInstance()
              .getNameByArtifact(resolved)
              + EnvManager.LJSI_EXTENSION
              + EnvManager.INFO_EXTENSION);
          if (infoFileEntry != null) {
            java.io.InputStream is = jarFile.getInputStream(infoFileEntry);
            BufferedReader buffer = new BufferedReader(
                new InputStreamReader(is));
            componenetID = buffer.readLine();

          }
        } catch (IOException e) {
          e.printStackTrace();
        } finally {
          ListFileManager.closeQuietly(jarFile);
        }
      }
    }
    return componenetID;
  }

  private int indentCount ( String s) {
    int i = 0;
    
    while ((s.length() > i) && s.charAt(i) == '\t' ) {
      i++;
    }
      
    return i;
  } 
  
  public void merge(File inputfile) throws Exception{
    if (!inputfile.exists())
      return;
    
    initroot();
    
    BufferedReader inputFileReader = null;
    
    try {
      inputFileReader = new BufferedReader(new FileReader(inputfile));
      String line;
      Stack<DependencyComponent> stack = new Stack<DependencyComponent>(); 
      stack.add(rootNode);
      
      while ((line = inputFileReader.readLine()) != null) {
        int currentDepth = indentCount (line);
        if (currentDepth == 0) 
          continue;
        
        int diffDept = currentDepth - (stack .size());
        
        if (diffDept > 0) {
          throw new Exception("Bad file format");
        }
        
        for (;diffDept<0;diffDept++) {
          if (stack.empty()) {
            throw new Exception("Bad file format");
          }
          stack.pop();
        }
        
        
         
        line = line.substring(currentDepth);
        String[] splitedlines = line.split("\t");
        if (splitedlines.length != 4) {
          throw new Exception("Bad file format");
        }
        
        String componentName    = splitedlines[0];
        String aritfactIncState = splitedlines[1];
        String aritfactDepScope = splitedlines[2];
        String analysisType     = splitedlines[3];
        DependencyComponent depcomp = new DependencyComponent();
        depcomp.setComponentId(componentName);
        depcomp.setDependencyKind(aritfactDepScope);
        depcomp.setIncludeType(IncludeType.valueOf(aritfactIncState));
        depcomp.setAnalysisType(AnalysisType.valueOf(analysisType));
        
        if (!stack.empty()) {
          DependencyComponent parentComp = stack.peek();
          //if ((currentDepth > 1) || (depcomp.getIncludeType()== IncludeType.DEPEND  ))
          parentComp.add(depcomp);
          
        }
        if (currentDepth > 0 ) {
          stack.add(depcomp);
        }
        
      }

    } catch (FileNotFoundException e) {
      e.printStackTrace();

    } catch (IOException e) {
      e.printStackTrace();

    } finally {
      ListFileManager.closeQuietly(inputFileReader);
    }
  }
  
  class RealtionEntry implements Comparable<RealtionEntry>{
    public RealtionEntry(String parent, String child, String aritfactDepScope,
        IncludeType includeType , boolean nowAnalyzed) {
      super();
      this.parent = parent;
      this.child = child;
      this.aritfactDepScope = aritfactDepScope;
      this.includeType = includeType;
      this.nowAnalyzed = nowAnalyzed;
    }
    
    String parent;
    String child;
    String aritfactDepScope;
    IncludeType includeType;
    boolean nowAnalyzed ;
    
    public int compareTo(RealtionEntry o) {
      if (parent.compareTo(o.parent) != 0)
        return parent.compareTo(o.parent);
      
      if (child.compareTo(o.child) != 0)
        return child.compareTo(o.child);
      
      if (aritfactDepScope.compareTo(o.aritfactDepScope) != 0)
        return aritfactDepScope.compareTo(o.aritfactDepScope);
      
      return includeType.compareTo( o.includeType);
        
      
    }
  }
  
  public void normalize (){
   
    
    //build a set 
    final Set<RealtionEntry> relationSet = new TreeSet<RealtionEntry>();
    
    DependencyComponentVisitor visitor = new DependencyComponentVisitor() {

      public boolean visit(DependencyComponent node) {
        if (node.getParent() != null)   {
          relationSet.add(new RealtionEntry(node.getParent().getComponentId(), node.getComponentId()
            , node.getDependencyKind(), node.getIncludeType(),node.getAnalysisType() == AnalysisType.CURRENT   ));
        }
        return true;
      }

      public boolean endVisit(DependencyComponent node) {
        return true;
      }
    };
    
    rootNode.accept(visitor);
    Set<String> nowAnalyzedArtifacts = new HashSet<String>();
   
    Map<String,DependencyComponent> dependencyComponentMap = new HashMap<String,DependencyComponent>();
    for(RealtionEntry e:relationSet){
      DependencyComponent parent =  dependencyComponentMap.get(e.parent);
      DependencyComponent child  =  dependencyComponentMap.get(e.child);
      if (parent == null ) {
        parent = new DependencyComponent();
        parent.setComponentId(e.parent);
        parent.setDependencyKind(DEFAULT);
        parent.setIncludeType(IncludeType.DEPEND);
        if (child != null){
        	boolean nowAnalyzed = false;
        	if (e.nowAnalyzed) {
          		nowAnalyzedArtifacts.add(child.getComponentId());
          		nowAnalyzed = true;
          	}
        	nowAnalyzed = nowAnalyzed || nowAnalyzedArtifacts.contains(child.getComponentId()); 
        	child.setAnalysisType(nowAnalyzed ? AnalysisType.CURRENT:AnalysisType.NONE);
        }
        dependencyComponentMap.put(e.parent , parent );
      }
      /*
      if (   (child.getParent().getComponentId().equals(parent.getComponentId())) 
          && (child.getParent().getDependencyKind().equals(parent.getDependencyKind()))
          && (child.getIncludeType() == IncludeType.DEPEND)
          &&   (e.includeType == IncludeType.INCLUDE)
          )  {
        child.setIncludeType(IncludeType.INCLUDE);
        continue;
      }
      */
      if ( child  == null  || (child.getParent() != null)) {
        child  = new DependencyComponent();
        if (!dependencyComponentMap.containsKey(e.child)) {
          dependencyComponentMap.put(e.child, child);
        }
      }
      
      child.setComponentId(e.child);
      child.setDependencyKind(e.aritfactDepScope);
      child.setIncludeType(e.includeType);
      if (child != null){
    	boolean nowAnalyzed = false;
      	if (e.nowAnalyzed) {
        		nowAnalyzedArtifacts.add(child.getComponentId());
        		nowAnalyzed = true;
        }
      	nowAnalyzed = nowAnalyzed || nowAnalyzedArtifacts.contains(child.getComponentId());
      	child.setAnalysisType(nowAnalyzed ? AnalysisType.CURRENT:AnalysisType.NONE);
      	
      }
      parent.add(child);
      
    }
    DependencyComponent newRoot = dependencyComponentMap.get(rootNode.getComponentId());
    rootNode = newRoot;
  }
  
  public String serialiseDependencyTree() {
    normalize();
    final StringWriter writer = new StringWriter();
    final Set<String> artifacts = new TreeSet<String>();
    final Set<String> currentArtifacts = new TreeSet<String>();
    final Set<String> artifactsInc = new HashSet<String>();
    artifactsInc.add(rootNode.getComponentId());
    DependencyComponentVisitor visitor = new DependencyComponentVisitor() {

      private int indent = 0;

      public boolean visit(DependencyComponent node) {

        artifacts.add(node.getComponentId());
        
        if (node.getAnalysisType() == AnalysisType.CURRENT) {
        	currentArtifacts.add(node.getComponentId());
        }
        
        if(   (node.getParent() == rootNode) 
           && (node.getIncludeType() == IncludeType.DEPEND)
           && (node.isEmpty())
           ){
           indent++;
           return true;
        }
        if (node.getIncludeType() == IncludeType.INCLUDE) {
          artifactsInc.add(node.getComponentId());
        }
        
        for (int i = 0; i < indent; i++) {
          writer.append("\t");
        }
        writer.append(node.toString());
        
        writer.append("\n");
        indent++;
        return true;
      }

      public boolean endVisit(DependencyComponent node) {
        indent--;
        return true;
      }
    };

    rootNode.accept(visitor);

    artifacts.removeAll(artifactsInc);
    
    for (String artifact : artifacts) {
        writer.append("\t");
        writer.append(artifact);
        writer.append("\t");
        writer.append(IncludeType.INCLUDE.toString());
        writer.append("\t");
        writer.append(DEFAULT);
        writer.append("\t");
        if (currentArtifacts.contains(artifact)) {
        	writer.append(AnalysisType.CURRENT.toString());
        }else{
        	writer.append(AnalysisType.NONE.toString());
        }
        
        writer.append("\n");
    }

    return writer.toString();
  }

}
