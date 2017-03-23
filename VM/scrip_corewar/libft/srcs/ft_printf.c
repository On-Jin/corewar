/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 17:18:15 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/02/10 03:34:23 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		init_struct(t_option *option)
{
	int i;

	i = -1;
	while (++i < 6)
		option->flags[i] = 0;
	option->prefix = NULL;
	option->final = NULL;
	option->before = NULL;
	option->word_c = NULL;
	option->word_w = NULL;
	option->width = 0;
	option->preci = 0;
	option->mod = 0;
	option->size_flags = 0;
	option->size_arg = 0;
	option->final_len = 0;
	option->sub_word = 0;
	option->sign = 1;
}

static int		check_type(char *str, t_option *option)
{
	if (*str == '%')
		write_percent(str, option);
	else if (option->mod != 0 && ft_isin("uoxX", *str))
		mod_uox(str, option);
	else if ((option->mod != 0 && ft_isin("di", *str)) || *str == 'D')
		mod_di(str, option);
	else if ((option->mod == 0 && ft_isin("dipouxX", *str))
										|| ft_isin("fFUOp", *str))
		dipfoux(str, option);
	else if (*str == 'c' || *str == 'C')
		sc_c(str, option);
	else if (*str == 's' || *str == 'S')
		sc_s(str, option);
	else if (option->width)
		write_other(str, option);
	else
		return (-1);
	option->final_len += option->width + option->size_flags
						+ option->size_arg;
	return (0);
}

static void		printf_loop(char *str, t_option *option)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			init_struct(option);
			i++;
			while (ft_isdigit(str[i]) || ft_isin(" #+-lhzj.*", str[i]))
				i += check_flags(&str[i], option);
			i += check_type(&str[i], option);
			option->len += option->final_len;
			ft_putbuffer(option);
			ft_strdel(&option->final);
		}
		else if (str[i] != '%')
		{
			option->len++;
			ft_putbufferchar(str[i], option);
		}
		i++;
	}
}

int				ft_printf(char *str, ...)
{
	t_option	option;

	option.len = 0;
	if (!str)
		return (0);
	if (str[0] == '%' && str[1] == '\0')
		return (0);
	option.b = 0;
	ft_bzero(option.buffer, BUFF_SIZE_P);
	va_start(option.ap, str);
	printf_loop(str, &option);
	va_end(option.ap);
	if (option.buffer[0] != '\0')
		write(1, &option.buffer, option.b);
	return (option.len);
}
