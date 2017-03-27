/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 17:06:06 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/01/18 12:44:46 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		can_i_write_width(char *str, t_option *option)
{
	if (ft_strchr("dDioOuUxXpfF", *str))
		option->size_arg += ft_strlen(option->nb_c);
	if ((option->size_flags + option->size_arg) < option->width)
		return (1);
	else
	{
		option->width = 0;
		return (0);
	}
}

char	*write_width(t_option *option)
{
	char	*str_width;

	str_width = NULL;
	option->width -= option->size_flags;
	option->width -= option->size_arg;
	str_width = ft_strnew(option->width);
	ft_memset(str_width, ' ', option->width);
	return (str_width);
}

char	*write_width_0(char *str, t_option *option)
{
	char *str_width;
	char *temp;

	temp = NULL;
	option->width -= option->size_flags;
	option->width -= option->size_arg;
	str_width = ft_strnew(option->width);
	if (ft_strchr("dDioOuUxX", *str) && option->nb_c[0] == '-')
	{
		temp = ft_strsub(option->nb_c, 1, option->size_flags
									+ option->size_arg - 1);
		ft_strdel(&option->nb_c);
		option->nb_c = temp;
		ft_memset(str_width, '0', option->width + 1);
		str_width[0] = '-';
	}
	else
		ft_memset(str_width, '0', option->width);
	return (str_width);
}
