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
	//===========
	// print_all();
	//===========
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
		// ==========
		// ft_putstr("\n=======\n");
		// ft_puthexa((unsigned long)base);
		// ft_putstr("\n=======\n");
		// ==========
		return base;
	}
	return (NULL);
}

<<<<<<< HEAD
// void *find_ptr(void* ptr, t_zone* zone)
// {
// 	t_header    *tmp;
// 	int         free_mem;
//
// 	free_mem = 0;
// 	while(zone)
// 	{
// 			tmp = ((t_header*)(void*)zone->header + META_SIZE_ZONE);
// 			while(tmp)
// 			{
// 					if ((void*)tmp == ptr)
// 							return (ptr);
// 					tmp = tmp->next;
// 			}
// 			zone = zone->next ;
// 	}
// 	return (NULL);
// }

void	*ft_find_data(void *data)
=======

t_header          *find_ptr(void* ptr, t_zone* zone)
{
    t_header    *tmp;

    while(zone)
    {
			tmp = (t_header*)zone->header;
			while(tmp)
			// while(tmp->next)
			{
				if (!tmp->free)
					return (NULL);
				if (ptr == tmp + META_SIZE_HEAD)
					return (ptr);
				tmp = tmp->next;
			}
			zone = zone->next ;
    }
    return (NULL);
}

void			*realloc(void *ptr, size_t size)
>>>>>>> f3a537371292a25ff7c64366df7798130b26c922
{
  t_header *head;
  t_zone *zone;
  int i;
  i = 0;

  while (i < 3)
	{
    i++;
		if (i == 1)
    	zone = (void*)global_env.tiny + META_SIZE_ZONE;
		else if (i == 2)
    	zone = (void*)global_env.small + META_SIZE_ZONE;
		else
	  	zone = (void*)global_env.large + META_SIZE_ZONE;
		if (zone)
		{
			while(zone)
			{
				head = zone->header;
				while(head)
				{
		      if (((void *)head + META_SIZE_HEAD) == data)
		        return head;
		      head = head->next;
		    }
				zone = zone->next;
			}
		}
  }
  return (NULL);
}

void					*find_ptr(void *ptr)
{
    t_header  *tmp;
		t_zone* 	zone;
		int i = 0;

		while (i++ <= 3)
		{
				if (i == 1)
					zone = global_env.tiny;
				else if (i == 2)
					zone = global_env.small;
				else
					zone = global_env.large;
				if (zone != NULL)
				{
					while(zone)
					{
					    tmp = zone->header;
					    while(tmp)
					    {
					        if ((void*)tmp + META_SIZE_HEAD == ptr)
									{
										ft_putstr("find ptr\n");
										return (ptr);
									}
					        tmp = tmp->next;
					    }
					    zone = zone->next ;
						}
				}
		}
		ft_putstr("fin du find ptr\n");
		return (NULL);
}


void			*realloc(void *ptr, size_t size) // penser a augmenter la taille qund c'est possible en gardant le meme pointeur
{
	// ptrtiny   sizesmall
	// ptr - head dans ta list ?
	// si non : malloc normal
	// find small ou creation dun SMALL
  //
	// copy tiny dans small
	void 		*tmp;
	void 		*tmp2;

	tmp2 = NULL;
	tmp = NULL;
	if (!find_ptr(ptr, global_env.tiny))
	{
		if (!find_ptr(ptr, global_env.small))
		{
			if (!find_ptr(ptr, global_env.large))
				ft_putstr("X");
				// return (NULL);
		}
	}

	if (ptr == NULL)
	{
		return(malloc(size));
	}
	if (!find_ptr(ptr))
		// ft_putstr("ptr NULL not find\n");
		return (NULL);
	// else
	// {
	// 	if (((t_head*)ptr)->size) <= size && size <= SMALL)
	// 		((t_head*)ptr)->size = size;
	// }
	if (!ptr)
	{
		ft_putstr("ptr NULL not find\n");
		return(NULL);
	}
	else if (ptr && size == 0)
		free(ptr);
	else
	{
		if (size <= TINY)
		{
<<<<<<< HEAD
			tmp2 = find_empty_bloc_tiny(size);
			if (!tmp2)
				tmp2 = create_new_tiny(size);
		}
		else if (size <= SMALL)
		{
			tmp2 = find_empty_bloc_small(size);
			if (!tmp2)
				tmp2 = create_new_small(size);
		}
		else
		{
			tmp2 = find_empty_bloc_large(size);
			if (!tmp2)
				tmp2 = create_new_large(size);
		}
		if (tmp2)
		{
			ft_putstr("coucou");
			return (NULL);
			tmp = ft_memory_copy(tmp2, ptr, size);
			free(ptr);
		}
		// else
		// {
		// 	return (NULL);
		// 	if (size <= TINY)
		// 		tmp2 = create_new_tiny(size);
		// 	else if (size <= SMALL)
		// 		tmp2 = create_new_small(size);
		// 	else
		// 		tmp2 = create_new_large(size);
		// 	tmp = ft_memory_copy(tmp2, ptr, size);
		// 	free(ptr);
		// }
=======
			tmp2 = (void*)find_empty_bloc_tiny(size);
			if (!tmp2)
				tmp2 = (void*)create_new_tiny(size);
		}
		else if (size <= SMALL)
		{
			tmp2 = (void*)find_empty_bloc_tiny(size);
			if (!tmp2)
				tmp2 = (void*)create_new_tiny(size);
		}
		else
		{
			tmp2 = (void*)find_empty_bloc_large(size);
			if (!tmp2)
				tmp2 = (void*)create_new_large(size);
		}
			// print_all();
		if (!tmp2)
			return(malloc(size));
		tmp = ft_memory_copy(tmp2, ptr, size);
		free(ptr);
>>>>>>> f3a537371292a25ff7c64366df7798130b26c922
	}
	return (tmp);
}

void      show_alloc_mem(void)
{
	print_all();
}
