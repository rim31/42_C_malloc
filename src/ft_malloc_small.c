/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_small.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 14:22:49 by oseng             #+#    #+#             */
/*   Updated: 2018/01/11 16:39:16 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_header		*init_header_small(t_zone *ptr)
{
	int		i;
	t_header 	*tmp;

	// ft_putnbr(META_SIZE_ZONE);
	// ft_putnbr(META_SIZE_HEAD);
	ptr->header = (t_header*)ptr;
	tmp = (void*)ptr->header + META_SIZE_ZONE;//peut etre juste mettre META_SIZE_HEAD plutot
	ptr->header = tmp;
	ptr->next = NULL;
	// ft_puthexa((unsigned long)global_env.small);
	i = 1;
	// ft_putstr(" init_small_header\n");
	while(i <= 100)//on itere 106x plutot aue 100 car il reste de la place dans la memoire 4* 4096 / 152
	{
		tmp->free = 1;
		tmp->size = 0;
		i++;
		tmp->next = (void*)tmp + META_SIZE_HEAD + SMALL;// attention au dernier
		tmp = tmp->next;
	}
	tmp->next = NULL;
	// ft_puthexa((unsigned long)tmp);
	// ft_putstr("\n\n");
	return ((void*)ptr->header + META_SIZE_HEAD + TINY);
	// return (tmp);
}

t_header          *find_empty_bloc_small(size_t size)//accomode avec la SIZE 
{
      t_zone      *small_zone;
      t_header    *tmp;

      small_zone = global_env.small;
    //   ft_puthexa((unsigned long)small_zone);
      if (size <= SMALL)
      {
            while(small_zone)
            {
                  tmp = global_env.small->header;
                  while(tmp)//on itere 103x plutot aue 100 car il reste de la place dans la memoire 4* 4096 / 152
                  {
					// ft_putstr(" ");
					// ft_puthexa((unsigned long)tmp);
					// ft_putstr("    ");
					// ft_putnbr(tmp->free);
					// ft_putstr("    ");
					// ft_putnbr(tmp->size);
					// ft_putstr("\n");
                        if (tmp->free == 1)
					return (tmp);
                        tmp = tmp->next;
                  }

                  small_zone = small_zone->next ;
            }
      }
	// ft_putstr("NULL !!!!\n");
      return (NULL);///PENSER A RETOURNER le POINTEUR + 28(pour pas ecraser le header)
}


t_header		*create_new_small(size_t size)
{
	t_zone 	*small_zone;
	t_zone 	*new_small;
	t_header 	*tmp;
	int 		i;

	i = 0;
	// if (size <= SMALL)
	// 	ft_putstr("create new Small\n");
	(void)size;
	small_zone = (t_zone*)global_env.small;
	while(small_zone->next)
		small_zone = small_zone->next ;
	if (!(new_small = mmap(0, getpagesize() * (4), PROT_READ | PROT_WRITE, MAP_ANON |
	MAP_PRIVATE, -1, 0)))
		return (NULL);//RISQUE DE SEGFAULT , ilfaut vaut mieux mettre un EXIT(0)
	// ft_puthexa((unsigned long)new_small);
	small_zone->next = new_small;
	new_small->next = NULL;
	// ft_putstr("-< ");
	// ft_puthexa((unsigned long)global_env.small->next); //// (!) SEGFAULT (!)
	// ft_putstr(" >-\n");
	// ft_putstr("Joined new small\n");

	tmp = init_header_small(new_small);

	ft_putstr("new small created\n");
	return (tmp);
}
