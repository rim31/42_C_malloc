/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 16:06:51 by oseng             #+#    #+#             */
/*   Updated: 2015/12/11 11:33:00 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char *str;

	if (!(str = (char *)malloc(sizeof(size_t) * (size + 1)))
			|| size > 2147483648)
		return (NULL);
	ft_bzero(str, size);
	return (str);
}
