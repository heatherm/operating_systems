#include <stdio.h>

int main(int argc, char *argv[]) {
  int year = atoi(argv[1]);

  if (year % 4 != 0){
    printf("%d was not a leap year", year);
    return 0;
  }

  if (year % 100 != 0){
    printf("%d was a leap year", year);
    return 0;
  }

  if (year % 400 != 0) {
    printf("%d was not a leap year", year);
    return 0;
  }

  printf("%d was a leap year", year);
  return 0;
}
