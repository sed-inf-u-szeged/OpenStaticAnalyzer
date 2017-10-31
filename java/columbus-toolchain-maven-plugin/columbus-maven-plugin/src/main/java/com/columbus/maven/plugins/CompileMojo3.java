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
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.lang.reflect.Field;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

import org.apache.maven.artifact.Artifact;
import org.apache.maven.plugin.MojoExecutionException;
import org.apache.maven.plugin.compiler.AbstractCompilerMojo;
import org.apache.maven.plugins.annotations.LifecyclePhase;
import org.apache.maven.plugins.annotations.Mojo;
import org.apache.maven.plugins.annotations.Parameter;
import org.apache.maven.plugins.annotations.ResolutionScope;
import org.apache.maven.project.MavenProject;
import org.codehaus.plexus.compiler.Compiler;
import org.codehaus.plexus.compiler.CompilerConfiguration;
import org.codehaus.plexus.compiler.CompilerError;
import org.codehaus.plexus.compiler.CompilerException;
import org.codehaus.plexus.compiler.CompilerOutputStyle;
import org.codehaus.plexus.compiler.CompilerResult;
import org.codehaus.plexus.compiler.manager.CompilerManager;
import org.codehaus.plexus.compiler.manager.NoSuchCompilerException;
import org.codehaus.plexus.compiler.util.scan.SimpleSourceInclusionScanner;
import org.codehaus.plexus.compiler.util.scan.SourceInclusionScanner;
import org.codehaus.plexus.compiler.util.scan.StaleSourceScanner;

@Mojo(name = "compileArgs3", defaultPhase = LifecyclePhase.COMPILE, threadSafe = true, requiresDependencyResolution = ResolutionScope.COMPILE_PLUS_RUNTIME )
public class CompileMojo3 extends AbstractCompilerMojo {


  public class ColumbusCompilerWrapper implements
      org.codehaus.plexus.compiler.Compiler {

    public ColumbusCompilerWrapper(org.codehaus.plexus.compiler.Compiler orig,
        String outputArgFile) {
      original = orig;
      this.outputArgFile = outputArgFile;
    }

    private org.codehaus.plexus.compiler.Compiler original;
    private String outputArgFile;

    public boolean canUpdateTarget(CompilerConfiguration arg0)
        throws CompilerException {

      return original.canUpdateTarget(arg0);
    }

    public String[] createCommandLine(CompilerConfiguration arg0)
        throws CompilerException {

      return original.createCommandLine(arg0);
    }


    public CompilerOutputStyle getCompilerOutputStyle() {
      return original.getCompilerOutputStyle();
    }


    public String getInputFileEnding(CompilerConfiguration arg0)
        throws CompilerException {

      return original.getInputFileEnding(arg0);
    }


    public String getOutputFile(CompilerConfiguration arg0)
        throws CompilerException {

      return original.getOutputFile(arg0);
    }

    public String getOutputFileEnding(CompilerConfiguration arg0)
        throws CompilerException {

      return original.getOutputFileEnding(arg0);
    }


    public CompilerResult performCompile(CompilerConfiguration arg0)
        throws CompilerException {
      CompilerResult result = new CompilerResult();

      PrintWriter writer = null;
      if (outputArgFile != null) {
        try {
          writer = new PrintWriter(outputArgFile,
                                   "UTF-8");
        } catch (FileNotFoundException e) {
          writer = null;
          e.printStackTrace();
        } catch (UnsupportedEncodingException e) {
          e.printStackTrace();
          writer = null;
        }
      }
      String[] cmdline = original.createCommandLine(arg0);
      boolean nextSkip = false;
      boolean nextIsSource = false;
      boolean nextIsEnc = false;
      boolean first = true;
      
      for (String s : cmdline) {

        if (nextSkip) {
          nextSkip = false;
          continue;
        }

        if (s.equals("-d")) {
          nextSkip = true;
          continue;
        }


        if (nextIsSource ) {
        	EnvManager.getInstance().setLastAnalyzedSource(s);
        	nextIsSource = false ;
        }

        if (s.equals("-source")) {
          nextIsSource = true;
        }

        if (nextIsEnc ) {
        	EnvManager.getInstance().setLastAnalyzedEnc (s);
        	nextIsEnc = false ;
        }

        if (s.equals("-encoding")) {
          nextIsEnc = true;
        }
        
        

        if (writer != null) {
          writer.print((first ? "" : " ") + "\""+ s+"\"");
        }
        first = false;
      }

      if (writer != null) {
        writer.close();
      }


      result.setSuccess(true);
      return result;
    }

    public List<CompilerError> compile(CompilerConfiguration arg0)
        throws CompilerException {
      return null;
    }

  }

  public class CompilerManagerWrapper implements CompilerManager {
    private CompilerManager original;
    private String outputArgFile;

    public CompilerManagerWrapper(CompilerManager orig, String outputArgFile) {
      original = orig;
      this.outputArgFile = outputArgFile;
    }


    public Compiler getCompiler(String arg0) throws NoSuchCompilerException {
      return new ColumbusCompilerWrapper(original.getCompiler(arg0),
                                         outputArgFile);
    }

  }

