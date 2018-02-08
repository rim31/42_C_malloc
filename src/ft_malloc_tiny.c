/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_tiny.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 14:22:49 by oseng             #+#    #+#             */
/*   Updated: 2018/01/11 16:39:16 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_header		*init_header_tiny(t_zone *ptr)
{
	int		i;
	t_header 	*tmp;

	// ft_putnbr(META_SIZE_ZONE);
	// ft_putnbr(META_SIZE_HEAD);
	ptr->header = (t_header*)ptr;
	tmp = (void*)ptr->header + META_SIZE_ZONE;//peut etre juste mettre META_SIZE_HEAD plutot
	ptr->header = tmp;
	ptr->next = NULL;
	// ft_puthexa((unsigned long)global_env.tiny);
	i = 1;
	// ft_putstr(" init_tiny_header\n");
	while(i <= 100)//on itere 106x plutot aue 100 car il reste de la place dans la memoire 4* 4096 / 152
	{
		tmp->free = 1;
		tmp->size = 0;
		i++;
		tmp->next = (void*)tmp + META_SIZE_HEAD + TINY;// attention au dernier
		tmp = tmp->next;
	}
	tmp->next = NULL;
	// ft_puthexa((unsigned long)tmp);
	// ft_putstr("\n\n");
	return ((void*)ptr->header + META_SIZE_HEAD + TINY);
}

t_header          *find_empty_bloc_tiny(size_t size)//accomode avec la SIZE 
{
      t_zone      *tiny_zone;
      t_header    *tmp;

      tiny_zone = global_env.tiny;
    //   ft_puthexa((unsigned long)tiny_zone);
      if (size <= TINY)
      {
            while(tiny_zone)
            {
				tmp = global_env.tiny->header;
				while(tmp)// 4* 4096 / 152
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

				tiny_zone = tiny_zone->next ;
            }
      }
	// ft_putstr("NULL !!!!\n");
      return (NULL);///PENSER A RETOURNER le POINTEUR + 28(pour pas ecraser le header)
}

t_header          *find_empty_bloc(size_t size, t_zone *zone, size_t nb_size)
{
    t_header    *tmp;

    while(zone)
    {
        if (zone->header)
		{
			tmp = zone->header;
			// ft_putstr("\n_____vvvv_____\n");
			// ft_puthexa((unsigned long)tmp);
			// ft_putstr("\n_____^^^^_____\n");
		}
        while(tmp)//!! 
        {
			ft_putnbr(tmp->free);
            if (tmp->free && size <= nb_size)
            {
                tmp->free = 0;
				tmp->size = size;
            	// ft_putstr("==> free done !!!!\n");
                return (tmp);
            }
            tmp = tmp->next;
        }
        zone = zone->next ;
    }
	return (NULL);
}

t_header			*create_new_tiny(size_t size)
{
	t_zone 		*tiny_zone;
	t_zone 		*new_tiny;
	t_header 	*tmp;
	int 	i;

	i = 0;
	(void)size;
	// if (size <= TINY)
	// 	ft_putstr("create new Tiny\n");
	tiny_zone = (t_zone*)global_env.tiny;
	while(tiny_zone->next)
		tiny_zone = tiny_zone->next ;
	if (!(new_tiny = mmap(0, getpagesize() * (4), PROT_READ | PROT_WRITE, MAP_ANON |
	MAP_PRIVATE, -1, 0)))
		return (NULL);//RISQUE DE SEGFAULT , ilfaut vaut mieux mettre un EXIT(0)
	// ft_puthexa((unsigned long)new_tiny);
	tiny_zone->next = new_tiny;
	new_tiny->next = NULL;
	// ft_putstr("-< ");
	// ft_puthexa((unsigned long)global_env.tiny->next); //// (!) SEGFAULT (!)
	// ft_putstr(" >-\n");
	// ft_putstr("Joined new Tiny\n");

	tmp = init_header_tiny(new_tiny);

	// ft_putstr("new tiny created\n");
	return (tmp);
}
