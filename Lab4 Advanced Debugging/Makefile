# Makefile for compiling various C programs that demonstrate common issues in C programming

# Compiler to use
CC = gcc

# Compiler flags:
# -g    Adds debugging information to the executable file
# -Wall Turns on most, but not all, compiler warnings
CFLAGS = -g -Wall

# Define the target executables
TARGETS = dead_lock leak_memory race_condition seg_fault

# Default target: build all programs
all: $(TARGETS)

# Rule to build dead_lock
dead_lock: dead_lock.c
	$(CC) $(CFLAGS) -pthread dead_lock.c -o dead_lock

# Rule to build leak_memory
leak_memory: leak_memory.c
	$(CC) $(CFLAGS) leak_memory.c -o leak_memory

# Rule to build race_condition
race_condition: race_condition.c
	$(CC) $(CFLAGS) -pthread race_condition.c -o race_condition

# Rule to build seg_fault
seg_fault: seg_fault.c
	$(CC) $(CFLAGS) seg_fault.c -o seg_fault

# Clean target to remove executable files
clean:
	rm -f $(TARGETS)

# Phony target to ensure that 'make clean' works even if a file named 'clean' exists
.PHONY: clean
