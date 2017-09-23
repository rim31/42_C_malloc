/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 18:22:18 by oseng             #+#    #+#             */
/*   Updated: 2017/09/07 18:22:19 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
** creation d'un nouveau maillon
*/
t_block *creation(size_t nb, char *str)
{
  t_block *new;

  // new = (t_block*)malloc(sizeof(t_block));
  if((new = (t_block*)malloc(sizeof(*new))) == NULL)
    return NULL;
  // new->nb = nb;
  // new->str = str;
  new->next = NULL;
  return (new);
}



/*
** fonction pour imprimer la liste chainee
*/
void printlist(t_block *liste)
{
  while(liste)
  {
    // printf("%lu %s ", liste->nb, liste->str);
    liste = liste->next;
  }
}

/*
** fonction mettre un maillon a l'arriere
*/
void pushback(t_block **malist, size_t nb, char *str)
{
  t_block *copie;
  copie = *malist;
  int i;

  i = 0;
  while(copie->next)
  {
    copie = copie->next;
	nb = i;
  }
  copie->next = creation(nb, str);
}
