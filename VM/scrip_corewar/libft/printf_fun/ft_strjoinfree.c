/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 20:48:15 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/01/17 17:51:57 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/printf_fun.h"

char	*ft_strjoinfree(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		n;

	n = 0;
	i = 0;
	str = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[n])
	{
		str[i + n] = s2[n];
		n++;
	}
	if (s1)
		ft_strdel(&s1);
	if (s2)
		ft_strdel(&s2);
	str[i + n] = '\0';
	return (str);
}

char	*ft_memjoinfree(char *s1, char *s2, int len)
{
	char	*str;
	int		i;
	int		n;

	n = 0;
	i = 0;
	str = ft_strnew(len + ft_strlen(s2));
	if (str == NULL)
		return (0);
	while (i < len)
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[n])
	{
		str[i + n] = s2[n];
		n++;
	}
	if (s1)
		ft_strdel(&s1);
	if (s2)
		ft_strdel(&s2);
	str[i + n] = '\0';
	return (str);
}
