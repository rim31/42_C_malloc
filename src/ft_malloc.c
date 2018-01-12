/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 14:22:49 by oseng             #+#    #+#             */
/*   Updated: 2018/01/11 16:39:16 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_header		*init_tiny_header(t_zone *ptr)
{
	int		i;
	t_header 	*tmp;

	ptr->header = (t_header*)ptr;
	tmp = ptr->header;
	i = 1;
	while(i < 106)//on itere 106x plutot aue 100 car il reste de la place dans la memoire 4* 4096 / 152
	{
		tmp->free = TRUE;
		if (i < 100)                //test find_empty_bloc
                  tmp->free = FALSE;    //test find_empty_bloc
            tmp->size = 0;
		tmp->next = (void*)tmp + META_SIZE_HEAD + TINY;
		tmp = tmp->next;
		i++;
	}
	tmp->next = NULL;
	return (tmp);
}

void              *find_empty_bloc(size_t size)
{
      t_zone      *tiny_head;
      t_header    *tmp;


      tiny_head = global_env.tiny;
      if (size <= TINY)
      {
            while(tiny_head->next)
            {
                  tmp = (t_header*)tiny_head;
                  while(tmp->next)//on itere 106x plutot aue 100 car il reste de la place dans la memoire 4* 4096 / 152
                  {
                        ft_putstr("?");
                        if (tmp->free == TRUE)
                              return ((void*)tmp);
                        tmp = tmp->next;
                  }
            tiny_head = tiny_head->next ;
            }
      }
      return (NULL);
}
