CC=gcc
BIN=dancing-cube

OBJS=dancing-cube.o cubes.o transforms.o materials.o utils.o
CFLAGS=-g -Wall -pedantic
LDFLAGS=-lGL -lglut -lGLU -lm

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(BIN)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(BIN)

.PHONY: clean
