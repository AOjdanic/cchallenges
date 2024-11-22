#include "cat.h"

void add_filename_to_file_list(char **files, char **argv) {
  static int position_in_arguments = 0;

  files[position_in_arguments] = *argv;
  position_in_arguments++;
};
