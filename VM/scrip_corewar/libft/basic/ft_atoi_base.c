/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 15:38:54 by ntoniolo          #+#    #+#             */
/*   Updated: 2016/12/18 18:19:22 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

/*
** Convert Base something to Base 10
*/

int		ft_atoi_base(const char *str, int base)
{
	int				i;
	int				sign;
	long long int	nb;

	nb = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
			str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]) ||
			(str[i] >= 'a' && str[i] <= ('a' + (base - 10))))
	{
		if (base <= 10 || str[i] - 'a' < 0)
			nb = nb * base + (str[i] - '0');
		else
			nb = nb * base + (str[i] - 'a' + 10);
		i++;
	}
	return (nb * sign);
}
