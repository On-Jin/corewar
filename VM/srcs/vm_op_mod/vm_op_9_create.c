/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_9_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:19:35 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:19:36 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			vm_op_9_create(t_datas *datas, t_process *process)
{
		(void)datas;
	process->cycle = 20;
	process->instruction = 9;
	process->in_stock[0]= vm_recup_indirect_num(process, datas->arene, process->PC + 1);
	/*
	**recuperation des information
	**traitement d'informations invalides?
	** recuperation du jump?
	*/
}
