/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_1_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:18:37 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:18:38 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"


void				vm_op_1_create(t_datas *datas, t_process *process)
{
	(void)datas;
	process->cycle = 10;
	process->instruction = 1;
}
