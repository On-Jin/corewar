/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VM_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 04:00:52 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/10 23:19:23 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "global.h"
/*
** etape 1 recuperer et verifier les champions
** etape 2 initialisation de la machine virtuelle
** (alloctaion de l'espace memoire, mise a 0 des process)
** etape 3 pose des champions sur la memoire
** etape 4 run de la machine jusqu'a la fin (lecture des donnes des champions)
** etape 5 fin de la machine, affichage du champion
*/

/*
** char code_instruction;
** char parm_format;
** char parm[REG_SIZE * 4]
*/

/*
** un op de la table
** 1 => nom du paramettre
** 2 => nombre d'arguments
** 3 => arguments acceptees(lien avec le nombre d'arguments)
** 4 => numero op_code
** 5 => nombre de cycles pour realiser l'instruction
** 6 => ?retour/affichage?
** 7 => carry(0 | 1)
** 8 => ?si 1 alors les valeurs direct sont sur 2 octets?
*/

/*
** A faire : define error
** pour verifier que les macros sont valides;
*/

void		place_champ(t_datas *data, t_vm *arene, t_champ champ[MAX_PLAYERS + 1])
{
	int i;
	int size;

	i = 0;
	size = 0;
	while (i < data->player_nbr)
	{
		size += champ[i].champ_size;
		i++;
	}
	i = 0;
	while (i < data->player_nbr)
	{
		ft_memcpy((void *)&arene->arene[(i) *
					(MEM_SIZE / data->player_nbr)], (void *)&champ[i],
					champ[i].champ_size);
		data->start[i] = i * (MEM_SIZE / data->player_nbr);
		if (champ || arene)
			;
		i++;
	}
}

void		vm_innit_to_0(t_datas *datas, t_champ *champs, t_vm *arene,
						t_lives *lives)
{
	ft_bzero((void *)datas, MEM_SIZE);
	ft_bzero((void *)champs, sizeof(t_champ) * (MAX_PLAYERS + 1));
	ft_bzero((void *)lives, sizeof(t_lives));
	ft_bzero((void *)arene->arene, MEM_SIZE);
	datas->lives = lives;
	datas->begin_champ = champs;
	datas->arene = arene;
	datas->nbr_cycles = CYCLE_TO_DIE;
}

/*
** a refaire avec les fonctions de creation de liste chainee?
*/

void		vm_destroy_process(t_process *process, t_datas *datas)
{
	t_process	*process2;

	process2 = datas->begin_process;
	while (process2 && process2->next == process)
		process2 = process2->next;
	if (process2)
	{
		process2 = process->next;
		ft_memdel((void **)&process);
	}
}

void		vm_destroy_all_process(t_datas *datas)
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

int			recup_op(t_datas *datas, t_process *pros)
{
	int cur_pros;
	static int i = 0;

	cur_pros = (int)datas->arene->arene[pros->PC] - 1;
	if (cur_pros + 1 >= 0 && cur_pros + 1 <= 16)
	{
		if (cur_pros == -1)
			cur_pros = 16;
		pros->instruction = op_tab[cur_pros].op_code;
		pros->cycle = op_tab[cur_pros].cycle;
	//	ft_printf("Start %s %i | Size PC : %i, cur_pros = %i\n", op_tab[cur_pros].name, i, pros->PC, cur_pros + 1);
	}
/*	else
		ft_printf("_");
*/	i++;
	return (0);
}

t_process	*vm_create_process(t_datas *datas, int nbr_champ)
{
	t_process	*process;
	t_process	*tmp;

	if (!(process = ft_memalloc(sizeof(t_process))))
		exit (ft_int_error("Malloc invalide"));
	tmp = datas->begin_process;
	datas->begin_process = process;
	process->next = tmp;
	process->PC = datas->start[nbr_champ - 1];
	process->champion = nbr_champ;
	recup_op(datas, process);
	return (process);
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
	return (0);
}

t_process		*vm_copy_process(t_datas *datas, t_process *process, int PC)
{
	t_process		*new;
	t_process		*tmp;

	new = vm_create_process(datas, process->champion);
	tmp = new->next;
	ft_memmove((void *)new, (void *)process, sizeof(process->reg));
	new->next = tmp;
	new->PC = PC;
	return (new);
}

