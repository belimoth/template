@echo off

setlocal

for /f "tokens=*" %%i in ( '"C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere" -latest -property installationPath' ) do set vs_path=%%i
call "%vs_path%\VC\Auxiliary\Build\vcvars64.bat" > nul

rmdir a:\local\build
mkdir a:\local\build
pushd a:\local\build

echo on
@cl ..\..\source\main.cpp /link
