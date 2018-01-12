/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 14:22:49 by oseng             #+#    #+#             */
/*   Updated: 2018/01/11 16:39:16 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int			init(size_t size)
{
	int		ok;

	ok = TRUE;
	if (size < TINY && !global_env.tiny)
	{
		if (!(global_env.tiny = mmap(0, getpagesize() * (4), PROT_READ | PROT_WRITE, MAP_ANON |
		MAP_PRIVATE, -1, 0)))
			return (FALSE);
		ft_putstr("init Tiny\n");
	}
	return (ok);
}

void			*malloc(size_t size)
{
	t_zone	*current_zone;
	t_header	*current_head;
	void 		*base;

	(void)current_head;
	(void)current_zone;
	if (!size)
		return (NULL);
	// if (size > SMALL)
	// 	return (malloc_large(size));
	if (!init(size))
		return (NULL);
	else
	{
		ft_puthexa((unsigned long)global_env.tiny);	
	}

	// ft_putnbr(TINY);
	ft_putstr("my malloc \n");
	ft_putnbr(sizeof(struct s_header));
	base = mmap(0, getpagesize() * 2, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	return (base);
}

void			free(void *ptr)
{
	(void)ptr;
}

void			*realloc(void *ptr, size_t size)
{
	(void)ptr;
	(void)size;
	return (ptr);
}

void			show_alloc_mem()
{
	return ;
}
