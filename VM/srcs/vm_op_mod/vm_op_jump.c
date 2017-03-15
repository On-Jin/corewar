/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_jump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 16:11:19 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/15 15:23:27 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			vm_op_jump(t_datas *datas, t_process *process, unsigned char size)
{
	unsigned char		i;
	unsigned char		instruc;

	instruc = datas->arene[vm_add_valid(process->PC + 1)];
	i = 4 - size;
	while (i)
	{
		instruc >>= 2;
		--i;
	}
	while (instruc)
	{
		((instruc & 3) == 1) ? i += 1 : 0;
		((instruc & 3) == 2 && datas->op_tab[(int)process->instruction].nbr_octet_dir == 0) ? i += 4 : 0;
		((instruc & 3) == 2 && datas->op_tab[(int)process->instruction].nbr_octet_dir == 1) ? i += 2 : 0;
		((instruc & 3) == 3) ? i += 2 : 0;
		instruc >>= 2;
	}
	return (vm_add_valid(process->PC + 2 + i));
}
