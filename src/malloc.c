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
	if (size <= TINY && !global_env.tiny)
	{
		if (!(global_env.tiny = mmap(0, getpagesize() * (4), PROT_READ | PROT_WRITE, MAP_ANON |
		MAP_PRIVATE, -1, 0)))
			return (FALSE);
		// ft_putstr("init Tiny\n");
		init_header_tiny(global_env.tiny);
	}
	if (size <= SMALL && !global_env.small)
	{
		if (!(global_env.small = mmap(0, getpagesize() * (26), PROT_READ | PROT_WRITE, MAP_ANON |
		MAP_PRIVATE, -1, 0)))
			return (FALSE);
		// ft_putstr("init small\n");
		init_header_small(global_env.small);
	}
	if (!global_env.large)
	{
		if (!(global_env.large = mmap(0, getpagesize() * (42), PROT_READ | PROT_WRITE, MAP_ANON |
		MAP_PRIVATE, -1, 0)))
			return (FALSE);
		// ft_putstr("init large\n");
		init_header_large(global_env.large, 42);
	}
	return (TRUE);
}

void			*malloc(size_t size)
{
	ft_putstr("\n\n");
	ft_putnbr(size);
	ft_putstr(" --> go malloc \n\n");
	t_header	*current_head;
	void 		*base;

	current_head = NULL;
	if (!size)
		return (NULL);
	if (!init(size))
		return (NULL);
	if (size <= TINY)
		current_head = find_empty_bloc_tiny(size);
	else if (size <= SMALL)
		current_head = find_empty_bloc_small(size);
	else
		current_head = find_empty_bloc_large(size);
	ft_putstr("\n_____malloc-find_empty_bloc_____\n");
	ft_puthexa((unsigned long)current_head);
	if (current_head)
	{
		current_head->free = FALSE;
		current_head->size = size;
		return ((void*)current_head + META_SIZE_HEAD);
	}
	else
	{
		ft_putstr("MALLOC pas TROUVE\n");
		if (size <= TINY)
			base =  create_new_tiny(size);// ! il faut recuperer le pointeur
		else if (size <= SMALL)
			base = create_new_small(size);// ! il faut recuperer le pointeur
		else
			base = (void*)create_new_large(size);// ! il faut recuperer le pointeur
		// ft_putstr("\n\n ===============\n\n ");
		// ft_puthexa((unsigned long)base);
		// ft_putstr("\n\n ===============\n\n ");
		return base;
	}
	//===========
	// print_all();
	//===========

	// ft_putstr("\nFIN MALLOC ");
	return (NULL);
}

void			*realloc(void *ptr, size_t size)
{
	void 		*tmp;
	void 		*tmp2;
	// print_all();
	tmp2 = NULL;
	if (ptr == NULL)
	{
		tmp = malloc(size);
		ft_putstr("\n======realloc========\n");
		ft_puthexa((unsigned long)tmp);
		return (tmp);
	}
	else
	{
		if (size <= TINY)
			tmp2 = find_empty_bloc_tiny(size);
		else if (size <= SMALL)
			tmp2 = find_empty_bloc_small(size);
		else
			{
				ft_putstr("\n==========LARGE empty block===========\n");
				ft_putnbr(size);
				tmp2 = find_empty_bloc_large(size);
				// return (NULL);
				ft_putstr("\n======LARGE FIND empty block==========\n");
			}
		ft_putstr("\n======realloc2==========\n");

		// ft_putnbr((t_header)tmp2->size);
		ft_putstr("\n");
		if (tmp2)
		{
			ft_puthexa((unsigned long)tmp2);
			ft_putstr(" tmp2 existe\n");
			tmp = ft_memory_copy(tmp2, ptr, size);
		}
		else
			{
				if (size <= TINY)
					tmp = create_new_tiny(size);
				else if (size <= SMALL)
					tmp = create_new_small(size);
				else
					tmp = create_new_large(size);
			}
		ft_puthexa((unsigned long)tmp);
	}
	ft_putstr("\nREALLOC\n");
	return (tmp);
}

void			show_alloc_mem()
{
	return ;
}
