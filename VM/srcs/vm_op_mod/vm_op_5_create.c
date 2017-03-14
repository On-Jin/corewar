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



void			vm_op_5_create(t_datas *datas, t_process *process)
{
	unsigned int tmp;

	(void)datas;
	process->cycle = 10;
	process->instruction = 5;

	/*
	**recuperation des information
	**traitement d'informations invalides?
	** recuperation du jump?
	*/
}
