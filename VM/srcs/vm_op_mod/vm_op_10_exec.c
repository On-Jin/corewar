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
**Ldi
**{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
**	"load index", 1, 1, 0},
**• ldi : ldi, comme son nom l’indique, n’implique nullement de se baigner dans de
** la crème de marrons, même si son opcode est 0x0a. Au lieu de ça, ca prend 2 index
** et 1 registre, additionne les 2 premiers, traite ca comme une adresse, y lit une
** valeur de la taille d’un registre et la met dans le 3eme
*/

void			vm_op_10_exec(t_datas *datas, t_process *process)
{
	unsigned int			instruc;

	instruc = (unsigned char)datas->arene[vm_add_valid(process->PC + 1)];
	if (vm_verif_datas(datas, process))
	{
		if (!vm_recup_all_process(process, datas->arene, 1 << 24 | 1 << 16) &&
			process->in_stock[2] > 0 && process->in_stock[2] <= REG_NUMBER)
		{
			process->reg[process->in_stock[2]] = vm_recup_arena_num(4, datas->arene, vm_add_valid(process->PC + (process->in_stock[0] +
												process->in_stock[1]) % IDX_MOD)) % IDX_MOD/*????*/;
		/*	process->reg[process->in_stock[2]] = vm_recup_indirect_num(process,
				datas->arene, process->PC + (process->in_stock[0] +
				process->in_stock[1]) % IDX_MOD);
		*/	process->carry = 1;
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
