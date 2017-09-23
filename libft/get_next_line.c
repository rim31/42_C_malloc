/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 10:23:36 by oseng             #+#    #+#             */
/*   Updated: 2016/04/22 14:50:44 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			*ft_read(int fd, char *str)
{
	char			buf[BUFF_SIZE + 1];
	int				ret;
	char			*tmp;
	int				i;

	str = ft_strnew(1);
	i = 0;
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		tmp = str;
		str = ft_strjoin(tmp, buf);
		ft_strdel(&tmp);
		i = 1;
	}
	if (i == 0 || ret == -1)
		return (NULL);
	return (str);
}

static char			*ft_line(char *str)
{
	char			*tmp;
	int				i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	tmp = ft_strnew(i);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		tmp[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		i++;
	tmp[i] = '\0';
	return (tmp);
}

static	char		*ft_subline(char *str)
{
	char			*tmp;
	int				i;
	int				j;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	tmp = ft_strnew(ft_strlen(str) - i);
	j = 0;
	while (str[i] != '\0')
	{
		tmp[j] = str[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	str = tmp;
	return (str);
}

int					get_next_line(int const fd, char **line)
{
	static	char	*str[256];
	int				i;

	i = 0;
	if (fd < 0 || line == NULL || BUFF_SIZE < 1 || fd > 256)
		return (-1);
	if (!(str[fd]))
		if ((str[fd] = ft_read(fd, str[fd])) == NULL)
			return (-1);
	if (str[fd][i] == '\0')
		return (0);
	*line = ft_line(str[fd]);
	str[fd] = ft_subline(str[fd]);
	return (1);
}
