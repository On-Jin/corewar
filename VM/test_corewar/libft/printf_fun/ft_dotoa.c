/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dotoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 20:08:58 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/01/18 13:12:36 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/printf_fun.h"

static char	*ft_cases_dotoa(char *str, int len, double nb)
{
	if (len == 0)
		return (str);
	if (nb == 0)
		return (ft_strjoinfree(str, ft_strdup(".0000000")));
	return (NULL);
}

char		*ft_dotoa(double nb, int len)
{
	char	*str;
	int		i;
	int		j;

	str = ft_itoa((long long int)nb);
	nb -= (long long)nb;
	if (len == 0 || nb == 0)
		return (ft_cases_dotoa(str, len, nb));
	str = ft_strjoinfree(str, ft_strdup("."));
	i = 0;
	j = 0;
	while (i++ < len + 1)
	{
		nb = nb * 10;
		if (nb < 1 && nb > -1 && i != len)
			j++;
	}
	if (j)
		str = ft_strjoinfree(str, ft_memset(ft_strnew(j), '0', j));
	if (nb < 0)
		nb *= -1;
	if ((int)nb % 10 > 4)
		nb += (int)nb % 10;
	nb = nb / 10;
	return (ft_strjoinfree(str, ft_itoa((long long int)nb)));
}
