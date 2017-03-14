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
	/*	if (!(vm_verif_i_code(datas->arene[process->PC + 1 % MEM_SIZE], 1, 5, 0)))
			return ;
	*/	vm_recup_all_process(process, datas->arene, 0);
		/*
		** a changer
		*/
		process->in_stock[3] = vm_ocp_size(datas->arene[(process->PC + 1) % MEM_SIZE], 4, 0);
		process->in_stock[0] = vm_recup_arena_num(1, datas->arene, process->PC + 2);
	(void)datas;
	if (process->in_stock[0] > 0 && process->in_stock[0] < REG_NUMBER)
	{
		process->reg[process->in_stock[0]] = process->PC + (process->in_stock[1] % IDX_MOD);
		process->carry = 0;
	}
	process->PC = (process->PC + process->in_stock[3] + 1) % MEM_SIZE;

//process->carry = 0;
//process->PC = (process->PC + A_CHANGER) % MEM_SIZE;
}
