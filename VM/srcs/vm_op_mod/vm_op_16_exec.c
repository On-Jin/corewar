/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_16_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:22:29 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/27 02:29:08 by ntoniolo         ###   ########.fr       */
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
			ft_putchar(vm_add_valid(datas->arene[process->PC + 2]));
	}
	process->PC = vm_op_jump(datas, process,
							datas->op_tab[(int)process->instruction].nb_arg);
}
