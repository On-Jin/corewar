/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 17:58:40 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/03/22 16:46:48 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft/includes/ft_printf.h"
#include "libft/basic/includes/get_next_line.h"
#include "libft/basic/includes/libft.h"

typedef struct	s_env
{
	int			fd_res;
	char		*line;
	int			dump;
	int			nb_player;
	int			i_champ;
	char		*chr;
	char		cmd[500];
}				t_env;
void		init_env(t_env *e, char **argv);

char	*player[15] = 
{
	"champ/Asombra.cor",
	"champ/doge.cor",
	"champ/Kappa.cor",
	"champ/dubo.cor",
	"champ/Machine-gun.cor",
	"champ/gedeon.cor",
	"champ/MarineKing.cor",
	"champ/jinx.cor",
	"champ/Misaka_Mikoto.cor",
	"champ/justin_bee.cor",
	"champ/Rainbow_dash.cor",
	"champ/littlepuppy.cor",
	"champ/THUNDER.cor",
	"champ/live.cor",
	"champ/Varimathras.cor"
};

void		make_cmd(t_env *e, int i, char *cor, char *ret_cor)
{
	if (i == 0)
		sprintf(e->cmd, "./%s -d %i %s > %s", cor, e->dump, player[e->i_champ], ret_cor);
	else if (i == 1)
		sprintf(e->cmd, "./%s -d %i %s %s > %s", cor, e->dump, player[e->i_champ], player[e->i_champ + 1], ret_cor);
	else if (i == 2)
		sprintf(e->cmd, "./%s -d %i %s %s %s > %s", cor, e->dump, player[e->i_champ], player[e->i_champ + 1], player[e->i_champ + 2], ret_cor);
	else if (i == 3)
		sprintf(e->cmd, "./%s -d %i %s %s %s %s > %s", cor, e->dump, player[e->i_champ], player[e->i_champ + 1], player[e->i_champ + 2], player[e->i_champ + 3], ret_cor);
}

void		print_diff(t_env *e, char *line_us, char *line_zaz)
{
	int i;
	int in_w = 0;

	i = 0;
	while (line_us[i])
	{
		if (!line_zaz[i] || line_us[i] != line_zaz[i])
		{
			if (!in_w)
			{
				ft_printf("\033[31m");
				in_w = 1;
			}
			ft_printf("%c", line_us[i]);
		}
		else
		{
			if (in_w)
			{
				ft_printf("\033[0m");
				in_w = 0;
			}
			ft_printf("%c", line_us[i]);
		}
		i++;
	}
	ft_printf("\033[0m\n");
	i = 0;
	in_w = 0;
	while (line_zaz[i])
	{
		if (!line_us[i] || line_us[i] != line_zaz[i])
		{
			if (!in_w)
			{
				ft_printf("\033[31m");
				in_w = 1;
			}
			ft_printf("%c", line_zaz[i]);
		}
		else
		{
			if (in_w)
			{
				ft_printf("\033[0m");
				in_w = 0;
			}
			ft_printf("%c", line_zaz[i]);
		}
		i++;
	}
	ft_printf("\033[0m\n");
}

int			diff(t_env *e)
{
	int fd_us = 0, fd_zaz = 0;
	char *line_us = NULL, *line_zaz = NULL;

	if (!(fd_us = open("ret_corewar.txt", O_RDONLY)) ||
			!(fd_zaz = open("ret_corewar_zaz.txt", O_RDONLY)))
	{
		ft_printf("recup file invalide\n");
		exit(0);
	}
	ft_printf("\n\n\n");
	while (get_next_line(fd_us, &line_us) > 0 && get_next_line(fd_zaz, &line_zaz) > 0)
	{
		if (ft_strcmp(line_us, line_zaz))
			print_diff(e, line_us, line_zaz);
		ft_strdel(&line_us);
		ft_strdel(&line_zaz);
	}
	close(fd_us);
	close(fd_zaz);
	return (1);
}

int			run_test(t_env *e)
{
	int i;

	i = 0;
	while (i < 4)
	{
		e->i_champ = 0;
		while (e->i_champ + 3 < e->nb_player)
		{
			ft_bzero(e->cmd, 500);
			make_cmd(e, i, "corewar", "ret_corewar.txt");
			system(e->cmd);
			ft_printf("Fin de [%s]\n", e->cmd);
			ft_bzero(e->cmd, 500);
			make_cmd(e, i, "corewar_zaz", "ret_corewar_zaz.txt");
			system(e->cmd);
			ft_printf("Fin de [%s]\n", e->cmd);
	//		diff(e);
			ft_bzero(e->cmd, 500);
			sprintf(e->cmd, "git diff %s %s", "ret_corewar.txt", "ret_corewar_zaz.txt");
			system(e->cmd);
			e->i_champ++;
		}
		i++;
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_env e;
	if (argc <= 1)
	{
		ft_printf("./prog [dump]");
		return (0);
	}
	init_env(&e, argv);
	run_test(&e);
	return(0);
}

void		init_env(t_env *e, char **argv)
{
	ft_bzero(e, sizeof(t_env));
	e->dump = ft_atoi(argv[1]);
	e->nb_player = 15;
}
