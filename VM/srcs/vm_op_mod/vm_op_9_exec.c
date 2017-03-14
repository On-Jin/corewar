/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_9_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:21:51 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:21:52 by gnebie           ###   ########.fr       */
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

void			vm_op_9_exec(t_datas *datas, t_process *process)
{
		process->in_stock[0]= vm_recup_indirect_num(process, datas->arene, process->PC + 1);
	/*
	** executions
	*/
	(void)datas;
	process->carry = 0;
	if (!process->in_stock[0])
		process->in_stock[0]++;
	process->PC = (process->PC + process->in_stock[0]) % MEM_SIZE;
}
