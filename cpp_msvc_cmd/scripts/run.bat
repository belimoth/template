@echo off

setlocal

rmdir a:local\run
mkdir a:local\run
pushd a:local\run

..\build\main.exe
