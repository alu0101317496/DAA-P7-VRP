CC=clang
MAINFILE=src/main.cc
CFLAGS=-Wall -g -o 
OBJECTS= ./include/*.o

main: 
	$(CC) $(CFLAGS) build/main.exe $(MAINFILE) $(OBJECTS)


