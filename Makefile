# Basic Makefile Template
# 4/4/16

# Project name  (GZipNameAndComments)
PROJECT = gznac

# Use GCC for c files
CC := gcc

# Include all .c source files
SOURCES := $(wildcard *.c)

# Name objects after sources
OBJS := $(SOURCES:.c=.o)

# Place any non-standard header paths here, -I will be appended by the 'foreach'
INC :=
INCLUDES=$(foreach d, $(INC), -I$d)
CFLAGS := -o2 $(INCLUDES)

# Target for linking the final executable. Call the compiler as a linker 
# to avoid specifying all the default settings and paths. 
.DEFAULT: GzipNameAndComments
$(PROJECT): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

# Target for turning sources into objects 
# Note - this is nearly identical to the default but I like
#        to explicitly write it out so there's no confustion
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
	
# Clean target for convenience
.PHONY: clean
clean:
	rm -vf $(OBJS) $(PROJECT)