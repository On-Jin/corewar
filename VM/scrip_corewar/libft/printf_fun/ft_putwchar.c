/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 17:25:02 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/01/17 17:45:03 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/printf_fun.h"

static void	ft_writew(wchar_t c, int shl, int shr, int mask)
{
	c = ((unsigned int)c << shl >> shr) | mask;
	write(1, &c, 1);
}

void		ft_putwchar(wchar_t c)
{
	int size;

	size = ft_sizebit(c);
	if (size <= 7)
		write(1, &c, 1);
	else if (size <= 11)
	{
		ft_writew(c, 0, 6, 192);
		ft_writew(c, 26, 26, 128);
	}
	else if (size <= 16)
	{
		ft_writew(c, 0, 12, 224);
		ft_writew(c, 20, 26, 128);
		ft_writew(c, 26, 26, 128);
	}
	else if (size <= 21)
	{
		ft_writew(c, 0, 18, 240);
		ft_writew(c, 14, 26, 128);
		ft_writew(c, 20, 26, 128);
		ft_writew(c, 26, 26, 128);
	}
}
