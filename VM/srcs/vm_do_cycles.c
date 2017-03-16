/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_do_cycles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 05:20:51 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/15 15:14:04 by ntoniolo         ###   ########.fr       */
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
		datas->nbr_process--;
		ft_memdel((void **)&process);
	}
	process = datas->begin_process;
	if (process)
		while (process->next)
		{
			process->live = 0;
			if (!process->next->live)
			{
				tmp = process->next;
				tmp_next = (tmp) ? tmp->next : NULL;
				process->next = tmp_next;
				datas->nbr_process--;
				ft_memdel((void **)&tmp);
			}
			process = process->next;
		}
	(process) ? process->live = 0: 0;
}

void		start_op_code(t_datas *datas, t_process *pros, int op_code)
{
	pros->instruction = datas->op_tab[op_code].op_code;
	pros->cycle = datas->op_tab[op_code].cycle;
}

static int	turn_process(t_datas *datas, void (**exec)(t_datas *, t_process *))
{
	t_process *pros;
	unsigned int	cur_ocp;

	pros = datas->begin_process;
	while (pros)
	{
		if (pros->cycle == 0)
		{
			cur_ocp = (unsigned int)datas->arene[pros->PC];
			if (17 <= cur_ocp)
				cur_ocp = 0;
			start_op_code(datas, pros, cur_ocp);
		}
		if (pros->cycle == 1)
		{
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

	cycle = &datas->cycle;
	vm_init_cycle(cycle);
	while (datas->begin_process)
	{
		cycle->cycle = (!cycle->total_cycle) ? 1 : 0;
		while (cycle->cycle_to_die <= 0 || cycle->cycle < cycle->cycle_to_die)
		{
			datas->i_debug = 0;
			//Si flag N
			if (datas->flag & FLAG_N)
			{
				ncurses_key(datas);
				ncurses_show_arene(datas);
				if (datas->key != NC_PAUSE)
				{
					if (datas->key == NC_SBS)
					datas->key = NC_PAUSE;
					turn_process(datas, exec);
					cycle->cycle++;
				}
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
		datas->lives->cycle_lives = 0;
	}
	return(vm_do_cycles_end(datas, cycle));
}
