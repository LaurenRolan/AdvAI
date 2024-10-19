all: src/main.cpp utils algorithms 
	g++ -std=c++11 -O3 -o main src/main.cpp utils.o puzzle.o bfs.o


utils:
	g++ -std=c++11 -O3 -c src/puzzle.cpp
	g++ -std=c++11 -O3 -c src/utils.cpp

algorithms:
	g++ -std=c++11 -O3 -c src/bfs.cpp

clean:
	rm -f *.o
	rm -f main
	rm -f *.csv