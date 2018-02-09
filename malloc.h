/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 13:56:58 by oseng             #+#    #+#             */
/*   Updated: 2018/01/11 16:37:13 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
#define MALLOC_H

#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#define TINY            128//(128+24)*100/4096 = 3.71 ==> 4 getpagesize
#define SMALL           1024
#define LARGE           1
#define TRUE            1
#define FALSE           0
#define META_SIZE_HEAD  sizeof(struct s_header)
#define META_SIZE_ZONE  sizeof(struct s_zone)


/*
** ============ + s_header =================
**    // size_t              total_size;
**    // struct s_header     *next_area;
**    // int                 type;
*/
typedef struct          s_header
{
    size_t              size;
    int                 free;
    struct s_header     *next;
}                       t_header;

/*
**    structure pour stocker toutes les structures
*/
typedef struct          s_zone{
      struct s_header   *header;
      struct s_zone     *next;
      size_t            size;
      size_t            count;
}                       t_zone;

typedef struct          s_env
{
      t_zone            *tiny;
      t_zone            *small;
      t_zone            *large;
}                       t_env;
/*
**    Global variables.
** t_header                *g_base;
*/
t_env                   global_env;

void                    free(void *ptr);
void			              free_zone(void *ptr, t_zone *zone);
void                    *malloc(size_t size);
void                    *realloc(void *ptr, size_t size);
void                    ft_show_alloc_mem(void);
void                    ft_putchar(char c);
void                    ft_putnbr(int n);
size_t                  ft_strlen(const char *s);
void                    ft_putstr(char const *str);
void	                  ft_puthexa(size_t ptr);
void                    print_list_header(t_header *liste);
void                    print_list_zone(t_zone *liste);
void                    print_all(void);
t_header                *init_header_tiny(t_zone *ptr);
t_header                *init_header_small(t_zone *ptr);
t_header                *init_header_large(t_zone *ptr);
t_header                *find_empty_bloc_tiny(size_t size);
t_header                *find_empty_bloc_small(size_t size);
t_header                *find_empty_bloc_large(size_t size);
t_header                *create_new_tiny(size_t size);
t_header                *create_new_small(size_t size);
t_header                *create_new_large(size_t size);
t_header                *find_empty_bloc(size_t size, t_zone *zone, size_t nb_size);
void                    *ft_realloc(void *ptr, size_t size, t_zone *zone, size_t nb_size);
void	                  *ft_memccpy(void *dest, const void *src, int c, size_t n);
void                    *ft_memory_copy(void *src, void *dest, size_t size);




#endif
