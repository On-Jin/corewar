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

void			vm_op_2_exec(t_datas *datas, t_process *process)
{
	(void)datas;
	int		tmp;

	tmp = datas->arene[(process->PC + 1) % MEM_SIZE] >> 6;
	if ((tmp & 0x3) == 0b10)
	{
		process->in_stock[0] = vm_recup_arena_num(4, datas->arene, process->PC + 2);
		tmp = 4;
	}
	else if ((tmp & 0x3) == 0b11)
	{
		process->in_stock[0] = vm_recup_indirect_num(process, datas->arene, process->PC + 2);
		tmp = 2;
	}
	process->in_stock[2] = vm_ocp_size(datas->arene[(process->PC + 1) % MEM_SIZE], 4, 0);
	process->in_stock[1] = vm_recup_arena_num(1, datas->arene, (process->PC + 2 + tmp) % MEM_SIZE);
	if (process->in_stock[1] > 0 && process->in_stock[1] <= REG_NUMBER)
	{
		process->reg[process->in_stock[1] - 1] = process->in_stock[0];
		process->carry = 1;
	}
	if (!process->in_stock[2])
		process->in_stock[2] = 2;
	process->PC = vm_add_valid(process->PC + process->in_stock[2] + 1);
}
