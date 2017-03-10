/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_1_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 23:05:14 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/09 18:14:42 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define A_CHANGER 1
/*
** Ce dont j'ai besoin pour realiser un op
** un process avec son PC et ses registres, son live, ...
** une structure live pour la commande live;
** l'arene pou les indirects, pour les modifications de valeur...
** ;
*/

/*
** La structure live contient
**		le nbr de live total,
**		le nbr de live du cycle to die en cours
**		le nbr de live par champion total
**		le nbr de live par champion par cycle to die
**		le nom du dernier live
*/




/*
** #define IND_SIZE				2
** #define REG_SIZE				4
** #define DIR_SIZE				REG_SIZE
** octets de codage parfois non existants
*/
/*
** possible de mettre le flag dans op_encode
** op == arene ? gestion de la fin de l'arene...
** possibe d'avoir besoin de moins de paramettres
** fonctions a reecrire de toute facon
** traiter la str comme un unsigned char
*/

/*
**5555;
*/

int				vm_champ_number_to_position(int champ_num, t_champ *champ_tab)
{
	int			i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (champ_num == champ_tab[i].champ_position)
			return (i);
		++i;
	}
	return (-1);
}

int				vm_champ_position_to_number(int champ_pos, t_champ *champ_tab)
{
	if ((unsigned int)champ_pos < CHAMP_MAX_SIZE)
		return (champ_tab[champ_pos].champ_nbr);
	return (0);
}

int			vm_recup_arena_num(int size, t_vm *arena, int PC)
{
	int		i;
	int		res;

	i = 0;
	res = 0;
	if (PC + size < MEM_SIZE && (size & 7) == 1)
	{
		if (size == 4)
			return (res = *(unsigned int *)(&arena->arene[PC]));
		if (size == 2)
			return (res = *(unsigned short *)(&arena->arene[PC]));
		if (size == 1)
			return (res = *(unsigned char *)(&arena->arene[PC]));
	}
	else
		while (i < size)
		{
			res = res * 0x100;
			res += (arena->arene[(PC + (i % IDX_MOD)) % MEM_SIZE]);
			i++;
		}
	return (res);
}

int				vm_recup_indirect_num(t_process *process, t_vm *arene, int adresse)
{
	unsigned int		ind_adress;
	int					val;

	ind_adress = vm_recup_arena_num(2, arene, adresse) + 1;
	if (1)
	{
		val = vm_recup_arena_num(2, arene, ind_adress);
		val = val >> (4 * 8 - IND_SIZE * 8);
		val = vm_recup_arena_num(2, arene, (process->PC + (val % IDX_MOD)) % MEM_SIZE);
		val = val >> (4 * 8 - IND_SIZE * 8);
		return (val);
	}
	return (0);
}

/*
** probleme de verifiaction des erreurs
** possible de prendre une adress de int pour le stocage de la valeur et de rnevoyer
** 1 ou 0 pour bon ou pas bon (comme get next line)
*/

int				vm_recup_process_reg(t_process *process, t_vm *arene, int adresse)
{
	unsigned int		reg;
	int					val;

	reg = vm_recup_arena_num(1, arene, adresse) + 1;
	if (reg <= REG_NUMBER)
	{
		val = process->reg[reg];
		val = val >> (4 * 8 - REG_SIZE * 8);
		return (val);
	}
	return (0);
}

int			*vm_recup_all_process(t_process *process, t_vm *arene, int flag)
{
	int			tmp;
	int			i;
	int			adress;

	i = 3;
	tmp = (arene->arene[(process->PC + 1) % MEM_SIZE]);
	adress = process->PC + 2;
	while (tmp && i > -1)
	{
		if ((tmp & 0xff) == 0b01)
		{
			if ((flag & 0xff) == 1)
				process->in_stock[i] = vm_recup_arena_num(1, arene, adress);
			else
				process->in_stock[i] = vm_recup_process_reg(process,arene, adress);
			adress += 1;
		}
		else if ((tmp & 0xff) == 0b10)
		{
			process->in_stock[i] = vm_recup_arena_num(4, arene, adress);
			adress += 4;//T_DIR;
		}
		else if ((tmp & 0xff) == 0b11)
		{
			process->in_stock[i] = vm_recup_indirect_num(process, arene, adress);
			adress += 2;//T_IND;//??? bizzare dir et ind semblent inversees
		}
		--i;
		flag >>= 8;
		tmp = tmp >> 2;
	}
	return (process->in_stock);
}

