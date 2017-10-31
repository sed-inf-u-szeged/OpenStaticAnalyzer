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

package com.columbus.javaagent;

import java.security.ProtectionDomain;
import java.io.File;
import java.io.IOException;
import java.lang.instrument.ClassFileTransformer;
import java.lang.instrument.IllegalClassFormatException;
import java.security.ProtectionDomain;

import javassist.CannotCompileException;
import javassist.ClassClassPath;
import javassist.ClassPool;
import javassist.CtClass;
import javassist.CtMethod;
import javassist.CtNewMethod;
import javassist.NotFoundException;

public class SleepingClassFileTransformer implements ClassFileTransformer {

  public byte[] transform(ClassLoader loader, String className,
      Class classBeingRedefined, ProtectionDomain protectionDomain,
      byte[] classfileBuffer) throws ClassFormatError {
    byte[] byteCode = classfileBuffer;
    if ((className != null) && (loader != null)) {
      try {

        if (className.contains("org/apache/maven/plugin/CompilerMojo")) {
         
          return injectWrapper(loader, "org.apache.maven.plugin.CompilerMojo",
              "compile");
        }

        if (className.contains("org/apache/maven/plugin/compiler/CompilerMojo")) {
         
          return injectWrapper(loader,
              "org.apache.maven.plugin.compiler.CompilerMojo", "compile");
        }

        if (className.contains("org/apache/maven/plugin/jar/AbstractJarMojo")) {
         
          return injectWrapper(loader,
              "org.apache.maven.plugin.jar.AbstractJarMojo", "link");
        }

        if (className.contains("org/apache/maven/plugin/install/InstallMojo")) {
         
          return injectWrapper(loader,
              "org.apache.maven.plugin.install.InstallMojo", "install");
        }

        if (className.contains("org/apache/maven/plugin/deploy/DeployMojo")) {
         
          return injectWrapper(loader,
              "org.apache.maven.plugin.deploy.DeployMojo", "deploy");
        }

        // hack to acess project.

        if (className.contains("org/apache/maven/DefaultMaven")) {
         

          return injectProjectAcessHack(loader, "org.apache.maven.DefaultMaven");
        }

      } catch (Exception e) {
        e.printStackTrace();
      }
    }

    return byteCode;

  }

  private byte[] injectProjectAcessHack(ClassLoader loader, String className)
      throws NotFoundException, CannotCompileException, IOException {

    byte[] byteCode;
    ClassPool cp = ClassPool.getDefault();
    boolean isNewMaven = false; 
    
    try {
      Class<?> testClass = loader.loadClass("org.apache.maven.execution.MavenExecutionRequest");
      try {
      testClass.getMethod("getPomFile");
      } catch (NoSuchMethodException e) {
        isNewMaven = true;
      }
    } catch (ClassNotFoundException e) {
      e.printStackTrace();
    }
    
    cp.insertClassPath(new javassist.LoaderClassPath(loader));
    CtClass cc = cp.get(className);
    CtMethod mold = cc.getDeclaredMethod("execute");

    String nname = "execute" + "$impl";
    mold.setName(nname);
    CtMethod mnew = CtNewMethod.copy(mold, "execute", cc, null);

    String type = mold.getReturnType().getName();
    StringBuffer body = new StringBuffer();
    body.append("{");
    if (!"void".equals(type)) {
      body.append(type + " result = ");
    }
    body.append(nname + "($$);\n");
    if (isNewMaven) {
      body.append("com.columbus.javaagent.Agent.executeMavenHook($1.getBaseDirectory() ,$1.getPom().getPath())  ;\n");
    }  else { 
      body.append("com.columbus.javaagent.Agent.executeMavenHook($1.getBaseDirectory() ,$1.getPomFile())  ;\n");
    }
    if (!"void".equals(type)) {
      body.append("return result;\n");
    }
    body.append("}");

    mnew.setBody(body.toString());
    cc.addMethod(mnew);

    byteCode = cc.toBytecode();
    cc.detach();
    return byteCode;

  }


  
  protected byte[] injectWrapper(ClassLoader loader, String className,
      String goalName) throws NotFoundException, CannotCompileException,
      IOException {
    byte[] byteCode;
    ClassPool cp = ClassPool.getDefault();
    cp.insertClassPath(new javassist.LoaderClassPath(loader));
    CtClass cc = cp.get(className);
    CtMethod m = cc.getDeclaredMethod("execute");

    if (goalName.equals("install") || goalName.equals("deploy")) {
      m.insertAfter("{com.columbus.javaagent.Agent.runTask(\"" + goalName
          + "\",pomFile.getParentFile(),null);}");
    } else {
      m.insertAfter("{com.columbus.javaagent.Agent.runTask(\"" + goalName
          + "\",new java.io.File(outputDirectory,\"..\"),null);}");

    }

    byteCode = cc.toBytecode();
    cc.detach();
    return byteCode;
  }

}
