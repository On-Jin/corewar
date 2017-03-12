/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_13_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:22:11 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:22:12 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			vm_op_13_exec(t_datas *datas, t_process *process)
{
	if (process->in_stock[3] != -1)
	{
		process->carry = 1;
		if (process->in_stock[1] > 0 && process->in_stock[1] < REG_NUMBER)
			process->reg[process->in_stock[1]] = process->in_stock[0];
	}
	process->in_stock[3] = vm_ocp_size(datas->arene->arene[(process->PC + 1) % MEM_SIZE], 4, 0);
	if (process->in_stock[3] == 0)
		{process->in_stock[3] = 3;}
	process->PC = (process->PC + process->in_stock[3]) % MEM_SIZE;

}