void			vm_delete_unlive_process(t_datas *datas)
{
	t_process		*tmp;
	t_process		*process;
	t_process		*tmp_next;

	while (datas->begin_process && !datas->begin_process->live)
	{
		process = datas->begin_process;
		datas->begin_process = process->next;
		ft_memdel((void **)&process);
	}
	if ((process = datas->begin_process))
		while (process->next)
		{
			if (!process->next->live)
			{
				tmp_next = NULL;
				tmp = process->next;
				if (tmp)
					tmp_next = tmp->next;
				process->next = tmp_next;
				ft_memdel((void **)&tmp);
			}
			process = process->next;
		}
}
/*
int			turn_process(t_datas *datas, int (**exec)(t_datas *, t_process *), int (**create)(t_datas *, t_process *))
{
	t_process *pros;

	(void)create;
	(void)exec;
	int	cur_ocp;
	pros = datas->begin_process;
	while (pros)
	{
		cur_ocp = (pros->PC + 1) % MEM_SIZE;
		pros->cycle--;
		if (pros->cycle == 0)
		{
			//OCP, NB_ARG, NBR_OCTET_DIR
			if (datas->arene->arene[pros->PC] > 0 && datas->arene->arene[pros->PC] < 17)
			{
				if (vm_have_ocp(datas->arene->arene[pros->PC]))
					pros->PC = (pros->PC + 2 + vm_ocp_size(datas->arene->arene[cur_ocp], 3, op_tab[(int)datas->arene->arene[pros->PC] - 1].nbr_octet_dir)) % MEM_SIZE;
				else
					pros->PC = (pros->PC + 1 + vm_havent_ocp(datas->arene->arene[pros->PC])) % MEM_SIZE;
				recup_op(datas, pros);
			}
			else
				pros->PC = (pros->PC + 1) % MEM_SIZE;
		}
		else if (pros->cycle < 0)
		{
			pros->PC = (pros->PC + 1) % MEM_SIZE;
			recup_op(datas, pros);
		}
		pros = pros->next;
	}
	return (0);
}
*/

int			turn_process(t_datas *datas, int (**exec)(t_datas *, t_process *), int (**create)(t_datas *, t_process *))
{
	t_process *pros;
	unsigned int	cur_ocp;

	pros = datas->begin_process;
	while (pros)
	{
		if (pros->cycle == 1)
			exec[(int)pros->instruction](datas, pros);
		if (pros->cycle == 0)
		{
			cur_ocp = datas->arene->arene[pros->PC];
			if (17 <= cur_ocp)
				cur_ocp = 0;
	//*		if (11 == cur_ocp)
	//			ft_printf("cur_ocp = %d\n", cur_ocp);
			create[cur_ocp](datas, pros);
		}
		else
			pros->cycle--;
		if (pros->cycle < 0)
			ft_printf("erreur procycle");
		pros = pros->next;
	}
	return (0);
}

typedef struct		s_cycle
{
	int				cycle;
	int				total_cycle;
	int				cycle_to_die;
	int				check;
}					t_cycle;

# define NBR_FONC 17

int			vm_op_create_create(t_datas *datas, int (**exec)(t_datas *, t_process *));
int			vm_do_cycles(t_datas *datas, int (**exec)(t_datas *, t_process *), int (**create)(t_datas *, t_process *));
int			vm_op_0_exec(t_datas *, t_process *);
int			vm_op_1_exec(t_datas *, t_process *);
int			vm_op_2_exec(t_datas *, t_process *);
int			vm_op_3_exec(t_datas *, t_process *);
int			vm_op_4_exec(t_datas *, t_process *);
int			vm_op_5_exec(t_datas *, t_process *);
int			vm_op_6_exec(t_datas *, t_process *);
int			vm_op_7_exec(t_datas *, t_process *);
int			vm_op_8_exec(t_datas *, t_process *);
int			vm_op_9_exec(t_datas *, t_process *);
int			vm_op_10_exec(t_datas *, t_process *);
int			vm_op_11_exec(t_datas *, t_process *);
int			vm_op_12_exec(t_datas *, t_process *);
int			vm_op_13_exec(t_datas *, t_process *);
int			vm_op_14_exec(t_datas *, t_process *);
int			vm_op_15_exec(t_datas *, t_process *);
int			vm_op_16_exec(t_datas *, t_process *);
int			vm_op_0_create(t_datas *, t_process *);
int			vm_op_1_create(t_datas *, t_process *);
int			vm_op_2_create(t_datas *, t_process *);
int			vm_op_3_create(t_datas *, t_process *);
int			vm_op_4_create(t_datas *, t_process *);
int			vm_op_5_create(t_datas *, t_process *);
int			vm_op_6_create(t_datas *, t_process *);
int			vm_op_7_create(t_datas *, t_process *);
int			vm_op_8_create(t_datas *, t_process *);
int			vm_op_9_create(t_datas *, t_process *);
int			vm_op_10_create(t_datas *, t_process *);
int			vm_op_11_create(t_datas *, t_process *);
int			vm_op_12_create(t_datas *, t_process *);
int			vm_op_13_create(t_datas *, t_process *);
int			vm_op_14_create(t_datas *, t_process *);
int			vm_op_15_create(t_datas *, t_process *);
int			vm_op_16_create(t_datas *, t_process *);







