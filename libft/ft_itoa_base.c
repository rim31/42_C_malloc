/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 13:43:09 by oseng             #+#    #+#             */
/*   Updated: 2016/04/22 14:54:06 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define ABS(v) ((v) < 0 ? -(v) : (v))

static void		base_10(int n, char *s, int *i)
{
	if (n < -9 || n > 9)
		base_10(n / 10, s, i);
	s[(*i)++] = '0' + ABS(n % 10);
}

static void		base_reste(int n, int b, char *s, int *i)
{
	char const	base[] = "0123456789ABCDEF";

	if (n >= b)
		base_reste(n / b, b, s, i);
	s[(*i)++] = base[n % b];
}

char			*ft_itoa_base(int value, int base)
{
	int			i;
	char		*s;

	i = 0;
	if (base > 16 || base < 2 || (s = malloc(sizeof(char) * sizeof(int) *
					8 + 1)) == NULL)
	{
		return (NULL);
	}
	if (value < 0 && base == 10)
		s[i++] = '-';
	if (base == 10)
		base_10(value, s, &i);
	else
	{
		value = ABS(value);
		base_reste(value, base, s, &i);
	}
	s[i] = '\0';
	return (s);
}
