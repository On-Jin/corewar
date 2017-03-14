/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_innit_to_0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 05:12:17 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/13 19:12:19 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** A changer :
** Utiliser unn flag FLAG_D plutot que i_debug
** mettre en char *datas->arene
*/

void		vm_innit_to_0(t_datas *datas, t_champ *champs, t_vm *arene,
						t_lives *lives)
{
	ft_bzero((void *)datas, MEM_SIZE);
	ft_bzero((void *)champs, sizeof(t_champ) * (MAX_PLAYERS + 1));
	ft_bzero((void *)lives, sizeof(t_lives));
	ft_bzero((void *)arene->arene, MEM_SIZE);
	datas->lives = lives;
	datas->begin_champ = champs;
	datas->arene = arene;
	datas->nbr_cycles = CYCLE_TO_DIE;
	datas->key = NC_PAUSE;
	datas->cur_pros = 0;
	datas->nbr_process = 0;
	datas->i_debug = 0;
}
