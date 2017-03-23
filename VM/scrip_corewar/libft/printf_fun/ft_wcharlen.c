/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcharlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 17:14:23 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/01/15 17:16:26 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/printf_fun.h"

int		ft_wcharlen(wchar_t c)
{
	int size;
	int i;

	i = 0;
	size = ft_sizebit(c);
	i++;
	if (size > 7)
		i++;
	if (size > 11)
		i++;
	if (size > 16)
		i++;
	return (i);
}
