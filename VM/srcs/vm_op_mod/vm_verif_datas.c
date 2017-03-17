/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_verif_datas.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 17:56:19 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/17 17:30:27 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			vm_verif_i_cod(char code, char a, char b, char c, t_datas *datas)
{
	if (datas)
		;
	if (code & 0b11)
{
	//	mvprintw(NC_DEBUG_Y + datas->i_debug++, NC_DEBUG_X, "test 1");
				return (0);
	}
//	mvprintw(NC_DEBUG_Y + datas->i_debug++, NC_DEBUG_X, "n_d = %d n_c = %d, n_b = %d, n_a = %d", code & 3, (code >> 2) & 3, (code >> 4) & 3, (code >> 6) & 3);
	code >>= 2;
	if ( ((c & 1) != (code & 3)) && ((c & 2) != (code & 3)) && ((c & 4) && (code & 3) != 3))
{
//	mvprintw(NC_DEBUG_Y + datas->i_debug++, NC_DEBUG_X, "test 1");
	return (0);
}	code >>= 2;
	if (((b & 1) != (code & 3)) && ((b & 2) != (code & 3)) && ((b & 4) && (code & 3) != 3))
{
//	mvprintw(NC_DEBUG_Y + datas->i_debug++, NC_DEBUG_X, "test 2"); 
	return (0);
}	code >>= 2;
	if (((a & 1) != (code & 3)) && ((a & 2) != (code & 3)) && ((a & 4) && (code & 3) != 3))
{
//		mvprintw(NC_DEBUG_Y + datas->i_debug++, NC_DEBUG_X, "test 3");
		return (0);
}
//		mvprintw(NC_DEBUG_Y + datas->i_debug++, NC_DEBUG_X, "test 4");
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
	c = (op_c->nb_arg = 3) ? op_c->tab_arg[2] : 0;
//	mvprintw(NC_DEBUG_Y + datas->i_debug++, NC_DEBUG_X, "a = %d, b = %d, c = %d, instruc = %d", a, b, c, process->instruction);
	return (vm_verif_i_cod(datas->arene[vm_add_valid(process->PC + 1)], a, b, c, datas));
}
