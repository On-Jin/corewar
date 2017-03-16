/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_15_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:22:23 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:22:24 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			vm_op_15_exec(t_datas *datas, t_process *process)
{
	vm_copy_process(datas, process, vm_add_valid(process->PC +
		vm_recup_arena_num(2, datas->arene, process->PC + 1) % IDX_MOD));
	process->PC = vm_add_valid(process->PC + 3);
}
