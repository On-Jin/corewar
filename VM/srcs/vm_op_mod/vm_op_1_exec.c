/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_1_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:21:10 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:21:12 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				vm_op_1_exec(t_datas *datas, t_process *process)
{
	datas->lives->total_lives++;
	datas->lives->cycle_lives++;
	process->live = 1;
	process->PC = (process->PC + 5) % MEM_SIZE;
	if (process->in_stock[1] != -1)
	{
		datas->lives->champ_total_lives[process->in_stock[1]]++;
		datas->lives->champ_cycle_lives[process->in_stock[1]]++;
		datas->lives->last_live = process->in_stock[0];
	}
}
