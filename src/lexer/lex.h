
#ifndef LEX_H
#define LEX_H

#define WORD_BUFFER_SIZE 80
#define CODE_BUFFER_SIZE 80
int get_next_word(const char *sentence, const int begin, const int max_length);
void lex(const char *filepath);
void test_get_next_word();

#endif // LEX_H