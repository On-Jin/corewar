/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_ui.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 18:04:34 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/01/17 17:47:16 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/printf_fun.h"

static int	count_number_ui(long long unsigned int n, int base)
{
	int i;

	i = 0;
	if (n == 0)
		i++;
	while (n)
	{
		n = n / base;
		i++;
	}
	return (i);
}

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

char		*ft_itoa_base_ui(long long unsigned int nb, int base)
{
	int			i;
	int			over;
	char		*str;

	over = 0;
	i = count_number_ui(nb, base) - 1;
	if ((str = ft_strnew(count_number_ui(nb, base))) == NULL)
		return (NULL);
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

char		*ft_itoa_base_maj_ui(long long unsigned int nb, int base)
{
	int			i;
	int			over;
	char		*str;

	over = 0;
	i = count_number_ui(nb, base) - 1;
	if ((str = ft_strnew(count_number_ui(nb, base))) == NULL)
		return (NULL);
	if (nb == 0)
		str[i] = '0';
	while (nb != 0)
	{
		over = nb % base > 9 ? 'A' - 10 : '0';
		str[i] = nb % base + over;
		i--;
		nb = nb / base;
	}
	return (str);
}

char		*ft_itoa_ll_limit(long long int nb)
{
	int				i;
	char			*str;
	long long int	nb2;

	i = count_number(nb, 10) - 1;
	str = ft_strnew(count_number(nb, 10));
	if (str == NULL)
		return (NULL);
	if (nb < 0)
		str[0] = '-';
	if (nb == 0)
		str[i] = '0';
	while (nb != 0)
	{
		nb2 = (nb % 10);
		nb2 *= nb2 < 0 ? -1 : 1;
		str[i] = nb2 + '0';
		i--;
		nb = nb / 10;
	}
	return (str);
}
