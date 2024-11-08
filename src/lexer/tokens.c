#include "lexer/tokens.h"

const KeywordMap keywords[LANGUAGE_KEYWORDS_NUMBER] = {{3, "int"},
                                                       {6, "return"}};
const char *token_name[LANGUAGE_TOKENS_NUMBER] = {
    "UNKNOWN_TOKEN", "OPEN_PARENTHESIS", "CLOSE_PARENTHESIS", "OPEN_CURL",
    "CLOSE_CURL",    "SEMICOLON",        "WHITESPACE",        "CARRIAGE_RETURN",
    "TAB",           "C_KEYWORD",        "LITERAL",           "IDENTIFIER"};

const GlyphMap glyphs[LANGUAGE_GLYPHS_NUMBER] = {
    {'(', OPEN_PAR},         {')', CLOSE_PAR},      {';', SEMICOLON},
    {'{', OPEN_CURL},        {'}', CLOSE_CURL},     {'+', UNKNOWN_TOKEN},
    {'-', UNKNOWN_TOKEN},    {'*', UNKNOWN_TOKEN},  {'/', UNKNOWN_TOKEN},
    {'>', UNKNOWN_TOKEN},    {'<', UNKNOWN_TOKEN},  {'=', UNKNOWN_TOKEN},
    {'#', UNKNOWN_TOKEN},    {'\'', UNKNOWN_TOKEN}, {'"', UNKNOWN_TOKEN},
    {',', UNKNOWN_TOKEN},    {'!', UNKNOWN_TOKEN},  {' ', WHITESPACE},
    {'\n', CARRIAGE_RETURN}, {'\t', TAB},           {'\0', UNKNOWN_TOKEN}};
