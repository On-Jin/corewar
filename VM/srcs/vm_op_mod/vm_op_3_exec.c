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
** St
** Prend un registre et un registre ou un indirect,
** et stocke la valeur du registre vers le second paramètre.
** Par exemple, st r1, 42 stocke la valeur de r1 à l’adresse
** (PC + (42 % IDX_MOD))
*/

void			vm_op_3_exec(t_datas *datas, t_process *process)
{
	char		i;

	mvprintw(NC_DEBUG_Y + datas->i_debug++ + 5, NC_DEBUG_X, "yooooo reg[%d][%d]",process->reg[1], process->reg[2]);
	i = datas->arene[vm_add_valid(process->PC + 1)];
	if (vm_verif_datas(datas, process))
	{
		vm_recup_all_process(process, datas->arene, 1 << 24 | 1 << 18);
		mvprintw(NC_DEBUG_Y + datas->i_debug++ + 5, NC_DEBUG_X, "hey process_in_stock[%d][%d]",process->in_stock[0], process->in_stock[1]);
		if (((i >> 4) & 3) == 1 && process->in_stock[1] > 0 && process->in_stock[1] <= REG_NUMBER)
		{
			process->reg[process->in_stock[1]] = process->in_stock[0];
		}
		else if (((i >> 4) & 3) == 3)
		{
			mvprintw(NC_DEBUG_Y + datas->i_debug++ + 3, NC_DEBUG_X, "good road");
			vm_put_nbr_in_arene(process->in_stock[0], process->in_stock[1], datas->arene, 4);
		}

	}
	else if (datas->op_tab[(int)process->instruction].mod_carry)
		process->carry = 0;
	process->PC = vm_op_jump(datas, process,
							datas->op_tab[(int)process->instruction].nb_arg);
}
