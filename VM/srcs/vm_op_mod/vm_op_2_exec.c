/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_2_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:21:16 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:21:17 by gnebie           ###   ########.fr       */
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
** ld recherche
** write the value of the first parameter in the second parameter(a register)2
** parameters T_DIR | T_IND, T_REG
** carry si carry = 1 passe le carry a 0
** si son op_code_instruc est erronne jump de 2
** lit le nombre de paramettres de l'octets d'encodage et jump de la taille de
** ses paramettes (exemple si 101010 et que deux paramettres jump de 1 + 2 * 4)
** ne check pas si les paramettes sont valides pour la fonction
** si repertory non valide ne fait rien / prends 0 a la place
** lit les insturctions a la fin de son cycle
*/

/*
** Ld
** Prend un paramètre quelconque et un registre.
** Charge la valeur du premier paramètre dans le registre.
**  il changera le carry.
*/

/*
process->instruction = -1;
if (vm_verif_i_code())
{
		vm_recup_all_process(process, datas->arene, 0);
		execute...;
		carry = ?;
}
process->PC = vm_op_jump(datas, process, 2);

*/

/*
** 1 modifier process(live) et instruction
** 2 verification de la validite de la demande
** 2.1 recuperation des valeurs necessaires;
** 2.2 execution de la fonction;
** 2.3 modification du carry;
** 3 jump sur le prochain process (fixe ou pc + vm_op_jump(op, nbr))
*/

void			vm_op_2_exec(t_datas *datas, t_process *process)
{
	if (vm_verif_datas(datas, process))
	{
//		mvprintw(NC_DEBUG_Y + datas->i_debug++, NC_DEBUG_X, "je suis la");
		vm_recup_all_process(process, datas->arene, 1 << 24);
//		mvprintw(NC_DEBUG_Y + datas->i_debug++, NC_DEBUG_X, "process_in_stock[%d][%d]",process->in_stock[0], process->in_stock[1] );
		if (process->in_stock[1] > 0 && process->in_stock[1] <= REG_NUMBER)
		{
			process->reg[process->in_stock[1]] = process->in_stock[0];
			process->carry = 1;
		}
	}
	else if (datas->op_tab[(int)process->instruction].mod_carry)
		process->carry = 0;
	process->PC = vm_op_jump(datas, process,
							datas->op_tab[(int)process->instruction].nb_arg);
	process->in_stock[0] = 0;
	process->in_stock[1] = 1;
}
