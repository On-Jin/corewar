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

/*
** Lld
** a faire : creer un flag pour sup IDX_MOD
*/

void			vm_op_13_exec(t_datas *datas, t_process *process)
{
	/*
	** Lld
	** a faire : creer un flag pour sup IDX_MOD
	*/
	if (vm_verif_datas(datas, process))
	{
		vm_recup_all_process(process, datas->arene, 1 << 24);
		if (process->in_stock[1] > 0 && process->in_stock[1] <= REG_NUMBER)
		{
			process->reg[process->in_stock[1]] = process->in_stock[0];
			process->carry = 1;
		}
	}
	else if (datas->op_tab[(int)process->instruction].mod_carry)
		process->carry = 0;
	process->PC = vm_op_jump(datas, process,
							datas->op_tab[(int)process->instruction].nb_arg);
}
