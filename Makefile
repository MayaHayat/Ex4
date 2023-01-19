
CC = gcc
FLAGS = -Wall
AR = ar

# Creating all
all: graph 

graph: algo.o graph.o main.o
	$(CC) $(FLAGS) -o graph algo.o graph.o main.o

# Create our O files
main.o: main.c graph.h
	$(CC) $(FLAGS) -c main.c

algo.o: algo.c graph.h algo.h
	$(CC) $(FLAGS) -c algo.c

graph.o: graph.c graph.h 
	$(CC) $(FLAGS) -c graph.c


clean:
	rm -rf *.o graph 

.PHONY: all clean 
