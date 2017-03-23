/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 19:10:32 by mprevot           #+#    #+#             */
/*   Updated: 2017/03/21 19:10:36 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compiler.h"

t_op		g_op_tab[19] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{"mul", 3, {T_REG, T_REG, T_REG}, 17, 10, "multiplication", 1, 0},
	{"div", 3, {T_REG, T_REG, T_REG}, 18, 10, "division", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

/*
** This function return the configuration for an humain-readable instruction.
**
** get_config("and");
** -> {"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
**		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0}
**
** get_config("noexistlol");
** -> {0, 0, {0}, 0, 0, 0, 0, 0}
*/

t_op		get_config(char *name)
{
	int		i;

	i = 0;
	while (g_op_tab[i].name)
	{
		if (ft_strcmp((char*)g_op_tab[i].name, name) == 0)
			return (g_op_tab[i]);
		i++;
	}
	if (*name)
		error("Unknow instruct\n");
	return (g_op_tab[18]);
}

/*
** This function return an int representing the end of an label.
**
** compiler_compile_get_label("l2:		sti r1, %:live, %1");
** -> 2
**
** compiler_compile_get_label("		and r1, %0, r1");
** -> -1
*/

int			compiler_compile_get_label(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr(LABEL_CHARS, line[i]))
		{
			if (line[i] == LABEL_CHAR)
				return (i);
			else
				return (-1);
		}
		i++;
	}
	return (-1);
}

/*
** This function return an int representing the type
** of the humain-readable argument.
**
** The second argument is the value of g_op_tab[6]
** (See get_config())
**
** get_argtype("r15", 0);
** -> T_REG
**
** get_argtype("-5", 0);
** -> T_IND
*/

int			get_argtype(char *str, int conf)
{
	int		type;

	type = T_UNK;
	if (*str == DIRECT_CHAR)
		type = T_DIR;
	if (*str == 'r')
		type = T_REG;
	if (*str == '-' || ft_isdigit(*str))
		type = T_IND;
	if (*str == DIRECT_CHAR && str[1] == LABEL_CHAR)
		type = T_LABDIR;
	if (str[0] == LABEL_CHAR)
		type = T_LABIND;
	if (type == T_UNK)
		error("Error : Unknow argtype.\n");
	if (type < T_LAB && (type & conf) == 0)
		error("Error : argtype\n");
	if (type == T_LABDIR && (T_DIR & conf) == 0)
		error("Error : argtype label\n");
	if (type == T_LABIND && (T_IND & conf) == 0)
		error("Error : argtype label\n");
	return (type);
}

/*
** This function return an new string representing the label name
** for an opcode argument.
**
** extract_str("%:loop")
** -> strdup("loop");
**
** extract_str("%loop")
** -> strdup("loop");
*/

char		*extract_str(char *str)
{
	int		end;
	int		start;

	end = 0;
	start = 0;
	while (str[start] && !ft_strchr(LABEL_CHARS, str[start]))
		start++;
	end = start;
	while (str[end] && ft_strchr(LABEL_CHARS, str[start]))
		end++;
	return (ft_strsub(str, start, end - start));
}

/*
** This function return the int asked by the opcode argument.
**
** extract_int("r16")
** -> 16
**
** extract_int("%-5")
** -> -5
*/

int			extract_int(char *str)
{
	int		start;

	start = 0;
	while (!(ft_isdigit(str[start]) || str[start] == '-'))
		start++;
	return (ft_atoi(str + start));
}
