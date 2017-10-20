/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 15:37:51 by oseng             #+#    #+#             */
/*   Updated: 2017/09/07 15:40:28 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"
#define META_SIZE sizeof(t_block)



void show_alloc_mem(void)
{

}

void ft_init(size_t size)
{
	int i;
	t_block *base;

	i = 0;
	base = mmap(0, getpagesize() * TINY_BLOCK, PROT_READ | PROT_WRITE, MAP_ANON |
	 MAP_PRIVATE, -1, 0);
	lst = base;
	lst->ptr = base;
	if (size <= TINY)
		lst->size = TINY;//=======> a changer selon la size
	while(i < 100)
	{
		lst->tab[i] = lst + META_SIZE + (TINY * i);
		lst->free[i] = 0;//ft_bzero
		i++;
	}
	lst->next = NULL;
}

t_block *add_block(size_t size)
{
	t_block *base;
	t_block *tmp;
	int i;

	i = 0;
	base = NULL;
	tmp = lst;
	while(tmp->next)
		tmp = tmp->next;
	base = mmap(0, getpagesize() * TINY_BLOCK, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	base->ptr = base;
	tmp->next = base;
	if (size < TINY)
		base->size = TINY;
	else if (size < SMALL)
		base->size = SMALL;
	while(i < 100)
	{
		base->tab[i] = base + META_SIZE + (TINY * i);
		base->free[i] = 0;
		i++;
	}
	base->next = NULL;
	base->prev = tmp;
	return (base);
}

void *find_empty_bloc(t_block *tmp, size_t size)
{
	int i;

	i = 0;
	while(i < 100)
	{
		if  (tmp->free[i] == 0 && size <= tmp->size)//mettre tmp->size
		{
			tmp->free[i] = size;
			return(tmp->tab[i]);
		}
		i++;
	}
	return (NULL);
}

void *find_empty_bloc_realloc(t_block *tmp, size_t size)
{
	int i;

	i = 0;
	while(i < 100)
	{
		if  (tmp->free[i] == 0 && size <= tmp->size)//mettre tmp->size
		{
			tmp->free[i] = size;
			return(tmp->tab[i]);
		}
		i++;
	}
	return (NULL);
}

int ft_loop(t_block *ptr)//for ft_nummap()
{
	int i;
	int list_free;

	i = 0;
	list_free = 1;
	while(i < 100)
	{
		if (ptr->free[i])
			list_free = 0;
		i++;
	}
	return (list_free);
}

void ft_munmap(void)
{
	t_block *tmp;
	t_block *tmp2;

	tmp = lst;
	while(tmp)
	{
		if (ft_loop(tmp) && !tmp->dontfree)
		// if (ft_loop(tmp))
		{
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			if (tmp == lst)
			{
				lst = lst->next;
				tmp = tmp->next;
			}
			tmp2 = tmp;
    }
		else
			tmp = tmp->next;
	}
}

void free(void *ptr)
{
	t_block *tmp;
	int i;
	int free_found;

	tmp = lst;
	free_found = 0;
	while(tmp && ptr)
	{
		i = 0;
		while(i < 100)
		{
			if (tmp->tab[i] == ptr && tmp->free[i] != 0)
				tmp->free[i] = 0;
				free_found = 1;
			i++;
		}
		tmp = tmp->next;
	}
	if (!free_found || ptr > tmp->tab[i])
	{
		printf("FREE ERROR\n");
		return;
	}
	ft_munmap();
	return;
}


void *realloc(void *ptr, size_t size)
{
	t_block *tmp;
	t_block *tmp2;
	int ptr_found;
	int i;

	tmp = lst;
	ptr_found = 0;
	while(tmp)
	{
		i = 0;
		while(i < 100 && tmp->tab[i] != ptr)
			i++;
		if (tmp->tab[i] == ptr && size <= tmp->size)
		{
			tmp->free[i] = size;
			ptr_found = 1;
		}
		else if (tmp->tab[i] == ptr && !(tmp2 = find_empty_bloc(ptr, size)))
		{
			return NULL;
		}
		else if (tmp2 == NULL)
		{
				tmp2 = add_block(size);
				tmp2->free[0] = size;
				return (tmp2->tab[0]);
		}
			// else
			// {
			// 	// tmp2->free[0] = size;
			// 	// tmp2->free[i] = 0;
				// return (tmp2->tab[0]);
			// }
		// }
		tmp = tmp->next;
	}
	if (!ptr_found)
		return NULL;
	return NULL;
}

void	*malloc(size_t size)
{
	t_block *tmp;
	t_block *base;

	base = NULL;
	if (size <= 0)
		exit(0);
	if (!lst) // intitialisation du 1 MMAP (//en fonction de TINY, SMALL, LARGE) !!!!
		ft_init(size);
	tmp = lst;
	while(tmp && !base)
	{
		base = find_empty_bloc(tmp, size);
		tmp = tmp->next;
	}
	if (!base)
	{
		add_block(size);
		base = malloc(size);
	}
	return (base);
}
