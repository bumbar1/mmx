CC = g++
FLAGS = -Wall -Wextra -std=c++11 -s

windows:
	$(CC) $(FLAGS) -static example.cpp -lmmx -o static.exe
	$(CC) $(FLAGS) example.cpp "build/bin/mmx.dll" -o dynamic.exe
	
linux:
	$(CC) $(FLAGS) -static example.cpp -lmmx -o static.out
	$(CC) $(FLAGS) example.cpp -o dynamic.out -lmmx
