#include "lexer/lex.h"
#include "utils/characters.h"
#include "utils/file.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern const KeywordMap keywords[LANGUAGE_KEYWORDS_NUMBER];
extern const char *token_name[LANGUAGE_TOKENS_NUMBER];

/**
 * Fetches the next word in the sentence, beginning at index `begin`.
 */
int get_next_word(const char *sentence, const int begin, const int max_length,
                  char *word_buffer) {

  int buffer_pointer = 0;

  if (begin >= max_length) {
    return -1;
  }

  for (int i = begin; i < max_length; i++) {

    if (buffer_pointer >= WORD_BUFFER_SIZE) {
      // Flushing if at buffer limit.
      return begin + buffer_pointer;
    }

    const char current = sentence[i];

    // Current is alphanumerical. Fetching other characters.
    if (is_alphanumerical(current)) {
      word_buffer[buffer_pointer++] = current;
      continue;
    }

    // A glyph deserves to be alone, they're ~~ specials ! ~~
    if (buffer_pointer == 0 && is_glyph(current)) {
      word_buffer[0] = current;
      return begin + 1;
    }

    // If a glyph is next to an identifier (for instance `main(`)
    // then flushing the word, then going back to the "empty buffer and glyph"
    // situation.
    if (is_glyph(current)) {
      return begin + buffer_pointer;
    }
  }

  return max_length;
}

int match_glyph(const char *word, Token *t) {
  t->type = is_glyph(word[0]);
  return t->type != UNKNOWN_TOKEN;
}

int match_keyword(const char *word, const int word_size, Token *t) {

  for (int i = 0; i < 2; i++) {
    const KeywordMap current = keywords[i];

    if (word_size != current.size) {
      continue;
    }

    if (memcmp(word, current.word, current.size) == 0) {
      t->type = C_KEYWORD;
      return 1;
    }
  }

  return 0;
}

int match_literal(const char *word, Token *t) {
  if (is_number(word, 0)) {
    t->type = LITERAL;
  }
  return t->type != UNKNOWN_TOKEN;
}

Token tokenize(const char *word) {

  int word_size = 0;

  while (word[word_size] != '\0') {
    word_size++;

    if (word_size >= WORD_BUFFER_SIZE) {
      fprintf(
          stderr,
          "[tokenize] Could not infer word size; Word size buffer overflow.\n");
      exit(-1);
    }
  }

  // Following line gives a valgrind read error.
  // char *value = calloc(sizeof(char), word_size);
  // To fix it, add +1 to the word_size.
  // Why +1 ? is it because of trailing \0 ?
  char *value = calloc(sizeof(char), word_size + 1);
  memcpy(value, word, sizeof(char) * word_size);

  Token t = {UNKNOWN_TOKEN, value};

  if (word_size == 1 && match_glyph(word, &t)) {
    return t;
  }

  if (match_keyword(word, word_size, &t)) {
    return t;
  }

  if (is_number(word, 0)) {
    t.type = LITERAL;
    return t;
  }

  if (is_identifier(word, 0)) {
    t.type = IDENTIFIER;
    return t;
  }

  return t;
}

int lex(const char *filepath, Token *token_list) {

  FILE *fd = open_file(filepath, "r");
  const int max_iterations = 100;
  int token_counter = 0;

  while (!feof(fd)) {
    char code_buffer[CODE_BUFFER_SIZE] = {'\0'};

    size_t read = fread(code_buffer, sizeof(char), CODE_BUFFER_SIZE, fd);
    printf("[lex-fd] Read %ld bytes: \n%s\n", read, code_buffer);

    // now, read all words in the current code buffer.

    size_t i = 0;

    while (i < read && token_counter < max_iterations) {
      printf("[lex-word] %ld, %ld => ", i, read);

      char word_buffer[WORD_BUFFER_SIZE] = {'\0'};
      i = get_next_word(code_buffer, i, read, word_buffer);

      // Printing glyphs
      if (word_buffer[1] == '\0') {
        switch (word_buffer[0]) {

        case '\n':
          printf("\\n => ");
          break;

        case '\t':
          printf("\\t => ");
          break;

        default:
          printf("%c => ", word_buffer[0]);
          break;
        }
      } else {
        printf("%s => ", word_buffer);
      }

      const Token token = tokenize(word_buffer);
      printf("%s", token_name[token.type]);

      if (token.value != NULL) {
        printf(" (%s)\n", token.value);
      }

      token_list[token_counter++] = token;
    }
  }

  close_file(fd);

  fprintf(stdout, "[lex] Completed\n");
  return token_counter;
}