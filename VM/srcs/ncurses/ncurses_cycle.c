/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_cycle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 18:42:25 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/03/17 18:44:09 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		print_cycle(t_datas *datas, t_nc *nc)
{
	wattron(nc->inf, WA_UNDERLINE);
	mvwprintw(nc->inf, 1, 2, "Total Cycles", WA_UNDERLINE | WA_LOW);
	wattroff(nc->inf, WA_UNDERLINE);
	mvwprintw(nc->inf, 1, 20, "Current Cycles / ");
	mvwprintw(nc->inf, 1, 37, "Cycles to die");
	mvwprintw(nc->inf, 2, 2, "[%7lld   ]", datas->cycle.total_cycle + datas->cycle.cycle);
	mvwprintw(nc->inf, 2, 28, "[%-4lld] /", datas->cycle.cycle);
	mvwprintw(nc->inf, 2, 37, "[%-4lld]", datas->cycle.cycle_to_die);;
	mvwprintw(nc->inf, 4, 1, "--------------------------------------------------------------------");;
}
