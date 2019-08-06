SRCS = $(wildcard *.cpp)
TRGS = $(patsubst %.cpp, ./bin/%, $(SRCS))


OPTS := -O3 -Wno-write-strings -g
ROOTLIBS := $(shell root-config --glibs --libs --evelibs) 
ROOTCFLAGS := $(shell root-config --cflags)

# Where we have our libraries
LIBDIR = `pwd`/rqlib

# The general CFLAGS
CPPFLAGS := $(OPTS) $(ROOTCFLAGS)

# The general libs
LIBS := $(ROOTLIBS) 

ifdef CUDAPATH
CUDA_DEFINES=-DCUDA
endif

ifdef MULTITHREAD
OMP_DEFINES=-DMULTITHREAD
CPPFLAGS += -fopenmp
endif

all : $(TRGS)

./bin/% : %.cpp
	g++ $(CPPFLAGS) $(INCLUDES) -o $@ $< -L$(LIBDIR) $(LIBS) -l:rqlib.so

# Remove the executables
clean:
	rm -f ./bin/*
