#include "utils/characters.h"

extern const GlyphMap glyphs[LANGUAGE_GLYPHS_NUMBER];

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

TokenType is_glyph(const char character) {
  // Glyphs used in the language such as {}.

  for (int i = 0; i < LANGUAGE_GLYPHS_NUMBER; i++) {
    if (character == glyphs[i].glyph) {
      return glyphs[i].glyph_id;
    }
  }

  return UNKNOWN_TOKEN;
}

int is_number(const char *word, int idx) {
  const char current = word[idx];

  if (idx > MAX_NUMBER_LENGTH) {
    return 0;
  }

  // Iterate until end of string (needs a well-formatted string.)
  if (current == '\0') {
    return 1;
  }

  if (is_numeric(current)) {
    return is_number(word, idx + 1);
  }

  return 0;
}

int is_identifier(const char *word, int idx) {
  const char current = word[idx];

  if (idx > MAX_IDENTIFIER_LENGTH) {
    return 0;
  }

  // Iterate until end of string (needs a well-formatted string.)
  if (current == '\0') {
    return 1;
  }

  if (is_alphanumerical(current) || current == '_') {
    return is_identifier(word, idx + 1);
  }

  return 0;
}
