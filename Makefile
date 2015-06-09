.PHONY: clean

INCLUDES      = include
CPP           = g++
CFLAGS	      = -Wall -Wextra -pedantic -D_FILE_OFFSET_BITS=64 -O3 --std=c++11
LINKFLAGS     =

CFLAGS += -MMD $(addprefix -I,$(INCLUDES))

EXE_O_FILES = $(patsubst %.cc,build/%.o,$(wildcard *.cc))
EXECUTABLES = $(patsubst build/%.o,bin/%,$(EXE_O_FILES))

SOURCES = $(shell find -name "*.cc")
O_FILES = $(patsubst ./%.cc,build/%.o,$(SOURCES))
OTHER_O_FILES = $(filter-out $(EXE_O_FILES),$(O_FILES))

.SECONDARY: $(O_FILES)

all: $(EXECUTABLES)

bin:
	@echo "Making $@ directory"
	@mkdir $@

bin/%: build/%.o $(OTHER_O_FILES) | bin
	@echo "Compiling $@"
	@$(CPP) $^ $(LINKFLAGS) -o $@

-include $(shell find "build" -name "*.d" 2> /dev/null)

build/%.o: %.cc
	@echo "Compiling $@"
	@mkdir -p $(dir $@)
	@$(CPP) -c $< -o $@ $(CFLAGS)

clean:
	@echo "Cleaning up"
	@rm -rf build
	@rm -rf bin