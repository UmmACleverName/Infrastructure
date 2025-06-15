CXX      =  g++
FLAGS    = -g -Wall  
STD      = -std=c++20
INCLUDES = -I. 
DEBUG    = -DDEBUG=0
LIBS     = -pthread 
OBJFILES = main.o tasking.o taskmanager.o logger.o 

all: main

%.o: src/%.cpp
	$(CXX) $(DEBUG) $(FLAGS) $(INCLUDES) $(STD) -c $^

.PHONY: main
main: $(OBJFILES) 
	$(CXX) $(LIBS) $(DEBUG) $(FLAGS) $(INCLUDES) $(STD) -o $@ $^ 
	mv $^ ./bin/
	mv $@ ./bin/

.PHONY: clean
clean:
	@rm -f ./bin/*
