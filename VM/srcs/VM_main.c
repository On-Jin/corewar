/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VM_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 04:00:52 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/10 02:19:27 by ntoniolo         ###   ########.fr       */
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
		ft_printf("Try Place %i : %s\n", i + 1, champ[i].champ_name);
		ft_memcpy((void *)&arene->arene[(i) *
					(MEM_SIZE / data->player_nbr)], (void *)&champ[i],
					champ[i].champ_size);
		data->start[i] = i * (MEM_SIZE / data->player_nbr);
		ft_printf("End Place %i\n", i + 1);
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

/*
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
*/

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
	process->PC = datas->start[nbr_champ];
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
/*
t_process		*vm_copy_process(t_datas *datas, t_process *process, int PC)
{
	t_process		*new;

	new = vm_create_process(datas);
	ft_memmove(new, process, sizeof(process->reg));
	new->PC = PC;
	return (new);
}
*/

int			turn_process(t_datas *datas)
{
	t_process *pros;

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
//		ft_printf("Size %i\n", pros->cycle);
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

void		vm_init_cycle(t_cycle *cycle)
{
	cycle->cycle = 0;
	cycle->total_cycle = 0;
	cycle->cycle_to_die = CYCLE_TO_DIE;
	cycle->check = 0;
}

int			vm_do_cycles(t_datas *datas)
{
	t_cycle cycle;

	vm_init_cycle(&cycle);
	while (datas->begin_process)
	{
		cycle.cycle = 0;
		while (cycle.cycle < cycle.cycle_to_die)
		{
			/*
			** instructions de cycle...
			*/
			turn_process(datas);
			cycle.cycle++;
		}
		ft_printf("\033[H\033[2J");
		vm_show_arene(datas->arene);
		usleep(40000);
		cycle.total_cycle += cycle.cycle;
		if (datas->lives->cycle_lives >= NBR_LIVE || cycle.check == MAX_CHECKS)
		{
			ft_printf("cycle_to_die = %i\n", cycle.cycle_to_die);
			cycle.cycle_to_die -= CYCLE_DELTA;
			cycle.check = 0;
		}
		else
			cycle.check++;
		datas->lives->cycle_lives = 0;
		if (cycle.cycle_to_die <= 0)
		{
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

int			main(int argc, char **argv)
{
	t_vm		arene;
	t_lives		lives;
	t_champ		champs[MAX_PLAYERS + 1];
	t_datas		datas;

	vm_verif_macro();
	vm_verif_arg(argc);
	vm_innit_to_0(&datas, champs, &arene, &lives);
	datas.player_nbr = vm_create_flags(argv, argc, &datas.flag);
	datas.player_nbr = vm_init_champ(champs, argc, argv, &datas);
	place_champ(&datas, &arene, champs);
	vm_show_arene(&arene);
	vm_init_process(&datas);
	vm_do_cycles(&datas);
	exit(0);
	return (0);
}
