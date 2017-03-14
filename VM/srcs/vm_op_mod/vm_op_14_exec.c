/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_14_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:22:16 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:22:17 by gnebie           ###   ########.fr       */
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

void			vm_op_14_exec(t_datas *datas, t_process *process)
{
	if (!(vm_verif_i_code(datas->arene[process->PC + 1 % MEM_SIZE], 1, 7, 3)))
	{
		process->in_stock[3] = -1;
		return ;
	}
	vm_recup_all_process(process, datas->arene, 1 << 9 | 1 << 17);
	if (process->in_stock[3] == -1 || !process->in_stock[2])
		process->in_stock[3] = 0;
	else
		datas->arene[(process->PC + (process->in_stock[1] + process->in_stock[2])) % MEM_SIZE] = process->in_stock[0];
	process->in_stock[3] = vm_ocp_size(datas->arene[(process->PC + 1) % MEM_SIZE], 4, 0);
	if (process->in_stock[3] == 0)
		{/*ft_printf("exec 11 jump de 0\n");*/process->in_stock[3] = 3;}
	process->PC = (process->PC + process->in_stock[3]) % MEM_SIZE;
}
