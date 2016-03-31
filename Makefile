CC = g++
CFLAGS = -g -O3 -std=c++11

all: main

main: main.o Bacteria.o Env.o Simulation.o Population.o
	$(CC) $(CFLAGS) main.o Bacteria.o Env.o Simulation.o Population.o -o main

main.o: main.cpp Bacteria.hpp Env.hpp Simulation.hpp Population.hpp
	$(CC) $(CFLAGS) -c main.cpp

Bacteria.o: Bacteria.cpp Bacteria.hpp
	$(CC) $(CFLAGS) -c Bacteria.cpp

Simulation.o: Simulation.cpp Simulation.hpp
	$(CC) $(CFLAGS) -c Simulation.cpp

Population.o: Population.cpp Population.hpp
	$(CC) $(CFLAGS) -c Population.cpp

Env.o: Env.cpp Env.hpp
	$(CC) $(CFLAGS) -c Env.cpp

clean:
	rm -rf ./main ./*.o
