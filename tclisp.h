#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

static void lerr(const char *msg) {
  fprintf(stderr, "error: %s\n", msg);
  exit(1);
}

static void lskipspace(const char **src) {
  while (isspace(**src)) (*src)++;
}

static char *lexec(const char **src, char *(*sexec)(const char **src), bool raw) {
  const char *start = (lskipspace(src), *src);
  if (**src == 0) {
    lerr("unexpected eof");
  } else if (**src == '(') {
    if (raw) {
      const char *start = (*src)++;
      while (**src && **src != ')') (lexec(src, sexec, raw), lskipspace(src));
      if (!*src) lerr("mismatched (");
      const char *end = ++(*src);
      return strncpy((char*)calloc(1, end-start+1), start, end-start);
    }
    return sexec(((*src)++, src));
  } else if (**src == '\'') {
    const char *start = ++(*src);
    while (**src && **src != '\'') (*src)++;
    const char *end = *src;
    if (!*(*src)++) lerr("unclosed string");
    return strncpy((char*)calloc(1, end-start+1), start, end-start);
  } else if (**src == ')') lerr("stray )");

  while (**src && **src != '\'' && **src != '(' && **src != ')' && !isspace(**src)) (*src)++;
  return strncpy((char*)calloc(1, (*src)-start+1), start, (*src)-start);
}

static char *lparam(const char **src, char *(*sexec)(const char **src), bool raw) {
  if (lskipspace(src), **src == ')') return NULL;
  return lexec(src, sexec, raw);
}

static void lendparam(const char **src) {
  if (lskipspace(src), **src != ')') lerr("expected end of parameters");
  (*src)++;
}