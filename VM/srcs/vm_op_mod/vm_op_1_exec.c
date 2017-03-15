/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_1_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:21:10 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/15 19:35:38 by ntoniolo         ###   ########.fr       */
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
	int		arg1;
	int		arg2;

	arg1 = vm_recup_arena_num(4, datas->arene, process->PC + 1);
	arg2 = vm_champ_number_to_position(arg1, datas->begin_champ);
	process->live = 1;
	process->PC = vm_add_valid(process->PC + 5);
	if (process->in_stock[1] != -1)
	{
		datas->lives->total_lives += 1;
		datas->lives->cycle_lives++;
		datas->lives->champ_total_lives[arg2]++;
		datas->lives->champ_cycle_lives[arg2]++;
		datas->lives->last_live = arg1;
	}
}
