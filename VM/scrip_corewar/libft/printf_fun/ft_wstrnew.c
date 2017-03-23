/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 19:24:25 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/01/15 19:26:16 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/printf_fun.h"

wchar_t		*ft_wstrnew(size_t size)
{
	wchar_t	*str;
	size_t	i;

	str = (wchar_t*)malloc(sizeof(*str) * size + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < size + 1)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}
