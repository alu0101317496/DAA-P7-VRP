CC=g++
MAINFILE=src/main.cc
CFLAGS=-Wall -g
INCLUDE=include/*.cc

main: src/main.cc 
	$(CC) $(CFLAGS) -o build/main.exe $(MAINFILE) $(INCLUDE)


