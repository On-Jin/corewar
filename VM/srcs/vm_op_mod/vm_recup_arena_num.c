/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_recup_arena_num.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:49:28 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/14 12:47:12 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			vm_recup_arena_num(int size, char *arena, int PC)
{
	int		i;
	int		res;

	i = 0;
	res = 0;
	if (PC + size < MEM_SIZE && (size & 7) == 1)
	{
		if (size == 4)
			return (res = *(unsigned int *)(&arene[PC]));
		if (size == 2)
			return (res = *(unsigned short *)(&arene[PC]));
		if (size == 1)
			return (res = *(unsigned char *)(&arene[PC]));
	}
	else
		while (i < size)
		{
			res = res * 0x100;
			res += (arene[(PC + (i % IDX_MOD)) % MEM_SIZE]);
			i++;
		}
	return (res);
}
