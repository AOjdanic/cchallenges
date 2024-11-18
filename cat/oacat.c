#include <stdio.h>
#include <stdlib.h>

struct flags {
  int number_all_lines;
  int ends_of_lines;
  int squeeze_non_empty_lines;
  int number_non_empty_lines;
};

int main(int argc, char **argv) {
  FILE *p_input_file;
  int character;
  int number_of_lines = 1;
  struct flags flags = {0, 0, 0, 0};
  char **file_arguments = (char **)malloc(argc * sizeof(char *));
  int position_in_arguments = 0;

  if (argc == 1) {
    while ((character = getc(stdin)) != EOF) {
      putchar(character);
    }
    exit(0);
  }

  while (--argc > 0) {
    ++argv;
    char *address_of_current_character = *argv;
    if (**argv == '-' && ((*++(address_of_current_character)) != '\0')) {
      while (*++(*argv)) {
        char current_character = **argv;
        printf("current character: %c\n", current_character);
        if (current_character == 'b') {
          // b overrides n
          flags.number_non_empty_lines = 1;
          flags.number_all_lines = 0;
          printf("CURRENT CHARACTER IS b\n");
        }
        if (current_character == 'e') {
          flags.ends_of_lines = 1;
          printf("CURRENT CHARACTER IS e\n");
        }
        if (current_character == 'n') {
          if (flags.number_non_empty_lines == 0) {
            flags.number_all_lines = 1;
          }
          printf("CURRENT CHARACTER IS n\n");
        }
        if (current_character == 'h') {
          // print help/usage
          printf("CURRENT CHARACTER IS h\n");
        }
        if (current_character == 's') {
          flags.squeeze_non_empty_lines = 1;
          printf("CURRENT CHARACTER IS s\n");
        }
      }
    } else {
      file_arguments[position_in_arguments] = *argv;
      position_in_arguments++;
    }
  }

  printf("%d, %d, %d, %d\n", flags.squeeze_non_empty_lines,
         flags.number_non_empty_lines, flags.number_all_lines,
         flags.ends_of_lines);

  while (*file_arguments) {

    if (**file_arguments == '-' && (*++(*file_arguments) == '\0')) {
      while ((character = getc(stdin)) != EOF) {
        putchar(character);
      }
    } else {
      p_input_file = fopen(*(file_arguments), "r");

      if (!p_input_file) {
        printf("Error: can\'t open the specified file: %s\n", *file_arguments);
        exit(1);
      }

      while ((character = getc(p_input_file)) != EOF) {
        putchar(character);
      }
      fclose(p_input_file);
    }

    file_arguments++;
  }

  free(file_arguments);
  exit(0);
}
