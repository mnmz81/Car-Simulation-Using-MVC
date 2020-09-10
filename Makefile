all:
	g++ -std=c++11 *.cpp -o 1
	./1 -w depot.dat -t Godzilla.txt
compile: