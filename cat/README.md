# A copycat C implementation of UNIX cat

## Here are program options, which are a subset of original cat:

```
Usage: ccat [option]... [file]...

concatenate file(s) to standard output.
with no file, or when file is -, read standard input.

-b number nonempty output lines, overrides -n
-e display $ at end of each line
-n number all output lines
-s suppress repeated empty output lines
-h display this help and exit

Examples:
 ccat file1 - file2 output file1's contents, then standard input, then file2's contents.
 ccat copy standard input to standard output.
```
