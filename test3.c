
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

  addr1 = (char*)malloc(16);
  strcpy(addr1, "Bonjours\n");
  print(addr1);
  addr3 = (char*)realloc(addr1, 18);
  addr3[18] = 42;
  print(addr3);
  return (0);
}
