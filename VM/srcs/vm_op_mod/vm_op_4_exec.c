/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_4_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:21:26 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:21:27 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			vm_op_4_exec(t_datas *datas, t_process *process)
{
	/*
	** executions
	*/
	(void)datas;
	if (process->in_stock[3] != -1)
	{
		process->reg[process->in_stock[2]] = ((unsigned int)process->in_stock[0] + (unsigned int)process->in_stock[1]) % IDX_MOD;
		process->carry = 1;
	}
	process->in_stock[3] = 0;
	process->PC = (process->PC + 4) % MEM_SIZE;
}
