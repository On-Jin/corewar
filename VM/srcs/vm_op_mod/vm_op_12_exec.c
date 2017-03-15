/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_12_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:22:07 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/15 18:18:03 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Questions par commande:
** Que fait la commande?
** De qui a t'elle besoin?
** que fait elle si ses instrictions sont eronnees ?
** que fait elle si son op_code_instruc est erronne ?
** carry ?
** jump?
** ;
*/

/*
** Fork
*/

void			vm_op_12_exec(t_datas *datas, t_process *process)
{
	vm_copy_process(datas, process, vm_add_valid(process->PC + (char)vm_recup_arena_num(2, datas->arene, process->PC + 1) % IDX_MOD));
	process->PC = vm_add_valid(process->PC + 3);
}
