CXX ?= c++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wpedantic -O2

slot-machine: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o $@

test: slot-machine
	python3 -m unittest discover -s tests -v

clean:
	rm -f slot-machine

.PHONY: test clean
