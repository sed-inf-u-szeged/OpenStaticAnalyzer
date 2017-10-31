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

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.URL;
import java.net.URLDecoder;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.jar.JarEntry;
import java.util.jar.JarFile;

import org.apache.maven.artifact.Artifact;
import org.apache.maven.project.MavenProject;


public class EnvManager {
  public static final String WRAPPER_LOG_DIR = "WRAPPER_LOG_DIR";
	private static final String ENV_MAVEN_FILTER = "OSA_WRAPPER_MAVEN_FILTER";
	public static final String TOOLCHAIN_DIR_ENV = "OSA_DIR";
	public static final String SUPERLINKLIST_DIR_ENV = "OSA_SUPERLINKLIST";
	public static final String SUPERPMDLIST_DIR_ENV = "OSA_SUPERPMDLIST";
	public static final String OSA_FILTER_COMPONENTLIST = "OSA_FILTER_COMPONENTLIST";
	public static final String SUPERCOMPONENTLIST_ENV = "OSA_CREATE_COMPONENTLIST";
	public static final String OSA_LOG_DIR = "OSA_LOG_DIR";
	public static final String OSA_CLASSIFER_AJSI = "OpenStaticAnalyzer-ajsi";
	public static final String OSA_CLASSIFER_APMD = "OpenStaticAnalyzer-apmd";
	public static final String OSA_CLASSIFER_AGRAP = "OpenStaticAnalyzer-agraph";
	public static final String ENV_WRAPPER_BIN_DIR = "WRAPPER_BIN_DIR";
	public static final String ENV_WRAPPER_WORK_DIR = "WRAPPER_WORK_DIR";
	
	public static final String OSA_MAVEN_ADD_FULL_SRC_DIR = "OSA_MAVEN_ADD_FULL_SRC_DIR";
    public static final String OSA_MAVEN_ADD_WHOLE_SRC_DIR = "OSA_MAVEN_ADD_WHOLE_SRC_DIR";
    
    public static final String OSA_MAVEN_VCS_SRC_DIR = "OSA_MAVEN_VCS_SRC_DIR";
    public static final String PROJECT_BASE_DIR = "PROJECT_BASE_DIR";
    
	public static final String CLASSIFER_SOURCES = "sources";
	public static final String LJSI_EXTENSION = ".ljsi";
	public static final String INFO_EXTENSION = ".info";

	private static final EnvManager instance = new EnvManager();
	private String includeDependenciesGroupIds;
	private boolean analyzeResovableDep;
	private boolean deployTheDept;
	private boolean createGraphDump;
	private boolean buildComponentStructure;
	private org.apache.maven.plugin.logging.Log defaultLogger;

  public void setDefaultLogger(org.apache.maven.plugin.logging.Log defaultLogger) {
    this.defaultLogger = defaultLogger;
  }

  private String lastAnalyzedSource;
	private String lastAnalyzedEnc;
	
	public String getLastAnalyzedSource() {
		return lastAnalyzedSource;
	}

	public void setLastAnalyzedSource(String lastAnalyzedSource) {
		this.lastAnalyzedSource = lastAnalyzedSource;
	}

	public String getLastAnalyzedEnc() {
		return lastAnalyzedEnc;
	}

	public void setLastAnalyzedEnc(String lastAnalyzedEnc) {
		this.lastAnalyzedEnc = lastAnalyzedEnc;
	}

	public String getToolchainIni() {
		String s = java.lang.System.getenv(ENV_WRAPPER_BIN_DIR);
		if (s == null)
			return null;

		return new File(s, "toolchain.ini").getPath();
	}

	public List<String> getJANOptions() {
		if (getToolchainIni() == null) {
			return new LinkedList<String>();
		}
		return ConfigReader.getValues(getToolchainIni(), "JAN_CALL",
				"JAN_OPTIONS");
	}

	public List<String> getJANJVMOptions() {
		if (getToolchainIni() == null) {
			return new LinkedList<String>();
		}
		return ConfigReader.getValues(getToolchainIni(), "JAN_CALL",
				"JAN_JVM_OPTS");
	}

	public String getJanStat() {
		if (getToolchainIni() == null) {
			return null;
		}
		return ConfigReader.getValue(getToolchainIni(), "STATISTICS",
				"janStatisticFile");
	}

	public String getPmdStat() {
		if (getToolchainIni() == null) {
			return null;
		}
		return ConfigReader.getValue(getToolchainIni(), "STATISTICS",
				"pmdStatisticFile");
	}

	public boolean isCreateGraphDump() {
		return createGraphDump;
	}

