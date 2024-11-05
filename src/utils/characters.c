#include "utils/characters.h"

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
