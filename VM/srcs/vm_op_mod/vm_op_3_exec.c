/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_3_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:21:21 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:21:22 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			vm_op_3_exec(t_datas *datas, t_process *process)
{
	(void)datas;
	if (process->in_stock[0] > 0 && process->in_stock[0] < REG_NUMBER)
	{
		process->reg[process->in_stock[0]] = process->PC + (process->in_stock[1] % IDX_MOD);
		process->carry = 0;
	}
	process->PC = (process->PC + process->in_stock[3] + 1) % MEM_SIZE;

//process->carry = 0;
//process->PC = (process->PC + A_CHANGER) % MEM_SIZE;
}
