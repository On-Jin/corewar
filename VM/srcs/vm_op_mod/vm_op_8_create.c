/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_8_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:19:30 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:19:31 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"



void			vm_op_8_create(t_datas *datas, t_process *process)
{
	process->cycle = 6;
	process->instruction = 8;

	/*
	**recuperation des information
	**traitement d'informations invalides?
	** recuperation du jump?
	*/
}
