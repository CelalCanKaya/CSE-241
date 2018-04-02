all: start

start: main.o 
	g++ -o exe main.o

main.o: main.cpp
	g++ -c -std=c++11 main.cpp

clean:
	rm *.o exe
