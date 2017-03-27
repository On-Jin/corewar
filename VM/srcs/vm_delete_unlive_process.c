/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_delete_unlive_process.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 02:32:45 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/03/27 03:02:33 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	vm_delete_first_unlive_process(t_datas *datas)
{
	t_process		*process;

	while (datas->begin_process && !(datas->begin_process->live))
	{
		process = datas->begin_process;
		datas->begin_process = process->next;
		datas->inf[(int)process->champion].nbr_process--;
		datas->inf[ALL].nbr_process--;
		ft_memdel((void **)&process);
	}
}

void		vm_delete_unlive_process(t_datas *datas)
{
	t_process		*tmp;
	t_process		*tmp_next;
	t_process		*process;

	vm_delete_first_unlive_process(datas);
	process = datas->begin_process;
	if (process)
		while (process && process->next)
		{
			process->live = 0;
			if (!process->next->live)
			{
				tmp = process->next;
				tmp_next = (tmp) ? tmp->next : NULL;
				process->next = tmp_next;
				datas->inf[(int)tmp->champion].nbr_process--;
				datas->inf[ALL].nbr_process--;
				ft_memdel((void **)&tmp);
			}
			else
				process = process->next;
		}
	(process) ? process->live = 0 : 0;
}
