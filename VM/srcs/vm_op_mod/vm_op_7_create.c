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
		(void)datas;
	process->cycle = 6;
	process->instruction = 7;


	/*
	**recuperation des information
	**traitement d'informations invalides?
	** recuperation du jump?
	*/
}
