/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoly <djoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 13:56:58 by djoly             #+#    #+#             */
/*   Updated: 2018/01/11 16:37:13 by djoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
#define MALLOC_H

#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>

typedef struct          s_header
{
    size_t              size;
    size_t              total_size;
    struct s_header     *next;
    struct s_header     *next_area;
    int                 type;
    int                 free;
}                       t_header;

/*
**    structure pour stocker toutes les structures
*/
typedef struct          t_env
{
                        s_zone      *small;
                        s_zone      *tiny;
                        s_zone      *large;
}                       s_env;
/*
**    Global variables.
*/
t_header                *g_base;
t_env                   global_env;

void free(void *ptr);
void *malloc(size_t size);
void *ft_realloc(void *ptr, size_t size);
void ft_show_alloc_mem(void);


#endif
