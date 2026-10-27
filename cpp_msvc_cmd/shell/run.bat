@echo off

setlocal

rmdir a:\null\run
mkdir a:\null\run
pushd a:\null\run

..\build\main.exe
