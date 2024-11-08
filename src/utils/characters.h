#ifndef UTILS_CHARACTERS_H
#define UTILS_CHARACTERS_H

#include "lexer/tokens.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Returns 1 if the character is a letter. Else, return 0.
 */
int is_alpha(const char character);

/**
 * Returns 1 if the character is a number. Else, return 0.
 */
int is_numeric(const char character);

/**
 * Returns 1 if the character is either a number or a letter.
 * Else, return 0.
 */
int is_alphanumerical(const char character);

/**
 * Returns the token ID (see TokenType) if the character is a symbol (glyph). 
 * Else, return 0.
 */
TokenType is_glyph(const char character);

/**
 * Returns 1 if word is a number. Else, return 0.
 */
int is_number(const char *word, int idx);

/**
 * Returns 1 if the word is a valid identifier
 * (follows regex [_a-zA-Z0-9]{1,20})
 */
int is_identifier(const char *word, int idx);

#endif // UTILS_CHARACTERS_H