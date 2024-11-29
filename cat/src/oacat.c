#include "../include/cat.h"
#include <stdio.h>
#include <stdlib.h>

struct options options = {0, 0, 0, 0};

void free_files(char **files, int argc) {
  for (int i = 0; i < argc; i++) {
    free(files[i]);
  }
  free(files);
}

void free_input_lines(char **input_lines) {
  for (int i = 0; i < MAX_LINES; i++) {
    free(input_lines[i]);
  }
  free(input_lines);
}

int main(int argc, char *argv[]) {
  char **input_lines = malloc(MAX_LINES * sizeof(char *));

  if (!input_lines) {
    printf("Memory allocation failed for input_lines");
    exit(1);
  }

  for (int i = 0; i < MAX_LINES; i++) {
    input_lines[i] = malloc(MAX_LINE_LENGTH * sizeof(char));
    if (!input_lines[i]) {
      perror("memory allocation failed for member of input_lines");
      free(input_lines);
      exit(1);
    }
  }

  if (argc == 1) {
    pipe_io(stdin, &options, input_lines);
    free_input_lines(input_lines);
    exit(0);
  }

  char files[argc][MAX_FILENAME_LENGTH];

  int file_index = 0;

  for (int i = 1; i < argc; i++) {
    bool is_option = argv[i][0] == '-' && argv[i][1] != '\0';

    if (is_option)
      set_options(argv[i], &options);
    else {
      add_file(files[file_index], argv[i]);
      file_index++;
    }
  }

  if (!files[0]) {
    pipe_io(stdin, &options, input_lines);
    free_input_lines(input_lines);
    exit(0);
  }

  for (int i = 0; i < argc; i++) {
    if (files[i]) {
      bool is_minus = files[i][0] == '-' && files[i][1] == '\0';

      if (is_minus)
        pipe_io(stdin, &options, input_lines);
      else
        pipe_file_io(files[i], &options, input_lines);
    }
  }

  free_input_lines(input_lines);
  exit(0);
}
