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
	// else if (size <= SMALL && !global_env.small)
	// {
	// 	if (!(global_env.small = mmap(0, getpagesize() * (26), PROT_READ | PROT_WRITE, MAP_ANON |
	// 	MAP_PRIVATE, -1, 0)))
	// 		return (FALSE);
	// 	ft_putstr("init Small\n");
	// }
	// else if (!global_env.large)
	// {
	// 	if (!(global_env.large = mmap(0, getpagesize() * (size), PROT_READ | PROT_WRITE, MAP_ANON |
	// 	MAP_PRIVATE, -1, 0)))
	// 		return (FALSE);
	// 	ft_putstr("init large\n");
	// }
	return (ok);
}

void			*malloc(size_t size)
{
	t_zone	*current_zone;
	t_header	*current_head;
	void 		*base;

	(void)current_zone;
	if (!size)
		return (NULL);
	if (!init(size))
		return (NULL);
	current_head = find_empty_bloc(size);

	if (current_head == NULL)
		create_new_tiny(size);// ! il faut recuperer le pointeur
	//===========
	print_list((t_header*)global_env.tiny);
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
