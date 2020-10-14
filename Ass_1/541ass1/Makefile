SYSTEMC=/Users/hamza/Documents/Developer/SourceCode/systemc-2.3.2/
SYSTEMC_ARCH=linux64
#SYSTEMC_ARCH=linux
LIB_DIRS=$ (SYSTEMC)/lib-$(SYSTEMC_ARCH)

#Include directories
INCLUDE_DIRS = -I. -I$(SYSTEMC)/include

#header files used, for dependency checking
HEADERS = define.h SADcomp.h simple_mem_if.hpp memRead.hpp memorySystem.h mem_RTL.hpp oscillator.hpp

SOURCES = main.cpp SADcomp.cpp memory.cpp memorySystem.cpp oscillator.cpp mem_RTL.cpp

DEPENDENCIES = \
				Makefile \
				$(HEADERS) \
				$(SOURCES)

LIBS= -lsystemc -lstdc++ -lm

TESTS= main

all: $(TESTS)
		./(TESTS)

$(TESTS): $(DEPENDENCIES)
			g++ -o $@ $(SOURCES) $(INCLUDE_DIRS) -I$(LIB_DIRS) $(LIBS)
			
clean:
		rm -f $(TESTS) *.dat

			

