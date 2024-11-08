#ifndef TOKENS_H
#define TOKENS_H

#define MAX_IDENTIFIER_LENGTH 20
#define MAX_NUMBER_LENGTH 20 // max long: 9223372036854775807
#define MAX_KEYWORD_SIZE 10

#define LANGUAGE_KEYWORDS_NUMBER 2
#define LANGUAGE_TOKENS_NUMBER 12
#define LANGUAGE_GLYPHS_NUMBER 21

// TODO
// Lookup metaprogramming for setting TokenTypes, Token numbers and token names.

typedef enum TokenType {
  UNKNOWN_TOKEN = 0,
  OPEN_PAR = 1,
  CLOSE_PAR = 2,
  OPEN_CURL = 3,
  CLOSE_CURL = 4,
  SEMICOLON = 5,
  WHITESPACE = 6,
  CARRIAGE_RETURN = 7,
  TAB = 8,
  C_KEYWORD = 9,
  // At this point, cannot see the difference between "main" (string literal)
  // and main (identifier). String literals will be considered identifiers
  // until parsing (surrounded by a couple of glyphs `'` or `"`).
  LITERAL = 10,
  IDENTIFIER = 11
} TokenType;

typedef struct GlyphMap {
  char glyph;
  TokenType glyph_id;
} GlyphMap;

typedef struct KeywordMap {
  int size;
  char word[MAX_KEYWORD_SIZE];
} KeywordMap;

#endif // TOKENS_H