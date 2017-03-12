/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_champ_number_to_position.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:48:31 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:48:34 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				vm_champ_number_to_position(int champ_num, t_champ *champ_tab)
{
	int			i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (champ_num == champ_tab[i].champ_position)
			return (i);
		++i;
	}
	return (-1);
}
