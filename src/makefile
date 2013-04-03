# make.exe: Interrupt/Exception caught (code = 0xc0000005, addr = 0x0040b001)
SHELL = C:/Windows/System32/cmd.exe

.PHONY: clean

PRODUCT_VERSION = 0.5.5

CC_32 = g++
CC_64 = g++64

# default is 32 bit code, user can override
# example: following will (try) to compile 64 bit code (g++ has to be named g++64)
# make win SIZE=64
SIZE = 32

CC = $(CC_$(SIZE))

SOURCES = dir.cpp math.cpp util/base64.cpp
# OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS = dir.o math.o base64.o

#   "-s" switch is used to strip symbols from the DLL
#	"-O3" if you really know what you're doing
FLAGS = -Wall -Wextra -std=c++0x -O1 -O2 -s

# TODO: target for SQLite only dll, static
# TODO: target with SQLite built into

static:
	$(CC) -c $(SOURCES) $(FLAGS)
	ar rcs libmmx.a $(OBJECTS)

shared:
#   -lpthread needed for <thread> on linux
	$(CC) -c -fPIC $(SOURCES) $(FLAGS) -lpthread
	$(CC) -shared -Wl,-soname,libmmx.so -o libmmx.so $(OBJECTS) $(FLAGS) -lpthread

# ld.exe: i386 architecture of input file `VERSIONINFO.o' is incompatible with i386:x86-64 output
dll:
#	windres VERSIONINFO.rc VERSIONINFO.o
	$(CC) -shared -D MMX_DYNAMIC $(SOURCES) -o mmx.dll $(FLAGS)

# 7-zip must be in %PATH%
windows: win
win: static dll
	mkdir bin
	mv mmx.dll bin
	cp ../bin/sqlite3.dll bin

	mkdir lib
	mv libmmx.a lib

# The syntax of the command is incorrect.

	mkdir "include" "include/mmx" "include/mmx/util" "include/mmx/ext"
	cp *.hpp include/mmx/
	cp util/*.hpp include/mmx/util/

	cp ../ext/* include/mmx/ext/
	
	7z a -r mmx-$(PRODUCT_VERSION)-win-$(SIZE).7z bin lib include ../makefile ../example.cpp
	7z d mmx-$(PRODUCT_VERSION)-win-$(SIZE).7z src

	rm -rf bin
	rm -rf lib
	rm -rf include
	
	rm *.o
	
linux: static shared
	mkdir -p lib
	mv libmmx.a lib
	mv libmmx.so lib
	
	mkdir -p include include/mmx include/mmx/util include/mmx/ext
	cp *.hpp include/mmx
	cp util/*.hpp include/mmx/util
	cp ../ext/* include/mmx/ext
	
	tar -cjf mmx-$(PRODUCT_VERSION).tar.bz2 lib/ include/ ../makefile ../example.cpp
	
	rm -rf lib
	rm -rf include
	rm *.o

clean:
	rm -rf bin
	rm -rf lib
	rm -rf include
	rm *.o
