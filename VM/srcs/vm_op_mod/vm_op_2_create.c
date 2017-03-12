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

/*
** Ld
** Prend un paramètre quelconque et un registre.
** Charge la valeur du premier paramètre dans le registre.
**  il changera le carry.
*/

void			vm_op_2_create(t_datas *datas, t_process *process)
{
	int		tmp;

	(void)datas;
	process->cycle = 5;
	process->instruction = 2;
	tmp = datas->arene->arene[(process->PC + 1) % MEM_SIZE] >> 6;
/*	if ((tmp & 0xff) == 0b01)
		process->in_stock[0] = vm_recup_process_reg(process, datas->arene, process->PC + 2);
*/	if ((tmp & 0x3) == 0b10)
	{
		process->in_stock[0] = vm_recup_arena_num(4, datas->arene, process->PC + 2);
		tmp = 4;
	}
	else if ((tmp & 0x3) == 0b11)
	{
		process->in_stock[0] = vm_recup_indirect_num(process, datas->arene, process->PC + 2);
		tmp = 2;
	}
/*	else
		ft_printf("fuck %i\n\n", datas->arene->arene[(process->PC + 1) % MEM_SIZE]);
*/	process->in_stock[2] = vm_ocp_size(datas->arene->arene[(process->PC + 1) % MEM_SIZE], 4, 0);
	process->in_stock[1] = vm_recup_arena_num(1, datas->arene, (process->PC + 2 + tmp) % MEM_SIZE);
}
