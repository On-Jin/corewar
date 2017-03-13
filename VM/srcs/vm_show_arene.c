/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_show_arene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 09:42:01 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/13 12:59:43 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

typedef struct 	s_draw
{
	int			index;
	int			min;
	int			max;
	int			count;
	int			in_champ;
	int			cur_champ;
	int			size_champ;
	int			save_pros;
}				t_draw;

void		init_draw(t_draw *d)
{
	//ft_bzero((void *)d->buff, MEM_SIZE * 4);
	d->index = 0;
	d->min = MEM_SIZE * 8;
	d->max = 0;
	d->count = 0;
	d->in_champ = 0;
	d->cur_champ = 0;
	d->size_champ = 0;
	d->save_pros = 0;
}

void		find_pc_pros(t_datas *datas, t_draw *d)
{
	t_process *pros;

	d->min = MEM_SIZE * 8;
	pros = datas->begin_process;
	while (pros)
	{
		if (pros->PC < d->min && pros->PC > d->max)
		{
			d->min = pros->PC;
			d->save_pros = pros->PC;
		}
		pros = pros->next;
	}
	if (d->save_pros >= 0)
		d->max = d->save_pros;
}

void	size_draw_champ(t_datas *datas, t_draw *d)
{
	d->size_champ = (datas->size_champ[d->cur_champ]);
}

void		vm_show_arene_element(t_datas *datas, t_draw *d, char elem, int y, int x)
{
	char		line[3];

	line[2] = 0;
	line[1] = (unsigned char)elem % 16;
	line[0] = ((unsigned char)elem / 16) % 16;
	line[0] += (line[0] >= 10) ? ('a' - 10) : ('0');
	line[1] += (line[1] >= 10) ? ('a' - 10) : ('0');

	if (d->count == datas->start[d->cur_champ])
	{
		d->in_champ = 1;
		wattron(datas->win, COLOR_PAIR(d->cur_champ + 1));
	}
	if (d->count == d->size_champ + datas->start[d->cur_champ])
	{
		d->cur_champ++;
		size_draw_champ(datas, d);
		d->in_champ = 0;
		wattroff(datas->win, COLOR_PAIR(d->cur_champ));
	}
	if (d->count == d->save_pros)
	{
		mvwaddch(datas->win, y, x, line[0] | A_REVERSE);
		mvwaddch(datas->win, y, x + 1, line[1] | A_REVERSE);
		find_pc_pros(datas, d);
	}
	else
	{
		mvwaddch(datas->win, y, x, line[0]);
		mvwaddch(datas->win, y, x + 1, line[1]);
	}
	d->count++;
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

void		vm_show_arene(t_datas *datas, t_vm *arene)
{
	int		i;
	int		j;
	int		x;
	int		y;
	char	*line;
	t_draw	d;


	init_draw(&d);
	werase(datas->win);
	wborder(datas->win, '*', '*', '*', '*', '*', '*', '*', '*');
	size_draw_champ(datas, &d);
	find_pc_pros(datas, &d);

	i = 0;
	j = ft_gcd(MEM_SIZE);//racine carree;
	line = (char *)arene->arene;
	y = 1;
	while (y < SIZE_MAX_Y - 1)
	{
		x = 1;
		while (x < SIZE_MAX_X - 1  && i < MEM_SIZE)
		{
			vm_show_arene_element(datas, &d, line[i], y, x);
			x += 3;
			++i;
		}
		y++;
	}
	mvprintw(10, SIZE_MAX_X + 5, "Cycle : %i", datas->cycle.total_cycle + datas->cycle.cycle);
	wrefresh(datas->win);
//	usleep(14000);
}
