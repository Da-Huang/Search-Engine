CXXFLAGS = -std=c++0x -g
LDFLAGS = -lrt -pthread -pg -g
LD = g++
CXX = g++
a: a.o
	$(LD) a.o -o a $(LDFLAGS)

a.o:

clean:
	rm a *.o -f
