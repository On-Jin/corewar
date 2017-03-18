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
	(void)process;
	process->in_stock[0] = vm_recup_arena_num(4, datas->arene, process->PC + 1);
	process->in_stock[1] = vm_champ_number_to_position(process->in_stock[0], datas->begin_champ);
}
