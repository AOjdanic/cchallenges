#include "../include/cat.h"
#include <string.h>

void add_file(char file[MAX_FILENAME_LENGTH], char argv[]) {
  static int index = 0;

  strcpy(file, argv);
  index++;
};
