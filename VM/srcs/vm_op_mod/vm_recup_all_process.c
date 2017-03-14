/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_recup_all_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:50:32 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/14 12:50:14 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			*vm_recup_all_process(t_process *process, char *arene, int flag)
{
	int			tmp;
	int			i;
	int			adress;

	i = 3;
	tmp = (arene[(process->PC + 1) % MEM_SIZE]);
	adress = process->PC + 2;
	while (tmp && i > -1)
	{
		if ((tmp & 0xff) == 0b01)
		{
			if ((flag & 0xff) == 1)
				process->in_stock[i] = vm_recup_arena_num(1, arene, adress);
			else
				process->in_stock[i] = vm_recup_process_reg(process, arene, adress);
			adress += 1;
		}
		else if ((tmp & 0xff) == 0b10 && flag & 0b10)
		{
			process->in_stock[i] = vm_recup_arena_num(2, arene, adress);
			adress += 2;
		}
		else if ((tmp & 0xff) == 0b10)
		{
			process->in_stock[i] = vm_recup_arena_num(4, arene, adress);
			adress += 4;
		}
		else if ((tmp & 0xff) == 0b11)
		{
			process->in_stock[i] = vm_recup_indirect_num(process, arene, adress);
			adress += 2;//T_IND;//??? bizzare dir et ind semblent inversees
		}
		--i;
		flag >>= 8;
		tmp = tmp >> 2;
	}
	return (process->in_stock);
}
