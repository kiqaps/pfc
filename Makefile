all: src/*.cpp
	mkdir -p obj/Debug/src/
	mkdir -p bin/Debug/
	g++ -std=c++11 -Wall -fexceptions -g -Iinclude -c ./src/AdjList.cpp -o obj/Debug/src/AdjList.o
	g++ -std=c++11 -Wall -fexceptions -g -Iinclude -c ./src/bruteforce.cpp -o obj/Debug/src/bruteforce.o
	g++ -std=c++11 -Wall -fexceptions -g -Iinclude -c ./src/mds.cpp -o obj/Debug/src/mds.o
	g++ -std=c++11 -Wall -fexceptions -g -Iinclude -c main.cpp -o obj/Debug/main.o
	g++ -o bin/Debug/PFC obj/Debug/main.o obj/Debug/src/AdjList.o obj/Debug/src/bruteforce.o obj/Debug/src/mds.o