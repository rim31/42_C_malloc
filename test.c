//#include <stdlib.h>
#include "malloc.h"
//#include

int main (int ac, char **av) {

  int *m;
  m = malloc(sizeof(int));

  *m = 10;


  //free(m);

  return 0;
}
