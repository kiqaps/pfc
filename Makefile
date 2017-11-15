all: src/*.cpp
	mkdir -p obj/Debug/src/
	mkdir -p bin/Debug/
	g++ -Wall -fexceptions -g -Iinclude -c /home/kiqaps/Documentos/pfc/src/AdjList.cpp -o obj/Debug/src/AdjList.o
	g++ -Wall -fexceptions -g -Iinclude -c /home/kiqaps/Documentos/pfc/src/bruteforce.cpp -o obj/Debug/src/bruteforce.o
	g++ -Wall -fexceptions -g -Iinclude -c /home/kiqaps/Documentos/pfc/src/mds.cpp -o obj/Debug/src/mds.o
	g++ -Wall -fexceptions -g -Iinclude -c /home/kiqaps/Documentos/pfc/main.cpp -o obj/Debug/main.o
	g++  -o bin/Debug/PFC obj/Debug/main.o obj/Debug/src/AdjList.o obj/Debug/src/bruteforce.o obj/Debug/src/mds.o