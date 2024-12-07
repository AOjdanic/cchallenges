#ifndef CAT_H
#define CAT_H
#include <stdbool.h>
#include <stdio.h>

struct Options {
  int mark_ends;
  int squeeze_lines;
  int enumerate_lines;
  int enumerate_all_lines;
};

bool is_empty_line(char *line);
void pipe_io(FILE *p_input_file);
void pipe_file_io(char *file);

#define HELP                                                                   \
  "Usage: ccat [OPTION]... [FILE]... \n"                                       \
  "Concatenate FILE(s) to standard output.\n"                                  \
  "With no FILE, or when FILE is -, read standard input.\n"                    \
  "  -b                       number nonempty output lines, overrides -n\n"    \
  "  -e                       display $ at end of each line\n"                 \
  "  -n                       number all output lines\n"                       \
  "  -s                       suppress repeated empty output lines\n"          \
  "  -h                       display this help and exit\n"                    \
  "Examples:\n"                                                                \
  "  ccat file1 - file2  Output file1's contents, then standard input, then "  \
  "file2's contents.\n"                                                        \
  "  ccat        Copy standard input to standard output.\n"

#endif /* CAT_H */
