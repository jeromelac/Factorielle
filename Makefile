# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c99
LDFLAGS = -lm

# Source files
SRCS = main.c bignum.c
OBJS = $(SRCS:.c=.o)

# Target executable
TARGET = factorial

# Default rule
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Rule to compile source files into object files
%.o: %.c bignum.h
	$(CC) $(CFLAGS) -c $< -o $@

# Test executable
TEST_SRCS = test_bignum.c bignum.c
TEST_TARGET = test_bignum

# Rule to build the test executable
test_bignum_objs = test_bignum.o bignum.o
$(TEST_TARGET): $(test_bignum_objs)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(test_bignum_objs) $(LDFLAGS)

# Rule to run tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Rule to clean up build artifacts
clean:
	rm -f $(OBJS) $(test_bignum_objs) $(TARGET) $(TEST_TARGET)

.PHONY: all clean test
