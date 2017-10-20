/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 15:40:47 by oseng             #+#    #+#             */
/*   Updated: 2017/09/07 15:47:17 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_MALLOC_H
#define FT_MALLOC_H
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../libft/libft.h"
#include <sys/mman.h>

#define TINY_BLOCK  1*4096
#define TINY  (TINY_BLOCK - sizeof(t_block)) / 100
#define SMALL_BLOCK  3*4096
#define SMALL  (SMALL_BLOCK - sizeof(t_block)) / 100
// #define TINY 28
// #define SMALL 84
#define LARGE 1


// void *base;
// void *base2;


typedef struct 		s_block {
	void		    		*ptr;/* le pointeur sur les données, pour le contrôleur d'erreur de free; */
	int							free[100];/*  indicateur de disponibilité du bloc;*/
	size_t					size;/* la taille du bloc alloué;*/
	struct s_block  *next;/* les pointeurs sur les méta-données des blocs suivants et précédants;*/
	struct s_block	*prev;
	size_t       		dontfree;
	void 						*tab[100];
}									t_block;

/*variable static globale pour stocker la liste*/
t_block *lst;

void free(void *ptr);
void *malloc(size_t size);
void *ft_realloc(void *ptr, size_t size);
void ft_show_alloc_mem(void);
void ft_print(void);
void show_alloc_mem();
void ft_init(size_t size);
t_block *add_block(size_t size);
void *find_empty_bloc(t_block *tmp, size_t size);
void *find_empty_bloc_realloc(t_block *tmp, size_t size);
int ft_loop(t_block *ptr);
void ft_munmap(void);
void free1(void *ptr);


#endif
