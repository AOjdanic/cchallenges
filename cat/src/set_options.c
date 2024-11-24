#include "../include/cat.h"

void set_options(char **argv, struct options *options) {
  while (*++(*argv)) {
    char current_character = **argv;

    if (current_character == 'b') {
      // b overrides n
      options->enumerate_lines = 1;
      options->enumerate_all_lines = 0;
    }

    if (current_character == 'e')
      options->mark_ends = 1;

    if (current_character == 'n' && options->enumerate_lines == 0)
      options->enumerate_all_lines = 1;

    if (current_character == 'h')
      printf("CURRENT CHARACTER IS h\n");

    if (current_character == 's')
      options->squeeze_lines = 1;
  }
}
