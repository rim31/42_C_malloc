/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 09:41:43 by oseng             #+#    #+#             */
/*   Updated: 2015/12/22 17:26:12 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	tmp = NULL;
	len = ft_strlen(s1);
	tmp = (char*)malloc(sizeof(char) * (len + 1));
	if (!tmp || !s1)
		return (NULL);
	while (i < len)
	{
		tmp[i] = s1[i];
		i++;
	}
	tmp[i] = '\0';
	return ((char*)tmp);
}
