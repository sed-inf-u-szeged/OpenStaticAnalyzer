# Tips for compiler-wrapping

In this chapter we describe our compiler-wrapping technique more in-depth and provide some tips for analyzing projects with non-trivial build systems.

In a previous chapter called *Preconditions*, we have described what conditions are required to run the analysis of a project in a normal scenario. In this chapter we try to answer why those preconditions are necessary and show you what kind of modifications are required to make the compiler-wrapping technique work. In our experience, every build can be wrapped with modifying only a couple of lines of the build scripts, but to know what you have to change, you have to understand the basics of compiler wrapping.

## Overview of our compiler-wrapping technique

In order to analyze your project, a list of your .cpp and .h files is not enough for us to plot the connections between your code, your headers, your executables, your static or dynamic libraries, etc. We need to eavesdrop on your whole build process. We do this by redirecting the compile, link and library creating commands of your buildtool man-in-the-middle style. Let us illustrate that through an example:

Let's say you have a Visual Studio 2017 project on Windows that you intend to compile with the regular MSVC tools. You can do this from the command line by setting up a native environment (running vcvarsall.bat) and calling msbuild on your project. Normally, this uses the cl.exe from Program Files to compile .cpp files, however, that's not good for us, because we would like to hijack cl.exe to log the compiled files and flags and macros used for the compilation.

So instead of that, whenever you call msbuild from inside the build.bat script, we automatically call msbuild with the /p:UseEnv=True parameter added to it. The result of this, is that the cl.exe, link.exe and lib.exe commands used by the msbuild are now the ones found in PATH and NOT the ones from Program Files . All we do now is put our fake cl.exe, lib.exe and link.exe files on PATH. These fake executables will log their received parameters, and forward everything to the real .exe files (in Program Files). This is the gist of compiler-wrapping.

Here is the rough scheme of the OpenStaticAnalyzer code analysis from the perspective of compiler-wrapping (Windows/Linux):

1. Open cmd/shell

2. Put compiler programs on PATH (on Windows: run the correct version of vcvarsall.bat; on Linux: add clang and clang++ to PATH (if not already there))

3. Run OpenStaticAnalyzerCPP.exe (with your build.bat/build.sh script supplied as a parameter)

4.    The program will create fake compiler tools(fake cl.exe/clang) that log their parameters and forward them to the real one. Also the program adds these fake compiler tools to the top of PATH (shadowing the real ones).

5.    The program calls build.bat/build.sh (that you have supplied), which builds your project with the fake compiler tools from PATH.

6.    In-depth analysis is run over your source files (which were gathered by the fake compiler tools)

Note<sup>1</sup>: Your build.bat/build.sh **MUST invoke a full build** (as we need to gather all the files)! This usually means rebuild in build.bat/build.sh.  
Note<sup>2</sup>: No matter what build system you use, you need to configure it somehow to call the compile, link and lib commands from PATH (instead of some other absolute or relative paths)  
Note<sup>3</sup>: Your build script should not put any of these compiler tools on PATH (as it would shadow our fake compiler tools)

If you cannot guarantee all these, the compiler-wrapping technique won't work.

## Examples of non-trivial build.bat/build.sh scripts

Writing the correct build.bat/build.sh scripts can be tricky, here are some examples to help:

**1. cmake + ninja on Windows**  
This is the build.bat for the project wasm3, using a CMake Ninja generator and building with Ninja:
```
set OLDDIR=%CD%
cd %~dp0

rmdir /Q /S build
mkdir build
cd build
SET OSA_DISABLE_ANALYSIS=true
cmake -GNinja ..\wasm3
SET OSA_DISABLE_ANALYSIS=
ninja
chdir /d %OLDDIR%
```
Note<sup>1</sup>: Ninja doesn't have a rebuild switch, so we need to delete the build folder and recreate it.  
Note<sup>2</sup>: Ninja uses the compiler paths hard coded into build.ninja by the CMake generator. CMake acquired these paths from the PATH (this is why we must put the CMake generator into the build.bat)  
Note<sup>3</sup>: The compiler is the msvc cl.exe found on PATH (put there by vcvarsall.bat). Currently, on Windows our tools can only analyze projects compiled with cl.exe  
Note<sup>4</sup>: The CMake Ninja generator compiles some tools for itself, therefore we must SET OSA_DISABLE_ANALYSIS=true surrounding the CMake generator call (we don't want to include CMake's own compiled tools into the analysis results)

