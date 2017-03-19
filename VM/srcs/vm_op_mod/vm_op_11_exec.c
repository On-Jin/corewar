/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_11_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:22:02 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/13 19:21:30 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** si le repertoire n'existe pas, ne rien faire
** n'ecrit pas
*/

void			vm_op_11_exec(t_datas *datas, t_process *process)
{
	char		i;

	i = datas->arene[vm_add_valid(process->PC + 1)];
	if (vm_verif_datas(datas, process))
	{
		vm_recup_all_process(process, datas->arene, 1 << 24 | 1 << 17 | 1 << 9 | 1 << 8);
//		ft_printf("process->in_stock[0] = %d, process->in_stock[1] = %d, process->in_stock[2] = %d", process->in_stock[0], process->in_stock[1], process->in_stock[2]);
//		sleep(10);
		vm_put_nbr_in_arene(process->in_stock[0], vm_add_valid(process->PC +
			((process->in_stock[1] + process->in_stock[2]) % IDX_MOD)),
			datas->arene, 4);
	}
	else if (datas->op_tab[(int)process->instruction].mod_carry)
		process->carry = 0;
	process->PC = vm_op_jump(datas, process,
							datas->op_tab[(int)process->instruction].nb_arg);
	process->in_stock[0] = 0;
	process->in_stock[1] = 0;
	process->in_stock[2] = 0;
	process->in_stock[3] = 0;
}
