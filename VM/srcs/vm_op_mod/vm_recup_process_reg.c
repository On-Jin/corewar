/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_recup_process_reg.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:50:15 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/14 12:50:46 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				vm_recup_process_reg(t_process *process, char *arene, int adresse)
{
	unsigned int		reg;
	int					val;

	reg = vm_recup_arena_num(1, arene, adresse) + 1;
	if (reg <= REG_NUMBER)
	{
		val = process->reg[reg];
		val = val >> (4 * 8 - REG_SIZE * 8);
		return (val);
	}
	return (0);
}
