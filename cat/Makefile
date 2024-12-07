CC = gcc
FLAGS = -Wall -Iinclude 
SRCS = src/ccat.c src/is_empty_line.c src/pipe_file_io.c src/pipe_io.c 
OBJS = $(patsubst src/%.c, build/%.o, $(SRCS))
TARGET = build/ccat

run: all clean 

all: $(TARGET) 

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

build/%.o: src/%.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
