/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_10_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:21:57 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:21:58 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Questions par commande:
** Que fait la commande?
** De qui a t'elle besoin?
** que fait elle si ses instrictions sont eronnees ?
** que fait elle si son op_code_instruc est erronne ?
** carry ?
** jump?
** ;
*/

/*
**Ldi
*/

void			vm_op_10_exec(t_datas *datas, t_process *process)
{
	if (vm_verif_datas(datas, process))
	{
		vm_recup_all_process(process, datas->arene, 1 << 24 | 1 << 16);
		if (process->in_stock[1] > 0 && process->in_stock[1] <= REG_NUMBER)
		{
			process->reg[process->in_stock[2]] = vm_recup_indirect_num(process, datas->arene, process->PC + (process->in_stock[0] + process->in_stock[1]) % IDX_MOD);
			process->carry = 1;
		}
	}
	else if (datas->op_tab[(int)process->instruction].mod_carry)
		process->carry = 0;
	process->PC = vm_op_jump(datas, process,
							datas->op_tab[(int)process->instruction].nb_arg);
/*	if (!(vm_verif_i_code(datas->arene[process->PC + 1 % MEM_SIZE], 7, 3, 1)))
	{
		process->in_stock[3] = -1;
		return ;
	}
	vm_recup_all_process(process, datas->arene, (1 << 8) | (1 << 17) | (1 << 25));
	if (process->in_stock[3] == -1 || !process->in_stock[2])
	{
		process->in_stock[3] = 0;
		return ;
	}
	process->reg[process->in_stock[2]] = ((process->in_stock[0] + process->in_stock[1]) % IDX_MOD);
	(void)datas;
	process->in_stock[3] = vm_ocp_size(datas->arene[(process->PC + 1) % MEM_SIZE], 4, 0);
	process->PC = (process->PC + process->in_stock[3]) % MEM_SIZE;
	*/
}
