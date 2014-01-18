CXX = g++
CFLAGS = -g

TARGETS = test_array  btree test_queue test_stack test_list test_dict
LIBS = 

SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

EXE = $(patsubst %,%.o,$(TARGETS))
NOEXEOBJS = $(filter-out $(EXE),$(OBJS))


all: ${TARGETS}

$(TARGETS): %:$(NOEXEOBJS) %.o
	$(CXX) $(CFLAGS) $^  -o $@
$(OBJS): %.o :%.cpp
	$(CXX) $(CFLAGS) $< -c -o $@

clean:
	rm -f *.o $(TARGETS) core

