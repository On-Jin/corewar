/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_comment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 00:08:04 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/03/22 22:38:46 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		print_comment(t_datas *datas, t_nc *nc)
{
	if (nc->i_com == 0)
		nc->i_com = 50;
//	mvwprintw(nc->inf, 13, 2, "%*sC'est une idee", nc->i_com, datas->begin_champ[0].champ_com);
	(void)datas;
		if (((nc->t2.tv_sec - nc->t1.tv_sec)))
		{
			gettimeofday(&nc->t1, NULL);
			nc->i_com--;
		}
		gettimeofday(&nc->t2, NULL);
}
