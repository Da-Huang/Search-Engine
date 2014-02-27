all:
	cd .. && make
	
SOURCE_DIR = $(shell find . -type d \( ! -path '*/.*' -o -prune \) \( ! -name ".*" \))
SOURCE_FILES = $(wildcard *.cpp) $(foreach dir,$(SOURCE_DIR),$(wildcard $(dir)/*.cpp))
#$(patsubst %,$(wildcard %/*.cpp),$(SOURCE_DIR))# $(wildcard field/*.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SOURCE_FILES))
DEPS = $(patsubst %.cpp,%.d,$(SOURCE_FILES))
#OBJS = $(SOURCE_FILES:.cpp=.o)
#DEPS = $(SOURCE_FILES:.cpp=.d)

clean:
	$(RM) $(OBJS) $(DEPS)

.PHONY: all clean
