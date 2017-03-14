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
		(void)datas;
	process->cycle = 2;
	process->instruction = 16;

	/*
	**recuperation des information
	**traitement d'informations invalides?
	** recuperation du jump?
	*/
}
