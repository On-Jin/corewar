/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_2_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:18:44 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:18:45 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"



void			vm_op_2_create(t_datas *datas, t_process *process)
{


	(void)datas;
	process->cycle = 5;
	process->instruction = 2;
}
