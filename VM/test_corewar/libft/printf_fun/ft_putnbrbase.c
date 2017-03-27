/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrbase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 17:21:29 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/01/17 17:44:41 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/printf_fun.h"

void	ft_putnbrbase(int n, int base)
{
	long long int	nb;
	int				reste;
	int				curr;

	reste = 0;
	curr = 0;
	nb = n;
	if (n < 0)
	{
		ft_putchar('-');
		nb = nb * -1;
	}
	reste = nb % base;
	curr = nb / base;
	if (curr != 0)
		ft_putnbrbase(curr, base);
	ft_putnbr(reste);
}
