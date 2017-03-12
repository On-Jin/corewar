/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VM_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 04:00:52 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/10 23:19:23 by ntoniolo         ###   ########.fr       */
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

/*
WINDOW *create_newwin(int height, int width, int starty, int startx)
{
	WINDOW *local_win;
	local_win = newwin(height, width, starty, startx);
	wrefresh(local_win);
	return local_win;
}
*/

void		vm_verif_arg(int argc)
{
	if (argc == 1)
		exit (ft_int_error("Usage : corewar [champ]"));

}

void	vm_init_color(void)
{
	initscr();
	start_color();
	init_pair(0, COLOR_RED, COLOR_BLACK);
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
//	datas.win = create_newwin(64 + 2, 64 * 3 + 4, 0, 0);
	noecho();
}

int		vm_end_main(void)
{
	endwin();
	exit(0);
	return (0);
}


int			main(int argc, char **argv)
{
	t_vm		arene;
	t_lives		lives;
	t_champ		champs[MAX_PLAYERS + 1];
	t_datas		datas;

	vm_verif_arg(argc);
	vm_init_color();
	vm_verif_macro();
	vm_innit_to_0(&datas, champs, &arene, &lives);
	vm_champ_process(&datas, argc, argv);
	vm_init_process(&datas);
	return (vm_end_main());
}
