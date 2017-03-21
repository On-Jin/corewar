/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_11_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:22:02 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/20 16:45:21 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** sti
** si le repertoire n'existe pas, ne rien faire
** n'ecrit pas
*/

void			vm_op_11_exec(t_datas *datas, t_process *process)
{
	char		i;
	unsigned int			instruc;

	instruc = (unsigned char)datas->arene[vm_add_valid(process->PC + 1)];
	i = datas->arene[vm_add_valid(process->PC + 1)];
	if (vm_verif_datas(datas, process))
	{
		if (!vm_recup_all_process(process, datas->arene, 1 << 24 | 1 << 17 | 1 << 16 | 1 << 9 |  1 << 8 ))
		{
			vm_put_nbr_in_arene(process->in_stock[0], vm_add_valid(process->PC +
				((process->in_stock[1] + process->in_stock[2]) % IDX_MOD)),
				datas->arene, 4);
			ncurses_put_background(datas, vm_add_valid(process->PC +
				((process->in_stock[1] + process->in_stock[2]) % IDX_MOD)), process->champion, 4);
		}
//		ft_printf("process->in_stock[0] = %d, process->in_stock[1] = %d, process->in_stock[2] = %d", process->in_stock[0], process->in_stock[1], process->in_stock[2]);
//		sleep(10);
	}
	else if (datas->op_tab[(int)process->instruction].mod_carry)
		process->carry = 0;
	process->PC = vm_op_jump(datas, process, instruc,
							datas->op_tab[(int)process->instruction].nb_arg);
	process->in_stock[0] = 0;
	process->in_stock[1] = 0;
	process->in_stock[2] = 0;
	process->in_stock[3] = 0;
}
