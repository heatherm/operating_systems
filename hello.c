#include "hello.h"
#include <stdio.h>

int main()
{
  puts(hello());
  return 0;
}

const char *hello(void)
{
  return "Hello World";
}
