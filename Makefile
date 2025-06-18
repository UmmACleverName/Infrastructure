CXX      =  g++
FLAGS    = -g -Wall  
STD      = -std=c++20
INCLUDES = -I. 
DEBUG    = -DDEBUG=0
LIBS     = -pthread 
OBJFILES = main.o logger.o 
OtheFILE = tasking.o taskmanager.o

all: main

%.o: src/%.cpp
	$(CXX) $(DEBUG) $(FLAGS) $(INCLUDES) $(STD) -c $^

%.o: tac/src/%.cpp
	$(CXX) $(DEBUG) $(FLAGS) $(INCLUDES) $(STD) -c $^

.PHONY: main
main: $(OBJFILES) $(OtheFILE)  
	$(CXX) $(LIBS) $(DEBUG) $(FLAGS) $(INCLUDES) $(STD) -o $@.exe $^ 
	mv $^ ./bin/
	mv $@.exe ./bin/

.PHONY: clean
clean:
	@rm -f ./bin/*
