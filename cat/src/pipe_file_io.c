#include "../include/cat.h"
#include <stdlib.h>

FILE *p_input_file;

void pipe_file_io(char file[], struct options *options, char **input_lines) {
  p_input_file = fopen(file, "r");

  if (!p_input_file) {
    printf("Error: can\'t open the specified file: %s\n", file);
    exit(1);
  }

  pipe_io(p_input_file, options, input_lines);
  fclose(p_input_file);
}
