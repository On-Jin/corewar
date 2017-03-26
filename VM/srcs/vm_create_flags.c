/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_create_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 04:14:54 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/23 14:48:27 by gnebie           ###   ########.fr       */
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

/*
** voir les options possibles
*/

int				vm_create_flags(t_datas *datas, char **argv, int argc,
																	int *flag)
{
	int		i;

	i = 1;
	while (i < argc && argv[i])
	{
		if (!ft_strcmp(argv[i], "-d"))
		{
			i++;
			*flag |= FLAG_D;
			datas->dump = ft_atoi(argv[i]);
		}
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
