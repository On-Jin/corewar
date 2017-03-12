/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_7_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:19:22 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:19:25 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			vm_op_7_create(t_datas *datas, t_process *process)
{
	process->cycle = 6;
	process->instruction = 7;

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