/*
** 1 = reg, 2 = dir, 4 = ind; 3 = reg || dir 5 = ind || reg 6 = dir || ind; 7 = any
*/
int			vm_verif_i_code(char code, char a, char b, char c)
{
	if (code & 0b11)
		return (0);
	code >>= 2;
	if (((c & 1) != (code & 3)) && ((c & 2) != (code & 3)) && ((c & 4) && code != 3))
		return (0);
	code >>= 2;
	if (((b & 1) != (code & 3)) && ((b & 2) != (code & 3)) && ((b & 4) && code != 3))
		return (0);
	code >>= 2;
	if (((a & 1) != (code & 3)) && ((a & 2) != (code & 3)) && ((a & 4) && code != 3))
		return (0);
	return (1);
}

/*
** separer les insturctions en 2
** partie 1 creation de la commande et des tours
** ajout des cycles a attendre
** recuperation des valeurs
** met l'instruction a jour;
** calcule du nombre jump apres l'intruction?
** patie 2
** execution de la commande
** modification du carry
** jump du PC
** utilise les valeurs stoquees pour executer la commande
*/

/*
** pour toute valeur autre que 1-16
*/

int				vm_op_0_create(t_datas *datas, t_process *process)
{
	(void)datas;
	process->instruction = 0;
	process->cycle = 1;
	return (0);
}

int				vm_op_0_exec(t_datas *datas, t_process *process)
{
	(void)datas;
	process->PC = (process->PC + 1) % MEM_SIZE;
	return (0);
}

/*
** Live
** faire un special pour live
** donc met +1 a nbr_live
** stoque live nbr du champion pour affichage;
** met param de live a 1
** met champ_live total a +1
** met champ live cycle a +1
*/

int				vm_op_1_create(t_datas *datas, t_process *process)
{
	(void)datas;
	process->in_stock[0] = vm_recup_arena_num(4, datas->arene, process->PC + 1);
	process->in_stock[1] = vm_champ_number_to_position(process->in_stock[0], datas->begin_champ);
	process->cycle = 10;
	process->instruction = 1;
	return (0);
}

int				vm_op_1_exec(t_datas *datas, t_process *process)
{
	datas->lives->total_lives++;
	datas->lives->cycle_lives++;
	process->live = 1;
	process->PC = (process->PC + 5) % MEM_SIZE;
	if (process->in_stock[1] != -1)
	{
		datas->lives->champ_total_lives[process->in_stock[1]]++;
		datas->lives->champ_cycle_lives[process->in_stock[1]]++;
		datas->lives->last_live = process->in_stock[0];
		return (1);
	}
	return (0);
}

/*
** Ld
** Prend un paramètre quelconque et un registre.
** Charge la valeur du premier paramètre dans le registre.
**  il changera le carry.
*/

void			vm_op_2_create(t_datas *datas, t_process *process)
{
	int		tmp;

	(void)datas;
	process->cycle = 5;
	process->instruction = 2;
	tmp = datas->arene->arene[(process->PC + 1) % MEM_SIZE] >> 6;
/*	if ((tmp & 0xff) == 0b01)
		process->in_stock[0] = vm_recup_process_reg(process, datas->arene, process->PC + 2);
*/	if ((tmp & 0x3) == 0b10)
	{
		process->in_stock[0] = vm_recup_arena_num(4, datas->arene, process->PC + 2);
		tmp = 4;
	}
	else if ((tmp & 0x3) == 0b11)
	{
		process->in_stock[0] = vm_recup_indirect_num(process, datas->arene, process->PC + 2);
		tmp = 2;
	}
	else
		ft_printf("fuck %i\n\n", datas->arene->arene[(process->PC + 1) % MEM_SIZE]);
	process->in_stock[2] = vm_ocp_size(datas->arene->arene[(process->PC + 1) % MEM_SIZE], 4, 0);
	process->in_stock[1] = vm_recup_arena_num(1, datas->arene, (process->PC + 2 + tmp) % MEM_SIZE);
}

void			vm_op_2_exec(t_datas *datas, t_process *process)
{
	(void)datas;

	if (process->in_stock[1] > 0 && process->in_stock[1] <= REG_NUMBER)
	{
		process->reg[process->in_stock[1] - 1] = process->in_stock[0];
		process->carry = 1;
	}
	if (!process->in_stock[2])
		process->in_stock[2] = 2;
	process->PC = (process->PC + process->in_stock[2] + 1) % MEM_SIZE;
}

