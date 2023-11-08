CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -lglfw -lGL
SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:src/%.c=obj/%.o)
EXECUTABLE = bin/gltest

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p obj bin
	$(CC) $^ -o $@ $(LDFLAGS) -lglfw -lGL

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)