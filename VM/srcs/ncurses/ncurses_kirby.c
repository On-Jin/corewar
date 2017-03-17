/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_kirby.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 18:19:08 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/03/17 18:19:33 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		print_kirby(t_datas *datas, t_nc *nc)
{
	if (datas->cycle.cycle % 14 == 1)
		mvwprintw(nc->inf, 1, NC_W_INF - 17, "<(^_^)>");
	else if (datas->cycle.cycle % 14 == 2)
		mvwprintw(nc->inf, 1, NC_W_INF - 17,  "<(^_^<)");
	else if (datas->cycle.cycle % 14 == 3)
		mvwprintw(nc->inf, 1, NC_W_INF - 17,  " (^_^<)");
	else if (datas->cycle.cycle % 14 == 4)
		mvwprintw(nc->inf, 1, NC_W_INF - 17,  "  (_^<)");
	else if (datas->cycle.cycle % 14 == 5)
		mvwprintw(nc->inf, 1, NC_W_INF - 17,  "   (^<)");
	else if (datas->cycle.cycle % 14 == 6)
		mvwprintw(nc->inf, 1, NC_W_INF - 17,  "   (< )");
	else if (datas->cycle.cycle % 14 == 7)
		mvwprintw(nc->inf, 1, NC_W_INF - 17,  "  <(  )");
	else if (datas->cycle.cycle % 14 == 8)
		mvwprintw(nc->inf, 1, NC_W_INF - 17,  "  (  )>");
	else if (datas->cycle.cycle % 14 == 9)
		mvwprintw(nc->inf, 1, NC_W_INF - 17,  "  (  >)");
	else if (datas->cycle.cycle % 14 == 10)
		mvwprintw(nc->inf, 1, NC_W_INF - 17,  "   ( >)");
	else if (datas->cycle.cycle % 14 == 11)
		mvwprintw(nc->inf, 1, NC_W_INF - 17,  "   (>^)");
	else if (datas->cycle.cycle % 14 == 12)
		mvwprintw(nc->inf, 1, NC_W_INF - 17,  "  (>^_)");
	else if (datas->cycle.cycle % 14 == 13)
		mvwprintw(nc->inf, 1, NC_W_INF - 17,  " (>^_^)");
	else if (datas->cycle.cycle % 14 == 0)
		mvwprintw(nc->inf, 1, NC_W_INF - 17,  "(>^_^)>");
}