**2. cmake + make with clang on Linux**  
This is the build.sh script for project wasm3, using the default make generator of CMake with clang on Linux.
```
export OSA_DISABLE_ANALYSIS=true &&
export CXX=clang++ &&
export CC=clang &&
rm -rf build &&
mkdir build &&
cd build &&
/usr/bin/cmake ../wasm3 &&
unset OSA_DISABLE_ANALYSIS &&
make -j8
```
Note<sup>1</sup>: As it is written earlier, you must use clang to compile and analyze your project on Linux. GCC is not yet supported.  
Note<sup>2</sup>: clang and clang++ are already on PATH by default but we have to export them as CXX and CC variables for CMake to find the right compilers.  
Note<sup>3</sup>: We use && to separate the commands here, but you could also use ;

**3. cmake + cmake --build on Windows **  
This is the build.bat script for project wasm3, using the CMake Visual Studio 2019 generator and the cmake --build command.
```
set OLDDIR=%CD%
cd %~dp0

rmdir /Q /S build
mkdir build
cd build
SET OSA_DISABLE_ANALYSIS=true
cmake -G"Visual Studio 16 2019" -A x64 ..\wasm3
SET OSA_DISABLE_ANALYSIS=
cmake --build . --config Release -- /p:UseEnv=True
chdir /d %OLDDIR%
```
Note<sup>1</sup>: The --build command of CMake builds the project with the build tool decided by the generator being used. For VS projects, this is msbuild. Unfortunetly, we cannot supply the cmake VS generator with compilers from PATH (the path to the tools in the CMake VS generator are taken from the registry). What we can do, however, is provide the /p:UseEnv=True parameter to msbuild to force it to use the tools from the environment. In the CMake command, every parameter after -- is forwarded to the buildtool.  
Note<sup>2</sup>: Just like ninja, cmake --build also does not have a rebuild flag. We have two options: pass the rebuild parameter to msbuild after the --, or delete and recreate the build folders. We chose the latter here.

**4. custom configuration script + nmake on Windows**  
This is the build.bat script for the project QTBase, it uses a custom configuration script and an nmake build on Windows.
```
set OLDDIR=%CD%
cd %~dp0

rmdir /Q /S build
mkdir build
cd build
SET OSA_DISABLE_ANALYSIS=true
call ..\qt5vars.cmd
echo y | call ..\qtbase\configure -debug -no-pch -nomake examples^
  -nomake tests -skip qtwebengine -opensource -prefix "C:\projektek\tests\qtbase\build"
SET OSA_DISABLE_ANALYSIS=
call nmake
cd ..
chdir /d %OLDDIR%
```
Note<sup>1</sup>: We had to use a caret(^) in the script to break the line so that the lines in this documentation are not too long. You don't have to do that in your script.  
Note<sup>2</sup>: There was no need to change the custom configuration scripts of the project here. Just follow the regular protocol. The only tricky thing is to prefix the configuration with "echo y |". This will result in automatic "yes" user input for prompts (which happen during configuration).

## Examples of build/configuration script modifications

In rare cases, a clever build.bat/build.sh is not enough, we need to modify the configuration/build scripts. Here are some examples of things to avoid and what to do instead.

**1. Do not depend on the path of compiler tools in the build/configuration scripts!**

This is a snippet of the CMakeLists.txt of the msvc/STL project. You can see that the TOOLSET_LIB variable is set based on a path relative to the CMAKE_CXX_COMPILER variable (which is the path to cl.exe in this case). Since we replace the cl.exe on PATH with our own fake one, this relative path will not work, so don't do this:

CMakeLists.txt (snippet):
```
get_filename_component(TOOLSET_BINARIES_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY) # $\VC\Tools\MSVC\14.23.27931\bin\Hostx86\x86
get_filename_component(TOOLSET_ROOT_DIR "${TOOLSET_BINARIES_DIR}" DIRECTORY) # $\VC\Tools\MSVC\14.23.27931\bin\Hostx86
get_filename_component(TOOLSET_ROOT_DIR "${TOOLSET_ROOT_DIR}" DIRECTORY) # $\VC\Tools\MSVC\14.23.27931\bin
get_filename_component(TOOLSET_ROOT_DIR "${TOOLSET_ROOT_DIR}" DIRECTORY) # $\VC\Tools\MSVC\14.23.27931

set(TOOLSET_LIB "${TOOLSET_ROOT_DIR}/lib/${VCLIBS_X86_OR_X64}")
```

