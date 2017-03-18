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

/*
** 03 70 02 00 13
** 03 70 03 ff ff
** 01 00 00 00 00
*/

void			vm_op_3_exec(t_datas *datas, t_process *process)
{
	char		i;

	i = datas->arene[vm_add_valid(process->PC + 1)];
//if ((datas->cycle.cycle + datas->cycle.total_cycle) >= 8894 && (datas->cycle.cycle + datas->cycle.total_cycle) <= 8898 && process->PC == 3967)
//	ft_printf("arg a la suite de l'op_encode [%2x][%2x][%2x]\n", datas->arene[vm_add_valid(process->PC + 2)], datas->arene[vm_add_valid(process->PC + 3)], datas->arene[vm_add_valid(process->PC + 4)]);

	if (vm_verif_datas(datas, process))
	{
		if (!(vm_recup_all_process(process, datas->arene, 1 << 24 | 1 << 18)))
		{
			if (((i >> 4) & 3) == 1 && process->in_stock[1] > 0 && process->in_stock[1] <= REG_NUMBER)
			{
				process->reg[process->in_stock[1]] = process->in_stock[0];
			}
			else if (((i >> 4) & 3) == 3)
			{
				if ((datas->cycle.cycle + datas->cycle.total_cycle) >= 8894 && (datas->cycle.cycle + datas->cycle.total_cycle) <= 8898 && process->PC == 3967)
				{
		//			ft_printf("reg1[%8x]reg2[%8x]reg3[%8x]reg4[%8x] op_encode = %x \n", process->reg[1], process->reg[2], process->reg[3], process->reg[4], i);
		//			ft_printf("process->in_stock[0] = %lx\t process->in_stock[1] = %d\t pc = %d\t adresse = %d \t cycle %ld\n", process->in_stock[0], process->in_stock[1], process->PC , vm_add_valid(process->PC + (process->in_stock[1] % IDX_MOD)), (datas->cycle.cycle + datas->cycle.total_cycle));
		//			if (vm_add_valid(process->PC + (process->in_stock[1] % IDX_MOD)) == 3969)
		//				process->in_stock[0] = -1;
				}
				vm_put_nbr_in_arene(process->in_stock[0], process->PC + (process->in_stock[1] % IDX_MOD), datas->arene, 4);
			}
		}
	}
	else if (datas->op_tab[(int)process->instruction].mod_carry)
		process->carry = 0;
	process->PC = vm_op_jump(datas, process,
							datas->op_tab[(int)process->instruction].nb_arg);
}
