CC=clang
MAINFILE=src/main.cc
CFLAGS=-g
INCLUDE=include/*.cc

all:
	$(CC) $(CFLAGS) -c $(MAINFILE) $(INCLUDE) 

main: src/main.cc 
	$(CC) -g -o build\main.exe *.o

greed2: main
	.\build\main.exe .\examples\I40j_2m_S1_1.txt 1

greed4: main
	./build/main.exe ./examples/I40j_4m_S1_1.txt 1

greed6: main
	./build/main.exe ./examples/I40j_6m_S1_1.txt 1

greed8: main
	./build/main.exe ./examples/I40j_8m_S1_1.txt 1


grasp2: main
	./build/main.exe ./examples/I40j_2m_S1_1.txt 0

grasp4: main
	./build/main.exe ./examples/I40j_4m_S1_1.txt 0

grasp6: main
	./build/main.exe ./examples/I40j_6m_S1_1.txt 0

grasp8: main
	./build/main.exe ./examples/I40j_8m_S1_1.txt 0
