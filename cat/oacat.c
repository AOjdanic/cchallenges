#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  FILE *p_input_file;
  int character;

  if (argc == 1) {
    while ((character = getc(stdin)) != EOF) {
      putchar(character);
    }
    if (EOF)
      exit(0);
  }

  while ((*++argv) != NULL) {
    printf("--------------the pointer value in while loop: %s-------------\n",
           *argv);
    if (**argv == '-') {
      while ((character = getchar()) != EOF) {
        putchar(character);
      }
      if (EOF)
        continue;
    }

    p_input_file = fopen(*(argv), "r");

    if (!p_input_file) {
      printf("Error: can\'t open the specified file: %s\n", *argv);
      exit(1);
    }

    while ((character = getc(p_input_file)) != EOF) {
      putchar(character);
    }
    fclose(p_input_file);
  }

  exit(0);
}
