/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_12_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:22:07 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/16 23:36:03 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Fork
*/

void			vm_op_12_exec(t_datas *datas, t_process *process)
{
	vm_copy_process(datas, process, vm_add_valid(process->PC +
		vm_recup_arena_num(2, datas->arene, process->PC + 1) % IDX_MOD));
	process->PC = vm_add_valid(process->PC + 3);

	process->in_stock[0] = 0;
	process->in_stock[1] = 0;
	process->in_stock[2] = 0;
	process->in_stock[3] = 0;
}
