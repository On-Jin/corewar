/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_10_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:21:57 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/21 16:32:32 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**Ldi
*/
/*
Cette opération modifie le carry. ldi 3,%4,r1 lit IND_SIZE octets
a l’adresse : (PC + (3 % IDX_MOD)) ajoute 4 à cette valeur. On
nommera S cette somme. On lit REG_SIZE octet à l’adresse (PC
		+ (S % IDX_MOD)) que l’on copie dans r1. Les paramètres 1 et
2 sont des index.
*/
void			vm_op_10_exec(t_datas *datas, t_process *process)
{
	if (vm_verif_datas(datas, process))
	{
		vm_recup_all_process(process, datas->arene, 1 << 25 | 1 << 16);
//		mvprintw(50, 64*3+2+100, "Stock [%i][%i][%i]", process->in_stock[0], process->in_stock[1], process->in_stock[2]);
		if (process->in_stock[2] > 0 && process->in_stock[2] <= REG_NUMBER)
		{
			process->reg[process->in_stock[2]] = vm_recup_arena_num(4, datas->arene,
					vm_add_valid((process->PC + (process->in_stock[0] %IDX_MOD) + process->in_stock[1])));
			process->carry = 1;
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
