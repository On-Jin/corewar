/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wctoc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 17:56:21 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/01/17 17:47:50 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/printf_fun.h"

static unsigned char	ft_save(wchar_t c, int shl, int shr, int mask)
{
	c = ((unsigned int)c << shl >> shr | mask);
	return (c);
}

static void				put_in_str(unsigned char *str_c, wchar_t c, int size)
{
	if (size <= 7)
		str_c[0] = c;
	else if (size <= 11)
	{
		str_c[0] = ft_save(c, 0, 6, 192);
		str_c[1] = ft_save(c, 26, 26, 128);
	}
	else if (size <= 16)
	{
		str_c[0] = ft_save(c, 0, 12, 224);
		str_c[1] = ft_save(c, 20, 26, 128);
		str_c[2] = ft_save(c, 26, 26, 128);
	}
	else if (size <= 21)
	{
		str_c[0] = ft_save(c, 0, 18, 240);
		str_c[1] = ft_save(c, 14, 26, 128);
		str_c[2] = ft_save(c, 20, 26, 128);
		str_c[3] = ft_save(c, 26, 26, 128);
	}
}

char					*ft_wctoc(wchar_t c)
{
	int				size;
	unsigned char	*str_c;

	str_c = (unsigned char*)ft_strnew(5);
	if (c == 0)
		return ((char*)str_c);
	size = ft_sizebit(c);
	put_in_str(str_c, c, size);
	return ((char*)str_c);
}
