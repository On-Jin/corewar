/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_1_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:21:10 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/17 19:36:01 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"


/*
** Questions par commande:
** Que fait la commande?
** De qui a t'elle besoin?
** que fait elle si ses instrictions sont eronnees ?
** que fait elle si son op_code_instruc est erronne ?
** carry ?
** jump?
** ;
*/

/*
** live recherche
** prends un paramettre, sur 4 octets
** lit live sur ce paramettre et inscrit live
** si 0 live durant le jeu le vainqueur est le dernier champion a arriver
** un processeur qui fait un live non valide reste en vie
** les lives non valides ne sont pas ajouter au decompte des lives totaux
** le prcesseur jump ensuite sur pc + 5
*/

/*
** Live
** faire un special pour live
** donc met +1 a nbr_live
** stoque live nbr du champion pour affichage;
** met param de live a 1
** met champ_live total a +1
** met champ live cycle a +1
*/

/*
** zork resultat du corear
** cycle 57955 manque 1 cycle
** lives
** valeurs de la ligne 0b 68 01 00 0f 00 01 06 64 01 00 00 00 00 01 01 ff ff ff ff 09 ff fb OK
**;
*/

void				vm_op_1_exec(t_datas *datas, t_process *process)
{
	int		arg1;
	int		arg2;

	arg1 = vm_recup_arena_num(4, datas->arene, process->PC + 1);
	arg2 = vm_champ_number_to_position(arg1, datas->begin_champ);
	process->live = 1;
	process->PC = vm_add_valid(process->PC + 5);
//	mvprintw(NC_DEBUG_Y + datas->i_debug++, NC_DEBUG_X, "champ == %x, position = %d    ",arg1, arg2);
	if (arg2 != -1)
	{
		datas->lives->total_lives++;
		datas->lives->cycle_lives++;
		datas->inf[arg2].total_lives++;
		datas->inf[arg2].cycle_lives++;
		datas->inf[arg2].cycle_last_live = datas->cycle.cycle + datas->cycle.total_cycle;
		datas->lives->champ_total_lives[arg2]++;
		datas->lives->champ_cycle_lives[arg2]++;
		datas->lives->last_live = arg1;
		datas->lives->cycle_last_live = datas->cycle.cycle + datas->cycle.total_cycle;
	}
}
