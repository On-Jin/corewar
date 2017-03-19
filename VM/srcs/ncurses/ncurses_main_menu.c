/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_main_menu.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 23:05:27 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/03/19 23:08:31 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		print_main_menu(t_datas *datas, t_nc *nc)
{
	int i;

	wattron(nc->inf, WA_BOLD);
	mvwprintw(nc->inf, nc->i_print += 2, 10, "%s   %s   %s   %s", "[Processes]", "[Cycle Lives]", "[Last Live]", "[Total live]");
	if (nc->cur_menu == 0)
	{
		wattron(nc->inf, WA_REVERSE);
		mvwprintw(nc->inf, ++nc->i_print, 1, "%.9s", "!All");
		wattroff(nc->inf, WA_REVERSE);
	}
	else
		mvwprintw(nc->inf, ++nc->i_print, 1, "%.9s", "!All");
	mvwprintw(nc->inf, nc->i_print, 10, "[%9lli]   [%11lli]   [%9i]   [%10lli]", datas->nbr_process, datas->lives->cycle_lives,
			datas->lives->cycle_last_live, datas->lives->total_lives);
	i = 0;
	while (i < datas->player_nbr)
	{
		wattron(datas->nc.inf, COLOR_PAIR(i + 1));
		if (nc->cur_menu == i + 1)
		{
			wattron(nc->inf, WA_REVERSE);
			mvwprintw(nc->inf, nc->i_print + i + 1, 1, "%.9s%i", "!Num", i + 1);
			wattroff(nc->inf, WA_REVERSE);
		}
		else
			mvwprintw(nc->inf, nc->i_print + i + 1, 1, "%.9s%i", "!Num", i + 1);
		mvwprintw(nc->inf, nc->i_print + i + 1, 10, "[%9lli]   [%11lli]   [%9i]   [%10lli]", datas->inf[i].nbr_process, datas->inf[i].cycle_lives,
				datas->inf[i].cycle_last_live, datas->inf[i].total_lives);
		wattroff(nc->inf, COLOR_PAIR(i + 1));
		i++;
	}
	nc->i_print += i;
	wattroff(nc->inf, WA_BOLD);
}
