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

	ptr->header = (t_header*)ptr  + META_SIZE_ZONE;
	tmp = (void*)ptr->header;
	ptr->header = tmp;
	ptr->next = NULL;
	i = 1;
	while(i <= 100)
	{
		tmp->free = 1;
		tmp->size = 0;
		i++;
		tmp->next = (void*)tmp + META_SIZE_HEAD + SMALL;
		tmp = tmp->next;
	}
	tmp->next = NULL;
	return ((void*)ptr->header + META_SIZE_HEAD + TINY);
}

t_header          *find_empty_bloc_small(size_t size)//accomode avec la SIZE
{
	t_zone      *small_zone;
	t_header    *tmp;

	small_zone = global_env.small;
	if (size <= SMALL)
	{
		while(small_zone)
		{
			tmp = global_env.small->header;
			while(tmp)
			{
				if (tmp->free == 1)
					return (tmp);
				tmp = tmp->next;
			}

			small_zone = small_zone->next ;
		}
	}
	return (NULL);
}

t_header		*create_new_small(size_t size)
{
	t_zone 		*small_zone;
	t_zone 		*new_small;
	t_header 	*tmp;

	(void)size;
	small_zone = (t_zone*)global_env.small;
	while(small_zone->next)
	small_zone = small_zone->next ;
	if (!(new_small = mmap(0, getpagesize() * (4), PROT_READ | PROT_WRITE, MAP_ANON |
	MAP_PRIVATE, -1, 0)))
	return (NULL);
	small_zone->next = new_small;
	new_small->next = NULL;
	tmp = init_header_small(new_small);
	return (tmp);
}
