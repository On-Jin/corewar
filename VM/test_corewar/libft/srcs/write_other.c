/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_percent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 17:07:48 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/01/17 23:48:43 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		write_percent(char *str, t_option *option)
{
	option->nb_c = ft_strdup("%");
	option->size_flags++;
	if (can_i_write_width(str, option))
	{
		if (option->flags[ZERO] == 0 && option->flags[MOINS] == 0)
			option->nb_c = ft_strjoinfree(write_width(option),
														option->nb_c);
		if (option->flags[ZERO] && option->flags[MOINS] == 0)
			option->nb_c = ft_strjoinfree(write_width_0(str, option),
														option->nb_c);
		if (option->flags[MOINS])
			option->nb_c = ft_strjoinfree(option->nb_c,
													write_width(option));
	}
	option->final = option->nb_c;
	return (0);
}

int		write_other(char *str, t_option *option)
{
	option->word_c = ft_strnew(1);
	option->word_c[0] = *str;
	option->size_flags += 1;
	if (can_i_write_width(str, option) == 1)
	{
		if (option->flags[MOINS] == 0 && option->flags[ZERO] == 0)
			option->word_c = ft_strjoinfree(write_width(option),
														option->word_c);
		if (option->flags[MOINS] == 0 && option->flags[ZERO])
			option->word_c = ft_strjoinfree(write_width_0(str, option),
														option->word_c);
		if (option->flags[MOINS])
			option->word_c = ft_strjoinfree(option->word_c,
												write_width(option));
	}
	option->final = option->word_c;
	return (0);
}
