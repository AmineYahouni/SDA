CC= gcc
CXXFLAGS= -Wall -ansi --pedantic -O3

CPP_O_FILE = Tas.o analyzer.o main.o
LIB = -lm


all: $(CPP_O_FILE)
	$(CC) $(CXXFLAGS) -o main $(CPP_O_FILE) $(LIB)

clean:
	rm -rf *.o
	rm -rf *~
	rm -rf main
