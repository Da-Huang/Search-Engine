CXXFLAGS = -std=c++0x -g -Wall
LDFLAGS = -lrt -pthread -pg -g -Wall
LD = g++
CXX = g++

TEXT_TEMPLATE = "\033[36mTEXT\033[0m"

TARGET = main

SOURCE_FILES = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SOURCE_FILES))
DEPS = $(patsubst %.cpp,%.d,$(SOURCE_FILES))
#OBJS = $(SOURCE_FILES:.cpp=.o)
#DEPS = $(SOURCE_FILES:.cpp=.d)

%.o: %.cpp
	@echo $(subst TEXT,"Compiling $< and Generating its Dependencies ...",$(TEXT_TEMPLATE))
	$(CXX) -c $(CXXFLAGS) -MMD -o $@ $<

$(TARGET): $(OBJS)
	@echo $(subst TEXT,"Generating Target file: $@",$(TEXT_TEMPLATE))
	$(LD) $^ -o $@ $(LDFLAGS)

-include $(DEPS)

clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS) *.out

.PHONY: clean
