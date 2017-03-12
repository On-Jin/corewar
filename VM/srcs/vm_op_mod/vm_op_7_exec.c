/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_7_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:21:40 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:21:41 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			vm_op_7_exec(t_datas *datas, t_process *process)
{
	process->in_stock[2] = process->in_stock[0] | process->in_stock[1];
	if (process->in_stock[3] != -1)
		process->carry = 1;
	process->in_stock[3] = vm_ocp_size(datas->arene->arene[(process->PC + 1) % MEM_SIZE], 4, 0);
	if (process->in_stock[3] == 0)
		{/*ft_printf("exec 7 jump de 0\n");*/ process->in_stock[3] += 3;}
	process->PC = (process->PC + process->in_stock[3]) % MEM_SIZE;
}
