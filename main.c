#include "tclisp.h"

char *command(const char **src)
{
  const char *fnc = lparam(src, command, false);

  if (strcmp(fnc, "print") == 0) {
    char *value;
    while ((value = lparam(src, command, false))) {
      printf("%s \n", value);
    }
    lendparam(src);
    return "";
  } else if (strcmp(fnc, "add") == 0) {
    double number = 0;
    char *value;
    while ((value = lparam(src, command, false))) {
      number += strtod(value, NULL);
    }
    char *buf = malloc(32);
    snprintf(buf, 32, "%g", number);
    lendparam(src);
    return buf;
  } else if (strcmp(fnc, "do") == 0) {
    char *value, *validvalue = ""; 
    while ((value = lparam(src, command, false)))
      validvalue = value;
    lendparam(src);
    return validvalue;
  } else if (strcmp(fnc, "repeat") == 0) {
    long long times = strtoll(lparam(src, command, false), NULL, 0);
    char *value = lparam(src, command, true);
    lendparam(src);
    for (int i=0; i<times; i++) {
      const char *ptr = value;
      lexec(&ptr, command, false);
    } 
    return "";
  }

  return "";
}

int main()
{
  const char *input =
    "(repeat 10 (do\n"
      "(print 'hi')\n"
      "print (add 1 2 3 4 5))\n"
    ")";
  while ((lskipspace(&input), *input))
    lexec(&input, command, false);
  printf("ok\n");
}