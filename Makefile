CC=gcc
BIN=dancing-cube

OBJS=dancing-cube.o
CFLAGS=-g -Wall -pedantic
LDFLAGS=-lGL -lglut -lGLU

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(BIN)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(BIN)

.PHONY: clean
