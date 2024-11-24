#include "../include/cat.h"
#include <stdlib.h>
#include <string.h>

struct options options = {0, 0, 0, 0};

int main(int argc, char **argv) {
  char **input_lines = malloc(MAX_LINES * sizeof(char *));
  if (!input_lines) {
    printf("Memory allocation failed for input_lines");
    exit(1);
  }

  if (argc == 1) {
    pipe_io(stdin, &options, input_lines);
    exit(0);
  }

  char **files = malloc(argc * sizeof(char *));

  if (!files) {
    perror("Memory allocation failed for files");
    exit(1);
  }

  while (--argc > 0) {
    ++argv;
    char *current_char = *argv;
    bool is_option = **argv == '-' && ((*++(current_char)) != '\0');

    if (is_option)
      set_options(argv, &options);
    else
      add_file(files, argv);
  }

  char **p_files = files;

  while (*p_files) {
    bool is_minus = **p_files == '-' && (*++(*p_files) == '\0');

    if (is_minus)
      pipe_io(stdin, &options, input_lines);
    else {
      pipe_file_io(p_files, &options, input_lines);
    }
    p_files++;
  }

  free(files);
  p_files = NULL;
  exit(0);
}
