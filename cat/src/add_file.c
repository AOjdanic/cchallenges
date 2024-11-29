#include "../include/cat.h"
#include <ctype.h>
#include <string.h>

void add_file(char file[MAX_FILENAME_LENGTH], char argv[]) {
  static int index = 0;

  int i = 0;

  strcpy(file, argv);

  while (!isspace(*file)) {
    i++;
    file++;
  }
  file[i] = '\0';

  index++;
};
