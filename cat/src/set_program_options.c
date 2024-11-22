#include "cat.h"

void set_program_options(char **argv, struct options *options) {
  while (*++(*argv)) {
    char current_character = **argv;
    printf("current character: %c\n", current_character);
    if (current_character == 'b') {
      // b overrides n
      options->number_non_empty_lines = 1;
      options->number_all_lines = 0;
    }

    if (current_character == 'e')
      options->ends_of_lines = 1;

    if (current_character == 'n' && options->number_non_empty_lines == 0)
      options->number_all_lines = 1;

    if (current_character == 'h')
      printf("CURRENT CHARACTER IS h\n");

    if (current_character == 's')
      options->squeeze_non_empty_lines = 1;
  }
}
