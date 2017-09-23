/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/21 10:21:48 by oseng             #+#    #+#             */
/*   Updated: 2016/01/04 09:26:55 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddend(t_list **alst, t_list *end)
{
	t_list *tmp;

	if (*alst && end)
	{
		tmp = *alst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = end;
	}
}
