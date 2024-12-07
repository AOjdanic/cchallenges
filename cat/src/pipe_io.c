#include "../include/cat.h"

extern struct Options options;

void pipe_io(FILE *p_input_file, char **input_lines) {
  static int line_number = 1;

  int line_length;
  unsigned long max_line_length = 0;

  while ((line_length = getline(input_lines, &max_line_length, p_input_file)) >
         0) {
    if (is_empty_line(input_lines) && options.squeeze_lines) {
      input_lines++;
      line_number++;
      continue;
    }

    if (options.enumerate_lines && !is_empty_line(input_lines)) {
      fprintf(stdout, "\t%d ", line_number);
    }

    if (options.enumerate_all_lines)
      fprintf(stdout, "\t%d ", line_number);

    if (options.mark_ends) {
      (*input_lines)[line_length - 1] = '$';
      (*input_lines)[line_length] = '\n';
      (*input_lines)[line_length + 1] = '\0';
    }

    fprintf(stdout, "%s", *input_lines);
    if (is_empty_line(input_lines))
      printf("\n");
    input_lines++;
    line_number++;
  }
}
