/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 23:03:13 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/03/20 14:00:56 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		print_process(t_datas *datas, t_nc *nc)
{
	t_process	*pros;
	t_process	*tmp;
	int			i;
	int			nbr_process;

	pros = NULL;
	nbr_process = datas->inf[nc->cur_menu].nbr_process;
	i = datas->inf[nc->cur_menu].nbr_process;
	tmp = datas->begin_process;
	while (tmp && i != datas->inf[nc->cur_menu].cur_process)
	{
		if ((tmp->champion == nc->cur_menu) || nc->cur_menu == 0)
		{
			i--;
			pros = tmp;
		}
		tmp = tmp->next;
	}
	nc->i_print += 4;
	mvwprintw(nc->inf, nc->i_print, 9, "Process %i/%i", datas->inf[nc->cur_menu].cur_process + 1, nbr_process);
	if (pros)
	{
		wattron(datas->nc.inf, COLOR_PAIR(pros->champion) | WA_UNDERLINE | WA_BOLD);
		mvwprintw(nc->inf, nc->i_print, 9, "Process %i/%i", datas->inf[nc->cur_menu].cur_process + 1, nbr_process);
		wattroff(datas->nc.inf, COLOR_PAIR(pros->champion) | WA_UNDERLINE | WA_BOLD);
		mvwaddch(nc->win, pros->PC/64 +1, pros->PC %64*3  +2, 'L' | A_REVERSE);
		mvwaddch(nc->win, pros->PC/64 +1, pros->PC %64*3 + 3, 'A' | A_REVERSE);
		mvwprintw(nc->inf, ++nc->i_print, 3,  "Reg : [%i][%i][%i][%i][%i][%i][%i][%i]", pros->reg[0], pros->reg[1], pros->reg[2], pros->reg[3], pros->reg[4], pros->reg[5], pros->reg[6], pros->reg[7]);
		mvwprintw(nc->inf, ++nc->i_print, 3 ,"Reg : [%i][%i][%i][%i][%i][%i][%i][%i]", pros->reg[8], pros->reg[9], pros->reg[10], pros->reg[11], pros->reg[12], pros->reg[13], pros->reg[14], pros->reg[15]);
		nc->i_print++;
		mvwprintw(nc->inf, ++nc->i_print, 3, "PC    [%i]", pros->PC);
		mvwprintw(nc->inf, ++nc->i_print, 3, "Cycle [%i]", pros->cycle);
		mvwprintw(nc->inf, ++nc->i_print, 3, "OpCod [%i]", pros->instruction);
		mvwprintw(nc->inf, ++nc->i_print, 3, "Carry [%i]", pros->carry);
		mvwprintw(nc->inf, ++nc->i_print, 3, "Live  [%i]", pros->live);
		nc->i_print++;
		mvwprintw(nc->inf, ++nc->i_print, 3, "In_stock  [%i][%i][%i]", pros->in_stock[0], pros->in_stock[1], pros->in_stock[2]);
	}
}
