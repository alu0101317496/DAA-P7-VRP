CC=g++
MAINFILE=src/main.cc
CFLAGS=-Wall -g
INCLUDE=include/*.cc

main: src/main.cc 
	$(CC) $(CFLAGS) -o build/main $(MAINFILE) $(INCLUDE)



run: main
	./build/main ./examples/I40j_2m_S1_1.txt
