/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:57:03 by oseng             #+#    #+#             */
/*   Updated: 2015/12/09 10:32:46 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base(long long n, int base)
{
	// if (n == -2147483648)
	// 	ft_putstr("-2147483648");
	// else
	// {
	// 	if (n < 0)
	// 	{
	// 		ft_putchar('-');
	// 		n = -n;
	// 	}
	// 	if (n > 9)
	// 	{
	// 		ft_putnbr(n / base);
	// 		ft_putnbr(n % base);
	// 	}
	// 	else
	// 		ft_putchar('0' + n);
	// }
  char nb[16];

  ft_strcpy(nb, "0123456789abcdef");
  if (n >= base && n >= 0)
    ft_putnbr(n / base);
  else
    ft_putchar('?');
  n = nb[(n %base)];
  ft_putchar(n);
}
