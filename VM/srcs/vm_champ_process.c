/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_champ_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:03:12 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:03:13 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		vm_place_champ(t_datas *data, t_vm *arene, t_champ champ[MAX_PLAYERS + 1])
{
	int i;
	int size;

	i = 0;
	size = 0;
	while (i < data->player_nbr)
	{
		size += champ[i].champ_size;
		i++;
	}
	i = 0;
	while (i < data->player_nbr)
	{
		ft_memcpy((void *)&arene->arene[(i) *
					(MEM_SIZE / data->player_nbr)], (void *)&champ[i],
					(size_t)champ[i].champ_size);
		data->start[i] = i * (MEM_SIZE / data->player_nbr);
		if (champ || arene)
			;
		i++;
	}
}

void		vm_champ_process(t_datas *datas, int argc, char **argv)
{
	int i;

	i = 0;
	datas->player_nbr = vm_create_flags(argv, argc, &datas->flag);
	datas->player_nbr = vm_init_champ(datas->begin_champ, argc, argv, datas);
	vm_place_champ(datas, datas->arene, datas->begin_champ);
	while (i < datas->player_nbr)
	{
		datas->size_champ[i] = datas->begin_champ->champ_size;
		i++;
	}
}