void		vm_init_cycle(t_cycle *cycle)
{
	cycle->cycle = 0;
	cycle->total_cycle = 0;
	cycle->cycle_to_die = CYCLE_TO_DIE;
	cycle->check = 0;
}

int			vm_op_create_exec(t_datas *datas)
{
	int		(*exec[NBR_FONC])(t_datas *, t_process *);

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

int			vm_op_create_create(t_datas *datas, int (**exec)(t_datas *, t_process *))
{
	int		(*create[NBR_FONC])(t_datas *, t_process *);

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

int			vm_do_cycles(t_datas *datas, int (**exec)(t_datas *, t_process *), int (**create)(t_datas *, t_process *))
{
	t_cycle	cycle;

	vm_init_cycle(&cycle);
	while (datas->begin_process)
	{
		cycle.cycle = 0;
		while (cycle.cycle < cycle.cycle_to_die)
		{
			/*
			** instructions de cycle...
			*/

			turn_process(datas, exec, create);
			vm_show_arene(datas, datas->arene);
			cycle.cycle++;
		}
//		ft_printf("\033[H\033[2J");
//		vm_show_arene(datas->arene);
//		usleep(40000);
		cycle.total_cycle += cycle.cycle;
		vm_delete_unlive_process(datas);
		if (datas->lives->cycle_lives >= NBR_LIVE || cycle.check == MAX_CHECKS)
		{
		//	ft_printf("cycle_live = %i\n", datas->lives->cycle_lives);
		//	ft_printf("cycle_to_die = %i\n", cycle.cycle_to_die);
			cycle.cycle_to_die -= CYCLE_DELTA;
			cycle.check = 0;
		}
		else
			cycle.check++;
		datas->lives->cycle_lives = 0;
		if (cycle.cycle_to_die <= 0)
		{
			endwin();
			ft_printf("total_live %d\n", datas->lives->total_lives);
			ft_printf("total_cycle %d\n", cycle.total_cycle);
			exit(ft_int_error("Fin de cycle to die"));// temp
		}
	}
	ft_printf("%d", datas->lives->last_live);
	/*
	** creation d un tableau de fonction(vm_op_0-vm_op_16)
	** creation d un tableau de fonction(vm_op_0_exec-vm_op_16_exec)
	** creation des instructions d'execution des cycles
	** creation des fonctions de verification des fin cycles
	** creation de la boucle verifiant chaque parammetre a chaque cycle;
	** creation de la fonction de fin du jeu;
	*/
	return (0);
}

/*
** le numero du champion ne peut pas etre 0;
** faire une fonction Usage
** faire une condition dans init_champ pour renvoyer erreur si champ > MAX_PLAYERS
*/

void		vm_verif_arg(int argc)
{
	if (argc == 1)
	{
		//Usage
	}
	if (argc > 5)
		exit (ft_int_error("Too many champ !"));
}
/*
WINDOW *create_newwin(int height, int width, int starty, int startx)
{
	WINDOW *local_win;
	local_win = newwin(height, width, starty, startx);
	wrefresh(local_win);
	return local_win;
}
*/
int			main(int argc, char **argv)
{
	t_vm		arene;
	t_lives		lives;
	t_champ		champs[MAX_PLAYERS + 1];
	t_datas		datas;
	int i;

	initscr();
	start_color();
	init_pair(0, COLOR_RED, COLOR_BLACK);
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
//	datas.win = create_newwin(64 + 2, 64 * 3 + 4, 0, 0);
	noecho();
	i = 0;
	vm_verif_macro();
	vm_verif_arg(argc);
	vm_innit_to_0(&datas, champs, &arene, &lives);
	datas.player_nbr = vm_create_flags(argv, argc, &datas.flag);
	datas.player_nbr = vm_init_champ(champs, argc, argv, &datas);
	place_champ(&datas, &arene, champs);
	while (i < datas.player_nbr)
	{
		datas.size_champ[i] = champs[i].champ_size;
		i++;
	}
	vm_init_process(&datas);
	vm_op_create_exec(&datas);
	endwin();
	exit(0);
	return (0);
}
