
#ifndef LEX_H
#define LEX_H

#define WORD_BUFFER_SIZE 80
#define CODE_BUFFER_SIZE 80
#define MAX_TOKENS 100

#include "lexer/tokens.h"
#include "utils/characters.h"

typedef struct Token {
  TokenType type;
  char *value;
} Token;

int get_next_word(const char *sentence, const int begin, const int max_length,
                  char *word_buffer);
int lex(const char *filepath, Token *token_list);

#endif // LEX_H