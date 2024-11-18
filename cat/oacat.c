#include <stdio.h>
#include <stdlib.h>

struct options {
  int number_all_lines;
  int ends_of_lines;
  int squeeze_non_empty_lines;
  int number_non_empty_lines;
};

FILE *p_input_file;
int character;
int number_of_lines = 1;
int position_in_arguments = 0;
struct options options = {0, 0, 0, 0};

void set_program_options(char **argv, struct options *options) {
  while (*++(*argv)) {
    char current_character = **argv;
    printf("current character: %c\n", current_character);
    if (current_character == 'b') {
      // b overrides n
      options->number_non_empty_lines = 1;
      options->number_all_lines = 0;
    }

    if (current_character == 'e')
      options->ends_of_lines = 1;

    if (current_character == 'n' && options->number_non_empty_lines == 0)
      options->number_all_lines = 1;

    if (current_character == 'h')
      printf("CURRENT CHARACTER IS h\n");

    if (current_character == 's')
      options->squeeze_non_empty_lines = 1;
  }
}

void add_filename_to_file_list(char **files, char **argv,
                               int *position_in_arguments) {
  files[*position_in_arguments] = *argv;
  (*position_in_arguments)++;
};

void copy_input_to_output(FILE *p_input_file, FILE *p_output_file) {
  while ((character = getc(p_input_file)) != EOF) {
    putc(character, p_output_file);
  }
}
int main(int argc, char **argv) {
  char **files = malloc(argc * sizeof(char *));

  if (argc == 1) {
    copy_input_to_output(stdin, stdout);
    exit(0);
  }

  while (--argc > 0) {
    ++argv;
    char *address_of_current_character = *argv;
    int is_an_option_argument =
        **argv == '-' && ((*++(address_of_current_character)) != '\0');

    if (is_an_option_argument)
      set_program_options(argv, &options);
    else
      add_filename_to_file_list(files, argv, &position_in_arguments);
  }

  printf("%d, %d, %d, %d\n", options.squeeze_non_empty_lines,
         options.number_non_empty_lines, options.number_all_lines,
         options.ends_of_lines);

  while (*files) {
    int filename_is_minus = **files == '-' && (*++(*files) == '\0');

    if (filename_is_minus)
      copy_input_to_output(stdin, stdout);
    else {
      p_input_file = fopen(*files, "r");

      if (!p_input_file) {
        printf("Error: can\'t open the specified file: %s\n", *files);
        exit(1);
      }

      copy_input_to_output(p_input_file, stdout);
      fclose(p_input_file);
    }

    files++;
  }

  free(*files);
  exit(0);
}
