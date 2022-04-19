CC=g++
MAINFILE=src/main.cc
CFLAGS=-Wall -g
INCLUDE=include/*.cc

main: src/main.cc 
	$(CC) $(CFLAGS) -o build/main $(MAINFILE) $(INCLUDE)

greed2: main
	./build/main ./examples/I40j_2m_S1_1.txt 1

greed4: main
	./build/main ./examples/I40j_4m_S1_1.txt 1

greed6: main
	./build/main ./examples/I40j_6m_S1_1.txt 1

greed8: main
	./build/main ./examples/I40j_8m_S1_1.txt 1


grasp2: main
	./build/main ./examples/I40j_2m_S1_1.txt 0

grasp4: main
	./build/main ./examples/I40j_4m_S1_1.txt 0

grasp6: main
	./build/main ./examples/I40j_6m_S1_1.txt 0

grasp8: main
	./build/main ./examples/I40j_8m_S1_1.txt 0
