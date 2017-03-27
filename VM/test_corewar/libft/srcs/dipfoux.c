/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dioux.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 17:09:44 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/01/18 12:49:28 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*assemblage(t_option *option)
{
	char *temp;

	temp = NULL;
	if (option->prefix && option->flags[ZERO])
	{
		if (option->before)
			option->before = ft_strjoinfree(option->prefix, option->before);
		else
			option->before = option->prefix;
	}
	if (option->prefix && option->flags[ZERO] == 0)
		option->nb_c = ft_strjoinfree(option->prefix, option->nb_c);
	if (option->before != NULL)
		temp = ft_strjoinfree(option->before, option->nb_c);
	else
		temp = option->nb_c;
	return (temp);
}

int			convert_itoa(char *str, t_option *option, long long int nb)
{
	if (*str == 'i' || *str == 'd' || *str == 'D')
		option->nb_c = ft_itoa_ll_limit(nb);
	else if (*str == 'u' || *str == 'U')
		option->nb_c = ft_itoa_base_ui(nb, 10);
	else if (*str == 'o' || *str == 'O')
		option->nb_c = ft_itoa_base_ui(nb, 8);
	else if (*str == 'x' || *str == 'p')
		option->nb_c = ft_itoa_base_ui(nb, 16);
	else if (*str == 'X')
		option->nb_c = ft_itoa_base_maj_ui(nb, 16);
	if (option->nb_c[0] == '-')
		option->sign = -1;
	return (1);
}

static int	before_dioux(char *str, t_option *option)
{
	if ((option->flags[PLUS] || option->flags[SPACE]) &&
			(*str == 'i' || *str == 'd' || *str == 'D') && option->sign == 1)
	{
		if (option->flags[PLUS])
			option->prefix = ft_strdup("+");
		else if (option->flags[SPACE] && option->flags[PLUS] == 0)
			option->prefix = ft_strdup(" ");
	}
	else if ((option->flags[DIESE] && option->nb_c[0] != '0'
						&& ft_strchr("xXoO", *str)) || *str == 'p')
	{
		if (*str == 'o' || *str == 'O')
			option->prefix = ft_strdup("0");
		else if (*str == 'x' || *str == 'p')
			option->prefix = ft_strdup("0x");
		else if (*str == 'X')
			option->prefix = ft_strdup("0X");
	}
	if (option->prefix)
		option->size_flags += ft_strlen(option->prefix);
	return (0);
}

int			write_dipoux(char *str, t_option *option, long long int nb)
{
	convert_itoa(str, option, nb);
	before_dioux(str, option);
	if (option->flags[PRECI])
		preci_dioux(str, option);
	if (can_i_write_width(str, option) == 1)
	{
		if ((option->flags[ZERO] == 0 && option->flags[MOINS] == 0))
			option->before = write_width(option);
		else if (option->flags[ZERO] && option->flags[MOINS] == 0)
			option->before = write_width_0(str, option);
		else if (option->flags[MOINS])
			option->nb_c = ft_strjoinfree(option->nb_c,
									write_width(option));
	}
	option->final = assemblage(option);
	return (0);
}
