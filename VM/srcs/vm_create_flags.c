/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_create_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 04:14:54 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/27 03:07:25 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Options a voir suivant les situations et les besoins
** Actuellement Flag V utilise pour afficher plus d'informations
*/

static void		vm_add_flag(char *line, int *flag)
{
	int		i;
	int		cp;

	i = 1;
	while (line[i])
	{
		cp = *flag;
		('v' == line[i]) ? (*flag |= FLAG_V) : 0;
		('b' == line[i]) ? (*flag |= FLAG_B) : 0;
		('n' == line[i]) ? (*flag |= FLAG_N) : 0;
		('m' == line[i]) ? (*flag |= FLAG_M) : 0;
		('g' == line[i]) ? (*flag |= FLAG_G) : 0;
		('h' == line[i]) ? (*flag |= FLAG_H) : 0;
		if (cp == *flag)
			exit(ft_int_error("Option invalide ou champion invalide"));
		++i;
	}
}

static int		vm_create_dump(t_datas *datas, char **argv, int *flag, int *i)
{
	if (!ft_strcmp(argv[*i], "-h"))
	{
		(*i)++;
		*flag |= FLAG_H;
		datas->dump = ft_atoi(argv[*i]);
		return (1);
	}
	else if (!ft_strcmp(argv[*i], "-dump"))
	{
		(*i)++;
		*flag |= FLAG_DUMP;
		datas->dump = ft_atoi(argv[*i]);
		return (1);
	}
	return (0);
}

int				vm_create_flags(t_datas *datas, char **argv, int argc,
																	int *flag)
{
	int		i;

	i = 1;
	while (i < argc && argv[i])
	{
		if (vm_create_dump(datas, argv, flag, &i))
			;
		else if (*argv[i] == '-' && ft_strcmp(argv[i], "-k"))
			vm_add_flag(argv[i], flag);
		else if (ft_strstr(argv[i], ".cor") || !ft_strcmp(argv[i], "-k"))
			return (i);
		else
			exit(ft_int_error("Option invalide ou champion invalide"));
		++i;
	}
	return (1);
}
