/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 20:54:16 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/02/26 14:52:32 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char		*assemblage_s(t_option *option)
{
	char *temp;

	temp = NULL;
	if (option->before)
		temp = ft_strjoinfree(option->before, option->word_c);
	else
		temp = option->word_c;
	return (temp);
}

static int		try_error(t_option *option)
{
	if (option->word_w == NULL)
	{
		if (option->flags[PRECI] == 0)
		{
			option->width = 0;
			option->final_len += 6;
			option->final = ft_strdup("(null)");
			return (0);
		}
		else
		{
			option->word_w = (wchar_t*)ft_strdup("\0");
			return (0);
		}
	}
	return (1);
}

static int		arg_s(char *str, t_option *option)
{
	if (*str == 's' && option->mod != MOD_L)
	{
		option->word_w = (wchar_t*)va_arg(option->ap, char*);
		if (try_error(option) == 0)
			return (0);
		option->size_arg = ft_strlen((char*)option->word_w);
		if (option->flags[PRECI])
			preci_sc(str, option);
		option->word_c = ft_strdup((char*)option->word_w);
	}
	else
	{
		option->word_w = va_arg(option->ap, wchar_t *);
		if (try_error(option) == 0)
			return (0);
		option->size_arg = ft_wstrlen(option->word_w);
		if (option->flags[PRECI])
			preci_sc(str, option);
		option->word_c = ft_watoa(option->word_w);
	}
	if (option->sub_word)
		free(option->word_w);
	return (1);
}

int				sc_s(char *str, t_option *option)
{
	if (*str == 'S')
		option->mod = MOD_L;
	if (arg_s(str, option) == 0)
		return (0);
	if (can_i_write_width(str, option) == 1)
	{
		if (option->flags[ZERO] == 0 && option->flags[MOINS] == 0)
			option->before = write_width(option);
		if (option->flags[ZERO] && option->flags[MOINS] == 0)
			option->before = write_width_0(str, option);
		if (option->flags[MOINS])
			option->word_c = ft_strjoinfree(option->word_c,
											write_width(option));
	}
	option->final = assemblage_s(option);
	return (0);
}
