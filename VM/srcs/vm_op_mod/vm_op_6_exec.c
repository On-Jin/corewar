/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_6_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:21:35 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:21:36 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			vm_op_6_exec(t_datas *datas, t_process *process)
{
	/*
	** executions
	*/
	process->in_stock[2] = process->in_stock[0] & process->in_stock[1];
	(void)datas;
	if (process->in_stock[3] != -1)
		process->carry = 1;
	process->in_stock[3] = vm_ocp_size(datas->arene->arene[(process->PC + 1) % MEM_SIZE], 4, 0);
	if (process->in_stock[3] == 0)
		{/*ft_printf("exec 6 jump de 0\n");*/}
	process->PC = (process->PC + process->in_stock[3]) % MEM_SIZE;
}
