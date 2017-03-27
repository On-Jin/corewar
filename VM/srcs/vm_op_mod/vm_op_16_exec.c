/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_16_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:22:29 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/27 17:45:11 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** a finir ?
*/

void			vm_op_16_exec(t_datas *datas, t_process *process)
{
	if (!(vm_verif_datas(datas, process)))
	{
		if (!(datas->flag & FLAG_H) && !(datas->flag & FLAG_DUMP))
			ft_printf("aff [%2c](value %0#.2hhx)\n", vm_recup_arena_num(1,
				datas->arene, vm_add_valid(process->pc + 2)),
				vm_recup_arena_num(1, datas->arene,
				vm_add_valid(process->pc + 2)));
	}
	process->pc = vm_op_jump(datas, process,
							datas->op_tab[(int)process->instruction].nb_arg);
}
