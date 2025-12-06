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
  if (**src == '(' || **src == '[') {
    if ((*src)++ && (raw || *start == '[')) {
      while (**src && **src != (*start == '(' ? ')' : ']')) (lexec(src, sexec, raw), lskipspace(src));
      if (!*(*src)++) lerr("mismatched bracket");
      return strncpy((char*)calloc(1, *src-start+1), start, *src-start);
    }
    return sexec(src);
  } else if (**src == '\'' && (*src)++) {
    while (**src && **src != '\'') (*src)++;
    if (!*(*src)++) lerr("unclosed string");
    return strncpy((char*)calloc(1, (*src-1)-start+1), start+1, (*src-1)-(start+1));
  } else if (**src == ')' || **src == ']') lerr("stray bracket");
  else if (**src == 0) lerr("unexpected eof");

  while (**src && **src != '\'' && **src != '(' && **src != ')' && **src != '[' && **src != ']' && !isspace(**src)) (*src)++;
  return strncpy((char*)calloc(1, (*src)-start+1), start, (*src)-start);
}

static char *lparam(const char **src, char *(*sexec)(const char **src), bool raw) {
  return (lskipspace(src), **src == ')') ? NULL : lexec(src, sexec, raw);
}

static void lendparam(const char **src) {
  return (lskipspace(src), **src != ')') ? lerr("expected end of parameters") : (void)(*src)++;
}