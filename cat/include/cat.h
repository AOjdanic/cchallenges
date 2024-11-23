#include <stdbool.h>
#include <stdio.h>

#define MAX_LENGTH_OF_LINE 1024
#define MAX_AMOUNT_OF_LINES 10000

struct options {
  int number_all_lines;
  int ends_of_lines;
  int squeeze_non_empty_lines;
  int number_non_empty_lines;
};

void add_filename_to_file_list(char **files, char **argv);

void copy_input_to_output(
  FILE *p_input_file,
  struct options *options,
  char **array_of_line_pointers);

void set_program_options(char **argv, struct options *options);

void copy_file_input_to_output(
  char **p_files,
  struct options options,
  char **array_of_line_pointers);

bool is_empty_line(char **line);
