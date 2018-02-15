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

	ptr->header = (t_header*)ptr;
	tmp = (void*)ptr->header + META_SIZE_ZONE;
	ptr->header = tmp;
	ptr->next = NULL;
	i = 1;
	while(i <= 100)
	{
		tmp->free = 1;
		tmp->size = 0;
		i++;
		tmp->next = (void*)tmp + META_SIZE_HEAD + TINY;
		tmp = tmp->next;
	}
	tmp->next = NULL;
	return ((void*)ptr->header + META_SIZE_HEAD + TINY);
}

t_header          *find_empty_bloc_tiny(size_t size)
{
      t_zone      *tiny_zone;
      t_header    *tmp;

      tiny_zone = global_env.tiny;
      if (size <= TINY)
      {
        while(tiny_zone)
        {
					tmp = global_env.tiny->header;
					while(tmp)
					{
						if (!tmp->free)
							return (NULL);
						else if (tmp->free == 1)
							return (tmp);
						tmp = tmp->next;
					}
					tiny_zone = tiny_zone->next ;
        }
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
	tiny_zone = (t_zone*)global_env.tiny;
	while(tiny_zone->next)
		tiny_zone = tiny_zone->next ;
	if (!(new_tiny = mmap(0, getpagesize() * (4), PROT_READ | PROT_WRITE, MAP_ANON |
	MAP_PRIVATE, -1, 0)))
		return (NULL);
	tiny_zone->next = new_tiny;
	new_tiny->next = NULL;
	tmp = init_header_tiny(new_tiny);
	return (tmp);
}
