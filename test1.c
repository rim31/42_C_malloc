
// #include  "malloc.h"
#include <stdlib.h>

int main()
{
    int i;
    char *addr;

    i = 0;
    while (i < 1024)
    {
        addr = (char*)malloc(10);
        addr[0] = 42;
        i++;
    }
    return (0);
}



