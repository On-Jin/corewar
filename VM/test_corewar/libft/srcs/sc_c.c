/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sc_c.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 20:25:22 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/01/17 23:47:31 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char		*assemblage_c(t_option *option)
{
	char *temp;

	temp = NULL;
	if (option->word_c == NULL)
		temp = option->before;
	else if (option->before)
		temp = ft_strjoinfree(option->before, option->word_c);
	else
		temp = option->word_c;
	return (temp);
}

static int		arg_c(char *str, t_option *option)
{
	wchar_t c;

	c = 0;
	if (*str == 'c' && option->mod != MOD_L)
	{
		option->word_c = ft_strnew(1);
		option->word_c[0] = va_arg(option->ap, int);
		option->word_c[1] = '\0';
		option->size_arg = 1;
	}
	else
	{
		c = (wchar_t)va_arg(option->ap, wchar_t);
		option->size_arg = ft_wcharlen(c);
		option->word_c = ft_wctoc(c);
	}
	return (1);
}

int				sc_c(char *str, t_option *option)
{
	if (*str == 'C')
		option->mod = MOD_L;
	arg_c(str, option);
	if (can_i_write_width(str, option) == 1)
	{
		if (option->flags[ZERO] == 0 && option->flags[MOINS] == 0)
			option->before = write_width(option);
		if (option->flags[ZERO] && option->flags[MOINS] == 0)
			option->before = write_width_0(str, option);
		if (option->flags[MOINS])
			option->word_c = ft_memjoinfree(option->word_c,
					write_width(option), option->size_arg);
	}
	option->final = assemblage_c(option);
	return (0);
}
