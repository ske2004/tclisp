#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstdbool>
#include <string>

static void lerr(const char *msg) {
  fprintf(stderr, "error: %s\n", msg);
  exit(1);
}

static void lskipspace(const char **src) {
  while (isspace(**src)) (*src)++;
}

static std::string lexec(const char **src, std::string (*sexec)(const char **src), bool raw = false) {
  const char *start = (lskipspace(src), *src);
  if (**src == 0) {
    lerr("unexpected eof");
  } else if (**src == '(') {
    if (raw) {
      const char *start = (*src)++;
      while (**src && **src != ')') (lexec(src, sexec, raw), lskipspace(src));
      if (!*src) lerr("mismatched (");
      const char *end = ++(*src);
      return std::string(start, end-start);
    }
    return sexec(((*src)++, src));
  } else if (**src == '\'') {
    const char *start = ++(*src);
    while (**src && **src != '\'') (*src)++;
    const char *end = *src;
    if (!*(*src)++) lerr("unclosed string");
    return std::string(start, end-start);
  } else if (**src == ')') lerr("stray )");

  while (**src && **src != '\'' && **src != '(' && **src != ')' && !isspace(**src)) (*src)++;
  return std::string(start, (*src)-start);
}

static std::string lparam(const char **src, std::string (*sexec)(const char **src), bool raw = false) {
  if (lskipspace(src), **src == ')') return "'ENDOFPARAMS";
  return lexec(src, sexec, raw);
}

static void lendparam(const char **src) {
  if (lskipspace(src), **src != ')') lerr("expected end of parameters");
  (*src)++;
}