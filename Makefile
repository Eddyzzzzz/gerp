#########################################################
#                Gerp Makefile                          #
#                Authors: Duncan and Eddy               #
#########################################################

MAKEFLAGS += -L 

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

# builds Gerp
gerp: main.o FSTree.o DirNode.o HashTable.o Gerp.o
	$(CXX) $(CXXFLAGS) -o gerp main.o FSTree.o DirNode.o HashTable.o \
							Gerp.o

# builds Hash
HashTable.o: HashTable.cpp HashTable.h
	$(CXX) $(CXXFLAGS) -c HashTable.cpp

# builds main
main.o: main.cpp Gerp.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# builds Gerp
Gerp.o: Gerp.cpp Gerp.h HashTable.h FSTree.h DirNode.h
	$(CXX) $(CXXFLAGS) -c Gerp.cpp

# compiles unit test
unit_test: unit_test_driver.o Gerp.o HashTable.o FSTree.o DirNode.o		
	$(CXX) $(CXXFLAGS) $^

