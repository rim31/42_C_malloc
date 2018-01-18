/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 14:22:49 by oseng             #+#    #+#             */
/*   Updated: 2018/01/11 16:39:16 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t		ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void			ft_putchar(char c)
{
	write(1, &c, 1);
}

void			ft_putstr(char const *str)
{
	if (!str)
		return ;
	write(1, str, ft_strlen(str));
}

void			ft_putnbr(int n)
{
	if (n == -2147483648)
		ft_putstr("-2147483648");
	else
	{
		if (n < 0)
		{
			ft_putchar('-');
			n = -n;
		}
		if (n > 9)
		{
			ft_putnbr(n / 10);
			ft_putnbr(n % 10);
		}
		else
			ft_putchar('0' + n);
	}
}


void		ft_puthexa(size_t ptr)
{
	size_t	i;

	i = 0;
	if (ptr)
	{
		i = ptr / 16;
		ft_puthexa(i);
		if (ptr % 16 < 10)
			ft_putchar('0' + ptr % 16);
		else
			ft_putchar('a' + (ptr % 16) - 10);
	}
	else
		ft_putstr("0x" );
}

void 		print_list(t_header *liste)
{
	int  i;

	i = 1;
	ft_putstr("print_list");
  	while(liste)
  	{
		ft_putstr("[");
		ft_putnbr(i);
		ft_putstr("]");
	  	ft_puthexa((unsigned long)liste);
	  	ft_putstr("|");
	  	liste = liste->next;
		i++;
  	}
}
