#ifndef UTILS_CHARACTERS_H
#define UTILS_CHARACTERS_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int is_alpha(const char character);
int is_numeric(const char character);
int is_alphanumerical(const char character);
int is_glyph(const char character);

#endif // UTILS_CHARACTERS_H