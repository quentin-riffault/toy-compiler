#include "lexer/lex.h"
#include "utils/file.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char word_buffer[WORD_BUFFER_SIZE] = {'\0'};

int is_alpha(const char character) {
  return ((character >= 'a' && character <= 'z') ||
          (character >= 'A' && character <= 'Z'));
}

int is_numeric(const char character) {
  return (character >= '0' && character <= '9');
}

int is_alphanumerical(const char character) {
  return is_alpha(character) || is_numeric(character);
}

int is_glyph(const char character) {
  // Glyphs used in the language such as {}.
  const char glyphs[] = {'(', ')', ';', '{', '}',  '+',  '-',
                         '*', '/', '>', '<', '=',  '#',  '\'',
                         '"', ',', '!', ' ', '\n', '\t', '\0'};

  int i = 0;

  while (glyphs[i] != '\0') {
    if (character == glyphs[i]) {
      return 1;
    }
    i++;
  }

  return 0;
}

/**
 * Fetches the next word in the sentence, beginning at index `begin`.
 */
int get_next_word(const char *sentence, const int begin, const int max_length) {

  // Reinit word buffer.
  memset(word_buffer, '\0', sizeof(char) * WORD_BUFFER_SIZE);

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

void lex(const char *filepath) {

  FILE *fd = open_file(filepath, "r");
  const int max_iterations = 100;

  char code_buffer[CODE_BUFFER_SIZE] = {'\0'};

  while (!feof(fd)) {

    memset(code_buffer, '\0', sizeof(char) * CODE_BUFFER_SIZE);

    size_t read = fread(code_buffer, sizeof(char), CODE_BUFFER_SIZE, fd);
    printf("[lex-fd] Read %ld bytes: \n%s\n", read, code_buffer);

    // now, read all words in the current code buffer.
    size_t i = 0;
    int counter = 0;

    while (i < read && counter < max_iterations) {
      printf("[lex-word] %ld, %ld => ", i, read);
      i = get_next_word(code_buffer, i, read);

      // Printing glyphs
      if (word_buffer[1] == '\0') {
        switch (word_buffer[0]) {

        case '\n':
          printf("\\n\n");
          break;

        case '\t':
          printf("\\t\n");
          break;

        default:
          printf("%c\n", word_buffer[0]);
          break;
        }
      } else {
        printf("%s\n", word_buffer);
      }

      counter++;
    }
  }

  close_file(fd);

  fprintf(stdout, "[lex] Completed\n");
}

void test_get_next_word() {
  int offset = 0;
  const char *sentence = "Bonjour 17 \n le monde\n";
  const int max_size = 26;

  int next_end = 0;

  while (next_end < max_size) {
    next_end = get_next_word(sentence, next_end, max_size);
    printf("%d => %s\n", next_end, word_buffer);
  }
}