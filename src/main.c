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
  Token token_list[MAX_TOKENS];
  int n_token = lex(argv[1], token_list);

  // Free all tokens
  for(int i = 0; i < n_token; i++){
    free(token_list[i].value);
  }

  return 0;
}
