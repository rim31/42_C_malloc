/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 11:41:27 by oseng             #+#    #+#             */
/*   Updated: 2015/12/10 16:05:52 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = start;
	if (!s)
		return (NULL);
	str = NULL;
	if (!(str = (char *)malloc(sizeof(*s) * (len + 1))))
		return (NULL);
	while (j < start + len && s[j] != '\0')
		str[i++] = s[j++];
	str[i] = '\0';
	return (str);
}
