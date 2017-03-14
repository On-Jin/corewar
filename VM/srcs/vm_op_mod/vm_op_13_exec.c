/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_13_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:22:11 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:22:12 by gnebie           ###   ########.fr       */
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
** Lld
** a faire : creer un flag pour sup IDX_MOD
*/

void			vm_op_13_exec(t_datas *datas, t_process *process)
{
	/*
	** Lld
	** a faire : creer un flag pour sup IDX_MOD
	*/
	if (vm_verif_datas(datas, process))
	{
//		mvprintw(NC_DEBUG_Y + datas->i_debug++, NC_DEBUG_X, "je suis la");
		vm_recup_all_process(process, datas->arene, 1 << 24);
//		mvprintw(NC_DEBUG_Y + datas->i_debug++, NC_DEBUG_X, "process_in_stock[%d][%d]",process->in_stock[0], process->in_stock[1] );
		if (process->in_stock[1] > 0 && process->in_stock[1] <= REG_NUMBER)
		{
			process->reg[process->in_stock[1]] = process->in_stock[0];
			process->carry = 1;
		}
	}
	else if (datas->op_tab[(int)process->instruction].mod_carry)
		process->carry = 0;
	process->PC = vm_op_jump(datas, process,
							datas->op_tab[(int)process->instruction].nb_arg);


/*	if (!(vm_verif_i_code(datas->arene[process->PC + 1 % MEM_SIZE], 6, 1, 0)))
	{
		process->in_stock[3] = -1;
		return ;
	}
	vm_recup_all_process(process, datas->arene, 0);
	if (process->in_stock[3] != -1)
	{
		process->carry = 1;
		if (process->in_stock[1] > 0 && process->in_stock[1] < REG_NUMBER)
			process->reg[process->in_stock[1]] = process->in_stock[0];
	}
	process->in_stock[3] = vm_ocp_size(datas->arene[(process->PC + 1) % MEM_SIZE], 4, 0);
	if (process->in_stock[3] == 0)
		{process->in_stock[3] = 3;}
	process->PC = (process->PC + process->in_stock[3]) % MEM_SIZE;
*/
}
