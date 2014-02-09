CXXFLAGS = -std=c++0x -g
LDFLAGS = -lrt -pthread -pg -g
LD = g++
CXX = g++
main: main.o
	$(LD) main.o -o main $(LDFLAGS)

main.o:

clean:
	rm main *.out *.o -f
