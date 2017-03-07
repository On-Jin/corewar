/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_create_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 04:14:54 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/07 04:14:56 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		vm_add_flag(char *line, int *flag)
{
	int		i;
	int		cp;

	i = 1;
	while (line[i])
	{
		cp = *flag;
		('d' == line[i]) ? (*flag |= 1) : 0;
		('n' == line[i]) ? (*flag |= 1 << 1) : 0;
		('s' == line[i]) ? (*flag |= 1 << 2) : 0;
		('v' == line[i]) ? (*flag |= 1 << 3) : 0;
		('f' == line[i]) ? (*flag |= 1 << 4) : 0;
		('g' == line[i]) ? (*flag |= 1 << 5) : 0;
		('h' == line[i]) ? (*flag |= 1 << 6) : 0;
		if (cp == *flag)
			exit (ft_int_error("Option invalide ou champion invalide"));
		++i;
	}
}

/*
** voir les options possibles
*/

int			vm_create_flags(char **argv, int argc, int *flag)
{
	int		i;

	i = 1;
	while (i < argc && argv[i])
	{
		if (*argv[i] == '-')
			vm_add_flag(argv[i], flag);
		else if (ft_strstr(argv[i], ".cor"))
			return (i);
		else
			exit (ft_int_error("Option invalide ou champion invalide"));
		++i;
	}
	return (0);
}