  @Parameter(defaultValue = "${project}", readonly = true, required = true)
  protected MavenProject project;

  public void execute() {
    PrintWriter writer = null;
    if (outputClassFile != null) {
      try {
        writer = new PrintWriter(outputClassFile, "UTF-8");

        for (String s : classpathElements) {
          writer.println(s);
        }

      } catch (FileNotFoundException e) {
        writer = null;
        e.printStackTrace();
      } catch (UnsupportedEncodingException e) {
        e.printStackTrace();
        writer = null;
      }

      if (writer != null) {
        writer.close();
      }
    }

    EnvManager.getInstance().init(project.getBuild().getOutputDirectory(),
                                  project,
                                  null,
                                  null,
                                  null,
                                  getLog());
    Field privateStringField;
    try {
      privateStringField = AbstractCompilerMojo.class.getDeclaredField("compilerManager");
      privateStringField.setAccessible(true);



      CompilerManager fieldValue = (CompilerManager) privateStringField.get(this);
      CompilerManager cm = new CompilerManagerWrapper(fieldValue, outputArgFile);
      privateStringField.set(this, cm);


      try {
        super.execute();
      } catch (MojoExecutionException e) {
        e.printStackTrace();
      } catch (org.apache.maven.plugin.compiler.CompilationFailureException e) {
        e.printStackTrace();
      }

    } catch (SecurityException e) {
      e.printStackTrace();
    } catch (IllegalArgumentException e) {
      e.printStackTrace();
    } catch (NoSuchFieldException e) {
      e.printStackTrace();
    } catch (IllegalAccessException e) {
      e.printStackTrace();
    }

    if (outputDirectory.isDirectory()) {
      projectArtifact.setFile(outputDirectory);
    }

  }

  /**
   * The source directories containing the sources to be compiled.
   */
  @Parameter(defaultValue = "${outputArgFile}")
  private String outputArgFile;

  /**
   * The source directories containing the sources to be compiled.
   */
  @Parameter(defaultValue = "${outputClassFile}")
  private String outputClassFile;

  /**
   * The source directories containing the sources to be compiled.
   */
  @Parameter(defaultValue = "${project.compileSourceRoots}", readonly = true, required = true)
  private List<String> compileSourceRoots;

  /**
   * Project classpath.
   */
  

  
  @Parameter(defaultValue = "${project.compileClasspathElements}", readonly = true, required = true)
  private List<String> classpathElements;

  /**
   * The directory for compiled classes.
   */
  @Parameter(defaultValue = "${project.build.outputDirectory}", required = true, readonly = true)
  private File outputDirectory;

  /**
   * Projects main artifact.
   * 
   * @todo this is an export variable, really
   */
  @Parameter(defaultValue = "${project.artifact}", readonly = true, required = true)
  private Artifact projectArtifact;

  /**
   * A list of inclusion filters for the compiler.
   */
  @Parameter
  private Set<String> includes = new HashSet<String>();

  /**
   * A list of exclusion filters for the compiler.
   */
  @Parameter
  private Set<String> excludes = new HashSet<String>();

  /**
   * <p>
   * Specify where to place generated source files created by annotation
   * processing. Only applies to JDK 1.6+
   * </p>
   * 
   * @since 2.2
   */
  @Parameter(defaultValue = "${project.build.directory}/generated-sources/annotations")
  private File generatedSourcesDirectory;

  protected List<String> getCompileSourceRoots() {
    return compileSourceRoots;
  }

  protected List<String> getClasspathElements() {

    return classpathElements;
  }

  protected File getOutputDirectory() {
    return new File(EnvManager.getInstance().getAnalyseOutputDir());
  }

  protected SourceInclusionScanner getSourceInclusionScanner(int staleMillis) {
    SourceInclusionScanner scanner = null;

    if (includes.isEmpty() && excludes.isEmpty()) {
      scanner = new StaleSourceScanner(staleMillis);
    } else {
      if (includes.isEmpty()) {
        includes.add("**/*.java");
      }
      scanner = new StaleSourceScanner(staleMillis, includes, excludes);
    }

    return scanner;
  }

  protected SourceInclusionScanner getSourceInclusionScanner(String inputFileEnding) {
    SourceInclusionScanner scanner = null;

    // it's not defined if we get the ending with or without the dot '.'
    String defaultIncludePattern = "**/*"
        + (inputFileEnding.startsWith(".") ? "" : ".") + inputFileEnding;

    if (includes.isEmpty() && excludes.isEmpty()) {
      includes = Collections.singleton(defaultIncludePattern);
      scanner = new SimpleSourceInclusionScanner(includes,
                                                 Collections.<String> emptySet());
    } else {
      if (includes.isEmpty()) {
        includes.add(defaultIncludePattern);
      }
      scanner = new SimpleSourceInclusionScanner(includes, excludes);
    }

    return scanner;
  }

  protected String getSource() {
    return source;
  }

  protected String getTarget() {
    return target;
  }

  protected String getCompilerArgument() {
    return compilerArgument;
  }

  protected Map<String, String> getCompilerArguments() {
    return compilerArguments;
  }

  protected File getGeneratedSourcesDirectory() {
    return generatedSourcesDirectory;
  }


}
