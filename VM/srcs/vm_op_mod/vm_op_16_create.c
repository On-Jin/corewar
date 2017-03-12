/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_16_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:20:15 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:20:16 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			vm_op_16_create(t_datas *datas, t_process *process)
{
	process->cycle = 2;
	process->instruction = 16;
	if (!(vm_verif_i_code(datas->arene->arene[process->PC + 1 % MEM_SIZE], 1, 0, 0)))
	{
		process->in_stock[3] = -1;
		return ;
	}
	vm_recup_all_process(process, datas->arene, 0);
	/*
	**recuperation des information
	**traitement d'informations invalides?
	** recuperation du jump?
	*/
}
