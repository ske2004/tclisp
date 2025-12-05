#include "tclisp.hpp"

std::string command(const char **src)
{
  std::string fnc = lparam(src, command);
  std::string value;

  if (fnc == "print") {
    while ((value = lparam(src, command)) != "'ENDOFPARAMS") {
      printf("%s\n", value.c_str());
    }
    lendparam(src);
    return "";
  } else if (fnc == "add") {
    double number = 0;
    std::string value;
    while ((value = lparam(src, command)) != "'ENDOFPARAMS") {
      number += strtod(value.c_str(), NULL);
    }
    char buf[32];
    snprintf(buf, 32, "%g", number);
    lendparam(src);
    return buf;
  } else if (fnc == "do") {
    std::string validvalue = ""; 
    while ((value = lparam(src, command)) != "'ENDOFPARAMS")
      validvalue = value;
    lendparam(src);
    return validvalue;
  } else if (fnc == "repeat") {
    value = lparam(src, command);
    long long times = strtoll(value.c_str(), NULL, 0);
    value = lparam(src, command, true);
    lendparam(src);
    for (int i=0; i<times; i++) {
      const char *ptr = value.c_str();
      lexec(&ptr, command);
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
      "(print (add 1 2 3 4 5))\n"
    "))";
  while ((lskipspace(&input), *input))
    lexec(&input, command);
  printf("ok\n");
}