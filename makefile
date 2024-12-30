FLAGS = -pg -Wall -O2 -march=native -flto -ffast-math
INCLUDES = -Iheaders

all: main

main: FileReader.o Grafo.o DinicMaxFlow.o main.o
	g++ $(FLAGS) main.o FileReader.o Grafo.o DinicMaxFlow.o -o main

Grafo.o: headers/Grafo.h src/Graph.cpp 
	g++ -c $(FLAGS) $(INCLUDES) src/Graph.cpp -o Grafo.o

DinicMaxFlow.o: headers/DinicMaxFlow.h src/DinicMaxFlow.cpp
	g++ -c $(FLAGS) $(INCLUDES) src/DinicMaxFlow.cpp -o DinicMaxFlow.o

FileReader.o: headers/FileReader.h src/FileReader.cpp
	g++ -c $(FLAGS) $(INCLUDES) src/FileReader.cpp -o FileReader.o

main.o: main.cpp headers/DinicMaxFlow.h headers/FileReader.h headers/Grafo.h
	g++ -c $(FLAGS) $(INCLUDES) main.cpp -o main.o

test: test_Grafo test_FileReader

test_Grafo: tests/test_Grafo.cpp FileReader.o Grafo.o
	g++ $(FLAGS) $(INCLUDES) tests/test_Grafo.cpp FileReader.o Grafo.o -o test_Grafo

test_FileReader: tests/test_FileReader.cpp FileReader.o Grafo.o
	g++ $(FLAGS) $(INCLUDES) tests/test_FileReader.cpp FileReader.o Grafo.o -o test_FileReader

clean:
	rm -f *.o main test_Grafo test_FileReader