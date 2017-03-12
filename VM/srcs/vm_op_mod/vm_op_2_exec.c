/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_2_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:21:16 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:21:17 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			vm_op_2_exec(t_datas *datas, t_process *process)
{
	(void)datas;

	if (process->in_stock[1] > 0 && process->in_stock[1] <= REG_NUMBER)
	{
		process->reg[process->in_stock[1] - 1] = process->in_stock[0];
		process->carry = 1;
	}
	if (!process->in_stock[2])
		process->in_stock[2] = 2;
	process->PC = (process->PC + process->in_stock[2] + 1) % MEM_SIZE;
}
