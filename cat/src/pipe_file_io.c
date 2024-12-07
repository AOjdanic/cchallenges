#include "../include/cat.h"
#include <stdlib.h>

void pipe_file_io(char *file, char **input_lines) {
  FILE *p_input_file = fopen(file, "r");

  if (!p_input_file) {
    perror("fopen");
    exit(-1);
  }

  pipe_io(p_input_file, input_lines);
  fclose(p_input_file);
}
