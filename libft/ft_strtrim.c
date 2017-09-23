/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 15:28:49 by oseng             #+#    #+#             */
/*   Updated: 2015/12/22 17:25:29 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		l;
	int		a;
	char	*str;

	if (!s)
		return (NULL);
	a = 0;
	i = 0;
	l = ft_strlen(s) - 1;
	str = 0;
	while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	if (i >= l)
		return (ft_strdup(""));
	while ((s[l] == ' ' || s[l] == '\n' || s[l] == '\t'))
		l--;
	if (!(str = (char *)malloc(sizeof(char) * (l - i + 2))))
		return (NULL);
	while (i <= l)
		str[a++] = s[i++];
	str[a] = '\0';
	return (str);
}
