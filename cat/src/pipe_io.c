#include "../include/cat.h"
#include <stdio.h>

bool is_empty_line(char **line);

void pipe_io(FILE *p_input_file, struct options *options, char **input_lines) {

  unsigned long max_value_64 = 18446744073709551615UL;
  static int line_number = 1;

  int line_length;

  while ((line_length = getline(input_lines, &max_value_64, p_input_file)) >
         0) {
    if (line_length >= MAX_LINE_LENGTH) {
      perror("Line longer than allowed");
      return;
    }

    if (is_empty_line(input_lines) && options->squeeze_lines) {
      input_lines++;
      line_number++;
      continue;
    }

    if (options->enumerate_lines == 1 && !is_empty_line(input_lines)) {
      fprintf(stdout, "\t%d ", line_number);
      line_number--;
    }

    if (options->enumerate_all_lines)
      fprintf(stdout, "\t%d ", line_number);

    if (options->mark_ends) {
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
