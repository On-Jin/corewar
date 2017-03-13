/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_5_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:19:08 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:19:09 by gnebie           ###   ########.fr       */
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

void			vm_op_5_create(t_datas *datas, t_process *process)
{
	unsigned int tmp;

	(void)datas;
	process->cycle = 10;
	process->instruction = 5;
	tmp = (datas->arene->arene[(process->PC + 1) % MEM_SIZE]);
	if (tmp <= REG_NUMBER)
		process->in_stock[0] = process->reg[tmp];
	else
		process->in_stock[3] = -1;
	tmp = (datas->arene->arene[(process->PC + 2) % MEM_SIZE]);
	if (tmp <= REG_NUMBER)
		process->in_stock[1] = process->reg[tmp];
	else
		process->in_stock[3] = -1;
	process->in_stock[2] = datas->arene->arene[(process->PC + 3) % MEM_SIZE];
	if (process->in_stock[2] > REG_NUMBER || process->in_stock[2] < 0)
		process->in_stock[3] = -1;
	/*
	**recuperation des information
	**traitement d'informations invalides?
	** recuperation du jump?
	*/
}
