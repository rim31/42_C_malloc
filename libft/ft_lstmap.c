/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 18:32:43 by oseng             #+#    #+#             */
/*   Updated: 2016/01/04 17:43:01 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*tmp;
	t_list	*atmp;
	t_list	*btmp;

	tmp = NULL;
	atmp = NULL;
	btmp = NULL;
	if ((*f) && lst)
	{
		btmp = (*f)(lst);
		atmp = btmp;
		lst = lst->next;
		while (lst)
		{
			tmp = (*f)(lst);
			atmp->next = tmp;
			atmp = tmp;
			lst = lst->next;
		}
		atmp->next = NULL;
	}
	return (btmp);
}
