#include "../include/cat.h"
#include <stdio.h>
#include <stdlib.h>

void set_options(char argv[], struct options *options) {
  for (int i = 0; argv[i] != false; i++) {
    char current_character = argv[i];

    if (current_character == 'b') {
      options->enumerate_lines = 1;
      options->enumerate_all_lines = 0; // b overrides n
    } else if (current_character == 'e') {
      options->mark_ends = 1;
    } else if (current_character == 'n' && options->enumerate_lines == 0) {
      options->enumerate_all_lines = 1;
    } else if (current_character == 'h') {
      printf(HELP);
      exit(0);
    } else if (current_character == 's') {
      options->squeeze_lines = 1;
    } else {
      printf(
        "Invalid option provided: -%c. Type oacat -h to get tips on usage\n",
        current_character);
      exit(1);
    }
  }
}
