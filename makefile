# Makefile for the sample API call program
# It is necessary to link the curl library through CLI, so its a lot simpler
# to just use this as a template in the future

CXX = g++
CXXFLAGS = -Wall -ggdb -std=c++11
INCLUDES = -lcurl

main: main.o readJSONFile.o
	$(CXX) $(CXXFLAGS) -o main main.o readJSONFile.o $(INCLUDES)
	make a.exe
	make clean

main.o: main.cpp main.h
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f *.o

a.exe: main.o readJSONFile.o
	$(CXX) $(CXXFLAGS) -o a.exe main.o readJSONFile.o $(INCLUDES)

rapidJSON: rapidJSON.cpp
	$(CXX) $(CXXFLAGS) -o rapidJSON rapidJSON.cpp

readJSONFile: readJSONFile.cpp readJSONFile.h
	$(CXX) $(CXXFLAGS) -o readJSONFile readJSONFile.cpp

readJSONFile.o: readJSONFile.cpp readJSONFile.h
	$(CXX) $(CXXFLAGS) -c readJSONFile.cpp
