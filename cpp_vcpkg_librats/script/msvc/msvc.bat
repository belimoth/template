@echo off

set PATH=%PATH%;C:\Program Files (x86)\Microsoft Visual Studio\Installer
for /f "usebackq tokens=*" %%i in (`vswhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set vs_path=%%i
call "%vs_path%\VC\Auxiliary\Build\vcvars64.bat" >NUL
