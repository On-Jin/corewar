/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_recup_indirect_num.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:49:56 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/22 19:42:35 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** ajouter le process?
*/

int				vm_recup_indirect_num(t_process *process, char *arene,
																	int adresse)
{
	unsigned int		ind_adress;
	int					val;

	ind_adress = (vm_recup_arena_num(2, arene, adresse));
	if (process->instruction < 13 || process->instruction > 15)
		ind_adress = ind_adress % IDX_MOD;
	ind_adress = vm_add_valid(ind_adress + process->PC);
	val = vm_recup_arena_num(4, arene, ind_adress);
//	mvprintw(21, 64*3+85, "Val recup IND : %i", val);
//	val = val >> (4 * 8 - IND_SIZE * 8);
//	mvprintw(22, 64*3+85, "Val afterchange : %i", val);
	return (val);
}
