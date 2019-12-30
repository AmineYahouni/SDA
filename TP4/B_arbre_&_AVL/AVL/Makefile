CC= gcc
CXXFLAGS= -Wall -ansi --pedantic -O3

CPP_O_FILE = Avl.o analyzer.o 
LIB = -lm


all: $(CPP_O_FILE)
	$(CC) $(CXXFLAGS) -o main $(CPP_O_FILE) $(LIB)

clean:
	rm -rf *.o
	rm -rf *~
	rm -rf main
