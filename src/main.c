#include "lexer/lex.h"
#include <stdio.h>
#include <stdlib.h>

#define PROJECT_VERSION "v0.0.0"

void help(const char *project_name) {

  const char *help_prompt = "usage: ./compiler <file>.c\n";

  fprintf(stdout, "%s %s\n%s", project_name, PROJECT_VERSION, help_prompt);
}

int main(int argc, char **argv) {

  if (argc < 2) {
    fprintf(stderr, "No argument given.\n");
    help(argv[0]);
    exit(-1);
  }

  fprintf(stdout, "Compiling file %s\n", argv[1]);

  lex(argv[1]);

  return 0;
}
