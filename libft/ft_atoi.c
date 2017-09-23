/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 15:27:14 by oseng             #+#    #+#             */
/*   Updated: 2015/12/09 14:25:27 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int	i;
	int	nbr;
	int less;

	i = 0;
	nbr = 0;
	less = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		less = 1;
		i++;
	}
	if (str[i] == '+' && less == 0)
		i++;
	while (str[i] != '\0' && (str[i] >= 48 && str[i] <= 57))
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	if (less == 1)
		nbr = -nbr;
	return (nbr);
}
