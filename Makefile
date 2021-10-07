#
# Makefile for Binary Search Tree
#
# Homework 4 (fall 2019)
#

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++11 

BSTInteractively: BSTInteractively.o BinarySearchTree.o
	${CXX} -o $@ $^

hw4: hw4.o BinarySearchTree.o
	${CXX} -o $@ $^
	
%.o: %.cpp $(shell echo *.h)
	${CXX} ${CXXFLAGS} -c $<

clean:
	rm -rf hw4 *.o *.dSYM

provide:
	provide comp15 hw4 hw4.cpp BinarySearchTree.cpp BinarySearchTree.h \
	        README Makefile BSTInteractively.cpp BSTInteractively

