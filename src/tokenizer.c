#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"

// Returns true if c is a whitespace character ('\t' or ' ')
int space_char(char c) {
  return (c == ' ' || c == '\t');
}

// Returns true if c is a non-whitespace character (not tab or space)
int non_space_char(char c) {
  return (c != ' ' && c != '\t');
}

// Returns a pointer to the first character of the next space-separated word in str
char *word_start(char *str) {
  while (*str != '\0' && space_char(*str)) {
    str++;
  }
  return (*str == '\0') ? NULL : str;
}

// Returns a pointer to the character following the end of the word pointed to by word
char *word_terminator(char *word) {
  while (*word != '\0' && non_space_char(*word)) {
    word++;
  }
  return word;
}

// Counts the number of words in str
int count_words(char *str) {
  int count = 0;
  char *ptr = str;

  while ((ptr = word_start(ptr)) != NULL) {
    count++;
    ptr = word_terminator(ptr);
  }

  return count;
}

// Copies len characters from inStr into a new dynamically allocated string
char *copy_str(char *inStr, short len) {
  char *outStr = (char *)malloc((len + 1) * sizeof(char));
  if (outStr == NULL) {
    fprintf(stderr, "Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }
  strncpy(outStr, inStr, len);
  outStr[len] = '\0'; // Ensure null termination
  return outStr;
}

// Tokenizes str into an array of tokens
char **tokenize(char *str) {
  int num_tokens = count_words(str);
  char **tokens = (char **)malloc((num_tokens + 1) * sizeof(char *));
  if (tokens == NULL) {
    fprintf(stderr, "Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }

  int token_index = 0;
  char *ptr = str;

  while ((ptr = word_start(ptr)) != NULL) {
    char *end = word_terminator(ptr);
    int token_len = end - ptr;
    tokens[token_index++] = copy_str(ptr, token_len);
    ptr = end;
  }

  tokens[token_index] = NULL; // Null terminator at the end of tokens array
  return tokens;
}

// Prints all tokens in the tokens array
void print_tokens(char **tokens) {
  for (int i = 0; tokens[i] != NULL; i++) {
    printf("tokens[%d] = \"%s\"\n", i, tokens[i]);
  }
}

// Frees memory allocated for tokens and the tokens array itself
void free_tokens(char **tokens) {
  for (int i = 0; tokens[i] != NULL; i++) {
    free(tokens[i]);
  }
  free(tokens);
}
