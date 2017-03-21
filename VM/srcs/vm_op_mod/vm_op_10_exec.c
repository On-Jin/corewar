/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_10_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:21:57 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/21 17:41:39 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**Ldi
**{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
**	"load index", 1, 1, 0},
*/

/* SAVE work gnebie // doesnt work with fluttershy.cor
	if (!vm_recup_all_process(process, datas->arene, 1 << 24 | 1 << 16) &&
		process->in_stock[2] > 0 && process->in_stock[2] <= REG_NUMBER)
	{
		process->reg[process->in_stock[2]] = vm_recup_arena_num(4, datas->arene, vm_add_valid(process->PC + (process->in_stock[0] +
											process->in_stock[1]) % IDX_MOD)) % IDX_MOD; //???
	//	process->reg[process->in_stock[2]] = vm_recup_indirect_num(process,
	//		datas->arene, process->PC + (process->in_stock[0] +
	//		process->in_stock[1]) % IDX_MOD);
		process->carry = 1;
*/

void			vm_op_10_exec(t_datas *datas, t_process *process)
{
	unsigned int			instruc;

	instruc = (unsigned char)datas->arene[vm_add_valid(process->PC + 1)];
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
