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
		init_tiny_header(global_env.tiny);
	}
	return (ok);
}

void			*malloc(size_t size)
{
	// ft_putnbr(size);
	ft_putstr("\ngo malloc \n\n");
	t_header	*current_head;
	void 		*base;

	print_all();
	ft_puthexa((unsigned long)global_env.tiny);
	ft_putstr("\n");
	current_head = NULL;
	if (!size)
		return (NULL);
	if (!init(size))
		return (NULL);
	current_head = find_empty_bloc(size);
	if (current_head)
	{
		current_head->free = FALSE;
		current_head->size = size;
		return current_head + META_SIZE_HEAD;
	}
	// else if (current_head == NULL)
	// 	create_new_tiny(size);// ! il faut recuperer le pointeur
	//===========
	print_all();
	//===========
	ft_putstr("GROS NULL ");
	return (NULL);
	ft_putstr("my malloc \n");

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
