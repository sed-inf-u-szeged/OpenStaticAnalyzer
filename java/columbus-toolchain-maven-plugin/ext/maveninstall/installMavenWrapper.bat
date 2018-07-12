@echo off
call :main


goto end




:installDepenedencies

call mvn install:install-file -Dfile=WindowsWrapper\WrapperBins\Tools\OpenStaticAnalyzer-Maven-plugin-mojo-executer-2.2.1.jar -DpomFile=WindowsWrapper\WrapperBins\Tools\OpenStaticAnalyzer-Maven-plugin-mojo-executer-2.2.1.pom
if %ERRORLEVEL% NEQ 0 (
goto:eof
)

call mvn install:install-file -Dfile=WindowsWrapper\WrapperBins\Tools\OpenStaticAnalyzer-Maven-plugin-mojo-executer-3.0.jar   -DpomFile=WindowsWrapper\WrapperBins\Tools\OpenStaticAnalyzer-Maven-plugin-mojo-executer-3.0.pom
if %ERRORLEVEL% NEQ 0 (
goto:eof
)

call mvn install:install-file -Dfile=WindowsWrapper\WrapperBins\Tools\OpenStaticAnalyzer-Maven-plugin-mojo-executer-3.1.jar   -DpomFile=WindowsWrapper\WrapperBins\Tools\OpenStaticAnalyzer-Maven-plugin-mojo-executer-3.1.pom
if %ERRORLEVEL% NEQ 0 (
goto:eof
)

goto:eof

:installplugin
echo.
for /f "tokens=3*" %%a in ('mvn --version') do (
  echo Current Maven version is: %%a
        
        
  if "%%a"=="2.2.1" ( 
    call :oldmaven
  ) else if "%%a"=="3.0.5" ( 
    call :newmaven
  ) else if "%%a"=="3.1.1" ( 
    call :newmaven
  ) else if "%%a"=="3.2.2" ( 
    call ::maven322
  ) else if "%%a"=="3.2.5" ( 
    call ::maven322
  ) else (
    set submaven=%%a
    set prob=%submaven:~0,-2%
    echo Warning! The Maven wrapper has not been tested with the current maven version!

    echo %prob%
    
    if "%prob%"=="2.2" ( 
       call :oldmaven
    ) else if "%prob%"=="3.0" ( 
       call :newmaven
    ) else if "%prob%"=="3.1" ( 
       call :newermaven
    ) else if "%prob%"=="3.2" ( 
       call ::maven322
    ) else (
        echo Error! Your Maven version is not supported yet!
        exit /B 1
    )
     goto:eof
  )
  goto:eof
)

goto:eof

:hackalias
call mvn org.apache.maven.plugins:OpenStaticAnalyzer-maven-plugin:4.0:installyourself
goto:eof

:oldmaven
echo Installing plugin for Maven 2.2.1 ...
call mvn install:install-file -Dfile=WindowsWrapper\WrapperBins\Tools\OpenStaticAnalyzer-maven-plugin-4.0.jar -DpomFile=WindowsWrapper\WrapperBins\Tools\OpenStaticAnalyzer-maven-plugin-4.0-V2.pom
goto:eof

:newmaven
echo Installing plugin for Maven 3.0.5 ...
call mvn install:install-file -Dfile=WindowsWrapper\WrapperBins\Tools\OpenStaticAnalyzer-maven-plugin-4.0.jar -DpomFile=WindowsWrapper\WrapperBins\Tools\OpenStaticAnalyzer-maven-plugin-4.0-V3.pom
goto:eof

:newermaven
echo Installing plugin for Maven 3.1.1 ...
call mvn install:install-file -Dfile=WindowsWrapper\WrapperBins\Tools\OpenStaticAnalyzer-maven-plugin-4.0.jar -DpomFile=WindowsWrapper\WrapperBins\Tools\OpenStaticAnalyzer-maven-plugin-4.0-V31.pom
goto:eof

:maven322
echo Installing plugin for Maven 3.2.2 ...
call mvn install:install-file -Dfile=WindowsWrapper\WrapperBins\Tools\OpenStaticAnalyzer-maven-plugin-4.0.jar -DpomFile=WindowsWrapper\WrapperBins\Tools\OpenStaticAnalyzer-maven-plugin-4.0-V31.pom
goto:eof


:main

call :installDepenedencies
if %ERRORLEVEL% NEQ 0 goto err

call :installplugin
if %ERRORLEVEL% NEQ 0 goto err

call :hackalias
if %ERRORLEVEL% NEQ 0 goto err

echo Maven plugin has been successfully installed.
exit /B 0 
goto:eof


:err
echo Maven plugin installation has been failed!
exit /B 1

:end


