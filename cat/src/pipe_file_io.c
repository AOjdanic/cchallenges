#include "../include/cat.h"
#include <stdlib.h>

void pipe_file_io(char *file) {
  FILE *p_input_file = fopen(file, "r");

  if (!p_input_file) {
    perror("fopen");
    exit(-1);
  }

  pipe_io(p_input_file);
  fclose(p_input_file);
}
