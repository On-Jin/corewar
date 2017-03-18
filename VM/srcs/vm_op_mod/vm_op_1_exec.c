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

void				vm_op_1_exec(t_datas *datas, t_process *process)
{

	process->live = 1;
	process->PC = vm_add_valid(process->PC + 5);
//	mvprintw(NC_DEBUG_Y + datas->i_debug++, NC_DEBUG_X, "champ == %x, position = %d    ",process->in_stock[0], process->in_stock[1]);
	if (process->in_stock[1] != -1)
	{
		datas->lives->total_lives++;
		datas->lives->cycle_lives++;
		datas->inf[process->in_stock[1]].total_lives++;
		datas->inf[process->in_stock[1]].cycle_lives++;
		datas->inf[process->in_stock[1]].cycle_last_live = datas->cycle.cycle + datas->cycle.total_cycle;
		datas->lives->champ_total_lives[process->in_stock[1]]++;
		datas->lives->champ_cycle_lives[process->in_stock[1]]++;
		datas->lives->last_live = process->in_stock[0];
		datas->lives->cycle_last_live = datas->cycle.cycle + datas->cycle.total_cycle;
	}
}
