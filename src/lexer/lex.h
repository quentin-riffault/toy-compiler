
#ifndef LEX_H
#define LEX_H

#define WORD_BUFFER_SIZE 80
#define CODE_BUFFER_SIZE 80
#define MAX_TOKENS 100

typedef enum TokenType {
  UNKOWN_TOKEN = 0,
  OPEN_PAR = 1,
  CLOSE_PAR = 2,
  OPEN_CURL = 3,
  CLOSE_CURL = 4,
  SEMICOLON = 5,
  WHITESPACE = 6,
  CARRIAGE_RETURN = 7,
  TAB = 8,
  C_KEYWORD = 9,
  LITERAL = 10,
  IDENTIFIER = 11

} TokenType;

typedef struct Token {
  TokenType type;
  char *value;
} Token;

int get_next_word(const char *sentence, const int begin, const int max_length,
                  char *word_buffer);
int lex(const char *filepath, Token *token_list);

#endif // LEX_H