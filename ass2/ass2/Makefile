SYSTEMC_ARCH=macosx64
#SYSTEMC_ARCH=macosx

SYSTEMC=/Users/hamza/Documents/Developer/SourceCode/systemc-2.3.2
LIB_DIRS=$(SYSTEMC)/lib-$(SYSTEMC_ARCH)

# Include directories
INCLUDE_DIRS = -I$(SYSTEMC)/include

# header files used, for dependency checking
HEADERS = define.h simple_bus.h bus.hpp memory.hpp SW.hpp HW.hpp

# source files used, for dependency checking
SOURCES = main.cpp SW.cpp memory.cpp HW.cpp bus.cpp
# source files used, for dependency checking
SOURCES2 = main.cpp SW.cpp memory.cpp HW.cpp utime_bus.cpp

DEPENDENCIES = \
	Makefile \
	$(HEADERS) \
	$(SOURCES)

LIBS = -lsystemc -lstdc++ -w -lm -std=c++98

TESTS = main
TESTS2 = main2

timed: $(TESTS)
	./$(TESTS)
	
untimed: $(TESTS2)
	./$(TESTS2)

$(TESTS): $(DEPENDENCIES)
	g++ -o $@ $(SOURCES) $(INCLUDE_DIRS) -L$(LIB_DIRS) $(LIBS)

$(TESTS2): $(DEPENDENCIES)
	g++ -o $@ $(SOURCES2) $(INCLUDE_DIRS) -L$(LIB_DIRS) $(LIBS)

clean:
	rm -f $(TESTS) *.dat
	rm -f $(TESTS2) *.dat
