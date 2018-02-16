/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 14:22:49 by oseng             #+#    #+#             */
/*   Updated: 2018/01/11 16:39:16 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"


void			free_zone(void *ptr, t_zone *zone)
{
    t_header    *tmp;
    int         free_mem;

    free_mem = 0;
    while(zone)
    {
      	// ft_putstr("i adress       free  size\n");
        tmp = ((t_header*)(void*)zone->header + META_SIZE_ZONE);
        while(tmp)
        {
          // ft_puthexa((unsigned long)tmp);
          // ft_putstr("    ");
          // ft_putnbr(tmp->free);
          // ft_putstr("    ");
          // ft_putnbr(tmp->size);
          // ft_putstr("\n");
            if ((void*)tmp == ptr)
            {
                tmp->free = 1;
                tmp->size = 0;
                free_mem = 1;
                break;
            }
            tmp = tmp->next;
        }
        zone = zone->next ;
    }
}

void			free(void *ptr)
{
    free_zone(ptr, global_env.tiny);
    free_zone(ptr, global_env.small);
    free_zone(ptr, global_env.large);
}

void            *ft_realloc(void *ptr, size_t size, t_zone *zone, size_t nb_size)
{
    t_header    *tmp;

    while(zone)
    {
        tmp = zone->header;
        while(tmp)
        {
            if (tmp == ptr && size <= nb_size)
            {
                tmp->free = 0;
				        tmp->size = size;
                return (void*)ptr;
            }
            tmp = tmp->next;
        }
        zone = zone->next ;
    }
    return (void*)ptr;
}




void  *ft_memory_copy(void *src, void *dest, size_t size)
{
	size_t i;
  // t_header  *h_src;
  // t_header  *h_dest;

	i = 0;
	while (i < size && ((unsigned char *)src)[i])
	{
		((unsigned char *)(void*)dest + META_SIZE_HEAD)[i] = ((unsigned char *)src)[i];
		i++;
	}
	// ptr->header = (t_header*)ptr;
	// h_dest = (t_header*)dest;
	// h_dest->free = 0;
	return (dest);
}

// void  *ft_memory_copy(void *src, void *dest, size_t size)
// {
//   size_t			i;
// 	unsigned char	*s1;
// 	unsigned char	*s2;
//   t_header  *h_src;
//   t_header  *h_dest;
//
//   if (src == NULL)
//   {
//       src = malloc(size);
//       h_src = src;
//       return (src);
//   }
//   h_src = src - META_SIZE_HEAD;
//   h_dest = dest - META_SIZE_HEAD;
// 	i = 0;
// 	s1 = (unsigned char *)dest;
// 	s2 = (unsigned char *)src;
// 	// while (s2[i] && i < size)
// 	while (s2[i] && i < size)
// 	{
// 		s1[i] = s2[i];
// 		i++;
// 	}
//   ft_putstr("\n__mem cp__\n");
//   ft_putstr((char*)s2);
//   ft_putstr((char*)s1);
//   ft_putstr("\n__end ^^ mem ^^ cp__\n");
//   h_dest->free = 0;
//   h_dest->size = size;
//   h_src->free = 1;
//   h_src->size = 0;
// 	return (dest);
// }
