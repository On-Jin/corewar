/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_9_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:21:51 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:21:52 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			vm_op_9_exec(t_datas *datas, t_process *process)
{
	/*
	** executions
	*/
	(void)datas;
	process->carry = 0;
	if (!process->in_stock[0])
		process->in_stock[0]++;
	process->PC = (process->PC + process->in_stock[0]) % MEM_SIZE;
}
