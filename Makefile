CC=g++
MAINFILE=src/main.cc
CFLAGS=-Wall -g
INCLUDE=include/*.cc

main: src/main.cc 
	$(CC) $(CFLAGS) -o build/main $(MAINFILE) $(INCLUDE)

run2: main
	./build/main ./examples/I40j_2m_S1_1.txt

run4: main
	./build/main ./examples/I40j_4m_S1_1.txt

run6: main
	./build/main ./examples/I40j_6m_S1_1.txt

run8: main
	./build/main ./examples/I40j_8m_S1_1.txt
