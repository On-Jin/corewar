/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sizebit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 17:17:58 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/01/15 18:55:25 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/printf_fun.h"

int		ft_sizebit(long long nbr)
{
	int		size;

	size = 0;
	while (nbr != 0)
	{
		nbr = nbr >> 1;
		size++;
	}
	return (size);
}
