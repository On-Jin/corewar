/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_show_arene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 09:42:01 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/09 18:58:19 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		vm_show_arene_start(int large_size)
{
	int		i;

	i = 1;
	ft_putchar('*');
	large_size = large_size * 3;
	while (i < large_size)
	{
		ft_putchar('_');
		++i;
	}
	ft_putstr("_*\n| ");
}

void		vm_show_arene_end(int large_size)
{
	int		i;

	i = 1;
	ft_putstr("|\n*_");
	large_size = large_size * 3;
	while (i < large_size)
	{
		ft_putchar('_');
		++i;
	}
	ft_putchar('*');
}

void		vm_show_arene_separ_line(void)
{
	ft_putstr("|\n| ");
}

void		vm_show_arene_element(char elem)
{
	char		line[3];

	line[2] = 0;
	line[1] = (unsigned char)elem % 16;
	line[0] = ((unsigned char)elem / 16) % 16;
	line[0] += (line[0] >= 10) ? ('a' - 10) : ('0');
	line[1] += (line[1] >= 10) ? ('a' - 10) : ('0');
	ft_putstr(line);
	ft_putchar(' ');
}

int			ft_square_root(int square)
{
	int		i;

	i = 1;
	while (i < square)
	{
		if (i * i == square)
			return (i);
		if (i * i > square)
			return (i - 1);
		++i;
	}
	return (0);
}

/*
** Plus grands diviseur commun
** great common divisor
*/

int			ft_gcd(int nbr)
{
	int		i;

	if (nbr < 1)
		return (-1);
	i = ft_square_root(nbr);
	while (nbr % i)
		--i;
	return (i);
}

void		vm_show_arene(t_vm *arene)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = ft_gcd(MEM_SIZE);//racine carree;

	line = (char *)arene->arene;
	vm_show_arene_start(j);
	while (i < MEM_SIZE)
	{
		vm_show_arene_element(line[i]);
		++i;
		if (i % j == 0 && i < MEM_SIZE)
			vm_show_arene_separ_line();
	}
	vm_show_arene_end(j);
	ft_printf("\n");
}
