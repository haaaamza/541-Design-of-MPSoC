SYSTEMC_ARCH=macosx64
#SYSTEMC_ARCH=macosx

SYSTEMC=/Users/hamza/Documents/Developer/SourceCode/systemc-2.3.2
LIB_DIRS=$(SYSTEMC)/lib-$(SYSTEMC_ARCH)

# Include directories
INCLUDE_DIRS = -I$(SYSTEMC)/include

# header files used, for dependency checking
HEADERS = define.h SADcomp.h simple_mem_if.hpp memRead.hpp memorySystem.h mem_RTL.hpp oscillator.hpp

# source files used, for dependency checking
SOURCES = main.cpp SADcomp.cpp memory.cpp memorySystem.cpp oscillator.cpp mem_RTL.cpp

DEPENDENCIES = \
	Makefile \
	$(HEADERS) \
	$(SOURCES)

LIBS = -lsystemc -lstdc++ -w -lm -std=c++98

TESTS = main

all: $(TESTS)
	#./$(TESTS) rtl mem_init.txt

$(TESTS): $(DEPENDENCIES)
	g++ -o $@ $(SOURCES) $(INCLUDE_DIRS) -L$(LIB_DIRS) $(LIBS)

clean:
	rm -f $(TESTS) *.dat