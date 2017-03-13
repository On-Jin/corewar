/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VM_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 04:00:52 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/13 13:09:02 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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
** le numero du champion ne peut pas etre 0;
** faire une fonction Usage
** faire une condition dans init_champ pour renvoyer erreur si champ > MAX_PLAYERS
*/

void		vm_verif_arg(int argc)
{
	if (argc == 1)
		exit (ft_int_error("Usage : corewar [champ]"));

}

int		vm_end_main(void)
{
	exit(0);
	return (0);
}

static void	recup_size_champ(t_datas *datas, t_champ champs[MAX_PLAYERS + 1])
{
	int i;

	i = 0;
	while (i < datas->player_nbr)
	{
		datas->size_champ[i] = champs[i].champ_size;
		dprintf(2, "%i\n", datas->size_champ[i]);
		i++;
	}
}

int			main(int argc, char **argv)
{
	t_vm		arene;
	t_lives		lives;
	t_champ		champs[MAX_PLAYERS + 1];
	t_datas		datas;

	vm_verif_arg(argc);
	vm_verif_macro();
	vm_innit_to_0(&datas, champs, &arene, &lives);
	vm_champ_process(&datas, argc, argv);
	recup_size_champ(&datas, champs);
	ncurses_init(&datas, SIZE_MAX_Y, SIZE_MAX_X);
	vm_init_process(&datas);
	ncurses_end(&datas);
	return (vm_end_main());
}
