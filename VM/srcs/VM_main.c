/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VM_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 04:00:52 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/23 14:16:47 by gnebie           ###   ########.fr       */
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
** faire une condition dans init_champ
** pour renvoyer erreur si champ > MAX_PLAYERS
*/

static void		vm_verif_arg(int argc)
{
	if (argc == 1)
		exit(ft_int_error("Usage : corewar [champ]"));
}

static int		vm_end_main(void)
{
	return (0);
}

static void		recup_data_size_arena(t_datas *datas)
{
	datas->nc.size_max_y = (ft_gcd(MEM_SIZE) + 2);
	datas->nc.size_max_x = (ft_gcd(MEM_SIZE) * 3 + 2);
}

int				main(int argc, char **argv)
{
	t_lives		lives;
	t_champ		champs[MAX_PLAYERS + 1];
	t_datas		datas;

	vm_verif_arg(argc);
	vm_verif_macro();
	vm_innit_to_0(&datas, champs, &lives);
	vm_champ_process(&datas, argc, argv);
	recup_data_size_arena(&datas);
	if (datas.flag & FLAG_N)
		ncurses_init(&datas, datas.nc.size_max_y, datas.nc.size_max_x + 1);
	vm_init_process(&datas);
	if (datas.flag & FLAG_N)
		ncurses_end(&datas);
	return (vm_end_main());
}
