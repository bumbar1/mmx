@echo off
mkdir bin
move mmx.dll bin
copy ..\bin\sqlite3.dll bin

mkdir lib
move libmmx.a lib

mkdir include\mmx\util
mkdir include\mmx\ext
copy *.hpp include\mmx
copy util\*.hpp include\mmx\util

copy ..\ext\* include\mmx\ext

7z a -r mmx-%1.7z bin lib include ..\makefile ..\example.cpp
7z d mmx-%1.7z src

rmdir /Q /S bin
rmdir /Q /S lib
rmdir /Q /S include

del *.o