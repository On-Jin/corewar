/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_watoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 17:30:32 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/01/18 13:05:47 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/printf_fun.h"

static unsigned char	ft_save(wchar_t c, int shl, int shr, int mask)
{
	c = ((unsigned int)c << shl >> shr | mask);
	return (c);
}

static int				put_in(unsigned char *str_c, wchar_t c, int j, int size)
{
	if (size <= 7)
		str_c[j++] = c;
	else if (size <= 11)
	{
		str_c[j++] = ft_save(c, 0, 6, 192);
		str_c[j++] = ft_save(c, 26, 26, 128);
	}
	else if (size <= 16)
	{
		str_c[j++] = ft_save(c, 0, 12, 224);
		str_c[j++] = ft_save(c, 20, 26, 128);
		str_c[j++] = ft_save(c, 26, 26, 128);
	}
	else if (size <= 21)
	{
		str_c[j++] = ft_save(c, 0, 18, 240);
		str_c[j++] = ft_save(c, 14, 26, 128);
		str_c[j++] = ft_save(c, 20, 26, 128);
		str_c[j++] = ft_save(c, 26, 26, 128);
	}
	return (j);
}

static int				size_tab(wchar_t *str)
{
	int size_tab;
	int	size;
	int i;

	i = 0;
	size_tab = 0;
	size = 0;
	while (str[i])
	{
		size = ft_sizebit(str[i]);
		if (size <= 7)
			size_tab += 1;
		else if (size <= 11)
			size_tab += 2;
		else if (size <= 16)
			size_tab += 3;
		else if (size <= 21)
			size_tab += 4;
		i++;
	}
	return (size_tab);
}

char					*ft_watoa(wchar_t *str)
{
	int				j;
	int				size;
	int				i;
	unsigned char	*str_c;

	str_c = NULL;
	i = 0;
	j = 0;
	size = 0;
	size = size_tab(str);
	str_c = (unsigned char*)ft_strnew(size);
	i = 0;
	while (str[i])
	{
		size = ft_sizebit(str[i]);
		j = put_in(str_c, str[i], j, size);
		i++;
	}
	return ((char*)str_c);
}
