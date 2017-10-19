
#include  "includes/malloc.h"

int main()
{
int i;
char *addr;

i = 0;
while (i < 1024)
{
addr = (char*)malloc(10);
addr[0] = 42;
free(addr);
i++;
}
return (0);
}
