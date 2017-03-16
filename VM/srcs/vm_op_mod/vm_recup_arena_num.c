/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_recup_arena_num.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:49:28 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/16 23:32:35 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			vm_recup_arena_num(int size, char *arene, int PC)
{
	int		i;
	int		res;

	i = 0;
	res = 0;
	while (i < size)
	{
		res <<= 8;
		res |= (unsigned char)arene[(PC + i) % MEM_SIZE];
		i++;
//			mvprintw(NC_DEBUG_Y + 22 + i, ft_gcd(MEM_SIZE) * 3 + 10/*NC_DEBUG_X*/, "else result = %d", res);
	}
//		mvprintw(NC_DEBUG_Y + 20, ft_gcd(MEM_SIZE) * 3 + 10/*NC_DEBUG_X*/, "else result = %d size = %d, pc  %d, %d, memsize %d", res,size,PC ,(size & 7), MEM_SIZE);
	if (size == 1 && (res >> 7) == 1)
		res |= 0xffffff00;
	if (size == 2 && (res >> 15) == 1)
		res |= 0xffff0000;
	if (size == 3 && (res >> 23) == 1)
		res |= 0xff000000;
	return (res);
}
