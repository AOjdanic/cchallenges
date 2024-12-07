#include "../include/cat.h"
#include <ctype.h>

bool is_empty_line(char *line) {
  while ((*line)) {
    if (!isspace(*line)) {
      return false;
      break;
    }
    (line)++;
  }
  return true;
}
