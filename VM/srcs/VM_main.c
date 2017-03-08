/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VM_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 04:00:52 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/08 16:57:48 by ntoniolo         ###   ########.fr       */
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

/*
** char code_instruction;
** char parm_format;
** char parm[REG_SIZE * 4]
*/

/*
** un op de la table
** 1 => nom du paramettre
** 2 => nombre d'arguments
** 3 => arguments acceptees(lien avec le nombre d'arguments)
** 4 => numero op_code
** 5 => nombre de cycles pour realiser l'instruction
** 6 => ?retour/affichage?
** 7 => carry(0 | 1)
** 8 => ?si 1 alors les valeurs direct sont sur 2 octets?
*/

/*
** A faire : define error
** pour verifier que les macros sont valides;
*/

void		place_champ(t_datas *data, t_vm *arene, t_champ champ[MAX_PLAYERS + 1])
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
	i = 1;
	while (i <= data->player_nbr)
	{
		ft_printf("Try Place %i\n", i);
		ft_memcpy((void *)&arene->arene[0/*Place du chmapion*/], (void *)&champ[i - 1], champ[i - 1].champ_size);
		ft_printf("End Place %i\n", i);
		if (champ || arene)
			;
		i++;
	}
}

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
//	ft_memcpy((void *)&arene, (void *)&champs[0], champs[0].champ_size);
	place_champ(&datas, &arene, champs);
	vm_show_arene(&arene);
//	vm_pose_champ();
//	vm_do_cycles();
	exit(0);
	return (0);
}
