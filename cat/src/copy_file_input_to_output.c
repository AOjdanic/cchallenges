#include "../include/cat.h"
#include <stdlib.h>

FILE *p_input_file;

void copy_file_input_to_output(char **p_files, struct options options,
                               char **array_of_line_pointers) {
  p_input_file = fopen(*p_files, "r");

  if (!p_input_file) {
    printf("Error: can\'t open the specified file: %s\n", *p_files);
    exit(1);
  }

  copy_input_to_output(p_input_file, &options, array_of_line_pointers);
  fclose(p_input_file);
}
