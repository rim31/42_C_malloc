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

	ptr = (unsigned long)ptr;
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

void 		print_list_header(t_header *liste)
{
	int  i;

	i = 1;
	ft_putstr("\nprint_list_head : \n");
	ft_putstr("i adress       free  size         char*\n");
  	while(liste && i <= 100)
  	{
		ft_putnbr(i);
		ft_putstr(" ");
	  	ft_puthexa((unsigned long)liste);
	  	ft_putstr("    ");
		ft_putnbr(liste->free);
	  	ft_putstr("    ");
			ft_putnbr(liste->size);
	  	ft_putstr("        ");
			ft_putstr((char*)((void*)liste+META_SIZE_HEAD));
	  	ft_putstr("\n");
	  	liste = liste->next;
		i++;
  	}
}

void 		print_list_zone(t_zone *liste)
{
	int  i;

	i = 1;
	ft_putstr("print_list_zone : ");
  	while(liste)
  	{
		ft_putstr("{");
		ft_putnbr(i);
	  	ft_puthexa((unsigned long)liste);
	  	ft_putstr("} | \n");
		print_list_header(liste->header);
	  	liste = liste->next;
		i++;
  	}
}


void			print_all(void)
{
	// t_header	*tmp;
	t_zone		*tiny_zone;
	t_zone		*small_zone;
	t_zone		*large_zone;

	tiny_zone = global_env.tiny;
	ft_puthexa((unsigned long)tiny_zone);
	ft_putstr("\n == tiny == \n");
	print_list_zone( global_env.tiny);
	small_zone = global_env.small;
	ft_puthexa((unsigned long)small_zone);
	ft_putstr("\n == small == \n");
	print_list_zone( global_env.small);
	large_zone = global_env.large;
	ft_puthexa((unsigned long)large_zone);
	ft_putstr("\n == large == \n");
	print_list_zone( global_env.large);

	// while(tiny_zone)
	// {
	// 	i = 1;
	// 	ft_putstr(" < ");
	// 	ft_puthexa((unsigned long)tiny_zone);
	// 	ft_putstr(" > \n");
	// 	tmp = (t_header*)tiny_zone->header;
	// 	print_list_header(tmp);
	// 	tiny_zone = tiny_zone->next ;
	// 	// ft_puthexa((unsigned long)tiny_zone);
	// }
}
