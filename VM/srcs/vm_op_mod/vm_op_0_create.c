/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_0_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:18:29 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:18:32 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				vm_op_0_create(t_datas *datas, t_process *process)
{
	(void)datas;
	process->instruction = 0;
	process->cycle = 1;
}
