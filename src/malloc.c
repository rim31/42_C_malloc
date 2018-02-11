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
		init_header_tiny(global_env.tiny);
	}
	if (size <= SMALL && !global_env.small)
	{
		if (!(global_env.small = mmap(0, getpagesize() * (26), PROT_READ | PROT_WRITE, MAP_ANON |
		MAP_PRIVATE, -1, 0)))
			return (FALSE);
		init_header_small(global_env.small);
	}
	if (!global_env.large)
	{
		if (!(global_env.large = mmap(0, getpagesize() * (42), PROT_READ | PROT_WRITE, MAP_ANON |
		MAP_PRIVATE, -1, 0)))
			return (FALSE);
		init_header_large(global_env.large, 42);
	}
	return (TRUE);
}

void			*malloc(size_t size)
{
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
	if (current_head)
	{
		current_head->free = FALSE;
		current_head->size = size;
		return ((void*)current_head + META_SIZE_HEAD);
	}
	else
	{
		if (size <= TINY)
			base =  create_new_tiny(size);
		else if (size <= SMALL)
			base = create_new_small(size);
		else
			base = (void*)create_new_large(size);
		return base;
	}
	//===========
	// print_all();
	//===========
	return (NULL);
}

void			*realloc(void *ptr, size_t size)
{
	void 		*tmp;
	void 		*tmp2;

	tmp2 = NULL;
	tmp = NULL;
	if (ptr == NULL)
		return(malloc(size));
	else if (ptr && size == 0)
		free(ptr);
	else
	{
		if (size <= TINY)
			tmp2 = find_empty_bloc_tiny(size);
		else if (size <= SMALL)
			tmp2 = find_empty_bloc_small(size);
		else
			tmp2 = find_empty_bloc_large(size);
		if (tmp2)
		{
			tmp = ft_memory_copy(tmp2, ptr, size);
			free(ptr);
		}
		else
			{
				if (size <= TINY)
					tmp2 = create_new_tiny(size);
				else if (size <= SMALL)
					tmp2 = create_new_small(size);
				else
					tmp2 = create_new_large(size);
				tmp = ft_memory_copy(tmp2, ptr, size);
				free(ptr);
			}
	}
	return (tmp);
}

void      show_alloc_mem(void)
{
	print_all();
}
