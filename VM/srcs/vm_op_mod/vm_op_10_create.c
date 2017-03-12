/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_10_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:19:42 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:19:43 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			vm_op_10_create(t_datas *datas, t_process *process)
{
		(void)datas;
	process->cycle = 1;
	process->instruction = 10;
	if (!(vm_verif_i_code(datas->arene->arene[process->PC + 1 % MEM_SIZE], 7, 3, 1)))
	{
		process->in_stock[3] = -1;
		return ;
	}
	vm_recup_all_process(process, datas->arene, (1 << 8) | (1 << 17) | (1 << 25));
	/*
	**recuperation des information
	**traitement d'informations invalides?
	** recuperation du jump?
	*/
}
