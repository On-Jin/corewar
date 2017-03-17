/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_show_arene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 09:42:01 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/17 19:39:31 by ntoniolo         ###   ########.fr       */
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

void		print_live(t_datas *datas, t_draw *d, t_nc *nc)
{
	if (d)
		;
	mvprintw(6, nc->size_max_x + 2, "Cycle_Lives_:_%ld      ", datas->lives->cycle_lives);
	mvprintw(7, nc->size_max_x + 2, "Last_Lives_:_%10i     Last_Lives_cycle:_%10i ", datas->lives->last_live, datas->lives->cycle_last_live);
	mvprintw(8, nc->size_max_x + 2, "Total_Lives_:_%ld      ", datas->lives->total_lives);
}

void		print_process(t_datas *datas, t_draw *d, t_nc *nc)
{
	t_process	*pros;
	int			i;
	if (d)
		;

	i = datas->nbr_process;
	pros = datas->begin_process;
	while (pros && i != datas->nc.cur_pros)
	{
		pros = pros->next;
		i--;
	}
	mvprintw(9, nc->size_max_x + 4, "Process %i/%i", datas->nc.cur_pros, datas->nbr_process);
	if (pros && i > 0)
	{
		mvwaddch(datas->nc.win, pros->PC/64 +1, pros->PC %64*3  +2, 'L' | A_REVERSE);
		mvwaddch(datas->nc.win, pros->PC/64 +1, pros->PC %64*3 + 3, 'A' | A_REVERSE);
		mvprintw(10, nc->size_max_x + 4, "[%i] PC        ", pros->PC);
		mvprintw(11, nc->size_max_x + 4, "[%i] Cycle         ", pros->cycle);
		mvprintw(12, nc->size_max_x + 4, "[%i] Carry            ", (int)pros->carry);
		mvprintw(13, nc->size_max_x + 4, "[%i] Instruction        ", (int)pros->instruction);
		mvprintw(14, nc->size_max_x + 4, "[%i] Live                ", (int)pros->live);
		if (pros->cycle == 0)
		{
			mvprintw(16, nc->size_max_x + 4, "In Stock");
			mvprintw(17, nc->size_max_x + 4, "[%i][%i][%i]          ", pros->in_stock[0], pros->in_stock[1], pros->in_stock[2]);
		}
		else
		{
			mvprintw(16, nc->size_max_x + 4, "        ");
			mvprintw(17, nc->size_max_x + 4, "                       ");
		}
		mvprintw(18, nc->size_max_x + 4, "Reg : [%i][%i][%i][%i][%i][%i][%i][%i]", pros->reg[1], pros->reg[2],pros->reg[3],pros->reg[4],pros->reg[5],pros->reg[6],pros->reg[7],pros->reg[8]);
	}
}

void		print_debug(t_datas *datas, t_nc *nc)
{
	if (datas)
		;
	mvvline(22, nc->size_max_x + 2, 0, 44);
	mvvline(22, nc->size_max_x + 52, 0, 44);
	mvhline(22, nc->size_max_x + 2, 0, 50);
	mvhline(nc->size_max_y - 1, nc->size_max_x + 2, 0, 50);
	mvaddch(22, nc->size_max_x + 2, ACS_ULCORNER);
	mvaddch(22, nc->size_max_x + 2 + 50, ACS_URCORNER);
	mvaddch(nc->size_max_y - 1, nc->size_max_x + 2, ACS_LLCORNER);
	mvaddch(nc->size_max_y - 1, nc->size_max_x + 52, ACS_LRCORNER);
}

void		print_main_menu(t_datas *datas, t_nc *nc)
{
	int i;

	wattron(nc->inf, WA_BOLD);
	mvwprintw(nc->inf, 6, 10, "%s   %s   %s   %s", "[Processes]", "[Cycle Lives]", "[Last Live]", "[Total live]");
	mvwprintw(nc->inf, 7, 1, "%.9s", "!All");
	mvwprintw(nc->inf, 7, 10, "[%9lli]   [%11lli]   [%9i]   [%10lli]", datas->nbr_process, datas->lives->cycle_lives,
																	datas->lives->cycle_last_live, datas->lives->total_lives);
	i = 0;
	while (i < datas->player_nbr)
	{
		wattron(datas->nc.inf, COLOR_PAIR(i + 1));
		mvwprintw(nc->inf, 7 + i + 1, 1, "%.9s%i", "!Num", i + 1);
		mvwprintw(nc->inf, 7 + i + 1, 10, "[%9lli]   [%11lli]   [%9i]   [%10lli]", datas->inf[i].nbr_process, datas->inf[i].cycle_lives,
																	datas->inf[i].cycle_last_live, datas->inf[i].total_lives);
		wattroff(nc->inf, COLOR_PAIR(i + 1));
		i++;
	}
	wattroff(nc->inf, WA_BOLD);
}

void		ncurses_show_arene(t_datas *datas)
{
	t_draw	d;

	init_draw(&d);
	werase(datas->nc.win);
	box(datas->nc.win, 0 , 0);
	box(datas->nc.inf, 0 , 0);
	find_size_champ(datas, &d);
	find_pc_pros(datas, &d);

	loop_arene(datas, &d);
	print_cycle(datas, &datas->nc);
	print_kirby(datas, &datas->nc);
	print_main_menu(datas, &datas->nc);
//	print_live(datas, &d, &datas->nc);
//	print_process(datas, &d, &datas->nc);
//	print_debug(datas, &datas->nc);
	wrefresh(datas->nc.win);
	wrefresh(datas->nc.inf);
}
