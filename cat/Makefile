CC = gcc
CFLAGS = -Wall -Iinclude
SRCS = src/oacat.c src/add_filename_to_file_list.c src/copy_file_input_to_output.c src/copy_input_to_output.c src/set_program_options.c
OBJS = $(SRCS:.c=.o)
TARGET = build/oacat

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

