/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_18_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 18:34:33 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/24 18:34:35 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**
*/

void			vm_op_18_exec(t_datas *datas, t_process *process)
{
	if (vm_verif_datas(datas, process))
	{
		vm_recup_all_process(process, datas->arene, 1 << 24 | 1 << 16);
		if (process->in_stock[2] > 0 && process->in_stock[2] <= REG_NUMBER)
		{
			if (process->in_stock[0] && process->in_stock[1])
				process->reg[process->in_stock[2]] = process->in_stock[0] /
													process->in_stock[1];
			else
				process->reg[process->in_stock[2]] = 0;
			if (!process->reg[process->in_stock[2]])
				process->carry = 1;
			else
				process->carry = 0;
		}
	}
	process->PC = vm_op_jump(datas, process,
							datas->op_tab[(int)process->instruction].nb_arg);
}
