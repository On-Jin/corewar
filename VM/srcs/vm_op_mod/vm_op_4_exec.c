/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_4_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:21:26 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:21:27 by gnebie           ###   ########.fr       */
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
** Add
** Prend trois registres,
** additionne les 2 premiers,
** met le résultat dans le troisième,
** juste avant de modifier le carry.
*/

void			vm_op_4_exec(t_datas *datas, t_process *process)
{
	mvprintw(NC_DEBUG_Y + datas->i_debug++ + 5, NC_DEBUG_X, "hey reg[%d][%d][%d][%d][%d][%d]",process->reg[1], process->reg[2],process->reg[3], process->reg[4],process->reg[5], process->reg[6]);
	if (vm_verif_datas(datas, process))
	{
		vm_recup_all_process(process, datas->arene, 1 << 24 | 1 << 16);
			mvprintw(NC_DEBUG_Y + datas->i_debug++, NC_DEBUG_X, "process_in_stock[%d][%d][%d]---",process->in_stock[0], process->in_stock[1], process->in_stock[2] );
		if (process->in_stock[2] > 0 && process->in_stock[2] <= REG_NUMBER)
		{
			process->reg[process->in_stock[2]] = process->in_stock[0] + process->in_stock[1];
			process->carry = 1;
		}
		else if (datas->op_tab[(int)process->instruction].mod_carry)
			process->carry = 0;
	}
	else if (datas->op_tab[(int)process->instruction].mod_carry)
		process->carry = 0;
	process->PC = vm_op_jump(datas, process,
							datas->op_tab[(int)process->instruction].nb_arg);

	mvprintw(NC_DEBUG_Y + datas->i_debug++ + 7, NC_DEBUG_X, "process[%d][%d][%d]",process->in_stock[0], process->in_stock[1],process->in_stock[2]);

/*
		unsigned int tmp;

	tmp = (unsigned int)(datas->arene[(process->PC + 1) % MEM_SIZE]);
	if (tmp <= REG_NUMBER)
		process->in_stock[0] = process->reg[tmp];
	else
		process->in_stock[3] = -1;
	tmp = (unsigned int)(datas->arene[(process->PC + 2) % MEM_SIZE]);
	if (tmp <= REG_NUMBER)
		process->in_stock[1] = process->reg[tmp];
	else
		process->in_stock[3] = -1;
	process->in_stock[2] = datas->arene[(process->PC + 3) % MEM_SIZE];
	if (process->in_stock[2] > REG_NUMBER || process->in_stock[2] < 0)
		process->in_stock[3] = -1;
	(void)datas;
	if (process->in_stock[3] != -1)
	{
		process->reg[process->in_stock[2]] = ((unsigned int)process->in_stock[0] + (unsigned int)process->in_stock[1]) % IDX_MOD;
		process->carry = 1;
	}
	process->in_stock[3] = 0;
	process->PC = (process->PC + 4) % MEM_SIZE;
	*/
}
