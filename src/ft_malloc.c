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

	ft_putnbr(META_SIZE_ZONE);
	ft_putnbr(META_SIZE_HEAD);
	ptr->header = (t_header*)ptr;
	tmp = (void*)ptr->header + META_SIZE_ZONE;//peut etre juste mettre META_SIZE_HEAD plutot
	ptr->next = NULL;
	i = 1;
	ft_putstr("init_tiny_header\n");
	while(i < 105)//on itere 106x plutot aue 100 car il reste de la place dans la memoire 4* 4096 / 152
	{
		tmp->free = TRUE;
		if (i < 105)                //test find_empty_bloc 106 max
            {
			tmp->free = FALSE;    //test find_empty_bloc
			ft_putstr(".");
		}
		tmp->size = 0;
		tmp->next = (void*)tmp + META_SIZE_HEAD + TINY;
		tmp = tmp->next;
		i++;
	}
	tmp->next = NULL;
	ft_putstr("\n");
	return (tmp);
}

t_header          *find_empty_bloc(size_t size)
{
      t_zone      *tiny_head;
      t_header    *tmp;

      tiny_head = global_env.tiny;
      ft_puthexa((unsigned long)tiny_head);
      if (size <= TINY)
      {
		ft_putstr("find find_empty_tiny_bloc\n");
            while(tiny_head)
            {
                  ft_puthexa((unsigned long)tiny_head);
                  tmp = (t_header*)tiny_head;
                  // ft_puthexa((unsigned long)tmp);
                  while(tmp->next)//on itere 106x plutot aue 100 car il reste de la place dans la memoire 4* 4096 / 152
                  {
				// ft_putstr(" ? ");
                        // if (!tmp->free)
                        //       ft_putstr("F");
                        // else
				// {
                        //       ft_putstr("_Trouve ");
				// 	ft_puthexa((unsigned long)tmp);
				// 	return ((t_header*)tmp);
				// }
                        // if (!tmp->size)
                        //       ft_putstr("S");
                        // else
                        //       ft_putstr(".");
                        if (tmp->free == TRUE)
                              return (tmp);
                        tmp = tmp->next;
                  }
                  tiny_head = tiny_head->next ;
            }
      }
      return (NULL);///PENSER A RETOURNER le POINTEUR + 28(pour pas ecraser le header)
}


t_zone		*create_new_tiny(size_t size)
{
	t_zone 	*tiny_head;
	t_zone 	*new_tiny;
	t_header	*tmp;
	int 		i;

	i = 0;
	if (size <= TINY)
		ft_putstr("create new Tiny\n");
	tiny_head = (t_zone*)global_env.tiny;
	while(tiny_head)
		tiny_head = tiny_head->next ;
	if (!(new_tiny = mmap(0, getpagesize() * (4), PROT_READ | PROT_WRITE, MAP_ANON |
	MAP_PRIVATE, -1, 0)))
		return (NULL);//RISQUE DE SEGFAULT , ilfaut vaut mieux mettre un EXIT(0)
	ft_puthexa((unsigned long)new_tiny);
	ft_putstr("Join new Tiny\n");
	tiny_head->next = new_tiny;
	ft_putstr("TEST ?\n");
	ft_puthexa((unsigned long)tiny_head->next); //// (!) SEGFAULT (!)
	new_tiny->next = NULL;
	ft_putstr("Joined new Tiny\n");
	ft_puthexa((unsigned long)new_tiny);
	tmp = (void*)new_tiny + META_SIZE_ZONE;//peut etre juste mettre META_SIZE_HEAD plutot
	ft_putstr("100 blocks in  new_tiny\n");
	while(i < 105)//on itere 106x plutot aue 100 car il reste de la place dans la memoire 4* 4096 / 152
	{
		tmp->free = TRUE;
		tmp->size = 0;
		tmp->next = (void*)tmp + META_SIZE_HEAD + TINY;
		tmp = tmp->next;
		i++;
	}
	ft_putstr("new tiny created\n");
	return (new_tiny);
}
