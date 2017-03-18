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

/*
** St
** Prend un registre et un registre ou un indirect,
** et stocke la valeur du registre vers le second paramètre.
** Par exemple, st r1, 42 stocke la valeur de r1 à l’adresse
** (PC + (42 % IDX_MOD))
*/

void			vm_op_3_exec(t_datas *datas, t_process *process)
{
	char		i;

	i = process->in_stock[3];
	if (i != 1)
	{
		if (((i >> 4) & 3) == 1 && process->in_stock[1] > 0 && process->in_stock[1] <= REG_NUMBER)
		{
			process->reg[process->in_stock[1]] = process->in_stock[0];
		}
		else if (((i >> 4) & 3) == 3)
		{
/*			if ((datas->cycle.cycle + datas->cycle.total_cycle) >= 8894 && (datas->cycle.cycle + datas->cycle.total_cycle) <= 8898)
			{
				ft_printf("process->in_stock[0] = %lx\t process->in_stock[1] = %d\t pc = %d\t adresse = %d \t cycle %ld\n", process->in_stock[0], process->in_stock[1], process->PC , vm_add_valid(process->PC + (process->in_stock[1] % IDX_MOD)), (datas->cycle.cycle + datas->cycle.total_cycle));
				if (vm_add_valid(process->PC + (process->in_stock[1] % IDX_MOD)) == 3969)
					process->in_stock[0] = -1;
			}
*/			vm_put_nbr_in_arene(process->in_stock[0], vm_add_valid(process->PC + (process->in_stock[1] % IDX_MOD)), datas->arene, 4);
		}
	}
	else if (datas->op_tab[(int)process->instruction].mod_carry)
		process->carry = 0;
	process->PC = vm_op_jump(datas, process,
							datas->op_tab[(int)process->instruction].nb_arg);
	process->in_stock[0] = 0;
	process->in_stock[1] = 0;
	process->in_stock[2] = 0;
	process->in_stock[3] = 0;
}
