CC = gcc
CFLAGS = -Wall -Iinclude
SRCS = src/oacat.c src/add_file.c src/is_empty_line.c src/pipe_file_io.c src/pipe_io.c src/set_options.c
OBJS = $(patsubst src/%.c, build/%.o, $(SRCS))
TARGET = build/oacat

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
