/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 12:24:14 by oseng             #+#    #+#             */
/*   Updated: 2015/12/11 09:56:33 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t i;
	size_t len;
	size_t j;

	j = 0;
	i = 0;
	len = 0;
	while (dest[i] != '\0' && i < size)
		i++;
	len = i;
	while (src[j] != '\0' && i < size - 1)
		dest[i++] = src[j++];
	if (len < size)
		dest[i] = '\0';
	return (len + ft_strlen(src));
}
