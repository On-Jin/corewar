/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_show_arene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 09:42:01 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/20 13:43:03 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		init_draw(t_draw *d)
{
	d->index = 0;
	d->max = 0;
	d->count = 0;
	d->in_champ = 0;
	d->cur_champ = 0;
	d->size_champ = 0;
	d->save_pros = 0;
}

void		find_pc_pros(t_datas *datas, t_draw *d)
{
	t_process	*pros;
	int			min;

	min = MEM_SIZE * 8;
	pros = datas->begin_process;
	while (pros)
	{
		if (pros->PC < min && pros->PC > d->max)
		{
			min = pros->PC;
			d->save_pros = pros->PC;
		}
		pros = pros->next;
	}
	if (d->save_pros >= 0)
		d->max = d->save_pros;
}

void	find_size_champ(t_datas *datas, t_draw *d)
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
		wattron(datas->nc.win, COLOR_PAIR(d->cur_champ + 1));
	}
	if (d->count == d->size_champ + datas->start[d->cur_champ])
	{
		d->cur_champ++;
		find_size_champ(datas, d);
		d->in_champ = 0;
		wattroff(datas->nc.win, COLOR_PAIR(d->cur_champ));
	}
	if (d->count == d->save_pros)
	{
		mvwaddch(datas->nc.win, y, x, line[0] | A_REVERSE);
		mvwaddch(datas->nc.win, y, x + 1, line[1] | A_REVERSE);
		find_pc_pros(datas, d);
	}
	else
	{
		mvwaddch(datas->nc.win, y, x, line[0]);
		mvwaddch(datas->nc.win, y, x + 1, line[1]);
	}
	d->count++;
}

static void	loop_arene(t_datas *datas, t_draw *d)
{
	int		i;
	int		x;
	int		y;

	i = 0;
	y = 1;
	while (y < datas->nc.size_max_y - 1)
	{
		x = 2;
		while (x < datas->nc.size_max_x - 1  && i < MEM_SIZE)
		{
			vm_show_arene_element(datas, d, datas->arene[i], y, x);
			x += 3;
			++i;
		}
		y++;
	}
}

void		ncurses_show_arene(t_datas *datas)
{
	t_draw	d;

	init_draw(&d);
	datas->nc.i_print = 0;
	werase(datas->nc.win);
	werase(datas->nc.inf);
	box(datas->nc.win, 0 , 0);
	box(datas->nc.inf, 0 , 0);
	find_size_champ(datas, &d);
	find_pc_pros(datas, &d);

	loop_arene(datas, &d);
	print_cycle(datas, &datas->nc);
	print_kirby(datas, &datas->nc);
	print_main_menu(datas, &datas->nc);
	print_process(datas, &datas->nc);
	wrefresh(datas->nc.win);
	wrefresh(datas->nc.inf);
}
