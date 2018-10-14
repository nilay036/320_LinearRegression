all: matrix clean

matrix: instantiation.cpp Matrix.o main.o
	g++ -std=c++11 instantiation.cpp -o matrix -g
main.o: main.cpp
	g++ -std=c++11 -c main.cpp -g
Matrix.o: Matrix.cpp
	g++ -std=c++11 -c Matrix.cpp -g
clean:
	rm -rf *o
