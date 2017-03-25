/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_verif_datas.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 17:56:19 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/23 17:42:00 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** 1 = reg
** 2 = dir
** 4 = ind
** 3 = reg || dir
** 5 = ind || reg
** 6 = dir || ind
** 7 = any
*/

static int		vm_verif_i_cod(char code, char a, char b, char c)
{
	code >>= 2;
	if ((a | b | c) && !code)
		return (0);
	if ((c && !(code & 0b11)) || ((code & 0b11) & !c))
		return (0);
	if ((c ^ (code & 0b11)) && (c & 4) && (code & 3) != 3)
		return (0);
	code >>= 2;
	if ((b && !(code & 0b11)) || ((code & 0b11) & !b))
		return (0);
	if ((b ^ (code & 0b11)) && (b & 4) && (code & 3) != 3)
		return (0);
	code >>= 2;
	if ((a && !(code & 0b11)) || ((code & 0b11) & !a))
		return (0);
	if ((a ^ (code & 0b11)) && (a & 4) && (code & 3) != 3)
		return (0);
	return (1);
}

int				vm_verif_datas(t_datas *datas, t_process *process)
{
	int			a;
	int			b;
	int			c;
	t_op		*op_c;

	op_c = &datas->op_tab[(int)process->instruction];
	if (!op_c->have_ocp)
		return (1);
	a = (op_c->nb_arg >= 1) ? op_c->tab_arg[0] : 0;
	b = (op_c->nb_arg >= 2) ? op_c->tab_arg[1] : 0;
	c = (op_c->nb_arg == 3) ? op_c->tab_arg[2] : 0;
	process->instruc = (unsigned char)datas->arene[vm_add_valid(process->PC +
																			1)];
	return (vm_verif_i_cod(process->instruc, a, b, c));
}
