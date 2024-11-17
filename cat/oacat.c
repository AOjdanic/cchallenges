#include <assert.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
  FILE *p_input_file;
  int character;

  if (*(argv + 1) == NULL || strstr(*(argv + 1), "-")) {
    while ((character = getc(stdin)) != EOF) {
      putchar(character);
    }
    if (EOF)
      return 0;
  }

  p_input_file = fopen(*(argv + 1), "r");
  assert(p_input_file);

  while ((character = getc(p_input_file)) != EOF) {
    putchar(character);
  }

  return 0;
}
