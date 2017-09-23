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
#include <sys/mman.h>

#define TINY_BLOCK  1
#define TINY  (TINY_BLOCK*4096 - sizeof(t_block)) / 100
#define SMALL_BLOCK  26*4096
#define SMALL  (SMALL_BLOCK - sizeof(t_block)) / 100
// #define TINY 32
// #define SMALL 128
#define LARGE 1


// void *base;
// void *base2;


typedef struct 			s_block {
	void		    	*ptr;/* le pointeur sur les données, pour le contrôleur d'erreur de free; */
	int					free[100];/*  indicateur de disponibilité du bloc;*/
	size_t				size;/* la taille du bloc alloué;*/
	// int					iteration;/* la taille du bloc alloué;*/
	struct s_block      *next;/* les pointeurs sur les méta-données des blocs suivants et précédants;*/
	struct s_block		*prev;
	/* A pointer to the allocated block */
	// char				data[1];
	// /*====================*/
	// size_t       		nb;
	// char          		*str;
	void 				*tab[100];
}						t_block;


t_block *lst;

void ft_free(void *ptr);
void *ft_malloc(size_t size);
void *ft_realloc(void *ptr, size_t size);
void ft_show_alloc_mem(void);

#endif
