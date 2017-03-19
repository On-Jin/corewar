/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 12:55:11 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/03/17 20:06:30 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		ncurses_key(t_datas *datas)
{
	int		ret;

	timeout(1);
	ret = getch();
	if (ret > 'A' && ret < 'z')
		datas->nc.key = ret;
	if (ret == NC_PROC_NEXT && datas->nbr_process > datas->nc.cur_pros)
		datas->nc.cur_pros++;
	if (ret == NC_PROC_BACK && datas->nc.cur_pros > 0)
		datas->nc.cur_pros--;
	if (ret == KEY_DOWN && datas->nc.cur_menu < datas->player_nbr )
		datas->nc.cur_menu++;
	if (ret == KEY_UP && datas->nc.cur_menu > 0)
		datas->nc.cur_menu--;
}
