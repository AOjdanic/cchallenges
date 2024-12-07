#include "../include/cat.h"
#include <stdlib.h>

extern struct Options options;

void pipe_io(FILE *p_input_file) {
  static int line_number = 1;

  char *line = NULL;
  ssize_t line_length;
  size_t max_line_length = 0;

  while ((line_length = getline(&line, &max_line_length, p_input_file)) > 0) {
    if (is_empty_line(line) && options.squeeze_lines) {
      line_number++;
      continue;
    }

    if (options.enumerate_lines && !is_empty_line(line)) {
      fprintf(stdout, "\t%d ", line_number);
    }

    if (options.enumerate_all_lines)
      fprintf(stdout, "\t%d ", line_number);

    if (options.mark_ends) {
      (line)[line_length - 1] = '$';
      (line)[line_length] = '\n';
      (line)[line_length + 1] = '\0';
    }

    fprintf(stdout, "%s", line);
    if (is_empty_line(line))
      printf("\n");
    line_number++;
  }

  free(line);
  line = NULL;
}
