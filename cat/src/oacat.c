#include "../include/cat.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int character;
int number_of_lines = 1;
struct options options = {0, 0, 0, 0};

int main(int argc, char **argv) {
  char **array_of_line_pointers = malloc(MAX_AMOUNT_OF_LINES * sizeof(char *));
  if (!array_of_line_pointers) {
    printf("Memory allocation failed for array_of_line_pointers");
    exit(1);
  }

  if (argc == 1) {
    copy_input_to_output(stdin, &options, array_of_line_pointers);
    exit(0);
  }

  char **files = malloc(argc * sizeof(char *));

  if (!files) {
    perror("Memory allocation failed for files");
    exit(1);
  }

  while (--argc > 0) {
    ++argv;
    char *address_of_current_character = *argv;
    bool is_an_option_argument =
      **argv == '-' && ((*++(address_of_current_character)) != '\0');

    if (is_an_option_argument)
      set_program_options(argv, &options);
    else
      add_filename_to_file_list(files, argv);
  }

  char **p_files = files;

  while (*p_files) {
    bool filename_is_minus = **p_files == '-' && (*++(*p_files) == '\0');

    if (filename_is_minus)
      copy_input_to_output(stdin, &options, array_of_line_pointers);
    else {
      copy_file_input_to_output(p_files, options, array_of_line_pointers);
    }
    p_files++;
  }

  free(files);
  p_files = NULL;
  exit(0);
}
