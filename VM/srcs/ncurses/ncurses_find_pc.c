/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 17:56:12 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/03/20 17:58:38 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		ncurses_find_pc(t_datas *datas, t_draw *d)
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