/*
** St
** Prend un registre et un registre ou un indirect,
** et stocke la valeur du registre vers le second paramètre.
** Par exemple, st r1, 42 stocke la valeur de r1 à l’adresse
** (PC + (42 % IDX_MOD))
*/

void			vm_op_3_create(t_datas *datas, t_process *process)
{
	(void)datas;
	process->cycle = 5;
	process->instruction = 3;
/*	if (!(vm_verif_i_code(datas->arene->arene[process->PC + 1 % MEM_SIZE], 1, 5, 0)))
		return ;
*/	vm_recup_all_process(process, datas->arene, 0);
	/*
	** a changer
	*/
	process->in_stock[3] = vm_ocp_size(datas->arene->arene[(process->PC + 1) % MEM_SIZE], 4, 0);
	process->in_stock[0] = vm_recup_arena_num(1, datas->arene, process->PC + 2);
}

void			vm_op_3_exec(t_datas *datas, t_process *process)
{
	(void)datas;
	if (process->in_stock[0] > 0 && process->in_stock[0] < REG_NUMBER)
	{
		process->reg[process->in_stock[0]] = process->PC + (process->in_stock[1] % IDX_MOD);
		process->carry = 0;
	}
	process->PC = (process->PC + process->in_stock[3] + 1) % MEM_SIZE;

//process->carry = 0;
//process->PC = (process->PC + A_CHANGER) % MEM_SIZE;
}

/*
** Add
** Prend trois registres,
** additionne les 2 premiers,
** met le résultat dans le troisième,
** juste avant de modifier le carry.
*/

void			vm_op_4_create(t_datas *datas, t_process *process)
{
	unsigned int tmp;

	(void)datas;
	process->cycle = 10;
	process->instruction = 4;
	tmp = (datas->arene->arene[(process->PC + 1) % MEM_SIZE]);
	if (tmp <= REG_NUMBER)
		process->in_stock[0] = process->reg[tmp];
	else
		process->in_stock[3] = -1;
	tmp = (datas->arene->arene[(process->PC + 2) % MEM_SIZE]);
	if (tmp <= REG_NUMBER)
		process->in_stock[1] = process->reg[tmp];
	else
		process->in_stock[3] = -1;
	process->in_stock[2] = datas->arene->arene[(process->PC + 3) % MEM_SIZE];
	if (process->in_stock[2] > REG_NUMBER || process->in_stock[2] < 0)
		process->in_stock[3] = -1;
	/*
	**recuperation des information
	**traitement d'informations invalides?
	** recuperation du jump?
	*/
}


void			vm_op_4_exec(t_datas *datas, t_process *process)
{
	/*
	** executions
	*/
	(void)datas;
	if (process->in_stock[3] != -1)
	{
		process->reg[process->in_stock[2]] = ((unsigned int)process->in_stock[0] + (unsigned int)process->in_stock[1]) % IDX_MOD;
		process->carry = 1;
	}
	process->in_stock[3] = 0;
	process->PC = (process->PC + 4) % MEM_SIZE;
}



void			vm_op_5_create(t_datas *datas, t_process *process)
{
	unsigned int tmp;

	(void)datas;
	process->cycle = 10;
	process->instruction = 5;
	tmp = (datas->arene->arene[(process->PC + 1) % MEM_SIZE]);
	if (tmp <= REG_NUMBER)
		process->in_stock[0] = process->reg[tmp];
	else
		process->in_stock[3] = -1;
	tmp = (datas->arene->arene[(process->PC + 2) % MEM_SIZE]);
	if (tmp <= REG_NUMBER)
		process->in_stock[1] = process->reg[tmp];
	else
		process->in_stock[3] = -1;
	process->in_stock[2] = datas->arene->arene[(process->PC + 3) % MEM_SIZE];
	if (process->in_stock[2] > REG_NUMBER || process->in_stock[2] < 0)
		process->in_stock[3] = -1;
	/*
	**recuperation des information
	**traitement d'informations invalides?
	** recuperation du jump?
	*/
}

