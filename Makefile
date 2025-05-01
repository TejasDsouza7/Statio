CXX=g++
CXXFLAGS=-std=c++17 -Iinclude -Wall
LDFLAGS=-lcurl

all: statio

statio: src/main.cpp src/tracker.cpp src/location.cpp src/spacetrack.cpp
	$(CXX) $(CXXFLAGS) src/main.cpp src/tracker.cpp src/location.cpp src/spacetrack.cpp -o statio $(LDFLAGS)

clean:
	rm -f statio