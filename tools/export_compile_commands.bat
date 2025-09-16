@ECHO off

cls
Premake5.exe --file=../premake5.lua export-compile-commands
pause
