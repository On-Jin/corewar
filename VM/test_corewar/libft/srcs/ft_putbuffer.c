/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbuffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 19:33:18 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/01/19 15:48:06 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_putbufferchar(char c, t_option *option)
{
	option->buffer[option->b] = c;
	option->b++;
	if (option->b == BUFF_SIZE_P)
	{
		write(1, &option->buffer, option->b);
		option->b = 0;
		ft_bzero(option->buffer, BUFF_SIZE_P);
	}
}

void	ft_putbuffer(t_option *option)
{
	int i;

	i = 0;
	while (i < option->final_len)
	{
		option->buffer[option->b] = option->final[i];
		option->b = option->b + 1;
		if (option->b == BUFF_SIZE_P)
		{
			write(1, &option->buffer, option->b);
			option->b = 0;
			ft_bzero(option->buffer, BUFF_SIZE_P);
		}
		i++;
	}
}
