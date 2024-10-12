main: src/main.cpp src/utils.cpp src/bfs.cpp include/headers.hpp
	g++ src/main.cpp src/utils.cpp src/bfs.cpp -o main

clean:
	rm -f main