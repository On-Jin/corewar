/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_4_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:19:00 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:19:01 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			vm_op_4_create(t_datas *datas, t_process *process)
{
	unsigned int tmp;

	(void)datas;
	process->cycle = 10;
	process->instruction = 4;

	/*
	**recuperation des information
	**traitement d'informations invalides?
	** recuperation du jump?
	*/
}
