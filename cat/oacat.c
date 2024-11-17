#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  FILE *p_input_file;
  int character;

  if (argc == 1) {
    while ((character = getc(stdin)) != EOF) {
      putchar(character);
    }
  } else {
    while ((*(++argv)) != NULL) {
      printf("-----the pointer value in while loop: %s--------\n", *argv);

      if (**argv == '-' && ((*++(*argv)) != '\0')) {
        printf("first_character_after_minus: %c\n", **argv);
        while (*(*argv)++) {
          char current_character = *(*argv - 1);
          printf("current character: %c\n", current_character);
          if (current_character == 'b') {
            printf("CURRENT CHARACTER IS b\n");
          }
          if (current_character == 'e') {
            printf("CURRENT CHARACTER IS e\n");
          }
          if (current_character == 'n') {
            printf("CURRENT CHARACTER IS n\n");
          }
          if (current_character == 'h') {
            printf("CURRENT CHARACTER IS h\n");
          }
          if (current_character == 's') {
            printf("CURRENT CHARACTER IS s\n");
          }
        }
      }

      // if (**argv == '-') {
      //   while ((character = getchar()) != EOF) {
      //     putchar(character);
      //   }
      //   if (EOF)
      //     continue;
      // }
      //
      // p_input_file = fopen(*(argv), "r");
      //
      // if (!p_input_file) {
      //   printf("Error: can\'t open the specified file: %s\n", *argv);
      //   exit(1);
      // }
      //
      // while ((character = getc(p_input_file)) != EOF) {
      //   putchar(character);
      // }
      // fclose(p_input_file);
    }
  }

  exit(0);
}
