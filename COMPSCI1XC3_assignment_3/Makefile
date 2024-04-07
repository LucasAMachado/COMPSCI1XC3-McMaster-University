# Define the compiler
CC = gcc

# Define any compile-time flags
CFLAGS = -Wall -g

# Define the source file names
SRC = math_matrix.c functions.c

# Define the executable file name
EXEC = math_matrix

# Default target
all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC)

# Clean target for removing compiled binary and object files
clean:
	rm -f $(EXEC) *.o

# Phony targets for commands that do not represent files
.PHONY: all clean
