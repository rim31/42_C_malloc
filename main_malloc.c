/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 15:37:51 by oseng             #+#    #+#             */
/*   Updated: 2017/09/07 15:40:28 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_malloc.h"
#define META_SIZE sizeof(t_block)

void ft_print(void)
{
	t_block *tmp;

	tmp = lst;
	while(tmp)
	{
		printf(" %lu (prev: %lu / next:%lu / tab[1]:%lu)==>", (unsigned long)tmp, (unsigned long)tmp->prev, (unsigned long)tmp->next,  (unsigned long)tmp->tab[0]);
		tmp = tmp->next;
	}
}

static void print_mem(t_block tmp)
{
			printf("%s", (tmp->free[i]) ? "\e[1;34mX\e[0m" : "\e[1;32m_\e[0m");
}

void show_alloc_mem()
{
	int i;
	t_block *tmp;

	tmp = lst;
	while(tmp)
	{
		printf("%p | %lu\n", tmp, (unsigned long)tmp);
		i = 0;
		while(i < 100){
			// printf("%s", (tmp->free[i]) ? "\e[1;34mX\e[0m" : "\e[1;32m_\e[0m");
			printf("[%lu]%s %d | ", (unsigned long)tmp->tab[i], (tmp->free[i]) ? "\e[1;32mX\e[0m" : "\e[1;34mF\e[0m", i);
			i++;
		}
		tmp = tmp->next;
	}
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

void ft_free(void *ptr)
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


void *ft_realloc(void *ptr, size_t size)
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

void ft_init(size_t size)
{
	int i;
	t_block *base;

	i = 0;
	base = mmap(0, getpagesize() * TINY_BLOCK, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	lst = base;
	(void)size;
	lst->ptr = base;
	lst->size = TINY;//=======> a changer selon la size
	while(i < 100)
	{
		lst->tab[i] = lst + META_SIZE + (TINY * i);
		lst->free[i] = 0;//ft_bzero
		i++;
	}
	lst->next = NULL;
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

void	*ft_malloc(size_t size)
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
		base = ft_malloc(size);
	}
	return (base);
}


int 	main(int ac, char **av)
{
	int i;
	void *ptr;

	i = 0;
	if(ac == 2)
	{
		while (i < 106)
		{
			ptr = ft_malloc(atoi(av[1]));
			print_mem(ptr);
			i++;
		}
		show_alloc_mem();
		// ft_putnbr_base((long long)ptr, 16);
		printf("taille de la structure ===> %lu + %lu\n", META_SIZE, TINY*100);
	}
	return (0);
}
