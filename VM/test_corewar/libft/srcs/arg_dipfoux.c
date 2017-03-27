/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_dipfoux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 20:51:08 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/01/18 13:23:21 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	mod_uox(char *str, t_option *option)
{
	long long int	nb;

	nb = 0;
	if (option->mod == MOD_HH)
		nb = (long long)(unsigned char)va_arg(option->ap, unsigned int);
	else if (option->mod == MOD_H)
		nb = (long long)(unsigned short int)va_arg(option->ap, unsigned int);
	else if (option->mod == MOD_L)
		nb = (long long)va_arg(option->ap, unsigned long int);
	else if (option->mod == MOD_LL)
		nb = (long long)va_arg(option->ap, long long unsigned int);
	else if (option->mod == MOD_J)
		nb = (long long)va_arg(option->ap, uintmax_t);
	else if (option->mod == MOD_Z)
		nb = (long long)va_arg(option->ap, size_t);
	write_dipoux(str, option, nb);
}

void	mod_di(char *str, t_option *option)
{
	long long int	nb;

	nb = 0;
	if (*str == 'D')
	{
		if (option->mod == MOD_L)
			option->mod = MOD_LL;
		if (option->mod < MOD_L)
			option->mod = MOD_L;
	}
	if ((*str == 'd' || *str == 'i') && option->mod == MOD_HH)
		nb = (long long)(signed char)va_arg(option->ap, int);
	else if ((*str == 'd' || *str == 'i') && option->mod == MOD_H)
		nb = (long long)(short int)va_arg(option->ap, int);
	else if (ft_isin("dDi", *str) && option->mod == MOD_L)
		nb = (long long)va_arg(option->ap, long int);
	else if (ft_isin("dDi", *str) && option->mod == MOD_LL)
		nb = va_arg(option->ap, long long);
	else if ((*str == 'd' || *str == 'i') && option->mod == MOD_J)
		nb = va_arg(option->ap, intmax_t);
	else if ((*str == 'd' || *str == 'i') && option->mod == MOD_Z)
		nb = va_arg(option->ap, size_t);
	write_dipoux(str, option, nb);
}

int		dipfoux(char *str, t_option *option)
{
	long long int nb;

	nb = 0;
	if (*str == 'f' || *str == 'F')
	{
		if (*str == 'f')
			write_f(str, option, (long double)va_arg(option->ap, double));
		else if (*str == 'F' || (*str == 'f' && option->mod == MOD_LLL))
			write_f(str, option, (long double)va_arg(option->ap, double));
		return (0);
	}
	else if (*str == 'U' || *str == 'O')
		nb = (long long)va_arg(option->ap, unsigned long int);
	else if (*str == 'u' || *str == 'o' || *str == 'x' || *str == 'X')
		nb = (long long)va_arg(option->ap, unsigned int);
	else if (*str == 'd' || *str == 'i' || *str == 'D')
		nb = (long long)va_arg(option->ap, int);
	else if (*str == 'p')
		nb = (long long int)va_arg(option->ap, void*);
	write_dipoux(str, option, nb);
	return (1);
}
