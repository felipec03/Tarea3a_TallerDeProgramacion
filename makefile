FLAGS = -pg -Wall -O2 -march=native -flto -ffast-math
INCLUDES = -Iheaders

all: main

main: LinkCutTree.o Grafo.o FileReader.o DinicMaxFlow.o main.o
	g++ $(FLAGS) main.o Grafo.o FileReader.o DinicMaxFlow.o LinkCutTree.o -o main

Grafo.o: headers/Grafo.h src/Graph.cpp 
	g++ -c $(FLAGS) $(INCLUDES) src/Graph.cpp -o Grafo.o

LinkCutTree.o: headers/LinkCutTree.h src/LinkCutTree.cpp
	g++ -c $(FLAGS) $(INCLUDES) src/LinkCutTree.cpp -o LinkCutTree.o

DinicMaxFlow.o: headers/DinicMaxFlow.h src/DinicMaxFlow.cpp
	g++ -c $(FLAGS) $(INCLUDES) src/DinicMaxFlow.cpp -o DinicMaxFlow.o

FileReader.o: headers/FileReader.h src/FileReader.cpp
	g++ -c $(FLAGS) $(INCLUDES) src/FileReader.cpp -o FileReader.o

main.o: main.cpp headers/DinicMaxFlow.h headers/FileReader.h headers/Grafo.h
	g++ -c $(FLAGS) $(INCLUDES) main.cpp -o main.o

test: test_Grafo test_FileReader test_LinkCutTree

test_Grafo: tests/test_Grafo.cpp FileReader.o Grafo.o
	g++ $(FLAGS) $(INCLUDES) tests/test_Grafo.cpp FileReader.o Grafo.o -o test_Grafo

test_FileReader: tests/test_FileReader.cpp FileReader.o Grafo.o
	g++ $(FLAGS) $(INCLUDES) tests/test_FileReader.cpp FileReader.o Grafo.o -o test_FileReader

test_LinkCutTree: tests/test_LinkCutTree.cpp LinkCutTree.o
	g++ $(FLAGS) $(INCLUDES) tests/test_LinkCutTree.cpp LinkCutTree.o -o test_LinkCutTree

clean:
	rm -f *.o main test_Grafo test_FileReader test_LinkCutTree