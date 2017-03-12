/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 05:30:04 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 05:30:05 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int			vm_op_create_create(t_datas *datas, void (**exec)(t_datas *, t_process *))
{
	void		(*create[NBR_FONC])(t_datas *, t_process *);

	if (NBR_FONC != 17)
		exit (ft_int_error("Mauvais nombre de fonctions"));
	create[0] = vm_op_0_create;
	create[1] = vm_op_1_create;
	create[2] = vm_op_2_create;
	create[3] = vm_op_3_create;
	create[4] = vm_op_4_create;
	create[5] = vm_op_5_create;
	create[6] = vm_op_6_create;
	create[7] = vm_op_7_create;
	create[8] = vm_op_8_create;
	create[9] = vm_op_9_create;
	create[10] = vm_op_10_create;
	create[11] = vm_op_11_create;
	create[12] = vm_op_12_create;
	create[13] = vm_op_13_create;
	create[14] = vm_op_14_create;
	create[15] = vm_op_15_create;
	create[16] = vm_op_16_create;
	return (vm_do_cycles(datas, exec, create));
}

static int			vm_op_create_exec(t_datas *datas)
{
	void		(*exec[NBR_FONC])(t_datas *, t_process *);

	if (NBR_FONC != 17)
		exit (ft_int_error("Mauvais nombre de fonctions"));
	exec[0] = vm_op_0_exec;
	exec[1] = vm_op_1_exec;
	exec[2] = vm_op_2_exec;
	exec[3] = vm_op_3_exec;
	exec[4] = vm_op_4_exec;
	exec[5] = vm_op_5_exec;
	exec[6] = vm_op_6_exec;
	exec[7] = vm_op_7_exec;
	exec[8] = vm_op_8_exec;
	exec[9] = vm_op_9_exec;
	exec[10] = vm_op_10_exec;
	exec[11] = vm_op_11_exec;
	exec[12] = vm_op_12_exec;
	exec[13] = vm_op_13_exec;
	exec[14] = vm_op_14_exec;
	exec[15] = vm_op_15_exec;
	exec[16] = vm_op_16_exec;
	return (vm_op_create_create(datas, exec));
}

int			vm_init_process(t_datas *datas)
{
	t_process		*process;
	int				i;

	i = 0;
	while (i < datas->player_nbr)
	{
		process = vm_create_process(datas, i + 1);
		process->reg[0] = datas->begin_champ[i].champ_nbr;
		process->carry = 1;
		i++;
	}
	vm_op_create_exec(datas);
	return (0);
}
