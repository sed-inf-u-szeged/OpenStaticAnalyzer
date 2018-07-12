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

import org.apache.maven.plugin.MojoExecutionException;
import org.apache.maven.plugin.MojoFailureException;
import org.apache.maven.plugins.annotations.Execute;
import org.apache.maven.plugins.annotations.LifecyclePhase;
import org.apache.maven.plugins.annotations.Mojo;
import org.apache.maven.plugins.annotations.Parameter;
import org.apache.maven.plugins.annotations.ResolutionScope;


//@Execute(phase = LifecyclePhase.INSTALL)
@Mojo(name = "install", defaultPhase = LifecyclePhase.INSTALL, threadSafe = true, requiresDependencyResolution = ResolutionScope.COMPILE_PLUS_RUNTIME)
public class InstallMojo extends AbstractColumbusMojo {

  @Parameter (defaultValue = "${noExportGraph}"   )
  private boolean skipGraph;
  

  public void execute() throws MojoExecutionException, MojoFailureException {
    if (project.getPackaging().equals("pom")) {
      getLog().info("The"+project.getName() +" is not a jar project");
      return;
    }
    init();

    executeMojo(getMyPlugin()
        ,"install-ajsi" 
        );
    executeMojo(getMyPlugin()
        ,"install-apmd" 
        );
    
    if (!skipGraph) {
      executeMojo(getMyPlugin()
          ,"install-agraph" 
          );
    } else {
      executeMojo(getMyPlugin()
          ,"link" 
          );
      getLog().info("The graph not genarated.");
    }
  }

}
