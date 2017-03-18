/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_9_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:21:51 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/17 17:29:03 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** zjmp
*/

void			vm_op_9_exec(t_datas *datas, t_process *process)
{
	int		arg1;
	int		arg2;

	arg1 = process->PC;
	if (process->carry)
		process->PC = vm_add_valid(process->PC +
			(arg2 = (vm_recup_arena_num(2, datas->arene, process->PC + 1) % IDX_MOD)));
	else
		process->PC = vm_add_valid(process->PC + 3);

	process->in_stock[0] = 0;
	process->in_stock[1] = 0;
	process->in_stock[2] = 0;
	process->in_stock[3] = 0;
}
