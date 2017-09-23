/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 13:43:09 by oseng             #+#    #+#             */
/*   Updated: 2016/03/11 18:13:13 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_sign(int i)
{
	int		less;

	less = 0;
	if (i < 0)
		return (1);
	return (0);
}

static int		ft_len(int i)
{
	int		tmp;

	tmp = 0;
	if (i == 0)
		return (1);
	while (i != 0)
	{
		i = i / 10;
		tmp++;
	}
	return (tmp);
}

char			*ft_itoa(int n)
{
	int		i;
	char	*str;
	int		less;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_len(n);
	less = ft_sign(n);
	i = len + less;
	str = NULL;
	if (!(str = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	if (less)
		n = -n;
	str[i] = '\0';
	while (i--)
	{
		str[i] = '0' + n % 10;
		n = n / 10;
		if (less == 1 && i == 0)
			str[i] = '-';
	}
	return (str);
}
