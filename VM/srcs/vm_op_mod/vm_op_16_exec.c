/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_16_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:22:29 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/22 23:52:30 by ntoniolo         ###   ########.fr       */
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
		process->in_stock[3] = -1;
		process->PC = (process->PC + 2) % MEM_SIZE;
		return ;
	}
/*	vm_recup_all_process(process, datas->arene, 0);
	if (process->in_stock[3] != -1 && (!(datas->flag & FLAG_D) || !(datas->flag & FLAG_N)))
		ft_putchar(process->in_stock[0] % (1 << 8));
	if (process->in_stock[3] <= 0)
		process->in_stock[3] = 3;*/
	process->PC = (process->PC + 3) % MEM_SIZE;
}
