all: src/main.cpp utils algorithms 
	g++ -std=c++14 -O3 -o main src/main.cpp utils.o puzzle.o bfs.o gbfs.o astar.o


utils:
	g++ -std=c++14 -O3 -c src/puzzle.cpp
	g++ -std=c++14 -O3 -c src/utils.cpp

algorithms:
	g++ -std=c++14 -O3 -c src/bfs.cpp
	g++ -std=c++14 -O3 -c src/gbfs.cpp
	g++ -std=c++14 -O3 -c src/astar.cpp

clean:
	rm -f *.o
	rm -f main
	rm -f *.csv