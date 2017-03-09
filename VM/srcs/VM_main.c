/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VM_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 04:00:52 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/09 17:47:30 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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
}

/*
** a refaire avec les fonctions de creation de liste chainee?
*/
t_process	*vm_create_process(t_datas *datas)
{
	t_process	*process;
	t_process	*tmp;

	if (!(process = ft_memalloc(sizeof(t_process))))
		exit (ft_int_error("Malloc invalide"));
	tmp = datas->begin_process;
	datas->begin_process = process;
	process->next = tmp;
	return (process);
}

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
int			vm_init_process(t_datas *datas)
{
	t_process		*process;
	int				i;

	i = 0;
	while (i < datas->player_nbr)
	{
		process = vm_create_process(datas);
		process->reg[0] = datas->begin_champ[i].champ_nbr;
		i++;
	}
	return (0);
}

t_process		*vm_copy_process(t_datas *datas, t_process *process, int PC)
{
	t_process		*new;

	new = vm_create_process(datas);
	ft_memmove(new, process, sizeof(process->reg) + sizeof(process->in_stock));
	new->PC = PC;
	return (new);
}

int			vm_do_cycles(t_datas *datas)
{
	(void)datas;
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
** Usage
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
