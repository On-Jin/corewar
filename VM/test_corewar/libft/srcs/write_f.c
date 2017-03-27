/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 20:46:21 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/01/17 23:43:45 by ntoniolo         ###   ########.fr       */
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

int			write_f(char *str, t_option *option, long double nb)
{
	if (option->flags[PRECI] == 0)
		option->preci = 6;
	if (nb == 0)
		ft_putstr("ejf[eof");
	option->nb_c = ft_dotoa(nb, option->preci);
	if (option->nb_c[0] == '-')
		option->sign = -1;
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
