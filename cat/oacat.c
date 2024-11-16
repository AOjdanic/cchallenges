#include <assert.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
  FILE *p_input_file;
  int character;
  p_input_file = fopen(*(argv + 1), "r");
  assert(p_input_file);

  while ((character = getc(p_input_file)) != EOF) {
    putchar(character);
  }

  return 0;
}
