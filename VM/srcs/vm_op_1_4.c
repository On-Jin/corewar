/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_1_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 23:05:14 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/07 23:05:17 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** #define IND_SIZE				2
** #define REG_SIZE				4
** #define DIR_SIZE				REG_SIZE
** octets de codage parfois non existants
*/

int				vm_op_size(char op_code, int op_flag)
{
	int		i;

	i = 0;
	while (op_code)
	{
		op_code = op_code >> 2;
		if ((op_code & 3) == 1)
			i += REG_SIZE;
		else if ((op_code & 3) == 2 && !op_flag)
			i+= DIR_SIZE;
		else if ((op_code & 3) == 2 && op_flag)
			i+= IND_SIZE;
		else if ((op_code & 3) == 3)
			i += IND_SIZE;
	}
	return (i);
}

int					vm_op_size_next(char op_code, int op_flag)
{
	if ((op_code & 3) == 1)
		return (REG_SIZE);
	else if ((op_code & 3) == 2 && !op_flag)
		return (DIR_SIZE);
	else if ((op_code & 3) == 2 && op_flag)
		return (IND_SIZE);
	else if ((op_code & 3) == 3)
		return (IND_SIZE);
	return (0);
}

/*
** possible de mettre le flag dans op_encode
** op == arene ? gestion de la fin de l'arene...
** possibe d'avoir besoin de moins de paramettres
** fonctions a reecrire de toute facon
** traiter la str comme un unsigned char
*/

int					vm_op_val_next(char op_encod, unsigned char *op, t_process *PC, t_vm *arene, int op_flag)
{
	if (op_encod == 1)
	{
		if (*op > 0 && *op < REG_NUMBER)
			return (*((int *)&PC->reg[*op * REG_SIZE]));
		else
			return (-1);
	}
	if (op_encod == 2 && !op_flag)
		return ((*(int *)(op)) >> ((4 - DIR_SIZE) * 8));
	if (op_encod == 2 && op_flag)
		return ((*(int *)(op)) >> ((4 - IND_SIZE) * 8));
	if (op_encod == 3)
		return (arene[(PC->PC + ((*(int *)(op)) >> ((4 - IND_SIZE) * 8))) % MEM_SIZE]);
}

int					*vm_op_size_next_val(char *op, int op_flag, int *val, t_process *PC)
{
	int		j1;
	int		j2;
	int		j3;

	if (op[1])
		op_size = vm_op_size(op[1], op_flag); // ? utile ?
	else
		return (NULL);
	j1 = vm_op_size_next(op[1] >> 6, op_flag);
	j2 = vm_op_size_next(op[1] >> 4, op_flag);
	j3 = vm_op_size_next(op[1] >> 2, op_flag);
	if (j1 && j1 + 2 <= op_size)
		val[0] = vm_op_val_next((op[1] >> 6 & 3), (op + 2), PC, arene, op_flag);
	if (j2 && j2 + j1 + 2 <= op_size)
		val[1] = vm_op_val_next((op[1] >> 4 & 3), (op + j1 + 2), PC, arene, op_flag);
	if (j3 && j3 + j2 + j1 + 2 <= op_size)
		val[2] = vm_op_val_next((op[1] >> 2 & 3), (op + j2 + j1 + 2), PC, arene, op_flag);
	if ((op[1] >> 6) & 3 == 1)
	return (val);
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

int				vm_op_1(char *op, int op_flag, t_process *PC)
{
	int			op_size;
	int			j;

	if (op[0] == 1 && op[1])
		op_size = vm_op_size(op[1], op_flag);
	else
		return (0);
	/*
	** op_size = 4;
	*/
	PC->live = 1;
	PC->cycle = 10;
	j = *(int *)(&op[2]);
	return (j);
}

/*
**
*/

void			vm_op_2(char *op, int op_flag, t_process *PC)
{
	;
}

/*
** Fork
** pas d'octets de codage
** cree une copie du process
** comment recuperer le PC?
*/

void			vm_op_3(char *op, int op_flag, t_process *PC)
{
	;
}

void			vm_op_4(char *op, int op_flag, t_process *PC)
{
	;
}

void			vm_op_5(char *op, int op_flag, t_process *PC)
{
	;
}

void			vm_op_6(char *op, int op_flag, t_process *PC)
{
	;
}

void			vm_op_7()
{
	;
}

void			vm_op_8()
{
	;
}

void			vm_op_9()
{
	;
}

void			vm_op_10()
{
	;
}

/*
** Sti
** ;
*/

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

void			vm_op_14()
{
	t_process	*new_PC;

	if (op[0] != 15)
		return (0);
	new_PC = vm_copy_process(PC);
	new_PC->PC = (PC->PC + (op[1] * (1 << 8) + op[2])) % MEM_SIZE;
}
