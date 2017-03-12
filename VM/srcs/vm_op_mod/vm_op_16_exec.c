/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_16_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:22:29 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:22:30 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			vm_op_16_exec(t_datas *datas, t_process *process)
{
	(void)datas;
	if (process->in_stock[3] != -1)
		ft_putchar(process->in_stock[0] % (1 << 8));
	if (process->in_stock[3] <= 0)
		{process->in_stock[3] = 3;}
	process->PC = (process->PC + process->in_stock[3]) % MEM_SIZE;
}
