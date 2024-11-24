#ifndef CAT_H
#define CAT_H
#include <stdbool.h>
#include <stdio.h>

#define MAX_LINES 10000
#define MAX_LINE_LENGTH 1024

struct options {
  int mark_ends;
  int squeeze_lines;
  int enumerate_lines;
  int enumerate_all_lines;
};

bool is_empty_line(char **line);
void add_file(char **files, char **argv);
void set_options(char **argv, struct options *options);
void pipe_io(FILE *p_input_file, struct options *options, char **input_lines);
void pipe_file_io(char **p_files, struct options *options, char **input_lines);

#define HELP                                                                   \
  "Usage: oacat [OPTION]... [FILE]... \n"                                      \
  "Concatenate FILE(s) to standard output.\n"                                  \
  "With no FILE, or when FILE is -, read standard input.\n"                    \
  "  -b                       number nonempty output lines, overrides -n\n"    \
  "  -e                       display $ at end of each line\n"                 \
  "  -n                       number all output lines\n"                       \
  "  -s                       suppress repeated empty output lines\n"          \
  "  -h                       display this help and exit\n"                    \
  "Examples:\n"                                                                \
  "  oacat file1 - file2  Output file1's contents, then standard input, then " \
  "file2's contents.\n"                                                        \
  "  oacat        Copy standard input to standard output.\n"

#endif /* CAT_H */
