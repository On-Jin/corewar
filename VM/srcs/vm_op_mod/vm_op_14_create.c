/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_14_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:20:04 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:20:05 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			vm_op_14_create(t_datas *datas, t_process *process)
{
	process->cycle = 50;
	process->instruction = 14;
	if (!(vm_verif_i_code(datas->arene->arene[process->PC + 1 % MEM_SIZE], 1, 7, 3)))
	{
		process->in_stock[3] = -1;
		return ;
	}
	vm_recup_all_process(process, datas->arene, 1 << 9 | 1 << 17);
	/*
	**recuperation des information
	**traitement d'informations invalides?
	** recuperation du jump?
	*/
}
