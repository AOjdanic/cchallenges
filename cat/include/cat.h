#include <stdbool.h>
#include <stdio.h>

#define MAX_LINES 10000
#define MAX_LINE_LENGTH 1024

struct options {
  int mark_ends;
  int squeeze_lines;
  int enumerate_lines;
  int enumerate_all_lines;
};

bool is_empty_line(char **line);
void add_file(char **files, char **argv);
void set_options(char **argv, struct options *options);
void pipe_io(FILE *p_input_file, struct options *options, char **input_lines);
void pipe_file_io(char **p_files, struct options *options, char **input_lines);
