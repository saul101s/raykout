@ECHO off

cls
Premake5.exe --file=../premake5.lua vs2022
msbuild ../build/Raykout.sln /property:Configuration=Release /property:Platform=x64
pause
start cmd.exe /K "cd ..\bin & Raykout.exe"