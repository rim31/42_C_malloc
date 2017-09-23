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

#define META_SIZE sizeof(struct t_block)

int		ft_size(size_t size)
{
	int nb;
	int page;

	nb = 1;
	page = getpagesize();
	nb += size / page;
	if (size < TINY)
	{
		printf("TINY\n");
	}
	else if (size < SMALL)
	{
		printf("SMALL\n");
	}
	else
	{
		printf("LARGE\n");
	}
	return (nb);
}

void 	*ft_init(size_t size)
{
	base = mmap(0, getpagesize() * size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	return (0);
}

t_block *ft_create_elem(t_block *list, void *ptr, size_t i, size_t type)
{
	t_block *tmp;

	tmp = list;
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->ptr = ptr;
		tmp->tab[i] = (char *)ptr;
		tmp->free[i] = type;
		tmp->next = NULL;
		return (tmp);
	}
	else
	{
		tmp->next = NULL;
		tmp->ptr = ptr;
		return (tmp);
	}
}


void printlist(t_block *liste)
{
	t_block* tmp;
	tmp = liste;
	printf("==========printlist==========\n" );
  while(tmp->next)
  {
    printf("%p LOL \n", tmp->ptr);
    tmp = tmp->next;
  }
}


void * ft_list()
{
	int i;
	t_block * tmp;
	t_block header;
	void *pointeur_init = base;

	tmp = base;
	i = 0;
	printf("%p <= base p* \n" , base);
	base += sizeof(header);
	tmp->ptr = base;
	printf("%p <= p* + header\n" , base);
	while (i <= 100){
		base += TINY;
		printf("pointeur + TINY : %p %d \n" , base, i);
		tmp = ft_create_elem(tmp, base, i, TINY);
		printf("List *tmp  Type  i        *p         tab[maillon]  free[i]\n");
		printf("%p %d  %d  %p     %p        %d\n\n" , tmp, TINY, i, tmp->ptr, tmp->tab[i], tmp->free[i]);
		i++;
	}
	printf("%p POINTEUR DE LA BASE2 \n", base2);

	tmp->next = NULL;
	printlist(tmp);
	return (0);
}

void ft_list2(){
	void *base;
	// void *tmp;
	int i;

	base = mmap(0, getpagesize() * 2, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	i = 0;
	lst = base;
	printf("p* %p \n", lst);
	lst->next = base + sizeof(t_block);
	printf("p* + struct %p \n", lst->next);
	// printf("tab %p ", lst->tab);
	// tmp = lst->tab;

	while(i <= 100)
	{
		printf("%p \n", lst->next + (TINY*i));
		lst->tab[i] = lst->next + sizeof(t_block) + (TINY * i);
		lst->free[i] = TINY;
		i++;
	}
}

void ft_printtab()
{
	int i;

	i = 0;
	while(i < 100){
		printf("%p %d | ", lst->tab[i], lst->free[i]);
		i++;
	}
}


void 	*ft_malloc(size_t size )
{
	void *base;
	if (!lst)
	{
		// ft_list2();
		// ft_printtab();
	}
	else
	{
		printf("BASE existe deja");
	}
	ft_init(size);
	ft_list();
	return (0);
}


int 	main(int ac, char **av)
{
	int nb;
	char c;
	char *str;
	int i;
	t_block test;
	if(ac == 2)
	{
		printf("%s", av[1]);
		ft_malloc(ft_size(atoi(av[1])));
		printf("taille de la structure ===> %lu + %d\n", sizeof(test), TINY*100);
	}
	return (0);
}
