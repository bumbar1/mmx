PRODUCT_VERSION = 0.5.3

CC = g++

SOURCES = date.cpp dir.cpp math.cpp time.cpp util.cpp util/base64.cpp util/file.cpp util/string.cpp
# OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS = date.o dir.o math.o time.o util.o base64.o file.o string.o

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

dll:
	windres VERSIONINFO.rc VERSIONINFO.o
	$(CC) -shared -D MMX_DYNAMIC $(SOURCES) VERSIONINFO.o -o mmx.dll $(FLAGS)

# 7-zip must be in %PATH%
windows: static dll
	windows.bat $(PRODUCT_VERSION)_win
	
linux: static shared
	mkdir lib
	mv libmmx.a lib
	mv libmmx.so lib
	
	mkdir include include/mmx include/mmx/util include/mmx/ext
	cp *.hpp include/mmx
	cp util/*.hpp include/mmx/util
	cp ../ext/* include/mmx/ext
	
	tar -cjf mmx-$(PRODUCT_VERSION)_nix.tar.bz2 lib/ include/ ../makefile ../example.cpp
	
	rm -f lib/*
	rmdir lib
	rm -f include/mmx/ext/*
	rmdir include/mmx/ext
	rm -f include/mmx/util/*
	rmdir include/mmx/util
	rm -f include/mmx/*
	rmdir include/mmx include
	
	rm *.o
