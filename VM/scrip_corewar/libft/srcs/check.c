/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_attri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 18:28:54 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/01/17 22:54:45 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	check_attri(char *str, t_option *option)
{
	int i;

	i = 0;
	if (str[i] == '#')
		option->flags[DIESE] = 1;
	if (str[i] == '-')
		option->flags[MOINS] = 1;
	if (str[i] == '+')
		option->flags[PLUS] = 1;
	if (str[i] == ' ')
		option->flags[SPACE] = 1;
	if (str[i] == '0')
		option->flags[ZERO] = 1;
	i++;
	return (i);
}

static int	check_w(char *str, t_option *option)
{
	int i;
	int temp;

	temp = 0;
	i = 0;
	if (str[i] == '*')
	{
		temp = va_arg(option->ap, int);
		if (temp < 0)
		{
			option->flags[MOINS] = 1;
			temp = temp * -1;
		}
		i++;
		option->width = temp;
	}
	temp = 0;
	while (ft_isdigit(str[i]))
	{
		temp = temp * 10 + (str[i] - '0');
		i++;
		option->width = temp;
	}
	return (i);
}

static int	check_p(char *str, t_option *option)
{
	int i;
	int temp;

	i = 1;
	temp = 0;
	if (str[i] == '*')
	{
		temp = va_arg(option->ap, int);
		if (temp < 0)
		{
			option->flags[PRECI] = 0;
			temp *= 0;
		}
		i++;
		option->preci = temp;
	}
	temp = 0;
	while (ft_isdigit(str[i]))
	{
		temp = temp * 10 + (str[i] - '0');
		i++;
		option->preci = temp;
	}
	return (i);
}

static int	check_spe(char *str, t_option *option)
{
	int i;

	i = 0;
	if (str[i] == 'h' && str[i + 1] == 'h' && option->mod <= MOD_HH)
	{
		option->mod = MOD_HH;
		i++;
	}
	else if (str[i] == 'h' && option->mod <= MOD_H)
		option->mod = MOD_H;
	else if (str[i] == 'j' && option->mod <= MOD_J)
		option->mod = MOD_J;
	else if (str[i] == 'z' && option->mod <= MOD_Z)
		option->mod = MOD_Z;
	else if (str[i] == 'l' && str[i + 1] == 'l' && option->mod <= MOD_LL)
	{
		option->mod = MOD_LL;
		i++;
	}
	else if (str[i] == 'l' && option->mod <= MOD_L)
		option->mod = MOD_L;
	else if (str[i] == 'L')
		option->mod = MOD_LLL;
	i++;
	return (i);
}

int			check_flags(char *str, t_option *option)
{
	int i;

	i = 0;
	while (str[i] == '#' || str[i] == '-' ||
			str[i] == '+' || str[i] == '0' || str[i] == ' ')
		i += check_attri(&str[i], option);
	i += check_w(&str[i], option);
	if (str[i] == '.')
	{
		option->preci = 0;
		option->flags[PRECI] = 1;
		i += check_p(&str[i], option);
	}
	while (str[i] == 'h' || str[i] == 'l' || str[i] == 'z' || str[i] == 'j')
		i += check_spe(&str[i], option);
	return (i);
}
