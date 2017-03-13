/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_6_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:19:15 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:19:16 by gnebie           ###   ########.fr       */
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

void			vm_op_6_create(t_datas *datas, t_process *process)
{
	int i;

	i = 0;
	(void)datas;
	process->cycle = 6;
	process->instruction = 6;
	if (!(vm_verif_i_code(datas->arene->arene[process->PC + 1 % MEM_SIZE], 7, 7, 1)))
	{
		process->in_stock[3] = -1;
		return ;
	}
	vm_recup_all_process(process, datas->arene, 1 << 8);

		/*
	**recuperation des information
	**traitement d'informations invalides?
	** recuperation du jump?
	*/
}
