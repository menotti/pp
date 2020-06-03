CXX=/usr/local/bin/g++-9
CXXFLAGS=-std=c++17 -O2 -Wall -fopenmp -pedantic

a.out: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

run:
	time ./a.out

clean:
	rm a.out
