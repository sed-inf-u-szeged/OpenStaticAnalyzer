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

import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;

import org.apache.maven.shared.dependency.tree.DependencyNode;
import org.apache.maven.shared.dependency.tree.traversal.DependencyNodeVisitor;

public class DependencyComponent implements Comparable<DependencyComponent> {
 
  public int compareTo(DependencyComponent o) {
    if (componentId.compareTo(o.componentId) != 0) {
      return componentId.compareTo(o.componentId);
    }
    if (dependencyKind.compareTo(o.dependencyKind) != 0){
      return dependencyKind.compareTo(o.dependencyKind);
    }
    
    if (includeType.compareTo(o.includeType) != 0){
      return includeType.compareTo(o.includeType);
    }
    
    return 0;
  }
  
  private int nullHashCode( Object a )
  {
      return ( a == null ) ? 0 : a.hashCode();
  }

  
  @Override
  public int hashCode() {
    int hashCode = 1;
   
    hashCode = hashCode * 31 + nullHashCode(componentId);
    hashCode = hashCode * 31 + nullHashCode(includeType);
    hashCode = hashCode * 31 + nullHashCode(dependencyKind);

    return hashCode;
  }

  @Override
  public boolean equals(Object object ) {
    boolean equal;

    if ( object instanceof DependencyComponent )
    {
      DependencyComponent node = (DependencyComponent) object;

        // TODO: no parent.equals() to prevent recursion
        equal = componentId.equals( node.componentId );
        equal &= includeType.equals( node.includeType);
        // DefaultArtifact.hashCode does not consider scope
        equal &=  dependencyKind.equals( node.dependencyKind );
        
      
    }
    else
    {
        equal = false;
    }

    return equal;
  }

  public enum IncludeType {
    DEPEND,INCLUDE
  }
  
  public enum  AnalysisType {
	  CURRENT, FORMER, NONE
  }
  
  private String componentId;
  
  private IncludeType includeType;
  
  private String dependencyKind;
 
  private AnalysisType analysisType; 
  
  public AnalysisType getAnalysisType() {
	return analysisType;
  }

  public void setAnalysisType(AnalysisType analysisType) {
	this.analysisType = analysisType;
  }

/**
   * The list of child dependency nodes of this dependency node.
   */
  private Set<DependencyComponent> children;

  public boolean isEmpty() {
    return children.isEmpty();
  }

  public Iterator<DependencyComponent> iterator() {
    return children.iterator();
  }

  public boolean add(DependencyComponent e) {
    e.setParent(this);
    
    if (!children.add(e) ) {
    	if (e.getAnalysisType() == AnalysisType.CURRENT) {
    		children.remove(e);
    	} 
    } else {
    	return true;
    }
    return children.add(e);
    
  }

  /**
   * The parent dependency node of this dependency node.
   */
  private DependencyComponent parent;
  
  public DependencyComponent getParent() {
    return parent;
  }

  private void setParent(DependencyComponent parent) {
    this.parent = parent;
  }

  public String toString(){
    return componentId+"\t"+includeType.toString()+"\t"+dependencyKind+"\t"+analysisType.toString();
  }

  public String getComponentId() {
    return componentId;
  }

  public void setComponentId(String componentId) {
    this.componentId = componentId;
  }

  public IncludeType getIncludeType() {
    return includeType;
  }

  public void setIncludeType(IncludeType includeType) {
    this.includeType = includeType;
  }

  public String getDependencyKind() {
    return dependencyKind;
  }

  public void setDependencyKind(String dependencyKind) {
    this.dependencyKind = dependencyKind;
  }

  public DependencyComponent(){
    children = new TreeSet<DependencyComponent>();
    analysisType = AnalysisType.NONE;
  } 
  
  public boolean accept( DependencyComponentVisitor visitor )
  {
      if ( visitor.visit( this ) )
      {
          boolean visiting = true;

          for ( Iterator iterator = children.iterator(); visiting && iterator.hasNext(); )
          {
            DependencyComponent child = (DependencyComponent) iterator.next();

              visiting = child.accept( visitor );
          }
      }

      return visitor.endVisit( this );
  }


 

    
}
