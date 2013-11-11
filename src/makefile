# make.exe: Interrupt/Exception caught (code = 0xc0000005, addr = 0x0040b001)
SHELL = C:/Windows/System32/cmd.exe

.PHONY: clean

CC = g++

SOURCES = dir.cpp math.cpp util/base64.cpp
# OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS = dir.o math.o base64.o

#   "-s" switch is used to strip symbols from the DLL
#	"-O3" if you really know what you're doing
FLAGS = -Wall -Wextra -std=c++11 -O1 -O2 -s

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

windows: static dll
# The syntax of the command is incorrect.
# native window mkdir has different syntax than gnu make -- it's using / for switch
	-mkdir "../build" "../build/lib" "../build/bin" "../build/include"
	-mkdir "../build/include/mmx" "../build/include/mmx/util" "../build/include/mmx/ext"

	mv libmmx.a ../build/lib
	
	cp *.hpp "../build/include/mmx"
	cp util/*.hpp "../build/include/mmx/util"
	cp ../ext/* "../build/include/mmx/ext"

	mv mmx.dll "../build/bin"
# To ignore errors in a recipe line, write a ‘-’ at the beginning of the line's text (after the initial tab).
	-cp "../bin/sqlite3.dll" "../build/bin"
	
linux: static shared
	mkdir -p ../build ../build/lib ../build/include/mmx/util ../build/include/mmx/ext

	mv libmmx.a ../build/lib
	mv libmmx.so ../build/lib
	
	cp *.hpp ../build/include/mmx
	cp util/*.hpp ../build/include/mmx/util
	cp ../ext/* ../build/include/mmx/ext

install:
	-cp ../build/lib/* /usr/lib/
	-cp -R ../build/include/* /usr/include/
	
clean:
	-rm -rf ../build
	-rm *.o
