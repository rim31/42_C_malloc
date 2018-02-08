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
#include <stdlib.h>

int main (int ac, char **av) {
  puts("coucou");
  char *m;
  // m = malloc(sizeof(int));
  puts("coucou");
  m = malloc(42);

  m = "lol";

  puts(m);
  return 0;
}
