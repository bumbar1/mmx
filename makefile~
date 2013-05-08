CC = g++
LIB = lib/
BIN = bin/
FLAGS = -Wall -Wextra -std=c++0x -s

windows:
	$(CC) $(FLAGS) -static example.cpp -L $(LIB) -lmmx -o static.exe
	$(CC) $(FLAGS) example.cpp $(BIN)mmx.dll -o dynamic.exe
	
linux:
	$(CC) $(FLAGS) -static example.cpp -L $(LIB) -lmmx -o static.out
	$(CC) $(FLAGS) example.cpp -o dynamic.out -L $(LIB) -lmmx
