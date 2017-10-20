
#include  "includes/malloc.h"
#define M (1024 * 1024)

void print(char *s)
{
  write(1, s, strlen(s));
}

int main()
{
  char *addr1;
  char *addr3;

  write(1, "test2\n", 6);
  addr1 = (char*)malloc(16);
  write(1, "test2\n", 6);
  strcpy(addr1, "Bonjours\n");
  print(addr1);
  addr3 = (char*)realloc(addr1, 18);
  addr3[18] = 42;
  print(addr3);
  return (0);
}
// make re
// gcc test3.c
// ./run.sh /usr/bin/time -l ./a.out
