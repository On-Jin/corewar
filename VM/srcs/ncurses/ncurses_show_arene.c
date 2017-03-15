/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_show_arene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 09:42:01 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/15 19:23:22 by ntoniolo         ###   ########.fr       */
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
		wattron(datas->win, COLOR_PAIR(d->cur_champ + 1));
	}
	if (d->count == d->size_champ + datas->start[d->cur_champ])
	{
		d->cur_champ++;
		find_size_champ(datas, d);
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

static void	loop_arene(t_datas *datas, t_draw *d)
{
	int		i;
	int		x;
	int		y;

	i = 0;
	y = 1;
	while (y < datas->size_max_y - 1)
	{
		x = 2;
		while (x < datas->size_max_x - 1  && i < MEM_SIZE)
		{
			vm_show_arene_element(datas, d, datas->arene[i], y, x);
			x += 3;
			++i;
		}
		y++;
	}
}

void		print_cycle(t_datas *datas, t_draw *d)
{
	if(d)
		;
	mvprintw(1, datas->size_max_x + 2, "Total cycle : %i", datas->cycle.total_cycle + datas->cycle.cycle);
	mvprintw(2, datas->size_max_x + 2, "%i/%i", datas->cycle.cycle, datas->cycle.cycle_to_die);
	mvprintw(4, datas->size_max_x + 2, "Check : %i", datas->cycle.check);
}

void		print_live(t_datas *datas, t_draw *d)
{
	if (d)
		;
	mvprintw(6, datas->size_max_x + 2, "Cycle_Lives_:_%ld      ", datas->lives->cycle_lives);
	mvprintw(7, datas->size_max_x + 2, "Last_Lives_:_%i      ", datas->lives->last_live);
	mvprintw(8, datas->size_max_x + 2, "Total_Lives_:_%ld      ", datas->lives->total_lives);
}

void		print_process(t_datas *datas, t_draw *d)
{
	t_process	*pros;
	int			i;
	if (d)
		;
	
	i = datas->nbr_process;
	pros = datas->begin_process;
	while (pros && i != datas->cur_pros)
	{
		pros = pros->next;
		i--;
	}
	mvprintw(9, datas->size_max_x + 4, "Process %i/%i", datas->cur_pros, datas->nbr_process);
	if (pros && i > 0)
	{
		mvprintw(10, datas->size_max_x + 4, "[%i] PC        ", pros->PC);
		mvprintw(11, datas->size_max_x + 4, "[%i] Cycle         ", pros->cycle);
		mvprintw(12, datas->size_max_x + 4, "[%i] Carry            ", (int)pros->carry);
		mvprintw(13, datas->size_max_x + 4, "[%i] Instruction        ", (int)pros->instruction);
		mvprintw(14, datas->size_max_x + 4, "[%i] Live                ", (int)pros->live);
		if (pros->cycle == 0)
		{
			mvprintw(16, datas->size_max_x + 4, "In Stock");
			mvprintw(17, datas->size_max_x + 4, "[%i][%i][%i]          ", pros->in_stock[0], pros->in_stock[1], pros->in_stock[2]);
		}
		else
		{
			mvprintw(16, datas->size_max_x + 4, "        ");
			mvprintw(17, datas->size_max_x + 4, "                       ");
		}
		mvprintw(18, datas->size_max_x + 4, "Reg : [%i][%i][%i][%i][%i][%i][%i][%i]", pros->reg[1], pros->reg[2],pros->reg[3],pros->reg[4],pros->reg[5],pros->reg[6],pros->reg[7],pros->reg[8]);
	}
}
//ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_BLCORNER, ACS_BRCORNER
void		print_debug(t_datas *datas)
{
	mvvline(22, datas->size_max_x + 2, 0, 44);
	mvvline(22, datas->size_max_x + 52, 0, 44);
	mvhline(22, datas->size_max_x + 2, 0, 50);
	mvhline(datas->size_max_y - 1, datas->size_max_x + 2, 0, 50);
	mvaddch(22, datas->size_max_x + 2, ACS_ULCORNER);
	mvaddch(22, datas->size_max_x + 2 + 50, ACS_URCORNER);
	mvaddch(datas->size_max_y - 1, datas->size_max_x + 2, ACS_LLCORNER);
	mvaddch(datas->size_max_y - 1, datas->size_max_x + 52, ACS_LRCORNER);
}

void		ncurses_show_arene(t_datas *datas)
{
	t_draw	d;

	init_draw(&d);
	werase(datas->win);
	box(datas->win, 0 , 0);
	find_size_champ(datas, &d);
	find_pc_pros(datas, &d);

	loop_arene(datas, &d);
	print_cycle(datas, &d);
	print_live(datas, &d);
	print_process(datas, &d);
	print_debug(datas);
	wrefresh(datas->win);
}
