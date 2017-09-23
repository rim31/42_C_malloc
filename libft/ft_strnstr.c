/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 09:55:53 by oseng             #+#    #+#             */
/*   Updated: 2015/12/11 17:15:32 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	a;
	size_t	b;

	i = 0;
	a = 0;
	if (s2[i] == '\0')
		return ((char *)s1);
	b = ft_strlen(s2);
	while (s1[i] != '\0' && i < n)
	{
		a = 0;
		while (s1[i + a] == s2[a] && a < b && a + i < n)
			a++;
		if (a == b)
			return ((char *)&s1[i]);
		i++;
	}
	return (NULL);
}
