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
/*
my_malloc
	init_base => *
		creation list chainee de 100 blocks
		// printf("TINY(header + 100 block) => %lu \n", (META_SIZE + (TINY * 100))/page + page/(META_SIZE + (TINY * 100))%page);
		// printf("SMAL(header + 100 block) => %lu \n", (META_SIZE + (SMALL * 100))/page + page/(META_SIZE + (SMALL * 100))%page);

		// base = mmap(0, getpagesize() * 2, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		// base = mmap(0, getpagesize() * 4, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		// base = mmap(0, getpagesize() * 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
*/

#define META_SIZE sizeof(t_block)

int		ft_size(size_t size)
{
	int page;
	void * base;

	page = size;
	// printf("tiny, small, t_block :\n- tiny %lu \n- small %lu \n- t_block %lu\n", TINY, SMALL, META_SIZE);
	if (size <= TINY)
		printf("TINY\n");
	else if (size <= SMALL)
	{
		printf("SMALL to do\n");
		exit(0);
	}
	else
	{
		printf("LARGE to do\n");
		exit(0);
	}
	return (page);
}

void ft_check_free(t_block* ptr, size_t size)
{
	int i;

	i = 0;
	if (size <= TINY)
	while(ptr->free[i] == 0 || i < 100)
		i++;
}


void ft_init_tiny(size_t size){
	t_block *base;
	t_block *tmp;
	int i;

	i = 0;
	tmp = lst;
	printf("tmp-->NEXT %p\n", tmp->next);
	base = mmap(0, getpagesize() * 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	while (tmp)
	{
		tmp = tmp->next;
		printf("TMP %p\n", tmp->next);
	}
	tmp->next = base;
	tmp->size = TINY;
	printf("p* %lu \n", (unsigned long)base);
	while(i < 100)
	{
		tmp->tab[i] = tmp + META_SIZE + (TINY * i);
		tmp->free[i] = 0;
		i++;
	}
	// tmp->next = tmp->tab[99]+TINY;//pour signifier que le dernier block doit faire 1 TINY
	// tmp = base->next;
	tmp->next = NULL;
	printf("p* + struct %lu ||| %lu\n", (unsigned long)base->next, META_SIZE+100*TINY);
}

void ft_printtab()
{
	int i;
	t_block *tmp;

	tmp = lst;
	// printf("dernier *tab %lu \n| ", (unsigned long)( lst + META_SIZE + (TINY* 100)));
	while(tmp)
	{
		printf("===>*ptr %lu <===\n ", (unsigned long)tmp);
		i = 0;
		while(i < 100){
			printf("%lu %s %d| ", (unsigned long)tmp->tab[i], (tmp->free[i]) ? "." : "FREE", i);
			// printf("%p %s %d| ", lst->tab[i], (lst->free[i]) ? "." : "FREE", i);
			i++;
		}
		tmp = tmp->next;
	}
	// printf("\nprochain octet libre %lu \n" , (unsigned long)lst->tab[i - 1 ] + TINY);
}

/*
* lst->next = base + META_SIZE + (99*TINY);// + taille des tab 100 tiny	//check next ?
* if (size <= SMALL)
* 	lst->tab[i] = base + META_SIZE + (SMALL * i);
*/
void *ft_init(size_t size){
	int i;
	t_block *base;

	i = 0;
	base = mmap(0, getpagesize() * 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	lst = base;
	lst->size = TINY;//=======> a changer selon la size
	printf("p* %lu \n", (unsigned long)lst);
	printf("p* + struct %lu \n", (unsigned long)lst->next);
	while(i < 100)
	{
		lst->tab[i] = lst + META_SIZE + (TINY * i);
		if (lst->free[i] == 0 && i < 98)//test du bon malloc
			lst->free[i] = size;
		else
			lst->free[i] = 0;
		// printf("%lu %d| ",(unsigned long)lst->tab[i], i);
		i++;
	}
	lst->next = NULL;
	printf("p* + struct %lu ||| %lu\n=======ft_init done========\n", (unsigned long)lst->next, META_SIZE+100*TINY);
	return ((void*)(lst + META_SIZE));
}


void	*ft_malloc(size_t size)
{
	t_block *tmp;
	t_block *copy;
	void *base;
	int i;

	i = 0;
	if (!lst) // intitialisation du 1 MMAP (//en fonction de TINY, SMALL, LARGE) !!!!
	{
		base = ft_init(size);
		// ft_printtab();
	}
	else
	{
		tmp = lst;
		printf("BASE existe deja => recherche du ptr* FREE\n");
		if (size <= TINY)
		{
			while(tmp->free[i] && i <= 99)
				i++;
			if (i <= 99)//tes
			{
				tmp->free[i] = size;
				printf("%lu *tmp => je remplis le free\n", (unsigned long)tmp->tab[i]);
				return(tmp->tab[i]);
			}
			else if(i > 99)
			{
				base = mmap(0, getpagesize() * 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
				// tmp->next = tmp;
				tmp->next = base;
				printf("REFAIRE un MMAP --> %lu\n", (unsigned long)tmp->next);

				i = 0;
				while(i < 100)
				{
					tmp->tab[i] = tmp + META_SIZE + (TINY * i);
					tmp->free[i] = 0;
					i++;
				}
				copy = tmp;
				copy->next = NULL;
				// ft_printtab();
				// ft_init_tiny(size);
				ft_malloc(size);
			}
		}
	}
	return (base);
}


int 	main(int ac, char **av)
{
	int i;

	i = 0;
	if(ac == 2)
	{
		while (i < 6)
		{
			ft_malloc(ft_size(atoi(av[1])));
			i++;
		}
		ft_printtab();
		printf("taille de la structure ===> %lu + %lu\n", META_SIZE, TINY*100);
	}
	return (0);
}
