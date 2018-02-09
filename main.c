/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 13:54:24 by oseng             #+#    #+#             */
/*   Updated: 2018/01/11 14:21:09 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
// #include <stdlib.h>

int main (int ac, char **av) {
  puts("coucou");
  char *m;
  char *n;
  // m = malloc(sizeof(int));
  puts("coucou");
  m = malloc(137999999);
  n = malloc(137999999);

  m = "lol";
  n = "lol2";

  puts(m);
  puts(n);
  return 0;
}


// int main()
// {
//   int i;
//   char *addr;
//
//   i = 0;
//   while (i < 1024)
//   {
//     i++;
//   }
//   return (0);
// }
