/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 14:12:44 by oseng             #+#    #+#             */
/*   Updated: 2017/07/18 14:12:49 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

library : libft_malloc_$HOSTTYPE.so

void my_free(void *ptr);
void *my_malloc(size_t size);
void *my_realloc(void *ptr, size_t size);
mmap(2)
munmap(2)
getpagesize()
zone : au moins 100 allocations
“TINY”, de 1 à n octets
“SMALL”, de (n+1)
“LARGE”, de (m+1)
n, m, N et M
void show_alloc_mem();

makefile :
ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif



◦ mmap(2)
◦ munmap(2)
◦ getpagesize(3)
◦ getrlimit(2)
◦ les fonctions autorisées dans le cadre de votre libft (write(2) par exemple ;-) )
◦ les fonctions de la libpthread
