/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VM_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 04:00:52 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/06 05:21:33 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** etape 1 recuperer et verifier les champions
** etape 2 initialisation de la machine virtuelle
** (alloctaion de l'espace memoire, mise a 0 des process)
** etape 3 pose des champions sur la memoire
** etape 4 run de la machine jusqu'a la fin (lecture des donnes des champions)
** etape 5 fin de la machine, affichage du champion
*/

void		vm_innit_to_0(t_champ *champs, t_vm *arene, int champs_size)
{
	ft_bzero((void *)champs, champs_size);
	ft_bzero((void *)arene->arene, MEM_SIZE);
}

int			main(int argc, char **argv)
{
	int			i;
	t_champ		champs[MAX_PLAYERS + 1];
	t_vm		arene;
	t_datas		datas;

	i = 0;
	datas.player_nbr = vm_create_flags(argv, argc, &datas.flag);
	vm_innit_to_0(champs, &arene, sizeof(champs));
	datas.player_nbr = vm_init_champ(champs, argc, argv, &datas);
	ft_printf("champ_size %d, champ nbr %d\n", champs[0].champ_size, champs[0].champ_nbr);
	ft_memcpy((void *)&arene, (void *)&champs[0], CHAMP_MAX_SIZE);
	vm_show_arene(&arene);
//	vm_pose_champ();
//	vm_do_cycles();
	exit(0);
	return (0);
}
