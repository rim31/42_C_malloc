/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 16:42:19 by oseng             #+#    #+#             */
/*   Updated: 2015/12/11 18:21:55 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(char const *s, char c)
{
	size_t	a;
	char	**tab;
	size_t	i;
	int		begin;
	int		end;

	a = 0;
	i = 0;
	tab = NULL;
	if (s && (tab = (char **)malloc(sizeof(*tab) * (ft_strlen(s) + 1))))
	{
		while (s[i] != '\0')
		{
			while (s[i] == c && s[i])
				i++;
			begin = i;
			while (s[i] != c && s[i])
				i++;
			end = i;
			if (end > begin)
				tab[a++] = ft_strsub(s, begin, (end - begin));
		}
		tab[a] = NULL;
	}
	return (tab);
}
