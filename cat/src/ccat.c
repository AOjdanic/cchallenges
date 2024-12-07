#include "../include/cat.h"
#include <bits/getopt_core.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>

struct Options options = {0};

int main(int argc, char **argv) {
  char **input_lines = malloc(MAX_LINES * sizeof(char *));
  if (!input_lines) {
    perror("malloc");
    exit(-1);
  }

  if (argc == 1) {
    pipe_io(stdin, input_lines);
    goto END;
  }

  int flag;
  while ((flag = getopt(argc, argv, "bensh")) != -1) {
    switch (flag) {
      case 'n':
        if (!options.enumerate_lines)
          options.enumerate_all_lines = 1;
        break;
      case 'b':
        options.enumerate_all_lines = 0;
        options.enumerate_lines = 1;
        break;
      case 'e':
        options.mark_ends = 1;
        break;
      case 's':
        options.squeeze_lines = 1;
        break;
      case 'h':
        printf(HELP);
        goto END;
        break;
      case '?':
      default:
        printf("Type ccat -h to get tips on usage\n");
        exit(-1);
    }
  }

  if (!argv[optind]) {
    pipe_io(stdin, input_lines);
  }

  while (argv[optind]) {
    if (strcmp(argv[optind], "-") == 0) {
      pipe_io(stdin, input_lines);
      optind++;
      continue;
    }
    pipe_file_io(argv[optind], input_lines);
    optind++;
  }

END:
  exit(0);
}
