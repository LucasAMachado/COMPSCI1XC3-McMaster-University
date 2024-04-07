# Define compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Define the target executable
TARGET = mySA

# Default target
all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

# Clean target for removing compiled objects and the executable
clean:
	$(RM) $(TARGET)
