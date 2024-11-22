#include "../include/cat.h"

void copy_input_to_output(
  FILE *p_input_file,
  struct options *options,
  char **array_of_line_pointers) {

  unsigned long max_value_64 = 18446744073709551615UL;
  static int line_number = 1;

  int line_length;
  while ((line_length =
            getline(array_of_line_pointers, &max_value_64, p_input_file)) > 0) {
    if (line_length >= MAX_LENGTH_OF_LINE) {
      perror("Line longer than allowed");
      return;
    }

    if (options->number_all_lines)
      fprintf(stdout, "\t%d ", line_number);

    if (options->ends_of_lines) {
      (*array_of_line_pointers)[line_length - 1] = '$';
      (*array_of_line_pointers)[line_length] = '\n';
      (*array_of_line_pointers)[line_length + 1] = '\0';
    }

    fprintf(stdout, "%s", *array_of_line_pointers);
    array_of_line_pointers++;
    line_number++;
  }
}