	public void setCreateGraphDump(boolean createGraphDump) {
		this.createGraphDump = createGraphDump;
	}

	public boolean isDeployTheDept() {
		return deployTheDept;
	}

	public void setDeployTheDept(boolean deployTheDept) {
		this.deployTheDept = deployTheDept;
	}

	private MavenProject project;
	private String outputDirectory;
	private File toolchainBinDir;
	private String OS = null;
	private String dependencyFilter = null;

	private EnvManager() {
		includeDependenciesGroupIds = null;
		analyzeResovableDep = false;
		project = null;
		deployTheDept = false;

	}

	public static EnvManager getInstance() {
		return instance;
	}

	public boolean isAnalyzeResovableDep() {
		return analyzeResovableDep;
	}

	public String getOsName() {
		if (instance.OS == null) {
			instance.OS = System.getProperty("os.name");
		}
		return instance.OS;
	}

	public boolean isWindows() {
		return getOsName().startsWith("Windows");
	}

	public boolean isLinux() {
		return getOsName().startsWith("Linux");
	}

	public String getMvnBin() {
		if (isWindows()) {
			return "mvn.bat";
		}
		return "mvn";
	}

	public String getToolchainBinDir() {
		String s = java.lang.System.getenv(TOOLCHAIN_DIR_ENV);
		if (s != null) {
			return s;
		}

		if (toolchainBinDir != null) {
			return toolchainBinDir.getAbsolutePath();
		}

		System.err.println("The toolchain dir has not set. ("
				+ TOOLCHAIN_DIR_ENV + ")");
		return null;
	}

	public String getProjectTempDir() {
		File outDir = new File(outputDirectory);
		File file2 = new File(outDir, "asg-deps");
		return file2.getPath();
	}

	public String getOutputJsiDir() {
		File outDir = new File(getAnalyseOutputDir());
		File file2 = new File(outDir, "jsi");
		return file2.getPath();
	}

	public String getTmpLjsiDir() {
		File outDir = new File(getProjectTempDir());
		File file2 = new File(outDir, "jsi");
		return file2.getPath();
	}

	public String getAnalyseOutputDir() {
		return new File(outputDirectory, "asg").getAbsolutePath();
	}

	public String getOutputPMDDir() {
		File outDir = new File(getAnalyseOutputDir());
		File file2 = new File(outDir, "PMD");
		return file2.getPath();
	}

	public String getOutputGraphDir() {
		File outDir = new File(outputDirectory);
		File file2 = new File(outDir, "Graph");
		return file2.getPath();
	}

	public String getTmpPMDDir() {
		File outDir = new File(getProjectTempDir());
		File file2 = new File(outDir, "PMDs");
		return file2.getPath();
	}

	public String getProjectLogDir() {
		if (System.getenv(OSA_LOG_DIR) != null) {
			return System.getenv(OSA_LOG_DIR);
		}

		File outDir = new File(outputDirectory);
		File file2 = new File(outDir, "log");
		return file2.getPath();
	}

	public String getExecutePMDScript() {
		File outDir = new File(getProjectTempDir());
		File file2;
		if (isLinux()) {
			file2 = new File(outDir, "executePMDScript.sh");
		} else {
			file2 = new File(outDir, "executePMDScript.bat");
		}
		return file2.getPath();
	}

	public String getArgFileName() {
		File outDir = new File(outputDirectory);
		File file2 = new File(new File(outDir, "temp"), "tmp.arg");
		return file2.getPath();
	}

	public String getWrapperToolsDir() {
		String res = java.lang.System.getenv("WRAPPER_BIN_DIR");
		if (res != null ){
			return res;
		}
		
		File outDir = new File(getToolchainBinDir());
		File file2;
		if (isWindows()) {
			file2 = new File(new File(new File(outDir, "WindowsWrapper"),
					"WrapperBins"), "Tools");
		} else {
			file2 = new File(new File(new File(outDir, "LinuxWrapper"),
					"WrapperBins"), "Tools");
		}
		 
		
		return file2.getPath();
	}

	public String getPmdConfigFile() {
		File outDir = new File(getWrapperToolsDir());
		File file2 = new File(new File(outDir, "PMD"), "PMD-config.xml");
		return file2.getPath();

	}

	public String getPmdResXml() {
		File file2 = new File(getOutputPMDDir(), getProjectId() + "-PMD.xml");
		return file2.getPath();
	}

	public String getClassPathListName() {
		File outDir = new File(getProjectTempDir());
		File file2 = new File(outDir, "cp_list.lst");
		return file2.getPath();
	}

