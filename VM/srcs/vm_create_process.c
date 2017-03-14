/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_create_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 05:14:18 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/13 16:10:59 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** A SUPPRIMER
*/

// pourquoi un static int ???

#include "global.h"

static int			recup_op(t_datas *datas, t_process *pros)
{
	int cur_pros;
	static int i = 0;

	cur_pros = (int)datas->arene->arene[pros->PC] - 1;
	if (cur_pros + 1 >= 0 && cur_pros + 1 <= 16)
	{
		if (cur_pros == -1)
			cur_pros = 16;
		pros->instruction = (char)op_tab[cur_pros].op_code;
		pros->cycle = op_tab[cur_pros].cycle;
	}
	i++;
	return (0);
}

t_process	*vm_create_process(t_datas *datas, int nbr_champ)
{
	t_process	*process;
	t_process	*tmp;

	if (!(process = ft_memalloc(sizeof(t_process))))
		exit (ft_int_error("Malloc invalide"));
	datas->nbr_process++;
	tmp = datas->begin_process;
	datas->begin_process = process;
	process->next = tmp;
	process->PC = datas->start[nbr_champ - 1];
	process->champion = (char)nbr_champ;
	recup_op(datas, process);
	return (process);
}
