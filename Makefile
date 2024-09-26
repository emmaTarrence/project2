CC=g++
CFLAGS=-std=c++17 -Wall -g


# The source files we use for building custom_tests
ALL_SRC=$(wildcard *.hpp *.h *cpp)

# The name of the resulting executable
APP=test

custom_tests:
	$(CC) $(CFLAGS) -o $(APP) $(ALL_SRC)

clean:
	rm -f $(APP)
