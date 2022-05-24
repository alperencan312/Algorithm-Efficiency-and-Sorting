hw1: main.o sorting.o
	g++ -std=c++11 -o hw1 main.o sorting.o
main.o: main.cpp sorting.h
	g++ -c main.cpp -std=c++11
sorting.o: sorting.cpp sorting.h
	g++ -c sorting.cpp -std=c++11
clean:
	rm sorting.o main.o hw1 