	public String getPMDBinName() {
		if (isLinux()) {
			return "run.sh";
		} else {
			return "pmd.bat";
		}
	}

	public static String getNameOfMavenProject (MavenProject project) {
		return project.getGroupId()+"-"+project.getArtifactId()+"-"+project.getVersion();
	}
	
	public void init(String _outputDirectory, MavenProject _project,
			String _includeDependenciesGroupIds, String _dependencyFilter,
			Boolean _tryAnaliseAllDep,
			org.apache.maven.plugin.logging.Log logger) {
		try {
			String wrapperWorkDir = System.getenv(ENV_WRAPPER_WORK_DIR); 
			if (wrapperWorkDir != null) {
				outputDirectory = new File(new File(wrapperWorkDir, "OpenStaticAnalyzer" ),getNameOfMavenProject(_project)
						).getCanonicalPath();
			} else {
				outputDirectory = new File(new File(_outputDirectory, ".."),
						"OpenStaticAnalyzer").getCanonicalPath();
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
		project = _project;

		new File(getProjectTempDir()).mkdirs();
		new File(getProjectLogDir()).mkdirs();
		new File(getOutputJsiDir()).mkdirs();
		new File(getOutputPMDDir()).mkdirs();

		//

		unpackTools();

		if (_includeDependenciesGroupIds != null) {
			includeDependenciesGroupIds = _includeDependenciesGroupIds;
		}

		if (_tryAnaliseAllDep != null) {
			analyzeResovableDep = _tryAnaliseAllDep;
		}
		if (_dependencyFilter != null) {
			dependencyFilter = _dependencyFilter;
		} else if ((dependencyFilter == null)
				&& (System.getenv(ENV_MAVEN_FILTER) != null)) {
			dependencyFilter = System.getenv(ENV_MAVEN_FILTER);
		}
		defaultLogger = logger;
	}

	public String getDependencyFilter() {
		return dependencyFilter;
	}

	public String getIncludeDependenciesGroupIds() {
		return includeDependenciesGroupIds;
	}

	public String getColumbusLicenseFile() {

		return new File(getToolchainBinDir(), "LICENSE.DAT").getAbsolutePath();
	}

	public int exec(ArrayList<String> cmd, String toolName,
			org.apache.maven.plugin.logging.Log logger) {
		return exec(cmd, toolName, logger, null);
	}

	public int exec(ArrayList<String> cmd, String toolName,
			org.apache.maven.plugin.logging.Log logger, File wokrDir) {
		ProcessBuilder pb = new ProcessBuilder(cmd);
		Map<String, String> env = pb.environment();
		env.put("COLUMBUS_LICENSE_FILE", getColumbusLicenseFile());
		env.put("JAVA_HOME", getToolchainJAVA_HOME());

		env.put("Path",
				new File(getToolchainJAVA_HOME(), "bin").getAbsolutePath()
						+ File.pathSeparator + System.getenv("Path"));

		pb.redirectErrorStream(true);
		if (wokrDir != null) {
			pb.directory(wokrDir);
		}

		PrintWriter writer = null;
		Process p;
		try {
			String line;
			p = pb.start();
			BufferedReader input = new BufferedReader(new InputStreamReader(
					p.getInputStream()));

			if (logger == null) {

				if (wokrDir == null && defaultLogger != null) {
					logger = defaultLogger;
				} else {

					try {
            if (getProjectLogDir() != null) {
              new File(getProjectLogDir()).mkdirs();
              writer = new PrintWriter(new FileOutputStream(new File(getProjectLogDir(),
                                                                     toolName
                                                                         + ".log").getAbsolutePath(),
                                                            true /*
                                                                  * append =
                                                                  * true
                                                                  */));

              for (String s : cmd) {
                writer.print(s + " ");
              }
              writer.println();
              writer.println();
            } else {
              logger = defaultLogger;
            }
					} catch (FileNotFoundException e) {
						e.printStackTrace();
						writer = null;
					}
				}
			}

			
			
			if (logger != null) {
				logger.info("RUN tool [" + toolName + "] " + cmd+"\n");
			} 
			
			while ((line = input.readLine()) != null) {
				if (logger != null) {
					logger.info("[" + toolName + "] " + line);
				} else {
					writer.println(line);
				}
			}
			int retCode = p.waitFor();

			if (writer != null) {
				writer.close();
			}
      if (retCode != 0) {
        PrintWriter errorLogWriter = new PrintWriter(new FileOutputStream(new File(java.lang.System.getenv(WRAPPER_LOG_DIR), "Error.log")));
        errorLogWriter.println("RUN tool [" + toolName + "] " + cmd+" has failed\n");
        errorLogWriter.close();
      }
      
			return retCode;
		} catch (IOException e) {
			e.printStackTrace();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		return -1;
	}

	public String getNameByArtifact(Artifact artifact) {
		return artifact.getGroupId() + "-" + artifact.getArtifactId() + "-"
				+ artifact.getVersion();
	}

	public String getProjectId() {
		return getNameByArtifact(project.getArtifact());
	}

	public String getProjectLjsiFileName() {
		return new File(getOutputJsiDir(), getProjectId() + LJSI_EXTENSION)
				.getAbsolutePath();
	}

	public String getProjectLjsiDepFileName() {
		return new File(getTmpLjsiDir(), getProjectId() + ".compStruc")
				.getAbsolutePath();
	}

	public String getProjectAjsiFileNameFilepart() {
		return getProjectId() + ".ajsi";
	}

	public String getProjectApmdFileNameFilepart() {
		return getProjectId() + ".apmd";
	}

	public String getProjectApmdFileName() {
		return new File(outputDirectory, getProjectApmdFileNameFilepart())
				.getAbsolutePath();
	}

	public String getLimFileName() {
		return new File(getProjectTempDir(), getProjectId() + ".lim")
				.getAbsolutePath();
	}

	public String getDcfGraphFileName() {
		return new File(getProjectTempDir(), getProjectId() + "-DCF.graph")
				.getAbsolutePath();
	}

	public String getMetricsGraphFileName() {
		return new File(getProjectTempDir(), getProjectId() + "-metrics.graph")
				.getAbsolutePath();
	}

	public String getPmdGraphFileName() {
		return new File(getProjectTempDir(), getProjectId() + "-pmd.graph")
				.getAbsolutePath();
	}

	public String getMergedGraphFileName() {
		return new File(getOutputGraphDir(), getProjectId() + ".graph")
				.getAbsolutePath();
	}

	public String getMergedAGraphFileNameFilepart() {
		return getProjectId() + ".agraph";
	}

	public String getMergedAGraphFileName() {
		return new File(outputDirectory, getMergedAGraphFileNameFilepart())
				.getAbsolutePath();
	}

	public String getSuperLinkListFileName() {
		return new File(getProjectTempDir(), getProjectId() + "-linklist.lst")
				.getAbsolutePath();
	}

	public String getPMDListFileName() {
		return new File(getProjectTempDir(), getProjectId() + "-PMDlist.lst")
				.getAbsolutePath();
	}

	public String getProjectAjsiFileName() {
		return new File(outputDirectory, getProjectId() + ".ajsi")
				.getAbsolutePath();
	}

	public String getOpenStaticAnalyzerDir() {
		return outputDirectory;
	}

	public String getToolsDir() {
		File outDir = new File(getToolchainBinDir());
		File file2;
		if (isLinux()) {
			file2 = new File(outDir, "LinuxTools");
		} else {
			file2 = new File(outDir, "WindowsTools");
		}

		return file2.getAbsolutePath();
	}

	public String getTmpGraphDir() {
		File outDir = new File(getProjectTempDir());
		File file2 = new File(outDir, "graph");
		return file2.getPath();
	}

	public String getToolchainJAVA_HOME() {
		if (System.getenv("COLUMBUS_JAVA_HOME") != null) {
			return System.getenv("COLUMBUS_JAVA_HOME");
		}
		return System.getenv("JAVA_HOME");
	}

	private void unpackTools() {
		if (getToolchainBinDir() != null) {
			return;
		}
		try {
			URL url = getClass().getClassLoader().getResource("/META-INF");

			if ("jar".equals(url.getProtocol())) {
				String urlPath = url.getPath();
				String jarPath = urlPath.substring(5, urlPath.indexOf('!'));
				String decodedJarPath = URLDecoder.decode(jarPath, "UTF-8");
				File toolsDir = new File(decodedJarPath.substring(0,
						decodedJarPath.lastIndexOf(".jar")));

				File toolsDirRoot = new File(decodedJarPath.substring(0,
						decodedJarPath.lastIndexOf("/")));

				toolchainBinDir = new File(toolsDir,
						"META-INF/OpenStaticAnalyzer_java/");
				if (!toolchainBinDir.exists()) {

					toolchainBinDir.mkdirs();
				}

				File pomProperties = new File(toolsDirRoot,
						"maven-metadata-local.xml");
				JarFile jarFile = new JarFile(decodedJarPath);
				File sysPropertiesFile = new File(toolchainBinDir,
						"pom.properties");
				if (sysPropertiesFile.exists()) {
					java.io.InputStream jarPropertiesIs = new FileInputStream(
							pomProperties); // get
											// the
											// input
											// stream
					java.io.InputStream sysPropertiesIs = new FileInputStream(
							sysPropertiesFile); // get
												// the
												// input
												// stream
					boolean eq = true;
					while (jarPropertiesIs.available() > 0) { // write contents
																// of 'is' to
																// 'fos'
						if (jarPropertiesIs.read() != sysPropertiesIs.read()) {
							eq = false;
							break;
						}
					}
					jarPropertiesIs.close();
					sysPropertiesIs.close();
					if (eq) {
						return;
					}
				}

				java.io.InputStream jarPropertiesIs = new FileInputStream(
						pomProperties); // get
										// the
										// input
										// stream
				java.io.OutputStream sysPropertiesos = new FileOutputStream(
						sysPropertiesFile); // get
											// the
											// input
											// stream

				while (jarPropertiesIs.available() > 0) { // write contents of
															// 'is' to
															// 'fos'
					sysPropertiesos.write(jarPropertiesIs.read());
				}
				jarPropertiesIs.close();
				sysPropertiesos.close();

				boolean foundToolchainDir = false;
				Enumeration<JarEntry> entries = jarFile.entries();
				for (JarEntry entry = null; entries.hasMoreElements();) {
					entry = entries.nextElement();

					if (entry.getName()
							.startsWith("META-INF/OpenStaticAnalyzer_java/")) {
						java.io.File f = new java.io.File(toolsDir,
								entry.getName());
						foundToolchainDir = true;

						if (entry.isDirectory()) { // if its a directory, create
													// it
							f.mkdir();
							continue;
						}

						java.io.InputStream is = jarFile.getInputStream(entry); // get
																				// the
																				// input
																				// stream
						java.io.FileOutputStream fos = new java.io.FileOutputStream(
								f);
						while (is.available() > 0) { // write contents of 'is'
														// to 'fos'
							fos.write(is.read());
						}
						fos.close();
						is.close();
					}
				}
				if (!foundToolchainDir) {
					toolchainBinDir = null;
				}
			}
		} catch (IOException e) {
			e.printStackTrace();
		}

	}

	File getMainSuperlinkList() {
		String s = java.lang.System.getenv(SUPERLINKLIST_DIR_ENV);
		if (s != null) {
			return new File(s);
		}
		return null;
	}

	File getMainComponetList() {
		String s = java.lang.System.getenv(SUPERCOMPONENTLIST_ENV);

		if (s != null) {
			if (getMainSuperlinkList() == null)
				return null;
			return new File(getMainSuperlinkList().getParentFile(),
					"components.info");
		}
		return null;
	}

	boolean getisCurrentComponetInList() {
		String s = java.lang.System.getenv(OSA_FILTER_COMPONENTLIST);

		if (s == null) {
			if (getMainSuperlinkList() == null) {
				return false;
			}
			return true;
		}
		return false;
	}

	File getMainSuperPMDList() {
		String s = java.lang.System.getenv(SUPERPMDLIST_DIR_ENV);
		if (s != null) {
			return new File(s);
		}
		return null;
	}

	public void setBuildComponentStructure(Boolean buildComponentStructure) {
		this.buildComponentStructure = buildComponentStructure;
	}

	public boolean isBuildComponentStructure() {
		return buildComponentStructure;
	}

  public void changePmdPath(String file, String _from, String _to) {
    try {
      String from = new String(_from);
      String to = new String(_to);
      PrintWriter writer = new PrintWriter(file + ".tmp",
                                           "UTF-8");
      BufferedReader br = new BufferedReader(new FileReader(file));
      String line;
      while ((line = br.readLine()) != null) {
        String s = new String(line);
        if (line.startsWith("<file name=\"")) {
          if (EnvManager.getInstance().isWindows()) {
            s = s.toLowerCase();
            from = from.toLowerCase();
            // to = to.toLowerCase();
          }
          int pos = s.indexOf(from);
          if (pos > -1) {
            writer.print(line.substring(0, pos));
            writer.print(to);
            writer.println(line.substring(pos + _from.length()));
          } else {
            writer.println(line);
          }
        } else {
          writer.println(line);
        }

      }
      br.close();
      writer.close();
      if (new File(file).delete()) {
        new File(file + ".tmp").renameTo(new File(file));
      }

    } catch (Exception e2) {
      e2.printStackTrace();
    }

  }

}
