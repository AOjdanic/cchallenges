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
void copy_input_to_output(FILE *p_input_file, FILE *p_output_file,
                          struct options *options, int *line_number) {
  while ((character = getc(p_input_file)) != EOF) {
    if (options->ends_of_lines) {
      if (character == '\n') {
        putc('$', p_output_file);
      }
    }
    if (options->number_all_lines && *line_number == 1) {
      fprintf(p_output_file, "\t%d ", *line_number);
      (*line_number)++;
    }
    putc(character, p_output_file);
    if (options->number_all_lines && character == '\n') {
      if ((character = getc(p_input_file))) {
        fprintf(p_output_file, "\t%d ", *line_number);
        ungetc(character, p_input_file);
        (*line_number)++;
      }
    }
  }
}

int main(int argc, char **argv) {
  int line_number = 1;

  if (argc == 1) {
    copy_input_to_output(stdin, stdout, &options, &line_number);
    exit(0);
  }

  char **files = malloc(argc * sizeof(char *));

  if (!files) {
    perror("Memory allocation failed");
    exit(1);
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
  char **p_files = files;

  while (*p_files) {
    int filename_is_minus = **p_files == '-' && (*++(*p_files) == '\0');

    if (filename_is_minus)
      copy_input_to_output(stdin, stdout, &options, &line_number);
    else {
      p_input_file = fopen(*p_files, "r");

      if (!p_input_file) {
        printf("Error: can\'t open the specified file: %s\n", *p_files);
        exit(1);
      }

      copy_input_to_output(p_input_file, stdout, &options, &line_number);
      fclose(p_input_file);
    }

    p_files++;
  }

  free(files);
  p_files = NULL;
  exit(0);
}
