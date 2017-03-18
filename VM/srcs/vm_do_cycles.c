/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_do_cycles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 05:20:51 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/17 19:36:23 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		vm_delete_unlive_process(t_datas *datas)
{
	t_process		*tmp;
	t_process		*process;
	t_process		*tmp_next;

	while (datas->begin_process && !(datas->begin_process->live))
	{
		process = datas->begin_process;
		datas->begin_process = process->next;
		datas->inf[(int)process->champion].nbr_process--;
		datas->nbr_process--;
		ft_memdel((void **)&process);
	}
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
				datas->inf[(int)process->champion].nbr_process--;
				datas->nbr_process--;
				ft_memdel((void **)&tmp);
			}
			process = process->next;
		}
	(process) ? process->live = 0: 0;
}

static int	turn_process(t_datas *datas, void (**exec)(t_datas *, t_process *))
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

	t_process *pros;
	unsigned int	cur_ocp;

	pros = datas->begin_process;
	while (pros)
	{
		if (pros->cycle == 1)
			create[(int)pros->instruction](datas, pros);
		pros = pros->next;
	}
	pros = datas->begin_process;
	while (pros)
	{
		if (pros->cycle == 0)
		{
			cur_ocp = (unsigned int)datas->arene[pros->PC];
			(17 <= cur_ocp) ? cur_ocp = 0 : 0;
			start_op_code(datas, pros, cur_ocp);
		}
		if (pros->cycle == 1)
		{
//			cur_ocp = (unsigned int)datas->arene[pros->PC];
//			(17 <= cur_ocp) ? cur_ocp = 0 : 0;
//			pros->instruction = datas->op_tab[cur_ocp].op_code;
			exec[(int)pros->instruction](datas, pros);
		}

		pros->cycle--;
		if (pros->cycle < 0)
			ft_printf("erreur procycle");
		pros = pros->next;
	}
	return (0);
}

static void		vm_destroy_all_process(t_datas *datas)
{
	t_process	*process;
	t_process	*tmp;

	process = datas->begin_process;
	while (process)
	{
		tmp = process;
		process = process->next;
		ft_memdel((void **)&tmp);
	}
}

static void		vm_init_cycle(t_cycle *cycle)
{
	cycle->cycle = 0;
	cycle->total_cycle = 0;
	cycle->cycle_to_die = CYCLE_TO_DIE;
	cycle->check = 1;
}

static int		vm_do_cycles_end(t_datas *datas, t_cycle *cycle)
{
	ft_printf("\n\nlast %d\n\n", datas->lives->last_live);
	ft_printf("\n\nlast live cycle %d\n\n", datas->lives->cycle_last_live);
	endwin();
	ft_printf("total_live %d\n", datas->lives->total_lives);
	ft_printf("total_cycle %d\n", cycle->total_cycle);
	vm_destroy_all_process(datas);
	if (datas->flag & FLAG_N)
		ncurses_end(datas);
	return(ft_int_error("Fin de cycle to die"));
}
//manque 1 cycle ~~~~~~~~~~
int			vm_do_cycles(t_datas *datas, void (**exec)(t_datas *, t_process *))
{
	t_cycle	*cycle;
	int i;


	cycle = &datas->cycle;
	vm_init_cycle(cycle);
	while (datas->begin_process)
	{
		//cycle->cycle = (cycle->total_cycle) == 0 ? 1 : 0;
		cycle->cycle = 0;
		while (cycle->cycle_to_die <= 0 || cycle->cycle < cycle->cycle_to_die)
		{
			datas->i_debug = 0;
			//Si flag N
			if (datas->flag & FLAG_N)
			{
				ncurses_key(datas);
				ncurses_show_arene(datas);
				if (datas->nc.key != NC_PAUSE)
				{
					if (datas->nc.key == NC_SBS)
					datas->nc.key = NC_PAUSE;
					turn_process(datas, exec);
					cycle->cycle++;
				}
				if (cycle->cycle + cycle->total_cycle == 8892)
					sleep(4);
			}
			else // Sinon
			{
				turn_process(datas, exec);
				cycle->cycle++;
			}
			if (cycle->cycle_to_die <= 0)
				break ;
		}
		cycle->total_cycle += cycle->cycle;
		vm_delete_unlive_process(datas);
		if (datas->lives->cycle_lives >= NBR_LIVE || cycle->check == MAX_CHECKS)
		{
			cycle->cycle_to_die -= CYCLE_DELTA;
			cycle->check = 1;
		}
		else
			cycle->check++;
		i = 0;
		while (i < datas->player_nbr)
		{
			datas->inf[i].cycle_lives = 0;
			i++;
		}
		datas->lives->cycle_lives = 0;
	}
	return(vm_do_cycles_end(datas, cycle));
}
