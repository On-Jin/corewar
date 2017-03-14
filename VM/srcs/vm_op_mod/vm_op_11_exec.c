/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_11_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:22:02 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/13 19:21:30 by ntoniolo         ###   ########.fr       */
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
** si le repertoire n'existe pas, ne rien faire
** n'ecrit pas
*/


void			vm_op_11_exec(t_datas *datas, t_process *process)
{
	/*
	** executions
	*/
	if (!(vm_verif_i_code(datas->arene[process->PC + 1 % MEM_SIZE], 1, 7, 3)))
	{
		process->in_stock[3] = -1;
		return ;
	}
	vm_recup_all_process(process, datas->arene, 1 << 9 | 1 << 17);
	if (process->in_stock[3] == -1)
		process->in_stock[3] = 0;
	else
	{
		mvprintw(NC_DEBUG_Y + datas->i_debug++, NC_DEBUG_X, "hello adresse dansl'arene %i valeur de l'adresse %i, valeur de remplacement %i\n", (process->PC + (process->in_stock[1] + process->in_stock[2]) % IDX_MOD) % MEM_SIZE, *(int *)(&datas->arene[(process->PC + (process->in_stock[1] + process->in_stock[2]) % IDX_MOD) % MEM_SIZE]), process->in_stock[0]);
	}
		process->in_stock[3] = vm_ocp_size(datas->arene[(process->PC + 1) % MEM_SIZE], 4, 0);
	if (process->in_stock[3] == 0)
		{/*ft_printf("exec 11 jump de 0\n");*/process->in_stock[3] = 3;}
	process->PC = (process->PC + process->in_stock[3]) % MEM_SIZE;
}
