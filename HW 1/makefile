all: start

start: main.o 
	g++ -o exe main.o

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o exe
