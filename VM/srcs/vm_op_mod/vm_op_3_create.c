/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_3_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:18:50 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:18:51 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"



void			vm_op_3_create(t_datas *datas, t_process *process)
{
	(void)datas;
	(void)process;

	process->in_stock[3] = datas->arene[vm_add_valid(process->PC + 1)];
	if (vm_verif_datas(datas, process))
		vm_recup_all_process(process, datas->arene, 1 << 24 | 1 << 18);
	else if (datas->op_tab[(int)process->instruction].mod_carry)
		process->carry = 0;
	else
		process->in_stock[3] = 1;
}
