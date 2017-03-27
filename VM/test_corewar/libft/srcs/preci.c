/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sc_preci.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 20:27:12 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/01/18 12:44:42 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	other_cases(char *str, t_option *option)
{
	if ((*str == 'o' || *str == 'O') && option->flags[DIESE])
	{
		if (option->preci <= 0)
			return (0);
		else
			option->preci--;
	}
	else if (option->nb_c[0] == '0' && option->preci <= 0)
	{
		ft_strdel(&option->nb_c);
		option->nb_c = ft_strdup("\0");
	}
	if (option->preci < 0)
		return (0);
	return (1);
}

int			preci_dioux(char *str, t_option *option)
{
	option->preci -= (ft_strlen(option->nb_c));
	option->flags[ZERO] = 0;
	if (other_cases(str, option) == 0)
		return (0);
	if (option->sign == -1 && option->preci + 1 > 0)
	{
		option->nb_c = ft_strsub(option->nb_c, 1,
				ft_strlen(option->nb_c) - 1);
		option->preci++;
	}
	option->nb_c = ft_strjoinfree(ft_memset(ft_strnew(option->preci),
				'0', option->preci), option->nb_c);
	if (option->sign == -1)
		option->nb_c = ft_strjoinfree(ft_strdup("-"), option->nb_c);
	return (0);
}

int			preci_sc(char *str, t_option *option)
{
	if (*str == 'S' || option->mod == MOD_L)
	{
		option->sub_word = 1;
		if (option->preci < option->size_arg)
		{
			option->word_w = ft_wstrsub(option->word_w, 0, option->preci);
			option->size_arg = ft_wstrlen(option->word_w);
		}
	}
	else if (option->preci < option->size_arg)
	{
		option->sub_word = 1;
		option->word_w = (wchar_t*)ft_strsub(
				(char*)option->word_w, 0, option->preci);
		option->size_arg = option->preci;
	}
	return (0);
}
