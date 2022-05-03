@echo off


devenv log4cplus-1.1.0\msvc10\log4cplus.vcxproj /upgrade
msbuild log4cplus-1.1.0\msvc10\log4cplus.vcxproj /t:Rebuild /p:Configuration=Release /p:PLatform=x64