Instead, you have two options. One is to set it as an absolute path: (not the best solution but it works)

CMakeLists.txt (snippet):
```
if (DEFINED ENV{OPENSTATICANALYZER_IS_ACTIVE})
  set(TOOLSET_ROOT_DIR "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.24.28314")
endif()
set(TOOLSET_LIB "${TOOLSET_ROOT_DIR}/lib/${VCLIBS_X86_OR_X64}")
```
Note<sup>1</sup>: You can always use the environmental variable OPENSTATICANALYZER_IS_ACTIVE to check whether the build is under the analysis of OpenStaticAnalyzer (this will guarantee that these modifications won't affect your regular build).

A better solution is to create the relative path based on cl.exe BEFORE the OpenStaticAnalyzerCPP.exe is called (while you still have the original cl.exe on top of PATH). To do this, we have to make a short script that calls OpenStaticAnalyzerCPP.exe, instead of calling it directly:

analyze.bat:
```
:: Putting the right compiler tools in PATH
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
:: These 3 lines are just a cmd trick to copy the file-path of cl.exe (from PATH) into a variable
where cl > tmpFile
set /p cl_path_env_var= < tmpFile
del tmpFile
:: Setting up the proper VC root path relative to the cl.exe on PATH
:: We will be able to find this variable(ENV_ORIGINAL_TOOLSET_ROOT_DIR) in CMakeLists.txt and use it.
set ENV_ORIGINAL_TOOLSET_ROOT_DIR=%cl_path_env_var%\..\..\..\..

N:\buildR\OpenStaticAnalyzer\OpenStaticAnalyzer-5.0.0-x64-Windows\CPP\OpenStaticAnalyzerCPP.exe^
  -projectName=STL -buildScript=build.bat -resultsDir=Results\clang -externalSoftFilter=softfilter
```
Note<sup>1</sup>: We had to use a caret(^) in the script to break the line so that the lines in this documentation are not too long. You don't have to do that in your script.

Here is how you use that variable in the modified CMakeLists.txt:

CMakeLists.txt (snippet):
```
if (DEFINED ENV{ENV_ORIGINAL_TOOLSET_ROOT_DIR})
  file(TO_CMAKE_PATH "$ENV{ENV_ORIGINAL_TOOLSET_ROOT_DIR}" TOOLSET_ROOT_DIR)
endif()
```

**2. Do not put compiler tools on PATH while building!**

This is a snippet of the custom build script of Panda3d, you can see that it adds the compiler binary path to the PATH variable, but your build script shouldn't do this:

makepandacore.py (snippet):
```
vc_binpath = SDK["VISUALSTUDIO"] + vcdir_suffix + "bin"
binpath = os.path.join(vc_binpath, bindir)
if not os.path.isfile(binpath + "\\cl.exe"):
    # Try the x86 tools, those should work just as well.
    if arch == 'x64' and os.path.isfile(vc_binpath + "\\x86_amd64\\cl.exe"):
        binpath = "{0}\\x86_amd64;{0}".format(vc_binpath)
    elif winsdk_ver.startswith('10.'):
        exit("Couldn't find compilers in %s.  You may need to install the Windows SDK 7.1." % binpath)
    else:
        exit("Couldn't find compilers in %s." % binpath)

AddToPathEnv("PATH",    binpath) # <-- This line causes the problem, don't do this!
```

Instead, given that we have to put the compiler tools on PATH anyways (with vcvarsall.bat), we can simply disable it by adding an IF check with our OPENSTATICANALYZER_IS_ACTIVE environmental variable:

makepandacore.py (snippet):
```
# If this enviromental variable is set, we know that the build is called from the OpenStaticAnalyzer analysis
# Therefore, we only do this if the build is NOT called from OpenStaticAnalyzer
if (os.environ.get('OPENSTATICANALYZER_IS_ACTIVE') == None):
    AddToPathEnv("PATH",    binpath)
```

Hopefully, with these hints you will be able to run the analysis on your project successfully. **If not, send us an email and we will help you sort it out!**
