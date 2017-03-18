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
	(void)process;
	if (vm_verif_datas(datas, process))
	{
		vm_recup_all_process(process, datas->arene, 1 << 24);
		if (process->in_stock[1] > 0 && process->in_stock[1] <= REG_NUMBER)
		{
			process->carry = 1;
		}
		else
			process->carry = 0;
	}
	else if (datas->op_tab[(int)process->instruction].mod_carry)
		process->carry = 0;
}
