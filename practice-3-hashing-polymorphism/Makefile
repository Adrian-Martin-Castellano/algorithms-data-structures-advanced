CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

all: hash

hash: main-hash.o Nif.o
	$(CXX) $(CXXFLAGS) $^ -o $@

main-hash.o: main-hash.cc HashTable.tpp StaticSequence.tpp DynamicSequence.tpp DispersionFunction.tpp ExplorationFunction.tpp Nif.hpp
	$(CXX) $(CXXFLAGS) -c main-hash.cc -o $@

Nif.o: Nif.cc Nif.hpp
	$(CXX) $(CXXFLAGS) -c Nif.cc -o $@

clean:
	rm -f *.o hash