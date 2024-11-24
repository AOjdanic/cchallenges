#include "../include/cat.h"

void add_file(char **files, char **argv) {
  static int index = 0;

  files[index] = *argv;
  index++;
};
