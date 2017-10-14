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

#include "ft_malloc.h"
#define META_SIZE sizeof(t_block)

void ft_check_free(t_block* ptr, size_t size)
{
	int i;

	i = 0;
	while(ptr->free[i] == 0 || i < 100)
		i++;
}

void ft_printtab()
{
	int i;
	t_block *tmp;

	tmp = lst;
	while(tmp)
	{
		printf("\n");
		i = 0;
		while(i < 100){
			printf("%lu %s %d | ", (unsigned long)tmp->tab[i], (tmp->free[i]) ? "." : "\e[1;34mFREE\e[0m", i);
			if (tmp->free[i])
				printf("<%lu %d>", (unsigned long)tmp->tab[i], (tmp->free[i]));
			i++;
		}
		tmp = tmp->next;
	}
}

void ft_init(size_t size){
	int i;
	t_block *base;

	i = 0;
	base = mmap(0, getpagesize() * TINY_BLOCK, PROT_READ | PROT_WRITE, MAP_ANON |
	 MAP_PRIVATE, -1, 0);
	lst = base;
	lst->ptr = base;
	lst->size = TINY;//=======> a changer selon la size
	printf("p* %lu \np* + struct %lu \n", (unsigned long)lst, (unsigned long)lst->next);
	while(i < 100)
	{
		lst->tab[i] = lst + META_SIZE + (TINY * i);
		// if (lst->free[i] == 0 && i < 98)//test du bon malloc
		// 	lst->free[i] = size;
		// else
			lst->free[i] = 0;//ft_bzero
		i++;
	}
	lst->next = NULL;
	lst->prev = NULL;
	printf("p* + struct %lu || %lu\n=======ft_init done========\n",
	(unsigned long)lst->next, META_SIZE + 100 * TINY);
	// return ((void*)(lst + META_SIZE));
}

t_block *add_block(size_t size)
{
	t_block *base;
	t_block *tmp;
	int i;

	i = 0;
	tmp = lst;
	while(tmp->next)
		tmp = tmp->next;
	base = mmap(0, getpagesize() * TINY_BLOCK, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	base->ptr = base;
	tmp->next = base;
	if (size < TINY)
		base->size = TINY;
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
		if  (tmp->free[i] == 0 && size <= TINY)
		{
			// printf("%lu *ptr MALLOC trouve \n", (unsigned long)tmp->tab[i]);
			tmp->free[i] = size;
			return(tmp->tab[i]);
		}
		i++;
	}
	// add_block(size);
	// ft_malloc(size);
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
		if (ptr->free[i] != 0)
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
		// if (ft_loop(tmp) && !tmp->dontfree)
		if (ft_loop(tmp))
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

	if (ptr == NULL)
		return;
	tmp = lst;
	while(tmp)
	{
		i = 0;
		while(i < 100)
		{
			if (i == 0)
				printf("[%lu/%lu]", (unsigned long)tmp->tab[i], (unsigned long)tmp->free[i]);
			if (tmp->tab[i] == ptr)
			{
				tmp->free[i] = 0;
				// printf("%d TROUVEE &FREE !!!!!!!!!!!!\n", tmp->free[i]);
			}
			i++;
		}
		if (tmp->next)
			tmp = tmp->next;
		else
			break;
	}
	ft_munmap();
	return;
}

// void 	*ft_realloc(void *ptr, size_t size)
// {
// 	t_block *tmp;
// 	t_block *base;
// 	int i;
//
// 	if (size <= 0)
// 		exit(0);
// 	tmp = lst;
// 	while(tmp && !base)
// 	{
// 		base = find_empty_bloc(tmp, size);
// 		tmp = tmp->next;
// 	}
// 	if (!base)
// 	{
// 		printf("\n%lu *ptr ADD_BLOCK \n", (unsigned long)base);
// 		add_block(size);
// 		ft_malloc(size);
// 	}
// 	return (base);
// }

void	*ft_malloc(size_t size)
{
	t_block *tmp;
	t_block *base;
	int i;

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
		tmp = add_block(size);
		printf("\n%lu *ptr ADD_BLOCK \n", (unsigned long)tmp);
		ft_malloc(size);
	}
	return (base);
}

int 	main(int ac, char **av)
{
	int i;
	t_block *tmp;
	void *test;
	void *free_test[200];

	i = 0;
	if(ac == 2)
	{
		while (i < 109)
		{
			// printf("\n%lu *malloc \n", (unsigned long)ft_malloc(atoi(av[1])));
			if (i >= 0 && i < 200)
			{
				free_test[i] = ft_malloc(atoi(av[1]));
				// printf("\n%lu *free_malloc %d\n", (unsigned long)free_test[i], i);
			}
			else
				ft_malloc(atoi(av[1]));
			i++;
		}
	}
	ft_printtab();
	printf("\n==========FREE=========\n");
	// i = 0;
	// ft_free(free_test[i]);
	// printf("\n%lu *free_malloc %d\n", (unsigned long)free_test[i], i);
	// printf("\n==========FREE=========\n");

	i = 0;
	while (i < 200)
	{
		// printf("\n%lu *free_malloc \n", (unsigned long)free_test[i]);
		if (free_test[i])
			ft_free(free_test[i]);
		i++;
	}
	ft_printtab();
	printf("taille de la structure ===> %lu + %lu\n", META_SIZE, TINY*100);
	return (0);
}
