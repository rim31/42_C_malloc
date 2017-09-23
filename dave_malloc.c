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

*/

#define META_SIZE sizeof(t_block)

int		ft_size(size_t size)
{
	int page;
	void * base;

	page = size;
	printf("tiny, small, t_block :\n- tiny %lu \n- small %lu \n- t_block %lu\n", TINY, SMALL, META_SIZE);
	// printf("TINY(header + 100 block) => %lu \n", (META_SIZE + (TINY * 100))/page + page/(META_SIZE + (TINY * 100))%page);
	// printf("SMAL(header + 100 block) => %lu \n", (META_SIZE + (SMALL * 100))/page + page/(META_SIZE + (SMALL * 100))%page);
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
	// base = mmap(0, getpagesize() * 2, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	// base = mmap(0, getpagesize() * 4, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	// base = mmap(0, getpagesize() * 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

	return (page);
}

void ft_check_free(t_block* ptr, size_t size)
{
	int i;

	i = 0;
	if (size <= TINY)
	while(ptr->free[i] == 0 || i <= 100)
		i++;

}

void ft_list(size_t size){
	void *base;
	int i;
	int malloc_ok;

	base = mmap(0, getpagesize() * 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	i = 0;
	malloc_ok = 0;
	lst = base;
	lst->size = TINY;
	printf("p* %lu \n", (unsigned long)lst);
	// lst->next = base + META_SIZE + (99*TINY);// + taille des tab 100 tiny	//check next ?
	printf("p* + struct %lu \n", (unsigned long)lst->next);
	while(i < 100)
	{
		// printf("%p ",base + META_SIZE + (TINY * i));
		// if (size <= TINY)
			lst->tab[i] = base + META_SIZE + (TINY * i);
		// if (size <= SMALL)
		// 	lst->tab[i] = base + META_SIZE + (SMALL * i);
		if (lst->free[i] == 0 && i < 90)
		{
			lst->free[i] = size;
			malloc_ok = 1;
		}
		else
			lst->free[i] = 0;
		i++;
	}
	lst->next = lst->tab[99]+TINY;
	printf("p* + struct %lu ||| %lu\n", (unsigned long)lst->next, META_SIZE+100*TINY);
	//lst->next = NULL;
	if (i == 100 && malloc_ok == 0)
	{
		printf("\n==FAIRE UN NOUVEAU MMAP==\n ");
	}
	printf("\n======================\n ");
}

void ft_printtab()
{
	int i;

	i = 0;

	// printf("dernier *tab %lu \n| ", (unsigned long)( lst + META_SIZE + (TINY* 100)));
	while(i < 100){
		printf("%lu %s %d| ", (unsigned long)lst->tab[i], (lst->free[i]) ? "." : "FREE", i);
		// printf("%p %s %d| ", lst->tab[i], (lst->free[i]) ? "." : "FREE", i);
		i++;
	}
	// printf("\nprochain octet libre %lu \n" , (unsigned long)lst->tab[i - 1 ] + TINY);
}


void 	*ft_malloc(size_t size)
{
	void *base;
	int i;

	i = 0;
	if (!lst)
	{
		printf("%p *lst\n", lst);
		ft_list(size);
		ft_printtab();
	}
	else
	{
		printf("BASE existe deja => recherche du ptr* FREE\n");
		if (size <= TINY)
		{
			while(lst->free[i] && i <= 99)
				i++;
			if(i <= 99)
			{
				lst->free[i] = size;
				printf("%lu *lst => je remplis le free\n", (unsigned long)lst->tab[i]);
				return(lst->tab[i]);
			}
			else if(i > 99)
			{
				printf("refaire un MMAP\n");
			}
		}
	}
	return (0);
}


int 	main(int ac, char **av)
{
	int i;

	i = 0;
	if(ac == 2)
	{
		while (i < 3)
		{
			ft_malloc(ft_size(atoi(av[1])));
			i++;
		}
		ft_printtab();
		printf("taille de la structure ===> %lu + %lu\n", META_SIZE, TINY*100);
	}
	return (0);
}
