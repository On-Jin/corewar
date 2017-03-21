/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_14_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:22:16 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:22:17 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			vm_op_14_exec(t_datas *datas, t_process *process)
{
	unsigned int			instruc;

	instruc = (unsigned char)datas->arene[vm_add_valid(process->PC + 1)];
	if (vm_verif_datas(datas, process))
	{
		vm_recup_all_process(process, datas->arene, 1 << 24 | 1 << 16);
		if (process->in_stock[1] > 0 && process->in_stock[1] <= REG_NUMBER)
		{
			process->reg[process->in_stock[2]] = vm_recup_indirect_num(process,
				datas->arene, process->PC + (process->in_stock[0] +
				process->in_stock[1]));
			process->carry = 1;
		}
		else
			process->carry = 0;
	}
	else if (datas->op_tab[(int)process->instruction].mod_carry)
		process->carry = 0;
	process->PC = vm_op_jump(datas, process, instruc,
							datas->op_tab[(int)process->instruction].nb_arg);
	process->in_stock[0] = 0;
	process->in_stock[1] = 0;
	process->in_stock[2] = 0;
	process->in_stock[3] = 0;
}
