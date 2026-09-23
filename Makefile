CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic

all: parent child1 child2

parent: parent.cpp io_utils.cpp io_utils.h
	$(CXX) $(CXXFLAGS) parent.cpp io_utils.cpp -o parent

child1: child1.cpp io_utils.cpp io_utils.h
	$(CXX) $(CXXFLAGS) child1.cpp io_utils.cpp -o child1

child2: child2.cpp io_utils.cpp io_utils.h
	$(CXX) $(CXXFLAGS) child2.cpp io_utils.cpp -o child2

run: all
	./parent

clean:
	rm -f parent child1 child2

rebuild: clean all

.PHONY: all run clean rebuild