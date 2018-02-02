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
	if (size <= TINY && !global_env.tiny)
	{
		if (!(global_env.tiny = mmap(0, getpagesize() * (4), PROT_READ | PROT_WRITE, MAP_ANON |
		MAP_PRIVATE, -1, 0)))
			return (FALSE);
		ft_putstr("init Tiny\n");
		init_header_tiny(global_env.tiny);
	}
	if (size <= SMALL && !global_env.small)
	{
		if (!(global_env.small = mmap(0, getpagesize() * (26), PROT_READ | PROT_WRITE, MAP_ANON |
		MAP_PRIVATE, -1, 0)))
			return (FALSE);
		ft_putstr("init small\n");
		init_header_small(global_env.small);
	}
	return (ok);
}

void			*malloc(size_t size)
{
	ft_putnbr(size);
	ft_putstr(" go malloc \n\n");
	t_header	*current_head;
	void 		*base;

	// print_all();
	ft_puthexa((unsigned long)global_env.tiny);
	ft_putstr("\n");
	current_head = NULL;
	if (!size)
		return (NULL);
	if (!init(size))
		return (NULL);
	if (size <= TINY)
		current_head = find_empty_bloc(size, global_env.tiny, TINY);
	else if (size <= SMALL)
		current_head = find_empty_bloc(size, global_env.small, SMALL);
	else
		current_head = find_empty_bloc(size, global_env.large, LARGE);
		// current_head = find_empty_bloc_tiny(size);
		// current_head = find_empty_bloc_small(size);
	if (current_head)
	{
		current_head->free = FALSE;
		current_head->size = size;
		return current_head + META_SIZE_HEAD;
	}
	else if (current_head == NULL)
		// ft_putstr("MALLOC pas TROUVE\n");
		create_new_tiny(size);// ! il faut recuperer le pointeur
	//===========
	// print_all();
	//===========
	ft_putstr("\n\n ===============\n\n ");
	ft_puthexa((unsigned long)global_env.tiny);
	ft_putstr("\n ");
	ft_puthexa((unsigned long)global_env.small);

	ft_putstr("\nGROS NULL ");
	return (NULL);
	ft_putstr("my malloc \n");

	base = mmap(0, getpagesize() * 2, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	return (base);
}

void			*realloc(void *ptr, size_t size)
{
	(void)ptr;
	(void)size;
	ft_putstr("REALLOC\n");
	return (ptr);
}

void			show_alloc_mem()
{
	return ;
}
