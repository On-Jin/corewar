/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 13:37:48 by ntoniolo          #+#    #+#             */
/*   Updated: 2016/12/18 18:18:05 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "./includes/libft.h"

static int	count_number(long long int n, int base)
{
	int i;

	i = 0;
	if (n == 0)
		i++;
	if (n < 0)
		i++;
	while (n)
	{
		n = n / base;
		i++;
	}
	return (i);
}

char		*ft_itoa_base(long long n, int base)
{
	long long int	nb;
	int				i;
	int				over;
	char			*str;

	over = 0;
	nb = n;
	i = count_number(nb, base) - 1;
	if ((str = ft_strnew(count_number(nb, base))) == NULL)
		return (NULL);
	if (nb < 0)
	{
		str[0] = '-';
		nb = nb * -1;
	}
	if (nb == 0)
		str[i] = '0';
	while (nb != 0)
	{
		over = nb % base > 9 ? 'a' - 10 : '0';
		str[i] = nb % base + over;
		i--;
		nb = nb / base;
	}
	return (str);
}
