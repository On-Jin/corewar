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

/*
** Flag :
** 0b1 : recupere le numero du registre plutot que sa valeur
** 0b10 : prends un direct de 2 plutot qu'un direct de 4
** 0b100 : recupere le nombre indirect et non sa valeur
** 0b1000 :
** 0b10000 :
** 0b100000 :
** 0b1000000 :
** 0b10000000 :
*/

int			vm_recup_all_process(t_process *process, char *arene, int flg)
{
	int			tmp;
	int			flag;
	int			i;
	int			adress;

	i = 0;
	tmp = (arene[vm_add_valid(process->PC + 1)]) >> 6;
	flag = flg >> 24;
	adress = process->PC + 2;
	while (i < 4)
	{
		if ((tmp & 3) == 0b01)
		{
			if (!(flag & 1))
			{
				if ((process->in_stock[i] = vm_recup_arena_num(1, arene, adress)) == -1)
					return (-1);
			}
			else if ((vm_recup_process_reg(process, arene, adress, &process->in_stock[i])) == -1)
				return (-1);
			adress += 1;
		}
		else if ((tmp & 3) == 0b10 && flag & 0b10)
		{
			process->in_stock[i] = vm_recup_arena_num(2, arene, adress);
			adress += 2;
		}
		else if ((tmp & 3) == 0b10)
		{
			process->in_stock[i] = vm_recup_arena_num(4, arene, adress);
			adress += 4;
		}
		else if ((tmp & 3) == 0b11 && flag & 0b100)
		{
			process->in_stock[i] = vm_recup_arena_num(2, arene, adress);
			adress += 2;
		}
		else if ((tmp & 3) == 0b11)
		{
			process->in_stock[i] = vm_recup_indirect_num(process, arene, adress);
			adress += 2;
		}
		i++;
		flag = flg >> (8 * (3 - i));
		tmp = (char)arene[vm_add_valid(process->PC + 1)] >> (2 * (3 - i));
	}
	return (0);
}