void			vm_op_5_exec(t_datas *datas, t_process *process)
{
	/*
	** executions
	*/
	(void)datas;
	if (process->in_stock[3] != -1)
	{
		process->reg[process->in_stock[2]] = ((unsigned int)process->in_stock[0] - (unsigned int)process->in_stock[1]) % IDX_MOD;
		process->carry = 1;
	}
	process->in_stock[3] = 0;
	process->PC = (process->PC + 4) % MEM_SIZE;
}

void			vm_op_6_create(t_datas *datas, t_process *process)
{
	int i;

	i = 0;
	(void)datas;
	process->cycle = 6;
	process->instruction = 6;
	if (!(vm_verif_i_code(datas->arene->arene[process->PC + 1 % MEM_SIZE], 7, 7, 1)))
	{
		process->in_stock[3] = -1;
		return ;
	}
	vm_recup_all_process(process, datas->arene, 1 << 8);

		/*
	**recuperation des information
	**traitement d'informations invalides?
	** recuperation du jump?
	*/
}

void			vm_op_6_exec(t_datas *datas, t_process *process)
{
	/*
	** executions
	*/
	process->in_stock[2] = process->in_stock[0] & process->in_stock[1];
	(void)datas;
	if (process->in_stock[3] != -1)
		process->carry = 1;
	process->in_stock[3] = vm_ocp_size(datas->arene->arene[(process->PC + 1) % MEM_SIZE], 4, 0);
	if (process->in_stock[3] == 0)
		{ft_printf("exec 6 jump de 0\n");}
	process->PC = (process->PC + process->in_stock[3]) % MEM_SIZE;
}

void			vm_op_7_create(t_datas *datas, t_process *process)
{
	process->cycle = 6;
	process->instruction = 7;

	if (!(vm_verif_i_code(datas->arene->arene[process->PC + 1 % MEM_SIZE], 7, 7, 1)))
	{
		process->in_stock[3] = -1;
		return ;
	}
	vm_recup_all_process(process, datas->arene, 1 << 8);
	/*
	**recuperation des information
	**traitement d'informations invalides?
	** recuperation du jump?
	*/
}

void			vm_op_7_exec(t_datas *datas, t_process *process)
{
	process->in_stock[2] = process->in_stock[0] | process->in_stock[1];
	if (process->in_stock[3] != -1)
		process->carry = 1;
	process->in_stock[3] = vm_ocp_size(datas->arene->arene[(process->PC + 1) % MEM_SIZE], 4, 0);
	if (process->in_stock[3] == 0)
		{ft_printf("exec 7 jump de 0\n"); process->in_stock[3] += 3;}
	process->PC = (process->PC + process->in_stock[3]) % MEM_SIZE;
}

void			vm_op_8_create(t_datas *datas, t_process *process)
{
	process->cycle = 6;
	process->instruction = 8;

	if (!(vm_verif_i_code(datas->arene->arene[process->PC + 1 % MEM_SIZE], 7, 7, 1)))
	{
		process->in_stock[3] = -1;
		return ;
	}
	vm_recup_all_process(process, datas->arene, 1 << 8);
	/*
	**recuperation des information
	**traitement d'informations invalides?
	** recuperation du jump?
	*/
}

void			vm_op_8_exec(t_datas *datas, t_process *process)
{
	process->in_stock[2] = process->in_stock[0] ^ process->in_stock[1];
	if (process->in_stock[3] != -1)
		process->carry = 1;
	process->in_stock[3] = vm_ocp_size(datas->arene->arene[(process->PC + 1) % MEM_SIZE], 4, 0);
	if (process->in_stock[3] == 0)
		{ft_printf("exec 8 jump de 0\n");}
	process->PC = (process->PC + process->in_stock[3]) % MEM_SIZE;
}

void			vm_op_9_create(t_datas *datas, t_process *process)
{
		(void)datas;
	process->cycle = 20;
	process->instruction = 9;
	process->in_stock[0]= vm_recup_indirect_num(process, datas->arene, process->PC + 1);
	/*
	**recuperation des information
	**traitement d'informations invalides?
	** recuperation du jump?
	*/
}

void			vm_op_9_exec(t_datas *datas, t_process *process)
{
	/*
	** executions
	*/
	(void)datas;
	process->carry = 0;
	process->PC = (process->PC + process->in_stock[0]) % MEM_SIZE;
}

void			vm_op_10_create(t_datas *datas, t_process *process)
{
		(void)datas;
	process->cycle = 1;
	process->instruction = 10;
	/*
	**recuperation des information
	**traitement d'informations invalides?
	** recuperation du jump?
	*/
}

