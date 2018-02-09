/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_large.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 14:22:49 by oseng             #+#    #+#             */
/*   Updated: 2018/01/11 16:39:16 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_header		*init_header_large(t_zone *ptr)
{
	ft_putstr("\n_____init head large_____\n");
	t_header 	*tmp;

	ptr->header = (t_header*)ptr;
	tmp = (void*)ptr->header + META_SIZE_ZONE;//peut etre juste mettre META_SIZE_HEAD plutot
	ptr->header = tmp;
	ptr->next = NULL;
		tmp->free = 1;
		tmp->size = META_SIZE_ZONE + META_SIZE_HEAD + 1;
		tmp->next = NULL;
	ft_putstr("\n_____end init head large_____\n");
	return ((void*)ptr->header + META_SIZE_ZONE + META_SIZE_HEAD + 1);
}

t_header          *find_empty_bloc_large(size_t size)//accomode avec la SIZE
{
	ft_putstr("\n_____find empty large_____\n");

  t_zone      *large_zone;
  t_header    *tmp;

	print_all();
  large_zone = global_env.large;
	(void)size;
  while(large_zone)
  {
		tmp = global_env.large->header;
		ft_puthexa((unsigned long)tmp);
		ft_putstr("\n");
		ft_putnbr(tmp->free);
		ft_putstr("\n_____^^ find large ^^_____\n");
		while(tmp)// 4* 4096 / 152
		{
			ft_puthexa((unsigned long)tmp);
			ft_putstr("\n");
			ft_putnbr(tmp->free);
			ft_putstr("\n_____^^ find large ^^_____\n");
				if (tmp->free == 1)
			return (tmp);
			tmp = tmp->next;
		}
		large_zone = large_zone->next ;
  }
	ft_putstr("\n_____end find empty large_____\n");
  return (NULL);///PENSER A RETOURNER le POINTEUR + 28(pour pas ecraser le header)
}


t_header			*create_new_large(size_t size)
{
	t_zone 		*large_zone;
	t_zone 		*new_large;
	t_header 	*tmp;
	int 	i;

	i = 0;
	(void)size;

	large_zone = (t_zone*)global_env.large;
	ft_puthexa((unsigned long)large_zone);
	ft_putstr("\n_____^^ glob large ^^_____\n");
	while(large_zone->next)
		large_zone = large_zone->next ;
	if (!(new_large = mmap(0, getpagesize() * ((size / 4096) + 1), PROT_READ | PROT_WRITE, MAP_ANON |
	MAP_PRIVATE, -1, 0)))
		return (NULL);//RISQUE DE SEGFAULT , ilfaut vaut mieux mettre un EXIT(0)
	large_zone->next = new_large;
	new_large->next = NULL;

	tmp = init_header_large(new_large);

	return (tmp);
}
