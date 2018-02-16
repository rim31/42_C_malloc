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

t_header		*init_header_large(t_zone *ptr, size_t size)
{
	t_header 	*tmp;

	ptr->header = (t_header*)ptr + META_SIZE_ZONE;
	tmp = (void*)ptr->header;
	ptr->header = tmp;
	ptr->next = NULL;
		tmp->free = 1;
		tmp->size = size;
		tmp->next = NULL;
	return ((void*)ptr->header + META_SIZE_ZONE + META_SIZE_HEAD + 1);
}

t_header      *find_empty_bloc_large(size_t size)
{
  t_zone      *large_zone;
  t_header    *tmp;

  large_zone = global_env.large;
  while(large_zone)
  {
		tmp = global_env.large->header;
		while(tmp)
		{
			if (!tmp->free)
				return (NULL);
			else if (tmp->free == 1 && tmp->size >= size)
				return ((void*)tmp + tmp->size);
			tmp = tmp->next;
		}
		large_zone = large_zone->next ;
  }
  return (NULL);
}


t_header			*create_new_large(size_t size)
{
	t_zone 		*large_zone;
	t_zone 		*new_large;
	t_header 	*tmp;

	large_zone = (t_zone*)global_env.large;
	while(large_zone->next)
		large_zone = large_zone->next;
	if (!(new_large = mmap(0, getpagesize() * ((size / 4096) + 1), PROT_READ | PROT_WRITE, MAP_ANON |
	MAP_PRIVATE, -1, 0)))
		return (NULL);
	large_zone->next = new_large;
	new_large->next = NULL;
	tmp = init_header_large(new_large, size);
	return (tmp);
}