void			vm_op_10_exec(t_datas *datas, t_process *process)
{
	/*
	** executions
	*/
		(void)datas;
	process->carry = 0;
	process->PC = (process->PC + A_CHANGER) % MEM_SIZE;
}

void			vm_op_11_create(t_datas *datas, t_process *process)
{
		(void)datas;
	process->cycle = 1;
	process->instruction = 11;
	/*
	**recuperation des information
	**traitement d'informations invalides?
	** recuperation du jump?
	*/
}

void			vm_op_11_exec(t_datas *datas, t_process *process)
{
	/*
	** executions
	*/
		(void)datas;
	process->carry = 0;
	process->PC = (process->PC + A_CHANGER) % MEM_SIZE;
}

void			vm_op_12_create(t_datas *datas, t_process *process)
{
		(void)datas;
	process->cycle = 1;
	process->instruction = 12;
	/*
	**recuperation des information
	**traitement d'informations invalides?
	** recuperation du jump?
	*/
}

void			vm_op_12_exec(t_datas *datas, t_process *process)
{
	/*
	** executions
	*/
		(void)datas;
	process->carry = 0;
	process->PC = (process->PC + A_CHANGER) % MEM_SIZE;
}

void			vm_op_13_create(t_datas *datas, t_process *process)
{
		(void)datas;
	process->cycle = 1;
	process->instruction = 13;
	/*
	**recuperation des information
	**traitement d'informations invalides?
	** recuperation du jump?
	*/
}

void			vm_op_13_exec(t_datas *datas, t_process *process)
{
	/*
	** executions
	*/
		(void)datas;
	process->carry = 0;
	process->PC = (process->PC + A_CHANGER) % MEM_SIZE;
}

void			vm_op_14_create(t_datas *datas, t_process *process)
{
		(void)datas;
	process->cycle = 1;
	process->instruction = 14;
	/*
	**recuperation des information
	**traitement d'informations invalides?
	** recuperation du jump?
	*/
}

void			vm_op_14_exec(t_datas *datas, t_process *process)
{
	/*
	** executions
	*/
		(void)datas;
	process->carry = 0;
	process->PC = (process->PC + A_CHANGER) % MEM_SIZE;
}

void			vm_op_15_create(t_datas *datas, t_process *process)
{
		(void)datas;
	process->cycle = 1;
	process->instruction = 15;
	/*
	**recuperation des information
	**traitement d'informations invalides?
	** recuperation du jump?
	*/
}

void			vm_op_15_exec(t_datas *datas, t_process *process)
{
	/*
	** executions
	*/
		(void)datas;
	process->carry = 0;
	process->PC = (process->PC + A_CHANGER) % MEM_SIZE;
}

void			vm_op_16_create(t_datas *datas, t_process *process)
{
		(void)datas;
	process->cycle = 1;
	process->instruction = 16;
	/*
	**recuperation des information
	**traitement d'informations invalides?
	** recuperation du jump?
	*/
}

void			vm_op_16_exec(t_datas *datas, t_process *process)
{
	/*
	** executions
	*/
		(void)datas;
	process->carry = 0;
	process->PC = (process->PC + A_CHANGER) % MEM_SIZE;
}


/*
** Sti
** ;
*/
/*
void			vm_op_11(char *op, int op_flag, t_process *PC)
{
	int		i;
	int		arg[3];
	int		new_adress;

	i = 2;
	vm_op_size_next_val(op, op_flag, arg, PC);
	arene[(PC->PC + arg[1] + arg[2]) % MEM_SIZE] = arg[0];
}

void			vm_op_12()
{
	t_process	*new_PC;

	if (op[0] != 12)
		return (0);
	new_PC = vm_copy_process(PC);
	new_PC->PC = (PC->PC + ((op[1] * (1 << 8) + op[2]) % IDX_MOD)) % MEM_SIZE;
}

void			vm_op_13()
{
	;
}

void			vm_op_14()
{
	;
}

void			vm_op_15()
{
	t_process	*new_PC;

	if (op[0] != 15)
		return (0);
	new_PC = vm_copy_process(PC);
	new_PC->PC = (PC->PC + (op[1] * (1 << 8) + op[2])) % MEM_SIZE;
}

void			vm_op_16()
{
	;
}

*/
